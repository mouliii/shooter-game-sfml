#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>
#include <string>
#include <assert.h>

class TextureManager
{
public:
	TextureManager(const TextureManager&) = delete;
	static TextureManager& Get();
	static std::shared_ptr<sf::Texture> AcquireTexture(std::string path);
	static void ClearTextures();
private:
	~TextureManager();
	TextureManager() {};
	std::unordered_map<std::string, std::shared_ptr<sf::Texture>> pTextures;
private:
	void I_ClearTextures();
	std::shared_ptr<sf::Texture> I_AcquireTexture(std::string path);
};