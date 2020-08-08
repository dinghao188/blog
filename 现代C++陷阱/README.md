# 记录一些现代C++使用过程中容易被忽略的一些"陷阱"

## 1. 线程锁相关

### 1.1 condition_variable

- `condition_variable`在调用`wait(unique_lock<mutex>&)`函数时，会把传入的锁变量先进行unlock(),并且在退出时会重新把锁变量lock()。对于另一个重载的wait函数也是如此。因此我们可以用下面的方式实现一个"生产者-消费者"模型。

```cpp
mutex m;
condition_variable c;

thread_producer()
{
    {
        unique_lock<mutex> lock(m);  // 离开作用域自动释放锁
        // 生产步骤
    }
    c.notify_one();
}

thread_consumer()
{
    {
        unique_lock<mutex> lock(m);
        c.wait(lock, /*这里可以通过lambda表达式的形式来对消费队列进行判空*/);
        // 消费步骤
    }
}
```

## 2. 使用auto进行型别推导有明显好处的场景

### 2.1 使用auto保存闭包（lambda函数），而不是使用function<T>对象来保存闭包

使用auto保存闭包，比使用function对象保存闭包，产生的调用开销和内存占用更小。

考虑下面的代码：

```cpp
#include <functional>

using std::function;

void test() {
    auto lamb = 
        []() {return 0x1111};
    function<int()> func = 
        []() {return 0x2222};

    lamb();
    func();
}
```

我们可以通过gdb调试的时候来查看lamb和func这两个变量的大小，lamb是1，func是32。我大胆地猜测了一下原因，auto方式声明的闭包被编译器实现为`一个重载了调用运算符的空的结构体`;但是函数对象是为了保存所有可以调用的对象而实现的，所以lambda表达式其实算是函数对象所指之物中的一种。所以使用auto进行自动推导来声明闭包的调用效率高就显而易见了，函数对象一定经过了很多层的封装，自然就会产生一层一层的调用(可以对上面的代码进行反汇编看一下)：

```asm
000000000000001f <_Z4testv>:                                                             # 这就是上面的test函数
  1f:	55                   	push   %rbp
  20:	48 89 e5             	mov    %rsp,%rbp
  23:	53                   	push   %rbx
  24:	48 83 ec 48          	sub    $0x48,%rsp
  28:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  2f:	00 00
  31:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  35:	31 c0                	xor    %eax,%eax
  37:	48 8d 45 c0          	lea    -0x40(%rbp),%rax
  3b:	48 89 c7             	mov    %rax,%rdi
  3e:	e8 5b 00 00 00       	callq  9e <_ZNSt8functionIFivEEC1IZ4testvEUlvE0_vvEET_> # 这是func对象的构造过程，这个过程代码就非常多了
  43:	48 8d 45 bf          	lea    -0x41(%rbp),%rax                                 # 这是获取lamb变量的地址
  47:	48 89 c7             	mov    %rax,%rdi                                        # C++调用类成员方法的汇编都是先把对象的地址先保存在rdi寄存器中，然后去掉用相应的方法
  4a:	e8 b1 ff ff ff       	callq  0 <_ZZ4testvENKUlvE_clEv>                        # 这是真正去调用闭包函数的汇编，这三行确实印证了我们上面的一个大胆的想法
  4f:	48 8d 45 c0          	lea    -0x40(%rbp),%rax                                 # 这里是取func对象的地址rbp-0x40，上面的lamb对象的地址是rbp-0x41，又恰好说明了闭包对象的大小确实为1
  53:	48 89 c7             	mov    %rax,%rdi                                        # 余下的步骤基本上都是调用func对象所指的闭包函数的过程，其实就是一层一层解封装的调用过程，效率高低很明显
  56:	e8 00 00 00 00       	callq  5b <_Z4testv+0x3c>
  5b:	48 8d 45 c0          	lea    -0x40(%rbp),%rax
  5f:	48 89 c7             	mov    %rax,%rdi
  62:	e8 00 00 00 00       	callq  67 <_Z4testv+0x48>
  67:	90                   	nop
  68:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  6c:	64 48 2b 04 25 28 00 	sub    %fs:0x28,%rax
  73:	00 00
  75:	74 21                	je     98 <_Z4testv+0x79>
  77:	eb 1a                	jmp    93 <_Z4testv+0x74>
  79:	48 89 c3             	mov    %rax,%rbx
  7c:	48 8d 45 c0          	lea    -0x40(%rbp),%rax
  80:	48 89 c7             	mov    %rax,%rdi
  83:	e8 00 00 00 00       	callq  88 <_Z4testv+0x69>
  88:	48 89 d8             	mov    %rbx,%rax
  8b:	48 89 c7             	mov    %rax,%rdi
  8e:	e8 00 00 00 00       	callq  93 <_Z4testv+0x74>
  93:	e8 00 00 00 00       	callq  98 <_Z4testv+0x79>
  98:	48 8b 5d f8          	mov    -0x8(%rbp),%rbx
  9c:	c9                   	leaveq
  9d:	c3                   	retq
```

我们再通过下面的例更好地理解一下闭包的本质:

```cpp
#include <iostream>

using namespace std;

struct Lmabda {
    void operator() () { cout << "Am i like a lambda function?" << endl; }
};

int main() {
    Lambda lamb;  //声明一个闭包（假的）
    lamb();       //调用闭包（假的）
}
```

上面例子的输出是`Am i like a lambda function?`。

### 2.2 使用foreach遍历容器的时候

在使用foreach遍历容器的时候，用auto声明迭代变量有时候可以避免容器内的元素进行拷贝构造。

比如下面的情况：

```cpp
map<string, int> m;

for (const pair<string, int> &item : m) {  // 这里如果不加const，会编译不了
    ... ...
}
```

看起来不错哈，但是实际上由于map的键值保存的是const类型的变量，所以上面的语句会产生大量的无用复制，也就是用pair<const string, int>&来构造一个`临时的pair<string, int>对象`，所以前面说必须要加const，因为右值没法赋值给左值引用，但是右值可以赋值给常值左值引用（可以去了解下左值引用和右值引用）。实际上我们应该用`const pair<const string, int> &item : m`，或者就用`const auto &item : m`。看吧，auto帮我们省了不少事呢!
