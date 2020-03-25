#pragma once
typedef int RANK;
#define DEFAULT_CAP  8

using std::initializer_list;

template<typename T> class Vector{
    protected:
RANK _size, _capacity;  // 大小、容量
T* _elem;   // 内部维护的数组
bool heapFlag; //堆排序标志，表明该Vector是用于堆排序的临时对象

///复制
void copyFrom(T const *A, RANK lo, RANK hi);
//扩容
void expand(RANK=0);

    public:
/* 构造 */
// 传入容量，构造空vector
Vector(RANK capacity=DEFAULT_CAP){ _elem = new T[_capacity=capacity];_size = 0; }
// 传入长度和默认值
Vector(RANK, T);
// 传入序列及区间，复制到本vector进行构建
Vector(const T *A, RANK lo, RANK hi, bool heapFlag=false):heapFlag(heapFlag){
    if(!heapFlag)copyFrom(A, lo, hi);}
// 复制另一个vector的某区间
Vector(Vector<T> const& V, RANK lo=0, RANK hi=-1){
    copyFrom(V._elem, lo, hi==-1?V.size():hi);}
// 使用列表初始化容器进行初始化
Vector(initializer_list<T>);
// 析构
~Vector() { std::cout<<"析构";if(!heapFlag) delete[] _elem; }
bool empty() {return _size==0;}
// 大小
RANK size() const{return _size;}
// 按索引获取值
T& get(RANK idx) const;
// 修改
bool put(RANK idx, T value);
// 重载[]
T& operator [](RANK idx) const{return get(idx);}
// 重载+
template<class STL> //参数、返回值模板化方便继承，下同
STL operator +(STL &v){STL newv(*this); newv.Vector<T>::insert(_size, v); return newv;}
// 重载+=
template<class STL> //参数、返回值模板化方便继承，下同
STL operator +=(const STL &v){extend(v); return *this;}
// template<class STL> //参数、返回值模板化方便继承，下同
Vector<T> operator +=(initializer_list<T> il){extend(il); return *this;}
// 插入单个元素
void insert(RANK idx, T value);
// 插入Vector
void insert(RANK idx, const Vector<T> &v);
// 尾部追加
void append(T value);
// 尾部扩展数组
void extend(initializer_list<T> il){extend(Vector<T>(il));}
void extend(const Vector<T> &v){this->Vector<T>::insert(_size, v);}
// 截取区间
Vector<T> sub(RANK lo, RANK hi);
// 删除区间
bool delRng(RANK lo, RANK hi);
// 按元素删除，删除最右边一个满足条件的元素
RANK remove(T value);
// 按索引删除
T pop(RANK idx);
// 删除全部
void clear();
// 在区间内查找值
virtual RANK index(T value, RANK lo=0, RANK hi=-1) const;
// 遍历
template<typename VST> void map(VST &visit);
// 去重
virtual RANK unique();
// 获取逆序度
RANK dissorted() const;
/**排序**/
void sort(RANK lo=0, RANK hi=-1){bubbleSort(lo, hi);}
// 冒泡排序
void bubbleSort(RANK lo=0, RANK hi=-1);
// 归并排序
void mergeSort(RANK lo=0, RANK hi=-1);  //TODO bug
// 堆排序
void heapSort(RANK lo=0, RANK hi=-1);
};

#include "vector_implement.h"