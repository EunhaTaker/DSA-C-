#include "complHeap.h"

void printch(ComplHeap<int> &ch){
    cout<<ch.size()<<" elems: ";
    for(int i=0;i<ch.size();i++){
        cout<<ch[i]<<" ";
    }cout<<endl;
}
void insert(ComplHeap<int> &ch, initializer_list<int> il){
    for(int const &e : il){
        ch.insert(e);
    }
    printch(ch);
}

class F{
    public:
    void fprint();
};

class S:public F{
    public:
    void sprint(){
        cout<<"sprint";
    }
}
;
void F::fprint(){
    S s;
    s.sprint();
}

int main(){
    ComplHeap<int> ch = ComplHeap<int>();
    insert(ch,{5,7,4,9});
    ch.removeMax();
    printch(ch);
    insert(ch, {12,6});
}