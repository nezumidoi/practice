#include <iostream>
#include "FactoryMethod.hpp"

int main()
{
	Factory* factory = new IDCardFactory();

	Product* card1 = factory->create("aaa");
	Product* card2 = factory->create("bbb");
	Product* card3 = factory->create("ccc");

	card1->use();
	card2->use();
	card3->use();

	return 0;
}
