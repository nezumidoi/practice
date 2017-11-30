#include <iostream>

using namespace std;

template <typename T>
T func(T val1, T val2) {
	if (val1 > val2) {
		return val1;
	}
	else {
		return val2;
	}
}

int main()
{
	cout << func(4, 2) << endl;
	cout << func(1.0, 2.4) << endl;
	cout << func('F', 'K') << endl;

	return 0;
}
