#pragma once
#include <torch/torch.h>

/**
 * \brief The implementation of the FeedForwardNN, a simple feed forward neural network
 */
class FeedForwardNNImpl : public torch::nn::Module
{
public:
    FeedForwardNNImpl(int inputDim, int outputDim, int hiddenDim, int hiddenLayerCount);

    torch::Tensor forward(torch::Tensor x);

private:
    int inputDim;
    int outputDim;
    int hiddenDim;
    int hiddenLayerCount;

    torch::nn::Linear inputLayer = nullptr;
    torch::nn::Linear outputLayer = nullptr;
    std::vector<torch::nn::Linear> hiddenLayers;
};

TORCH_MODULE(FeedForwardNN);
