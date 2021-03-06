# Webpack的诞生，理念，以及其主要应用场景

>## 介绍
>- 前端项目规模的不断扩大催生了一系列前端模块化开发技术，和包管理工具的发展。Webpack就是一款能够兼容各种模块化标准的依赖管理和项目打包的工具，与npm不同的是webpack在前端项目打包中绝对的优势，如将html,css,图片等静态资源当作模块导入项目。

>## JS模块化编程
>- 原生的JavaScript并不支持模块化编程，至少在ECMAScript2015标准之前是不支持的，但随着项目规模的扩大，模块化是必然的，于是乎社区的开发者们利用语言现有的特性制定了一些模块化的规范。
>- 模块的概念
>   - 内部变量不会对外界变量造成污染的，具有独立功能的，可以被组织引用的代码集合
>   - 一个模块就是一个单独的可执行的JS文件(多个模块可以放在同一个JS文件中，但这会使模块的概念变得非常模糊)，模块之间会层层依赖，甚至是相互依赖，当模块数目增大的时候，模块的管理和引用将会变的非常复杂。这就是打包工具出现的前提和必要条件，有点类似于java中的maven和graddle之类的自动进行打包和依赖管理的工具，虽然Java是基于jar包进行组织，但是现在js项目的规模根本无法跟java项目相提并论，不过随着需求的发展，JS项目规模的增长，基于包进行依赖管理的思想是必然要被应用到JS项目中的，而其根基仍然是模块。
>- 模块化的意义(现在知道的，以后再添加)
>   - 将大的项目拆分成一个个小的功能独立的模块，有利于项目的维护和扩展
>   - 避免因项目规模扩大而必然导致的变量污染现象，虽然以前可以用**立即执行函数**封闭变量，但是这种方式可读性较差，且很难理清楚模块与模块之间的关系

>## 现有的常用模块化标准
>- CommonJS标准
>   - 同步加载,即加载完指定模块之后才会往下执行,如下所示,只有按照一定规则加载somemodule.js成功或失败之后才会执行TODO之后的语句：(由于其同步加载的特性，注定它不能在浏览器上得到广泛运用)
>
>           require('./somemodule.js')
>           //TODO
>   - 模块需要通过module.exports对外暴露接口
>   - 经典的实现有Node.js平台实现的的模块结构
>
>- AMD标准
>   - 异步加载，模块加载时可以执行其他与引入模块无关的过程，并可以通过回调函数来执行那些与引入模块相关的过程，如下所示：
>
>           define('ModuleName',['module1.js','module2.js',...],callback)
>           //TODO
>   - 通过define函数构造和引用模块
>   - 经典实现有RequireJS,Curl等
>
>- ES2015标准，太多了，不介绍了，上网查吧，未来的标准(官方标准不必须的吗)

>## [webpack原理及工作流程](https://segmentfault.com/a/1190000015088834)
>Webpack 的运行流程是一个串行的过程，从启动到结束会依次执行以下流程：
>
>>1. 初始化参数：从配置文件和 Shell 语句中读取与合并参数，得出最终的参数；
开始编译：用上一步得到的参数初始化 Compiler 对象，加载所有配置的插件，执行对象的 run 方法开始执行编译；
>>2. 确定入口：根据配置中的 entry 找出所有的入口文件；
>>3. 编译模块：从入口文件出发，调用所有配置的 Loader 对模块进行翻译，再找出该模块依赖的模块，再递归本步骤直到所有入口依赖的文件都经过了本步骤的处理；
>>4. 完成模块编译：在经过第4步使用 Loader 翻译完所有模块后，得到了每个模块被翻译后的最终内容以及它们之间的依赖关系；
>>5. 输出资源：根据入口和模块之间的依赖关系，组装成一个个包含多个模块的 Chunk，再把每个 Chunk 转换成一个单独的文件加入到输出列表，这步是可以修改输出内容的最后机会；
输出完成：在确定好输出内容后，根据配置确定输出的路径和文件名，把文件内容写入到文件系统。
>
>在以上过程中，Webpack 会在特定的时间点广播出特定的事件，插件在监听到感兴趣的事件后会执行特定的逻辑，并且插件可以调用 Webpack 提供的 API 改变 Webpack 的运行结果。
>
>**我个人感觉有点像C语言程序编译步骤：预处理、汇编、链接、汇编编译、生成可执行程序。**

>## webpack注意事项
>>1. 正常情况下所有入口chunk都会被打包成一个文件，该文件中包含入口chunk需要的所有模块，入口chunk之间不共享任何代码，也不会对window对象产生任何影响。
>>2. 动态导入或者利用插件使代码分离时都会对window对象插件产生影响。