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