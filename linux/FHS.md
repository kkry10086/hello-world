FHS:filesystem hierarchy(等级) standard;

一、generalization:
style:
static,variable,shareable,unshareable;

--------------------------------------------------------
            |shareable(可分享)   |unshareable(不可分享)
-----------------------------------------------------------
static(不变)|/usr(软件存放处)    |/etc(配置文件)
            |/opt(第三方辅助软件)|/boot(启动和内核文件)
--------------------------------------------------------
variable    |/var/mail(用户邮箱) |/var/run(程序相关)
(可变动)    |/var/spool/newds    |/var/lock(程序相关)
            |(新闻组)            |
-----------------------------------------------------------


FHS针对目录树架构仅仅定义出三层目录下面应该放置什么数据而已。
/(root，根目录):与启动系统有关；
/usr(unit software resource):与软件安装与执行有关；
/var(variable):与系统运行过程有关。

二、tree of directory:
1. the meanings and contents of /

/ is the most important folder of the whole system.
since all folders derive from root.
因为不但所有的目录都是由根目录,同时根目录也与启动，还原，系统修复等操作有关。
因此/非常重要，所以FHS建议/不要放在较大的分区中。较大的分区即代表会存入越大的数据，
/就有更多的发生错误的的可能。

FHS标准建议:/所在分区应该越小越好，且应用程序所安装的软件(/usr)最好不要和根目录放在
同一分区，保持/越小越好。如此，不但性能最佳，根目录所在的文件系统也较不容易发生问题。
