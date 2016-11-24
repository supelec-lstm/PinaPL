//
//  test.hpp
//  PinaPL
//

#ifndef DEF_TEST
#define DEF_TEST

class Test{

protected:
	double randomizer(double m, double M);

public:
	Test();
	virtual void learn() = 0;
	virtual void test() = 0;

};

#endif