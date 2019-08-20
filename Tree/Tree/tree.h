#include "../BinTree/binTree.h"
#define child lchild
#define brother rchild

template<typename T> class Tree : public BinTree<T>{
public:
    Tree(T e):BinTree<T>(e){}
    BNode(T) insertAsChild(BNode(T), T const);
    BNode(T) insertAsBrother(BNode(T), T const);
    template<typename VST> void printTree(VST&, BNode(T)=NULL, int=0);
};

template<typename T> BNode(T) Tree<T>::insertAsChild(BNode(T) v, T const e){
    if(v->child){
        return insertAsBrother(v->child, e);
    }else{
        return v->child = new BinNode<T>(e, v);
    }
}

template<typename T> BNode(T) Tree<T>::insertAsBrother(BNode(T) v, T const e){
    while(v->brother){
        v = v->brother;
    }
    return v->brother = new BinNode<T>(e, v);
}

template<typename T> template<typename VST> void Tree<T>::printTree(VST& visit, BNode(T) v, int depth){
    if(!v) v=this->_root;
    for(int i=0;i<depth-1;i++){
        cout<<"   ";
    }
    if(depth) cout<<"|--";
    cout<<visit(v)<<endl;
    if(v->child) printTree(visit, v->child, depth+1);
    if(v->brother) printTree(visit, v->brother, depth);
}