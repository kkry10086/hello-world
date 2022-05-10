查找文件:

一、whereis:只找系统中特定目录下面的文件。
whereis [-bmsu] 文件或目录名;
l:可以列出whereis会去查询的几个主要目录;
b:只找binary(二进制)格式的文件;
m:只找在说明文件(manual)路径下的文件;
s:只找source源文件;
u:查找不在上述三个项目当中的其它特殊文件。

whereis 主要针对/bin,/sbin下面的执行文件,
/usr/share/man下面的man page文件，以及其他的特殊目录。


二、locate:利用数据库来查找文件名。
locate [-ir] keyword
i: 忽略大小写差异;
c: 不输出文件名，仅计算找到的文件的数量;
l: 仅输出几行，例如 -l 6;
S: 输出locate所使用的数据库文件的相关信息，包括该数据库
   记录的文件/目录数量等;
r: 后面可接正则表达式的显示方式。

locate寻找的数据是由已建立的数据库 /var/lib/mlocate里面
的数据所查找到的。所以不用在硬盘当中读取数据，速度就比较快。
但是数据库并不是实时更新的，而是隔一段时间更新一次数据。
那么，你刚创建的文件，就无法在更新之前查找到。
手动更新数据库的方法:键入[ updatedb ]就可以了。
updatedb 命令可以去读取/etc/updatedb.conf这个配置文件的设置，
然后再去硬盘里面进行查找文件名的操作，最后就更新整个数据库文件。
updatedb:根据/etc/updatedb.conf 的设置去查找系统硬盘内的文件，
         并跟新/var/lib/mlocate内的数据库文件。


locate:根据/var/lib/mlocate内的数据库记录，找出用户所输入关键词
       的文件名。



三、find:
find [PATH] [option] [action]
选项与参数:
1.与时间相关的选项: mtime,atime,ctime;
以mtime为例:
-mtime n    n为数字,意义为在n天之前的[那一天之内]内修改过内容的文件。
-mtime +n   列出在n天之前(不含n本身)被修改过的内容。
-mtime -n   列出在n天之内(包含n本身)被修改过的内功。
-newer file: file为存在的文件，列出比file更新的文件。

2.与使用者或用户组有关的参数:
-uid n: n为数字，这个数字是使用者的账号ID,以即UID，这个UID是记录
        在/etc/passwd里面。

-gid n: n为数字，这个数字是用户组名称ID,以即GID，这个GID是记录
        在/etc/group里面。

-user name: name为使用者的账号的名称;
-group name:name 为用户组名称;
-nouser : 查找的文件的拥有者不在/etc/passwd中;
-nogroup :查找的文件的拥有用户组不在/etc/group的文件;
当你安装某 个软件时，很可能该软件属性当中并没有文件拥有者，
这是可能的。 这时就可以用这个来查找。
或者当你将某个用户删除时，那么该用户的文件就会变成无主的文件。此时
就可以用nouser,nogroup来将他们找出来。


3.与文件权限及名称相关的参数:
-name filename:查找文件名称为filename的文件;
-size [+-]size:查找出比size还要大(+)或小(-)的文件。这个size的规格：
               c:bytes;k:1024bytes;
-type TYPE:查找文件类型为TYPE的，类型主要有:
           一般正规文件(f),设备文件(b,c),目录(d),链接文件(l),
	   socket(s),FIFO(p)的属性。


-perm mode :查找文件权限【刚好等于】mode的文件，mode是四个数字such as:7744
-perm -mode:查找文件权限【必须要全部囊括mode的权限】的文件，我们要查找
            权限0744的文件，那么每一个数字对应的权限大于，等于0744的文件就会
	    被找出来。

-perm /mode:查找文件权限【包含任一mode的权限】的文件，其中任一mode指
            四个权限数字中的任一一个权限。

-exec command:command为其他命令，-exec后面可接额外的命令来处理查找到的结果。
-print:将结果打印到屏幕上，默认操作。
e.g.:
find /usr/bin /usr/sbin -perm /7000 -exec ls -l {}\;

{}代表的是由find找到的内容，find的结果会放到{}里面;
-exec ... \;：代表find额外操作的开始(exec)到结束(\;);由于;具有特殊意义，
              因此使用\来转义为;。
