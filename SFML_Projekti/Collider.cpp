#include "Collider.h"
#include <iostream>


void Collider::Move(sf::RectangleShape* body, sf::Vector2f delta)
{
	body->move(delta);
}

bool Collider::CheckCollision(sf::RectangleShape* _this, sf::RectangleShape* other, float push)
{
	sf::Vector2f otherPosition = other->getPosition();
	sf::Vector2f otherHalfSize = other->getSize() / 2.f;
	sf::Vector2f thisPosition = _this->getPosition();
	sf::Vector2f thisHalfSize = _this->getSize() / 2.f;

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;
	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		push = std::min(std::max(push, 0.0f),1.0f);
		if (intersectX > intersectY)
		{
			if (deltaX > 0.0f)
			{
				Move(_this, { intersectX * (1.0f - push), 0.0f });
				Move(other, { -intersectX * push, 0.0f });
			}
			else
			{
				Move(_this, { -intersectX * (1.0f - push), 0.0f });
				Move(other, { intersectX * push, 0.0f });
			}
		}
		else
		{
			if (deltaY > 0.0f)
			{
				Move(_this, { 0.0f, intersectY * (1.0f - push) });
				Move(other, { 0.0f , -intersectY * push });
			}
			else
			{
				Move(_this, { 0.0f , -intersectY * (1.0f - push) });
				Move(other, { 0.0f, intersectY * push });
			}
		}
		return true;
	}
	return false;
}

void Collider::Update(std::vector<std::unique_ptr<Entity>>& e, std::vector<std::unique_ptr<Tile>>& t)
{
	
	for (size_t i = 0; i < e.size(); i++)
	{
		// entity tiles chekki kö tähän?
		for (size_t j = 0; j < t.size(); j++)
		{
			if (!t[j]->isPassable() )
			{
				if (CheckCollision(&e[i]->GetRect(), &t[j]->GetRect(), t[j]->GetResistance()))
				{
					//std::cout << e[0]->GetPos().x << std::endl;
					//std::cout << "collision" << std::endl;
				}
			}
		}
	}
	for (size_t i = 0; i < t.size(); i++)
	{
		// tile to tile
	}
}
