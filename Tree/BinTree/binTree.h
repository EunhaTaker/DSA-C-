#include "binNode.h"

template<typename T> class BinTree{
protected:
BNode(T) _root;

public:
BinTree(){_root = nullptr;}
~BinTree(){_root->releaseAll();}
BNode(T) getRoot() const;
BNode(T)& search(T const&);
virtual BNode(T)& searchFrom(T const& , BNode(T)& );
void link(BNode(T) , BNode(T), BNode(T)&);
BNode(T) insertAsRoot(T const&);
// 以下作为测试函数，实际作用不大
BNode(T) insertAsLchild(BNode(T), T const&);
BNode(T) insertAsRchild(BNode(T), T const&);
};


template<typename T> BNode(T) BinTree<T>::insertAsRoot(T const& e){
    return _root = new BinNode<T>(e);
}

template<typename T> BNode(T) BinTree<T>::insertAsLchild(BNode(T) node, T const& e){
    if(!node) return nullptr;
    return node->lchild = new BinNode<T>(e);
}

template<typename T> BNode(T) BinTree<T>::insertAsRchild(BNode(T) node, T const& e){
    if(!node) return nullptr;
    return node->rchild = new BinNode<T>(e);
}

template<typename T> BNode(T) BinTree<T>::getRoot() const{
    return this->_root;
}

template<typename T> BNode(T)& BinTree<T>::search(T const& e){
    return searchFrom(e, _root);
}

template<typename T> BNode(T)& BinTree<T>::searchFrom(T const& e, BNode(T)& v){
    if(e==v->data)return v;
    BNode(T)& t=v;
    if(v->lchild){
        BNode(T)& t=searchFrom(e, v->lchild);
        if(t) return t;
    }
    return (!v->rchild)? v->rchild : searchFrom(e, v->rchild);
}

template<typename T> void BinTree<T>::link(BNode(T) nextParent, BNode(T) nextChild, BNode(T)& pastChild){
    pastChild = nextChild;
    if(nextChild) nextChild->parent = nextParent;
}

