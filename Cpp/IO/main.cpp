#include <iostream>

using namespace std;

/*                             *\
 * cin:		input from console *
 * cout:	output to console  *
 * cerr:	output to error    *
 * clog:	output to error    *
\*                             */

int main()
{
	string in;

	cin >> in;
	cout << in << endl;
	cerr << "cerr" << endl;
	clog << "clog" << endl;

	return 0;
}
