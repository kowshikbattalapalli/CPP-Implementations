#include <iostream>
#include<vector>
using namespace std;
class PriorityQueue{
    vector<int>arr;
    int size;
    public:
    PriorityQueue(){
        arr.push_back(-1);
        size=0;
    }
    void insertinheap(int value){
        size++;
        arr.push_back(value);
        
        int temp=size;
        while(temp>0){
            if((temp/2)>0 and arr[temp/2]<arr[temp]){
                swap(arr[temp/2],arr[temp]);
                temp=temp/2;
            }
            else{
                return;
            }
            
        }
        
    }

    int topElement(){
        if(size<=0){
            return -1; //No elements
        }
        int val=arr[1];
        arr[1]=arr[size];
        size--;
        arr.pop_back();
        int id=1;
        while(id<=size){
            int left=2*id;
            int right=2*id+1;
            if(left<=size and right<=size and (arr[id]<arr[left] or arr[id]<arr[right])){
                if(arr[left]>arr[right] and arr[left]>arr[id]){
                    swap(arr[left],arr[id]);
                    id=left;
                }
                else if(arr[right]>arr[left] and arr[right]>arr[id]){
                    swap(arr[right],arr[id]);
                    id=right;
                }

            }
            else if(left<=size and arr[left]>arr[id]){
                swap(arr[left],arr[id]);
                id=left;
            }
            else if(right<=size and arr[right]>arr[id]){
                swap(arr[right],arr[id]);
                id=right;
            }
            else{
                break;
            }
        }
        return val;

    }
    void printheap(){
        for(auto t:arr){
            cout<<t<<" ";
        }
        cout<<endl;
    }

};



int main() 
{
    PriorityQueue pq;
    pq.insertinheap(3);
    pq.printheap();
    pq.insertinheap(10);
    pq.printheap();
    pq.insertinheap(5);
    pq.printheap();
    pq.insertinheap(15);
    pq.printheap();
    cout<<pq.topElement()<<endl;

    return 0;
}