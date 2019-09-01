#include "../Vector/sorted_vector.h"

template<typename T>
class Set : public SortedVector<T>{
public:
Set():SortedVector<T>::SortedVector(){}
template<class STL>
Set(STL& set, RANK lo=0, RANK hi=-1): SortedVector<T>::SortedVector(set, lo, hi) {SortedVector<T>::unique();}
Set(initializer_list<T> il): SortedVector<T>::SortedVector(il) {SortedVector<T>::unique();}
//新增
bool add(T e);
//是否包含元素e
bool contain(T const& e) const;
//并集 |
Set<T> operator|(Set<T> & a){Set<T> set = SortedVector<T>::operator+(a); set.unique(); return set;}
//交集 &
//差集 -
//对称差 ^

protected:
//重载[]
T operator [](RANK idx){return this->_elem[idx];}
// //重载+
// template<class STL>
// STL operator +(STL &v){STL set=SortedVector<T>::operator+(v); SortedVector<T>::unique(); return set;}

private:    //禁用以下方法
//按索引获取值
T get(RANK idx) const;
//唯一化
RANK unique();
//二分查找, 查找失败返回合适插入位置
RANK index(T e, RANK lo=0, RANK hi=-1);
//二分查找，查找失败返回-1
RANK find(T e, RANK lo=0, RANK hi=-1);
};


template<typename T>
bool Set<T>::add(T e){
    RANK idx = SortedVector<T>::index(e);
    if(idx==-1 || this->_elem[idx] != e){  //若集合中无元素e，插入之
        Vector<T>::insert(idx+1, e);
        return true;
    }else return false;
}


template<typename T>
bool Set<T>::contain(T const& e) const{
    return (SortedVector<T>::find(e)>=0);
} 


// template<typename T>
// Set<T> Set<T>::operator |(Set<T> & a){
//     Set<T>* c;
//     Set<T> &b = *this;
//     RANK i=0,j=0;
//     RANK la=a.size(), lb=b.size();
//     while(i<la && j<lb){
//         if(a[i]==b[j]){ //保持唯一性
//             (*c).add(a[i++]);
//             j++;
//         }else if(a[i]<b[j]) (*c).add(a[i++]);  //保持有序性
//         else (*c).add(b[j++]);
//     }
//     if(i<la) c = &(c->Vector<T>::operator+(a.cut(i,la)));
//     else if(j<lb) c = &(c->Vector<T>::operator+(b.cut(j,lb)));
//     return *c;

// }
