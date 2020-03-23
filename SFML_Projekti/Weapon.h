#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"


// TODO max range tänne  - json file
//		bullet size myös?
class Weapon
{
public:
	Weapon(sf::Vector2f pos, std::string texture_path, float fd, int magSize, float reloadTime)
		:
		pos(pos),
		firingDelay(fd),
		magSize(magSize),
		curBullets(magSize),
		reloadTime(reloadTime)
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
	virtual sf::RectangleShape GetRect()
	{
		sf::RectangleShape rect;
		rect.setPosition(pos);
		rect.setSize(sf::Vector2f(sprite.getTexture()->getSize()) );
		return rect;
	}
	const int GetMagSize() { return magSize; }
	const int GetCurBullets() { return curBullets; }
	const float GetFiringDelay() { return firingDelay; }
	const float GetReloadTime() { return reloadTime; }
	void ReduceCurAmmo(int i) { curBullets -= i; }
	void Reload() { curBullets = magSize; }
protected:
	sf::Sprite sprite;
	sf::Vector2f pos;
	float firingDelay;
	int magSize;
	int curBullets;
	float reloadTime;
};

class Pistol : public Weapon
{
public:
	Pistol(sf::Vector2f pos, std::string texture_path)
		:
		Weapon(pos, texture_path, 0.3f, 7, 0.7f)
	{
	}
	void UpdatePos(sf::Vector2f newPos, sf::Vector2f mouse)
	{
		Weapon::UpdatePos(newPos, mouse);
		if (mouse.x < pos.x)
		{
			pos.x -= 5.f;
			sprite.move({ -5.f,0.f });
		}
		else
		{
			pos.x += 5.f;
			sprite.move({ 5.f,0.f });
		}
	}
private:
};

class Ak47 : public Weapon
{
public:
	Ak47(sf::Vector2f pos, std::string texture_path)
		:
		Weapon(pos, texture_path, 0.1f, 30, 1.0f)
	{
		sprite.setOrigin(sprite.getTexture()->getSize().x / 2, sprite.getTexture()->getSize().y / 2);
	}
	void UpdatePos(sf::Vector2f newPos, sf::Vector2f mouse)
	{
		Weapon::UpdatePos(newPos, mouse);
	}
	sf::RectangleShape GetRect() override
	{
		sf::Vector2f tpos;
		tpos.x = pos.x - sprite.getTexture()->getSize().x / 2;
		tpos.y = pos.y - sprite.getTexture()->getSize().y / 2;
		sf::RectangleShape rect;
		rect.setPosition(tpos);
		rect.setSize(sf::Vector2f(sprite.getTexture()->getSize()));
		return rect;
	}
private:
};