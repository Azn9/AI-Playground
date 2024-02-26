#pragma once
#include <DirectXMath.h>
#include <vector>

class Outputs
{
public:
    Outputs(int outputCount);
    
    bool ReadFloat(float &value);
    bool ReadXMFLOAT2(DirectX::XMFLOAT2 &value);
    bool ReadXMFLOAT3(DirectX::XMFLOAT3 &value);

    void Reset();
    void SetValues(std::vector<float> values);

private:
    int outputCount = 0;
    int currentIndex = 0;
    std::vector<float> values;
};
