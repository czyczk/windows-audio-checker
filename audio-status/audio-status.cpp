// audio-status.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <initguid.h>
#include <Mmdeviceapi.h>

int main() {
    HRESULT hr;
    IMMDevice* pDevice = NULL;
    IMMDeviceEnumerator* pEnumerator = NULL;
    IPropertyStore* store = nullptr;
    PWAVEFORMATEX deviceFormatProperties;
    PROPVARIANT prop;

    CoInitialize(NULL);

    // get the device enumerator
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (LPVOID*)&pEnumerator);

    // get default audio endpoint
    hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &pDevice);

    hr = pDevice->OpenPropertyStore(STGM_READ, &store);
    if (FAILED(hr)) {
        std::cout << "OpenPropertyStore failed!" << std::endl;
    }

    hr = store->GetValue(PKEY_AudioEngine_DeviceFormat, &prop);
    if (FAILED(hr)) {
        std::cout << "GetValue failed!" << std::endl;
    }

    deviceFormatProperties = (PWAVEFORMATEX)prop.blob.pBlobData;
    std::cout << "Channels    = " << deviceFormatProperties->nChannels << std::endl;
    std::cout << "Sample rate = " << deviceFormatProperties->nSamplesPerSec << std::endl;
    std::cout << "Bit depth   = " << deviceFormatProperties->wBitsPerSample << std::endl;

    system("pause");
    return 0;
}
