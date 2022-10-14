# 实现信号的捕捉

## 1.singal函数的情况：


typedef void (* sighandler_t) (int)

```
这里就是定义类型别名，将一个void (*)(int)一个函数指针起了一个另外的名字为一个sighandler_t。
typedef a b:
此时的 a就是void，而此时的b就是(* sighandler_t)。而后面的(int)就是告诉我们这是一个函数。
```

sighandler_t signal(int signum,sighandler_t handler);
```
函数参数的handler的类型是sighandler_t，所以其是一个函数。
```

## 2.使用signal函数捕捉超时信号


## 3.信号集和信号操作函数

在PCB中有两个非常重要的信号集，一个称之为"阻塞信号集"，另一个是"未决信号集"。这两个信号集都是内核使用**位图机制**实现的。

用户可以设置阻塞信号集，但是不可以设置未决信号集。

sigset_t 构造信号集并设置。然后再注册信号集，注册到当前的进程。


## 4自定义信号集函数

在signal.h文件里面有
其中一个sigemptyset(sigset_t *set);




