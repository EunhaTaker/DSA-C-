#include "vector.h"

template<typename T>
class SortedVector: public Vector<T>{
    
public:

    //唯一化
    RANK unique(){
        int i=0,j=0;    //各对互异相邻元素的下标
        while(++j<this->_size)
            //跳过雷同元素，发现不同元素时，将j处元素移至i右侧
            if(this->_elem[i]!=this->_elem[j]) this->_elem[++i]=this->_elem[j];
        this->_size = ++i;
        return j-i;
    }

    //二分查找
    RANK binSearch(T e, RANK lo=0, RANK hi=-1){
        if(hi==-1) hi = this->_size;
        RANK mi;
        while(lo<hi){   //直至区间长度缩短为0
            mi = (lo+hi)>>1;
            e<this->_elem[mi]? hi=mi: lo=mi+1;    //缩短区间时无视mi处元素
        }
        //最终lo位于<=e的最大元素右侧一位
        return lo-1;
    }

    //添加至合适的位置
    RANK add(T e){
        RANK idx=binSearch(e)+1;
        this->insert(idx, e);
        return idx;
    }


};