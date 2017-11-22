#ifndef __BRIDGE_H__
#define __BRIDGE_H__

#include <iostream>
#include <string>

using namespace std;

class DisplayImpl {
	public:
		virtual ~DisplayImpl() {};
		virtual void rawOpen()	= 0;
		virtual void rawPrint()	= 0;
		virtual void rawClose()	= 0;
};

class Display {
	public:
		Display(DisplayImpl *impl) {
			this->impl = impl;
		};

		virtual ~Display() {
			cout << __func__ << endl;
			if (this->impl != nullptr) {
				delete impl;
			}
		};

		void open() {
			impl->rawOpen();
		};

		void print() {
			impl->rawPrint();
		};

		void close() {
			impl->rawClose();
		};

		void display() {
			open();
			print();
			close();
		};

	private:
		DisplayImpl *impl;
};

class CountDisplay : public Display {
	public:
		CountDisplay(DisplayImpl *impl) : Display(impl) {
		};

		~CountDisplay() {
			cout << __func__ << endl;
		};

		void multiDisplay(int times) {
			for (int i = 0; i < times; i++) {
				print();
			}

			close();
		};
};

class StringDisplayImpl : public DisplayImpl {
	public:
		StringDisplayImpl(string str) {
			this->str	= str;
			this->width	= str.length();
		};

		void rawOpen() {
			printLine();
		};

		void rawPrint() {
			cout << "|" << str << "|" << endl;
		};

		void rawClose() {
			printLine();
		};

	private:	
		void printLine() {
			cout << "+";
			for (int i = 0; i < width; i++) {
				cout << "-";
			}
			cout << "+" << endl;
		};

		string str;
		int width;
};

#endif /*  __BRIDGE_H__ */
