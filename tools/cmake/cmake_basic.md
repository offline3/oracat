# CMake

cmake是一个跨平台的工程管理工具。使用cmake管理工程的优势在于：1.跨平台。在window环境下，cmake可以输出vs project文件，可以用MSVC编译构建工程，在linux下，cmake可以输出makefile文件，可以用make工具构建工程；2.在linux环境下，不需要在手动去编写复杂繁琐的makefile文件，通过cmake工具可以使用cmake内置的高级API管理工程。

在学习CMake之前，需要对g++，make有一些基础的了解，这样才能更好的了解cmake一些命令的含义。关于g++，可参考[该文档](https://cloud.tencent.com/developer/article/1394309)



## 基本命令

cmake有很多内置的命令，且命令的拼写是与大小写无关的。cmake的所有命名可以参开[官方文档](https://cmake.org/cmake/help/latest/manual/cmake-commands.7.html)

常见的工程命令有：

- `cmaek_minimum_required`:设置能够使用的cmake最低版本
- `project`:定义工程名称
- `add_executable`:添加给定名称的可执行程序
- `add_subdirectory`:添加构建的子目录

同时，camke也有自己一套脚本命令（条件，循环，赋值）

- if, endif
- elif, endif
- while, endwhile
- foreach, endforeach
- list
- return
- set_property (assign value to variable.)
- message

> cmake 不使用';'来表示语句结束

## 环境变量

环境变量通常用于配制编译，链接，测试选项。cmake定义的环境变量可参考[官方文档](https://cmake.org/cmake/help/latest/manual/cmake-env-variables.7.html)

