#include <iostream>
#include "Proxy.h"

using namespace std;

int main()
{
	Printable* p = new PrinterProxy("Alice");
	cout << p->getPrinterName() << endl;

	p->setPrinterName("Bob");
	cout << p->getPrinterName() << endl;

	p->print("Hello, world.");

	return 0;
}
