#pragma once
#include "../Vector/vector.h"
#include <string.h>

class String: public Vector<char>{
protected:
    // 获取内部字符数组，意义在于补充\0
    char* getElem() const;

public:
    // 默认构造--复制const char*
    String(const char* A="", RANK lo=0, RANK hi=-1);
    // 拷贝构造
    String(const String& str, RANK lo=0, RANK hi=-1): String(str.getElem(), lo, hi){}


    // 查找
    RANK find(const char* A);
    RANK find(const String& str) {return find(str.getElem());}
    // 替换（返回替换次数）
    int replace(const char*, const char*);
    int replace(const String& str, const char* A) {return replace(str.getElem(), A);}
    int replace(const String& str1, const String& str2) {return replace(str1.getElem(), str2.getElem());}
    int replace(const char* A, const String& str) {return replace(A, str.getElem());}
    //插入
    void insert(RANK, const char*);
    void insert(RANK idx, const String& str) {insert(idx, str.getElem());}
    // 截取
    String sub(RANK, RANK);
    // 截去
    String cut(RANK, RANK);
    // 重载+
    String operator+(const char*);
    String operator+(const char ch);  // char* 与 char& 冲突？？？
    String operator+(const String& str){return operator+(str.getElem());}
    // 重载+=
    String& operator+=(const char*);
    String& operator+=(const char& ch){Vector<char>::append(ch);}
    String& operator+=(const String& str){operator+=(str.getElem());}

    // 重载==
    bool operator ==(const char*);
    // 重载<<
    friend std::ostream& operator <<(std::ostream&, const String&);

private:    //禁用以下方法
    //尾部追加
    void append();
    ///排序
    void sort();
};
// #include "string_implement.h"


String::String(const char* A, RANK lo, RANK hi): Vector<char>::Vector(A, lo, hi!=-1?hi:strlen(A)) {}

std::ostream& operator <<(std::ostream& os, const String& str){
    for(int i=0; i<str._size; i++) os<<str[i];
    return os;
}


char* String::getElem() const{
    this->_elem[this->_size] = '\0';
    return this->_elem;
}


String String::operator+(const char* A){
    auto str = *this;
    str.Vector<char>::extend(A, 0, strlen(A));
    return str;
};


String& String::operator+=(const char* A){
    Vector<char>::extend(A, 0, strlen(A));
};


// 截取
String String::sub(RANK lo, RANK hi){
    return String(this->_elem, lo, hi);
}


// 截去
String String::cut(RANK lo, RANK hi){
    auto substr = sub(lo, hi);
    Vector<char>::delRng(lo, hi);
    return substr;
}


// 替换
int String::replace(const char* A1, const char* A2){
    RANK idx;
    int count = 0;
    RANK len1 = strlen(A1), len2 = strlen(A2);
    while((idx=find(A1))!=-1){      // 查找
        this->expand(len2-len1);    // 扩容
        Vector<char>::move(idx+len1, this->_size, len2-len1);   // 腾挪
        Vector<char>::carry(A2, 0, len2, idx);  // 拷贝
        count ++;   // 统计
        _size += len2-len1;     // 更新长度
    }
    return count;
}


void String::insert(RANK idx, const char* A){
    RANK len = strlen(A);
    expand(len);
    Vector<char>::move(idx, this->_size, len);
    carry(A, 0, len, idx);
}


Vector<int> buildKMP(const char* pattern){
    /* 建立kmp查询表 */
    int len=strlen(pattern);
    Vector<int> next(len, -1);
    int k=next[0]=-1, i=0;
    while(i<len){
        if(k==-1 || pattern[i]==pattern[k]){
            if(k!=-1) next[i] = next[k];
            i++;
            k++;
        }else{
            next[i] = k;
            k = next[k];
        }
    }
    return next;
}


RANK String::find(const char* A){
    /* KMP算法 查找模式串 */
    Vector<int> next = buildKMP(A);
    int k=0, i=0, len=strlen(A);
    while(i<this->_size && k<len){
        if(k==-1 || this->get(i)==A[k]){
            k++;
            i++;
        }else{
            k = next[k];
        }
    }
    return k==len? i-k: -1;
}


Vector<int> buildBM(const char* A){
    int n = strlen(A);
    Vector<int> gs(n, 0);
    int k=n-1, i=n-1;
    while(i>=0){
        ;
    }
    return gs;
}