#include <iostream>
using namespace std;
// #ifndef _LIBCPP_VECTOR
// #define _LIBCPP_VECTOR
// template<class T, class Allocator = allocator<T> >
#include "set.h"

void iltst(initializer_list<int> il){
    int* _elem = new int[il.size()];
    int i=0;
    for(auto &e: il){
        _elem[i++] = e;
    }
    for(int i=0;i<il.size();i++){
        cout<<_elem[i]<<endl;
    }
}
void look(int& a){
    cout<<a<<" ";
}

class yy{
    public:
    yy(){cout<<"构造"<<endl;}
    yy(yy &y){cout<<"构造"<<endl;}
    ~yy(){cout<<"稀构"<<endl;}
};
yy fun(){
    yy y;
    return y;
}
void ff(int const& n){cout<<n;}
int main(){
    Set<int> l = {6,3,2,7,3,6,9,0,3};
    cout<<"use {6,3,2,7,3,6,9,0,3} build set l: ";l.map(look);cout<<endl;
    cout<<"l >> 3? "<<(l>>3)<<endl;
    cout<<"-1 << l? "<<(1<<l)<<endl;
    cout<<"l add 5, l= "; l.add(5);l.map(look);cout<<endl;
    Set<int> m = {8,3,2,5,8,4};
    cout<<"use {8,3,2,5,8,4} build set m: ";m.map(look);cout<<endl;
    cout<<"并集 l|m: ";(l|m).map(look);cout<<endl;
    cout<<"交集 l&m: ";(l&m).map(look);cout<<endl;
    cout<<"差集 l-m: ";(l-m).map(look);cout<<endl;
    cout<<"对称差 l^m: ";(l^m).map(look);cout<<endl;
    Set<int> n = {8,3,2,5,8,4};
    cout<<"n: ";n.map(look);cout<<endl;
    Set<int> o = {2,3,4,5};
    cout<<"o: ";o.map(look);cout<<endl;
    cout<<"相等 m==n: "<<(m==n)<<endl;
    cout<<"真含于 o<n: "<<(o<m)<<endl;
    cout<<"包含 n>=o: "<<(n>=o)<<endl;
}