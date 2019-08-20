#include "binTree.h"

int coo(BNode(int) a){
    return a->data;
}
int main(){
    auto t = BinTree<int>(3);
    BNode(int) b= t.getRoot()->insertAsLC(5);
    b=t.getRoot()->insertAsRC(6);
    b= b->insertAsRC(4);
    b= b->insertAsLC(8);
    b= b->insertAsRC(2);
    b= b->insertAsRC(1);
    b= b->insertAsRC(9);
    b= b->insertAsRC(4);
    b= b->insertAsRC(3);
    cout<<t.search(4)->data<<endl;
    cout<<t.search(-1)<<endl;
    t.getRoot()->printTree(coo);

    // BinNode<int> t  =  BinNode<int>(3);
    // t.insertAsRC(6);
    // t.insertAsLC(4);
    // cout<<"size:"<<t.size()<<endl;
    // t.travPre(coo);
}