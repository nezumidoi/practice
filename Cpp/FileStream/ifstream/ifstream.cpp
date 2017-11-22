#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ifstream ifs;
	string line;
	
	ifs.open("test.txt");

	while (ifs.good()) {
		getline(ifs, line);
		cout << line << endl;
	}
	
	ifs.close();

	return 0;
}
