#include <iostream>
#include "TemplateSample.h"

int main()
{
	TemplateSample<int> obj1(100);
	TemplateSample<float> obj2(3.4);
	TemplateSample<char> obj3('A');

	obj1.print();
	obj2.print();
	obj3.print();

	return 0;
}
