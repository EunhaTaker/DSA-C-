#include "bst.h"
#include<iostream>
using namespace std;

void coo(BNode(int) a){
    cout<<a->data<<" "<<endl;
}
void printh(BNode(int) b){
    cout<<b->height<<endl;
}
int t(int  a=9){
    return a;
}

int main(){
    BST<int> b = BST<int>(5);
    // cout<<b.getRoot()->data;
    b.insert(7);
    b.insert(9);
    b.insert(2);
    b.insert(2);
    b.insert(3);
    // cout<<endl<<endl;
    // b.remove(3);
    // b.remove(5);
    cout<<endl;
    // b.getRoot()->travIn(coo);
    b.search(7);
    // cout<<"566\n"<<setw(19)<<"——";


}