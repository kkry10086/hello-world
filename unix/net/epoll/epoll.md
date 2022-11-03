## epoll

做法：
1. 创建红黑树
2. 向树上添加需要监听的文件描述符
3. 监听

特点：
没有文件描述符数量的限制
需要监听的文件描述符，已经上树之后不需要再次上树
只返回已经变化的文件描述符

## epollAPI
#include<sys/epoll.h>

1. 创建红黑树：
int epoll_create(int  size);
创建一棵红黑树

返回一个树的句柄（根节点）；

2. 节点上树，节点下树，修改树节点

int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);


3. 监听
int epoll_wait(int epfd,struct epoll_event *events,
		int maxevents,int timeout);

监听树上节点属性变化



## epoll的水平触发和边沿触发

1. 水平触发(EPOLLLT)：电平一直为1/0 就触发
2. 边沿触发(EPOLLET)： 电平由高到低或由低到高的跳变


epoll监听有两种方式：

epoll_wait()监听：

读缓冲区：
```
 水平触发（默认）：读缓冲区只要有数据就会被触发
 
 边沿触发：缓冲区只要有数据到达就触发

```

写缓冲区：
```
 水平触发：写缓冲区可写就会被触发
 
 边沿触发：数据发送就会触发
```

工作时一般使用边沿触发。在写缓冲区，必定是边沿触发，否则写缓冲区太浪费资源了。
而读缓冲区，使用边沿触发可能会有buf的长度不够读取缓冲区所有的数据，但是我们
可以通过循环读取，直到读到的数据的长度小于buf的SIZE就可以停止，这样就可以解决了。而且不用使用非常浪费资源的水平触发。




