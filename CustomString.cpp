#include<iostream>
using namespace std;
class String {
	char* start;
	int size;

public:
	//constructor
	String(const char* temp) {
		//char* t1=temp;
		int sz = 0;
		while (*(temp + sz) != '\0') {
			sz++;
		}
		size = sz;
		start = new char[size + 1];
		int i = 0;
		while (i < sz) {
			*(start + i) = *(temp + i);
			i++;
		}
		start[sz] = '\0';

	}

	int length(char* temp) {
		int sz = 0;
		while (*temp != '\0') {
			sz++;
			temp = temp + 1;
		}
		return sz;

	}

	//copy constructor
	String(const String& other) {
		size = length(other.start);
		start = new char[size + 1];
		int i = 0;
		while (i < size) {
			*(start + i) = *(other.start + i);
			i++;
		}
		start[size] = '\0';


	}


	//Copy Assignment operator
	String& operator=(const String& other) {

		if (this == &other) {
			return *this;
		}
		char* temp = other.start;

		//first clear already assigned one
		delete[] start;
		size = length(temp);
		start = new char[size + 1];
		int i = 0;
		while (i < size) {
			*(start + i) = *(temp + i);
			i++;
		}
		start[size] = '\0';
		return *this;

	}

	//Move Constructor
	String(String&& other) {
		char* temp = other.start;
		size = other.size;
		start = other.start;

		other.size = 0;
		other.start = nullptr;
	}

	//Move copy assignment
	String& operator=(String&& other) {
		if (this == &other) {
			return *this;
		}
		char* temp = other.start;
		size = 0;
		delete[] start;
		size = other.size;
		start = other.start;
		other.size = 0;
		other.start = nullptr;

		return *this;

	}


	//Destructor
	~String() {
		if (start != nullptr)
		{
			delete[] start;
		}
		start = nullptr;
		size = 0;

	}
};

int main() {

	return 0;
}