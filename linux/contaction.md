compression:
压缩后与未压缩的文件所占磁盘空间的大小的比值，称为压缩比。

8.2  Linux常见的压缩命令：
   压缩文件的扩展名大多是：*.tar,*.tar.gz,*.tgz,*.gz,*.Z,*.bz2,*.xz。
   Linux支持的压缩命令非常多，而且不同的命令所用的压缩技术并不相同，当然，
   彼此之间可能就无法互通压缩/解压缩文件。所以扩展名可以让我们知道其所用
   的技术。

*.Z		compress程序压缩的文件
*.zip		zip程序压缩的文件
*.gz		gzip程序压缩的文件
*.bz2		bzip2程序压缩的文件
*.xz		xz程序压缩的文件
*.tar		tar程序打包的文件，并没有压缩过
*.tar.gz	tar程序打包的文件，并且经过gzip的压缩
*.tar.bz2	tar程序打包的文件，并且经过bzip2的压缩
*.tar.xz	tar程序打包的文件，并且经过xz的压缩

    compress已经不流行了，现在已经用gzip取代了它。xz是最新的。不过，这些
    命令通常仅能针对一个文件来压缩与解压缩，如此一来，每一次压缩与解压缩
    都要一大堆的命令。所以就有了打包软件 tar；
    tar可以将很多文件打包成一个文件，甚至目录也可以这么做。不过，单纯的tar
    仅是打包而已，即将很多文件结合为一个文件，它并没有提供压缩的功能，后来，
    GNU计划中，将整个tar与压缩功能结合在一起。

   8.2.1 gzip,zcat/zmore/zless/zgrep
   （man 可以看）
   使用gzip进行压缩时，在默认的状态下原本的文件会被压缩成.gz后缀文件，源文件
   就不在存在了。
   而且使用gzip压缩的文件在windows系统中，竟然可以被Winrar和7Zip软件解压缩。
   zcat fname.gz
   zcat/zmore/zless读取压缩后的文件，屏幕上会显示解压缩后的原始文件内容。


   8.2.2 bzip2.bzcat/bzmore/bzless/bzgrep
   gzip是为了替换compress并提供更好的压缩比而成立的，bzip2则是为了替换gzip
   并提供更佳的压缩比而成立的。bizp2的压缩比gzip要好，且用法几乎与gzip相同。
   压缩比越好，花的时间越久。
   bzip2 [-cdkzv#] fname （去man看）
   bzcat fname.bz2
   
   
   8.2.3 xz,xzcat/xzmore/xzless/xzgrep
   bzip2已经具有很棒的压缩比了，不过xz的压缩比更好。它的用法也跟gzip/bzip2
   几乎一模一样。同样，压缩比越好，花的时间越久。




8.3打包命令：tar
   前面的命令大多是对单一文件进行压缩，虽然也能够对文件压缩，但是其本质是对
   目录内的所有文件【分别】进行压缩。而Windows就有Winrar这一类的压缩软件
   来将好多数据包成一个文件的样式。
   这种将多个文件或目录打包成一个大文件的命令功能，就叫打包命令。Linux最
   出名的就是tar。tar可以将多个目录或文件打包成一个大文件，同时还可以通过
   gzip,bzip2,xz的支持，将该文件同时进行压缩。而且，由于tar使用太广泛，
   windows的winrar也支持.tar.gz文件名的解压缩。
   tar的选项与参数非常多；最好自己去看man
   tar [-z|-j|-J] [cv] [-f 带建立的新文件名] filename 打包与压缩
   tar [-z|-j|-J] [tv] [-f 既有的tar文件名]          查看文件名
   tar [-z|-j|-J] [xv] [-f 既有的tar文件名] [-C 目录] 解压缩
   -c ：建立打包文件，可搭配-v查看过程中被打包的文件名；
   -t ：查看打包文件的内容含有那些文件名，重点在查看文件名；
   -x ：解包或解压缩的功能，可以搭配-C在特定目录解压，特别留意-c，-t
        -x不可同时出现在一串命令行中；
   -z ：通过gzip的支持进行压缩、解压缩：此时文件名为*.tar.gz；
   -j ：通过bzip2的支持进行压缩、解压缩；此时文件名为*.tar.bz2；
   -J ：通过xz的支持进行压缩、解压缩；此时文件名为*.tar.xz；
   -v ：在压缩/解压缩的过程中，将正在处理的文件名显示出来；
   it is very important
   -f filename： -f后面要立刻接要被处理的文件名；
   
   -C 目录： 用在解压缩，若要在特定目录解压缩，就可以使用这个选项；
   -P ：保留绝对路径，亦即允许备份数据中含有根目录存在之意；
   -p ：保留备份数据的原本权限与属性，常用于备份[-c]重要的配置文件
   用bzip2的方式来举例
   tar -jcv -f fname.tar.bz2 要被压缩的文件名或目录名；
   tar -jtv -f fname.tar.bz2 ；
   tar -jxv -f fname.tar.bz2 -C 欲解压缩的目录名；

   tar最好用来备份一些重要的数据，例如/etc等。要加-p，保存好这些文件
   原本的权限与属性。-P最好不要加，因为一旦解压，那些文件的路径就会
   回覆掉现在的同名文件。
   
   
   仅解开单一文件的方法：
   -t能查看压缩包的文件dabao.tar.xz ，找到目标文件；【fname】
   假设用xz：
   然后：tar -xJv -f 被打包的文件.tar.xz fname
   
   
   打包某目录但不含该目录下的某些文件的做法：
   可以使用--exinclude，意思是不包含。
   tar -jcv -f /root/system.tar.bz2 --exinclude=/root/etc* \
   --exclude=/root/system.tar.bz2 /etc /root
   第一个exinclude指不要打包/root/etc*
   第二个exinclude指不要打包/root/system.tar.bz2自己。
   
  
   仅备份比某个时刻要新的文件：
   --newer-mtime：仅输入mtime
   --newer：输入mtime与ctime
   example：tar -jvc -f fname.tar.bz2 --newer-time "yyyy/MM/dd" /etc/*


   tarfile and tarball:
   仅打包：tarfile
   打包并支持压缩：tarball


   特殊应用：利用管道与数据流
   通过标准输入输出的数据流重定向，以及管道命令，将待处理文件一边打包一边
   解压缩到目标目录；
   tar -cvf - /etc|tar -xvf -
   两个-分别是standard output,standard input;



解压后的SELinux的问题：
当我们需要将我们备份的数据恢复到原本的系统时，那么要注意SELinux的问题；例如：
在/etc的文件，SELinux是比较特别的详细权限设置。而此时，SELinux的权限问题
可能让你的系统无法读写某些配置文件内容，导致影响到系统的正常使用。
例如/etc/passwd在还原后，由于SELinux的类型被修改了，导致系统的登陆程序无法
顺利读取它，因此无法登陆。一般进入单人维护模式。

解决方式：（建议第二和第三）
   1.通过各种可行的恢复方式登陆系统，然后修改/etc/selinux/config文件，
     将SELinux改成permissive模式，重新启动后系统就正常了；
   2.在第一次恢复系统后，不要立即重启，先使用restorecon -Rv /etc自动恢复
     SELinux的类型即可；
   3.通过各种可行的恢复方式登陆系统，建立/.autorelabel文件，重新启动后
     系统会自动修复SELinux的类型，并且会再次重新启动，之后就正常了。
   
8.4.1 XFS文件系统备份xfsdump：
   除了可以进行文件系统的完整备份（full backup），还可以进行增量备份（Incremental
   backup）。实现增量备份的方法是差异比较。
   第一次备份一定是完整备份，在xfsdump中被定义为level 0；而之后的备份就可以是
   增量备份了。
   限制：
        .xfsdump不支持没有挂载的文件系统备份，所以只能备份已挂载的文件系统。
	.xfsdump必须使用root的权限才能操作。
	.xfsdump只能备份xfs文件系统。
	.xfsdump备份下来的数据只能让xfsrestore解析。
	.xfsdump是通过文件系统的UUID来辨别各备份文件，因此不能备份两个具有相同
	 UUID的文件系统。

   xfsdump [-L S label] [-M M label] [-l #] [-f 备份文件] 待备份数据
   xfsdump -I
   
   -L　：xfsdump 会记录每次备份的session标头，这里可以填写对此文件系统的建议说明。
   -M　：xfsdump 可以记录存储媒介的标头，这里可以填写此媒介的建议说明。
   -l　：指定等级（0-9），默认0，即完整备份，其他就是增量备份。
   -f　：指定生成的文件。
   -I　：从/var/lib/xfsdump/inventory列出目前备份的信息状态。



   8.4.2 文件系统还原：xfsrestore：
   查看备用文件：xfsrestore -I
   1.单一文件全系统恢复：xfsdump [-f 备份文件] [-L S label] [-s] 待恢复目录
   2.通过增量备份文件来恢复系统：xfsdump [-f 备份文件] -r 待恢复目录
   3.进入交互模式：xfsdump [-f 备份文件] -i 待恢复目录
   -s ： 需要接特定目录，亦即恢复某一个文件或目录。
   恢复增量备份数据：第一条。
   仅还原部分文件的xfsrestore交互模式：第三条；



8.5 光盘写入工具：
   磁带：容量高，存储时限长，挺耐摔。所以在大容量存储中，还是很多人用的。
   dvd现在被usb取代了，但还是可以学一学。

   8.5.1 mkisofs ：建立镜像文件
   制作一般数据光盘镜像文件：
   mkisofs [-o 镜像文件] [-Jrv] [-V vol] [-m file] 待备份文件...\
   >-graft-point isodir=systemdir ...
   -o：后面接你想要产生的镜像文件。
   -J：产生较兼容Windows的文件名结构，可增加文件名长度到64个unicode字符。
   -r：通过Rock Ridge 产生支持Unix/Linux的文件数据，可记录较多的数据（如
       UID/GID等）。
   -v：显示创建iso文件的过程。
   -V：建立Volume,有点像Windows在文件资源管理器内看到的cd卷标。
   -m file：-m为(exclude)排除文件的意思,后面的文件不备份到镜像文件中。
   -graft-point isodir=systemdir：有转嫁或移嫁的意思。其实，不加这个，在镜像
       文件中所有文件都放在一起，没有其他的分类。有了的话，镜像文件就会有目录。



    制作、修改可启动光盘镜像文件系统：