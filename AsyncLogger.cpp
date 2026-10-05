//Async Logger // Multiple producers and one consumer //Producers soawned in main//consumer is spawned in constructor#include<iostream>#include<thread>#include<mutex>#include<condition_variable>#include<queue>#include<string>using namespace std;
#include<iostream>
#include<queue>
#include<thread>
#include<mutex>
#include<condition_variable>
using namespace std;

class AsyncLogger{queue<string> q;
    mutex mtx;
    condition_variable cv;
    bool isStop=false;
    thread consume;
    public:
       AsyncLogger(){consume = thread([this](){while(true){unique_lock<mutex>lock(mtx);
                cv.wait(lock,[this](){return !q.empty() or isStop;});
                if(isStop && q.empty()){break;
                }auto t=q.front();
                q.pop();
                cout<<t<<endl;
            }});
       }void log(string s){unique_lock<mutex>lock(mtx);
            q.push(s);
            cv.notify_one();
       }~AsyncLogger(){{unique_lock<mutex>lock(mtx);
                isStop=true;
            }cv.notify_one();
            consume.join();

       }};
int main(){AsyncLogger logger;
    thread prod1([&](){for(int i=1;i<=100;i++){logger.log("Producer 1 added: " + to_string(i)+ " value");
        }});

    thread prod2([&](){for(int i=1;i<=100;i++){logger.log("Producer 2 added: " + to_string(i)+" value");
        }});

    prod1.join();
    prod2.join();
    return 0;}