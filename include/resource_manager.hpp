#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include <SDL3/SDL.h>

class ResourceManager
{
public:
	ResourceManager(const ResourceManager& other) = delete;
	void operator=(const ResourceManager& other) = delete;

	static ResourceManager& GetInstance()
	{
		static ResourceManager instance;
		return instance;
	}

	bool Initialize();

	template<typename T, typename ...Args>
	std::shared_ptr<T> LoadResource(std::string path, Args... args);

protected:
	ResourceManager() = default;

	std::unordered_map<std::string, std::weak_ptr<void>> _resources;

	std::string _baseResourcesPath = "";
};