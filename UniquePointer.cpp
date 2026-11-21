//Unique pointer implementation

#include<iostream>
using namespace std;
class unique_pointer{
    int *ptr=nullptr;
    public:

    //constructor
    unique_pointer(int data){
        ptr=new int(data);
    }

    //copy constructor
    unique_pointer(const unique_pointer& obj) = delete;

    //copy assignment operator
    unique_pointer& operator=(const unique_pointer& obj) = delete;

    //move constructor
     unique_pointer(unique_pointer&& obj){
        this->ptr=obj.ptr;
        obj.ptr=NULL;

    }

    //Move assignment operartor
    unique_pointer& operator=(unique_pointer&& obj){
        if(this==&obj){
            return *this;
        }
        delete this->ptr;
        this->ptr=obj.ptr;
        obj.ptr=NULL;
        return *this;
    }

    //destructor
    ~unique_pointer(){
        delete ptr;
        ptr=NULL;
    }

};

int main(){

    unique_pointer p1(10);
    unique_pointer p2(20);

    p1 = move(p2);

    unique_pointer p3(30);
    p3 = move(p1);

    return 0;
}