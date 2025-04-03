#include "TextureResource.h"

TextureResource::~TextureResource()
{
    UnloadData();
}

void TextureResource::LoadData(const std::string& filename)
{
    data = AEGfxTextureLoad(filename.c_str());
}

void TextureResource::UnloadData()
{
    if (data != nullptr)
        AEGfxTextureUnload(static_cast<AEGfxTexture*>(data));

    data = nullptr;
}
