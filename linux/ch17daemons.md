                      chapter17 daemons

17.1 什么是daemon与服务(service)
【服务】是【常驻在内存中的程序，且可以提供一些系统或网络功能】。而服务一般的英语说法是【service】。
daemon的字面意思是守护神。简单的说，系统为了某些功能必须要提供一些服务，这个服务就成为service。但是service的提供总是需要程序的运行。为了达成这个执行service的程序就被我们称为daemon。举例来说：达成循环型例行性工作排程服务的程序的crond就是daemon的一种。

daemon既然是一只程序执行后的程序，那么daemon所处的原本程序通常是如何命名的？
无论如何这些服务的名称被建立之后，被挂上Linux使用时，通常在服务的名称之后会加上一个d。例如：
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
  S为启动该服务，SS是数字，为启动的顺序。由于有SXX的设定，因此开机时可以【依次执行】所有需要的服务，同时也能解决相依服务的问题。
  
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
  






 