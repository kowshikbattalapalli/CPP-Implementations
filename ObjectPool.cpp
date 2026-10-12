#include<iostream>
#include<queue>
#include<map>

using namespace std;
class Nodes{
        int data;
        public:
         Nodes(int val){
            data=val;
         }
};

class ObjectPool {
    queue<Nodes*>q;
    map<Nodes*,int>mp;
public:
    ObjectPool(size_t capacity){
        for(int i=0;i<capacity;i++){
            Nodes* nd=new Nodes(1);
            q.push(nd);
            mp[nd]++;
        }
        cout<<"Objects created"<<endl;
    }

    Nodes* acquire(){
        if(!q.empty()){
            cout<<"Acquiring the objects"<<endl;
            auto t=q.front();
            mp[t]=2;
            q.pop();
            return t;
        }
        cout<<"No object available currently.. come again"<<endl;
        return nullptr;
    }

    void release(Nodes* obj){
        if(obj==nullptr){
            cout<<"what is this ?? .. Don't give nullptr to release"<<endl;
            return;
        }
        if(mp.find(obj)!=mp.end() and mp[obj]==2){
            cout<<"Released Object. Thank you "<<endl;
            q.push(obj);
            mp[obj]=1;
            return;
        }
        cout<<"Object doesn't belongs to this pool or already released"<<endl;
        
    }

    ~ObjectPool(){

        cout<<"Destructor cleared"<<endl;
        for(auto temp:mp){
            auto t=temp.first;
            delete t;
            t=nullptr;
        }

        while(!q.empty()){
            q.pop();
        }
    }
};

int main(){
    ObjectPool manager(5);
    Nodes* t1=manager.acquire();
    manager.release(t1);
    Nodes* t2=manager.acquire();
    Nodes* t3=manager.acquire();
    Nodes* t4=manager.acquire();
    Nodes* t5=manager.acquire();
    Nodes* t6=manager.acquire();
    Nodes* t7=manager.acquire();

    manager.release(t6);

    return 0;


}