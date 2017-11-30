#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <iostream>

using namespace std;

class InvalidValue {
	public:
		const string what;

		InvalidValue(const string& what) : what(what) {}
};


void func(int val) {

	if (val < 0) {
		cout << "NG" << " " << val << endl;
		InvalidValue negative("negative number");
		throw negative;
	}

	cout << "OK" << " " << val <<  endl;
};


#endif /* __EXCEPTION_H__ */
