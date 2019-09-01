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
    l.map(look);
    l.add(5);
    l.map(look);
    cout<<endl;
    cout<<l.contain(0)<<endl;
    Set<int> m = {8,3,2,5,8,4};
    (l|m).map(look);
}