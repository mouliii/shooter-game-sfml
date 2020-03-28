#include "TextureManager.h"
#include "iostream"

TextureManager& TextureManager::Get()
{
	static TextureManager instance;
	return instance;
}

std::shared_ptr<sf::Texture> TextureManager::AcquireTexture(std::string path)
{
	return Get().I_AcquireTexture(path);
}

void TextureManager::ClearTextures()
{
	Get().I_ClearTextures();
}

TextureManager::~TextureManager()
{
	for (auto it = pTextures.begin(); it != pTextures.end();)
	{
		it = pTextures.erase(it);
	}
}

void TextureManager::I_ClearTextures()
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

std::shared_ptr<sf::Texture> TextureManager::I_AcquireTexture(std::string path)
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
			std::cout << "ei oo tollast textuuria, tyhmä" << std::endl;
		}
		pTextures.insert({ path, pTex });
		return pTex;
	}
}
