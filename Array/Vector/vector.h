typedef int RANK;
#define DEFAULT_CAP  8
#include<iostream>
using namespace std;

template<typename T> class Vector{
protected:
RANK _size, _capacity;
T* _elem;
///复制
void copyFrom(T const *A, RANK lo, RANK hi);
template<class STL>
void copyFrom(STL& V, RANK lo, RANK hi);
//扩容
void expand(RANK n=0);

public:
///构造
Vector(RANK capacity=DEFAULT_CAP){
    _elem = new T[_capacity=capacity];_size = 0;}
Vector(T const *A, RANK lo, RANK hi){
    copyFrom(A, lo, hi);}
template<class STL>
Vector(STL& V, RANK lo=0, RANK hi=-1){
    copyFrom(V, lo, hi==-1?V.size():hi);}
Vector(initializer_list<T>);
// Vector(const Vector<T>& V){
//     copyFrom(V, 0, V.size());}
//析构
~Vector() {delete[] _elem; }
bool empty() {return _size==0;}
// 大小
RANK size() const{return _size;}
//按索引获取值
T get(RANK idx) const;
//修改
bool put(RANK idx, T value);
//重载[]
T operator [](RANK idx){return get(idx);}
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
// STL cut(RANK lo, RANK hi);
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
void sort(RANK lo=0, RANK hi=-1){bubbleSort(lo, hi);}
//冒泡排序
void bubbleSort(RANK lo=0, RANK hi=-1);
//归并排序
void mergeSort(RANK lo=0, RANK hi=-1);  //TODO bug

};


template<typename T>
Vector<T>::Vector(initializer_list<T> il){
    _elem = new T[_capacity = 2*(_size = il.size())];
    RANK i=0;
    for(auto &e: il){
        _elem[i++] = e;
    }
}


template<typename T>
void Vector<T>::copyFrom(T const *A, RANK lo, RANK hi){
    _elem=new T[_capacity=2*(hi-lo)];
    _size=0;
    while(lo<hi)
        _elem[_size++]=A[lo++];
}

template<typename T> template<class STL>
void Vector<T>::copyFrom(STL& V, RANK lo, RANK hi){
    _elem=new T[_capacity=hi-lo];
    _size=0;
    while(lo<hi)
        _elem[_size++]=V[lo++];
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


// template<typename T> template<typename STL>
// STL Vector<T>::cut(RANK lo, RANK hi){
//     RANK size = hi-lo;
//     auto container = this;
//     container->delRng(hi, container.size());
//     container->delRng(0, lo);
//     // RANK i=0;
//     // while(lo<hi)
//     //     container[i++] = _elem[lo++];
//     return *container;
// }

template<typename T>
bool Vector<T>::delRng(RANK lo, RANK hi){
    if(lo<0 || hi>_size || lo>=hi) return false;
    while(lo< (_size-=hi-lo)) //lo靠上新size时，搬运结束
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
T Vector<T>::get(RANK idx) const{
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