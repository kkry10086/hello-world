我们的程序想要运行，需要三样东西：
1.  硬件：　　执行程序且呈现的硬件．
2.　内核管理：操作系统的内核可以支持这个芯片组，当然还需要提供芯片的驱动程序．
3.　应用程序：我们要执行命令．

　　　我们的程序要让内核（kernel）的管理工作来让硬件执行，可是，我们是如何让内核工作
　　　的？我们可以通过shell将我们输入的命令与内核沟通，让内核可以控制硬件来正确无误
　　　地工作．
　
　　　shell意思为壳，意义是覆盖在内核之上的外壳，在最外层．
　　　操作系统其实是一组软件，由于这组软件在控制整个硬件与管理系统的活动监测，如果
　　　这组软件能被用户随意操作，若用户应用不当，将会使得整个系统崩溃．
　　　但是我们总是需要让用户使用操作系统，所以就有了在操作系统上面发展的应用程序．
　　　这样用户就不会可以通过应用程序来指挥内核，让内核完成我们所需要的硬件任务．
      shell的功能只是提供用户使用操作系统的一个界面，可以执行其他的命令，例如
      mk,rm,man,vim等．

　
10.1.2为何学习shell?几乎所有的linux发行版使用的bash(shell的一种)都是一样的．
　　　而像XWindow之类的工具，在某些时候，例如升级或是使用其他程序管理模块时，会造成
　　　设置上的困扰．

　　　远程管理：
　　　此外，Linux的管理常常需要通过远程联机，此时命令行模式传输速度一定比较快，而且
　　　较不容易出现掉线或是信息外流的问题．

　　　
　　　Linux的任督二脉：shell
      良好的shell程序编写对于管理主机是一定需要的．


　　　10.1.3　系统的合法shell与/etc/shells功能：
　　　linux使用的一种版本的shell称为［Bourne Again SHell］bash.
      /etc/shells里面就有数种我们可以使用的shells,包括/bin/sh.
      这个文件的意义：系统的某些服务在运行过程中，会去检查用户能够使用的shells,而
      这些shell的查询就是借由/etc/shells这个文件．
　　　某些FTP网站回去检查用户可用的shell,而如果你不想要让这些用户使用FTP以外的
　　　主机资源时，可能会给予该用户一些怪怪的shell，让用户无法以其他服务登录主机．
　　　此时，你就会将该shell类型写入/etc/shells中．

　　　我们用户会使用那个shell来使用呢？这好似可以通过/etc/passwd这个文件每个
　　　用户的最后来得到．


     10.1.4 Bash shell 的功能：
     history：
     能够记录你使用过的命令，这些命令一般记录在使用者的家目录的.bash_history里面．
     不过，当前登录的命令都放置在内存中，只有当你注销账户后，才会写入到.bash_histor
     y里面．

　　　命令与文件补全功能：[TAB]

      命令别名设置功能：(alias)
      例如：alias ll='ls -al'
      
      任务管理，前台，后台控制：（job control,foreground,background）

      程序化脚本（shell scripts）：
      shell scripts可以将我们平时管理系统常需要执行的连续命令写成一个文件，该文件
      并且可以通过交互式的方式来进行主机的检工作，也可借由shell提供的环境变量及相关
      命令来进行设计．

　　　
　　　通配符：（Wildcard）
      除了完整的字符串，还支持通配符帮助用户查询与命令执行．
      
　　　　
　　　10.1.5　查询命令是否为Bash shell 的内置命令：　type
     　example：type [-tpa] name
     -t　：当加入时，将name以下面这些字眼显示出它的意义:
           file：外部命令
	   alias：该命令为其他命令的别名
	   builtin：该命令为bash的内置命令
     　　　
     -p　：如果后面接的name为外部命令时，才会显示完整的文件名
     -a　：会由PATH变量定义的路径中，将所有含name的命令都列出来，包括alias

　　　
      10.1.6命令的执行与快速编辑按钮：
      ctrl+u/k向前/后删除命令行．
      ctrl+a/e光标移动到开始/结束位置．



10.2shell 的变量功能：
　　　
　　　1.变量的可变性与方便性
　　　2.影响bash环境操作的变量
　　　　例如：PATH,所有的命令就是通过它来查找的，并使用的．
　　　3.脚本程序设计：
　　　　大型脚本中，变量可以保存一些需要经常使用或者修改的数据，那么就可以减少
　　　　shell scripts的修改了．

      10.2.2 变量的使用与设置：echo，变量设置规则，unset
      变量的设置与规则：
      用=来链接
      等号两边不能直接接空格
      变量名称只能是英文与数字，且开头只能是英文
      变量的内容若有空格，需要使用""包住
      只有双引号里面的$才有使用变量的含有，单引号没有．
      反单引号也有与$相似的功能，只有命令的功能
      export 可以将变量转变为环境变量：export name
      取消变量的方法为使用unset: ［unset 变量名称］
      进入内核模块：
      cd /lib/modules/`uname -r`/kernel
      cd /lib/modules/$(uname -r)/kernel


      10.2.3 环境变量的功能：
      使用env/export来查看我们有多少环境变量．
      结果中的变量含义：
      HOME　：用户的根目录．
      SHELL　：我们使用的shell是哪个程序
      HISTSIZE　：history记录的命令的条数由这个来决定
      MAIL　：邮箱文件读取时，使用到的变量名．
      PATH　：执行文件查找的路径
      LANG　：语系数据，
      RANDOM　：随机数的变量，现在的linux都有随机数生成器，在/dev/random这个文件．
      　　　　　
      用set观察所有变量：
      bash不只有环境变量，还有一些与bash操作界面有关的变量，以及用户自定义的变量。
      基本上，前两种变量设置为大写字母，一般为系统内定需要的变量。
      
      PS1：（提示字符的设置）
      PS1是命令提示字符，当你使用bash时，每一行前面的提示user，hostname，workspace
      等等，就可以用这个来设置。
      \d:显示日期
      \H:完整的主机名
      \h:仅取主机名在第一个小数点之前的名字
      \t:显示时间，24小时制
      \T:显示时间，12小时制
      \A:显示时间，24小时制，没有秒
      \@:显示时间，12小时制，am/pm
      \u:当前用户的账号名称
      \v:BASH的版本信息
      \w:显示完整工作目录名称
      \W:利用basename函数获得工作目录名称，仅会列出最后一个目录名
      \#:执行第几个命令
      \$:提示字符，如果是root就是#，否则是$
      
      $:（关于本shell的PID）
      $是shell的PID的变量，可以通过echo $$得到
      
      ？：（关于上个命令的返回值）
      当我们执行某个命令后，这些命令都会返回一个执行后的代码。一般来说，成功了，
      就是0，其他的情况，非0.
      
      OSTYPE,HOSTTYPE,MACHTYPE（主机硬件与内核的等级）
      
      export：（自定义变量转化为环境变量）
      环境变量与自定义变量的差异在于【该变量是否会被子进程所继续引用】。
      bash是一个独立的进程，这个进程的识别使用的是进程标识符，也就是PID。
      而你在这个bash下执行的任何命令都是有这个bash所衍生出来的，那些被执行
      的命令就被成为子进程。
      子进程仅会继承父进程的环境变量，子进程不会继承父进程的自定义变量。
      export就可以将自定义变量转化为环境变量。
      本质上是共享自己的变量设置给后来调用的文件或其他进程。例如，使用主文件
      调用其他附属文件时，可以用export将变量的设置只在主文件做一次。
      export name
      只使用export，择类似于env


     10.2.4影响显示结果的语系变量（locale）
     系统默认的语系定义在/etc/locale.conf
     
     10.2.5 变量的有效范围
     为何环境变量的数据可以被子进程所引用？
     。当启动一个shell，操作系统会分配一个内存区域给shell使用，此内存中的变量可以
       让子进程使用
     。若在父进程利用export的功能，可以让自定义变量的内容写到上述的内存区域当中
     。当加载另一个shell时（启动子进程），子shell可以将父shell的环境变量所在的内
       存区域导入自己的环境变量区块当中。


     10.2.6 变量键盘的读取、数组与声明：read、array、declare
       1.read:
         要读取来自键盘输入的变量，用read命令。最常见与shell scripts的编写当中。
	 这个命令可以与用户交互。
	 read [-pt] variable
	 -p ：后面接提示字符（提示语句将会被显示出来）
	 -t ：后面可以接等待的秒数
	 
       2.declare,typeset
          declare或typeset是一样的功能，就是声明变量的类型．
	  decleare [-aixr] variable
	  -a　：将后面名为variable的变量定义为array类型
	  -i　：将后面名为variable的变量定义为integer类型
	  -x　：用法与export一样，就是将后面的variable变为环境变量
	  -r　：将变量设置成为readonly类型，该变量不可被改变内容，也不能unset．
	  　　　也不能修改readonly的类型，只有注销再登陆才能恢复．

          important:
	  1.变量类型默认是字符串，所以整形是要-i来指定变量类型;
	  2.bash环境中的数值计算，默认最多仅能到整数形态，所以1/3结果是0；
	  　argument(参数)前面变为+变为取消．
	  
       3.array（变量类型）
       数组的设置方式：
       var[index]=content
       读取建议使用${var[index]}


　　　10.2.7　与文件系统及程序的限制关系：ulimit
      linux是多人多任务的系统，我们要考虑到各种可能的情况：假设有十几个人同时
      登陆，同时打开多个文件．假设一个人打开的文件占用内存大小至少为1Ｇ，此时
      电脑内存就要有20Ｇ才行，现实中内存没有可能每个电脑都做到那样．
      因此我们要限制用户的某些系统资源，包括可以打开的文件数量，可以使用的
      cpu时间，可以使用的内存总量等．

　　　ulimit:
      ulimit [-SHacdfltu] [配额]
      -H：hard limit,必定不能超过这个值
      -S：soft limit,可以超过这个设置值，但是超过则有警告信息
      -a：后面不接任何选项与参数,可列出所有的限制额度
      -c：当某些程序发生错误时，系统可能会将该程序在内存中的信息写成文件（除错用）
      　　，这种文件就被称作内核文件（core file）．此为限制每个内核文件的最大容量．
      -f：此shell可以建立的最大文件容量，单位为2kbytes.
      -d：此程序可使用的最大段内存（segment）容量．
      -l：可用于锁定（lock）的内存量．
      -t：可使用的最大cpu时间（单位为秒）
      -u：单一使用者可以使用的最大进程（process）数量．


   10.2.8　变量内容的删除，取代与替换．
   　　1.变量内容的删除与替换：
   　　　可以自己试试，不过别用环境变量．
         ${variable#/name}
	 ${variable%:name}
	 #代表从前面开始删除，到name，由于最前面是/,所以是/
	 %/#代表最短，
	 %%/##代表最长
	 %代表从后面开始删除，到name,由于最后面是:,所以是:

         替换：
	 ${variable/name1/name2}
	 两个/之间就是要替换的旧字符串．后面的name2就是替换的新字符串．
	 只替换最先一个
	 若是${vaariable//name1/name2},就是全部替换．

         new var=${old var-content}这个是赋值的，只有当var还没有赋值时可以使用，
	 就连空字符串也没法用．
	 但是空字符串可以使用new var=${old var:-content}来赋值．

         若-变为+,那么就会反过来，只有在var已经赋值/var是空字符串才可以赋值，
	 其他情况不可以．
	 var=${str[:]+expr}
	 var=${str[:]=expr}
	 var=${str[:]?expr}
	 这里还是自己实操比较好．


10.3 命令别名与命令历史
   　10.3.1　命令别名设置：alias,unalias
      当你要使用的命令非常长时，可以用alias取别名．
      另一种方法是，使用shell script
      alias用法：alias str1='str2'
      本质是创造一个新的命令．
      取消别命：unalias
      用法：unalias str1
      
   　10.3.2　历史命令history
      history [n]
      history [-c]
      history [-raw] histfiles
       n：列出最近的ｎ条命令
      -c：将目前的shell中的所有histroty内容全部清除
      -r：将hissfiles的内容读到shell的history记录中
      -a：将目前新增的history命令新增入histfiles中，若没有家histfiles,
          则默认加入~./bash_history
      -w：将目前的history记录内容写入到histfiles中
      1
      !num：执行第num条命令
      !command：有最近的命令开始向前查开头是command，并执行
      !!：执行上一条命令


10.4 Bash shell的操作环境：

   10.4.1命令的运行顺序：
    1.相对/绝对路径执行命令
    2.有alias找到该命令来执行
    3.由bash内置的（builtin）命令来执行
    4.通过$PATH这个变量的顺序查找到的第一个命令来执行
    可以看到我们平常使用的命令都是在后面的几个中，例如ls等

   10.4.2 bash 登陆与欢迎信息：/etc/issue、/etc/motd
     使用tty登陆时，看到的信息由两个部分组成，欢迎信息，登陆要求
     欢迎信息在issue里面。
     还有一个是/etc/issue.net是远程登录时使用的。
     如果你想要让用户登录后取得一些信息，例如你想要让大家都知道的信息：那么可以
     将信息写入到/etc/motd里面。


    10.4.3 bash的环境配置文件：
     系统中一些环境配置文件，让bash子啊启动时直接读取这些配置文件，以规划好bash
     的操作环境。而这些配置文件又可以分为全局系统配置文件以及用户个人偏好配置文
     件。
     
     1.login 与non-login shell
       .login shell:取得bash时需要完整的登陆流程，就成为login shell。也可以
                    这么说：你需要输入用户的账号与密码。此时取得的bash就是
		    login shell。
       .non-login shell：取得bash的方式不需要重复登录的操作。我们在使用GNOME的
                         界面后，打开terminal（实际上是/bin/bash）时不需要登陆。


      login shell一般会读取两个配置文件：
      1./etc/profile:
      这是系统整体的设置，最好不要修改。
      2.~/.bash_profile或/~.bash_login或~/.profile：
      属于用户个人设置，你要添加自己的数据，就写入这里。

      /etc/profile:login shell才会读取。这个文件可以利用用户标识符（UID）来
      决定很多重要的变量数据。也是每个用户登陆取得bash时一定会读取的配置文件。
      这个文件设置的主要变量有：
      PATH：会根据UID决定PATH变量要不要含有sbin的系统命令目录。
      MAIL：根据账号设置好用户的mailbox到/var/spool/mail账号名。
      USER：根据用户的上好设置此变量内容。
      HOSTNAME：根据主机的hostname命令来决定此变量的内容。
      HISTSIZE：历史命令记录条数。
      umask ：包括root默认为022，而一般用户为002。
      
      除此之外，下面的这些文件会依序被调用（在centos7中）：
      1./etc/profile.d/*.sh:
      只要在/etc/profile.d目录中且扩展名为.sh，另外，用户具有r的权限，那么该文件就
      可以/etc/profile调用。这个目录下面的文件规范了bash操作界面的颜色、语系、命令
      别名等。同时你也可以用*.sh来给其他用户设置一些共享的命令别名等。
      2./etc/locale.conf:
      这个文件是由/etc/profile.d/lang.sh调用的，这也是决定bash默认使用何种语系的
      重要配置文件。
      3.usr/share/bash-completion/completions/*
      命令行的【tab】功能就是在这个目录找到相应的命令来处理的。由/etc/profile.d/
      bash_completion.sh加载。
      
      ~/.bash_profile:
      bash在读完整体环境设置的/etc/profile并借此调用其他配置文件后，接下来则是会
      读取用户的个人配置文件。读取顺序：
      ~/.bash_profile
      ~/.bash_login
      ~/.profile
      本质只会读取一个，但是前面的没读到，就会读后面的。
      
      source：读入环境配置文件的命令
      source ~/.bashrc
      . ~/.bashrc 这两个命令是一样的。
      
      ~/.bashrc(non-login shell也会读)：
      当你取得non-login shell，该bash配置文件仅会读到/.bashrc而已。
      此外linux还会调用/etc/bashrc这个文件，为什么？
      1.根据不同的UID设置umask的值。
      2.根据不同的uid设置提示字符（PS1）。
      3.调用/etc/profile.d/*.sh的设置。



      其他相关配置文件：
      /etc/man_db.conf:
      这个文件对于系统管理员是非常重要的文件。规范了使用man的时候，man page的路径
      到哪里去寻找。什么时候来修改文件，当你使用tarball（解压压缩包）的方式来安装
      你的软件的时候。那么你的man page可能会放置在/usr/local/software/man里面。
      这个时候你就要以手动的方式将该路径加到/etc/man_db.conf里面。
      ~/.bash_history:
      默认情况下，我们的历史命令就记录在这里。记录的条数有HISTFILESIZE决定。
      ~/.bash_logout：
      这个文件则记录了【当我注销bash后，系统帮我做完什么操作后才离开】的意思。一般
      情况下只是帮我们清掉屏幕的消息。当然你也可以将其他的任务写在里面。



   10.4.4 终端的环境设置：stty,set
   stty -a 显示bash环境所有的按键内容。
   intr：发送一个interrupt信号给目前正在run的程序（意思是终止）；
   quit：发送一个quit信号给目前正在run的程序；
   erase：向后删除字符；
   kill：删除在目前命令行的所有文字；
   eof：End of file，代表输入结束；
   start：在某个程序停止后，重新启动它的ouput；
   stop：停止目前屏幕的输出；
   susp：送出一个terminal stop的信号给正在运行的程序．

   stty name 按键；修改name相应的按键；

   除了stty，我们还有一些终端设置值,那就是利用set来设置的．
   set可以查看所有的变量．还可以帮我们设置整个命令输出/入的环境．
   set [-uvCHhmBx]
   -u：默认不启用，若启用后，当使用未设置的变量时，会显示设置错误信息
   -v：默认不启用，若启用后，在信息被输出前，会先显示信息的原始内容
   -x：默认不启用，若启用后，在命令被执行前，会显示命令内容
   -h：默认启用，与历史命令有关
   -H：默认启用，与历史命令有关
   -m：默认启用，与任务管理有关
   -B：默认启用，与中括号的作用有关
   -C：默认不启用，若使用>等，则若文件存在时，该文件不会被覆盖．
   
  
   10.4.5 通配符与特殊符号：
   wildcard：
   *：代表0到无穷多个任意字符
   ?：代表一定有一个任意字符
   []：代表［一定有一个在括号内］的字符，example:[abcd]代表一定有其中一个字符
   [-]：代表在编号顺序内的所有字符，即[0-9]即代表0和9之间的任意字符
   [^]：代表反向选择，example:［^abc］代表不是abc的所有字符

　　特殊字符：我就不写了


10.5 数据流重定向：
　　　10.5.1含义：
　　　STDOUT：命令执行所返回的正确信息．
      STDERR：命令执行失败所返回的错误信息．
      数据流重定向可以将STDOUT and STDERR的数据分别传输到其它的文件或设备．
      stdin:code 0,using < / <<
      stdout:code 1,using > / >>
      stderr:code 2,using 2> /2>>

      /dev/null垃圾桶黑洞设备与特殊写法：
      不想看到错误信息：
      find /etc 2> /dev/null
      若想要将正确与错误信息写入同一个文件：
      find /home -name .bashrc > list 2>&1 指将错误的信息转到正确的信息
      find /home -name .bashrc &> list
      不能这么做：
      find /home -name .bashrc > list 2> list
      由于没有特殊的写法，会导致数据交叉写入，导致数据乱序．


      < / <<：将原本需要键盘输入的数据有文件内容来替代



10.6 管道命令：（pipe）
  管道命令是使用|这个界定符号．与；不同，|意思是将上一个命令的结果作为下一个
  命令的参数使用；而；就只是单纯的不同的命令．
  　　

   10.6.1选取命令：cut,grep
   一般来说，选取命令通常都是针对一行一行来分析的．
   　1.cut:
     cut -d　'分割字符' -f fields
     cut -c 字符区间
     -d：后面接分割字符，与-f一起使用．
     -f：根据-d的分割符将一段信息划分成数段，用-f取出第几段．
     -c：以字符（characters）的单位取出固定字符区间．
     2.grep:cut是取出一行中我们要的信息，而grep则是分析一行信息，若有我们要的
     信息，就取出来．
     grep [-acinv] [--color=auto] '查找字符' filename
     -a：将二进制文件以文本文件的方式查找数据
     -c：计算找到'查找字符'的次数
     -i：忽略大小写的不同
     -n：输出行号
     -v：方向选择，结果相反
     
     
     10.6.2 排序命令：sort,wc,uniq
     sort:
     sort是排序命令：
     sort [-fbMnrtuk] [file or stdin]
     -f：忽略大小写
     -b：忽略最前面的空格字符部分
     -M：以月份的名字来排序
     -n：使用纯数字进行排序
     -r：反向排序
     -t：分割符号，默认是[tab]
     -u：uniq，相同的数据只输出一行
     -k：以哪个区间来进行排序（类似cut的-f）


     uniq:
     uniq [-ic]
     -i：忽略大小写字符不同
     -c：进行计数
     
     
     wc:计算字，行
     wc [-lvm]
     -l：仅列出行
     -v：仅列出多少字
     -m：多少字符



    10.6.3双向重定向：tee
    tee可以将数据分流到一个文件，一个屏幕．
    tee [-a] file
    -a：以累加（append）的方式，将数据加入file里面

　　
　　10.6.4　字符转换命令：　tr,col,join,paste,expand
    tr可以用来删除一段信息当中的文字，或是进行文字信息的交换
    tr [-ds] set1
    -d：删除信息当中的set1这个字符
    -s：替换调重复的字符
    set1是可以使用正则表达式的，最好用来解决ｄｏｓ与ｌｉｎｕｘ系统下换行符的
    不同．


    col:
    col [-xb]
    -x：将［tab］转换成对等的空格键
    
    
    join:
    处理俩个文件中，有相同数据的一行，才将它加在一起
    join [-ti12] file1 file2
    -t：join默认以空格分割数据，并且比对第一个栏目(filed)的数据，
    　　如果两个文件相同，则将两条数据连成一条，file1放在前面．
    -i：忽略大小写
    -1：代表第一个文件要用哪个栏目（filed）来分析
    -2：代表第二个文件要用哪个栏目（filed）来分析
    使用join之前数据最好要先排序（sort）否则，会忽略数据

　　
　　　paste:
　　　paste比起join就简单粗暴多了，会直接将两行贴在一起．中间以［tab］来
　　　作为分隔；
　　　paste [-d] file1 file2
      -d：后面可以直接加分隔符，默认是［tab］
      -：如果file部分写成-，表示来自标准输入的数据的意思．
      
      
      expand:与col相似，就是把［tab］转变成空格键．
      expand [-t] file
      -t：后面接数字，表示一个［tab］要用多少个空格键来替换．


   10.6.5 划分命令：split
   split 可以将大文件按照大小或行数来划分，将大文件划分成为小文件．
   split [-bl] file PREFIX
   -b：后面可接欲划分的文件大小，可加单位
   -l：以行数来进行划分
   PREFIX：代表前缀字符的意思，可作为划分文件的前缀字符



　10.6.6参数代换：xargs
　　xargs:生产某个命令的参数．
　　xargs [0epn] command
    -0：如果输入的stdin含有特殊字符，将它还原成一般字符．
    -e：这是EOF的意思，后面可以接一个字符，当xargs接收到这个字符，就会停止工作．
    -p：在执行每个命令时，都会询问使用者的意思
    -n：后面接次数，每次command命令执行时，要使用几个参数的意思
      很多的命令其实并不支持管道命令，因此我们可以通过xargs来提供该命令使用
      标准输入．


   10.6.7 关于减号[-]的用途：
   可以同时用作stdin and stdout,主要看具体情况：
   tar -cvf - /home |tar -xvf - /tmp/homeback
   实际运行后，-在这里意味着stdout;
