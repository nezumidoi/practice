#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
	int num = 0x3FF;

	cout << "Dec: " << num << endl;

	cout.unsetf(ios::dec);
	cout.setf(ios::hex);

	cout << "Hex: " << num << endl;

	return 0;
}
