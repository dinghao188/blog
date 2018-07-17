# JavaScript，Html相关的那些事

## 一、JS基本语法

- JS是一种解释性的脚本语言，没有编译的过程，与Python，Matlab等相似

- 基本数据类型有：object,function,number,string,boolean,null,undefined

- 函数是第一等对象

- 对象是类的实例化结果,类可以被继承。

- 常用内置对象有:Number,Math,String,Date,Array,Global,Object,Function等，它们都是函数对象，也可以叫做类。
- 两个特殊的对象：Object和Function.
    1. Object特殊之处在于Object.prototype是凭空出来的。语法上，所有{}都会被解释为new Object().

    2. Function特殊在__proto__=prototype.语法上所有函数声明都会被解释为new Function().

    3. 以上列出的所有对象，当其作为Function的实例化对象时，其__proto__均指向Function的prototype,但是其本身的prototype仍然指代该类的原型对象，且prototype.--proto--指向Object的prototype。类型扩展时规律相同。

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

## 四、JQuery Ajax操作

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