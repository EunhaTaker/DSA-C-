#pragma once
typedef int RANK;
#define DEFAULT_CAP  8
#include<iostream>
using namespace std;

template<typename T> class Vector{
protected:
RANK _size, _capacity;
T* _elem;
bool heapFlag; //堆排序标志，说明该对象是用于堆排序的临时对象

///复制
void copyFrom(T const *A, RANK lo, RANK hi);
//扩容
void expand(RANK n=0);

public:
///构造
Vector(RANK capacity=DEFAULT_CAP){ _elem = new T[_capacity=capacity];_size = 0; }
Vector(T const *A, RANK lo, RANK hi, bool heapFlag=false):heapFlag(heapFlag){
    if(!heapFlag)copyFrom(A, lo, hi);}
Vector(Vector<T> const& V, RANK lo=0, RANK hi=-1){
    copyFrom(V._elem, lo, hi==-1?V.size():hi);}
Vector(initializer_list<T>);
//析构
~Vector() { if(!heapFlag) delete[] _elem; }
bool empty() {return _size==0;}
// 大小
RANK size() const{return _size;}
//按索引获取值
T& get(RANK idx) const;
//修改
bool put(RANK idx, T value);
//重载[]
T& operator [](RANK idx){return get(idx);}
//重载+
template<class STL> //参数、返回值模板化方便继承，下同
STL operator +(STL &v){STL newv(*this); newv.Vector<T>::insert(_size, v); return newv;}
//插入
void insert(RANK idx, T value);
//插入Vector
// template<class STL>
void insert(RANK idx, Vector<T> &v);
//尾部追加
void append(T value);
//截取区间 TODO STL无法推断
// template<typename STL>
Vector<T> sub(RANK lo, RANK hi);
//删除区间
bool delRng(RANK lo, RANK hi);
//按元素删除，删除最右边一个满足条件的元素
RANK remove(T value);
//按索引删除
T pop(RANK idx);
//删除全部
void clear();
//在区间内查找值
virtual RANK index(T value, RANK lo=0, RANK hi=-1) const;
//遍历
template<typename VST> void map(VST &visit);
//去重
virtual RANK unique();
//获取逆序度
RANK dissorted() const;
/**排序**/
void sort(RANK lo=0, RANK hi=-1){heapSort(lo, hi);}
//冒泡排序
void bubbleSort(RANK lo=0, RANK hi=-1);
//归并排序
void mergeSort(RANK lo=0, RANK hi=-1);  //TODO bug
//堆排序
void heapSort(RANK lo=0, RANK hi=-1);
};

#include "vector_implement.h"