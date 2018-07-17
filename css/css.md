# CSS有关的技巧

## 1. *display:table*是一个可以使盒子模型具有类table显示功能的属性

- 与子元素属性*display:table-cell*配合使用，可以使子元素里的内容相对该子元素居中对齐，效果如下

        .parent{
            display:table;
            border:1px solid red;
            width:100%;
            height:200px;
        }
        .son{
            display:son;
            background-color:blue;
        }
        <div class="parent">
            <div class="son>
                <h1>Hello World</h1>
                <p>Do you see this?</p>
            </div>
        </div>
![GitHub Logo](/images/logo.png)
![Example](url)
