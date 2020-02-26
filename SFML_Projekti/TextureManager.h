#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>
#include <string>
#include <assert.h>

class TextureManager
{
public:
	TextureManager() = default;
	~TextureManager()
	{
		for (auto it = pTextures.begin(); it != pTextures.end() ;)
		{
			it = pTextures.erase(it);
		}
	}

	std::shared_ptr<sf::Texture> AcquireTexture(std::string path)
	{
		auto it = pTextures.find(path);
		if (it != pTextures.end() )
		{
			return it->second;
		}
		else
		{
			auto pTex = std::make_shared<sf::Texture>();
			if (!pTex->loadFromFile(path))
			{
			}
			pTextures.insert({ path, pTex });
			return pTex;
		}
	}
	void ClearTextures()
	{
		for ( auto it = pTextures.begin(); it != pTextures.end() ;)
		{
			if (it->second.unique())
			{
				it = pTextures.erase(it);
			}
			else
			{
				it++;
			}
		}
	}

private:
	std::unordered_map<std::string, std::shared_ptr<sf::Texture>> pTextures;
};