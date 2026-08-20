#include<bits/stdc++.h>
using namespace std;

class LRUCache{
		class Node{
		 public:
		  int data;
		  int key;
		  Node* prev;
		  Node* nxt;

		  public:
		    Node(int k, int d){
			 data=d;
			 key=k;
			 prev=NULL;
			 nxt=NULL;
			}

		};

		unordered_map<int,Node*>mp;
		Node* start;
		Node* end;
		int counter;
		int capacity;

        public:
		LRUCache(int cap){
            if(cap<=0){
                throw "capacity hould be greater than 0";
            }
			capacity=cap;
			counter=0;
			start=new Node(-1,-1);
			end=new Node(-1,-1);
			start->nxt=end;
			end->prev=start;
		}

		void deleteNode(Node* temp){
			Node* before=temp->prev;
			Node* after=temp->nxt;
			before->nxt=after;
			after->prev=before;
		}

		void AddAtStart(Node* temp){
			Node* tomove=start->nxt;
			start->nxt=temp;
			tomove->prev=temp;
            temp->nxt=tomove;
            temp->prev=start;
		}

		void RemoveLRU(){
			Node* todel=end->prev;
			Node* check=todel->prev;
			check->nxt=end;
            end->prev=check;
			int k=todel->key;
			mp.erase(k);
			delete todel;

		}
		int get(int key){
            auto it=mp.find(key);
			if(it!=mp.end()){
				Node* temp=it->second;
				deleteNode(temp);
				AddAtStart(temp);
				return temp->data;
			}
            return -1;
		}

		void put(int k, int val){
            auto it=mp.find(k);
			if(it!=mp.end()){
			   Node* t=mp[k];
			   t->data=val;
			   deleteNode(t);
			   AddAtStart(t);
               return;
			}

			if(it==mp.end() and mp.size()==capacity){
				RemoveLRU();
			}
            
			Node* nd=new Node(k, val);
            mp[k]=nd;
			AddAtStart(nd);

		}
        ~LRUCache(){
            Node* temp=start;
            while(temp!=NULL){
                Node* curr=temp;
                temp=temp->nxt;
                delete curr;
            }
        }

};

int main(){
	LRUCache list(2);
    cout<<"constructor called"<<endl;
	list.put(1,10);
	cout<<list.get(2)<<endl;
	list.put(2,20);
	cout<<list.get(1)<<endl;
    list.put(3,30);
    cout<<list.get(2)<<endl;
	return 0;


}