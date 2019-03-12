# 2. 空间配置器(allocator)
> *它总是隐藏在一切组件（更具体指容器，container）的背后，默默工作，默默付出。*
> 
> [2.1 空间配置器的标准接口](#21-空间配置器的标准接口)
> 
> [2.2 具备次配置能力的SGI空间配置器](#22-具备次配置能力（sub-allocation）的SGI空间配置器)

## 2.1 空间配置器的标准接口
> *根据STL的规范，allocator必须由些必要接口*

* **allocator::value_type**
* **allocator::pointer**
* **allocator::const_pointer**
* **allocator::reference**
* **allocator::const_reference**
* **allocator::size_type**
* **allocator::difference_type**
* **allocator::rebind**：一个嵌套的类模板。class rebind<U>拥有唯一成员other，是一个typedef，代表allocator<U>
* **allocator::allocator()**：默认构造函数default constructor
* **allocator::allocator(const allocator&)**：拷贝构造函数copy constructor
* **template<class U> allocator::allocator(const allocator<U>&)**：泛化的copy constructor
* **allocator::~allocator()**：析构函数，destructor
* **pointer allocator::address(reference x) const**：返回某个对象的地址，等同于&x
* **const_pointer allocator::address(const_reference x) const**：返回某个const对象的地址，等同于&x
* **pointer allocator::allocate(size_type n,cosnt void* = 0)**：配置足以存储n个T对象。第二个参数貌似没啥用
* **void allocator::deallocate(pointer p,size_type n)**：归还先前配置的空间
* **size_type allocator::max_size() const**：返回可成功配置的最大量
* **void allocator::construct(pointer p,const T& x)**：等同于new ((const void*)p) T(x)，意思是在p所指位置构造T对象
* **void allocator::destroy(pointer p)**：等同于p->~T()

> *根据前述标准，我们可以自行完成一个功能简单，接口不怎么齐全的[JJ::allocator](code/jjalloc_2.h)*

    //注：该配置其功能非常简单有限，很难与STL的容器进行搭配，因为无论哪种STL的allocator设计地都很复杂，还用到了缓冲区的概念。但这个示例很好地展示了配置器的思想。
    //file: jjalloc_2.h
    #ifndef _JJALLOC_2_H_
    #define _JJALLOC_2_H_

    #include <new>          //for placement new
    #include <cstddef>      //for ptrdiff_t,size_t
    #include <cstdlib>      //for exit()
    #include <climits>      //for UINT_MAX
    #include <iostream>     //for cerr

    namespace JJ {

        template <class T>
        inline T* _allocate(ptrdiff_t size,T*) {
            //T* 参数的传递只是为了让模板可以根据调用情况自动生成代码，而不用指定模板参数
            std::set_new_handler(0);    //指定new操作失败时的处理函数，传0参即表示不处理
            T* tmp = (T*)(::operator new((size_t)(sizeof(T)*size)));  //operator new 只分配内存，不执行构造函数
            if(tmp == 0) {
                std::cerr<<"out of memory"<<endl;
                exit(1);
            }
            return tmp;
        }

        template <class T>
        inline void _deallocate(T* buffer) {
            ::operator delete(buffer);      //operator delete 仅仅回收内存，不执行析构函数
        }

        template <class T1,class T2>
        inline void _construct(T1* p,const T2& value) {
            new (p) T1(value);      //在p所指内存上执行构造函数T1(const T2&)
        }

        template <class T>
        inline void _destroy(T* ptr) {
            ptr->~T();          //执行ptr所指对象的析构函数
        }

        template <class T>
        class allocator {
        public:
            typedef T value_type;
            typedef T* pointer;
            typedef const T* const_pointer;
            typedef T& reference;
            typedef const T& const_reference;
            typedef size_t size_type;
            typedef ptrdiff_t difference_type;

            template <class U>
            struct rebind
            {
                typedef allocator<U> other;
            };
            
            pointer allocate(size_type n,const void *hint = 0) {
                return _allocate((difference_type)n,(pointer)0);
            }

            void deallocate(pointer p,size_type n) {
                _deallocate(p);
            }

            void construct(pointer p, const T& value) {
                _construct(p,value);
            }

            void destroy(pointer p) {
                _destroy(p);
            }

            pointer address(reference x) {
                return (pointer)&x;
            }

            const_pointer address(const_reference x) {
                return (const_pointer)&x;
            }

            size_type max_size() const {
                return size_type(UINT_MAX/sizeof(T));
            }
        };
    }   //end namespace JJ
    #endif

## 2.2 具备次配置能力（sub-allocation）的SGI空间配置器