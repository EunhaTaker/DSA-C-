#include "../Vector/vector.h"

template<typename T>
class Stack : public Vector<T>{
public:
void push(T);
T pop();
T top();

private:    // 下列方法禁用
virtual T operator [](RANK idx){return 0;}
//扩容
void expand();
//插入
void insert(RANK idx, T value);
//尾部追加
void append(T value);
//删除区间
bool cut(RANK lo, RANK hi);
//按索引删除
T pop(RANK idx);
//按索引获取值
T get(RANK idx) const;
//在区间内查找值
RANK index(T value, RANK lo=0, RANK hi=-1) const;
//按元素删除，删除最右边一个满足条件的元素
RANK remove(T value);
//修改
bool put(RANK idx, T value);
//遍历
template<typename VST> void map(VST &visit);
//去重
void unique();
//获取逆序度
RANK dissorted() const;
///排序
//冒泡排序
void bubbleSort();
//归并排序
void mergeSort(RANK lo=0, RANK hi=-1);
// 大小
RANK size();
};

template<typename T>
void Stack<T>::push(T e){
    Vector<T>::append(e);
}


template<typename T>
T Stack<T>::pop(){
    return Vector<T>::pop(this->_size-1);
}


template<typename T>
T Stack<T>::top(){
    return this->_elem[this->_size-1];
}
