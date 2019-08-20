#include "../BST/bst.h"

template<typename T> class Splay : public BST<T>{
// protected:
public:
Splay(T const& e):BST<T>(e){}
BNode(T) splay(BNode(T));
bool search(T const&);
BNode(T) insert(T const&);
BNode(T) remove(T const&);
};

template<typename T> BNode(T) Splay<T>::splay(BNode(T) v){
    BNode(T) p; BNode(T) g;
    while( (p=v->parent) && (g=p->parent) ){    //巧妙
        if(v->isLChild()){
            if(p->isLChild()){
                g->zig();
                p->zig();
            }else{
                p->zig();
                g->zag();
            }
        }else{
            if(p->isLChild()){
                p->zag();
                g->zig();
            }else{
                g->zag();
                p->zag();
            }
        }
    }
    p = v->parent;
    if(p){
        if(v->isLChild()) p->zig();
        else p->zag();
    }
    this->_root = v;
    return v;
}


template<typename T> bool Splay<T>::search(T const& e){
    BNode(T) v = BST<T>::search(e);
    splay((v)? v : this->_hot);    //若未查找到，将_hot输送至根部
    return v;
}

template<typename T> BNode(T) Splay<T>::insert(T const& e){
    if(search(e))
        return NULL;
    // if(!this->_hot) static_assert
    auto v = new BinNode<T>(e);
    if(e< this->_hot->data){
        this->link(v, this->_hot, v->rchild);
        this->link(v, this->_hot->lchild, v->lchild);
    }else{
        this->link(v, this->_hot, v->lchild);
        this->link(v, this->_hot->rchild, v->rchild);
    }
    this->_root = v;
    return v;
}

template<typename T> BNode(T) Splay<T>::remove(T const& e){
    BNode(T) v = search(e);
    if(!v) return NULL;
    BNode(T) newRoot = this->getMax(v->rchild);
    this->link(newRoot->parent, newRoot->rchild, newRoot->parent->lchild);
    newRoot->parent = NULL;
    this->link(newRoot, v->lchild, newRoot->lchild);
    this->link(newRoot, v->rchild, newRoot->rchild);
    v->release();
}