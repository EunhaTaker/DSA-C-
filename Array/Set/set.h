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
Set<T> operator|(Set<T> &a){Set<T> set = SortedVector<T>::operator+(a); set.SortedVector<T>::unique(); return set;}
//交集 &
Set<T> operator&(Set<T> &);
//差集 -
Set<T> operator-(Set<T> &);
//对称差 ^
Set<T> operator^(Set<T> &);
//集合相等 =
bool operator==(Set<T>&);
//真含于 <
bool operator<(Set<T>&);
//衍生运算符
bool operator<=(Set<T>& b) {Set<T> &a=*this; return a==b || a<b;}
bool operator>(Set<T>& b) {Set<T> &a=*this; return !(a<b);}
bool operator>=(Set<T>& b) {Set<T> &a=*this; return a==b || a>b;}


protected:
//重载[]
T operator [](RANK idx){return this->_elem[idx];}
//按索引获取值
T get(RANK idx) const;

private:    //禁用以下方法
//重载+
Set<T> operator +(Set<T> &v);
//唯一化
RANK unique(){cout<<"set::unique"<<endl;return 0;}
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


template<typename T>
Set<T> Set<T>::operator&(Set<T> &b){
    Set<T> set;
    Set<T> &a = *this;
    RANK i=0,j=0;
    RANK la=a.size(), lb=b.size();
    while(i<la && j<lb){
        if(a[i]==b[j]){set.Vector<T>::append(a[i++]); j++;}
        else if(a[i]<b[j]) i++;
        else j++;
    }
    return set;
}


template<typename T>
Set<T> Set<T>::operator-(Set<T> &b){
    Set<T> set;
    Set<T> &a = *this;
    RANK i=0,j=0;
    RANK la=a.size(), lb=b.size();
    while(i<la){
        if(j<lb){
            if(a[i]==b[j]){i++;j++;}
            else if(a[i]<b[j]){set.Vector<T>::append(a[i++]);}
            else {j++;}
        }else set.Vector<T>::append(a[i++]);
    }
    return set;
}


template<typename T>
Set<T> Set<T>::operator^(Set<T> &b){
    Set<T> set;
    Set<T> &a = *this;
    RANK i=0,j=0;
    RANK la=a.size(), lb=b.size();
    while(i<la || j<lb){
        // cout<<"a[i]: "<<a[i]<<" b[j]: "<<b[j]<<endl;
        if(j>=lb) set.Vector<T>::append(a[i++]);
        else if(i>=la) set.Vector<T>::append(b[j++]);
        else{
            if(a[i]==b[j]){i++;j++;}
            else if(a[i]<b[j]){set.Vector<T>::append(a[i++]);}
            else {set.Vector<T>::append(b[j++]);}
        }
    }
    return set;
}

template<typename T>
bool Set<T>::operator==(Set<T> &b){
    Set &a = *this;
    RANK i=0,j=0, la=a.size(),lb=b.size();
    if(la!=lb) return false;
    while(i<la){
        if(a[i++]!=b[j++]) return false;
    }
    return true;
}


template<typename T>
bool Set<T>::operator<(Set<T> &b){
    Set &a = *this;
    RANK i=0,j=0, la=a.size(),lb=b.size();
    if(la>=lb) return false;
    while(i<la){
        if(a[i]<b[j]) return false;
        if(a[i]==b[j]) {i++;j++;}
        else j++;
    }
    return true;
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
