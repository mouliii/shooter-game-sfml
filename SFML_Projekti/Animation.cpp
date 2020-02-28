#include "Animation.h"
#include <iostream>

Animation::Animation(TextureManager& textures, std::string path, int x, int y, int nFrames, int frameWidth, int frameHeight, float frameTime)
	:
	frameTime(frameTime),
	nFrames(nFrames)
{
	frames.reserve(nFrames);
	texture = *textures.AcquireTexture(path);
	// load
	for (int i = 0; i < nFrames; i++)
	{
		sf::IntRect iRect(sf::Vector2i(x,y),sf::Vector2i(frameWidth,frameHeight));
		frames.push_back(iRect);
		x += frameWidth;
		if (texture.getSize().x >= size_t(x + frameWidth))
		{
			//x -= i * frameWidth;
			//y += frameHeight;
		}
		if (texture.getSize().y > size_t((y + frameHeight) * i))
		{
			assert("y meni kyl iha päi helvettiä, wtf");
		}
	}
}

void Animation::Update(float dt)
{
	curTime += dt;
	//std::cout << curFrame << std::endl;
	while (curTime >= frameTime)
	{
		curTime -= frameTime;
		if (!stopAnimation)
		{
			Advance();
		}
	}
}

void Animation::ApplyToSprite(sf::Sprite& sprite)
{
	sprite.setTextureRect(frames[curFrame]);
}

void Animation::StopAnimation()
{
	stopAnimation = true;
}

void Animation::ResumeAnimation()
{
	stopAnimation = false;
}

void Animation::SetFrameTo(int nFrame)
{
	curFrame = nFrame;
}

void Animation::Advance()
{
	if (++curFrame > nFrames - 1)
	{
		curFrame = 0;
	}
}
