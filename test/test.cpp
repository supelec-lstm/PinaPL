#include <random>

#include "test.hpp"

Test::Test(){
	return;
}

double Test::randomizer(double m, double M){
	int a = rand();
    double b = static_cast<double>(a)/RAND_MAX * (M - m) + m;
    return b;
}