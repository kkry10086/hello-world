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
    
  
    


 