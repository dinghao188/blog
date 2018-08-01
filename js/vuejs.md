# 关于VUE的一些重要知识结构

- ## Vue项目的结构
  - 整个Vue项目有且必须只能有一个根实例,此实例必须有一个挂载点(通过el属性或者mount函数指定)即只能有一个通过如下代码构造出来的实例

        new Vue(
          el,   //指定挂载点,可与mount互相代替.
          router, //路由信息,建议放在一个模块中,结构更清晰(vue-router)
          store,  //状态存储信息,state,mutation,action,getters等(vuex)
          components, //注册到该实例内的组件,只有注册过的组件才能在模板中使用,基本格式为[{name:component},...],注意::name才是最终使用component的有效方式,一般直接{component}这样,这是ES6的新特性,就表示{component:component}
          template, //模板,可有可无,若指定模板则该模板会覆盖挂载点内的原有模板信息
          [render: h=>h(component)],  //效果同上,其中h代表createElement函数,整体意思相当于在挂载点内构造一个component组件,作用与注册component,并在template中添加<component />完全相同

          ...//还有其它的,以后再写
        ).mount() //与el选其一使用

- ## VueRouter中的一些规定
  - router对象只能注入根实例,组件中不能添加路由信息,只能添加router-view
  - 路由可以嵌套,顶级路由路径必须以/开头否则永远匹配不到,子路由没有限制,基本结构如下

        router = new VueRouter({
          routes: [
            {
              path: '/xxx1',
              name: '',可有可无
              component: xxx1
            },
            {
              path: '/xxx2',
              component: xxx2,
              children: [
                {
                  /**
                  * 原则上可以将子路由path设置为以'/'开头,且子路由的path可以设置为与父路由形式同级,并且推荐写成'/'开头,但不推荐写成父子路由形式同级,理由如下:1. 路由匹配是以绝对path为准的,即便写成相对path,生成路由时也会根据父路由信息将其组装成绝对path  2. 父子路由形式同级不利于项目结构的展示
                  */
                  path: '/xxx2/xxxx1',
                  component: xxxx1
                }
                ...
              ]
            }
            ...
          ]
        })

  - 如果有同名的路由信息,写在前面的会被优先匹配,如果匹配到的路由有父路由,则会按照父子关系进行组件的生成和渲染