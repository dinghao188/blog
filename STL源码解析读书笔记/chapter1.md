# 1. STL概论与版本简介
> *STL是一套背后拥有先进技术和深厚理论的程序库*
> 
> [1.1 STL概论](#11-STL概论)
> 
> [1.2 STL六大组件，功能和应用](#12-STL六大组件，功能与运用)
> 
> [1.3 STL历史及版本](#13-STL历史及版本)
> 
> [1.4 STL头文件分布](#14-头文件及可链接目标文件的分布（书中没有）)

## 1.1 STL概论
> *STL（Standard Template Libraries）标准模板库，因此STL的核心是模板、也就是泛型编程*
* 提高复用性（reusability）是现代程序设计的重要目标,减少重复编写的代码量，并且一个设计实现良好的库可以大大避免许多不必要的错误
* STL的诞生是为了建立数据结构和算法的一套标准并降低其间的耦合（coupling），提升各自的独立性、弹性和交互操作性
* STL中的一些抽象概念：Assignable(可被赋值)、Default Constructor(默认构造函数，无参)、Equality Comparable(可判断是否相等)、LessThan Comparable(可比较大小)、Regular(正规)、Input Iterator(输入迭代器)、Output Iterator(输出迭代器)、Forward Iterator(单向迭代器)、Bidirectioan Iterator(双向迭代器)、Random Access Iterator(可随机存取的迭代器)、Unary Function(一元函数)、Binary Function(二元函数)、Predicate(一元判断式)、Binary Predicate(二元判断式)、sequence container(序列式容器)、associative container(关联式容器)...
## 1.2 STL六大组件，功能与运用
> *STL提供六大组件，彼此可以组合套用*
1. **容器（containers）**：各种数据结构，如vector，list，deque，map，set，用于存放数据
2. **算法（algorithms）**：各种常用算法如sort，search，copy，erase
3. **迭代器（iterators）**：容器和算法之间的粘合剂，就是所谓的“泛型指针”。共有五种类型，从实现角度看，迭代器是一种将operator*(不是乘，而是解引用符号)，operator->,operator++,operator--等与指针相关操作予以重载的class template。所有STL容器都有自己专属的迭代器。
4. **仿函数（functors）**：行为类似函数，可作为算法的某种策略。从实现角度来看，仿函数就是重载了operator()的class或class template。函数指针一般视为狭义的仿函数。
5. **适配器（adapters）**：用来修饰容器、仿函数、迭代器接口的东西，参考设计模式中的适配器模式。
6. **配置器（allocators）**：负责空间的配置与管理。从实现角度看，配置器是实现了动态空间配置、空间管理、空间释放的class template。
## 1.3 STL历史及版本
> *美国人Richard Stallman于1984年离开麻省理工学院，创立了自由软件基金会，写下著名的GNU（GNU is Not Unix）宣言，开始进行名为GNU的开放源代码计划*
* HP STL:HP实现版本
* P.J. Plauger实现版本
* Rouge Wave实现版本
* STL port实现版本
* SGI STL:Silicon Graphics Computer Systems,Inc.公司发展。被gcc采用的版本。
## 1.4 头文件及可链接目标文件的分布（书中没有）
> *我使用的是Ubuntu 18.04版本的gcc，不同版本分布位置大体上都类似*
* 头文件一般在**/usr/include/c++(或者g++)/**目录或者其子孙目录下，这些头文件大致可分为五种：
  * C++标准规范下的C头文件（无扩展名），如cstdio，cstring
  * C++标准程序库中不属于STL范畴的内容，如stream，string
  * STL标准头文件（无扩展名），如vector，list，deque，map，algorithm
  * C++ Standard定案前、HP所规范的STL头文件，如vector.h，list.h
  * SGI STL内部文件，例如stl_vector.h,stl_deque.h,stl_list.h
* 可链接目标文件（.o）、静态链接库文件(.a)、动态链接库文件（.so）,一般在**/usr/lib/gcc/**目录或者其子孙目录下