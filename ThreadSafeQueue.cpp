//Implement Thread safe Queue
#include<iostream>
#include<queue>
#include<mutex>
#include<condition_variable>
using namespace std;

template<typename T>

class BlockingQueue {
queue<T>q;
mutable mutex mtx;
condition_variable cv;
public:
    BlockingQueue(){
        //Constructor called
    }
    void push(const T& value){
        unique_lock<mutex>lock(mtx);
        q.push(value);
        cv.notify_one();
    }
    T pop(){
      unique_lock<mutex>lock(mtx); 
      cv.wait(lock,[this]{return !q.empty();});
      auto t=q.front();
      q.pop();
      return t;
      
    }
    
    bool empty() const{
    unique_lock<mutex>lock(mtx);
    return q.empty();
    
    }
    size_t size() const{
    unique_lock<mutex>lock(mtx);
     return q.size();
    
    }
};

int main(){

    BlockingQueue<int> bq;

    thread producer1([&]() {
        for(int i = 1; i <= 50; i++) {
            bq.push(i);
        }
    });

    thread producer2([&]() {
        for(int i = 51; i <= 100; i++) {
            bq.push(i);
        }
    });


    thread consumer1([&]() {
        for(int i = 0; i < 50; i++) {
            bq.pop();
        }
    });

    thread consumer2([&]() {
        for(int i = 0; i < 50; i++) {
            bq.pop();
        }
    });


    producer1.join();
    producer2.join();

    consumer1.join();
    consumer2.join();


    cout << "Remaining elements: "
         << bq.size() << endl;

    return 0;
}
