#include "../Vector/vector.h"
#define Lchild(i) (i*2+1)
#define Rchild(i) (i*2+2)
#define Parent(i) ((i-1)/2)


template<typename T> class ComplHeap : public Vector<T>{
protected:
    RANK percolateUp(RANK i);
    RANK percolateDown(RANK i);
public:
    ComplHeap():Vector<T>(){}
    T getMax();
    RANK insert(T const e);
    RANK removeMax(T const e);
};

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
    T temp = this->_elem[i];
    RANK j;
    while( Lchild(i)<this->_size ){
        if(Rchild(i)<this->_size){
            j= (this->_elem[Lchild(i)]<this->_elem[Rchild(i)])? Lchild(i) : Rchild(i);
        }else{
            j=Lchild(i);
        }
        if(this->_elem[i]>=this->_elem[j])
            break;
        this->_elem[i] = this->_elem[j];
        i = j;
    }
    return i;
}

template<typename T> T ComplHeap<T>::getMax(){
    return this->_elem[0];
}

template<typename T> RANK ComplHeap<T>::insert(T const e){
    this->append(e);
    return percolateUp(this->_size-1);
}

template<typename T> RANK ComplHeap<T>::removeMax(T const e){
    this->_elem[--this->_size-1] = this->_elem[0];
    return percolateDown(0);
}