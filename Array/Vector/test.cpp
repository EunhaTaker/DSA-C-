#include <iostream>
#include "sorted_vector.h"
#define pop() target+=ans.back();ans.pop_back();if(ans.empty()){i++;j=i;continue;}
void look(int& a){
    cout<<a<<" ";
}

class F{
    public :
    F(){cout<<"f constru";apply();}
    virtual void apply(){cout<<"f apply";}
    ~F(){cout<<"F析构 ";}
};
class S{
    public :
    S(){cout<<"null \n";}
    S(int n){cout<<"int n\n";}
    void jianjie(){apply();}
    virtual void apply(){cout<<"s apply";}
    void nvfun(){cout<<"s nvfun\n";}
    // virtual void apply()=0;
    ~S(){}
};
class GS:public S{
    public:
    GS(){}
    virtual void apply(){cout<<"gs apply";}
    void nvfun(){cout<<"gs nvfun\n";}
    ~GS(){}
};

#include<memory>
int main()
{
    
    // shared_ptr<GS> g = shared_ptr<GS>();
    // cout<<g.use_count();
    // shared_ptr<GS> gg = g;
    // cout<<g.use_count();
    return 0;
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
    v.heapSort();
    cout<<"heapsort: ";v.map(look);cout<<endl;
    return 0;
}

int smain(){
    SortedVector<int> sv = {4,23,7,5,0,5};
    cout<<"it's sv: ";sv.map(look);cout<<endl;
    SortedVector<int> sv1 = {9,0,1,-3,56};
    cout<<"it's sv1: ";sv1.map(look);cout<<endl;
    cout<<"sortedvector's operate+ : ";(sv+sv1).map(look);cout<<endl;
    return 0;
}

int mmain(){
    shared_ptr<Solution> s(new Solution);
    cout<<s.use_count()<<endl;
    shared_ptr<Solution> t = s;
    cout<<s.use_count()<<endl;
    s = nullptr;
    cout<<t.use_count()<<endl;
    weak_ptr<Solution> w = t;
    w.lock();
    cout<<w.lock().use_count()<<endl;
    cout<<t.use_count()<<endl;
    return 0;
    
    
}
