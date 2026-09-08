#include<iostream>
#include<queue>
#include<mutex>
#include<condition_variable>
using namespace std;

template<typename T>
class BoundedBlockingQueue {
    size_t cap;
    queue<T>q;
    mutable mutex mtx; // need to mention mutable to use in const function
    condition_variable cv;
public:
    BoundedBlockingQueue(size_t capacity){
        cap=capacity;
    }

    void push(const T& value){
        unique_lock<mutex>lock(mtx);
        cv.wait(lock,[this]{return q.size()<cap;});
        q.push(value);
        cv.notify_one();

    }
    T pop(){
        unique_lock<mutex>lock(mtx);
        cv.wait(lock,[this]{return q.size()>0;});
        auto top=q.front();
        q.pop();
        cv.notify_one();
        return top;

    }

    size_t size() const{
        size_t ans;
        {
        unique_lock<mutex>lock(mtx);
        ans=q.size();
        }
        return ans;
    
    }
};


int main(){
    
    return 0;

}