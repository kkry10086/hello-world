                      chapter17 daemons

17.1 什么是daemon与服务(service)
【服务】是【常驻在内存中的程序，且可以提供一些系统或网络功能】。而服务一般的英语说法是【service】。
daemon的字面意思是守护神。简单的说，系统为了某些功能必须要提供一些服务，这个服务就成为service。但是service的提供总是需要程序的运行。为了达成这个执行service的程序就被我们称为daemon。举例来说：达成循环型例行性工作排程服务的程序的crond就是daemon的一种。

daemon既然是一只「程序执行后面」的程序，那么daemon所处的原本程序通常是如何命名的？无论如何这些服务的名称被建立之后，被挂上Linux使用时，通常在服务的名称之后会加上一个d。例如：
at和atd，cron和crond这个d代表的就是daemon的意思。

  17.1.1早期System V 的 init 管理行为中daemon的主要分类(Optional)
  在那种年代，我们启动系统服务的管理方式被称为SysV的init脚本程序的处理方式。亦即系统核心第一支呼叫的程序是init，然后init去唤起所有的系统所需要的服务，无论是本地服务好还是网络服务。
  
  基本上init的管理机制有几个特色：
  a.服务的启动、关闭与观察等方式：
    所有的服务启动脚本通通放置于/etc/init.d/底下，基本上都是使用bash shell script 所写成的脚本程序，需要启动、关闭、重新启动、观察动态时，可以透过如下的方式来处理：
    启动：/etc/init.d/deamon start
    关闭：/etc/init.d/deamon stop
    重新启动：/etc/init.d/deamon restart
    状态观察：/etc/init.d/deamon status


  b.服务启动的分类：
  init服务的分类中依据服务是独立启动或被一只总管程序管理而分为两大类：
    独立启动模式(stand alone)：服务独立启动，该服务直接常驻与内存中，提供本机或用户的服务行为，反应速度快。
    总管程序(super daemon)：有特殊的xinetd或inetd这两个总管程序提供socket对应或port对应的管理。当没有用户要求某socket或port时所需要的服务是不会被启动的。若有用户要求时，xinetd总管才会去唤醒相对应的服务程序。当该要求结束时，这个服务也会被结束掉。因为透过xinetd所总管，因此这个家伙就被称为super daemon。好处是可以透过super daemon来进行服务的时程、联机需求等的控制，缺点是唤醒服务需要一点时间的延迟。

  c.服务的相依性问题：
  服务是可能会有相依性的。例如你要启动网络服务，但是系统没有网络，那怎么可能可以唤醒网络服务？如果你需要练级道外部取得认证服务器的联机，当该联机需要另一个A服务的需求，问题是，A服务没没有启动，因此，你的认证服务就不可能成功启动。init在管理员自己手动处理这些服务时，是没有办法协助相依服务的唤醒的。

  d.执行等级的分类：
  上面说到init是开机后主动呼叫的，然后init可以根据用户自定义的执行等级(runlevel)来唤醒不同的服务，已进入不同的操作界面。基本上Linux提供7个执行等级，分别是0,1...6，比较重要的是（1）单人维护模式、（3）纯文本模式、（5）文字加图形界面。
  而各个执行等级的启动脚本是透过/etc/rc.d/rc[0-6]/SXXdaemon连接到/etc/init.d/daemon，连结档名(SXXdaemon)的功能为：
  S为启动该服务，XX是数字，为启动的顺序。由于有SXX的设定，因此开机时可以【依次执行】所有需要的服务，同时也能解决相依服务的问题。
  
  e.制定执行等级默认要启动的服务：
  若要建立如上SXXdaemon的话，不需要管理员手动建立连结档，透过如下的指令可以来处理默认启动、预设不启动、观察预设启动否的行为：
  预设要启动：chkconfig deamon on
  预设不启动：chkconfig daemon off
  观察预设为启动否：chkconfig --list daemon

  f.执行等级的切换行为：
  当你要从纯文本界面(runlevel 3)切换到图形界面(runlevel 5)，不需要手动启动、关闭该执行等级的相关服务，只要【init5】即可切换，init会主动去分析/etc/rc.d/rc[3|5].d/这两个目录内的脚本，然后启动转换runlevel中需要的服务。就完成整体的runlevel切换。


  基本上init主要的功能都写在上头了，重要的指令包括deamon本身自己的脚本(/etc/init.d/daemon)、xinetd这个特殊的总管指令(super daemon)、设定预设开机启动的chkconfig，以及会影响到执行等级的initN等。现在的Linx发行版本已经不适用init了，但是有些脚本没有办法直接塞入systemd的处理，因此这些脚本还是被保留下来。


  17.1.2systemd使用的unit分类
  现在改用systemd这个启动服务管理机制。systemd的好处：
  
  a.平行处理所有服务，加速开机流程：
    旧的init启动脚本是「一项一项任务依序启动」的模式，因此不相依的服务也是得要一个一个的等待。但目前我们的硬件主机系统与操作系统几乎都支持多核心架构了，因此systemd可以让所有的服务同时启动，然后，你会发现系统启动的速度便快了。
    
  b.一经要求就响应的on-demand启动方式：
    systemd全部就是仅有一支systemd服务搭配systemctl指令来处理，无需其他额外的指令来支持。不像systemV还要init，chkconfig，service等等指令。此外，systemd由于常驻内存，因此任何要求(on-demand)都可以立即处理后续的daemon启动的任务。
    
  c.服务相依性的自我检查：
    由于systemd可以自定义服务相依性的检查，因此如果B服务是架构在A服务上面启动的，那当你在没有启动A服务的情况下仅手动启动B服务时，systemd会自动帮你启动A服务。这样就可以免去管理员得要一项一项服务去分析的麻烦。
    
  d.依daemon功能分类：
    systemd管理的服务非常多，为了厘清所有服务的功能，因此，首先systemd先定义所有的服务为一个服务单位(unit)，并将该unit归类到不同的服务类型去。旧的init仅分为stand alone 与super deamon所控制的实在不够，systemd将服务单位(unit)区分为service，socket，target，path，snapshot，timer等多种不同的类型，方便管理员的分类与记忆。
    
  e.将多个deamons集合成为一个群组：
    如同systemV的init有个runlevel的特色，systemd也将许多的功能集合成为一个所谓的target项目，这个项目主要在设计操作环境的建置，所以是集合了许多的daemons，亦即是执行某个target就是执行好多个daemon的意思。
    
  f.向下兼容旧有的init服务脚本：
    基本上，sytemd是可以兼容init的启动脚本的，因此，旧的init启动脚本也能够透过systemd来管理，只是更进阶的systemd功能就没有办法支持了。

  当然也有sytemd没法替代的部分：
  1.在runlevel的对应上，大概仅有runlevel 1,3,5有对应到systemd的某些target类型而已，没有全部对应；
  2.全部的systemd都用systemctl这个管理程序管理，而systemctl支持的语法有限制，不像/etc/init.d/daemon就是纯脚本可以自定义参数，systemctl不可自定义参数；
  3.如果某个服务启动是管理员手动执行启动，而不是使用sytemctl去启动的，那么systemd将无法侦测到该服务，而无法进一步管理；
  4.systemd启动过程中，无法与管理员透过standard input传入信息，因此自行撰写systemd的启动设定时，务必要取消互动机制。


  。systemd的配置文件放置目录
    基本上，systemd将过去所谓的daemon执行脚本通通称为一个服务单位(unit)，而每种服务单位依据功能来区分时，就分类为不同的类型。基本的类型有：系统服务(service)，数据监听与交换的插槽档服务(socket)，储存系统状态的快照类型(snapshot)，提供不同的类似执行等级分类的操作环境(target)等等。
     其配置文件都放置在底下的目录中：
     a./usr/lib/systemd/system/：每个服务最重要的启动脚本设定，有点类似以前的/etc/init.d底下的文件；
     
     b./run/systemd/system/：系统执行过程中所产生的服务脚本，这些脚本的优先序比/usr/lib/systemd/system高；
     
     c./etc/systemd/system/：管理员依据主机系统的需求所建立的执行脚本，这个目录有点像以前的/etc/rc.d/rc5.d/Sxx之类的功能。执行优先比/run/systemd/system高。

     也就是说：系统开机会不会执行某些服务要看/etc/systemd/system/底下的设定，所以该目录下就是一大堆连结档。而实际执行的systemd启动脚本配置文件，其实都是放置在/usr/lib/systemd/system/底下。因此如果要修改某个服务启动的设定，应该去/usr/lib/systemd/system/底下去修改。/etc/systemd/system/仅是连结到正确的执行脚本配置文件而已。


    。systemd的unit类型分类说明：
    那/usr/lib/systemd/system/以下的数据如何区分不同的类型？看扩展名。举例来说：
    ll /usr/lib/systemd/system |grep -E '(vsftpd|multi|cron)'
    -rw-r--r--  1 root root   776 10月 10  2021 anacron.service
    -rw-r--r--  1 root root   154 10月 10  2021 anacron.timer
    -rw-r--r--  1 root root   319  3月 18  2021 cron.service
    -rw-r--r--  1 root root   540  3月 11 20:48 multi-user.target	
    drwxr-xr-x  2 root root   258  7月 16 10:39 multi-user.target.wants/
    lrwxrwxrwx  1 root root    17  6月 28 02:28 runlevel2.target -> multi-user.target
    lrwxrwxrwx  1 root root    17  6月 28 02:28 runlevel3.target -> multi-user.target
    lrwxrwxrwx  1 root root    17  6月 28 02:28 runlevel4.target -> multi-user.target
    -rw-r--r--  1 root root   248  2月 24 02:18 vsftpd.service
    
    vsftpd和crond都是系统服务(service)，而multi-user要算是执行环境相关的类型(target type)。



|扩展名   |       主要服务功能                                                |
|---------+------------------------------------------------------------------|
| service +一般服务类型(service unit)：主要是系统服务，包括服务器本身所需要的本地|
|         +服务以及网络服务都是。                                              |
|---------+-------------------------------------------------------------------|
|socket   +内部程序数据交换的插槽服务(socket unit)：主要是IPC(Inter-process com |
|         +munication)的传输讯息插槽文件(socket file)功能。这种类型的服务通常在监|
|         +控讯息传递的插槽文件，当有透过此插槽文件传递讯息来说要连接服务时，就依据|
|         +当时的状态将该用户的要求传送到对应的daemon，若deamon尚未启动，则启动该 |
|         +daemon后再传送用户的要求。                                           |
|         +使用socket类型的服务一般是比较不会被用到的服务，因此在开机时通常会稍微 |
|         +延迟启动的时间。一般用于本地服务比较多，例如我们的图形界面很多的软件都是|
|         +透过socket来进行本机程序数据交换的行为。                             |
|---------+--------------------------------------------------------------------|
|target   +执行环境类型(target unit)：其实就是一群unit的集合，执行这个target就是 |
|         +执行一堆其他的unit                                                  |
|---------+-------------------------------------------------------------------|
|mount    +文件系统挂载相关的服务(automount unit/mount unit)：例如来自网络的自动|
|automount+挂载、NFS文件系统挂载等与文件系统相关性较高的程序管理                 |
|---------+-------------------------------------------------------------------|
|path     +侦测特定文件或目录类型(path unit)：某些服务需要侦测某些特定的目录来提供|
|         +队列服务，例如最常见的打印服务，就是透过侦测打印队列目录来启动打印功能 |
|---------+--------------------------------------------------------------------|
|timer    +循环执行的服务(timer unit)：这个东西有点类似anacrontab。不过是由      |
|         +systemd主动提供的，比anacrontab更加有弹性                            |
|---------+--------------------------------------------------------------------|




17.2透过systemctl管理服务

  1.2.1透过systemctl管理单一服务(service unit)的启动/开机状态与观察状态
  一般来说，服务的启动有两个阶段，一个是「开机的时候设定要不要启动这个服务」，以及「你现在要不要启动这个服务」。要取消atd这个服务，正规的方法是使用systemctl 而不是使用kill，因为systemctl是专门来管理服务的。

    systemctl [command] [unit]
    command主要有：
    start：立刻启动后面接的unit；
    stop：立刻关闭后面接的unit；
    restart：立刻关闭后启动后面接的unit，亦即执行stop在start；
    reload：不关闭后面接的unit的情况下，重新部署文件，让设定生效；
    enable：设定下次开机时，后面接的unit会被启动；
    disable：设定下次开机时，后面接的unit不会被启动；
    status：目前后面接的unit的状态，会列出有没有运行，开机预设执行与否，登陆等信息。
    is-active：目前有没有在运作中；
    is-dnable：开机时有没有预设要启动这个unit。

    我们要使用systemctl来关掉正常的服务，如果使用kill的方式来关掉一个正常的服务，systemd会无法继续监控该服务的。这就比较麻烦。
    服务(service)的状态中active(***)这个地方是有多个状态的。几个常见的：
      。active(running)：正有一支或多支程序正在系统中执行的意思。
      。active(exited)：仅执行一次就正常结束的服务，目前并没有任何程序在系统中执行。举例：开机或者是挂载时才会进行一次的quotaon功能。quotaon不需一直执行，只执行一次后，就交给文件系统自行处理。
      。active(waiting)：正在执行当中，不过还再等待其他的事件才能继续处理。例如：打印的队列相关服务。虽然正在启动中，不过也需要真的有队列进来，才能唤醒打印机服务来进行下一步打印的功能。
      。inactive：这个服务目前没有运作的意思。


  其实预设启动的位置也是有多个状态的，例如：
    。enabled：这个daemon将在开机时被执行；
    。disabled：这个daemon在开机时不会被执行；
    。static：这个daemon不可以自己启动（enable不可），不过可能会被其他的enabled的服务唤醒。
    。mask：这个daemon无论如何都无法被启动。因为已经被强行注销（非删除）。可透过systemctl unmask改回。


  a.服务启动/关闭与观察
  自己看书。cups是打印服务。

  b.强迫服务注销(mask)的练习
  systemctl stop xx
  systemctl mask xx
  mask这些动作本质就是修改具有大量连接档的/etc/systemd/system。
  mask就是将软连接的xx连接到/dev/null而不是真正的文件。

  17.2.2 透过systemctl观察系统上所有的服务
  如何查看所有的服务。
  systemctl [command] [--type=TYPE] [--all]
  command：
    list-units：依据unit列出目前有启动的unit。若加上--all才会列出没启动的。
    list-unit-files：依据/usr/lib/systemd/system/内的文件，将所有文件列表说明。

  --type=TYPE：就是之前提到的unit type，主要有service，socket，target等。
  sudo systemctl list-units --type=service
  UNIT                                                  LOAD   ACTIVE SUB     D>
  accounts-daemon.service                               loaded active running A>
  acpid.service                                         loaded active running A>
  alsa-restore.service                                  loaded active exited  S>
  在这里，
  UNIT：项目的名称，包括各个unit的类别；
  LOAD：开机时是否会被加载，默认systemctl显示的是加载的项目而已；
  ACTIVE：目前的状态，须与后续的SUB搭配。
  SUB：就是与active一起配合的。


  17.2.3透过systemctl管理不同的操作环境(target unit)
  使用sudo systemctl list-units --type=target --all
  可以看到所有target类型的服务，但是跟操作界面相关性比较高的target有底下几个：
    。graphical.target：就是文字加上图形界面，这个项目已经包含了底下的multi-user.target。
    。multi-user.target：纯文本模式。
    。rescure.target：在无法使用root登入的情况下，systemd在开机时会多加一个额外的暂时系统，与你原本的系统无关。这时你可以取得root的权限来维护你的系统。但是这是额外系统，因此可能需要使用chroot的方式来取得你原有的系统。
    。emergency.target：紧急处理系统的错误，还是需要使用root登入的情况，在无法使用rescure.target时，可以尝试使用这种模式。
    。shutdown.target:就是关机的流程。
    。getty.target：可以设定你需要几个tty之类的，如果想要降低tty的项目，可以修改这个的配置文件。
    正常的模式是multi-user.target以及graphical.target。救援方面的模式主要有rescur.target以及更加严重的emergency.target。如果要修改可提供登入的tty数量，则修改getty.target项目。基本上，我们最常用的就是multi-user.target和graphical.target。
    关于上面两个项目的操作：
    systemctl [command] [unit.target]
    选项与参数：
    get-default：取得目前的target；
    set-default：设定后面接的target成为默认的操作模式；
    isolate：切换到后面接的模式；
    multi-user与graphical两种模式是非冲突的，从开启上面，graphical开启需要multi-user先开启。但是我们这里的set-default选择的类型会改变是否开启graphical。
    而set-default这个命令其实也就是修改/etc/systemd/system/default.target的符号连接的对象，在/usr/lib/systemd/system/multi-user.target和/usr/lib/systemd/system/graphical.target之间。
    注意：改变praphical和multi-user是透过isolate来处理的。在service类型的情况下，使用start/stop/restart才是正确。但是在target这种类型下，使用isolate才是正确的，因为target本质是多个unit的组合，你stop时，会关闭哪个unit？而且这个target关闭后，不代表另一个target会以你想要的方式开启。
    在正常的切换下，使用上述的isolate的方式即可。不过为了方便起见：systemd也提供了数个简单的指令给我们切换操作模式使用：
    systemctl poweroff 系统关机
    systemctl reboot  重新启动
    systemctl suspend  进入暂停状态
    systemctl hibernate进入休眠状态
    systemctl rescue    强制进入救援模式
    systemctl emergency强制进入紧急救援模式

    这里我们了解以下暂停模式和休眠模式：
     。suspend：暂停模式会将系统的状态数据保存到内存中，然后关闭掉大部分的系统硬件，当然，并没有实际关机。当用户按下唤醒机器的按钮，系统数据会从内存中恢复，然后重新驱动被大部分关闭的硬件，就开始正常运作。
     。hibernate：休眠模式则是将系统状态保存到硬盘中，保存完毕后，将计算机关机。当用户尝试唤醒系统时，系统会开始正常运作，然后将保存在硬盘中的系统状态恢复回来。因为数据是有硬盘读出的，因此唤醒的效能与读取硬盘速度有关。


  17.2.4透过systemctl分析各服务之间的相依性
  systemd具有相依性的问题克服，那么如何追踪某一个unit的相依性。我们怎么知道graphical会用到multi-user呢？
  systemctl list-dependencies [unit] [--reverse]
  选项与参数：
  --reverse：反向追踪谁使用这个unit的意思。


  17.2.5与systemd的daemon运作过程相关的目录简介
  那么有那些目录跟系统的daemon运作有关？基本上：
  /usr/lib/systemd/system/：
    默认的启动脚本配置文件都放在这里，这里的数据尽量不要修改，要修改时，请到/etc/systemd/system下修改较佳。
    
  /run/systemd/system/：系统执行过程中所产生的服务脚本，这些脚本的优先序要比/usr/lib/systemd/system高。
  
  /etc/systemd/system/：管理员依据主机系统的需求所建立的执行脚本，其实这个目录有点像以前/etc/rc.d/rc5.d/Sxx之类的功能。执行优先序又比/run/systemd/systemd高。
  
  /etc/sysconfig/*：几乎所有的服务都会将初始化的一些选项设定写入到这个目录下，举例来说，mandb所要更新的man page索引中，需要加入的参数就写入到此目录下的man-db当中。而网络的设定则卸载/etc/sysconfig/network-scripts/这个目录中。

  /var/lib/：一些会产生数据的服务都会将他的数据写入到/var/lib/目录中。
  
  /run/：放置了好多daemon的暂存档，包括lock file以及PID file等等。


  我们的systemd里面有很多的本机会用到的socket服务，里头可能会产生更多的socket file。那么这些socket file在哪里？我们可以透过systemctl来控制。socket本来就是unit的一种类型。
  systemctl list-sockets
  LISTEN                       UNIT                            ACTIVATES         >
/run/acpid.socket            acpid.socket                    acpid.service
/run/avahi-daemon/socket     avahi-daemon.socket             avahi-daemon.servi>
/run/cups/cups.sock          cups.socket                     cups.service
/run/dbus/system_bus_socket  dbus.socket                     dbus.service

  。网络服务与端口对应简介
  系统所有的功能都是某些程序所提供的，而进程都是透过触发程序来产生的。同样，系统提供的网络服务当然也是这样的。
  为了网络连接的顺利，就有了协议，约定服务与接口的默认的一对一关系，接口其实并不是真的存在的，实际是有系统虚拟而成的，类似文件中的info文件。
  那么系统上面设定可以让服务与port对应在一起的文件就是：/etc/services。
  cat /etc/services：
  tcpmux		1/tcp				# TCP port service multiplexer
  echo		        7/tcp
  echo		        7/udp
  discard		9/tcp		sink null
  discard		9/udp		sink null
  systat		11/tcp		users
  
  第一栏是daemon的名称，第二栏为该daemon所使用的端口号与网络数据封包协议，封包协议主要为可靠联机的TCP封包以及较快速但为非面向连接的UDP封包。
  虽然有的时候你可以藉由修改/etc/services来更改一个服务的port，但是不建议，因为可能会造成协议的错误。

  17.2.6关闭网络服务
  当你第一次使用systemctl去观察本地服务器启动的服务时，我们会发现有上百个的服务。而这里要讲的是网络服务。虽然网络服务默认有SELinux管理，但我们还是建议非必要的网络服务就关闭。基本上，会产生一个网络监听端口的程序，这个可以称为服务。
  netstat -tlunp
  Proto Recv-Q Send-Q Local Address           Foreign Address         State       PID/Program name    
  tcp        0      0 127.0.0.1:631           0.0.0.0:*               LISTEN      3589/cupsd          
  tcp        0      0 0.0.0.0:25              0.0.0.0:*               LISTEN      6673/master         
  tcp        0      0 127.0.0.53:53           0.0.0.0:*               LISTEN      2528/systemd-resolv 
  udp        0      0 0.0.0.0:5353            0.0.0.0:*                           3158/avahi-daemon:  
  udp        0      0 0.0.0.0:51052           0.0.0.0:*                           3158/avahi-daemon:  
  udp6       0      0 :::48906                :::*                                3158/avahi-daemon:  
  udp6       0      0 :::5353                 :::*      

  在这里我们至少开了53,25,631等的port但是其中可以看到5353,48906等都是由acahi-daemon来开启的。接下来我们使用systemctl 来观察。
  sudo systemctl list-units --all |grep avahi
  avahi-daemon.service                                                                     loaded    active   running   Avahi mDNS/DNS-SD Stack
  avahi-daemon.socket                                                                      loaded    active   running   Avahi mDNS/DNS-SD Stack Activation Socket
  avahi-daemon的目的是在局域网络进行类似网络邻居的查找，因此这个服务可以协助你在局域网内随时了解网络邻居的即插即用设备。
  既然不需要用到那么就关掉。
  关掉，并且确定disabled。这里有两个。
  一般来说，本地服务器至少需要25port，而22pport则最好加上防火墙来管理远程联机登入比较好。因此除了我们需要的其他都给关掉。


17.3systemctl针对service类型的配置文件

  以前，我们想要建立系统服务，就要到/etc/init.d/底下去建立相对应的bash shell script来处理。现在systemd的环境下，又该如何处理。
  17.3.1systemctl配置文件相关目录简介
  systemd的配置文件大部分放置于/usr/lib/systemd/system/目录内，但是该目录内份额文件主要是原本软件所提供的设定，建议不要修改。最好是去修改连接档的/etc/systemd/system/目录。
  如果我们要额外修改vsftpd.service的话，RedHat建议要放置到的地方：
  。/usr/lib/systemd/system/vsftpd.service：
    官方释出的预设配置文件；
  。/etc/systemd/system/vsftpd.serviec.d/custom.conf：
  在/etc/systemd/system底下建立与配置文件相同文件名的目录，但是要加上.d的扩展名。然后在该目录下建立配置文件即可。另外，配置文件最好附档名取名为.conf较佳。在这个目录下的文件会「累加其他设定」进入/usr/lib/systemd/system/vsftpd.service。
 
  。/etc/systemd/system/vsftpd.service.wants/*：
    此目录内的文件为链接档，设定相依服务的连接。意思是启动了vsftpd.service之后，最好再加上这目录建议的服务。
    
  。/etc/systemd/system/vsftpd.service.requires/*：
    此目录内的文件为链接档，设定相依服务的连接。意思是启动vsftpd.service之前，需要事先启动的服务。

  基本上，在配置文件里面你都可以自由设定相依服务的检查，并且设定加入到那些target里面。但是如果是已经存在的配置文件，或者是官方提供的配置文件，Red Hat是建议你不要修改原设定，而是到上面提到的几个目录去进行额外的客制化设定比较好。当然最后还是由你自己决定。

  17.3.2 systemctl配置文件的设定项目简介
  了解配置文件的相关目录与文件之后，就是了解配置文件本身的内容。用sshd.service来作例子。
  cat /usr/lib/systemd/system/ssh.service
  [Unit]
  Description=OpenBSD Secure Shell server
  Documentation=man:sshd(8) man:sshd_config(5)
  After=network.target auditd.service
  ConditionPathExists=!/etc/ssh/sshd_not_to_be_run

  [Service]
  EnvironmentFile=-/etc/default/ssh
  ExecStartPre=/usr/sbin/sshd -t
  ExecStart=/usr/sbin/sshd -D $SSHD_OPTS
  ExecReload=/usr/sbin/sshd -t
  ExecReload=/bin/kill -HUP $MAINPID
  KillMode=process
  Restart=on-failure
  RestartPreventExitStatus=255
  Type=notify
  RuntimeDirectory=sshd
  RuntimeDirectoryMode=0755

  [Install]
  WantedBy=multi-user.target
  Alias=sshd.service

  [unit]这个项目与此unit的解释、执行服务相依性有关
  [service]这个项目与实际执行的指令参数有关
  [install]这个项目说明此unit要挂载那个target底下

  至于配置文件内有些规则还是要说明一下：
  。设定项目通常是可以重复的，例如我可以设定两个after在配置文件中，不过，后面的设定会取代前面的。如果想要将设定归零，可以使用类似「After=」的设定。
  。如果设定参数需要由「是/否」的项目，你可以使用1,yes，true，on代表启动，用0,no，false，off代表关闭。
  。空白行、开头为#或;的那一行，都代表批注。

   a.unit部分：
   Description：就是当我们使用systemctl list-units时，会输出给管理员看的建议说明。当然，status 也可以看到。
   Documentation：这个项目提供管理员能够进行进一步的文件查询的功能。
   例如：Documentation=http://...
         Documentation=man:ssh(8)
	 Documentation=file:/etc/ssh/sshd_config

   After：说明此unit是在哪个daemon启动之后才启动的意思。基本上仅是说明服务启动的顺序而已，并没有强制要求里头的服务一定要启动后此unit才能启动。以ssh的内容为例，after后面由network.target以及ssh-eygen.service，但是若这两个unit没有启动而强制启动sshd.service的话，那么sshd.service应该还是能够启动的。
   Befor：与After的意义相反，是在什么服务启动前最好启动这个服务的意思。不过这仅是规范服务启动的顺序，并非强制要求的意思。
   Requires：明确的定义此unit需要在哪个daemon启动后才能够启动。就是设定相依服务。如果此项设定的前导服务没有启动，那么此unit就不会被启动。
   Wants：与Requires刚好相反，规范的是这个unit之后最好还要启动什么服务比较好的意思。不过，并没有明确的规范就是了。主要的目的是希望建立让使用者比较好操作的环境。因此，这个Wants后面接的服务如果没有启动，不会影响到这个unit本身。
   Conflicts：代表冲突的服务。亦即这个项目后面接的服务如果有启动，那么我们这个unit本身就不能启动。我们unit有启动，则此项目后的项目就不能启动。

  
  b.service
  Type：说明这个daemon启动的方式，会影响ExecStart。有以下几种类型；
   。simple：默认值，这个daemon主要由ExecStart接的指令串来启动，启动后常驻于内存中。
   。forking：由ExecStart启动的程序透过spawns延伸出其他子程序来作为此daemon的主要服务。原生的父程序在启动结束后就会终止运作。传统的unit服务大多属于这种项目，例如httpd这个www服务，当httpd的程序因为运作过久因此即将终结了，则systemd会再重新生出另一个子程序持续运作后，再将父程序删除。
   。oneshot：与simple类似，不过这个程序在工作为完毕后就结束了，不会常驻在内存中。
   。dbus：与simple类似，但这个daemon必须要在取得一个D-Bus的名称后，才会继续运作。因此设定这个项目时，通常也要设定BusName=xxx才行。
   。idle：与simple类似。意思是，要执行这个daemon必须要所有的工作都顺利执行完毕才会执行。这类的daemon通常是开机到最后才执行即可的服务。

  EnvironmentFile：可以指定启动脚本的环境配置文件。例如ssh的配置文件写入到/etc/sysconfig/sshd档和总，也可以在后面接多个不同的Shell变量来给予设定。
  ExecStart：就是实际执行此daemon的指令或脚本程序。你也可以使用ExecStartPre（之前）以及ExecStartPost（之后）两个设定项目来在实际启动服务前，进行额外的指令行为。但是你得要特别注意的是，指令串仅接受「指令 参数 参数 ...」的格式，不能接受<,>,>>,|,&等特殊字符，很多的bash语法也不支持。所以要使用这些特殊字符时，最好直接写入到指令脚本里面去。不过上述的语法也不是完全不能用，若要支持比较完整的bash语法，那你得要使用Type=oneshot才行。
  ExecStop：与systemctl stop的执行有关，关闭此服务时所进行的指令。
  ExecReload：与systemctl reload有关的指令行为。
  Restart：当设定Restart=1时，则当此daemon服务终止后，会再次的启动此服务。举例来说，如果你在tty2使用文字界面登入，操作完毕后注销，基本上，这个时候tty2就已经结束服务了。但是你会看到屏幕又立刻产生一个新的tty2的登入界面等待你的登入。这就是Restart的功能，除非使用systemctl强制将此服务关闭，否则这个服务会源源不断的一直重复产生。
  RemainAfterExit：当设定为RemainAfterExit=1时，则当这个daemon所属的所有程序都终止之后，此服务会再尝试启动。这对于Type=oneshot的服务很有帮助。
  TimeoutSec：若这个服务在启动或者关闭时，因为某些缘故导致无法顺利「正常启动或正常结束」的情况下，则我们要等多久才进入「强制结束的状体」。
  KillMode：可以时process，control-group，none的其中一种，如果时process则daemon终止时，只会终止主要的程序（ExecStart接的后面的那串指令），如果时control-group时，则由此daemon所产生的其他control-group的程序，也都会被关闭。如果时none，则没有程序会被关闭。
  RestartSec：与Restart有点相关性，如果这个服务被关闭，然后需要重新启动时，大概需要sleep多少实践再重新启动的意思。预设时100ms。
  

  c.「install」
  WantedBy：这个设定后面接的大部分是*.target unit。这个unit本身是附挂在某一个target unit底下。一般来说，大多的服务性质的unit都是附挂在multi-user.target底下。
  Also：当这个unit本身被enable时，Also后面接的unit也会enable的意思。也就是具有相依性的服务可以写在这里。
  Alias：进行一个连结的别名的意思。当systemctl enable相关的服务时，则此服务会进行连接档的建立。以multi-user.target为例，这个家伙是用来作为默认操作环境default.target的使用，因此当你设置用成default.target时，这个/etc/systemd/system/default.target就会连接到/usr/lib/systemd/system/multi-user.target。

  17.3.3 两个vsftpd运作的实例
  我们可能需要在vsftod使用到两个port，分别是21以及555；在这两个port都启用的情况下，我们就需要两个配置文件以及两个启动脚本设定了。
  现在假设是：
    。预设的port21：使用/etc/vsftpd/vsftpd.conf配置文件，以及/usr/lib/systemd/system/vsftpd.service设定脚本；
    。预设的port555：使用/etc/vsftpd/vsftpd2.conf配置文件，以及/usr/lib/systemd/system/vsftpd2.service设定脚本；
!!!这里是centos的，但是在ubuntu里面：/etc/vsftpd.conf；

这里自己看书，自己配置文件的修改等。

17.3.4 多重的重复设定方式：以getty为例
  我们有6个终端机可以使用，就是那个tty1-tty6。那个东西是由agetty这个指令达成的。而主要管理的是getty.target。不过实际产生tty1-tty2的则是由getty@.service所提供的。
  先看看/usr/lib/systemd/system/getty@.service
  其中最重要的是
  ExecStart=-/sbin/agetty -o '-p -- \\u' --noclear %I $TERM
  而我们由于有很多个tty，那么同样的我们需要相应的getty(num).service的配置文件，设定脚本。但是我们只有getty@.service，所以我们可以看看开启这个service的getty.target。
  在鸟哥中：After=getty@tty1.service，getty@tty2.service，getty@tty3.service，getty@tty4.service，getty@tty5.service，getty@tty6.service
  在我的系统中：After=getty@tty1.service getty-static.service

  这里是因为：当我们执行完getty.target之后，他会持续要求后面的getty@ttyn.service服务继续启动。而我们的systemd会这么作：
  。先看/usr/lib/systemd/system，/etc/systemd/system有没有getty@tty1.service的设定，若有就执行，若没有则执行下一步。
  。找getty@.service的设定，若有则将@后面的数据带入成%I的变量，进入getty@.service执行。getty@.service里面的ExecStart=-/sbin/agetty -o '-p -- \\u' --noclear %I $TERM。
  也就是说其实没有getty@tty1.service而是透过getty@.service来执行。也就是说，getty@.service的目的是为了要简化多个执行的启动设定。命名方式是：
  源文件：执行服务名称@.service；
  执行文件：执行服务名称@范例名称.service。因此当有范例名称带入时，则会有一个新的服务名称产生出来。

  a.改变tty的数量
  我们tty的数量是在ssytemd的登入配置文件/etc/systemd/logind.conf里面规范的。
  所以可以看看该配置文件里面，
  修改[login]的内容：
  #NAutoVTs=6
  #ReserveVT=6
  改为
  NAutoVTs=n
  ReserveVT=0


  b.暂时增加vsftpd到2121port
  其实在/usr/lib/systemd/system/底下还有个特别的vsftpd@.service。
  cat /usr/lib/systemd/system/vsftpd@.service
  在我的电脑中没有这个文件。
  实际上，%i/%I就是代表@后面接的范例文件名的意思。那么我们能不能建立vsftpd3.conf文件，然后透过该文件来启动新的服务?
  当然可以，使用方法：
  systemctl start vsftpd@vsftpd3.service
  systemctl status vsftpd@vsftpd3.service

  17.3.5自己的服务自己作：
  假设我要作一支可以备份自己系统的服务，这支脚本我放在~/backups底下。
  vim ~/backups/backup.sh：
  #!/bin/bash
  source="/etc /usr /root /var/lib /var/spool/{cron,at} /home/zcj/书 /home/zcj/helloworld"

  target="~/backups/backup-system-$(date +%Y-%m-%d).tar.xz"
  [ ! -d ~/backups] && mkdir ~/backups
  tar -cvzf ${target} ${source} &> ~/backups/backup.log

  这是脚本。然后就是服务了，在所有的脚本的目录中，/etc/systemd/system是优先级最高的，而且我们也最好不要修改/usr/lib/systemd/system里面的内容。所以最好在/etc/systemd/system里面修改。
  vim /etc/systemd/system/backup.service
  [Unit]
  Description=server to back my file 
  Requires=atd.service

  [Service]
  Type=simple //可以改成oneshot，因为只执行一次。
  ExecStart=/bin/bash -c "echo /home/zcj/backups/baskup.sh | at now"

  [Install]
  WantedBy=multi-user.target
  Requires的at服务，是我们的ExecStart需要用到at指令。
  之后就是重载所有的服务，然后开启我们的服务。顺带一提，作为脚本而不是程序，因此执行完毕后，就不会继续在内存中存在。
  可以通过ps来看到我们的服务有成功运行。
  ps aux |grep backup
  root       19041  0.0  0.0  13060  3740 ?        S    10:55   0:00 /bin/bash /home/zcj/backups/backup.sh
  root       19043  4.7  0.0  14216  4504 ?        S    10:55   0:05 tar -cvzf /home/zcj/backups/backup-system-2022-08-20.tar.xz /etc /usr /root /var/lib /var/spool/{cron,at} /home/zcj/书 /home/zcj/helloworld
  root       19108  0.0  0.0  12184  2376 pts/1    S+   10:57   0:00 grep --color=auto backup

  
17.4 systemctl 针对timer的配置文件

  有时候，某些服务你想要定期执行，或者是开机后执行，或者什么服务启动多久后执行等等。在过去，我们大概使用crond这个服务来定期处理，不过既然现在有一直常驻在内存中的systemd，加上systemd有个协力服务timers.target，可以协助定期处理各种任务。

  a.systemd.timer的优势
    在archlinux的官网上有提到：
    。由于所有的systemd的服务产生的信息都会被及记录(log)，因此比crond在debug方面要更清除方便的多；
    。各项timer的工作可以跟systemd的服务相结合；
    。各项timer的工作可以跟contrl group(cgroup，用来取代/etc/secure/limit.conf的功能)结合，来限制该工作的资源利用。
    
  b.任务需求
  基本上，想要使用systemd的timer功能，必须要有几个要件：
    。系统的timer.target一定要启动；
    。要有个sname.service的服务存在，sname是自己指定的名称；
    。要有个sname.timer的时间启动服务存在。
  满足上面的需求就可以了。我们的backup.service可以拿来实验，我们也不希望每次都要打开使用，但是可以让它定期执行。

  c.sanme.timer的设定值
  