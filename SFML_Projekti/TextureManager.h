#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>
#include <string>

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	std::shared_ptr<sf::Texture> AcquireTexture(std::string path)
	{
		auto it = pTextures.find(path);
		if (it != pTextures.end() )
		{
			// return it->2
		}
		else
		{
			// load it up
		}
	}

private:
	std::unordered_map<std::string, std::shared_ptr<sf::Texture>> pTextures;
};