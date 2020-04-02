#include "Random.h"

Random& Random::Get()
{
	static Random instance;
	return instance;
}

int Random::GetRandomInt(int low, int high)
{
	return Get().I_RandInt(low,high);
}

float Random::GetRandomFloat(float min, float max)
{
	return Get().I_RandFloat(min,max);
}

int Random::I_RandInt(int low, int high)
{
	std::uniform_int_distribution<int> dist(low, high);
	int r = dist(rng);
	return r;
}

float Random::I_RandFloat(float min, float max)
{
	std::uniform_real_distribution<float> dist(min, max);
	float f = dist(rng);
	return f;
}
