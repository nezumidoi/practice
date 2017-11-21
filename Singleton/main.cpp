#include "Singleton.hpp"

int main()
{
	Singleton* singleton1 = Singleton::getInstance();		
	Singleton* singleton2 = Singleton::getInstance();		

	cout << singleton1 << endl;
	cout << singleton2 << endl;

	if (singleton1 == singleton2) {
		cout << "identical object" << endl;
	}
	else {
		cout << "non-identical object" << endl;
	}

	return 0;
}
