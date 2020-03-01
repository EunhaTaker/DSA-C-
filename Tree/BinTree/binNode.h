
#include<cstddef>
#include<iostream>
#include<iomanip>
using namespace std;
#define BNode(T) BinNode<T>*
#define getHeight(p) (p?p->height:-1)
#define dataWidth 3

template<typename T> struct BinNode
{
    BNode(T) parent; BNode(T) lchild; BNode(T) rchild;
    T data;
    int height;
    //构造函数
    // BinNode():
    //     parent(nullptr), lchild(nullptr), rchild(nullptr), height(0) {}
    BinNode(T e, BNode(T) p = nullptr, int h=0):
        data(e), parent(p), height(h), lchild(nullptr), rchild(nullptr) {}
    // ~BinNode(){ delete this;}//大忌
    int size() const; //后代数量
    bool isLChild() const;
    void releaseAll();
    void release();
    BNode(T) insertAsLC(T const&);
    BNode(T) insertAsRC(T const&);
    bool updateHeight();    //更新此节点高度
    void updateHeightAbove();   //更新此节点及其祖先高度
    template<typename VST> void travPre(VST&);  //先序遍历
    template<typename VST> void travIn(VST&);  //中序遍历
    template<typename VST> void travPost(VST&);  //后序遍历
    template<typename VST> void printTree(VST&, int=0);   //打印该树
    void zig();
    void zag();
private:
    string rangeText(BNode(T) const&);
};

// template<typename T> string BinNode<T>::rangeText(BNode(T) const& p){
//     static int lackCount = 0;
//     int width = 5;  //单个节点占用宽度
// }

template<typename T> void BinNode<T>::zig(){
    BNode(T) newRoot = this->lchild;
    newRoot->parent = parent;
    if(parent){
        ((this->isLChild())? parent->lchild : parent->rchild) = newRoot;
    }
    lchild = newRoot->rchild; if(lchild) lchild->parent = this;
    newRoot->rchild = this; parent = newRoot;
}
template<typename T> void BinNode<T>::zag(){
    BNode(T) newRoot = this->rchild;
    newRoot->parent = parent;
    if(parent){ //this可能是根节点
        ((isLChild())? parent->lchild : parent->rchild) = newRoot;
    }
    rchild = newRoot->lchild; if(rchild) rchild->parent = this;
    parent = newRoot; parent->lchild = this;
}

template<typename T> template<typename VST> void BinNode<T>::printTree(VST& visit, int depth){
    cout<<setw(dataWidth)<<visit(this);
    if(rchild){
        cout<<"-->";
        rchild->printTree(visit, depth+1);
    }
    if(lchild){
        cout<<endl<<setw((depth+1)*(dataWidth+3))<<"\\->";
        lchild->printTree(visit, depth+1);
    }
    if(depth==0) cout<<endl;
}

template<typename T> bool BinNode<T>::updateHeight(){
    int oldHeight = height;
    height = 1+ max(getHeight(lchild), getHeight(rchild));
    return oldHeight!=height;
}

template<typename T> void BinNode<T>::updateHeightAbove(){
    if(updateHeight() && parent)
        parent->updateHeightAbove();
}

template<typename T> int BinNode<T>::size() const{
    return 1+
        ((lchild)?lchild->size():0)+
        ((rchild)?lchild->size():0);
}

template<typename T> bool BinNode<T>::isLChild() const{
    return this == parent->lchild;
}

template<typename T> void BinNode<T>::releaseAll(){
    if(lchild) lchild->releaseAll();
    if(rchild) rchild->releaseAll();
    release();
}

template<typename T> void BinNode<T>::release(){
    // cout<<"节点"<<data<<"删除"<<endl;
    delete this;
}

template<typename T> BNode(T) BinNode<T>::insertAsLC(T const& e){
    lchild = new BinNode<T>(e, this);
    updateHeightAbove();
    return lchild;
}

template<typename T> BNode(T) BinNode<T>::insertAsRC(T const& e){
    rchild =  new BinNode<T>(e, this);
    updateHeightAbove();
    return rchild;
}

template<typename T> template<typename VST> void BinNode<T>::travPre(VST & visit){
    visit(this);
    if(lchild){
        // cout<<lchild<<"  dd  "<<lchild->data<<endl;
        lchild->travPre(visit);
    }
    if(rchild)rchild->travPre(visit);
}

template<typename T> template<typename VST> void BinNode<T>::travIn(VST & visit){
    if(lchild)
        lchild->travIn(visit);
    visit(this);
    if(rchild)
        rchild->travIn(visit);
}

int getData(BNode(int) a){
    return a->data;
}