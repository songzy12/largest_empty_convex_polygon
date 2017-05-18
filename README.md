## Largest Empty Convex Polygon

This is a course project for Computational geometry of Tsinghua University, where we try to implement the method of reporting empty convex polygons from paper [1].

## Report 

* [Read & Edit Link](https://www.overleaf.com/9458081kkgxkngrhchd)
* [Read Only Link](https://www.overleaf.com/read/khbqxnhwbffx)

## Wiki

For algorithm description, project structure, APIs please see: <https://github.com/songzy12/LECP/wiki>

## C++ Style Guide

Google Style Guide: <https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/contents/>

* 文件命名：文件名要全部小写, 可以包含下划线：`my_useful_class.cc`
* 类型命名：类型名称的每个单词首字母均大写, 不包含下划线：`MyExcitingClass`, `MyExcitingEnum`
* 变量命名：变量 (包括函数参数) 和数据成员名一律小写, 单词之间用下划线连接. 类的成员变量以下划线结尾：`a_local_variable`, `a_struct_data_member`, `a_class_data_member_`
* 函数命名：常规函数使用大小写混合, 取值和设值函数则要求与变量名匹配： `MyExcitingFunction()`, `MyExcitingMethod()`, `my_exciting_member_variable()`, `set_my_exciting_member_variable()`

## References

[1] Dobkin, D. P., Edelsbrunner, H., & Overmars, M. H. (1990). Searching for empty convex polygons. Algorithmica, 5(1-4), 561-571.