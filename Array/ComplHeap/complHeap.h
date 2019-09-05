#pragma once
#include "../Vector/vector.h"
#define Lchild(i) (i*2+1)
#define Rchild(i) (i*2+2)
#define Parent(i) ((i-1)/2)


template<typename T> class ComplHeap : public Vector<T>{
protected:
    RANK percolateUp(RANK i);
    RANK percolateDown(RANK i);
    void heapify(RANK n);   //Floyd建堆算法
public:
    ComplHeap():Vector<T>::Vector(){}
    ComplHeap(initializer_list<T> il) : Vector<T>::Vector(il) {heapify(this->_size);}
    ComplHeap(T* A, int lo, int hi, bool sort=false) : Vector<T>::Vector(A, lo, hi, sort) {
        if(sort) {this->_elem = A+lo; this->_size = hi-lo;} //若是排序情形，不申请空间（用于vector的排序算法）
        heapify(this->_size);
    }
    T getMax();
    RANK insert(T const e);
    T removeMax();

private:    //隐藏以下方法
//插入
void insert(RANK idx, T value);
//尾部追加
void append(T value);
//获取逆序度
RANK dissorted() const;
///排序
void sort();
//冒泡排序
void bubbleSort();
//归并排序
void mergeSort(RANK lo=0, RANK hi=-1);
};


template<typename T> void ComplHeap<T>::heapify(RANK n){
    for(RANK i=Parent(n-1);i>=0;i--)
        percolateDown(i);
    //自下而上的下滤，相比自上而下的上滤，对于每个节点的成本，前者正比于其高度，后者正比于其深度
    //前者的优点在于，大部分节点处在中下层，高度之和远小于深度之和
}



template<typename T> RANK ComplHeap<T>::percolateUp(RANK i){
    T temp = this->_elem[i];
    while(i>0 && this->_elem[Parent(i)] < temp ){
        this->_elem[i] = this->_elem[Parent(i)];
        i = Parent(i);
    }
    this->_elem[i] = temp;
    return i;
}


template<typename T> RANK ComplHeap<T>::percolateDown(RANK i){
    T temp = this->_elem[i];    //开始时拷贝，结束时放置到应得位置，免得过程中交换
    RANK j;
    while( Lchild(i)<this->_size ){
        if(Rchild(i)<this->_size){
            j= (this->_elem[Lchild(i)]>this->_elem[Rchild(i)])? Lchild(i) : Rchild(i);
        }else{
            j=Lchild(i);
        }
        if(temp>=this->_elem[j])
            break;
        this->_elem[i] = this->_elem[j];
        i = j;
    }
    this->_elem[i] = temp;
    return i;
}

template<typename T> T ComplHeap<T>::getMax(){
    return this->_elem[0];
}

template<typename T> RANK ComplHeap<T>::insert(T const e){
    this->append(e);
    return percolateUp(this->_size-1);
}

template<typename T> T ComplHeap<T>::removeMax(){
    T max = this->_elem[0];
    this->_elem[0] = this->_elem[--this->_size];
    percolateDown(0);
    return max;
}