//Singleton is all about creating only one instance and allowing that to be used all the time 
#include<iostream>
using namespace std;

class Singleton{
	

	//Constructor
	Singleton(){
		cout<<"Constructor Called"<<endl;
	}

	//copy constructor
	Singleton(Singleton&)=delete;

	//copy Assignment constructor
	Singleton& operator=(const Singleton&) = delete;

	//Move Constructor
	Singleton( Singleton&&) = delete;

	//Move Assignment Constructor
	Singleton& operator=(Singleton&&) = delete;


	public:
	static Singleton& getInstance(){
		static Singleton instance;
		return instance;

	}
};
int main(){

Singleton& s1=Singleton::getInstance();
Singleton& s2=Singleton::getInstance();

cout<<&s1 <<" "<<&s2<<endl;
return 0;
}