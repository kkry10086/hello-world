# TCP

## 流程：

1. (socket)创建监听套接字
2. (bind)绑定该套接字
3. (listen)监听该套接字，创建两个链接队列：已完成链接队列，未已完成链接队列。
4. (accept)接收链接请求。从已完成链接队列提取新的链接，创建一个新的链接套接字，
    使用这个已连接套接字和当前这个客户端通信
5. (read/write)收发信息
6. (close)关闭套接字

v

## accept:

**细节：**
<p><font color = 'red'>
tcp的三次握手，第一次握手是通过监听套接字完成的。
剩下的两次握手是通过新创建的套接字来通讯完成的。
</font></p>

**函数：**
int accept(int sockfd,struct sockaddr *addr,socklen_t *addrlen);
参数：
  sockfd:监听套接字
  addr:保存客户端地址信息结构体
  addrlen：结构体的大小的地址

**返回值：**
  success: 返回已连接套接字
  failed: 返回-1，errno is set appropriately




## 一些有用的拓展：

有时候，服务器的sercer SIGINT或者close(socket)，会导致再次开启server时，无法接收客户端的链接。


<h3><font color = "red">!!!非常重要，可以学习!!!</font></h3>


<p>
<strong><font color = "red">
实际上在发生上诉操作时，系统内核不会那么快的回收socket资源。因为内核需要完成TCP的四次挥手来结束这次的链接，因此内核无法那么快的将进程完全杀掉，因为需要进程的信息来完成四次挥手。 
此时，server再次运行就再次绑定了。这次的绑定是允许的。
</font>
</strong>
</p>


<p>
<strong>
<font color = "red">
reason：
  同一个套接字（同一个ip与port）是可以多次绑定的，套接字实质上就是在内存的一个栈。
</font>
</strong>
</p>

<p>
<strong>
<font color = "red">
  此时一旦有一个进程将套接字的状态改变，多个进程共用的栈空间就被修改了状态。
  假设SIGINT或close(socket)，那么内核要遵循TCP的四次挥手来结束链接。
</font>
</strong>
</p>

<p>
<strong>
<font color = "red">
  但是我们这边关闭了，而我们没有发送FIN报文给对方(SIGINT)，对方没有发送FIN报文给我们(socket)，这时我们的链接都存在着，却无法进行通信(无论接收)，只能等待TCP自己关闭，要等待一段时间，这时该socket才能再次使用。
</font>
</strong>
</p>

## 

