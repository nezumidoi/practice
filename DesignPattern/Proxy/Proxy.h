#ifndef __PROXY_H__
#define __PROXY_H__

#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

class Printable {
	public:
		virtual ~Printable() {};
		virtual void setPrinterName(string name) = 0;
		virtual string getPrinterName() = 0;
		virtual void print(string str) = 0;
};

class Printer : public Printable {
	public:
		Printer() {
			heavyJob("Printer");
		};

		Printer(string name) {
			this->name = name;
			heavyJob("Printer " + name);
		};

		void setPrinterName(string name) {
			this->name = name;
		};

		string getPrinterName() {
			return name;
		};

		void print(string str) {
			cout << "=== " << name << " ===" << endl;
			cout << str << endl;
		};

	private:
		string name;

		void heavyJob(string msg) {
			cout << msg;
			for (int i = 0; i < 5; i++) {
				try {
					sleep(1);
				}
				catch (...) {
				}
				cout << ".";
				fflush(stdout);
			}
			cout << "end" << endl;
		};
};

class PrinterProxy : public Printable {
	public:
		PrinterProxy() {};
		~PrinterProxy() { delete real; };

		PrinterProxy(string name) {
			this->name = name;
		};

		void setPrinterName(string name) {
			if (real != nullptr) {
				real->setPrinterName(name);
			}
			this->name = name;
		};

		string getPrinterName() {
			return name;
		};

		void print(string str) {
			realize();
			real->print(str);
		};

	private:
		void realize() {
			if (real == nullptr) {
				real = new Printer(name);
			}
		};

		string name;
		Printer *real;
};


#endif /*  __PROXY_H__ */
