#include "complHeap.h"

void printch(ComplHeap<int> &ch){
    cout<<"size:"<<ch.size()<<endl;
    for(int i=0;i<ch.size();i++){
        cout<<ch[i]<<" ";
    }cout<<endl;
}
void insert(ComplHeap<int> &ch, int e){
    ch.insert(e);
    printch(ch);
}

void nosth(ComplHeap<int> &ch){
    // ComplHeap<int> s = ch;
}

int main(){
    ComplHeap<int> ch = ComplHeap<int>();
    insert(ch,5);
    insert(ch,7);
    insert(ch,4);
    insert(ch,9);

}