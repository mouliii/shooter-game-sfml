#pragma once
#include <random>





class Random
{
public:
	Random(const Random&) = delete;
	static Random& Get();
	static int GetRandomInt(int low, int high);
	static float GetRandomFloat(float min, float max);
private:
	Random() {}
	std::random_device rd;
	std::mt19937 rng{rd()};
	int I_RandInt(int low, int high);
	float I_RandFloat(float min, float max);
};