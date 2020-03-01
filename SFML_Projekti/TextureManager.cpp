#include "TextureManager.h"


TextureManager::~TextureManager()
{
	for (auto it = pTextures.begin(); it != pTextures.end();)
	{
		it = pTextures.erase(it);
	}
}

std::shared_ptr<sf::Texture> TextureManager::AcquireTexture(std::string path)
{
	auto it = pTextures.find(path);
	if (it != pTextures.end())
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

void TextureManager::ClearTextures()
{
	for (auto it = pTextures.begin(); it != pTextures.end();)
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