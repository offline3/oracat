### .pro 实现条件编译

```c++
// c++ 条件编译
#define shapeA
 
 
#if defined(shapeA)
FORMS += \
    formA.ui
#elif defined(shapeB)
FORMS += \
    formB.ui
#endif
```

在pro文件中对应的方法

```
// .pro
 
DEFINES += SHAPE_A
 
#...
 
contains(DEFINES,SHAPE_A){
    FORMS += formA.ui
}
contains(DEFINES,SHAPE_B){
    FORMS += formB.ui
}
```