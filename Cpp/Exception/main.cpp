#include <iostream>
#include "Exception.h"

using namespace std;

int main()
{

	try { 
		func(1);
		func(2);
		func(-4);
		func(10);
		func(9);
	}
	catch (InvalidValue& err) {
		cerr << err.what << endl;
	}

	return 0;
}
