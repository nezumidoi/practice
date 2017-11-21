#ifndef __SINGLETON_HPP__
#define __SINGLETON_HPP__

#include <iostream>

using namespace std;


class Singleton {

	public:
		~Singleton() {
			if (!singleton) {
				delete singleton;
			}
		};

		static Singleton* getInstance() {
			if (singleton == nullptr) {
				singleton = new Singleton;
			}
			return singleton;			
		};

	private:
		Singleton() {};

		static Singleton* singleton;
		
};

Singleton* Singleton::singleton = nullptr;	

bool operator==(const Singleton &lhs, const Singleton &rhs) {
	if (lhs == rhs) {
		return true;
	}
	else {
		return false;
	}
};

#endif /* __SINGLETON_HPP__ */
