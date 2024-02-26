#include "AI/Public/Outputs.h"

Outputs::Outputs(const int outputCount) : outputCount(outputCount)
{
    this->values.resize(outputCount);
}

bool Outputs::ReadFloat(float& value)
{
    if (currentIndex < outputCount)
    {
        value = values[currentIndex];
        currentIndex++;
        return true;
    }
    return false;
}

bool Outputs::ReadXMFLOAT2(DirectX::XMFLOAT2& value)
{
    if (currentIndex < outputCount - 1)
    {
        value.x = values[currentIndex];
        value.y = values[currentIndex + 1];
        currentIndex += 2;
        return true;
    }
    return false;
}

bool Outputs::ReadXMFLOAT3(DirectX::XMFLOAT3& value)
{
    if (currentIndex < outputCount - 2)
    {
        value.x = values[currentIndex];
        value.y = values[currentIndex + 1];
        value.z = values[currentIndex + 2];
        currentIndex += 3;
        return true;
    }
    return false;
}

void Outputs::Reset()
{
    currentIndex = 0;
    values.clear();
}

void Outputs::SetValues(std::vector<float> values)
{
    std::swap(this->values, values);
}
