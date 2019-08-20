#include "binNode.h"

template<typename T> class BinTree{
protected:
BNode(T) _root;

public:
BinTree(T const& e){_root = new BinNode<T>(e);}
~BinTree(){_root->releaseAll();}
BNode(T) getRoot() const;
BNode(T)& search(T const&);
virtual BNode(T)& searchFrom(T const& , BNode(T)& );
void link(BNode(T) , BNode(T), BNode(T)&);
};

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

