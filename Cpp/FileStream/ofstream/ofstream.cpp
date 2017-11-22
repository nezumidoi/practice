#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ofstream ofs("out.dat", ios::out | ios::trunc);

	if (ofs.fail()) {
		ofs << "hello" << endl;
	}

	ofs.close();

	return 0;
}
