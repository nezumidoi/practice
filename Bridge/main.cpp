#include <iostream>
#include "Bridge.h"

using namespace std;

int main()
{
	cout << "hello" << endl;

	Display* d1 = new Display(new StringDisplayImpl("Hello, Japan."));
	Display* d2 = new CountDisplay(new StringDisplayImpl("Hello, World."));
	CountDisplay* d3 = new CountDisplay(new StringDisplayImpl("Hello, Universe."));

	d1->display();
	d2->display();
	d3->display();
	d3->multiDisplay(5);

	delete d1;

	return 0;
}
