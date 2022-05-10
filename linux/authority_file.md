文件的权限:
----------(10位)。
0:类型:-/d/|
1-3:rwx:owner
4-6:rwx:group
7-9:rwx:other

umask:---
初始:
文件权限为:666-umask
文件夹权限为:777-umask

修改方式:
chmod [-option] arguments filename
chown arguments filename 
chgrp arguments filename
option : o,g,u,a;
arguments:
---,641;
+ - =


隐藏属性:
i:不能删除，改名，设置链接，无法写入或新增数据，只能看。
a:文件只能增加数据，不能删除/修改数据(log)。
S:当文件修改时，立即写入硬盘。
修改与查看方式:
chattr,lsattr;

特殊权限:
/usr/bin/passwd 权限为:-rwsr-x--x;root:root;
3:s
s指set SUID,简称SUID的特殊权限。
不能用于shell脚本。
限制与功能:
1.SUID权限仅对二进制文件(binary program)有效;
2.执行者对于该程序需要具有x的可执行权限;
3.本权限仅在执行该程序的过程中有效(run-time);
4.执行者将具有该程序拥有者的权限。

用于/etc/shadow;这个文件只有root可读和修改。
但是我们可以使用 /usr/bin/passwd 修改我们的密码？
为何:SUID的使用，第四条，可以让我们使用passwd(/usr/bin/passwd)
来暂时获得root的权限，从而修改/etc/shadow;


6:s
/usr/bin/locate:-rwx--s--x; root:root;
s指set GUID(SGID)，可以针对文件或目录来使用。
一.对文件来说，限制与功能:
1.SGID对二进制程序有效
2.程序执行者对于该程序来说，需具备x的权限
3.执行者在执行过程中将会获得该程序用户组的支持

/usr/bin/locate可以用来查找/var/lib/mlocate/mlocate.db的内容。

mlocate.db的权限:-rw-r----- root root
如果我们是abc且不在root group,那么我们就无法直接来查询
mlocate.db,但是我们可以通过使用locate来暂时获取用户组的权限
来查询mlocate.db的内容。

二.对目录来说，限制与功能:
1.用户若对于此目录具有r与x的权限，该用户能够进入此目录。
2.用户在此目录下的有效用户组(effictive group)将会变成该目录的
  用户组

3.用途:若用户在此目录下具有w的权限，则用户所建立的新文件，该新
文件的用户组与此目录的用户组相同

Sticky Bit:
目前只针对目录有效，对文件已经没有效果了。
SBIT:
1.当用户对于此目录具有w、x权限，即具有写入的权限。
2.当用户在此目录下建立文件或目录时，仅有自己与root才有权利删除文件。

当A对于B的目录具有w、x的权限时，就可以在里面随意删除、更名、移动
他人的文件/目录。而如果将B的目录加入了SBIT的权限选项时，则A只能
对自己的文件或目录操作。而无法操作他人的目录/文件。

eg:/tmp的权限是drwxrwxrwt。任何人都可以在/tmp中建立文件/目录，
并修改。但仅有root与创建者可以删除、更名、移动自己的目录/文件。

查看文件权限时，如果特殊权限是大写，就代表相关的user/group没有
执行权限。







