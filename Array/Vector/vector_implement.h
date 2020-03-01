#include "../ComplHeap/complHeap.h"

template<typename T>
Vector<T>::Vector(initializer_list<T> il):_size(0){
    _elem = new T[_capacity = il.size()<<1];
    for(auto &e: il) _elem[_size++] = e;
}


template<typename T>
void Vector<T>::copyFrom(T const *A, RANK lo, RANK hi){
    _elem=new T[_capacity=(hi-lo)<<1];
    _size=0;
    while(lo<hi)
        _elem[_size++]=A[lo++];
}


template<typename T>
void Vector<T>::expand(RANK n){
    if(n==0 && _size<_capacity) return;
    if(n>0) _capacity += max(n, _capacity); //批量增加元素时
    else _capacity<<=1;
    T *oldElem = _elem;
    _elem = new T[_capacity];
    for(RANK i=0;i<_size;i++)
        _elem[i] = oldElem[i];
    delete [] oldElem;
}


template<typename T>
void Vector<T>::insert(RANK idx, T value){
    expand();
    for(RANK i=_size++; i>idx; i--){
        _elem[i] = _elem[i-1];
    }
    _elem[idx] = value;
}


template<typename T> //template<class STL>
void Vector<T>::insert(RANK idx, Vector<T> &v){
    expand(v.size());
    RANK ridx = idx+v.size();
    for(RANK j=_size-1, i=(_size+=v.size())-1; i>=ridx; ){  //搬运[idx, _size) 到 [idx+v.size, _size+v.size)区间
        _elem[i--] = _elem[j--];
    }
    for(RANK i=idx, j=0; i<ridx; ){ //将v拷贝到[idx, idx+v.size)区间
        _elem[i++] = v[j++];
    }
}


template<typename T>
void Vector<T>::append(T value){
    expand();
    _elem[_size++]=value;
}


template<typename T> //template<typename STL>
Vector<T> Vector<T>::sub(RANK lo, RANK hi){
    RANK size = hi-lo;
    Vector<T> container = *this;
    container.delRng(hi, container.size());
    container.delRng(0, lo);
    // RANK i=0;
    // while(lo<hi)
    //     container[i++] = _elem[lo++];
    return container;
}

template<typename T>
bool Vector<T>::delRng(RANK lo, RANK hi){
    if(lo<0 || hi>_size || lo>=hi) return false;
    _size-=hi-lo;
    while(lo< _size) //lo靠上新size时，搬运结束
        _elem[lo++] = _elem[hi++];
    return true;
}


template<typename T>
T Vector<T>::pop(RANK idx){
    T value = _elem[idx];
    delRng(idx, idx+1);
    return value;
}


template<typename T>
T& Vector<T>::get(RANK idx) const{
    // if (idx < _size*-1 || idx >= _size)
    //     return NULL;
    if(idx<0) idx += _size;
    return _elem[idx];
}


template<typename T>
RANK Vector<T>::index(T value, RANK lo, RANK hi) const{
    if(hi==-1) hi = _size;
    while(lo<hi-- && _elem[hi]!=value); //逆向查找
    return hi;  //hi<lo意味着查找失败
}


template<typename T>
RANK Vector<T>::remove(T value){
    RANK idx = index(value);
    if(idx!=-1)
        pop(idx);
    return idx;
}


template<typename T>
void Vector<T>::clear(){
    _size = 0;
}


template<typename T>
bool Vector<T>::put(RANK idx, T value){
    if(idx<0 || idx>=_size) return false;
    _elem[idx] = value;
    return true;
}


template<typename T> template<typename VST>
void Vector<T>::map(VST &visit){
    for(RANK idx=0; idx<_size; idx++)
        visit(_elem[idx]);
}


// //版本1
// RANK unique(){
//     Vector reps = Vector(_size)
//     for(RANK i=1; i<_size; i++){
//         for(RANK j=0; j<i; j++){
//             if(_elem[j]==_elem[i]){
//                 reps.append(i);
//                 break;
//             }
//         }
//     }
//     RANK count=0
//     for(RANK i=reps[0]; i<_size; i++){
//         if(i+count==reps[0]){
//             count++;
//             _size--;
//             reps.pop(0);
//         }
//         _elem[i]=_elem[i+count];
//     }
//     return count
// }
template<typename T>
RANK Vector<T>::unique(){
    RANK i=1,j=1,k=0;
    while(i<_size){
        for(k=0; k<i; k++){
            if(_elem[j]==_elem[k]){
                j++;
                _size--;
                break;
            }
        }
        if(k==i){
            _elem[i++]=_elem[j++];
        }
    }
    return j-i;
}


template<typename T>
void Vector<T>::bubbleSort(RANK lo, RANK hi){
    if(hi==-1) hi = _size;
    RANK temphi, j;
    while(hi>lo+1){    //直至未排序部分只剩一个元素
        temphi = 0;
        for(j=lo+1;j<hi;j++){   //冒泡至未排序部分的边界
            if(_elem[j]<_elem[j-1]){
                swap(_elem[j], _elem[j-1]);
                temphi=j;   //记录交换操作到达的最右位置
            }
        }
        hi = temphi;    //智能限制右边界
    }
}


template<typename T>
void Vector<T>::mergeSort(RANK lo, RANK hi){
    if(hi==-1) hi=_size;
    if(hi-lo<=1) return;
    RANK mi = (lo+hi)>>1;
    //平分为两段，分别排序
    mergeSort(lo, mi);
    mergeSort(mi, hi);
    //用一段临时空间暂存lo至mi的数据
    T *telem = new T[mi - lo];
    for(RANK i=lo;i<mi;i++){
        telem[i] = _elem[i];
    }
    //归并左右两段
    RANK lo1 = 0, lo2 = mi, hi1=mi-lo;
    while (lo1 < hi1){                                                     //lo-mi的数据有序，代表lo-hi的数据已经有序
        _elem[lo++] = (lo2>=hi || telem[lo1]>_elem[lo2])? //将两段中更小的数据填充到lo，若右段数据用完，还需用左段数据继续填充
            telem[lo1++]:
            _elem[lo2++];
    }
}


template<typename T>
RANK Vector<T>::dissorted() const{
    RANK count=0;
    for(RANK idx=1; idx<_size; idx++)
        count += (_elem[idx] < _elem[idx - 1]);
    return count;
}


template<typename T> void Vector<T>::heapSort(RANK lo, RANK hi){
    ComplHeap<T> ch(_elem, lo, hi=(hi==-1?_size:hi), true);
    while(!ch.empty())
        _elem[--hi] = ch.removeMax();
}
