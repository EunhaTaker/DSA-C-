#include "splay.h"

int daa(BNode(int) t){
    return t->data;
}

class P{
public:
void f(){
    dd();
}
virtual void dd(){
    cout<<"P"<<endl;
}
};

class C : public P{
public:
void dd(){
    cout<<"C"<<endl;
}
};

int main(){
    // auto s = Splay<int>(1);
    Splay<int> s = 1;
    s.insert(2);
    s.insert(3);
    s.insert(4);
    s.insert(5);
    s.insert(6);
    s.insert(7);
    s.insert(8);
    s.insert(9);
    s.search(1);
    s.getRoot()->printTree(daa);
    endl(cout);
    s.search(2);
    s.getRoot()->printTree(daa);
    endl(cout);
    s.search(3);
    s.getRoot()->printTree(daa);
    endl(cout);
    s.search(4);
    s.getRoot()->printTree(daa);
    endl(cout);
}