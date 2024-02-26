#include "AI/Public/InputGatherer.h"

#include <iostream>
#include <ostream>

InputGatherer::InputGatherer(const int inputCount) : inputCount(inputCount)
{
}

void InputGatherer::AddValue(float value)
{
    if (currentIndex < inputCount)
    {
        values.push_back(value);
        currentIndex++;
    } else
    {
        std::cerr << "InputGatherer::AddValue: Too many values added" << std::endl;
    }
}

void InputGatherer::AddValue(DirectX::XMFLOAT2 value)
{
    if (currentIndex < inputCount - 1)
    {
        values.push_back(value.x);
        values.push_back(value.y);
        currentIndex += 2;
    } else
    {
        std::cerr << "InputGatherer::AddValue: Too many values added" << std::endl;
    }
}

void InputGatherer::AddValue(DirectX::XMFLOAT3 value)
{
    if (currentIndex < inputCount - 2)
    {
        values.push_back(value.x);
        values.push_back(value.y);
        values.push_back(value.z);
        currentIndex += 3;
    } else
    {
        std::cerr << "InputGatherer::AddValue: Too many values added" << std::endl;
    }
}

void InputGatherer::Reset()
{
    values.clear();
    currentIndex = 0;
}

std::vector<float>* InputGatherer::Readll()
{
    return &values;
}
