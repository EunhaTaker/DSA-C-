#include "vector.h"

class SortedVector: public Vector{
    
public:

//唯一化
rank unique(){
    int i=0,j=0;    //各对互异相邻元素的下标
    while(++j<size)
        //跳过雷同元素，发现不同元素时，将j处元素移至i右侧
        if(_elem[i]!=_elem[j]) _elem[++i]=_elem[j];
    _size = ++i;
    return j-i;
}

//二分查找
rank binSearch(T e, rank lo=0, rank hi=_size){
    rank mi;
    while(lo<hi){   //直至区间长度缩短为0
        mi = (lo+hi)>>1;
        e<_elem[mi]? hi=mi: lo=mi+1;    //缩短区间时无视mi处元素
    }
    //最终lo位于<=e的最大元素右侧一位
    return lo-1;
}

//添加至合适的位置
rank add(T e){
    rank idx=binSearch(e)+1;
    insert(idx, e);
    return idx;
}


}