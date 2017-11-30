#ifndef __TEMPLATESAMPLE_H__
#define __TEMPLATESAMPLE_H__

#include <iostream>

using namespace std;

template <typename T>
class TemplateSample {
	public:
		TemplateSample(T val);
		~TemplateSample();

		T print();

	private:
		T val;
};

template <typename T>
TemplateSample<T>::TemplateSample(T val) : val(val) {
};

template <typename T>
TemplateSample<T>::~TemplateSample() {
};

template <typename T>
T TemplateSample<T>::print() {
	cout << val << endl;
};

template <>
float TemplateSample<float>::print() {
	cout << "float: " << val << endl;
};

#endif /* __TEMPLATESAMPLE_H__ */
