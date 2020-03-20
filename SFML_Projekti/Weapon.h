#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

class Weapon
{
public:
	Weapon(sf::Vector2f pos, std::string texture_path)
		:
		pos(pos)
	{
		sprite.setTexture(*TextureManager::AcquireTexture(texture_path));
		sprite.setPosition(pos);
		sprite.setOrigin(0.f, sprite.getTexture()->getSize().y / 2);
	}
	void Draw(sf::RenderTarget& rt)
	{
		rt.draw(sprite);
	}
	virtual void UpdatePos(sf::Vector2f newPos, sf::Vector2f mouse)
	{
		sf::Vector2f delta = newPos - mouse;
		float rotation = atan2(delta.y, delta.x) * 180 / 3.14f;
		if (delta.x < 0)
		{
			sprite.setScale(1.f, 1.f);
			sprite.setRotation(rotation + 180);
		}
		else
		{
			sprite.setScale(1.f, -1.f);
			sprite.setRotation(rotation + 180);
		}
		pos = newPos;
		sprite.setPosition(pos);
	}
	sf::RectangleShape GetRect()
	{
		sf::RectangleShape rect;
		rect.setPosition(pos);
		rect.setSize(sf::Vector2f(sprite.getTexture()->getSize()) );
		return rect;
	}
protected:
	int magSize = 7;
	int curBullets = magSize;
	sf::Sprite sprite;
	sf::Vector2f pos;
};

class Pistol : public Weapon
{
public:
	Pistol(sf::Vector2f pos, std::string texture_path)
		:
		Weapon(pos, texture_path)
	{ }
	void UpdatePos(sf::Vector2f newPos, sf::Vector2f mouse)
	{
		Weapon::UpdatePos(newPos, mouse);
		if (mouse.x < pos.x)
		{
			pos.x -= 5.f;
		}
		else
		{
			pos.x += 5.f;
		}
	}
private:

};

class Ak47 : public Weapon
{
public:
	Ak47(sf::Vector2f pos, std::string texture_path)
		:
		Weapon(pos, texture_path)
	{
		sprite.setOrigin(sprite.getTexture()->getSize().x / 2, sprite.getTexture()->getSize().y / 2);
	}
	void UpdatePos(sf::Vector2f newPos, sf::Vector2f mouse)
	{
		Weapon::UpdatePos(newPos, mouse);
	}
private:

};