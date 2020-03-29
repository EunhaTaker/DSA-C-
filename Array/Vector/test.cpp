#include <iostream>
#include "sorted_vector.h"
using std::cout;
using std::endl;

#define pop() target+=ans.back();ans.pop_back();if(ans.empty()){i++;j=i;continue;}
void look(int& a){
    cout<<a<<" ";
}


int vector_test()
{
    Vector<int> v =  {1, 2, 3, 4, 5, 6, 7, 8};
    cout<<"it's v: ";v.map(look);cout<<endl;
    cout<<"v' size: "<<v.size()<<endl;
    v.insert(4, {9,9,9});
    cout<<"insert {9,9,9} to index 4 of v: v= ";v.map(look);cout<<endl;
    Vector<int> v2 = {0,0,0};
    cout<<"it's v2: ";v2.map(look);cout<<endl;
    cout<<"v += v2  v= "; v+=v2; v.map(look); cout<<endl;
    cout<<"delete range[3, 7): v= "; v.delRng(3, 7); v.map(look); cout<<endl;
    cout<<"sub[4,7) of v: subv= "; auto subv = v.sub(4,7); subv.map(look); cout<<endl;
    v.unique();cout<<"unique v: ";v.map(look);cout<<endl;
    v.heapSort();
    cout<<"heapsort v: ";v.map(look);cout<<endl;
    return 0;
}

int sortedvector_test(){
    // 初始化列表初始化
    SortedVector<int> sv = {4,23,7,5,0,5};
    cout<<"it's sv: ";sv.map(look);cout<<endl;
    cout<<"add 22 and add 55: ";sv.add(22);sv.add(55); sv.map(look);cout<<endl;
    
    
    SortedVector<int> sv1 = {9,0,1,-3,56};
    cout<<"it's sv1: ";sv1.map(look);cout<<endl;
    cout<<"sv+=sv1(extend), sv= ";sv+=sv1; sv.map(look);cout<<endl;
    return 0;
}


#include<math.h>

int main(){
    cout<<"test vector:\n";
    vector_test();
    cout<<"\n\ntest sorted vector:\n";
    sortedvector_test();
    
}

