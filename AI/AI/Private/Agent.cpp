#include "AI/Public/Agent.h"

#include <iostream>
#include <ostream>

#include "AI/Public/Environment.h"

#include <stdexcept>

#include "AI/Public/InputGatherer.h"
#include "AI/Public/Trainer/Trainer.h"
#include "Api/Public/GameObject/GameObject.h"

void Agent::Initialize()
{
    if (!parentObject)
    {
        throw std::runtime_error("Agent::Initialize: parentObject is nullptr");
    }

    if (!environment)
    {
        throw std::runtime_error("Agent::Initialize: environment is nullptr");
    }

    environment->RegisterAgent(this);

    int inputCount = 0;
    int outputCount = 0;
    Setup(inputCount, outputCount);

    inputGatherer = new InputGatherer(inputCount);
    outputs = new Outputs(outputCount);

    // Create NN
    actionNetwork = FeedForwardNN(inputCount, outputCount, 256, 3);
    criticNetwork = FeedForwardNN(inputCount, 1, 256, 3);

    const auto covVar = torch::full({outputCount}, 0.5f);
    covMat = covVar.diag().to(torch::kCUDA);

    L = torch::cholesky(covMat);
    Lt = L.transpose(0, 1);
}

double log_prob(torch::Tensor x, torch::Tensor mu, torch::Tensor L)
{
    const auto n = mu.size(0);
    const double logDetSigma = 2 * torch::log(L.diagonal(0, -2, -1)).sum().item<double>();
    const double normConst = n * -1.0 / 2.0 * std::log(2 * M_PI);

    // Compute z = L^{-1} (x - mu)
    const auto [solution, b] = torch::triangular_solve(x - mu, L, false, false, false);
    const double expTerm = -0.5 * solution.pow(2).sum().item<double>();

    return normConst - 0.5 * logDetSigma + expTerm;
}

void Agent::Think()
{
    const auto inputs = inputGatherer->Readll();

    const auto options = torch::TensorOptions().device(torch::kCUDA).dtype(torch::kFloat32);
    const auto inputTensor = torch::from_blob(inputs->data(), {static_cast<int64_t>(inputs->size())}, options);

    const auto mean = actionNetwork->forward(inputTensor);

    auto action = torch::randn({mean.size(0)}, options);
    action = mean + action.matmul(Lt);

    const auto logProb = log_prob(action, mean, L);

    const auto actionCpu = action.to(torch::kCPU);

    std::vector actions(actionCpu.data_ptr<float>(), actionCpu.data_ptr<float>() + actionCpu.numel());

    outputs->SetValues(std::move(actions));

    trainer->AddActions(action, logProb);

    ApplyAction(outputs);

    float reward = 0.f;
    ComputeReward(reward);

    trainer->AddReward(reward);
}
