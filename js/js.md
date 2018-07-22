# JavaScript，Html相关的那些事

## 一、JS基本语法

- JS是一种解释性的脚本语言，没有编译的过程，与Python，Matlab等相似

- 基本数据类型有：object,function,number,string,boolean,null,undefined

- 函数是第一等对象

- 常用内置对象有:Number,Math,String,Date,Array,global,Object,Function等，它们都是函数对象(global除外，他是Object的实例对象)，也可以叫做类。

- 两个特殊的对象：Object和Function.
    1. Object特殊之处在于Object.prototype是凭空出来的。语法上，所有{}都会被解释为new Object().

    2. Function特殊在__proto__=prototype.语法上所有函数声明都会被解释为new Function().

    3. 以上列出的所有对象，当其作为Function的实例化对象时，其__proto__均指向Function的prototype,但是其本身的prototype仍然指代该类的原型对象，且prototype.--proto--指向Object的prototype。类型扩展时规律相同。

- JS的函数中的**this**，以及apply,call,和bind对this引用的影响
    1. 所有函数若没有明确指出调用它的对象，则this默认均指向global对象。

    2. 使用new调用函数时，会返回该函数的实例对象，即便函数里加了返回语句。

    3. 使用apply，call和bind可改变函数内this引用的对象，如下代码所示

            function bark(){
                console.log("I am a "+this.name);
            }   //工具函数
            var dog = {
                name:'dog'
            }   //怎样通过dog对象正确调用bark函数输出‘I am a dog’？？？？

            //1. 假定希望调用的函数为function，希望调用该函数的对象为thisObj，则通过function.call(thisObj,参数列表)可以实现，对于该例子就是：
            bark.call(dog);

            //2. 对于apply调用形式如下function.apply(thisObj,[参数列表])
            bark.apply(dog);
            //可见call与apply唯一的区别在于参数列表的形式不同，call通过多个形式参数传参，apply通过数组传参。注意：参数顺序均要与原先的顺序一一对应。

            //3. function.bind(thisObj);bind与前两者的不同之处在于其返回值是函数，故需要调用返回的函数才能完成功能，其参数可像call一样传递，也可以传给返回的函数。
            bark.bind(dog)();
        ![call](output1.png)

        **感觉有点面向切面编程的意思**，
- 类与对象之间的关系通过原型链串起来:详情见[继承与原型链](https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Inheritance_and_the_prototype_chain)。

- JS中内置了Global对象，函数调用时，若没有明确的调用对象，则函数内的this均指向Global对象

## 二、JS与Html DOM

- 每个载入浏览器的HTML都会成为Document对象
- HTML DOM中每个部分都是节点
    1. 文档本身是*文档(Document对象)节点*
    2. 所有的HTML元素是*元素(Element对象)节点*
    3. 所有HTML属性是*属性(Attribute对象)节点*
    4. HTML元素内的文本是*文本节点*
    5. 注释是*注释节点*
- 要操作相应的节点，只需通过相应的节点对象调用对应的方法即可

## 三、原生的JS Ajax操作

    //声明变量，用于存放XMLHttpRequest(用于ajax请求的核心对象)
    var http;
    //创建对象
    if(window.XMLHttpRequest) {
        _http = new XMLHttpRequest();
    } else {
        _http = new ActiveXObject("Microsoft.XMLHTTP");
    }

    //打开接口的连接，并发送请求
    http.open("get","http://www.baidu.com");
    /**
    * 可以放一些设置请求头信息的代码
    * 如，setRequestHeader("test","www.baidu.com");
    */
    http.send();

    //获取数据
    http.onreadystatechange=function(){
        if(http.readyState=4 && http.status==200){
            //请求成功
        } else {
            //请求失败
        }
    }

## 四、JQuery(一个优秀的开源JS库) Ajax操作

>### 1. $.ajax([settings])
>>settings是可选参数。用于配置ajax请求的键值对集合。可以通过$.ajaxSetup()设置任何选项的默认值。常用选项如下:
>>
>>- options : *Object* : Ajax请求设置对应的对象
>>- async : *Boolean* : 默认为true表示异步请求
>>- beforeSend(XHR) : *function* : 发送请求前可修改XMLHttpRequest对象，返回false可取消本次ajax请求。
>>- cache : *Boolean* : 默认为true，dataTypee为script和jsonp时默认为false，设置为false是不缓存此页面。
>>- complete(XHR,TS) : *function* : 请求完成后的回调函数（请求成功或失败时均调用，XHR为本次的XMLHttpRequest对象，TS为描述请求类型的字符串）
>>- contentType : *String* : 默认值: "application/x-www-form-urlencoded"。发送信息至服务器时内容编码类型。
>>- context : *Obejct* : 这个对象用于设置 Ajax 相关回调函数的上下文。也就是说，让回调函数内 this 指向这个对象（如果不设定这个参数，那么 this 就指向调用本次 AJAX 请求时传递的 options 参数）。比如指定一个 DOM 元素作为 context 参数，这样就设置了 success 回调函数的上下文为这个 DOM 元素。
>>- success(result,ts) : *function* : 请求成功后的回调函数。参数：由服务器返回，并根据 dataType 参数进行处理后的数据；描述状态的字符串。同理error选项。
>
>### 2. serialize()
>>将表单内容序列化为字符串
>>
>>- das