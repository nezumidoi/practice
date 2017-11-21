#ifndef __FACTORYMETHOD_HPP__
#define __FACTORYMETHOD_HPP__

#include <vector>

using namespace std;

class Product {
	public:
		virtual void use() = 0;
};

class Factory {
	public:
		Product* create(string owner) {
			Product *p = createProduct(owner);
			registerProduct(p);
			return p;
		}

		virtual Product* createProduct(string owner) = 0;
		virtual void registerProduct(Product* product) = 0;

};

class IDCard : public Product {
	public:
		IDCard(string owner) {
			cout << owner << endl;
			this->owner = owner;
		};

		virtual void use() {
			cout << "use " << owner << "'s card" << endl;
		};

		string getOwner() {
			return owner;
		};

	private:
		string owner;
};

class IDCardFactory : public Factory {
	public:
		virtual Product* createProduct(string owner) {
			return new IDCard(owner);	
		};

		virtual void registerProduct(Product* product) {
			owners.push_back(static_cast<IDCard*>(product)->getOwner());
		};

		vector<string> getOwner() {
			return owners;
		};

	private:
		vector<string> owners;

};


#endif /* __FACTORYMETHOD_HPP__ */
