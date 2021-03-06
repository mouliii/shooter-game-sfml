#include "Collider.h"
#include <iostream>

extern const int TILEMAPDIMENSIONS;


void Collider::Move(sf::RectangleShape* body, sf::Vector2f delta)
{
	body->move(delta);
}

bool Collider::CheckCollision(sf::RectangleShape* _this, sf::IntRect* other)
{
	sf::Vector2f otherPosition = sf::Vector2f(float(other->left),float(other->top));
	sf::Vector2f otherHalfSize = sf::Vector2f(float(other->width), float(other->height)) / 2.f;
	sf::Vector2f thisPosition = _this->getPosition();
	sf::Vector2f thisHalfSize = _this->getSize() / 2.f;

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;
	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		float push = 0.0f;
		//std::min(std::max(push, 0.0f), 1.0f);
		if (intersectX > intersectY)
		{
			if (deltaX > 0.0f)
			{
				Move(_this, { intersectX * (1.0f - push), 0.0f });
			}
			else
			{
				Move(_this, { -intersectX * (1.0f - push), 0.0f });
			}
		}
		else
		{
			if (deltaY > 0.0f)
			{
				Move(_this, { 0.0f, intersectY * (1.0f - push) });
			}
			else
			{
				Move(_this, { 0.0f , -intersectY * (1.0f - push) });
			}
		}
		return true;
	}
	return false;
}

void Collider::Update(EntityManager* em, Tilemap& tm)
{
	std::vector<std::unique_ptr<Entity>>& e = em->GetEntities();
	std::vector<std::unique_ptr<Bullet>>& b = BulletManager::GetBullets();
	// entity - wall
	for (size_t i = 0; i < e.size(); i++)
	{
		sf::RectangleShape tempRect = e[i]->GetRect();
		sf::Vector2f topLeft = tempRect.getPosition();							// top left
		sf::Vector2f topRight = { topLeft.x + tempRect.getSize().x, topLeft.y - 1 };// top right
		sf::Vector2f botLeft = { topLeft.x, topLeft.y + tempRect.getSize().y }; // bot left
		sf::Vector2f botRight = { topLeft.x + tempRect.getSize().x, topLeft.y + tempRect.getSize().y - 1 };// bot right

		for (int ix = int(topLeft.x); ix <= int(topRight.x); ix += TILEMAPDIMENSIONS)
		{
			for (int iy = int(topLeft.y); iy <= int(botLeft.y); iy += TILEMAPDIMENSIONS)
			{
				if (tm.GetCollisionRect(ix, iy).second)
				{
					if (CheckCollision(&e[i]->GetRect(), &tm.GetCollisionRect(ix, iy).first))
					{
						//std::cout << e[0]->GetPos().x << std::endl;
						//std::cout << "collision" << std::endl;
					}
				}
			}
		}
	}
	// bullet - entity
	for (size_t i = 0; i < b.size(); i++)
	{	// loppaa kaikki entityt ja jos collision -> ja jos ei sama tag -> dmg
		// check collsion
		for (size_t k = 0; k < em->GetEntities().size(); k++)
		{
			// TODO WTF

			if (CRCollision::CircleRectCollision(b[i]->GetCircle(), em->GetEntities()[k]->GetRect()))
			{
				if (b[i]->GetOwner() != e[k]->GetID() )
				{
					//std::cout << i << " " << b.size() << std::endl;
					// TODO dmg source
					em->GetEntities()[k]->GetDmg(1);
					b[i].swap( b.back());
					b.pop_back();
					if (i != 0)
					{
						i--;
					}
					break;
				}
			}
		}
	}
	// bullet wall
	for (size_t i = 0; i < b.size(); i++)
	{
		int left = b[i]->GetCircle().getPosition().x - b[i]->GetCircle().getRadius();
		int top = b[i]->GetCircle().getPosition().y - b[i]->GetCircle().getRadius();
		int width = b[i]->GetCircle().getPosition().x + b[i]->GetCircle().getRadius();
		int height = b[i]->GetCircle().getPosition().y + b[i]->GetCircle().getRadius();

		for (int tempx = left; tempx < width; tempx += TILEMAPDIMENSIONS)
		{
			for (int tempy = top; tempy < height; tempy += TILEMAPDIMENSIONS)
			{
				if (tm.GetCollisionRect(tempx, tempy).second)
				{
					if (CRCollision::CircleRectCollision(b[i]->GetCircle(), tm.GetCollisionRect(tempx, tempy).first))
					{
						//std::cout << pBullets.size() << std::endl;
						b.erase(b.begin() + i);
						break;
					}
				}
			}
		}
	}
	// pelaaja - item
	for (size_t i = 0; i < ItemList::GetWeapons().size(); i++)
	{
		if (em->GetEntities()[0]->GetRect().getGlobalBounds().intersects(ItemList::GetWeapons()[i]->GetRect().getGlobalBounds()))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			{
				if (!keyPressed)
				{
					keyPressed = true;
					em->GetEntities()[0]->PickupWeapon(ItemList::GetWeapons()[i]);
				}
			}
			else
			{
				keyPressed = false;
			}
		}
		for (size_t i = 0; i < ItemList::GetWeapons().size(); i++)
		{
			if (ItemList::GetWeapons()[i] == nullptr)
			{
				ItemList::RemoveWeapon(i);
			}
		}
	}
}




/*

bool Collider::CheckCollision(sf::RectangleShape* _this, sf::IntRect* other, float push)
{
	sf::Vector2f otherPosition = sf::Vector2f(other->left,other->top);
	sf::Vector2f otherHalfSize = sf::Vector2f(other->width, other->height) / 2.f;
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

*/