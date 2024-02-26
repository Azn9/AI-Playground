#pragma once
#include <DirectXMath.h>
#include <vector>

class InputGatherer
{
public:
    InputGatherer(int inputCount);
    
    void AddValue(float value);
    void AddValue(DirectX::XMFLOAT2 value);
    void AddValue(DirectX::XMFLOAT3 value);

    void Reset();
    std::vector<float>* Readll();

private:
    int inputCount = 0;
    int currentIndex = 0;
    std::vector<float> values;
};
