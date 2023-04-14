#include <ModuleInterface.h>
#include "PyDevice.h"

// Entry points for loading the dll and creating devices.
MODULE_API void InitializeModuleData()
{
    RegisterDevice(CPyGenericDevice::g_adapterName, MM::GenericDevice, "Generic micro-manager device that is implemented by a Python script");
    RegisterDevice(CPyCamera::g_adapterName, MM::CameraDevice, "Camera device that obtains images from a Python script");
}

MODULE_API MM::Device* CreateDevice(const char* deviceName)
{
    if (!deviceName)
        return nullptr;

    // decide which device class to create based on the deviceName parameter
    if (strcmp(deviceName, CPyGenericDevice::g_adapterName) == 0) {
        return new CPyGenericDevice();
    }
    if (strcmp(deviceName, CPyCamera::g_adapterName) == 0) {
        return new CPyCamera();
    }

    // ...supplied name not recognized
    return nullptr;
}

MODULE_API void DeleteDevice(MM::Device* pDevice)
{
    delete pDevice;
}
