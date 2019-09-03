## 数据结构自实现

### 数组

* [vector](#vector)
  * [有序数组](#sorted-vector)
    *  [集合](#set)
  * 完全二叉堆
  * 栈



### 链表
- [ ] list
  - [ ] 队列

### 树
* 二叉树
  * 二叉搜索树
    * AVL树
    * 伸展树
  * 森林


<a name="vector"></a>
### vector
+ 2倍扩充策略
- 实现功能：
  + 循秩访问：运算符[]
  + 合并两个vector：运算符+
  + 按值查找（自后向前）
  + 插入单个元素
  + 插入一段vector
  + 末尾追加
  + 按索引删除元素
  + 按值删除元素
  + 删除区间
  + 清空
  + 获取大小
  + 判空
  + 排序（冒泡、归并）
  + 唯一化

<a name="sorted-vector"></a>
### sorted vector
+ 继承自vector
+ 私有化了：插入操作、排序操作、尾部追加
- 实现功能（或重写方法）：
  + 合并两个sorted-vector（在vector合并的基础上排序）：运算符+
  + 二分查找
  + 唯一化
  + 新增元素

<a name="set"></a>
### set
+ 继承自sorted vector
+ 私有化了：+运算符、[]运算符、二分查找、唯一化
- 实现功能（或重写方法）：
  + 新增元素
  + 是否包含指定元素
  + 交集：运算符&
  + 并集：运算符|
  + 差集：运算符-
  + 对称差：运算符^
  + 相等：运算符==
  + 含于：运算符<