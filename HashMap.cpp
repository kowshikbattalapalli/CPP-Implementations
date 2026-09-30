#include<iostream>
using namespace std;
//Hashmap implementation

class HashMap {
    class Node{
         public:
         int key;
         int value;
         Node* next;
            Node(int k, int v){
                key=k;
                value=v;
                next=NULL;
            }
        };
    
    Node** arr;
    int counter=0;
    size_t capacity;
   
public:
    
    HashMap(size_t capacity = 10){
        this->capacity=capacity;
        arr=new Node*[capacity];
        for(int i=0;i<capacity;i++){
            arr[i]=NULL;
        }
    }

    void insert(const int& key, const int& value){
        int index=key%capacity;
        Node* temp=arr[index];
        if(temp==NULL){
            arr[index]=new Node(key, value);
            counter++;
        }
        else{
            while(temp!=NULL){
            if(temp->key==key){
                temp->value=value;
                return;
            }
                temp=temp->next;
            }
            temp->next=new Node(key,value);
            counter++;
        }

    }

    int find(const int& k){
        //if key is there return value else return -1;
        int index=k%capacity;
        Node* temp=arr[index];
        while(temp!=NULL){
            if(temp->key==k){
                return temp->value;
            }
            temp=temp->next;
        }
        return -1;
    
    }

    bool erase(int k){
        int index=k%capacity;
        Node* temp=arr[index];
        Node* prev=temp;
        while(temp!=NULL){
        if(temp->key==k){
            if(prev==temp){
                arr[index]=temp->next;
                delete temp;
                counter--;
                return true;
            }
            prev->next=temp->next;
            temp->next=NULL;
            delete temp;
            counter--;
            return true;
        }
        prev=temp;
        temp=temp->next;
        }
        return false;
    }

    size_t size() const{
        return counter;
    }

    ~HashMap(){
        for(int i=0;i<capacity;i++){
           //delete each list;
           delete arr[i]; //it deletes first node but need complete deletion
        }
        
    }
};

int main(){
    HashMap mp;
    mp.insert(10, 30);
    cout<<mp.size()<<endl;
    mp.insert(23, 58);
    mp.insert(56, 2);
    mp.insert(6785, 14);
    cout<<"Finding 24:"<<mp.find(24)<<endl;
    cout<<"Finding 10:"<<mp.find(10)<<endl;
    cout<<mp.erase(10)<<endl;
    cout<<"Finding 10:"<<mp.find(10)<<endl;
    return 0;
}