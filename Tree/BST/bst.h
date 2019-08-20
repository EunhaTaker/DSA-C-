#include "../BinTree/binTree.h"

template<typename T> class BST : public BinTree<T>{

protected:
BNode(T) _hot;   //用于查找，临时记忆点
public:
BST(T const& e):BinTree<T>(e){}
BNode(T)& searchFrom(T const& , BNode(T)& );
BNode(T) insert(T const& );
void remove(T const&);
BNode(T) getMin(BNode(T)=NULL);
BNode(T) getMax(BNode(T)=NULL);
};

template<typename T> BNode(T)& BST<T>::searchFrom(T const& e, BNode(T)& r){
    if(!r || r->data==e) return r;
    _hot = r;
    return searchFrom(e, ((e<r->data)? r->lchild : r->rchild));
}

template<typename T> BNode(T) BST<T>::insert(T const& e){
    BNode(T)& r = this->search(e);    //&很关键，保留了空孩子的地址信息，省去父亲->孩子这一步
    if(!(r)){ //暂只处理不重复的元素
        r = new BinNode<T>(e, _hot);
        _hot->updateHeightAbove();
    }
    return r;
}

template<typename T> void BST<T>::remove(T const& e){
    BNode(T)& r = this->search(e);
    if(!r) return;
    if(r->lchild && r->rchild){ //左右子树都存在
        BNode(T) lc = r->lchild;    //皮之不存，使毛暂存
        r->rchild->parent = r->parent;  //我子认我父为父
        r = r->rchild;  //狸猫换太子
        BNode(T) minRNode = r;  //（原）右子树中的最小节点
        while(r->lchild) minRNode = r->lchild;
        minRNode->lchild = lc;  //使毛重新附着
        minRNode->updateHeightAbove();   //高度变化至多从minRNode开始
    }else{
        r = (r->lchild? r->lchild : r->rchild);
        if(r) r->parent = _hot;
        _hot->updateHeightAbove();
    }
}

template<typename T> BNode(T) BST<T>::getMin(BNode(T) p){
    if(!p) p=this->_root;
    while(p->lchild) p=p->lchild;
    return p;
}

template<typename T> BNode(T) BST<T>::getMax(BNode(T) p){
    if(!p) p=this->_root;
    while(p->rchild) p=p->rchild;
    return p;
}