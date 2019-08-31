typedef int RANK;
#define DEFAULT_CAP  8
#include<iostream>
using namespace std;
// #include "vector.h"

template<typename T> class Vector{
protected:
RANK _size, _capacity;
T* _elem;

public:
///构造
Vector(RANK capacity=DEFAULT_CAP){
    _elem = new T[_capacity=capacity];_size = 0;}
Vector(T const *A, RANK lo, RANK hi){
    copyFrom(A, lo, hi);}
Vector(const Vector<T>& V, RANK lo, RANK hi){
    copyFrom(V, lo, hi);}
// Vector(const Vector<T>& V){
//     copyFrom(V, 0, V.size());}
///析构
~Vector() {delete[] _elem; }

bool empty() {return _size==0;}

virtual T operator [](RANK idx){return _elem[idx];}

///复制
void copyFrom(T const *A, RANK lo, RANK hi){
    _elem=new T[_capacity=2*(hi-lo)];
    _size=0;
    while(lo<hi)
        _elem[_size++]=A[lo++];
}
void copyFrom(const Vector<T>& V, RANK lo, RANK hi){
    _elem=new T[_capacity=hi-lo];
    _size=0;
    while(lo<hi)
        _elem[_size++]=V[lo++];
}

//扩容
void expand(){
    if(_size<_capacity) return;
    T *oldElem = _elem;
    _elem = new T[_capacity<<=1];
    for(RANK i=0;i<_size;i++)
        _elem[i] = oldElem[i];
    delete [] oldElem;
}

//插入
void insert(RANK idx, T value){
    expand();
    for(RANK i=_size++; i>idx; i--){
        _elem[i] = _elem[i-1];
    }
    _elem[idx] = value;
}

//添加
void append(T value){
    expand();
    _elem[_size++]=value;
}

//删除区间
bool cut(RANK lo, RANK hi){
    if(lo<0 || hi>=_size || lo>=hi) return false;

    while(lo< (_size-=hi-lo)) //lo靠上新size时，搬运结束
        _elem[lo++] = _elem[hi++];
    return true;
}

//按索引删除
T pop(RANK idx){
    T value = _elem[idx];
    cut(idx, idx+1);
    return value;
}

//按索引获取值
T get(RANK idx) const{
    if (idx < 0 || idx >= _size)
        return NULL;
    return _elem[idx];
}

//在区间内查找值
RANK index(T value, RANK lo=0, RANK hi=-1) const{
    if(hi==-1) hi = _size;
    while(lo<hi-- && _elem[hi]!=value); //逆向查找
    return hi;  //hi<lo意味着查找失败
}

//按元素删除，删除最右边一个满足条件的元素
RANK remove(T value){
    RANK idx = index(value);
    if(idx!=-1)
        pop(idx);
    return idx;
}

//修改
bool put(RANK idx, T value){
    if(idx<0 || idx>=_size) return false;
    _elem[idx] = value;
    return true;
}

// //测试：增1
// template<typename T>
// struct increase
// {
//     virtual void operator()(T &e){e++;}
// };

//遍历
template<typename VST>
void map(VST &visit){
    for(RANK idx=0; idx<_size; idx++)
        visit(_elem[idx]);
}

//去重
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
void unique(){
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
}

//获取逆序度
RANK dissorted() const{
    RANK count=0;
    for(RANK idx=1; idx<_size; idx++)
        count += (_elem[idx] < _elem[idx - 1]);
    return count;
}

///排序
//冒泡排序
void bubbleSort(){
    T temp;
    RANK hi=_size,j;
    while(hi>1){    //直至未排序部分剩余一个元素
        for(j=1;j<hi;j++){   //冒泡至未排序部分的边界
            if(_elem[j]<_elem[j-1]){
                temp = _elem[j];
                _elem[j]=_elem[j-1];
                _elem[j-1]=temp;
                hi=j;   //智能限制边界
            }
        }
        if(hi>=j) return;   //特殊情况，已为顺序，退出
    }
}

//归并排序
void mergeSort(RANK lo=0, RANK hi=-1){
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

/**
 * 只读
 */
RANK size() const{return _size;}

};
