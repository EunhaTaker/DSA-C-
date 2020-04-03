#include <iostream>
#include "string.h"
using namespace std;

void print(int& n){
    cout<<n<<" ";
}


int main(){
    String str = "hello worl";
    String str1 = String("d! world");
    cout<<"str="<<str<<"\nstr1="<<str1<<endl;
    cout<<"str sub[2,5): "<<str.sub(2, 5)<<endl;
    cout<<"str cut[2,5), str="; str.cut(2, 5); cout<<str<<endl;
    cout<<"str+=str1 str="; str+=str1; 
    cout<<str<<endl;
    cout<<"find \"world\" from str, index="<<str.find("world")<<endl;
    cout<<"str replace all \"world\" to \"c++\", replace times="<<str.replace("world", String("c++")); cout<<"  str="<<str<<endl;
    cout<<"str+=\'a\', str+=\'bc\', str="; str+='a', str+="bc"; cout<<str<<endl;
}