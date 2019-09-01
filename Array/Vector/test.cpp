#include <iostream>
#include "sorted_vector.h"

void look(int& a){
    cout<<a<<" ";
}

int vmain()
{   
    Vector<int> v =  {1, 2, 3, 4,9,4,2,1};
    cout<<"size: "<<v.size()<<endl;
    // v.unique();
    cout<<"it's v: ";v.map(look);cout<<endl;
    Vector<int> v1 = {5,5,5};
    v.insert(4, v1);
    cout<<"insert a vector: ";v.map(look);cout<<endl;
    Vector<int> v2 = {0,0,0};
    cout<<"operator + : ";(v+v2).map(look);cout<<endl;
    cout<<"v not change: ";v.map(look);cout<<endl;
    return 0;

}

int main(){
    SortedVector<int> sv = {4,23,7,5,0,5};
    cout<<"it's sv: ";sv.map(look);cout<<endl;
    SortedVector<int> sv1 = {9,0,1,-3,56};
    cout<<"sortedvector's operate+ : ";(sv+sv1).map(look);cout<<endl;
    return 0;
}
