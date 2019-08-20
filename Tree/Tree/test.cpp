#include "tree.h"

int gd(BNode(int) v){
    return v->data;
}

int main(){
    auto t = Tree<int>(3);
    BNode(int) n = t.getRoot();
    n=t.insertAsChild(n,4);
    n=t.insertAsBrother(n,5);
    n=t.insertAsChild(n,4);
    t.getRoot()->printTree(gd);
    t.printTree(gd);
}