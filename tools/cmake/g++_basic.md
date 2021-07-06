# 1.g++简介

g++是GNU开发的C++编译器，是GCC（GNU Compiler Collection）GNU编译器套件的组成部分。另外，gcc是GNU的C编译器。

看官方手册你会发现g++的命令选项真的多如繁星，令人头皮发麻。但是常用的命令选项也就那几个，足以完成日常编译，g++使用起来还是比较简单的！

g++编译器是GCC的一部分，GCC编译工作一般分为四个步骤： （1）预处理（Preprocessing）。由预处理器cpp完成，将.cpp源文件预处理为.i文件。

```javascript
g++  -E  test.cpp  -o  test.i    //生成预处理后的.i文件
```

（2）编译（Compilation）。由编译器cc1plus完成，将.i文件编译为.s的汇编文件。使用`-S`选项，只进行编译而不进行汇编，生成汇编代码。

```javascript
g++ -S test.i -o test.s			//生成汇编.s文件
```

（3）汇编（Assembly）。由汇编器as完成，将.s文件汇编成.o的二进制目标文件。

```javascript
g++  -c  test.s  -o  test.o    //生成二进制.o文件
```

（4）链接（Linking）。由链接器ld，将.o文件连接生成可执行程序。

```javascript
g++ test.o  -o  test.out  	  //生成二进制.out可执行文件 
```

# 2.命令格式

```javascript
gcc [-c|-S|-E] [-std=standard]
    [-g] [-pg] [-Olevel]
    [-Wwarn...] [-pedantic]
    [-Idir...] [-Ldir...]
    [-Dmacro[=defn]...] [-Umacro]
    [-foption...] [-mmachine-option...]
    [-o outfile] [@file] infile...
```

# 3.命令选项

关于g++的命令选项，大家可以参考[g++百度百科](http://baike.baidu.com/link?url=FQvGegKMC9UsRPbdBRSRkto7y-QJuy093kei3dqlVwzghhwZv_i3nD53Xtq16n4_26phqLxD4DKCqnXSQ17Az_)或者[GCC官方手册](https://gcc.gnu.org/onlinedocs/gcc-6.1.0/gcc.pdf)，或者使用`man g++`单独查看g++使用手册。

下面列出常用的命令选项。 

**（1）总体选项**

```bash
-E
	只激活预处理,这个不生成文件,你需要把它重定向到一个输出文件里面。例子用法:   
	gcc -E hello.c > pianoapan.txt   
	gcc -E hello.c | more   
	慢慢看吧,一句`hello word`也要预处理成800行的代码。     
-S   
	只激活预处理和编译，就是指把文件编译成为汇编代码。例子用法： 
	gcc -S hello.c   
	将生成.s的汇编代码，可以用文本编辑器查看。    
-c    
	只激活预处理,编译,和汇编,也就是他只把程序做成obj文件。例子用法:   
	gcc -c hello.c   
	将生成.o的目标文件（object file）。 
-o
	指定目标名称，缺省的时候，gcc/g++编译出来的文件是a.out。例子如下：   
	g++ -o hello.out hello.cpp
	g++ -o hello.asm -S hello.cpp   
```

**（2）目录选项**

```
-I[dir]
	在你是用#include "file"的时候，gcc/g++会先在当前目录查找你所指定的头文件，如果没有找到，会到系统默认的头文件目录找。如果使用-I指定了目录，编译器会先在指定的目录查找，然后再去系统默认头文件目录查找。对于#include <file>，gcc/g++会到-I指定的目录查找，查找不到，然后再到系统默认的头文件目录查找。
-include [file]
	相当于“#include”，用于包含某个代码,简单来说,就是编译某个文件,需要另一个文件的时候,就可以   
	用它设定,功能就相当于在代码中使用#include。例子用法:   
	gcc hello.c -include /root/pianopan.h   
-I-
	就是取消前一个参数的功能,所以一般在-Idir之后使用   
-idirafter [dir]   
	在-I的目录里面查找失败，将到目录dir里面查找。
-iprefix [prefix]，-iwithprefix [dir]
	一般一起使用，当-I的目录查找失败，会到prefix+dir下查找。
-L[dir]   
	编译的时候，指定搜索库的路径。比如你自己的库，可以用它指定目录，不然编译器将只在标准库的
	目录找。这个dir就是目录的名称。
-l[library]    
	指定编译的时使用的库，例子用法   
	gcc -lcurses hello.c   
	使用curses库编译连接，生成程序。  
```

**（3）预处理选项**

```javascript
-Dmacro
	相当于C语言中的#define macro
-Dmacro=defn
	定义宏，相当于C语言中的#define macro defn
-Umacro
	取消宏定义，相当于C语言中的#undef macro
-undef
	取消任何非标准宏的定义，C++标准预定义的宏仍然有效
```

**（4）链接方式选项**

```javascript
-static
	此选项将禁止使用动态库。优点：程序运行不依赖于其他库。缺点：可执行文件比较大。
-shared
	此选项将尽量使用动态库，为默认选项。优点：生成文件比较小。缺点：运行时需要系统提供动态库。
-symbolic
	建立共享目标文件的时候，把引用绑定到全局符号上。对所有无法解析的引用作出警告（除非用连接选项，'-Xlinker -z -Xlinker defs'取代)。注：只有部分系统支持该选项。
-Wl,-Bstatic
	告诉链接器ld只链接静态库，如果只存在动态链接库，则链接器报错。
-Wl,-Bdynamic
	告诉链接器ld优先使用动态链接库，如果只存在静态链接库，则使用静态链接库。
```

**（5）错误与告警选项**

```javascript
-pedantic
	允许发出ANSI/ISO C标准所列出的所有警告
-pedantic-errors
	允许发出ANSI/ISO C标准所列出的错误
-Wall
	一般使用该选项，允许发出GCC能够提供的所有有用的警告。也可以用-W{warning}来标记指定的警告
-Wno-deprecated
	使用C++标准废弃特性不告警
-Werror
	要求GCC将所有的警告当成错误进行处理，在警告发生时中止编译过程。
-Werror={warning}
	将指定警告设置为错误。例如-Werror=return-type，如果函数需要返回值却没有return语句，则编译报错
-w
	关闭所有警告,建议不要使用此项。
```

**（6）调试选项**

```javascript
 -g   
	指示编译器，在编译时，产生调试信息。
-gstabs   
	此选项以stabs格式生成调试信息,但不包括gdb调试信息。 
-gstabs+   
	此选项以stabs格式声称调试信息,并且包含仅供gdb使用的额外调试信息.   
-ggdb    
	此选项将尽可能的生成gdb可以使用的调试信息。
-glevel
	请求生成调试信息，同时用level指出需要多少信息，默认的level值是2。
```

**（7）优化选项**

```javascript
-O0   
-O1   
-O2   
-O3   
	编译器优化选项分为4个级别，-O0表示没有优化，-O1为缺省值，建议使用-O2，-O3优化级别最高。
```

**（8）宏条件编译**

C++中通常使用宏来实现条件编译，如下源文件

```c++
#include <iostream>

int main(int argc, char *argv[])
{
   std::cout << "Hello Compile Flags!" << std::endl;

   // only print if compile flag set
#ifdef EX2
  std::cout << "Hello Compile Flag EX2!" << std::endl;
#endif

#ifdef EX3
  std::cout << "Hello Compile Flag EX3!" << std::endl;
#endif

   return 0;
}
```

当希望定义宏`EX2`进行编译时，可使用

```bash
g++ -o main main.cpp -DEX2
```

执行可执行性文件，对应的输出为

```
Hello Compile Flags!
Hello Compile Flag EX2!
```

**（9）其他选项**

```javascript
-fpic
	编译器生成位置无关目标码（PIC，position-independent code），用于动态链接库，即Linux下的.so文件。通过全局偏移表（GOT，Global Offset Table）访问所有常量地址。程序启动时通过动态加载程序解析GOT条目。如果链接的so文件的GOT大小超过计算机特定的最大大小，则会从链接器收到错误消息，指示-fpic不起作用。这种情况下，请使用-fPIC重新编译
-fPIC
	同-fpic功能一致，生成位置无关目标码，用于生成动态链接库，建议使用该选项，而非-fpic
-v
	显示详细的编译、汇编、连接命令
-pipe
	使用管道代替编译过程中的临时文件,在使用非gnu汇编工具的时候,可能有些问题   
	g++ -pipe -o hello.out hello.cpp
-ansi
	关闭gnu c中与ansi c不兼容的特性，激活ansi c的专有特性(包括禁止一些asm inline typeof关键字,以及
	UNIX,vax等预处理宏。
-fno-asm   
	此选项实现ansi选项功能的一部分，它禁止将asm,inline和typeof用作关键字。   
-fno-strict-prototype
	只对g++起作用,使用这个选项,g++将对不带参数的函数,都认为是没有显式的对参数的个数和类型说明,而不是没有
	参数.而gcc无论是否使用这个参数,都将对没有带参数的函数,认为没有显式说明的类型。
-fthis-is-varialble   
	就是向传统c++看齐,可以使用this当一般变量使用。
-fcond-mismatch   
	允许条件表达式的第二和第三参数类型不匹配,表达式的值将为void类型。
-funsigned-char   
-fno-signed-char   
-fsigned-char   
-fno-unsigned-char   
	这四个参数是对char类型进行设置,决定将char类型设置成unsigned char(前两个参数)或者signed char(后
	两个参数)。
-fpermissive
	把代码的语法错误作为警告，并继续编译。请谨慎使用该选项。
-imacros file   
	将file文件的宏,扩展到gcc/g++的输入文件,宏定义本身并不出现在输入文件中     
-nostdinc   
	使编译器不在系统缺省的头文件目录里面找头文件,一般和-I联合使用,明确限定头文件的位置。 
-nostdin C++
	规定不在g++指定的标准路经中搜索,但仍在其他路径中搜索,此选项在创建libg++库使用。
-C
	在预处理的时候,不删除注释信息,一般和-E使用,有时候分析程序，用这个很方便的。 
-m
	生成与具体CPU相关的程序。
-mtune=cpu-type 
	为指定类型的CPU生成代码。cpu-type 可以是：i386，i486，i586，pentium，i686，pentium4 等等。
-m32
-m64
	生成32bits程序或64bits程序
-mmmx
-msse
-msse2
-mno-mmx
-mno-sse
-mno-sse2
	使用或者不使用MMX，SSE，SSE2指令。
-M
	生成文件依赖的信息，包含目标文件所依赖的所有源文件。你可以用gcc -M hello.c来测试一下，很简单。   
-MM   
	和上面的那个一样，但是它将忽略由#include造成的依赖关系。   
-MD
	和-M相同，但是输出将导入到.d的文件里面。
-MMD   
	和-MM相同，但是输出将导入到.d的文件里面。
-Wa,option   
	此选项传递option给汇编程序；如果option中间有逗号,就将option分成多个选项，然后传递给会汇编程序。 
-Wl.option   
	此选项传递option给连接程序;如果option中间有逗号,就将option分成多个选项,然后传递给会连接程序。
-x language filename   
	设定文件所使用的语言,使后缀名无效,对以后的多个有效.也就是根据约定C语言的后缀名称是.c的，而C++的后缀
	名是.C或者.cpp。如果你很个性，决定你的C代码文件的后缀名是.pig，那你就要用这个参数,这个参数对他后面
	的文件名都起作用，除非到了下一个参数的使用。可以使用的参数有下面的这些：
	c,objective-c,c-header,c++,cpp-output,assembler,assembler-with-cpp。   
	看到英文，应该可以理解的。例子用法:   
	gcc -x c hello.pig
-x none filename
	关掉上一个选项，也就是让gcc根据文件名后缀，自动识别文件类型，例子用法:   
	gcc -x c hello.pig -x none hello2.c
```

# 4.FAQ

## 4.1编译选项疑问

### 4.1.1-Wunknown-pragmas和-Wno-format -pg

**（1）-Wunknown-pragmas**

```javascript
Warn when a #pragma directive is encountered that is not understood by GCC. If this 
command-line option is used, warnings are even issued for unknown pragmas in system 
header files. This is not the case if the warnings are only enabled by the ‘-Wall’ 
command-line option.
```

遇到GCC无法识别的编译指导指令，发出警告。在使用了-Wall选项时，就不需要使用该命令选项了。

**（2）-Wno-pragmas**

```javascript
Do not warn about misuses of pragmas, such as incorrect parameters, invalid
syntax, or conflicts between pragmas. See also '-Wunknown-pragmas'.
```

遇到GCC无法识别的编译指导指令，不发出警告。

**-pg作用：**编译的过程中加入额外的代码， 供性能分析工具gprof剖析程序的耗时情况。

\##4.2链接注意事项 ###4.2.1指定静态与动态的链接方式 g++链接库时，默认优先链接动态链接库。静态库与动态库混合链接时，有如下两种方法： （1）静态链接库使用绝对路径，动态链接库使用-l。以boost库为例，如果我们要使用静态库则可书写如下：

```javascript
 g++ main.cpp -pthread /usr/lib64/libboost_thread.a /usr/lib64/libboost_system.a
```

（2）使用`-Wl,-Bstatic`告诉链接器`ld`链接静态库，不存在静态库，则`ld`报错，只存在动态链接库也报错。使用`-Wl,-Bdynamic`告诉链接器**优先**使用动态链接库，如果只存在静态库，则链接静态库，不报错。示例如下：

```javascript
g++  main.cpp -Wl,-Bstatic -lboost_system -lboost_thread -Wl,-Bdynamic
```

**注意：** （1）命令末尾`-Wl,-Bdynamic`，作用是告诉链接器，后续系统库的链接默认使用动态链接，否则会出现找不到系统库的错误，诸如：

```javascript
/usr/bin/ld: cannot find -lgcc_s
collect2: ld returned 1 exit status
```

（2）链接时，库要放在目标文件的后面，否则会报"undefined reference to: xxx"错误。具体参见gcc手册的如下描述：

```javascript
the linker searches and processes libraries and object files in the order they are 
specified. Thus, `foo.o -lz bar.o' searches library `z' after file foo.o but before 
bar.o. If bar.o refers to functions in `z', those functions may not be loaded.
```

------

# 参考文献

[1] [gcc及其选项详解](http://blog.chinaunix.net/uid-25119314-id-224398.html) 

[2] [GCC官方手册](https://gcc.gnu.org/onlinedocs/gcc-6.1.0/gcc.pdf) 

[3] [gcc编译选项](http://www.cnblogs.com/fengbeihong/p/3641384.html)

[4] [gcc/g++ 静态动态库混链接](http://blog.csdn.net/wangxvfeng101/article/details/15336955) 

[5] [折腾gcc/g++链接时.o文件及库的顺序问题](http://blog.csdn.net/imilli/article/details/51454236)

[6] [g++参数介绍](http://www.cnblogs.com/lidan/archive/2011/05/25/2239517.html)

[7] [gcc cannot find cc1plus](https://stackoverflow.com/questions/36353302/gcc-cannot-find-cc1plus?utm_medium=organic&utm_source=google_rich_qa&utm_campaign=google_rich_qa) 

[8] [GNU g++常用编译选项用法](https://blog.csdn.net/zxy_cs/article/details/6901737) 

[9] [-fpic 与-fPIC的区别](https://blog.csdn.net/xiangguiwang/article/details/81939237)



