iceplayer - Music Player
=========================

* **Author:** gjp1120 <<gjp1120@gmail.com>>, jasy.ice <<jasy.ice@gmail.com>>
* **Source:** [GitHub](https://github.com/gjp1120/iceplayer), [Google Code](https://code.google.com/p/iceplayer)
* **Verison:** 0.1

项目状态
--------
  
  工作中


介绍
----

  因为[原有的iceplayer][googlecode] 是一个好项目，但现在为其增加功能时遇到了麻烦，因为原有代码耦合过度，难以从中分离部分有价值的代码，在这里的项目就是为解决这个问题而诞生的。

  在GitHub的这个项目仅是用于为iceplayer重构代码的，我们可能不会使用过多的原有代码。但会尽力提高iceplayer的可用性和效率。

  [googlecode]: https://code.google.com/p/iceplayer

  
代码要求
--------

###编辑器

VIM:

    tabstop = 4
    textwidth = 87
    expandtab


###代码风格
    BSD

###变量和内存
+ 禁止全局变量，至少要用`static`修饰，为在其他文件中访问提供GET函数
+ 减少固定分配的数组
+ 认真管理内存
+ 保证类型转换正确

###避免污染全局名称空间
+ 标准宏名全部大写，伪装成函数的不遵循此要求
+ 仅内部使用的函数用static


###可移植性
+ 减少代码中警告
+ 尽力优化（但不能破坏可读性）
+ 使用标准的API报告错误，提供调试信息

###头文件
+ 每个文件开头都要有声明，包括GPL和文件功能
+ 每个头文件必须有保证只包含一次的宏

<code>
    #ifndef \_\_NAME\_H</br>
    #define \_\_NAME_H

    //...

    #endif /*__NAME_H*/
</code>

###函数
+ 复杂或有争议的代码要带有注释
+ 对外的函数要有说明，应放置于.h和.c中
+ 不要大批量使用`inline`（会增大调试难度）
+ 未实现和有问题的提供FIXME标记

###国际化
+ 尽量在代码中使用英文的字符串，例如`GtkLabel`中的字符串
+ 将每一个用户能看到的字符串使用`_()`或`N_()`[后者仅用于全局字符常量，例如UIManager所需的]
