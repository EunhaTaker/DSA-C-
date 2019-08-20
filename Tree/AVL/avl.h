#include "../BST/bst.h"
using namespace std;

template<typename T> class AVL : public BST<T>{
protected:
int balFac(BNode(T) const&);    //获取平衡因子
BNode(T)& zig(BNode(T) &);    //顺时针旋转
BNode(T)& zag(BNode(T) &);    //逆时针旋转
void updateHeightAbove(BNode(T) const);
void counterBalance(BNode(T));   //平衡

void rotateAt(BNode(T));
void connect34(BNode(T), BNode(T), BNode(T), BNode(T), BNode(T), BNode(T), BNode(T));

public:
AVL(T const& e): BST<T>(e){}
bool insert(T const);
bool remove(T const);
};

template<typename T> int AVL<T>::balFac(BNode(T) const& p){
    return getHeight(p->lchild)-getHeight(p->rchild);
}

template<typename T> void AVL<T>::updateHeightAbove(BNode(T) const p){
    if(p->height != (1+ max(getHeight(p->lchild), getHeight(p->rchild)) ) ){
        p->height = (1+ max(getHeight(p->lchild), getHeight(p->rchild)) );
        int bf = balFac(p);
        if(bf<-1 || bf>1){
            this->_hot = p;
        }
        if(p->parent) updateHeightAbove(p->parent);
    }
}

template<typename T> void AVL<T>::counterBalance(BNode(T) p){
    if(p->updateHeight()){
        if(balFac(p)>1) p=zig(p);
        else if(balFac(p)<-1) p=zag(p);
        else if(p->parent) p=p->parent;
        counterBalance(p);
    }
    // cout<<"counter??? "<<p->data<<endl;
    // while(true){
    //     updateHeightAbove(p, this->_hot=NULL);
    //     if(this->_hot){
    //         if(balFac(this->_hot)>1) p=zig(this->_hot);
    //         else p=zag(this->_hot);
    //     }else break;
    // }
}

template<typename T> BNode(T)& AVL<T>::zig(BNode(T) &p){
    BNode(T) newRoot = p->lchild;
    if(p->parent){
        if(p->isLChild()) this->link(p->parent, newRoot, p->parent->lchild);
        else this->link(p->parent, newRoot, p->parent->rchild);
    }else{
        this->_root = newRoot;
        newRoot->parent = NULL;
    }
    if(newRoot->rchild) this->link(p, newRoot->rchild, p->lchild);
    else p->lchild=NULL;
    this->link(newRoot, p, newRoot->rchild);
    return p;
}
template<typename T> BNode(T)& AVL<T>::zag(BNode(T) &p){
    BNode(T) newRoot = p->rchild;
    if(newRoot->lchild) this->link(p, newRoot->lchild, p->rchild);
    else p->rchild=NULL;
    if(p->parent){
        if(p->isLChild()) this->link(p->parent, newRoot, p->parent->lchild);
        else this->link(p->parent, newRoot, p->parent->rchild);
    }else{
        this->_root=newRoot;
        newRoot->parent=NULL;
    }
    this->link(newRoot, p, newRoot->lchild);
    return p;
}

template<typename T> void AVL<T>::connect34(BNode(T) a, BNode(T) b, BNode(T) c, BNode(T) t0, BNode(T) t1, BNode(T) t2, BNode(T) t3){
    a->lchild=t0; if(t0) t0->parent=a;
    a->rchild=t1; if(t1) t1->parent=a; a->updateHeight();
    c->lchild=t2; if(t2) t2->parent=c;
    c->rchild=t3; if(t3) t3->parent=c; c->updateHeight();
    b->lchild=a, a->parent=b;
    b->rchild=c, c->parent=b; b->updateHeight();
}

template<typename T> void AVL<T>::rotateAt(BNode(T) v){
    BNode(T) p=v->parent; BNode(T) g=p->parent;
    if(p->isLChild()){
        if(v->isLChild()){
            connect34(p,g,v,v->lchild, v->rchild, p->rchild, g->rchild);
        }else{
            connect34(p, v, g, p->lchild, v->lchild, v->rchild, g->rchild);
        }
    }
}

template<typename T> bool AVL<T>::insert(T const e){
    BNode(T)& r = this->search(e);    //&很关键，保留了空孩子的地址信息，省去父亲->孩子这一步
    if(r) return false; //暂只处理不重复的元素
    r = new BinNode<T>(e, this->_hot);
    // cout<<"r->par  "<<r->parent->data<<endl;
    counterBalance(r->parent);
    return true;
}

template<typename T> bool AVL<T>::remove(T const e){
    BNode(T)& r = this->search(e);  //r为其父的孩子的引用
    if(!r) return false;
    if(r->lchild && r->rchild){ //左右子树都存在
        BNode(T) minRNode = this->getMin(r);  //（原）右子树中的最小节点
        if(minRNode->rchild) this->link(minRNode, minRNode->rchild, minRNode->parent->lchild);  //离开前先给孩子找个归宿
        this->link(minRNode, r->lchild, minRNode->lchild);
        this->link(minRNode, r->rchild, minRNode->rchild);
        this->link(r->parent, minRNode, r);

        // BNode(T) lc = r->lchild;    //皮之不存，使毛暂存
        // r->rchild->parent = r->parent;  //我子认我父为父
        // r = r->rchild;  //狸猫换太子
        // BNode(T) minRNode = this->getMin(r);  //（原）右子树中的最小节点
        // minRNode->lchild = lc;  lc->parent = minRNode; //使毛重新附着
        // counterBalance(minRNode);   //高度变化至多从minRNode开始
    }else{
        r = (r->lchild? r->lchild : r->rchild);
        if(r) r->parent = this->_hot;
        counterBalance(this->_hot);
    }
    return true;

    // if(r->rchild){
    //     BNode(T)& lc = r->lchild;
    //     link(r->parent, r->rchild, r);
    //     if(lc){
    //         link(getMin(r), lc, getMin(r)->lchild);
    //     }
    // }else{
    //     link(r->parent, r->lchild, r);
    // }
    // counterBalance()
}
