## select函数


```
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int select(int nfds, fd_set *readfds, fd_set *writefds,
		fd_set *exceptfds, struct timeval *timeout);
```

功能：监听多个文件描述符的属性变化（读写缓冲区的变化）

## arguments
nfds：最大文件描述符+1(遍历所有文件描述符获得最大的文件描述符）。
readfds: 需要监听读属性变化的文件描述符集合
writefds: 需要监听写属性变化的文件描述符集合
exceptfds: 需要监听异常属性变化的文件描述符集合 
timeout: 多久监听一次，超时时间；NULL：永久监听；>0：超时时间;=0:立即饭返回。

## return value
on success:
1. 返回变化的文件描述符的个数
2. 改变了的文件描述符的集合会覆盖原本的集合





## select的优缺点
1. 优点：
   跨平台，windows和linux都可以使用
2. 缺点：
   有1024文件描述符限制
   每次重新监听都需要将监听的文件描述符集合从用户态拷贝至内核态
   大量并发，少量活跃，效率低（指遍历大量的文件描述符，却不一定都是有用的，也不一定都是已经被改变了的） -- 无解的缺陷







