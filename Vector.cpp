#include<iostream>
using namespace std;

// Vector implementation covering dynamic resizing, templates, deep copy, move semantics and Rule of 5
template <typename T>
class Myvector{
    int capacity;
    int current;
    T* data;

    public:

    // constructor
    Myvector(){
        capacity=1;
        current=0;
        data=new T[1];
    }

    //push_back - doubles capacity when existing capacity is exhausted
    void push_back(T val){
        if(current<capacity){
            *(data+current)=val;
            current++;
            return;
        }

        capacity*=2;
        T* temp=new T[capacity];

        for(int i=0;i<current;i++){
            *(temp+i)=*(data+i);
        }

        *(temp+current)=val;
        current++;

        delete[] data;
        data=temp;
        temp=nullptr;
    }

    //copy constructor - performs deep copy
    Myvector(const Myvector& other){
        current=other.current;
        capacity=other.capacity;
        data= new T[capacity];

        for(int i=0;i<current;i++){
            data[i]=other.data[i];
        }
    }

    // copy assignment operator - handles self assignment and deep copy
    Myvector& operator=(const Myvector& other){

        if(this==&other){
            return *this;
        }

        current=other.current;
        capacity=other.capacity;

        delete[] data;

        data=new T[capacity];

        for(int i=0;i<current;i++){
            data[i]=other.data[i];
        }

        return *this;
    }

    // Move constructor - transfers ownership instead of copying
    Myvector(Myvector&& other){
        current=other.current;
        capacity=other.capacity;
        data=other.data;

        other.data=nullptr;
        other.current=0;
        other.capacity=0;
    }

    // Move assignment operator - releases old memory and takes ownership from other
    Myvector& operator=(Myvector && other){

        if(this== &other){
            return *this;
        }

        delete[] data;

        current=other.current;
        capacity=other.capacity;
        data=other.data;

        other.data=nullptr;
        other.current=0;
        other.capacity=0;

        return *this;
    }

    //pop_back - decreases size without reducing capacity
    void pop_back(){
        if(current==0){
            cout<<"No elements"<<endl;
            return;
        }

        current--;
    }

    void printelements(){
        for(int i=0;i<current;i++){
            cout<<*(data+i)<<" ";
        }
        cout<<endl;
    }

    int size() const{
        return current;
    }

    int capacit() const{
        return capacity;
    }

    //operator[] returns reference so the element can be modified
    T& operator[](const size_t index){
        return data[index];
    }

    //Destructor - releases dynamically allocated memory
    ~Myvector(){
        delete[] data;
    }
};


int main(){

    Myvector<int> v1;

    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);

    Myvector<int> v2;

    v2 = std::move(v1);

    cout << v2[0] << endl;
    cout << v2[1] << endl;
    cout << v2[2] << endl;

    cout << v1.size() << endl;

    return 0;
}