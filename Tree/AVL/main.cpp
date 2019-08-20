#include "avl.h"
#include "../../Array/Vector/vector.h"

int geth(BNode(int) a){
    return a->height;
}
int daa(BNode(int) a){
    return a->data;
}

bool in(Vector<int> &v, int e){
    for(int i=0;i<v.size();i++){
        if(e==v[i]) return true;
    }
    return false;
}
void visit(int  a){
    cout<<a<<" ";
}

void insert(AVL<int> &a,int b){
    a.insert(b);
    a.getRoot()->printTree(daa);
    cout<<endl<<endl;
}

int main(){
    AVL<int> a = AVL<int>(7);
    // insert(a,47);
    // insert(a,0);
    // insert(a,9);
    // insert(a,34);
    // insert(a,65);
    // insert(a,23);
    

    Vector<int> v = Vector<int>();
    v.append(7);
    int x;
    // rand();
    for(int i=0;i<20;i++){
        x = rand()%100;
        cout<<"x: "<<x<<endl;
        v.map(visit);
        cout<<"  visit "<<v.size()<<endl;
    a.getRoot()->printTree(daa);
        cout<<endl;
        if(rand()%2){
            cout<<" insert"<<endl;
            if(!in(v,x)){
            a.insert(x);
            v.append(x);
            }
        }else{
            cout<<" remove"<<endl;
            if(in(v,x)){
            a.remove(x);
            v.remove(x);
            }
        }
    }
    a.getRoot()->printTree(daa);


}