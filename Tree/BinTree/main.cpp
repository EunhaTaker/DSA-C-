#include "binTree.h"

int coo(BNode(int) a){
    return a->data;
}
int main(){
    auto t = BinTree<int>();
    auto b = t.insertAsRoot(3);
    auto c = t.insertAsRchild(b, 6);
    c= t.insertAsRchild(b, 4);
    b= t.insertAsLchild(c, 8);
    c= t.insertAsRchild(c, 2);
    b= t.insertAsRchild(b, 1);
    b= t.insertAsRchild(c, 9);
    cout<<t.search(4)->data<<endl;
    cout<<t.search(-1)<<endl;
    t.getRoot()->printTree(coo);

    // BinNode<int> t  =  BinNode<int>(3);
    // t.insertAsRchild(6);
    // t.insertAsLchild(4);
    // cout<<"size:"<<t.size()<<endl;
    // t.travPre(coo);
}