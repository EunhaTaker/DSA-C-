#include <iostream>
#include "string.h"
using namespace std;

// #include <set>
// #include <vector>
// #include <queue>

void print(int& n){
    cout<<n<<" ";
}

int main(){
    String str = "hello worl";
    String str1 = String("d! world");
    cout<<"str="<<str<<" str1= "<<str1<<endl;
    cout<<"str.sub(2,5): "<<str.sub(2, 5)<<endl;
    cout<<"str.cut(2,5), str= "; str.cut(2, 5); cout<<str<<endl;
    cout<<"str+=str1 str= "; str+=str1; 
    cout<<str<<endl;
    cout<<"find world from find, index= "<<str.find("world")<<endl;
    cout<<"str replace world to c++, replace times = "; str.replace("world", String("c++")); cout<<"str= "<<str<<endl;
    cout<<"str+=\'a\', str+=\'bc\', str= "; str+='a', str+="bc"; cout<<str<<endl;
    // auto next = buildKMP("ababcabc");
    // next.map(print);
    // cout<<String("ababcababcabc").find("ababcabc")<<endl;
}