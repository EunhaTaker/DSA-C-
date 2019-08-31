#include<iostream>
using namespace std;
#include "stack.h"

int main(){
    Stack<int> st;
    cout<<st.empty()<<endl;
    st.push(6);
    cout<<st.empty()<<endl;
    int a = st.top();
    cout<<a<<endl;
    st.pop();
    cout<<st.empty()<<endl;
}