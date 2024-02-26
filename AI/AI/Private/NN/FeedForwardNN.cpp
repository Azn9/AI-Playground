#include "AI/Public/NN/FeedForwardNN.h"

/**
 * \brief Initializes a new FeedForwardNN with the given parameters
 * \param inputDim The number of input neurons 
 * \param outputDim The number of output neurons
 * \param hiddenDim The number of neurons in each hidden layer
 * \param hiddenLayerCount The number of hidden layers
 */
FeedForwardNNImpl::FeedForwardNNImpl(
    const int inputDim,
    const int outputDim,
    const int hiddenDim,
    const int hiddenLayerCount
) : inputDim(inputDim), outputDim(outputDim), hiddenDim(hiddenDim), hiddenLayerCount(hiddenLayerCount)
{
    // Create the input layer
    inputLayer = register_module("inputLayer", torch::nn::Linear(inputDim, hiddenDim));

    // Create the hidden layers
    for (int i = 0; i < hiddenLayerCount; i++)
    {
        hiddenLayers.push_back(register_module("hiddenLayer" + std::to_string(i), torch::nn::Linear(hiddenDim, hiddenDim)));
    }

    // Create the output layer
    outputLayer = register_module("outputLayer", torch::nn::Linear(hiddenDim, outputDim));
}

/**
 * \brief Forward pass for the FeedForwardNN
 * \param x The input tensor
 * \return The output tensor
 */
torch::Tensor FeedForwardNNImpl::forward(torch::Tensor x)
{
    x = torch::relu(inputLayer->forward(x));
    for (int i = 0; i < hiddenLayerCount; i++)
    {
        x = torch::relu(hiddenLayers[i]->forward(x));
    }
    x = outputLayer->forward(x);

    return x;
}
