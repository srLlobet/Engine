#include "ModuleTexture.h"
#include "Globals.h"



ModuleTexture::ModuleTexture()
{
}

ModuleTexture::~ModuleTexture()
{
}



DirectX::ScratchImage ModuleTexture::LoadImage(const wchar_t* imageFileName) {
    DirectX::ScratchImage image; // The ScratchImage object to hold the loaded image
    HRESULT hr = S_OK;

    // Try to load as DDS
    hr = DirectX::LoadFromDDSFile(imageFileName, DirectX::DDS_FLAGS_NONE, nullptr, image);
    if (SUCCEEDED(hr)) {
        LOG( "Loaded DDS image");
        return image;
    }

    // Try to load as TGA
    hr = DirectX::LoadFromTGAFile(imageFileName, nullptr, image);
    if (SUCCEEDED(hr)) {
        LOG("Loaded TGA image");
        return image;
    }

    // Try to load as WIC (BMP, JPEG, PNG, etc.)
    hr = DirectX::LoadFromWICFile(imageFileName, DirectX::WIC_FLAGS_NONE, nullptr, image);
    if (SUCCEEDED(hr)) {
        LOG("Loaded WIC image");
        return image;
    }

    LOG("Error loading image");
}
