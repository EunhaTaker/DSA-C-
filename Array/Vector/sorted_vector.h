#include "vector.h"

template<typename T>
class SortedVector: public Vector<T>{

protected:
    // 二分查找, 查找失败返回合适插入位置
    virtual RANK index(T const& e, RANK lo=0, RANK hi=-1) const;
    
public:
    // 构造--根据容量
    SortedVector(RANK capacity=DEFAULT_CAP): Vector<T>::Vector(capacity){};
    // 构造--根据Vector
    SortedVector(const Vector<T>& sv, RANK lo=0, RANK hi=-1);
    // 构造--复制SortedVector
    SortedVector(const SortedVector<T> & sv, RANK lo=0, RANK hi=-1) : Vector<T>::Vector(sv, lo, hi) {}
    // 构造--根据初始化列表
    SortedVector(const initializer_list<T>& il);
    // 唯一化
    virtual RANK unique();
    // 二分查找，查找失败返回-1
    RANK find(T const& e, RANK lo=0, RANK hi=-1) const;
    // 添加至合适的位置
    RANK add(const T& e);
    // 合并两个SortedVector生成副本
    SortedVector<T> concat(const Vector<T> &);
    // 合并另一有序数组
    void extend(const SortedVector<T> &);
    // 合并Vector
    void extend(const Vector<T> &);
    // 重载+
    SortedVector<T> operator +(const Vector<T> &v){return concat(v);}
    // 重载+=
    void operator +=(const T &e){add(e);}
    void operator +=(const SortedVector<T> &v){extend(v);}

private:    //禁用以下方法
    //插入
    void insert(RANK idx, T value);
    //尾部追加
    void append(T value);
    ///排序
    void sort();
};


template<typename T>    // 构造--根据Vector
SortedVector<T>::SortedVector(const Vector<T>& sv, RANK lo, RANK hi): Vector<T>::Vector(sv, lo, hi) {
    Vector<T>::sort();
}


template<typename T>    // 构造--根据初始化列表
SortedVector<T>::SortedVector(const initializer_list<T>& il): Vector<T>::Vector(il) {
    Vector<T>::sort();
}


template<typename T>    // 去重
RANK SortedVector<T>::unique(){
    int i=0,j=0;    //各对互异相邻元素的下标
    while(++j<this->_size)
        //跳过雷同元素，发现不同元素时，将j处元素移至i右侧
        if(this->_elem[i]!=this->_elem[j]) this->_elem[++i]=this->_elem[j];
    this->_size = ++i;
    return j-i;
}


template<typename T>    // 查找并返回合适的插入位置
RANK SortedVector<T>::index(T const& e, RANK lo, RANK hi) const{
    if(hi==-1) hi = this->_size;
    RANK mi;
    while(lo<hi){   //直至区间长度缩短为0
        mi = (lo+hi)>>1;
        e<this->_elem[mi]? hi=mi: lo=mi+1;    //缩短区间时无视mi处元素，区间每次至少缩短1
    }
    //最终lo位于<=e的最大元素右侧一位
    return lo;
}


template<typename T>    // 查找，失败返回-1
RANK SortedVector<T>::find(T const& e, RANK lo, RANK hi) const{
    RANK idx = index(e, lo, hi)-1;
    if(idx!=-1 && this->_elem[idx] != e) idx = -1;
    return idx;
}


template<typename T>    // 新增元素到合适位置
RANK SortedVector<T>::add(const T& e){
    RANK idx=index(e);
    Vector<T>::insert(idx, e);
    return idx;
}


template<typename T>    // 合并两个SortedVector生成副本
SortedVector<T> SortedVector<T>::concat(const Vector<T> &v){
    SortedVector<T> newv = *this;
    newv.extend(v);
    return newv;
}

template<typename T>    // 合并Vector
void SortedVector<T>::extend(const Vector<T> &v){
    // v.sort()
    // extend(static_cast<SortedVector<T>>(v));
    Vector<T>::extend(v);
    Vector<T>::sort();
}


template<typename T>    // 合并另一有序数组 mlogn
void SortedVector<T>::extend(const SortedVector<T> &v){
    RANK hi = this->_size;    // hi是查找所依赖的右边界，查找区间为[0, hi)
    RANK ind;           // 查找位置
    this->expand(v._size);
    for(RANK i=v._size-1; i>=0; i--){   // 自右向左
        ind = index(v[i], 0, hi);   // 寻找v[i]的合适插入位置
        this->move(ind, hi, i+1);     // 将[ind, hi)区间后移i+1（v中剩余元素数量）
        this->_elem[ind+i] = v[i];      // [ind, ind+i+1)是腾出的空间，将v[i]放到该区间最右
        hi = ind;               // 更新右边界
    }
    this->_size += v._size;
}
