#pragma once
#include <random>
class Random
{
public:
  Random();
  Random(int seed);

  int next(int minValue, int maxValue);
  int next(int maxValue);
  double nextDouble();
private:
  std::random_device r;
  std::default_random_engine e1;
  std::uniform_real_distribution<double> uniform_dist;
};

