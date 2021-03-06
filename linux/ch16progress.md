			16 进程管理与SELinux初探

16.1什么是进程(process)
  在linux系统当中:[触发任何一个事件时,系统都会将他定义成为一个进程,并且给予这个进程一个ID,称为PID,同时依据启发这个进程的用户与相关属性关系,给予这个PID一组有效的权限设定.]

  16.1.1 进程与程序(process&program)
  进程的产生:执行一个程序或指令,然后就可以触发一个事件从取得一个PID.系统只认识二进制文件(binary file),binary file就是程序(program).
  进程一般是放置在实体磁盘中,然后透过用户的执行来触发.出发后会加载到内存中成为一个个体,那就是进程.为了操作系统可以管理这个进程,因此进程有给予执行者的权限/属性等参数,并包括程序所需要脚本与数据或文件数据等,最后再给予一个PID.系统就是透过这个PID来判断该process是否具有权限进行工作.当执行指令时,这个进程衍生出来的其他进程在一般状态下,也会沿用这个进程的相关权限.

  总结:
  程序(program):通常为binary program,放置在储存媒体中,为实体文件的形态存在.
  进程(process):程序被触发后,执行者的权限与属性,程序的程序代码与所需数据等都会被加载内存中,操作系统并给予这个内存内的单位一个标识符(PID),可以说,进程就是一个正在运行中的程序.

   1.子进程与父进程:
   我们使用bash这个shell程序时,使用touch等指令时,这个指令会产生一个新的进程,这个新的进程就是子进程,而产生这个子进程的bash进程就是父进程.

   2.fork and exec: 进程呼叫的流程
   在linux的进程呼叫通常成为fork-and-exec的流程.进程都会皆由父进程以复制(fork)的方式产生一个一模一样的子进程(此时更应该称为暂存进程),然后被复制出来的子进程再以exec的方式来执行实际要进行的程序,最终就成为一个子进程的存在.因此父进程与子进程的差别就在与PID和PPID,执行的程序,两者的环境基本相同.

   3.系统与网络服务:常驻在内存的进程
   我们知道系统每分钟都会去扫描/etc/crontab以及相关的配置文件,来进行工作排程.那么这个工作排程是谁负责?是crond这个程序所管理的,我们将它启动在背景当中一直持续不断的运作,这就是常驻在内存中的进程.
   
   常驻在内存当中的进程通常是负责一些系统所提供的功能以服务用户各项任务,因此这些常驻程序就会被我们称为:服务(daemon).系统的服务非常多,不过主要大致分成系统本身所需要的服务,还有一些则是负责网络联机的服务,而网络服务比较有趣的地方,在于这些程序被执行后,它们会启动一个可以负责网络监听的端口(port),以提供外部客户端(client)的联机要求.
   

  16.1.2 Linux的多人多任务环境

    1.多人环境:
      linux最棒的地方就在于它的多人多任务环境.在Linux系统上面具有多种不同的账号,每 种账号都有其特殊的权限,只有一个人具有至高无上的权利,那就是root(系统管理员).除了root之外,其他人都必须要受一些限制,而每个人进入linux的环境设定都可以随着每个人的喜好来设定.
    2.多任务行为:
      CPU切换进程的工作,与这些工作进入到CPU运作的排程会影响到系统的整体效能.目前Linux使用的多任务切换行为是非常棒的一个机制,几乎可以将PC的性能整个压榨出来.由于效能非常好,因此当多人同时登陆系统时,会感觉整部主机好像是为了你存在一般.
 
    3.多重登入环境的七个基本终端窗口:
      在Linux当中,默认提供了六个文字界面登入窗口,以及一个图形界面,可以使用[alt]+[FN]来切换不同的终端机界面.细节部分19章学习.

    4.特殊的进程管理行为:
      Linux几乎可以说绝对不会当机(kkry我就有过一次,当然电脑差是一个重要原因),因为它可以在任何时候,将某个被困住的进程杀掉,然后在重新执行该进程而不用重新启动.如果我们在某一个终端界面挂了,就可以切换其他的界面.然后使用pa -aux,找到错误进程,然后kill.

    5.bash环境下的工作管理(job control):
      其实当你使用apt update 和apt upgrade这时有时会要很长的时间来更新,会给你一个终端只能执行一个任务.但是你可以在命令的后面加上&符号,将其放在背景完成,这样就可以继续使用bash来执行工作.

    6.多人多任务的系统资源分配问题考虑:
      多人多任务的确有很多的好处,但其实也有管理上的困扰,因为使用者越来越多,将导致你管理上的困扰.另外,当使用者达到一定数量后,你的机器便需要省级,因为CPU的运算与RAM的大小可能就会不够使用.


16.2 工作管理(job control)
  工作管理就是在用在bash环境下的，也就是说：「当我们登入系统取得bash shell之后，在单一终端机接口下同时进行多个工作的行为管理」。

  16.2.1什么是工作管理
  进行工作管理的行为中，其实每个工作都是目前bash的子进程，亦即彼此之间是有相关性的。我们无法以job control的方式由tty1的环境去挂你了tty2的bash。
  由于假设我们只有一个终端接口，因此可以出现提示字符让你操作的环境就称为前景（foreground），至于其他工作就可以让你放入北京（background）去暂停或运行。放入背景的工作想要运行时，其必须不能够与使用者互动。放入背景的工作是不可以使用「ctrl」+c来终止的。
  总结：这些工作所触发的进程必须来自于shell的子进程；你可以控制与下达指令的这个环境成为前景（前台）的工作；背景：可以自行运作的个哦你做，你无法使用「ctrl」+c终止它，可使用bg/fg呼叫该工作；背景中「执行」的进程不能等待terminal/shell的输入。


  16.2.2job conrtol 的管理
    任务分为前景（前台）与背景（后台），然后，背景里面的工作状态又可以分为「暂停(stop)」与「运作中(running)」。实际进行job控制的指令：

    1.直接将指令丢到背景中「执行」&
    我们在只有一个bash的环境下，如果想要同时进行多个工作，那么可以将某些工作直接丢到背景环境中，让我们可以继续操作前景的工作。将工作丢到背景的最简单的方法：利用「&」。
    假设我们要将/etc备份到/tmp/etc.tar.gz：
    tar -czf /tmp/etc.tar.xz /etc &
    但是当这条指令变成 tar -czvf /tmp/etc.tar.xz /etc & 时，此时其会将该任务的情况表现在前台，这就会影响前台的操作，所以一旦加上-v等类似可以想前台报告情况的选项时，可以使用数据流重定向，将数据转发到其他的文件：/dev/null都可以。
    例如：tar -czvf /tmp/etc.tar.xz /etc > /dev/null 2>& 1 &

    2.将「目前（前台）」的工作丢到背景（后台）中「暂停」：「ctrl」+z
    假设我们在使用一个vim的程序，却发现我们要打开一个文件，但是不知道在哪里，需要在bash的环境下进行搜寻，此时不一定要结束vim，我们可以暂时将vim放到后台中等待就行了。
    在vim的一般模式下，按下「ctrl」+z，屏幕就会出现「1」，表示这是第一个工作，而那个+代表最近一个被丢进背景的工作，且目前在背景下预设会被去用的吧和工作（与fg这个指令有关）。而那和Stopped则代表目前这个工作的状态。在预设的情况下，使用「ctrl」+z丢到背景当中的工作都是「暂停」的状态。

    3.观察目前的背景工作状态：jobs
    jobs [-lrs]
    -l：除了列出job number与指令串之外，同时列出PID的号码；
    -r：仅列出正在背景run的工作；
    -s：仅列出正在背景当中暂停(stop)的工作。
    在列出的结果中还有+/-号，+号代表预设的取用工作。「目前我有两个工作在背景当中，两个工作都是暂停的，而如果我仅输入fg时，就会取用有+号的任务到前景来使用。」
    
    4.将背景工作拿到前景来处理：fg
    之前都是讲如何将工作放到背景去执行，现在来讲将背景的工作拿到前景来处理。
    fg %jobnumber
    %jobnumber:jobnumber为工作号码。注意：%可以不加。
    jobnumber可以使用jobs查看到。
    fg +/- 取出有+/-的任务。
    
    5.让工作在背景下的状态变成运作中：bg
    我们如何让一个在背景中暂停的工作变成运行中「running」,使用bg；
    bg %jobnumber
    使用方式与fg类似。
    
    6.管理背景当中的工作：kill
      那么将工作移除或是让其重新启动，这个时候就得需要给予该工作一个讯息(signal)，让他知道该怎么作才好。此时，kill这个指令就派上了用场。
      kill -signal 「%jbnumber」/「PID」
      kill -l
      -l：列出目前kill能够使用的讯号有哪些。
      signal：代表给予后面接的那个工作什么样的指示。用man 7 signal可知。
        -1：重新读取一次参数的配置文件（类似reload）
	-2：代表与由键盘输入「ctrl」+c 同样的动作
	-9：代表强制删除一个工作
	-15：以正常的进程的方式终止一项工作。
	-9通常是用来「强制删除一个不正常的工作」。-15是以正常的步骤结束一项工作。两者并不相同。

  
  16.2.3 脱机管理问题
  之前讲的情况都是在主机情况下，但是，如果我们以远程联机的方式链接到Linux主机，并且将工作以&的方式放到背景中，假设此时在工作为结束时，你脱机了，该工作还会进行吗？答案是「否」。这个工作会中断掉。
   那怎么办，我们的工作需要一大段时间，又不能放置在背景（可能会忘掉）。此时我们可以考虑使用at，at与系统有关，但是与终端无关。如果不使用at，那么还有nohup这个指令，这个nohup可以让你在脱机或注销系统后，还能够让工作继续进行。

    nohup [指令与参数]
    nohup [指令与参数] &
    nohup并不支持bash内建的指令，因此你的指令要是外部指令才行。
    nohup也与终端机无关，因此这个讯息的输出会被导向「~/nohup.out」，所以当你输入nohup会告知你信息会重定向到~/nohup.out。


16.3进程管理
  本章一开始就提到所谓进程的概念，进程的触发、子进程与父进程的相关性等，此外，还有那个「进程的相依性」以及所谓的「僵尸进程」等等需要说明。


  16.3.1进程的观察
    1.ps:将某个时间点的过程运作情况攫取下来
      ps aux：观察系统所有的进程数据
      ps -lA：观察所有系统的数据
      ps axjf：连同部分进程树状态
      选项与参数
      -A：所有的process均显示出来，与-e相同；
      -a：不与terminal有关的所有process；
      -u：有效使用者(effictive user)相关的process；
      x ：通常与a这个参数一起使用，显示较完整的信息；
      输出格式规划
      l ：较长、详细的将该PID信息列出；
      j ：工作的格式(jobs format)；
      -f：做一个更为完整的输出；

      最重要的两个ps：
      a.ps -l：仅观察自己的bash相关进程
      F S   UID     PID    PPID  C PRI  NI ADDR SZ WCHAN  TTY          TIME CMD
      0 S  1000  154410  154384  0  80   0 -  3823 do_wai pts/0    00:00:00 bash
      0 R  1000  159513  154410  0  80   0 -  3944 -      pts/0    00:00:00 ps

      上面就是 ps -l 的结果，
      F：代表这个进程旗标(process flags)，说明这个进程的总结权限。
      若为4表示次进程的权限为root;
      若为1则表示此子进程仅进行复制(fork)而没有实际执行(exec)

      S：代表这个进程的状态(STAT),主要状态有：
        a.R(Running)：该程序正在运行中；
	b.S(Sleep)：该程序目前正在睡眠状态(idle)，但可以被唤醒(signal)；
	c.D：不可被唤醒的睡眠状态，通常这支程序可能在等待I/O的情况；
	d.T：停止状态(stop)，可能是在工作控制（背景暂停）或除错(traced)状态；
	e.Z(Zombie)：僵尸状态，进程已经终止但却无法移除至内存外。

      UID,PID,PPID：代表此进程该UID所拥有的进程的PID号码，与其父进程的PID号码。

      C：代表CPU的使用率，单位为百分比。
 
      PRI/NI：Priority/Nice的缩写。代表此进程被CPU所执行的优先级，数值越小代表该进程越快被CPU执行。
      
      ADDR/SZ/WCHAN：都与内存有关，ADDR是kernel function，指出该进程在内存的那个部分，如果是个running的进程一般都会显示「-」；SZ代表此进程用掉多少内存；WCHAN表示目前进程是否运作中，同样的，若为-表示正在运作中。
      
      TTY：登入者的终端位置，若为远程登陆则使用动态CPU终端接口(pts/n)。
      
      TIME：使用掉的CPU时间，注意，是此进程实际花费CPU运作的时间，而不是系统时间。
      
      CMD：就是command的缩写，造成此进程的触发程序的指令。

      b.ps aux :
      
USER         PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
root           1  0.5  0.1 167000 12312 ?        Ss   06:38   0:02 /sbin/init splash
root           2  0.0  0.0      0     0 ?        S    06:38   0:00 [kthreadd]
root           3  0.0  0.0      0     0 ?        I<   06:38   0:00 [rcu_gp]
      可以看到 ps -l 与ps aux的结果不同，在ps aux中，各字段的含义：
      USER：该process属于哪个使用者的账号；
      PID：该process的进程标识符；
      %CPU：该process使用调的CPU资源百分比；
      %MEM：该process所占用的物理内存百分比；
      VSZ：该process使用掉的虚拟内存量(Kbytes)；
      RSS：该process占用的固定的内存量(Kbytes)；
      TTY：该process是在那个终端机上面运作，若与终端机无关，则显示?，另外，tty1-tty6是本机上面的登入者进程，若为pts/0等等的，则表示为由网络连接进主机的进程。
      STAT：该进程目前的状态，状态显示与 ps -l 的S旗标相同(R/S/D/T/Z)；
      START：该process被触发启动的时间；
      TIME：该process实际使用的CPU运作的时间；
      COMMAND：该进程的实际指令。

      

      c.僵尸进程(zombie)：
        原因：因为该进程应该执行完毕，或者是因故障应该要终止了，但是该进程的父进程却无法完整的将该进程结束，而造成那个进程一直存在内存当中。如果某个进程的CMD后面还接上<defunct>时，就代表该进程是僵尸进程。
	当系统不稳定时就容易造成所谓的僵尸进程，可能是因为程序写的不好，或者是使用者的操作习惯不良等等所造成的。如果你发现系统中很多僵尸进程时，要记得找出父进程，然后好好的做个追踪，好好的进行主机的环境优化。不要直接的kill，否则以后还是会产生的。
	事实上，通常僵尸进程都已经无法管控，而直接是交给systemd这支程序来负责，偏偏systemd是系统第一支程序，是所有程序的父程序。我们无法杀掉该程序的。所以，如果产生了僵尸进程，而系统过一阵子还没有办法透过核心非经常性的特殊处理来将该进程删除时，就只好reboot来将该进程抹去。



    2.top 动态观察进程的变化
    相对于ps是擷取一个时间点的进程状态，top则可以持续侦测进程运作的状态。
    
    top [-d 数字] |top [-bnp]
    选项与参数：
    -d：后面可以接秒数，就是整个进程画面更新的描述，预设是5秒。
    -b：以批次的方式执行top，还有更多的参数可以使用。通常会搭配数据流重导向来将批次的结果输出成为文件。
    -n：与-b搭配，意义是，需要进行几次top的输出结果。
    -p：制定某些个PID来进行观察检测。
    
    在top执行过程中，可以使用的按键指令：
    ?：显示在top当中可以键入的按键指令
    P：以CPU的使用资源排序显示
    M：以Memery的使用资源排序显示
    N：以PID来排序
    T：有该Process是使用的CPU时间积累排序
    k：给予某个PID一个讯号
    r：给予某个PID重新制定一个nice值
    q：离开top软件的按键。
	
	
进程号 USER      PR  NI    VIRT    RES    SHR    %CPU  %MEM     TIME+ COMMAND
6453   zcj       20   0 5769228 334072 143980 S  10.4   4.2   9:17.40 gnome-s+ 
16636  zcj       20   0 3256212 229688 131712 S   3.6   2.9   2:34.64 clement+ 

     PID：Process的ID；
     USER：该process所属的使用者；
     PR：Priority的简写，进程的优先执行顺序，越小越早被执行；
     NI：Nice的简写，与Priority有关，越小越早被执行；
     %CPU：CPU的使用率。
     %MEM：内存的使用率。
     TIME+：CPu使用时间的累加。



    3.pstree ：
    pstree [-A|U] [-up]

    选项与参数：
    -A：各进程之间的连接以ASCII字符来连接；
    -U：各进程之间的连接以万国码的字符来连接，在某些终端接口下可能有错误；
    -p：并同时列出每个process的PID；
    -u：并同时列出每个process的所属账号名称。
    
    所有的进程都是依附在systemd这只程序底下的。其PID是1，因为这支进程是由linux的核心主动呼叫的第一支程序，所以PID就是1号。所以systemd发生僵尸进程时，需要reboot。

  16.3.2进程的管理
  进程之间是可以互相控制的。你可以关闭，重新启动服务器软件，服务器软件本身是个进程，所以就是相应的控制进程。我们是通过给予进程一个信号(signal)来告知进程我们想要它干什么。
  
  使用kill -l或man 7 signal都可以查询到。
  主要的讯号代号与名称对应内容：
  代号   名称             内容
  1    SIGHUP        启动被终止的进程，可让PID重新读取自己的配置文件，类似
                     重新启动
  2    SIGINT        相当于用键盘输入【ctrl】+c来中断一个进程的进行
  9    SIGKILL       代表强制中断一个进程的进行，如果该进程进行到一半，那么
                     尚未完成的部分可能会有半产品产生。
  15   SIGTERM       以正常的结束进程来来终止进程。由于是正常的终止，所以后
                     续的动作会完成。不过，如果该进程已经发生问题，就是无法
		     使用正常的方法终止时，这个signal就没用了。
  19   SIGSTOP       相当于用键盘输入【ctrl】+z来暂停一个进程的机型。


    1.kill -signal PID
  kill可以帮我们将这个signnal传送给某个工作(%jobnumber)或者某个PID。kill后面直接加数字与加上%jobnumber是不同的。%jobnumbber是指工作控制中有n号工作，而直接加数字指的是PID。

    2.killall -signal 指令名称
  由于kill后面必须加上PID或是%jobnumber，所以kill都会配合ps，pstree等指令。因为我们能必须要找到相应的进程的ID。。但是，可以通过指令的名称来给予信号。
  killall [-iIe] [command name]
  选项与参数：
  -i：interactive的意思，交互式的，若需要删除时，会出现提示字符给用户；
  -e：exact的意思，表示【后面接的command name要一致】，但整个完整的指令不能超过15个字符；
  -I：指令名称忽略大小写。


  16.3.3 关于进程的执行顺序
  Linux是多人多任务的环境，由top的输出结果可以发现你，系统同时间有非常多的进程在运行中,只是绝大部分进程都在休眠中。如果所有程序都被唤醒，系统应该先执行哪个程序。此时就要考虑进程的优先执行序(Priiority)与CPU排程。
  CPU排程指的是每支进程被CPU运作的演算规则，而例行性工作排程则是将某支程序安排在某个时间再交由系统执行。CPU排程与操作系统较具有相关性。


    1.Priority与Nice值
    我们知道CPU一秒钟可以执行多达数G的微指令次数，透过核心的CPU排程可以让各进程被CPU所切换运作，因此每个进程在一秒钟内或多或少都会被CPU执行部分脚本。如果进程都是集中在一个队列中等待CPU的运作，，而不具有优先级之分，或导致一些需要紧急完成的任务必须等待很长的时间才能运行，一些需要I/O等其他资源的进程占用的时间又太多。
    Linux给予进程一个所谓的【进程执行序(priority,PRI)】，这个PRI值越低代表越优先执行的意思。不过这个PRI值是由核心动态调整的，用户无法直接调整PRI。
    PRI(new)=PRI(old)+NI
    Nice可以影响PRI，但是最终的PRI仍是要经过系统分析才会决定。Nice可以是负值，nice为负值时，那么该进程就会降低PRI值，亦即会变得较优先被处理。

    nice值可以调整的范围为-20~19；
    root可随意调整自己或他人进程的nice值，范围也是-20~19；
    一般使用者仅可调整自己进程的nice值，且范围仅为0~19（避免一般用户抢占系统资源）；
    一般使用者仅可将nice值越调越高。
    
    如何给予进程nice值：
    a.一开始执行程序就立即给予一个特定的nice值：用nice指令；
    b.调整某个已经存在的PID的nnice值：用renice指令。

    a.nice：新执行的指令即给予新的nice值
    nice [-n 数字] command
    -n：后面接一个数值，数值的范围-20~19。

    b.renice：已经存在进程的nice重新调整
    renice [number] PID


  16.3.4系统资源的观察
  除了系统的进程之外，我们还必须就系统的一些资源进行检查。top可以。

    1.free：观察内存使用情况
    free [-b|k|m|g|h] [-t] [-s N -c N]
    选项与参数：
    -b：直接输入free时，显示的单位时Kbytes，当然也可以使用其他单位，此时就使用其他字母
    -t：在输出的最终结果，显示物理内存与swap的总量
    -s：可以让系统每几秒钟输出一次，不间断的一直输出的意思。对于系统观察很有效。
    -c：：与-s同时处理，让free列出几次的意思。

     free：
     total    used    free    shared    buff/cachhe    available
     total是总量，used是已被使用的量，free则是剩余可用的量，后面的buff/shared/cached则是在已被使用的量当中，用来作为缓冲及快取的量，这些用量在系统比较忙碌的时候，可以被释放而继续利用，因此后面就有一个available（可用的）数值。
     cache是块取的意思，当我们读取一些文件时，还会将保存在内存当中，但是，不会在我们关闭文件时将这些内存写入到硬件，或是将这些数据从内存中删掉。快取是为了等待下次读取时更快的取出。
     Swap最不要被使用到，一旦超过20%，最好考虑购买更大容量的内存条。


     2.uname：查询系统与核心相关信息
     uname [-asrmpi]
     选项与参数：
     -a：所有系统相关的信息，包括底下的数据都会被列出来
     -s：系统核心名称
     -r：核心的版本
     -m：本系统的硬件名称
     -p：CPU的类型，与-m类似，只是显示的是CPU的类型
     -i：硬件的平台

      3.uptime：观察系统启动时间与工作负载
      这个指令就是显示出目前系统已经开机多久的时间，以及1,5,15分钟的平均负载。
      
      4.netstat：追踪网络或插槽文件(socket file)：
      netstat比较常用在网络的监控方面，不过，在进程管理方面也是需要了解的。
      netstat的输出分为两大部分，分别是网络与系统自己的进程相关性。
      netstat -[atunlp]
      选项与参数：
      -a：将目前系统上所有的联机、监视、Socket数据都列出来；
      -t：列出tcp网络封包的数据；
      -u：列出udp网络封包的数据；
      -n：不以进程的服务名称，以port number来显示；
      -l：列出目前正在网路监听的服务；
      -p：列出该网路服务的进程PID；

       可以看到互联网联机情况的部分：
       Proto    Recv-Q    Send-Q    Local Address    Foreign Address    State
       Proto：网络的封包协议，主要分为TCP和UDP封包。
       Recv-Q：非由用户程序链接到此socket的复制的总bytes数；
       Send-Q：非由远程主机传送过来acknowledged的总bytes数；
       LocalAddress：本地端的IP:Port情况；
       ForeignAddress：远程主机的IP:Port情况；
       State：联机状态，主要有建立(ESTABLISED)即监听(LISTEN)；

       本机的socket file输出字段有：
       Proto：一般是UNIX；
       RefCnt：连接到此socket的进程数量；
       Flags：联机的旗标；
       Type：socket存取的类型。主要有确认联机的STREAM与不许确认的DGEAM两种；
       State：若为CONNECTED表示多个进程之间已经联机建立；
       Path：连接到此socket的相关程序的路径，或者有相关数据输出的路径。


       4.dmesg：分析核心产生的讯息
       系统在开机的时候，核心会去侦测系统的硬件，硬件是否会被捉到，就与这个侦测有关。但是这些侦测是会被飞速显示出来，所以我们使用dmesg。
       所有核心侦测的讯息，不管是什么时候的，只要是核心产生的讯息，都会被记录到内存中的某个保护区段。dmesg这个指令就能够将该区段的讯息读出来。因为讯息是在太多了，所以执行时可以加入这个管线指令【| more】来使画面暂停。
       dmesg | more

       5.vmstat：检测系统资源变化
       如果你想要动态地了解一下系统资源的运行，就看可以使用vmstat。vmmstat可以检测【CPU/内存/磁盘I/O状态】等，如果你想要了解一个繁忙的系统到底哪个环节最雷人，可以使用vmstat分析。
       vmstat [-a] [延迟[总计检测次数]]  cpu/内存等信息
       vmstat [-fs]                    内存相关
       vmstat [-S 单位]                设置显示数据单位
       vmstat [-d]                     与磁盘有关
       vmmstat [-p 分区]                与磁盘有关
       选项与参数：
       -a：使用inactive/active替换buffer/cache的内存输出信息；
       -f:开机到目前为止，系统复制(fork)的进程数；
       -s：将一些事件（启动至目前为止）导致的内存变化情况列表说明；
       -S：后面接单位，数据显示的单位；
       -d：列出磁盘的读写总量的统计表；
       -p：后面列出分区，可显示该分区的读写总量的统计表。
       
       利用vmstat甚至可以执行跟踪。可以vmstat 5　这样就可以５秒跟新一次，且无穷跟新。除非你结束或停止它。
procs -----------memory---------- ---swap-- -----io---- -system-- ------cpu-----
 r  b   swpd   free  inact active   si   so    bi    bo   in   cs us sy id wa st
 1  0      0 227948 221616 265444    0    0   190    28   69  152  1  1 98  0  0
　　　　　
　　　　a.进程字段(procs)的项目分别是：
         r：等待运行中的进程数量
         b：不可被唤醒的进程数量
       
       b.内存字段(memory)项目分别是：
         swpd：虚拟内存被使用的量
	 free：未被使用的量
	 buff：用于缓冲存储器
	 cache：用于高速缓存
	 
       c.内存交换分区(swap)的项目分别为：
         si：由磁盘将进程取出的容量
	 so：由于内存不足而将没用到的进程写入到磁盘的swap的容量
         
       d.磁盘读写(I/O)的项目分别是：
         bi：由磁盘读入的区块数量
	 bo：写入到磁盘中的区块数量
	 
       e.系统(system)的项目分别是：
         in：每秒被中断的进程次数
	 cs：每秒执行的事件切换次数
	 
       f.CPU的项目分别是：
         us：非内核层的CPU使用状态
	 sy：内核层所使用的CPU状态
	 id：闲置的状态
	 wa：等待I/O所耗费的CPU状态
	 st：被虚拟机(virtual machine)所使用的CPU状态（2.6.11以后才支持）




16.4 特殊文件与进程
       
       
