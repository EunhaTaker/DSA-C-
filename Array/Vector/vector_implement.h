#include "../ComplHeap/complHeap.h"
#include <iostream>
#include<string.h>


template<typename T>    // 交换两个同类型对象的值
inline void Vector<T>::swap(RANK i, RANK j){
    // _size位置永远没有数据, _size永远小于capacity
    _elem[_size] = _elem[i];
    _elem[i] = _elem[j];
    _elem[j] = _elem[_size];
}


template<typename T>    // 判断相等，若T未重载==则判断相同
static bool equal(const T& a, const T& b){
    // try{
    //     if(a==b) return true;
    //     else return false;
    // }catch{
    //     return &a == &b;
    // }
    return 0;
}

template<typename T>    // 构造--依据容量
Vector<T>::Vector(RANK capacity){
    _elem = new T[_capacity=capacity];
    _size = 0;
}


template<typename T>    // 构造--依据初始化列表
Vector<T>::Vector(const initializer_list<T>& il):_size(0){
    _elem = new T[_capacity = il.size()<<1];
    for(auto &e: il) _elem[_size++] = e;
}


template<typename T>    // 构造--根据长度和默认值
Vector<T>::Vector(RANK size, const T& e){
    _elem = new T[_capacity=size<<1];
    _size = 0;
    while(_size<size)
        _elem[_size++] = T(e);
}


template<typename T>    // 构造--复制数组
Vector<T>::Vector(const T *A, RANK lo, RANK hi, bool heapFlag):heapFlag(heapFlag){
    if(!heapFlag)copyFrom(A, lo, hi);
}


template<typename T>    // 构造--复制其他Vector
Vector<T>::Vector(Vector<T> const& V, RANK lo, RANK hi){
    copyFrom(V._elem, lo, hi==-1?V.size():hi);
}


template<typename T>    // 析构
Vector<T>::~Vector(){
    std::cout<<"析构";
    if(!heapFlag) delete[] _elem;
}


template<typename T>    // 从数组复制到_elem（内部方法）
void Vector<T>::copyFrom(T const *A, RANK lo, RANK hi){
    _elem=new T[_capacity=(hi-lo)<<1];
    _size=hi-lo;
    carry(A, lo, _size, 0);
}



template<typename T>    // 将[lo, hi)处的数据挪动n个位置，n:向后为正，向前为负
void Vector<T>::move(RANK lo, RANK hi, RANK n){
    if(n>0){
        RANK hi2 = hi+n;
        while(lo<hi)
            _elem[--hi2] = _elem[--hi];
    }else{
        RANK lo2 = lo+n;
        while(lo<hi)
            _elem[lo2++] = _elem[lo++];
    }
}


template<typename T>    // 搬运（将A的srcStart往后length个字符搬运到this的destStart开始的length个位置上）
inline void Vector<T>::carry(const T* A, RANK srcStart, RANK length, RANK destStart){
    memcpy(_elem+destStart, A+srcStart, length*sizeof(T));
}


template<typename T>    // 扩容，2倍扩充策略
void Vector<T>::expand(RANK n){
    RANK need = n + _size;
    if(need < _capacity) return;
    else
        while(need >= _capacity)    // 容量多次翻倍，直至超过所需
            _capacity <<= 1;
    T *oldElem = _elem;
    _elem = new T[_capacity];
    carry(oldElem, 0, _size);
    delete [] oldElem;
}


template<typename T>    // 是否空
inline bool Vector<T>::empty()const{
    return _size==0;
}


template<typename T>    // 长度
inline RANK Vector<T>::size() const{
    return _size;
}


template<typename T>    // 插入一个T
void Vector<T>::insert(RANK idx, const T& value){
    expand();
    move(idx, _size++, 1);
    _elem[idx] = value;
}


template<typename T>    // 插入Vector
void Vector<T>::insert(RANK idx, const Vector<T> &v){
    expand(v.size());
    RANK ridx = idx+v.size();
    move(idx, _size, v._size);  //搬运[idx, _size) 到 [idx+v.size, _size+v.size)区间
    _size += v._size;
    for(RANK i=idx, j=0; i<ridx; ){ //将v拷贝到[idx, idx+v.size)区间
        _elem[i++] = v.get(j++);
    }
}


template<typename T>
void Vector<T>::append(const T& value){
    expand();
    _elem[_size++]=value;
}


template<typename T>
void Vector<T>::extend(const T* A, RANK lo, RANK hi){
    expand(hi-lo);
    carry(A, lo, hi-lo, _size);
    _size += hi-lo;
}


template<typename T>
void Vector<T>::extend(const initializer_list<T>& il){
    expand(il.size());
    for(auto e: il) append(e);
}


template<typename T>    // 合并两个vector生成副本
Vector<T> Vector<T>::concat(const Vector<T> &v){
    Vector<T> newv = *this;
    newv.Vector<T>::insert(_size, v);
    return newv;
}


template<typename T> //template<typename STL>
Vector<T> Vector<T>::sub(RANK lo, RANK hi){
    return Vector<T>(_elem, lo, hi);
}


template<typename T>
bool Vector<T>::delRng(RANK lo, RANK hi){
    if(lo<0 || hi>_size || lo>=hi) return false;
    // while(lo< _size) //lo靠上新size时，搬运结束
    //     _elem[lo++] = _elem[hi++];
    carry(_elem, hi, _size-hi, lo);
    _size-=hi-lo;
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
RANK Vector<T>::find(const T& value, RANK lo, RANK hi) const{
    if(hi==-1) hi = _size;
    while(lo<hi-- && _elem[hi]!=value); //逆向查找
    return hi;  //hi<lo意味着查找失败
}


template<typename T>
RANK Vector<T>::remove(const T& value){
    RANK idx = find(value);
    if(idx!=-1)
        pop(idx);
    return idx;
}


template<typename T>
void Vector<T>::clear(){
    _size = 0;
}


template<typename T>    // 修改值
void Vector<T>::put(RANK idx, const T& value){
    // if(idx<0 || idx>=_size) return false;
    _elem[idx] = value;
    // return true;
}


template<typename T> template<typename VST>
void Vector<T>::map(VST &visit){
    for(RANK idx=0; idx<_size; idx++)
        visit(_elem[idx]);
}


template<typename T>    // 去重
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
                swap(j, j-1);
                temphi=j;   //记录交换操作到达的最右位置
            }
        }
        hi = temphi;    //智能缩小右边界
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
