//ThreadPool Implementation
#include<iostream>
#include<functional>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<queue>
#include<chrono>

using namespace std;

class ThreadPool{
	int numberofthreads;
	queue<function<void()>>tasks;
	vector<thread>threads;
	mutex mtx;
	condition_variable cv;
	bool stop;
	public:
	 ThreadPool(int numthread){
		
		numberofthreads=numthread;
		stop=false;
		for(int i=0;i<numberofthreads;i++){

		threads.emplace_back([this]{

			while(true){
				
				unique_lock<mutex>lock(mtx);
				cv.wait(lock,[this]{return stop or !tasks.empty();});
				if(stop and tasks.empty()){
					return;
				}
				auto t=tasks.front();
				tasks.pop();
				lock.unlock();
				cv.notify_all();
				t(); //executes the task
			}


		});

		}


	 }

	 void enqueue(function<void()> NewTask){
		//Pushing the elements
		unique_lock<mutex>lock(mtx);
		tasks.push(NewTask);
		cv.notify_one();
	 }
	 ~ThreadPool(){
		{
			unique_lock<mutex>lock(mtx);
			stop=true;
		}

		for(auto& t:threads){
			t.join();
		}

	 }

};

int main(){

	ThreadPool pool(4);

	for(int i=0;i<10;i++){
		pool.enqueue([i]{
		
		     this_thread::sleep_for(chrono::seconds(5));
			cout<<"task:"<<i<<" is getting executed"<<endl;
		
		});

	}
    
    return 0;
}