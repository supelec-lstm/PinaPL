//
//  main.cpp
//  PINAPL
//

#include <iostream>
#include "neurone.h"

int test(int x)
{
    return 2*x;
}

int main(int argc, const char * argv[]) {
	int (*func)(int);
	func = &test;
	std::cout << func(2);
    return 0;
}
