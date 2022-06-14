14.1 磁盘配额（Quota）的应用与实操

  14.1.1什么是Quota
   a.Quota的一般用途：
     比较常用的情况：
     。针对WWW server，例如每个人的网页空间的容量限制
     。针对mail server，例如每日个人的邮件空间限制
     。针对 file server ，例如每个人最大的可用网络硬盘空间

     针对Linux系统主机上面的设定：
     。限制某一群组所能使用的最大磁盘配额（使用群组限制）
     。限制某一用户的最大磁盘配额（使用用户限制）
     。限制某一目录（directory,project）的最大磁盘配额

   b.Quota的使用限制：
     。在EXT 文件系统家族仅能针对整个filesystem：
       EXT文件系统家族在进行quota限制的时候，仅能针对整个文件系统来进行设计，无法针对
       某个单一的目录来设计它的磁盘配额。因此，如果你逍遥使用不同的文件系统进行quota
       时，请先搞清楚该文件系统支持的情况狂。

     。核心必须支持quota：
       Linux核心必须有支持quota的功能

     。只对一般身份使用者有效：
       例如root是不能设定quota的

     。若启用SELinux，非所有目录均可设定quota。
       SELinux这个核心功能会加强某些细部的权限控制。由于担心管理员不小心设定错误，因
       此，预设情况下，quota仅能针对/home进行设定。除非解开SELinux限制。


   c.Quota的规范设定项目：
     对XFS filesystem 的限制项目主要分为：
     
     。分别针对用户、群组或个别目录（user,groupm,project）

     。容量限制或文件数量限制（block 或 inode）
       限制inode用量：可以管理使用者可以建立的文件数量
       限制block涌浪：管理用户此磁盘容量的限制。

    d.柔性劝导与硬性规定（soft/hard）
      。hard：表示使用者的用量绝对不会超过这个限制值，以上面的设定为例，用户所能使用
      的磁盘容量那个绝对不会500Mbytes，若超过这个值，系统会锁住该用户的磁盘使用权。
      
      。soft：表示使用在低于soft限值时，可以正常使用磁盘，但若是超过soft且低于hatd
      的限制，每次用户登入系统时，系统会主动发出磁盘即将爆满的警告讯息，且会给予一个
      宽限时间。不过，若使用者在宽限时间倒数期间就将容量再次降低到soft限值之下，则宽
      限时间会停止。

    e.会倒数计时的宽限时间：
      这个宽限时间只有在用户的磁盘用量介于soft到hard之间时，才会出现。由于到了hard
      的限值时，用户的磁盘使用权可能会被锁住，为了让用户注意到磁盘配额的问题，因此
      设计了soft。当磁盘用量介于soft与hard之间，系统会给予警告，但也会给一段时间让用
      户自行管理磁盘。如果在宽限时间内不进行磁盘管理，那么soft限制值会即刻取代hard的
      限值来作为quota的限制。


  14.1.2一个XFS 文件系统的Quota实作范例：
    自己跟着教材学（鸟哥）


  14.1.3 实作Quota流程-1：文件系统的支持与观察
    不要在根目录下进行quota设计。因为文件系统会变得太复杂。
    由于XFS 文件系统的quota似乎是在挂载的时候就宣告了，因此无法使用remount来重新启动
    quota功能。一定要写入/etc/fstab当中，或者在初始初始挂载过程中加入这个项目，否则
    不会生效。

    /dev/....  /home    xfs   defaults,usrguota,grpquota 0 0
    之后重新挂载。强调：在挂载之前，一定要mount -a 来测试一下是否有问题。否则后果
    很严重，我就是这样。
    quota 限制的项目主要有三项：
    。uquota/usrquota/quota：针对使用者账号的设定
    。gpquota/grpquota：针对群组的设定
    。pquota/prjquota：针对单一目录的设定，但是不可与grpquota同时存在


  14.1.4 实作Quota流程-2：观察Quota报告资料
    xfs_quota -x -c "指令" [挂载点]
    -x：专家模式，后续才能够加入-c的指令参数
    -c：后面加的就是指令。

    指令：
      print：单纯的列出目前主机内的文件系统参数等资料；
      df   ：与原本的df一样的功能，可以加上 -b -i -h 等；
      report：列出目前的quota项目，有-ugr(usr/group/project)以-bi等资料；
      state：说明目前支持quota的文件系统的信息，有没有启动相关项目等。


  14.1.5 实作Quota流程-3：限制值设定方式
    xfs_quota -x -c "limit [-ug] b[soft|hard]=N i[soft|hard]=N name " 挂载点
    xfs_quota -x -c "timer [-ug] [-bir] Ndays"

    limit：实际限制的项目，可以针对usr/group 来限制，限制的项目有
           bsoft/bhard：block的soft/hard限制值，可以加单位
	   isoft/ihard：inode的soft/hard限制值
	   name：就是用户/群组的名称
	   
    timer：用来设定grace time的项目，也是可以针对user/group以及block/inode设定。


  14.1.6 实作Quota流程-4：project 的限制（针对目录的限制）（Optional）
    a.修改/etc/fstab的文件系统支持参数
      defaults,usrquota,prjquota

    b.规范目录、项目名称（project）与项目ID
      目录的设定比较奇怪，他必须设定一个【项目名称，项目标识符】来规范才行。
      而且还需要用到两个配置文件:/etc/projects 和 /etc/projid
      指定名称与标识符方式：
      
      指定项目标识符与目录对应在/etc/projects
      echo "11:/home/myquota" >> /etc/projects

      规范专案名称与标识符对应在/etc/projid
      echo "myquotaproject:11" >>/etc/projid

      初始化专案名称：
      xfs_quota -x -c "project -s myquotaproject"

    c.实际设定规范与测试
      xfs_quota -x -c "limit -p bsoft=450M bhard=500M myquotaproject" /home


    如果以后要对某个目录进行限制，那么就修改/etc/projects,/etc/projid设定一下规范就
    行了。


  14.1.7 XFS quota的管理与额外指令对照表
    加入你需要暂停quota的限制，或是重新启动quota的限制时：

    。disable：暂时取笑quota的限制，但其实系统还是在计算quota，只是没有管制而已。
    。enable：就是恢复到正常管制的状态中，与disable可以互相取消、启用。
    。off：完全关闭quota的限制，使用这个状态后你只有卸载在重新挂载才能够再次的启动
           quota。enable也没法恢复quota的管制。建议不要乱用，除非你要执行remove
	   的动作。
    。remove：必须要在off的状态下才能够执行的指令，这个remove可以【移除】quota的限
             制设定，例如要取消project的设定。使用remove需要将所欲的quota的设定
	     清除，所有的usr/grp/project。即在state看到所有都是off。

    xfs_quota -x -c "[disable|enable|off|remove] -up" /home


  14.1.8 不更改既有系统的quota实例
    使用ls -s 源 目的 将两个目录链接起来，这样，比较难以设定的目录就能够由于同步于
    源目录而做到配额。



14.2软件磁盘阵列（Software RAID）

  14.2.1 什么是RAID
    磁盘阵列全名是【Redundant Arrays of Inexpensive Disks,RAID】，容错式廉价磁盘
    阵列。RAID可以透过一个技术（软件或硬件），将多个较小的磁盘整合成一个较大的磁盘装
    置。而这个较大的磁盘工功能可不止是储存而已，它还具有保护数据的功能。这个RAID由于
    选择的等级（level）不同，而使得整合后的磁盘具有不同的功能。

    a.RAID-0（等量模式，stripe）：效能最佳
      这种模式如果使用相同型号与容量的磁盘来组成时，效果较佳。这种模式的RAID会将磁盘先
      切出等量的区块（名为chunk，一般可设定4K~1M之间），然后当一个文件要写入RAID时，该
      文件会根据chunk的大小切割好，之后再依序放到各个磁盘上面。由于每个磁盘都会交错的存
      放数据，因此当你的数据要放入RAID时，数据会被等量的放置到各个磁盘上面。
      举例来说，你有两颗磁盘组成RAID-0，当你有100MB的数据要写入时，每个磁盘会各被分配
      到50MB的储存量。
                     档案资料
                     |     |
		     |     |
	           diskA   diskB


      由于数据已经先被切割并且依序放置到不同的磁盘上面，因此每颗磁盘负责的数据量都降低
      了。照这样看，越多颗磁盘组成的RAID-0效能会越好，因为每颗负责的资料量就更低了。
      （其实就是用了两个硬盘）。
      只是使用此等级你必须要自行负担数据损毁的风险。
      假设RAID-0的某一颗磁盘损毁了，在RAID上面的所有数据都会遗失而无法读取。
      如果使用不同容量的磁盘来组成RAID-0时，当小容量的磁盘用完后，其他的数据就都会
      写入大容量的磁盘。

    b.RAID-1（映像模式，mirror）：完整备份
      这种模式也是需要相同的磁盘容量的，最好是一模一样的。如果是不同容量的磁盘组成
      RAID-1时,那么总容量将以最小的那一颗磁盘为主.这种模式主要是【让同一份数据，
      完整的保存在两颗磁盘上头】。
      举例来说：如果我有一个100MB的文件，且我仅有两颗磁盘组成RAID-1时，那么这两颗
      磁盘将会同步写入100MB到他们的储存空间。因此，整体RAID的容量几乎少了50%。
      RAID-1最大的优点就在于数据的备份。不过由于磁盘容量有一般用在备份，因此总容量
      会是全部磁盘容量的一半。而且写入效率不佳，要写入两次，虽然第二次不需要io总线。


    c.RAID1+0，RAID0+1
    RAID-0效能佳但是数据不安全，RAID则相反。所以有了RAID0+1或RAID1+0。
    含义：（1）先让两个磁盘组成RAID1；（2）将这两组RAID1在组成RAID0。这就是RAID1+0
    反过来RAID0+1，就是先RAID0再RAID1。这里有四颗磁盘，两组磁盘。
    

    


     
      