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
