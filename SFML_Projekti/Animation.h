#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"


class Animation
{
public:
	Animation() = default;
	Animation(TextureManager& textures, std::string path, int x, int y, int nFrames, int frameWidth, int frameHeight, float frameTime );
	void Update(float dt);
	void ApplyToSprite(sf::Sprite& sprite);
	void StopAnimation();
	void ResumeAnimation();
	void SetFrameTo(int nFrame);
private:
	void Advance();
private:
	sf::Texture texture;
	float curTime = 0.0f;;
	float frameTime;
	int nFrames;
	int curFrame = 0;
	bool stopAnimation = false;
	std::vector<sf::IntRect> frames;

};