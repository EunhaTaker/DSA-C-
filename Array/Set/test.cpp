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
int main(){
    Set<int> l = {6,3,2,7,3,6,9,0,3};
    cout<<"l: ";l.map(look);cout<<endl;
    // cout<<l.contain(0)<<endl;
    // l.add(5);
    // l.map(look);cout<<endl;
    Set<int> m = {8,3,2,5,8,4};
    cout<<"m: ";m.map(look);cout<<endl;
    cout<<"l|m: ";(l|m).map(look);cout<<endl;
    cout<<"l&m: ";(l&m).map(look);cout<<endl;
    cout<<"l-m: ";(l-m).map(look);cout<<endl;
    cout<<"l^m: ";(l^m).map(look);cout<<endl;
    Set<int> n = {8,3,2,5,8,4};
    cout<<"n: ";n.map(look);cout<<endl;
    Set<int> o = {2,3,4,5};
    cout<<"o: ";o.map(look);cout<<endl;
    cout<<"m==n: "<<(m==n)<<endl;
    cout<<"o<n: "<<(o<m)<<endl;
    cout<<"n>=o: "<<(n>=o)<<endl;

}