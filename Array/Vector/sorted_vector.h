#include "vector.h"

template<typename T>
class SortedVector: public Vector<T>{
    
public:
SortedVector(RANK capacity=DEFAULT_CAP):Vector<T>::Vector(capacity){}
template<class STL>
SortedVector(STL& sv, RANK lo=0, RANK hi=-1): Vector<T>::Vector(sv, lo, hi) {Vector<T>::sort();}
SortedVector(initializer_list<T> il):Vector<T>::Vector(il) {Vector<T>::sort();}
//唯一化
RANK unique();
//二分查找, 查找失败返回合适插入位置
RANK index(T const& e, RANK lo=0, RANK hi=-1) const;
//二分查找，查找失败返回-1
RANK find(T const& e, RANK lo=0, RANK hi=-1) const;
//添加至合适的位置
RANK add(T e);
//重载+
template<class STL>
STL operator +(STL &v){ STL sv=Vector<T>::operator+(v);sv.Vector<T>::sort();return sv;}

private:    //禁用以下方法
//插入
void insert(RANK idx, T value);
//尾部追加
void append(T value);
//按索引删除
T pop(RANK idx);
//获取逆序度
RANK dissorted() const;
///排序
void sort();
//冒泡排序
void bubbleSort();
//归并排序
void mergeSort(RANK lo=0, RANK hi=-1);
};


template<typename T>
RANK SortedVector<T>::unique(){
    int i=0,j=0;    //各对互异相邻元素的下标
    while(++j<this->_size)
        //跳过雷同元素，发现不同元素时，将j处元素移至i右侧
        if(this->_elem[i]!=this->_elem[j]) this->_elem[++i]=this->_elem[j];
    this->_size = ++i;
    return j-i;
}


template<typename T>
RANK SortedVector<T>::index(T const& e, RANK lo, RANK hi) const{
    if(hi==-1) hi = this->_size;
    RANK mi;
    while(lo<hi){   //直至区间长度缩短为0
        mi = (lo+hi)>>1;
        e<this->_elem[mi]? hi=mi: lo=mi+1;    //缩短区间时无视mi处元素
    }
    //最终lo位于<=e的最大元素右侧一位
    return lo-1;
}


template<typename T>
RANK SortedVector<T>::find(T const& e, RANK lo, RANK hi) const{
    RANK idx = index(e, lo, hi);
    if(idx>=0 && this->_elem[idx] != e) idx = -1;
    return idx;
}


template<typename T>
RANK SortedVector<T>::add(T e){
    RANK idx=index(e)+1;
    Vector<T>::insert(idx, e);
    return idx;
}
