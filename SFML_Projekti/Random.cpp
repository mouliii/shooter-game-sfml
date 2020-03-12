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

int Random::I_RandInt(int low, int high)
{
	std::uniform_int_distribution<int> dist(low, high);
	int r = dist(rng);
	return r;
}
