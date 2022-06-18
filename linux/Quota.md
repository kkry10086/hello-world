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
    使用RAID1+0与RAID0+1的不同:
    因为先用RAID1在使用RAID0,而RAID0时数据是不会倍增的,而RAID1时
    根据磁盘颗粒数量n,增长n倍.
    此时a会通过RAID0(m),此时数据大小不变,然后使用RAID1,此时所有的数据均变为na,所有
    的数据都有了n个备份.
    而先RAID0在使用RAID1.此时RAID1会变成na,在通过RAID0数据不变.也就是说只要RAID1这一
    层的数量n是相同的,数据就没有变.
    存储速率:
    RAID1+0最先经过RAID0所以数据存储速率变为m,之后经过RAID1
    数据存储速率变为m/n.反过来也是:RAID0+1计算后的速率也是m/n.
    但是这里m是分子,n是分母,此时只要分子尽量大,分母尽量小,存储速率就会比较快.
    而分母是RAID1的数量,备份时2份就足够了.所以m就要大点.


    d.RAID5:效能与数据备份的均衡考虑
    RAID5 至少需要三颗以上的磁盘才能够组成这种类型的磁盘阵列.这种磁盘阵列的和数据写入
    有点类似RAID0,不过每个循环的写入过程中(striping),在每颗磁盘还加入一个同位检查数据
    (parity),这个数据会记录其他磁盘的备份数据,用于当有磁盘损毁时的救援.
    每个循环写入时,都会有部分的同位检查码(parity)被记录起来,并且记录的同位检查码每次
    都记录在不同的磁盘,因此,任何一个磁盘损毁时都能够藉由其他磁盘的检查码来重建原本磁盘
    内的数据.由于有同位检查码,因此RAID5的总容量会是整体磁盘数量减一颗.当损毁的磁盘数
    量大于等于两颗时,这整组RAID5的资料就损毁了.因为RAID5预设仅能支持一颗磁盘的损毁情
    况.
    在读写性能上,RAID5的读取效能还不赖,近乎RAID0.但是写的效能就很一般,因为在写入RAID5
    的数据还得经过计算同位检查码(parity).由于还要计算检查码,所以写入的效能与系统的硬件
    关系较大.尤其当使用软件磁盘阵列时,同位检查码是透过CPU去计算而非专职的磁盘阵列卡,
    因此性能方面还需评估.
    另外由于RAID5仅能支持一刻磁盘损毁,因此,近来还发展了另外一种等级,就是RAID6,这个
    RAID6则使用两颗磁盘的容量来作为parity的储存,因此整体的磁盘容量就会少两颗,但是允
    许出错的磁盘数量就可以达到两颗了.也就是在RAID6的情况下,同时两颗磁盘损毁时,数据还
    是可以救回来.


    e.Spare Disk: 预备磁盘的功能:
    但磁盘阵列的磁盘损毁时,就得要将坏掉的磁盘拔除,然后换掉一颗新的磁盘.换成新磁盘并且
    顺利启动磁盘阵列后,磁盘阵列就会开始主动的重建(rebuild)原本坏掉的那颗磁盘数据到新
    的磁盘上.这就是磁盘阵列的优点.不过我们还是得要动手拔插硬盘,除非你的系统有支持热
    拔插,否则通常得要关机才能这么做.
    为了让系统可以实时的在坏掉硬盘时主动的重建,因此就需要预备磁盘(spare disk)的辅助.
    所谓的spare disk 就是一颗或多颗没有包含在原本磁盘阵列等级中的磁盘,这颗磁盘平时不
    会被磁盘阵列所使用,当磁盘阵列有任何磁盘损毁时,则这颗spare disk会被主动的拉进磁盘
    阵列中,并将坏掉的那颗磁盘移出磁盘阵列.然后立即重建数据系统.如此你的系统则可以永保
    安康.若有热拔插就更完美了,直接换掉坏的.


    f.磁盘阵列的优点
      1.数据安全与可靠性:指的并非网络信息安全,而是当硬件(这里指硬盘)损毁时,数据是否还能
        够安全的救援或使用之意.
      2.读写效能:例如RAID0可以加强读写效能,让你的系统I/O部分得以完善.
      3.容量:可以让多颗磁盘组合起来,故单一文件系统可以有相当大的容量.

    

  14.2.2 software,hardware RAID
    磁盘阵列又分为硬件与软件.所谓的硬件磁盘阵列(hardware RAID)是透过磁盘阵列卡来达成
    数组的目的.磁盘阵列卡上面有一块专门的芯片在处理RAID的人物,因此在效能方面会比较好.
    在很多任务,磁盘阵列并不会重复消耗原本系统的I/O总线,理论上效能会较佳,理论上效能会
    较佳.此外目前一般的中高阶磁盘阵列卡都支持热拔插,亦即在不关机的情况下抽换损坏的磁
    盘,对于系统的复原与数据的可靠性方面非常的好用.
    
    不过,好的磁盘阵列卡很贵,便宜的在主板上[附赠]的磁盘阵列功能可能不支持某些高阶功能.
    此外,操作系统也必须拥有磁盘阵列卡的驱动程序.
    
    因此就发展出利用软件来仿真磁盘阵列的功能,这就是所谓的软件磁盘阵列(software RAID).
    软件磁盘阵列主要是透过软件来仿真数组的任务,因此会损耗较多的系统资源,比如说CPU的运
    算与I/O总线的资源等.不过现在个人计算机已经够快了,所以可以试试.


    Centos提供的软件磁盘阵列为mdadm这套软件,这套软件会以partition 或disk为磁盘的单位.
    也就是说你不需要两颗以上的磁盘,只要两颗以上的分区槽(partition)就能够设计你的磁盘阵
    列了.此外,mdadm支持刚刚我们面前提到的RAID0/1/5,spare disk 等.而且提供的管理机制还
    可以达到类似热拔插的功能呢个,可以在线(文件系统正常使用)进行分区槽的抽换.

    另外,必须知道的是,硬件磁盘阵列在Linux底下看起来就是一颗实际的大磁盘,因此硬件磁盘
    阵列的装置文件名为/dev/sd[a-p],因为使用到SCSI的模块之故.至于软件磁盘阵列则是系统
    仿真的,因此使用的装置文件名是系统的装置文件,文件名为:/dev/md0,1....
    两者的配置文件名并不相同.

    tips:intel的南桥附赠的磁盘阵列功能,在windows底下似乎是完整的磁盘阵列,但是在Linux
    底下则被视为是软件磁盘阵列的一种.因此如果你有设定过Intel的南桥芯片磁盘阵列,那么
    Linux底下反而还会是/dev/md126/7等等装置文件名,而他的分区草竟然是/dev/md126p1,
    /dev/md126p2... 之类的.

     

  14.2.3 软件磁盘阵列的设定
  centos使用mdadm这个指令：
  mdadm --detail /dev/md0
  mdadm --create /dev/md[0-9] --auto=yes --level=[015] --chunk=NK \
  --raid-devices=N --spare-devices=N /dev/sdx /dev/hdx

  --create:为建立RAID的选项
  --auto=yes: 决定建立后面接的软件磁盘阵列装置，亦即/dev/dm0,/dev/md1。
  --chunk=NK：决定这个装置的chunk大小，也可以当成stripe大小，一般是64K或512K。
  --raid-devices=N：使用几个磁盘（partition）作为磁盘阵列的装置。
  --spare-devices=N：使用几个磁盘作为备用（spare）装置。
  --level=[015]：设定这组磁盘阵列的等级。支持很多，不过建议只要用0,1,5。
  --detail：后面所接的那个磁盘阵列装置的详细信息。

  a.格式化与挂载使用RAID
    因为涉及到xfs 文件系统的优化。我们这里的参数
    stripe(chunk)容量为256K，所以su=256k
    共有4颗组成RAID5，因此容量少一颗，所以sw=3
    有上面两项计算出数据宽度为256K*3=768K
    此时应该是
    mkfs.xfs -f -d su=256K,sw=N-1 -r extsize=(N-1)*256k /dev/md0
    这里extsize是实时运作区的extent区块的大小,当有文件要被建立的时候,就会先防止在这
    个区块内,等到分配完毕,再写入到data section的inode与block.而每次要将数据写入raid
    中,由于RAID5的特性,都会写入所有的n颗磁盘,所以就相当于写入n*stripe的整数倍的数据.
    因此,extent的大小就要等于n*stripe.假设要写入m个extent,就要写入m*n*stripe的数据.



   14.2.4 仿真RAID错误的救援模式
   mdadm --manage /dev/md[0-9] [--add 装置] [--remove 装置] [--fail 装置]
   --add   ：会将后面的装置加入到md中。
   --remove：会将后面的装置由这个md中移除。
   --fail  ：会将后面的装置设定为出错的状态。

     a.设定磁盘为错误（fail）
       mdadm --manage /dev/md[0-9] --fail /dev/sdan
     b.把/dev/sdan 移除在加回去
       mdadm --manage /dev/md[0-9] --remove /dev/sdan
       mdadm --manage /dev/md[0-9] --add /dev/sdan


  14.2.5 开机自启动RAID并自动挂载
    现在的distribution大多会自己搜寻装置（/dev/sda..）然后在开机的时候给予设定好所需
    要的功能不过还是修改配置文件比较好。
    文件位置：  /etc/mdadm.conf.
    ARRAY /dev/md0  UUID=......

    之后在/etc/fstab写上相应的配置。
    这里会有两个UUID，一个是blkid的，另一个是mdadm --details /dev/md0。不要搞错。



  14.2.6 关闭软件RAID（重要！）
    除非你以后需要用到这个md0，否则就一定要删掉。关掉它，是因为它使用的是我们系统的
    磁盘分区槽，如果只是将/dev/md0卸载掉，然后忘记关掉RAID。结果就是你未来重新分区
    /dev/sdaN时可能出现一些莫名其妙的问题。所以一定要关闭。
    1.先卸载挂载点；
    2.删掉/dev/fstab里面的挂载信息；
    3.覆盖掉RAID的metadata以及XFS的superblock，才关闭/dev/md0；
    4.dd if=/dev/zero of=/dev/md0 bs=1M count=50
    5.mdadm --stop /dev/md0（就关闭掉了）
    6.将磁盘里面备份的RAID的相关数据删除掉。
    7.dd if=/dev/zero of=/dev/sda[0-128] bs=1M count=10
    8.cat /proc/mdstat 此时数据就会消失
    9.将/etc/mdadm.conf的相关数据删掉。
    
    上面7的dd是用来将磁盘中备份的RAID的相关数据删除掉的，因此，如果你只是将配置文件移
    除，同时关闭了RAID，但是分区草并没有重新规划果，那么重新启动过后，系统还是会将这颗
    磁盘阵列建立起来，只是名称改变了。




14.3 逻辑滚动条管理员（Logical Volume Maneger）
  LVM的重点是[可以弹性的调整filesystem的容量!]而并非在于效能与数据保全上面.LVM可以
  整合多个实体partition在一起,让这些partitions看起来就像是一个磁盘一样!而且,还可以
  在未来新增或移除其他的实体partition到这个LVM管理的磁盘当中.

  14.3.1 什么是LVM:PV,PE,VG,LV的意义
    LVM的全名是:Logical Volume Manager.中文翻译:逻辑滚动条管理员.之所以成为[滚动条]
    可能是因为可以将filesystem像滚动条一样伸长或缩短.LVM的作法是将几个实体的
    partitions(或disk)透过软件组合成为一块看起来是独立的大磁盘(VG),然后将这块大磁盘
    再经过分区成为可使用分区槽(LV),最终就能够挂载使用了.但是为什么这样的系统可以进行
    filesystem的扩充或缩小呢?这与一个称为PE的项目有关.

    a.Physical Volume,PV,实体滚动条
    我们实际的partition(或disk)需要调整系统标志符(system ID)成为8e(LVM 的标志符),
    然后再经过pvcreate的指令将它转成LVM最底层的实体滚动条(PV),之后才能够将这些PV
    加以利用.

    b.Volume Group,VG,滚动条群组
    所谓LVM大磁盘就是将许多PV整合成这个VG的东西.所以VG就是LVM组合起来的大磁盘.那么
    这个磁盘最大可以到多少容量?32为的linux系统时,lv最大仅能支持65534个PE而以,若使用
    的PE为4MB的情况下,最大容量仅能达到:65534*4/(1024)=256GB差不多.而使用64为的linux
    就几乎没有容量限制.


    c.Physical Extent,PE,实体范围区块
    LVM预设使用4MB的PE区块,而LVM的LV在32位系统上最多仅能含有65534个PE(lvml的格式).
    因此预设LVM的LV会有4M*65534/(1024M/G)=256G.这个PE是整个LVM最小的储存区块.也
    就是说,我们的文件资料都是藉由写入PE来处理的.简单的说:PE就类似文件系统里面的
    block大小.


    d.Logical Volume,LV,逻辑滚动条
    最终的VG还会被切成LV,这个LV就是最后可以被格式化使用的类似分区槽的东西.那么
    LV是否可以随意制定大小?不可以.既然PE是整个LVM的最小储存单位,那么LV的大小就
    与在此LV内的PE总数有关.为了方便用户利用LVM来管理系统,因此LV的装置文件名通常
    执行为[/dev/vgname/lvname]的样式。
    LVM是如何做到可弹性的变更filesystem的容量？其实就是透过交换PE来进行数据转移。
    将原本LV内的PE转移到其他装置中以降低LV容量，或将其他装置的PE加到此LV中以加大
    容量。



    e.实作流程
    透过PV，VG，LV的规划后，再利用mkfs就可以将你的LV格式化成为可以利用的文件系统。而
    且这个文件系统的容量在未来还能够进行扩充或减少，而且里面的数据还不会被影响到。
    流程看鸟哥的14.3

    那么我的数据写入这个LV时，到底是怎么写入硬盘的。
    有两种机制：
      。线性模式（linear）：加入我将/dev/sda1,/dev/sdb1这两个partition加入到VG当
        中，并且整个VG只有一个LV时，那么所谓的线性模式就是：当/dev/sda1的容量用完之
	后，/dev/sdb1的硬盘才会被使用到。


      。交错模式（triped）：就是将一个数据拆成两部分，分别写入/dev/sda1与/dev/sdb1
        的含义。类似RAID0。


    基本上，LVM的最主要用处是在实现一个可以弹性调整容量的文件系统上，而不是在建立一个
    效能为主的磁盘上，所以我们应该利用的是LVM可以弹性管理整个partition大小的用途。
    因此，LVM默认的读写模式是线性模式。如果你是用triped模式，当你的一个partition
    损坏时，所有LVM的数据都会损坏。所以建议不要。



  14.3.2 LVM 实作流程
    LVM 需要核心有支持且需要lvm2这个软件。好在，Centos与其他较新的distributions
    已经预设将lvm的支持与软件都安装妥当了。
    接下来就是生成分区：使用fdisk/gdisk， 总共四个，ID为8e，因为有些系统可能侦测不到
    partition，所以要该为8e。

    1.PV阶段
      PV有关的指令：
      。pvcreate：讲实体partition建立成PV
      。pvscan：搜寻目前系统里面任何具有PV的磁盘
      。pvdisplay：显示出目前系统上面的PV状态
      。pvremove：将PV属性移除，让该partition不具有PV属性


    2.VG阶段
      VG有关的指令：
      。vgcreate：即是主要建立VG的指令。
      。vgcan：搜寻系统上面是否有VG存在
      。vgdisplay：显示目前系统上面的VG状态
      。vgextend：在VG内增加额外的PV
      。vgreduce：在VG内移除PV
      。vgchange：设定VG是否启动（active）
      。vgremove：删除一个VG

      pv的名字就是partition的名字，VG就可以自己取。
      
      vgcreate [-s N[mgt]] VG名称  PV名称
      -s：后面接PE的大小（size）,单位可以是mgt


    3.LV 阶段
      。lvcreate：建立lv
      。lvscan：查询系统上面的lv
      。lvdisplay：显示系统上面的lv状态
      。lvextend：在lv里面增加容量
      。lvreduce：在lv里面减少容量
      。lvremove：删除一个lv
      。lvresize：对lv进行容量大小的调整

      lvcreate [-L N[mgt]] [-n lv名称] VG名称
      lvcreate [-L N] [-n lv名称] VG名称
      -L：后面接容量，容量的单位可以是M，G，T等，大小最小是PE，或者是PE的整数倍。
      -l：后面可以接PE的个数，而不是数量。若要这么做，得要
      -n：后面接的就是lv的名称

      生成lv partition后，就可以针对lv来处理。VG的名称是kkryvg,而lv的名称必须使用
      全名。亦即/dev/kkryvg/kkry1才行。
      lv可以看成是一个partition。之后格式化，挂载就可以使用。
      文件格式化：
      mkfs.xfs /dev/kkryvg/kkry1


  14.3.3 放大LV容量
    LVM的最大特色就是弹性调整磁盘容量。放大文件系统时，需要一下这些流程：
    1.VG阶段需要有剩余的容量：因为需要放大文件系统，所以需要放大LV，但是若没有多的
      VG容量，那么更上层的LV与文件系统就无法放大。因此你得要用尽各种方法来产生多的
      VG容量才行。一般来说VG容量不够，最简单的方法就是加硬盘，然后用pvcreate,
      vgentend增加到VG。


    2.LV阶段产生更多的可用容量：如果VG的剩余容量足够了，就可以利用lvresize这个指令
      来将剩余的容量加入到所需要的lv装置内。
      
    3.文件系统的放大：我们的linux实际使用的其实不是lv，而是lv这个装置里面的文件系统。
      所以一且还是要以文件系统为依归。目前可以放大的文件系统有XFS以及EXT家族。缩小
      的仅有EXT家族，目前XFS文件系统并不支持文件系统的容量做小。
      xfs_growfs 指令可以放大XFS文件系统。


    最后一个步骤非常重要，整个文件系统在最初格式化的时候就建立了inode/block/
    superblock等信息，要改变这些信息很难。不过因为文件系统格式化的时候建置的是过个
    blockgroup，因此我们可以透过在文件系统当中增加blockgroup的方式来增减文件系统的
    量。而增减block group就是利用xfs_growfs。


    14.3.4 使用LVM thin Volume 让lvm动态自动调整磁盘使用率

    想想一个情况，你有个目录未来会使用到大约5T的容量，但是目前你的磁盘仅有3T，问题是，
    接下来的两个月你的系统还不会超过3T的容量，不过你想要让用户知道，就是他最多有5T可
    以使用。而且在一个月内你确实可以将系统提升到5T以上的容量。你又不想在提升容量后才
    放大到5T。这时可以考虑【实际用多少才分配多少容量给LV的LVM Thin Volume】功能。
    
    另外，再想象一个环境，如果你需要有3个10GB的磁盘来进行某些测试，问题是你的环境仅有
    5GB的剩余容量，在传统的LVM环境下，LV的容量是一开始就分配好的，因此你当然没有办法
    在这样的环境中产生出3个10GB的装置。而且那个10GB的装置其实每个实际使用率都没有超过
    10%，也就是总用量仅会到3GB而已。所以就可以使用LVM thin Volume

    LVM thin Volume的概念：
      先建立一个可以实支实付、用多少容量才分配实际写入多少容量的磁盘容量储存池
      （thin pool），然后再由这个thin pool去产生一个【指定要固定容量大小的LV装置】。
      在LV上，虽然你会看到【宣告上，他的容量可能由10GB，但实际上，该装置用到多少容量
      时，才会从thin pool去实际取得所需要的容量】。当然，在所有由thin pool 所分配
      出来的LV装置中，总实际使用量绝不能超过 thin pool 的最大实际容量。

      开始实作：
      1.由VB 剩余容量去取出1GB来做出一个名为VBpool的thin pool LV装置，这就是所谓的
        磁盘容量储存池（thin pool）。

      2.由VB内的VBpool产生一个名为VBthin1的10GB LV装置

      3.将此装置实际格式化为xfs文件系统，并且挂载于/srv/thin目录内。

      。建立一个thin pool装置：
        lvcreate -L 1G --thinpool kkryvg/kkrypool
	lvcreate -L 1G -T kkryvg/kkrypool


      。建立由thinpool 产生的 lv装置
        lvcreate -V 10G -n kkrythin1 --thinpool kkrypool kkryvg
        lvcreate -V 10G -T kkryvg/kkrypool -n kkrythin1


      。kkrythin1格式化，挂载。
        mkfs.xfs /dev/kkryvg/kkrythin1

      这里必须非常小心，虽然一个磁盘可以仿真出很多容量，但是，实际上可用的容量就是实际
      磁盘储存池内的容量。如果超过该容量，会导致thin pool 里面的内容损毁。
	
	

  14.3.5 LVM的 LV 磁盘快照
    LVM除了可以改变lv的大小，还有一个重要的能力，那就是LV磁盘的快照（snapshot）：
    快照就是：将当时的系统信息记录下来，就好像照相机一样。未来若有任何资料更改了，则
    原始资料会被搬移到快照区，没有被更改的区域则由快照区与文件系统共享。

    说明一下：最初建置LV磁盘快照区的时候，LVM会预留一个区域作为数据存放处。此时快照区
    没有任何数据。而快照区与系统区共享所有的PE数据，因此你会看到快照区的内容与文件系统
    是一模一样的。等到系统运作一阵子后，假设A区域的数据被更改了，则更改前系统会将该区域
    的数据移动到快照区。此时系统区的A区域就不会与快照区共享，此时快照区就看不到A区域的
    新的内容了。还有其他的区域还在与快照区文件系统共享。

    LVM的磁盘快照是很棒的【备份工具】，因为快照缩占用的容量非常小。而且能将当时的文件
    系统备份下来。

    由于快照区与原本的LV共享PE区块。因此，
    快照去与被快照的LV必须要在同一个VG里面。（顺带一提，可以使用thin pool的功能来
    制作快照。但是使用限制非常多。包括最好要在同一个thin pool 内的原始LV磁盘，如果
    为非thin pool 内的原始LV磁盘快照，则该磁盘快照不可以写入，以及LV磁盘要设定成
    只读才行。同时使用thin pool做出来的快照，通常是不可启动（inactive）的预设情况，
    启动柜又有点麻烦。）所以不建议现在做。


    针对传统Lv磁盘进行快照的建置，大致流程：
    。预计被拿来备份的原始LV为/dev/VG/LV
    。使用传统方式快照建置，原始LV为/dev/VG/LV，快照名称为kkrysnap1,容量为VG的剩余
      容量

     lvcreate -s -l chunknum -n snapname besnaplvname
     mount -o nouuid /dev/VG/snap  挂载点
     这里直接挂载就行，不用格式化。但是要加-o nouuid，因为此时两个partition的UUID是
     相同的，会报错。


    利用快照恢复源系统：
    首先注意：你也好复原的数据量不能够高于快照区所能负载的实际容量。由于原始数据会被
    搬移到快照区，如果你的快照区不够大，若原始资料被更改的实际数据量比快照区大，那么
    快照区当然容纳不了，此时快照区功能会失效。


    利用快照区将原本的filesystem备份，我们使用xfsdump
    xfsdump -l 0 -L lvml -M lvml -f /home/lv.dump /srv/snapshot1
    因为快照区数据要搬移到原来的数据区，会导致自己本身也有修改，所以要先备份。
    还原是要格式化的，所以要先备份。格式化即意味着要先umount，在格式化，在挂载上去。
    所以快照区也是要卸载的再加上删除lv装置，否则就无法作为数据区的快照区（我就有过几
    次的类似这样的经历）。

    利用快照区进行各项练习与测试的任务，再以原系统还原快照：
      我们将原本的kkrylv当作备份数据，然后将kkrysnap1当作实际在运作中的数据，任何
      测试的动作都在kkrysnap1这个快照区当中测试，那么当测试完毕要将测试的数据删除
      时，只要讲快照区扇区即可。而要复制一个kkrylv的系统，再作另外一个快照区即可。

      这个方法的确有趣：因为修改快照区并不会使得双方的共享文件区域减少，而且，卸载，
      删除一个快照区，也不会对原本的数据产生影响。这样就只需要删除快照区的数据即可。
      而用原来的方式就要多几步操作，卸载数据区，删除数据区，在恢复，最后恢复数据。

     当然实际如何，还是要我们亲自去尝试一下。


     如何移除系统内的LVM：
     1.先卸载系统上面的LVM文件系统（包括快照与所有LV）
     2.使用lvremove移除LV
     3.使用vgchange -a n VGname让VGname这个VG不具有Active的标志
     4.使用vgremove移除VG
     5.使用pvremove移除PV
     6.使用g/fdisk修改system ID回来。



      
	
    
 
    
  