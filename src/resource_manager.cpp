#include <resource_manager.hpp>
#include <SDL3_image/SDL_image.h>
#include <filesystem>
#include <windows.h>
#include <application.hpp>

bool ResourceManager::Initialize()
{
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    
    _baseResourcesPath = std::filesystem::path(buffer).parent_path().parent_path().parent_path().string();
    _baseResourcesPath.append("\\resources\\");
    return true;
}

template<>
std::shared_ptr<SDL_Texture> ResourceManager::LoadResource<SDL_Texture>(std::string path, SDL_ScaleMode scaleMode)
{
    if (_resources.find(path) != _resources.end())
    {
        if (_resources[path].expired()) return nullptr; //Who knows...
        //There shouldn't be no need to check for ptr validity, since if an item is inside the hashmap it is always valid,
        //because when it invalidates (destructor) it removes by itself from the hashmap.
        return std::static_pointer_cast<SDL_Texture>(_resources[path].lock());
    }

    path.insert(0, _baseResourcesPath);
    SDL_Texture* texture = IMG_LoadTexture(IsaacClone::isaacRenderer, path.c_str());
    if (!texture)
    {
        std::printf("Failed to load image at path: %s\n\tError message: %s\n", path.c_str(), SDL_GetError());
        return nullptr;
    }

    SDL_SetTextureScaleMode(texture, scaleMode);

    std::shared_ptr<SDL_Texture> texturePointer(
        texture,
        [this, path](SDL_Texture* _texture)
        { SDL_DestroyTexture(_texture); _resources.erase(path); });

    _resources[path] = texturePointer;

    return texturePointer;
}