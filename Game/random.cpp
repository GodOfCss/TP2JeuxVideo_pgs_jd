#include "stdafx.h"
#include "random.h"
#include <time.h>

#include <cmath>

Random::Random(int seed)
	: e1(seed)
	, uniform_dist(0, 1.0)
{

}

Random::Random()
	: e1(r())
	, uniform_dist(0, 1.0)
{
}


int Random::next(int minValue, int maxValue)
{
	double pct = nextDouble();
	return minValue + (int)(minValue + pct * (maxValue - minValue));
}

int Random::next(int maxValue)
{
	return next(0, maxValue);
}

double Random::nextDouble()
{
	return uniform_dist(e1);
}
