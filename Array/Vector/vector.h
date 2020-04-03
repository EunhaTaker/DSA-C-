#pragma once
typedef int RANK;       // RANK根据需要设置为合适的整数类型
#define DEFAULT_CAP  8  // 默认容量为8

using std::initializer_list;

template<typename T> class Vector{
protected:
    // 长度、容量
    RANK _size, _capacity;
    // 内部维护的数组
    T* _elem;
    // 堆排序标志，表明该Vector是否是用于堆排序的临时对象
    bool heapFlag;
    // 复制
    void copyFrom(T const *A, RANK lo, RANK hi);
    // 扩容
    void expand(RANK n=0);
    // 将[lo, hi)处的数据挪动n个位置，n:向后为正，向前为负
    void move(RANK lo, RANK hi, RANK n);
    // 获取逆序度
    RANK dissorted() const;
    // 冒泡排序
    void bubbleSort(RANK lo=0, RANK hi=-1);
    // 归并排序
    void mergeSort(RANK lo=0, RANK hi=-1);  //TODO bug
    // 堆排序
    void heapSort(RANK lo=0, RANK hi=-1);
    // 交换两个位置
    void swap(RANK, RANK);
    // 搬运（将A的srcStart往后length个字符搬运到this的destStart开始的length个位置上）
    void carry(const T* A, RANK srcStart, RANK length, RANK destStart=0);

public:
    /* 构造 */
    // 默认构造，按容量初始化空vector
    Vector(RANK capacity=DEFAULT_CAP);
    // 拷贝构造
    Vector(Vector<T> const& V, RANK lo=0, RANK hi=-1);
    // 传入长度和默认值
    Vector(RANK, const T&);
    // 传入序列及区间，复制到本vector进行构建
    Vector(const T *A, RANK lo, RANK hi, bool heapFlag=false);
    // 使用列表初始化容器进行初始化
    Vector(const initializer_list<T>&);
    // 析构
    ~Vector();

    // 是否空
    bool empty() const;
    // 大小
    RANK size() const;
    // 按索引获取值
    T& get(RANK idx) const;
    // 修改
    void put(RANK idx, const T& value);
    // 重载[]
    T& operator [](RANK idx) const{return get(idx);}
    // 在区间内查找值
    virtual RANK find(const T& value, RANK lo=0, RANK hi=-1) const;
    // 截取区间
    Vector<T> sub(RANK lo, RANK hi);

    // 插入单个元素
    void insert(RANK idx, const T& value);
    // 插入Vector
    void insert(RANK idx, const Vector<T> &v);
    // 尾部追加
    void append(const T& value);
    // 尾部扩展
    virtual void extend(const T* A, RANK lo, RANK hi);
    virtual void extend(const initializer_list<T>& il);
    virtual void extend(const Vector<T>& v){extend(v._elem, 0, v._size);}
    // 返回两个vector合并产生的副本
    virtual Vector<T> concat(const Vector<T> &);
    // 重载+（合并两个vector生成副本）
    virtual Vector<T> operator +(const Vector<T> &v){return concat(v);}
    // 重载+=（尾部追加）
    virtual Vector<T>& operator +=(const T& e){append(e); return *this;}
    virtual Vector<T>& operator +=(const Vector &v){extend(v); return *this;}
    virtual Vector<T>& operator +=(const initializer_list<T>& il){extend(il); return *this;}

    // 按值删除，删除最右边一个满足条件的元素
    RANK remove(const T& value);
    // 按索引删除
    T pop(RANK idx);
    // 删除区间
    bool delRng(RANK lo, RANK hi);
    // 清空
    void clear();

    // 去重
    virtual RANK unique();
    // 遍历
    template<typename VST> void map(VST &visit);

    //排序
    void sort(RANK lo=0, RANK hi=-1){bubbleSort(lo, hi);}
};

#include "vector_implement.h"