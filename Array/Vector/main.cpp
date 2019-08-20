#include <iostream>
#include "vector.h"
// template<typename T>
// class Test{
//     public:
//     T v;
//     Test(T b){
//         v= b;
//     }
// };

int main()
{
    using namespace std;
    int e[] = {1, 2, 3, 4,9,4,2,1};
    Vector<int> v =  Vector<int>(e, 0, 7);
    // cout<<v.size()<<endl;
    v.unique();
    for(int i = 0;i<v.size();i++){
        cout<<v[i]<<endl;
    }
}
