# AI Playground

This project is based on a project created during the first semester of my year at the University of Sherbrooke (Canada). Named "PetitMoteur3D", it was a way to learn how game engine works by creating our own engine in C++ using DirectX 11 and PhysX.
I kept the "Core" and "Api" part that does the rendering and added IA stuff to it to test and experiment.

### How to build
1. Clone this repository.
2. Build PhysX from NVIDIA's repository, and copy the following .dll files in the `dll` folder :
- PhysX_64.dll
- PhysXCommon_64.dll
- PhysXCooking_64.dll
- PhysXFoundation_64.dll
3. Build PhysX from [NVIDIA's repository](https://github.com/NVIDIA-Omniverse/PhysX) __in debug mode__, and copy the following .lib files in the `libs/debug` folder:
- PhysX_64.lib
- PhysXCommon_64.lib
- PhysXCooking_64.lib
- PhysXExtensions_static_64.lib
- PhysXFoundation_64.lib
- PhysXPvdSDK_static_64.lib
4. Build PhysX from [NVIDIA's repository](https://github.com/NVIDIA-Omniverse/PhysX) __in release mode__, and copy the same .lib files in the `libs/release` folder.
5. Copy PhysX include files from the cloned repo (/physx/include) into the `libs/physx_include` folder.
6. Build FX11 form [Microsoft's repository](https://github.com/microsoft/FX11) and copy the `effects11.lib` file in `libs/release` and the `effects11d.lib` file in `libs/debug`.
7. Download libtorch from [here](https://pytorch.org/). Extract the zip file at the project's root.
8. If you downloaded libtorch with CUDA support, install CUDA if you don't already have it. (https://developer.nvidia.com/cuda-downloads)
9. Run the `rebuild.bat` file to generate the solution files. You need cmake and Visual Sutdio 2022 to be installed.
If you have an issue like "Failed to find nvToolsExt", have a look at https://github.com/pytorch/pytorch/issues/116242.
10. Open the `build/AIPlayground.sln` file with your preferred IDE.
11. Build the solution

### How to run
// TODO
