#include "../Vector/sorted_vector.h"

template<typename T>
class Set : public SortedVector<T>{
public:
    // 构造--根据容量
    Set(RANK capacity=DEFAULT_CAP): SortedVector<T>::SortedVector(capacity){};
    Set(const Vector<T>& set): SortedVector<T>::SortedVector(set) {SortedVector<T>::unique();}
    Set(const initializer_list<T>& il): SortedVector<T>::SortedVector(il) {SortedVector<T>::unique();}
    // 新增
    bool add(const T& e);
    // 删除(不予返回删除位置)
    void remove(const T& e){SortedVector<T>::remove(e);}
    // 是否包含元素e
    bool contain(T const& e) const;
    // 成为与另一集合的 并、交、差、对称差
    void operator|=(const Set<T> &a);
    void operator&=(const Set<T> &a);
    void operator-=(const Set<T> &a);
    void operator^=(const Set<T> &a);
    //并集 |
    Set<T> operator|(const Set<T> &a){auto newSet = *this; newSet|=a; return newSet;}
    //交集 &
    Set<T> operator&(const Set<T> &a){auto newSet = *this; newSet&=a; return newSet;}
    //差集 -
    Set<T> operator-(const Set<T> &a){auto newSet = *this; newSet-=a; return newSet;}
    //对称差 ^
    Set<T> operator^(const Set<T> &a){auto newSet = *this; newSet^=a; return newSet;}
    //集合相等 =
    bool operator==(const Set<T>&);
    //真含于 <
    bool operator<(const Set<T>&);
    //衍生运算符
    bool operator<=(const Set<T>& b) {Set<T> &a=*this; return a==b || a<b;}
    bool operator>(const Set<T>& b) {Set<T> &a=*this; return !(a<b);}
    bool operator>=(const Set<T>& b) {Set<T> &a=*this; return a==b || a>b;}


protected:
    //重载[]
    T operator [](RANK idx)const {return this->_elem[idx];}
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
bool Set<T>::add(const T& e){
    RANK idx = SortedVector<T>::index(e);
    if(this->_elem[idx] != e){  //若集合中无元素e，插入之
        Vector<T>::insert(idx, e);
        return true;
    }else return false;
}


template<typename T>    // 是否包含
bool Set<T>::contain(T const& e) const{
    return (SortedVector<T>::find(e)>=0);
}


template<typename T>    // 并集
void Set<T>::operator|=(const Set<T>& a){
    SortedVector<T>::extend(a);
    SortedVector<T>::unique();
}


template<typename T>    // 交集
void Set<T>::operator&=(const Set<T> &b){
    Set<T> &a = *this;  // 仅为了美观统一
    RANK la=a.size(), lb=b.size();
    RANK i=0,j=0;
    this->_size = 0;
    while(i<la && j<lb){
        if(a[i]==b[j]){this->_elem[this->_size++]=a[i++]; j++;}
        else if(a[i]<b[j]) i++;
        else j++;
    }
}


template<typename T>    // 差集
void Set<T>::operator-=(const Set<T> &b){
    Set<T> &a = *this;
    RANK i=0,j=0;
    RANK la=a.size(), lb=b.size();
    this->_size = 0;
    while(i<la){
        if(j<lb){
            if(a[i]==b[j]){i++;j++;}
            else if(a[i]<b[j]){this->_elem[this->_size++] = a[i++];}
            else {j++;}
        }else this->_elem[this->_size++] = a[i++];
    }
}


template<typename T>    // 对称差
void Set<T>::operator^=(const Set<T> &b){
    Set<T> &a = *this;
    RANK i=0,j=0;
    RANK la=a.size(), lb=b.size();
    this->_size = 0;
    while(i<la || j<lb){
        if((j>=lb&&i<la) || a[i]<b[j]) this->_elem[this->_size++] = a[i++];
        else if((i>=la&&j<lb) || b[j]<a[i]) this->_elem[this->_size++] = b[j++];
        else{   // a[i]==b[j]
            i++;j++;
        }
    }
}

template<typename T>    // 判等
bool Set<T>::operator==(const Set<T> &b){
    Set &a = *this;
    RANK i=0,j=0, la=a.size(),lb=b.size();
    if(la!=lb) return false;
    while(i<la){
        if(a[i++]!=b[j++]) return false;
    }
    return true;
}


template<typename T>    // 真含于
bool Set<T>::operator <(const Set<T> &b){
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


// template<typename T>    // 并集
// Set<T> Set<T>::operator |(const Set<T> & a){
//     Set<T> c;
//     Set<T> &b = *this;
//     RANK i=0,j=0;
//     RANK la=a.size(), lb=b.size();
//     while(i<la || j<lb){
//         if((i>=la && j<lb) || b[j]<a[i]) c.add(b[j++]);     // 保持有序性
//         else if((j>=lb && i<la) || a[i]<b[j]) c.add(a[i++]);
//         else if(a[i]==b[j]){ //保持唯一性
//             c.add(a[i++]);
//             j++;
//         }
//     }
//     return c;
// }
