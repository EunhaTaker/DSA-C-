## 目录

#### 数组

* [vector](#vector)
  * [有序数组](#sorted-vector)
    *  [集合](#set)
  * [完全二叉堆](#heap)
  * 栈


#### 链表
- [ ] list
  - [ ] 队列

#### 树
* [二叉树](#bintree)
  * [二叉搜索树](#BST)
    * AVL树
    * 伸展树
  * 森林

## 详情
<a name="vector"></a>
### vector

```CPP
// 自动扩容，采用2倍扩容策略
// RANK为秩类型，默认为int
```
+ 构造
  ```CPP
  // 传入容量，构造空vector
  Vector(RANK capacity=DEFAULT_CAP);
  // 传入长度和默认值
  Vector(RANK, const T& default_value);
  // 传入序列及区间，复制到本vector进行构建
  Vector(const T *A, RANK lo, RANK hi, bool heapFlag=false);
  // 复制另一个vector
  Vector(Vector<T> const& V, RANK lo=0, RANK hi=-1);
  // 使用列表初始化容器进行初始化
  Vector(const initializer_list<T>&);
  ```
+ 重载运算符
  ```CPP
  // []  循秩访问（允许负数索引）
  T e = arr[index];   // 读
  arr[index] = e;     // 改
  // +   返回两个vector合并产生的副本
  Vector<T> v = v1 + v2;
  // +=  在末端追加（vec表示Vector<int>)
  vec += 5;   // 追加单个元素
  vec += {5, 6};  // 追加序列
  vec += vec2;     // 追加另一Vector<int>
  ```
+ 访问
  ```CPP
  // 循秩访问（允许负数索引，索引范围：[-size, size) ）
  T get(int index);
  // 在区间内按值查找值的索引（自后向前）
  virtual RANK index(const T& value, RANK lo=0, RANK hi=-1);
  // 截取区间
  Vector<T> sub(RANK lo, RANK hi);
  ```
+ 插入
  ```CPP
  // 插入单个元素
  void insert(RANK idx, const T& value);
  // 插入一段vector
  void insert(RANK idx, const Vector<T> &v);
  ```
+ 末端追加
  ```CPP
  // 追加单个元素
  void append(const T& value);
  // 追加一段序列
  void extend(initializer_list<T> il);
  // 追加另一Vector
  void extend(const Vector<T> &);
  // 返回两个vector合并产生的副本
  auto concat(Vector<T> v);   // auto是为了便于派生类使用
  ```
+ 删除
  ```CPP
  // 按索引删除
  T pop(RANK idx);
  // 按值删除
  RANK remove(const T& value);
  // 删除区间
  bool delRng(RANK lo, RANK hi);
  // 清空
  void clear();
  ```
+ 获取信息
  ```CPP
  // 长度
  RANK size();
  // 是否为空
  bool empty();
  ```
+ 排序（冒泡、归并、堆排序）
  ```CPP
  // 默认排序
  void sort(RANK lo=0, RANK hi=-1);
  // 冒泡排序
  void bubbleSort(RANK lo=0, RANK hi=-1);
  // 归并排序
  void mergeSort(RANK lo=0, RANK hi=-1);
  // 堆排序
  void heapSort(RANK lo=0, RANK hi=-1);
  ```
+ 去重
  ```CPP
  virtual RANK unique();
  ```
+ 遍历操作
  ```CPP
  template<typename VST>  // VST是函数指针
  void map(VST &visit);
  ```

<a name="sorted-vector"></a>
### sorted vector

```CPP
// 继承自Vector，隐藏了父类部分api
```

+ 构造
  ```CPP
  // 构造--根据Vector
  SortedVector(const Vector<T>& sv, RANK lo=0, RANK hi=-1);
  // 构造--复制SortedVector
  SortedVector(const SortedVector<T> & sv, RANK lo=0, RANK hi=-1);
  // 构造--根据初始化列表
  SortedVector(const initializer_list<T>&);
  ```
+ 扩充
  ```CPP
  // 新增元素
  RANK add(const T& e);
  // 合并另一有序数组
  void extend(const SortedVector<T> &);
  // 合并两个SortedVector生成副本
  auto concat(const Vector<T> &);   // auto是为了便于派生类使用
  ```
+ 访问
  ```CPP
  // 继承，循秩访问（允许负数索引，索引范围：[-size, size) ）
  T get(int index);
  // 二分查找，查找失败时返回合适的插入位置
  virtual RANK index(const T& value, RANK lo=0, RANK hi=-1);
  // 继承，截取区间
  Vector<T> sub(RANK lo, RANK hi);
  ```
+ 重载运算符
  ```CPP
  // 继承，[]  循秩访问（允许负数索引）
  T e = arr[index];
  // +   返回两个vector合并产生的副本
  Vector<T> v = v1 + v2;
  // +=  在末端追加（vec表示Vector<int>)
  vec += 5;   // 追加单个元素
  vec += vec2;     // 追加另一SortedVector<int>
  ```
+ 删除
  ```CPP
  // 继承，按索引删除
  T pop(RANK idx);
  // 继承，按值删除
  RANK remove(const T& value);
  // 继承，删除区间
  bool delRng(RANK lo, RANK hi);
  // 继承，清空
  void clear();
  ```
+ 去重
  ```CPP
  virtual RANK unique();
  ```
+ 遍历操作
  ```CPP
  template<typename VST>  // 继承，VST是函数指针
  void map(VST &visit);
  ```


<a name="set"></a>
### set

+ 继承自sorted vector
<!-- + 隐藏了：+运算符、[]运算符、二分查找、唯一化、按索引或区间删除 -->
- 实现功能（或重写方法）：
  + 新增元素
  + 是否包含指定元素
  + 交集：运算符&
  + 并集：运算符|
  + 差集：运算符-
  + 对称差：运算符^
  + 相等：运算符==
  + 含于：运算符<

<a name="heap"></a>
### compl-heap
+ 继承自vector
- 实现功能
  + 获取最大元素
  + 删除最大元素
  + 插入元素

<!-- <a name="bintree"></a>
### bintree
- binNode实现：
  + 是否是父亲的左孩子
  + 左/右插入
  + 更新此节点及祖先节点高度
  + 先序遍历
  + 中序遍历
  + 打印以该节点为根的树
  + 顺/逆时针旋转
- binTree实现：
  + 查找
  + 删除

<a name="BST"></a>
### BST
+ 继承自binTree
- 实现功能：
  + 二叉查找
  + 获取最小/最大节点
  + 插入
  + 删除 -->

<!-- <a name="AVL"></a>
### AVL
+ 继承自BST
- 实现功能：
  +  -->