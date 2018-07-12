# JavaScript，Html相关的那些事

## 一、JS基本语法

- JS是一种解释性的脚本语言，没有编译的过程，与Python，Matlab等相似
- JS中一切都是Objct（对象）
- 基本数据类型有：number,string,boolean,null,undefined
- 常用对象有：Number,Math,String,Date,Array

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

    