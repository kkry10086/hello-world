                      chapter17 daemons

17.1 ʲô��daemon�����(service)
�������ǡ���פ���ڴ��еĳ����ҿ����ṩһЩϵͳ�����繦�ܡ���������һ���Ӣ��˵���ǡ�service����
daemon��������˼���ػ��񡣼򵥵�˵��ϵͳΪ��ĳЩ���ܱ���Ҫ�ṩһЩ�����������ͳ�Ϊservice������service���ṩ������Ҫ��������С�Ϊ�˴�����ִ��service�ĳ���ͱ����ǳ�Ϊdaemon��������˵�����ѭ���������Թ����ų̷���ĳ����crond����daemon��һ�֡�

daemon��Ȼ��һֻ������ִ�к��桹�ĳ�����ôdaemon������ԭ������ͨ������������ģ����������Щ��������Ʊ�����֮�󣬱�����Linuxʹ��ʱ��ͨ���ڷ��������֮������һ��d�����磺
at��atd��cron��crond���d����ľ���daemon����˼��

  17.1.1����System V �� init ������Ϊ��daemon����Ҫ����(Optional)
  �������������������ϵͳ����Ĺ���ʽ����ΪSysV��init�ű�����Ĵ���ʽ���༴ϵͳ���ĵ�һ֧���еĳ�����init��Ȼ��initȥ�������е�ϵͳ����Ҫ�ķ��������Ǳ��ط���û����������
  
  ������init�Ĺ�������м�����ɫ��
  a.������������ر���۲�ȷ�ʽ��
    ���еķ��������ű�ͨͨ������/etc/init.d/���£������϶���ʹ��bash shell script ��д�ɵĽű�������Ҫ�������رա������������۲춯̬ʱ������͸�����µķ�ʽ������
    ������/etc/init.d/deamon start
    �رգ�/etc/init.d/deamon stop
    ����������/etc/init.d/deamon restart
    ״̬�۲죺/etc/init.d/deamon status


  b.���������ķ��ࣺ
  init����ķ��������ݷ����Ƕ���������һֻ�ܹܳ���������Ϊ�����ࣺ
    ��������ģʽ(stand alone)����������������÷���ֱ�ӳ�פ���ڴ��У��ṩ�������û��ķ�����Ϊ����Ӧ�ٶȿ졣
    �ܹܳ���(super daemon)���������xinetd��inetd�������ܹܳ����ṩsocket��Ӧ��port��Ӧ�Ĺ�����û���û�Ҫ��ĳsocket��portʱ����Ҫ�ķ����ǲ��ᱻ�����ġ������û�Ҫ��ʱ��xinetd�ܹܲŻ�ȥ�������Ӧ�ķ�����򡣵���Ҫ�����ʱ���������Ҳ�ᱻ����������Ϊ͸��xinetd���ܹܣ��������һ�ͱ���Ϊsuper daemon���ô��ǿ���͸��super daemon�����з����ʱ�̡���������ȵĿ��ƣ�ȱ���ǻ��ѷ�����Ҫһ��ʱ����ӳ١�

  c.��������������⣺
  �����ǿ��ܻ��������Եġ�������Ҫ����������񣬵���ϵͳû�����磬����ô���ܿ��Ի�����������������Ҫ�������ⲿȡ����֤������������������������Ҫ��һ��A��������������ǣ�A����ûû����������ˣ������֤����Ͳ����ܳɹ�������init�ڹ���Ա�Լ��ֶ�������Щ����ʱ����û�а취Э����������Ļ��ѵġ�

  d.ִ�еȼ��ķ��ࣺ
  ����˵��init�ǿ������������еģ�Ȼ��init���Ը����û��Զ����ִ�еȼ�(runlevel)�����Ѳ�ͬ�ķ����ѽ��벻ͬ�Ĳ������档������Linux�ṩ7��ִ�еȼ����ֱ���0,1...6���Ƚ���Ҫ���ǣ�1������ά��ģʽ����3�����ı�ģʽ����5�����ּ�ͼ�ν��档
  ������ִ�еȼ��������ű���͸��/etc/rc.d/rc[0-6]/SXXdaemon���ӵ�/etc/init.d/daemon�����ᵵ��(SXXdaemon)�Ĺ���Ϊ��
  SΪ�����÷���XX�����֣�Ϊ������˳��������SXX���趨����˿���ʱ���ԡ�����ִ�С�������Ҫ�ķ���ͬʱҲ�ܽ��������������⡣
  
  e.�ƶ�ִ�еȼ�Ĭ��Ҫ�����ķ���
  ��Ҫ��������SXXdaemon�Ļ�������Ҫ����Ա�ֶ��������ᵵ��͸�����µ�ָ�����������Ĭ��������Ԥ�費�������۲�Ԥ�����������Ϊ��
  Ԥ��Ҫ������chkconfig deamon on
  Ԥ�費������chkconfig daemon off
  �۲�Ԥ��Ϊ������chkconfig --list daemon

  f.ִ�еȼ����л���Ϊ��
  ����Ҫ�Ӵ��ı�����(runlevel 3)�л���ͼ�ν���(runlevel 5)������Ҫ�ֶ��������رո�ִ�еȼ�����ط���ֻҪ��init5�������л���init������ȥ����/etc/rc.d/rc[3|5].d/������Ŀ¼�ڵĽű���Ȼ������ת��runlevel����Ҫ�ķ��񡣾���������runlevel�л���


  ������init��Ҫ�Ĺ��ܶ�д����ͷ�ˣ���Ҫ��ָ�����deamon�����Լ��Ľű�(/etc/init.d/daemon)��xinetd���������ܹ�ָ��(super daemon)���趨Ԥ�迪��������chkconfig���Լ���Ӱ�쵽ִ�еȼ���initN�ȡ����ڵ�Linx���а汾�Ѿ�������init�ˣ�������Щ�ű�û�а취ֱ������systemd�Ĵ��������Щ�ű����Ǳ�����������


  17.1.2systemdʹ�õ�unit����
  ���ڸ���systemd����������������ơ�systemd�ĺô���
  
  a.ƽ�д������з��񣬼��ٿ������̣�
    �ɵ�init�����ű��ǡ�һ��һ������������������ģʽ����˲������ķ���Ҳ�ǵ�Ҫһ��һ���ĵȴ�����Ŀǰ���ǵ�Ӳ������ϵͳ�����ϵͳ������֧�ֶ���ļܹ��ˣ����systemd���������еķ���ͬʱ������Ȼ����ᷢ��ϵͳ�������ٶȱ���ˡ�
    
  b.һ��Ҫ�����Ӧ��on-demand������ʽ��
    systemdȫ�����ǽ���һ֧systemd�������systemctlָ���������������������ָ����֧�֡�����systemV��Ҫinit��chkconfig��service�ȵ�ָ����⣬systemd���ڳ�פ�ڴ棬����κ�Ҫ��(on-demand)�������������������daemon����������
    
  c.���������Ե����Ҽ�飺
    ����systemd�����Զ�����������Եļ�飬������B�����Ǽܹ���A�������������ģ��ǵ�����û������A���������½��ֶ�����B����ʱ��systemd���Զ���������A���������Ϳ�����ȥ����Ա��Ҫһ��һ�����ȥ�������鷳��
    
  d.��daemon���ܷ��ࣺ
    systemd����ķ���ǳ��࣬Ϊ���������з���Ĺ��ܣ���ˣ�����systemd�ȶ������еķ���Ϊһ������λ(unit)��������unit���ൽ��ͬ�ķ�������ȥ���ɵ�init����Ϊstand alone ��super deamon�����Ƶ�ʵ�ڲ�����systemd������λ(unit)����Ϊservice��socket��target��path��snapshot��timer�ȶ��ֲ�ͬ�����ͣ��������Ա�ķ�������䡣
    
  e.�����deamons���ϳ�Ϊһ��Ⱥ�飺
    ��ͬsystemV��init�и�runlevel����ɫ��systemdҲ�����Ĺ��ܼ��ϳ�Ϊһ����ν��target��Ŀ�������Ŀ��Ҫ����Ʋ��������Ľ��ã������Ǽ���������daemons���༴��ִ��ĳ��target����ִ�кö��daemon����˼��
    
  f.���¼��ݾ��е�init����ű���
    �����ϣ�sytemd�ǿ��Լ���init�������ű��ģ���ˣ��ɵ�init�����ű�Ҳ�ܹ�͸��systemd������ֻ�Ǹ����׵�systemd���ܾ�û�а취֧���ˡ�

  ��ȻҲ��sytemdû������Ĳ��֣�
  1.��runlevel�Ķ�Ӧ�ϣ���Ž���runlevel 1,3,5�ж�Ӧ��systemd��ĳЩtarget���Ͷ��ѣ�û��ȫ����Ӧ��
  2.ȫ����systemd����systemctl���������������systemctl֧�ֵ��﷨�����ƣ�����/etc/init.d/daemon���Ǵ��ű������Զ��������systemctl�����Զ��������
  3.���ĳ�����������ǹ���Ա�ֶ�ִ��������������ʹ��sytemctlȥ�����ģ���ôsystemd���޷���⵽�÷��񣬶��޷���һ������
  4.systemd���������У��޷������Ա͸��standard input������Ϣ���������׫дsystemd�������趨ʱ�����Ҫȡ���������ơ�


  ��systemd�������ļ�����Ŀ¼
    �����ϣ�systemd����ȥ��ν��daemonִ�нű�ͨͨ��Ϊһ������λ(unit)����ÿ�ַ���λ���ݹ���������ʱ���ͷ���Ϊ��ͬ�����͡������������У�ϵͳ����(service)�����ݼ����뽻���Ĳ�۵�����(socket)������ϵͳ״̬�Ŀ�������(snapshot)���ṩ��ͬ������ִ�еȼ�����Ĳ�������(target)�ȵȡ�
     �������ļ��������ڵ��µ�Ŀ¼�У�
     a./usr/lib/systemd/system/��ÿ����������Ҫ�������ű��趨���е�������ǰ��/etc/init.d���µ��ļ���
     
     b./run/systemd/system/��ϵͳִ�й������������ķ���ű�����Щ�ű����������/usr/lib/systemd/system�ߣ�
     
     c./etc/systemd/system/������Ա��������ϵͳ��������������ִ�нű������Ŀ¼�е�����ǰ��/etc/rc.d/rc5.d/Sxx֮��Ĺ��ܡ�ִ�����ȱ�/run/systemd/system�ߡ�

     Ҳ����˵��ϵͳ�����᲻��ִ��ĳЩ����Ҫ��/etc/systemd/system/���µ��趨�����Ը�Ŀ¼�¾���һ������ᵵ����ʵ��ִ�е�systemd�����ű������ļ�����ʵ���Ƿ�����/usr/lib/systemd/system/���¡�������Ҫ�޸�ĳ�������������趨��Ӧ��ȥ/usr/lib/systemd/system/����ȥ�޸ġ�/etc/systemd/system/�������ᵽ��ȷ��ִ�нű������ļ����ѡ�


    ��systemd��unit���ͷ���˵����
    ��/usr/lib/systemd/system/���µ�����������ֲ�ͬ�����ͣ�����չ����������˵��
    ll /usr/lib/systemd/system |grep -E '(vsftpd|multi|cron)'
    -rw-r--r--  1 root root   776 10�� 10  2021 anacron.service
    -rw-r--r--  1 root root   154 10�� 10  2021 anacron.timer
    -rw-r--r--  1 root root   319  3�� 18  2021 cron.service
    -rw-r--r--  1 root root   540  3�� 11 20:48 multi-user.target	
    drwxr-xr-x  2 root root   258  7�� 16 10:39 multi-user.target.wants/
    lrwxrwxrwx  1 root root    17  6�� 28 02:28 runlevel2.target -> multi-user.target
    lrwxrwxrwx  1 root root    17  6�� 28 02:28 runlevel3.target -> multi-user.target
    lrwxrwxrwx  1 root root    17  6�� 28 02:28 runlevel4.target -> multi-user.target
    -rw-r--r--  1 root root   248  2�� 24 02:18 vsftpd.service
    
    vsftpd��crond����ϵͳ����(service)����multi-userҪ����ִ�л�����ص�����(target type)��



|��չ��   |       ��Ҫ������                                                |
|---------+------------------------------------------------------------------|
| service +һ���������(service unit)����Ҫ��ϵͳ���񣬰�����������������Ҫ�ı���|
|         +�����Լ���������ǡ�                                              |
|---------+-------------------------------------------------------------------|
|socket   +�ڲ��������ݽ����Ĳ�۷���(socket unit)����Ҫ��IPC(Inter-process com |
|         +munication)�Ĵ���ѶϢ����ļ�(socket file)���ܡ��������͵ķ���ͨ���ڼ�|
|         +��ѶϢ���ݵĲ���ļ�������͸���˲���ļ�����ѶϢ��˵Ҫ���ӷ���ʱ��������|
|         +��ʱ��״̬�����û���Ҫ���͵���Ӧ��daemon����deamon��δ�������������� |
|         +daemon���ٴ����û���Ҫ��                                           |
|         +ʹ��socket���͵ķ���һ���ǱȽϲ��ᱻ�õ��ķ�������ڿ���ʱͨ������΢ |
|         +�ӳ�������ʱ�䡣һ�����ڱ��ط���Ƚ϶࣬�������ǵ�ͼ�ν���ܶ���������|
|         +͸��socket�����б����������ݽ�������Ϊ��                             |
|---------+--------------------------------------------------------------------|
|target   +ִ�л�������(target unit)����ʵ����һȺunit�ļ��ϣ�ִ�����target���� |
|         +ִ��һ��������unit                                                  |
|---------+-------------------------------------------------------------------|
|mount    +�ļ�ϵͳ������صķ���(automount unit/mount unit)����������������Զ�|
|automount+���ء�NFS�ļ�ϵͳ���ص����ļ�ϵͳ����Խϸߵĳ������                 |
|---------+-------------------------------------------------------------------|
|path     +����ض��ļ���Ŀ¼����(path unit)��ĳЩ������Ҫ���ĳЩ�ض���Ŀ¼���ṩ|
|         +���з�����������Ĵ�ӡ���񣬾���͸������ӡ����Ŀ¼��������ӡ���� |
|---------+--------------------------------------------------------------------|
|timer    +ѭ��ִ�еķ���(timer unit)����������е�����anacrontab����������      |
|         +systemd�����ṩ�ģ���anacrontab�����е���                            |
|---------+--------------------------------------------------------------------|




17.2͸��systemctl�������

  1.2.1͸��systemctl����һ����(service unit)������/����״̬��۲�״̬
  һ����˵������������������׶Σ�һ���ǡ�������ʱ���趨Ҫ��Ҫ����������񡹣��Լ���������Ҫ��Ҫ����������񡹡�Ҫȡ��atd�����������ķ�����ʹ��systemctl ������ʹ��kill����Ϊsystemctl��ר�����������ġ�

    systemctl [command] [unit]
    command��Ҫ�У�
    start��������������ӵ�unit��
    stop�����̹رպ���ӵ�unit��
    restart�����̹رպ���������ӵ�unit���༴ִ��stop��start��
    reload�����رպ���ӵ�unit������£����²����ļ������趨��Ч��
    enable���趨�´ο���ʱ������ӵ�unit�ᱻ������
    disable���趨�´ο���ʱ������ӵ�unit���ᱻ������
    status��Ŀǰ����ӵ�unit��״̬�����г���û�����У�����Ԥ��ִ����񣬵�½����Ϣ��
    is-active��Ŀǰ��û���������У�
    is-dnable������ʱ��û��Ԥ��Ҫ�������unit��

    ����Ҫʹ��systemctl���ص������ķ������ʹ��kill�ķ�ʽ���ص�һ�������ķ���systemd���޷�������ظ÷���ġ���ͱȽ��鷳��
    ����(service)��״̬��active(***)����ط����ж��״̬�ġ����������ģ�
      ��active(running)������һ֧���֧��������ϵͳ��ִ�е���˼��
      ��active(exited)����ִ��һ�ξ����������ķ���Ŀǰ��û���κγ�����ϵͳ��ִ�С����������������ǹ���ʱ�Ż����һ�ε�quotaon���ܡ�quotaon����һֱִ�У�ִֻ��һ�κ󣬾ͽ����ļ�ϵͳ���д���
      ��active(waiting)������ִ�е��У��������ٵȴ��������¼����ܼ����������磺��ӡ�Ķ�����ط�����Ȼ���������У�����Ҳ��Ҫ����ж��н��������ܻ��Ѵ�ӡ��������������һ����ӡ�Ĺ��ܡ�
      ��inactive���������Ŀǰû����������˼��


  ��ʵԤ��������λ��Ҳ���ж��״̬�ģ����磺
    ��enabled�����daemon���ڿ���ʱ��ִ�У�
    ��disabled�����daemon�ڿ���ʱ���ᱻִ�У�
    ��static�����daemon�������Լ�������enable���ɣ����������ܻᱻ������enabled�ķ����ѡ�
    ��mask�����daemon������ζ��޷�����������Ϊ�Ѿ���ǿ��ע������ɾ��������͸��systemctl unmask�Ļء�


  a.��������/�ر���۲�
  �Լ����顣cups�Ǵ�ӡ����

  b.ǿ�ȷ���ע��(mask)����ϰ
  systemctl stop xx
  systemctl mask xx
  mask��Щ�������ʾ����޸ľ��д������ӵ���/etc/systemd/system��
  mask���ǽ������ӵ�xx���ӵ�/dev/null�������������ļ���

  17.2.2 ͸��systemctl�۲�ϵͳ�����еķ���
  ��β鿴���еķ���
  systemctl [command] [--type=TYPE] [--all]
  command��
    list-units������unit�г�Ŀǰ��������unit��������--all�Ż��г�û�����ġ�
    list-unit-files������/usr/lib/systemd/system/�ڵ��ļ����������ļ��б�˵����

  --type=TYPE������֮ǰ�ᵽ��unit type����Ҫ��service��socket��target�ȡ�
  sudo systemctl list-units --type=service
  UNIT                                                  LOAD   ACTIVE SUB     D>
  accounts-daemon.service                               loaded active running A>
  acpid.service                                         loaded active running A>
  alsa-restore.service                                  loaded active exited  S>
  �����
  UNIT����Ŀ�����ƣ���������unit�����
  LOAD������ʱ�Ƿ�ᱻ���أ�Ĭ��systemctl��ʾ���Ǽ��ص���Ŀ���ѣ�
  ACTIVE��Ŀǰ��״̬�����������SUB���䡣
  SUB��������activeһ����ϵġ�


  17.2.3͸��systemctl����ͬ�Ĳ�������(target unit)
  ʹ��sudo systemctl list-units --type=target --all
  ���Կ�������target���͵ķ��񣬵��Ǹ�������������ԱȽϸߵ�target�е��¼�����
    ��graphical.target���������ּ���ͼ�ν��棬�����Ŀ�Ѿ������˵��µ�multi-user.target��
    ��multi-user.target�����ı�ģʽ��
    ��rescure.target�����޷�ʹ��root���������£�systemd�ڿ���ʱ����һ���������ʱϵͳ������ԭ����ϵͳ�޹ء���ʱ�����ȡ��root��Ȩ����ά�����ϵͳ���������Ƕ���ϵͳ����˿�����Ҫʹ��chroot�ķ�ʽ��ȡ����ԭ�е�ϵͳ��
    ��emergency.target����������ϵͳ�Ĵ��󣬻�����Ҫʹ��root�������������޷�ʹ��rescure.targetʱ�����Գ���ʹ������ģʽ��
    ��shutdown.target:���ǹػ������̡�
    ��getty.target�������趨����Ҫ����tty֮��ģ������Ҫ����tty����Ŀ�������޸�����������ļ���
    ������ģʽ��multi-user.target�Լ�graphical.target����Ԯ�����ģʽ��Ҫ��rescur.target�Լ��������ص�emergency.target�����Ҫ�޸Ŀ��ṩ�����tty���������޸�getty.target��Ŀ�������ϣ�������õľ���multi-user.target��graphical.target��
    ��������������Ŀ�Ĳ�����
    systemctl [command] [unit.target]
    ѡ���������
    get-default��ȡ��Ŀǰ��target��
    set-default���趨����ӵ�target��ΪĬ�ϵĲ���ģʽ��
    isolate���л�������ӵ�ģʽ��
    multi-user��graphical����ģʽ�Ƿǳ�ͻ�ģ��ӿ������棬graphical������Ҫmulti-user�ȿ������������������set-defaultѡ������ͻ�ı��Ƿ���graphical��
    ��set-default���������ʵҲ�����޸�/etc/systemd/system/default.target�ķ������ӵĶ�����/usr/lib/systemd/system/multi-user.target��/usr/lib/systemd/system/graphical.target֮�䡣
    ע�⣺�ı�praphical��multi-user��͸��isolate������ġ���service���͵�����£�ʹ��start/stop/restart������ȷ��������target���������£�ʹ��isolate������ȷ�ģ���Ϊtarget�����Ƕ��unit����ϣ���stopʱ����ر��ĸ�unit���������target�رպ󣬲�������һ��target��������Ҫ�ķ�ʽ������
    ���������л��£�ʹ��������isolate�ķ�ʽ���ɡ�����Ϊ�˷��������systemdҲ�ṩ�������򵥵�ָ��������л�����ģʽʹ�ã�
    systemctl poweroff ϵͳ�ػ�
    systemctl reboot  ��������
    systemctl suspend  ������ͣ״̬
    systemctl hibernate��������״̬
    systemctl rescue    ǿ�ƽ����Ԯģʽ
    systemctl emergencyǿ�ƽ��������Ԯģʽ

    ���������˽�������ͣģʽ������ģʽ��
     ��suspend����ͣģʽ�Ὣϵͳ��״̬���ݱ��浽�ڴ��У�Ȼ��رյ��󲿷ֵ�ϵͳӲ������Ȼ����û��ʵ�ʹػ������û����»��ѻ����İ�ť��ϵͳ���ݻ���ڴ��лָ���Ȼ�������������󲿷ֹرյ�Ӳ�����Ϳ�ʼ����������
     ��hibernate������ģʽ���ǽ�ϵͳ״̬���浽Ӳ���У�������Ϻ󣬽�������ػ������û����Ի���ϵͳʱ��ϵͳ�Ὺʼ����������Ȼ�󽫱�����Ӳ���е�ϵͳ״̬�ָ���������Ϊ��������Ӳ�̶����ģ���˻��ѵ�Ч�����ȡӲ���ٶ��йء�


  17.2.4͸��systemctl����������֮���������
  systemd���������Ե�����˷�����ô���׷��ĳһ��unit�������ԡ�������ô֪��graphical���õ�multi-user�أ�
  systemctl list-dependencies [unit] [--reverse]
  ѡ���������
  --reverse������׷��˭ʹ�����unit����˼��


  17.2.5��systemd��daemon����������ص�Ŀ¼���
  ��ô����ЩĿ¼��ϵͳ��daemon�����йأ������ϣ�
  /usr/lib/systemd/system/��
    Ĭ�ϵ������ű������ļ������������������ݾ�����Ҫ�޸ģ�Ҫ�޸�ʱ���뵽/etc/systemd/system���޸Ľϼѡ�
    
  /run/systemd/system/��ϵͳִ�й������������ķ���ű�����Щ�ű���������Ҫ��/usr/lib/systemd/system�ߡ�
  
  /etc/systemd/system/������Ա��������ϵͳ��������������ִ�нű�����ʵ���Ŀ¼�е�����ǰ/etc/rc.d/rc5.d/Sxx֮��Ĺ��ܡ�ִ���������ֱ�/run/systemd/systemd�ߡ�
  
  /etc/sysconfig/*���������еķ��񶼻Ὣ��ʼ����һЩѡ���趨д�뵽���Ŀ¼�£�������˵��mandb��Ҫ���µ�man page�����У���Ҫ����Ĳ�����д�뵽��Ŀ¼�µ�man-db���С���������趨��ж��/etc/sysconfig/network-scripts/���Ŀ¼�С�

  /var/lib/��һЩ��������ݵķ��񶼻Ὣ��������д�뵽/var/lib/Ŀ¼�С�
  
  /run/�������˺ö�daemon���ݴ浵������lock file�Լ�PID file�ȵȡ�


  ���ǵ�systemd�����кܶ�ı������õ���socket������ͷ���ܻ���������socket file����ô��Щsocket file��������ǿ���͸��systemctl�����ơ�socket��������unit��һ�����͡�
  systemctl list-sockets
  LISTEN                       UNIT                            ACTIVATES         >
/run/acpid.socket            acpid.socket                    acpid.service
/run/avahi-daemon/socket     avahi-daemon.socket             avahi-daemon.servi>
/run/cups/cups.sock          cups.socket                     cups.service
/run/dbus/system_bus_socket  dbus.socket                     dbus.service

  �����������˿ڶ�Ӧ���
  ϵͳ���еĹ��ܶ���ĳЩ�������ṩ�ģ������̶���͸�����������������ġ�ͬ����ϵͳ�ṩ���������ȻҲ�������ġ�
  Ϊ���������ӵ�˳����������Э�飬Լ��������ӿڵ�Ĭ�ϵ�һ��һ��ϵ���ӿ���ʵ��������Ĵ��ڵģ�ʵ������ϵͳ������ɵģ������ļ��е�info�ļ���
  ��ôϵͳ�����趨�����÷�����port��Ӧ��һ����ļ����ǣ�/etc/services��
  cat /etc/services��
  tcpmux		1/tcp				# TCP port service multiplexer
  echo		        7/tcp
  echo		        7/udp
  discard		9/tcp		sink null
  discard		9/udp		sink null
  systat		11/tcp		users
  
  ��һ����daemon�����ƣ��ڶ���Ϊ��daemon��ʹ�õĶ˿ں����������ݷ��Э�飬���Э����ҪΪ�ɿ�������TCP����Լ��Ͽ��ٵ�Ϊ���������ӵ�UDP�����
  ��Ȼ�е�ʱ������Խ����޸�/etc/services������һ�������port�����ǲ����飬��Ϊ���ܻ����Э��Ĵ���

  17.2.6�ر��������
  �����һ��ʹ��systemctlȥ�۲챾�ط����������ķ���ʱ�����ǻᷢ�����ϰٸ��ķ��񡣶�����Ҫ���������������Ȼ�������Ĭ����SELinux���������ǻ��ǽ���Ǳ�Ҫ���������͹رա������ϣ������һ����������˿ڵĳ���������Գ�Ϊ����
  netstat -tlunp
  Proto Recv-Q Send-Q Local Address           Foreign Address         State       PID/Program name    
  tcp        0      0 127.0.0.1:631           0.0.0.0:*               LISTEN      3589/cupsd          
  tcp        0      0 0.0.0.0:25              0.0.0.0:*               LISTEN      6673/master         
  tcp        0      0 127.0.0.53:53           0.0.0.0:*               LISTEN      2528/systemd-resolv 
  udp        0      0 0.0.0.0:5353            0.0.0.0:*                           3158/avahi-daemon:  
  udp        0      0 0.0.0.0:51052           0.0.0.0:*                           3158/avahi-daemon:  
  udp6       0      0 :::48906                :::*                                3158/avahi-daemon:  
  udp6       0      0 :::5353                 :::*      

  �������������ٿ���53,25,631�ȵ�port�������п��Կ���5353,48906�ȶ�����acahi-daemon�������ġ�����������ʹ��systemctl ���۲졣
  sudo systemctl list-units --all |grep avahi
  avahi-daemon.service                                                                     loaded    active   running   Avahi mDNS/DNS-SD Stack
  avahi-daemon.socket                                                                      loaded    active   running   Avahi mDNS/DNS-SD Stack Activation Socket
  avahi-daemon��Ŀ�����ھ�������������������ھӵĲ��ң��������������Э�����ھ���������ʱ�˽������ھӵļ��弴���豸��
  ��Ȼ����Ҫ�õ���ô�͹ص���
  �ص�������ȷ��disabled��������������
  һ����˵�����ط�����������Ҫ25port����22pport����ü��Ϸ���ǽ������Զ����������ȽϺá���˳���������Ҫ�����������ص���


17.3systemctl���service���͵������ļ�

  ��ǰ��������Ҫ����ϵͳ���񣬾�Ҫ��/etc/init.d/����ȥ�������Ӧ��bash shell script����������systemd�Ļ����£��ָ���δ���
  17.3.1systemctl�����ļ����Ŀ¼���
  systemd�������ļ��󲿷ַ�����/usr/lib/systemd/system/Ŀ¼�ڣ����Ǹ�Ŀ¼�ڷݶ��ļ���Ҫ��ԭ��������ṩ���趨�����鲻Ҫ�޸ġ������ȥ�޸����ӵ���/etc/systemd/system/Ŀ¼��
  �������Ҫ�����޸�vsftpd.service�Ļ���RedHat����Ҫ���õ��ĵط���
  ��/usr/lib/systemd/system/vsftpd.service��
    �ٷ��ͳ���Ԥ�������ļ���
  ��/etc/systemd/system/vsftpd.serviec.d/custom.conf��
  ��/etc/systemd/system���½����������ļ���ͬ�ļ�����Ŀ¼������Ҫ����.d����չ����Ȼ���ڸ�Ŀ¼�½��������ļ����ɡ����⣬�����ļ���ø�����ȡ��Ϊ.conf�ϼѡ������Ŀ¼�µ��ļ��ᡸ�ۼ������趨������/usr/lib/systemd/system/vsftpd.service��
 
  ��/etc/systemd/system/vsftpd.service.wants/*��
    ��Ŀ¼�ڵ��ļ�Ϊ���ӵ����趨������������ӡ���˼��������vsftpd.service֮������ټ�����Ŀ¼����ķ���
    
  ��/etc/systemd/system/vsftpd.service.requires/*��
    ��Ŀ¼�ڵ��ļ�Ϊ���ӵ����趨������������ӡ���˼������vsftpd.service֮ǰ����Ҫ���������ķ���

  �����ϣ��������ļ������㶼���������趨��������ļ�飬�����趨���뵽��Щtarget���档����������Ѿ����ڵ������ļ��������ǹٷ��ṩ�������ļ���Red Hat�ǽ����㲻Ҫ�޸�ԭ�趨�����ǵ������ᵽ�ļ���Ŀ¼ȥ���ж���Ŀ��ƻ��趨�ȽϺá���Ȼ����������Լ�������

  17.3.2 systemctl�����ļ����趨��Ŀ���
  �˽������ļ������Ŀ¼���ļ�֮�󣬾����˽������ļ���������ݡ���sshd.service�������ӡ�
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

  [unit]�����Ŀ���unit�Ľ��͡�ִ�з����������й�
  [service]�����Ŀ��ʵ��ִ�е�ָ������й�
  [install]�����Ŀ˵����unitҪ�����Ǹ�target����

  ���������ļ�����Щ������Ҫ˵��һ�£�
  ���趨��Ŀͨ���ǿ����ظ��ģ������ҿ����趨����after�������ļ��У�������������趨��ȡ��ǰ��ġ������Ҫ���趨���㣬����ʹ�����ơ�After=�����趨��
  ������趨������Ҫ�ɡ���/�񡹵���Ŀ�������ʹ��1,yes��true��on������������0,no��false��off����رա�
  ���հ��С���ͷΪ#��;����һ�У���������ע��

   a.unit���֣�
   Description�����ǵ�����ʹ��systemctl list-unitsʱ�������������Ա���Ľ���˵������Ȼ��status Ҳ���Կ�����
   Documentation�������Ŀ�ṩ����Ա�ܹ����н�һ�����ļ���ѯ�Ĺ��ܡ�
   ���磺Documentation=http://...
         Documentation=man:ssh(8)
	 Documentation=file:/etc/ssh/sshd_config

   After��˵����unit�����ĸ�daemon����֮�����������˼�������Ͻ���˵������������˳����ѣ���û��ǿ��Ҫ����ͷ�ķ���һ��Ҫ�������unit������������ssh������Ϊ����after������network.target�Լ�ssh-eygen.service��������������unitû��������ǿ������sshd.service�Ļ�����ôsshd.serviceӦ�û����ܹ������ġ�
   Befor����After�������෴������ʲô��������ǰ�����������������˼����������ǹ淶����������˳�򣬲���ǿ��Ҫ�����˼��
   Requires����ȷ�Ķ����unit��Ҫ���ĸ�daemon��������ܹ������������趨����������������趨��ǰ������û����������ô��unit�Ͳ��ᱻ������
   Wants����Requires�պ��෴���淶�������unit֮����û�Ҫ����ʲô����ȽϺõ���˼����������û����ȷ�Ĺ淶�����ˡ���Ҫ��Ŀ����ϣ��������ʹ���߱ȽϺò����Ļ�������ˣ����Wants����ӵķ������û������������Ӱ�쵽���unit����
   Conflicts�������ͻ�ķ����༴�����Ŀ����ӵķ����������������ô�������unit����Ͳ�������������unit�������������Ŀ�����Ŀ�Ͳ���������

  
  b.service
  Type��˵�����daemon�����ķ�ʽ����Ӱ��ExecStart�������¼������ͣ�
   ��simple��Ĭ��ֵ�����daemon��Ҫ��ExecStart�ӵ�ָ���������������פ���ڴ��С�
   ��forking����ExecStart�����ĳ���͸��spawns����������ӳ�������Ϊ��daemon����Ҫ����ԭ���ĸ�����������������ͻ���ֹ��������ͳ��unit����������������Ŀ������httpd���www���񣬵�httpd�ĳ�����Ϊ����������˼����ս��ˣ���systemd��������������һ���ӳ�������������ٽ�������ɾ����
   ��oneshot����simple���ƣ�������������ڹ���Ϊ��Ϻ�ͽ����ˣ����᳣פ���ڴ��С�
   ��dbus����simple���ƣ������daemon����Ҫ��ȡ��һ��D-Bus�����ƺ󣬲Ż��������������趨�����Ŀʱ��ͨ��ҲҪ�趨BusName=xxx���С�
   ��idle����simple���ơ���˼�ǣ�Ҫִ�����daemon����Ҫ���еĹ�����˳��ִ����ϲŻ�ִ�С������daemonͨ���ǿ���������ִ�м��ɵķ���

  EnvironmentFile������ָ�������ű��Ļ��������ļ�������ssh�������ļ�д�뵽/etc/sysconfig/sshd�����ܣ�Ҳ�����ں���Ӷ����ͬ��Shell�����������趨��
  ExecStart������ʵ��ִ�д�daemon��ָ���ű�������Ҳ����ʹ��ExecStartPre��֮ǰ���Լ�ExecStartPost��֮�������趨��Ŀ����ʵ����������ǰ�����ж����ָ����Ϊ���������Ҫ�ر�ע����ǣ�ָ������ܡ�ָ�� ���� ���� ...���ĸ�ʽ�����ܽ���<,>,>>,|,&�������ַ����ܶ��bash�﷨Ҳ��֧�֡�����Ҫʹ����Щ�����ַ�ʱ�����ֱ��д�뵽ָ��ű�����ȥ�������������﷨Ҳ������ȫ�����ã���Ҫ֧�ֱȽ�������bash�﷨�������Ҫʹ��Type=oneshot���С�
  ExecStop����systemctl stop��ִ���йأ��رմ˷���ʱ�����е�ָ�
  ExecReload����systemctl reload�йص�ָ����Ϊ��
  Restart�����趨Restart=1ʱ���򵱴�daemon������ֹ�󣬻��ٴε������˷��񡣾�����˵���������tty2ʹ�����ֽ�����룬������Ϻ�ע���������ϣ����ʱ��tty2���Ѿ����������ˡ�������ῴ����Ļ�����̲���һ���µ�tty2�ĵ������ȴ���ĵ��롣�����Restart�Ĺ��ܣ�����ʹ��systemctlǿ�ƽ��˷���رգ�������������ԴԴ���ϵ�һֱ�ظ�������
  RemainAfterExit�����趨ΪRemainAfterExit=1ʱ�������daemon���������г�����ֹ֮�󣬴˷�����ٳ��������������Type=oneshot�ķ�����а�����
  TimeoutSec��������������������߹ر�ʱ����ΪĳЩԵ�ʵ����޷�˳������������������������������£�������Ҫ�ȶ�òŽ��롸ǿ�ƽ�����״�塹��
  KillMode������ʱprocess��control-group��none������һ�֣����ʱprocess��daemon��ֹʱ��ֻ����ֹ��Ҫ�ĳ���ExecStart�ӵĺ�����Ǵ�ָ������ʱcontrol-groupʱ�����ɴ�daemon������������control-group�ĳ���Ҳ���ᱻ�رա����ʱnone����û�г���ᱻ�رա�
  RestartSec����Restart�е�����ԣ����������񱻹رգ�Ȼ����Ҫ��������ʱ�������Ҫsleep����ʵ����������������˼��Ԥ��ʱ100ms��
  

  c.��install��
  WantedBy������趨����ӵĴ󲿷���*.target unit�����unit�����Ǹ�����ĳһ��target unit���¡�һ����˵�����ķ������ʵ�unit���Ǹ�����multi-user.target���¡�
  Also�������unit����enableʱ��Also����ӵ�unitҲ��enable����˼��Ҳ���Ǿ��������Եķ������д�����
  Alias������һ������ı�������˼����systemctl enable��صķ���ʱ����˷����������ӵ��Ľ�������multi-user.targetΪ��������һ���������ΪĬ�ϲ�������default.target��ʹ�ã���˵��������ó�default.targetʱ�����/etc/systemd/system/default.target�ͻ����ӵ�/usr/lib/systemd/system/multi-user.target��

  17.3.3 ����vsftpd������ʵ��
  ���ǿ�����Ҫ��vsftodʹ�õ�����port���ֱ���21�Լ�555����������port�����õ�����£����Ǿ���Ҫ���������ļ��Լ����������ű��趨�ˡ�
  ���ڼ����ǣ�
    ��Ԥ���port21��ʹ��/etc/vsftpd/vsftpd.conf�����ļ����Լ�/usr/lib/systemd/system/vsftpd.service�趨�ű���
    ��Ԥ���port555��ʹ��/etc/vsftpd/vsftpd2.conf�����ļ����Լ�/usr/lib/systemd/system/vsftpd2.service�趨�ű���
!!!������centos�ģ�������ubuntu���棺/etc/vsftpd.conf��

�����Լ����飬�Լ������ļ����޸ĵȡ�

17.3.4 ���ص��ظ��趨��ʽ����gettyΪ��
  ������6���ն˻�����ʹ�ã������Ǹ�tty1-tty6���Ǹ���������agetty���ָ���ɵġ�����Ҫ�������getty.target������ʵ�ʲ���tty1-tty2��������getty@.service���ṩ�ġ�
  �ȿ���/usr/lib/systemd/system/getty@.service
  ��������Ҫ����
  ExecStart=-/sbin/agetty -o '-p -- \\u' --noclear %I $TERM
  �����������кܶ��tty����ôͬ����������Ҫ��Ӧ��getty(num).service�������ļ����趨�ű�����������ֻ��getty@.service���������ǿ��Կ����������service��getty.target��
  ������У�After=getty@tty1.service��getty@tty2.service��getty@tty3.service��getty@tty4.service��getty@tty5.service��getty@tty6.service
  ���ҵ�ϵͳ�У�After=getty@tty1.service getty-static.service

  ��������Ϊ��������ִ����getty.target֮���������Ҫ������getty@ttyn.service������������������ǵ�systemd����ô����
  ���ȿ�/usr/lib/systemd/system��/etc/systemd/system��û��getty@tty1.service���趨�����о�ִ�У���û����ִ����һ����
  ����getty@.service���趨��������@��������ݴ����%I�ı���������getty@.serviceִ�С�getty@.service�����ExecStart=-/sbin/agetty -o '-p -- \\u' --noclear %I $TERM��
  Ҳ����˵��ʵû��getty@tty1.service����͸��getty@.service��ִ�С�Ҳ����˵��getty@.service��Ŀ����Ϊ��Ҫ�򻯶��ִ�е������趨��������ʽ�ǣ�
  Դ�ļ���ִ�з�������@.service��
  ִ���ļ���ִ�з�������@��������.service����˵��з������ƴ���ʱ�������һ���µķ������Ʋ���������

  a.�ı�tty������
  ����tty����������ssytemd�ĵ��������ļ�/etc/systemd/logind.conf����淶�ġ�
  ���Կ��Կ����������ļ����棬
  �޸�[login]�����ݣ�
  #NAutoVTs=6
  #ReserveVT=6
  ��Ϊ
  NAutoVTs=n
  ReserveVT=0


  b.��ʱ����vsftpd��2121port
  ��ʵ��/usr/lib/systemd/system/���»��и��ر��vsftpd@.service��
  cat /usr/lib/systemd/system/vsftpd@.service
  ���ҵĵ�����û������ļ���
  ʵ���ϣ�%i/%I���Ǵ���@����ӵķ����ļ�������˼����ô�����ܲ��ܽ���vsftpd3.conf�ļ���Ȼ��͸�����ļ��������µķ���?
  ��Ȼ���ԣ�ʹ�÷�����
  systemctl start vsftpd@vsftpd3.service
  systemctl status vsftpd@vsftpd3.service

  17.3.5�Լ��ķ����Լ�����
  ������Ҫ��һ֧���Ա����Լ�ϵͳ�ķ�����֧�ű��ҷ���~/backups���¡�
  vim ~/backups/backup.sh��
  #!/bin/bash
  source="/etc /usr /root /var/lib /var/spool/{cron,at} /home/zcj/�� /home/zcj/helloworld"

  target="~/backups/backup-system-$(date +%Y-%m-%d).tar.xz"
  [ ! -d ~/backups] && mkdir ~/backups
  tar -cvzf ${target} ${source} &> ~/backups/backup.log

  ���ǽű���Ȼ����Ƿ����ˣ������еĽű���Ŀ¼�У�/etc/systemd/system�����ȼ���ߵģ���������Ҳ��ò�Ҫ�޸�/usr/lib/systemd/system��������ݡ����������/etc/systemd/system�����޸ġ�
  vim /etc/systemd/system/backup.service
  [Unit]
  Description=server to back my file 
  Requires=atd.service

  [Service]
  Type=simple //���Ըĳ�oneshot����Ϊִֻ��һ�Ρ�
  ExecStart=/bin/bash -c "echo /home/zcj/backups/baskup.sh | at now"

  [Install]
  WantedBy=multi-user.target
  Requires��at���������ǵ�ExecStart��Ҫ�õ�atָ�
  ֮������������еķ���Ȼ�������ǵķ���˳��һ�ᣬ��Ϊ�ű������ǳ������ִ����Ϻ󣬾Ͳ���������ڴ��д��ڡ�
  ����ͨ��ps���������ǵķ����гɹ����С�
  ps aux |grep backup
  root       19041  0.0  0.0  13060  3740 ?        S    10:55   0:00 /bin/bash /home/zcj/backups/backup.sh
  root       19043  4.7  0.0  14216  4504 ?        S    10:55   0:05 tar -cvzf /home/zcj/backups/backup-system-2022-08-20.tar.xz /etc /usr /root /var/lib /var/spool/{cron,at} /home/zcj/�� /home/zcj/helloworld
  root       19108  0.0  0.0  12184  2376 pts/1    S+   10:57   0:00 grep --color=auto backup

  
17.4 systemctl ���timer�������ļ�

  ��ʱ��ĳЩ��������Ҫ����ִ�У������ǿ�����ִ�У�����ʲô����������ú�ִ�еȵȡ��ڹ�ȥ�����Ǵ��ʹ��crond������������ڴ���������Ȼ������һֱ��פ���ڴ��е�systemd������systemd�и�Э������timers.target������Э�����ڴ����������

  a.systemd.timer������
    ��archlinux�Ĺ��������ᵽ��
    ���������е�systemd�ķ����������Ϣ���ᱻ����¼(log)����˱�crond��debug����Ҫ���������Ķࣻ
    ������timer�Ĺ������Ը�systemd�ķ������ϣ�
    ������timer�Ĺ������Ը�contrl group(cgroup������ȡ��/etc/secure/limit.conf�Ĺ���)��ϣ������Ƹù�������Դ���á�
    
  b.��������
  �����ϣ���Ҫʹ��systemd��timer���ܣ�����Ҫ�м���Ҫ����
    ��ϵͳ��timer.targetһ��Ҫ������
    ��Ҫ�и�sname.service�ķ�����ڣ�sname���Լ�ָ�������ƣ�
    ��Ҫ�и�sname.timer��ʱ������������ڡ�
  �������������Ϳ����ˡ����ǵ�backup.service��������ʵ�飬����Ҳ��ϣ��ÿ�ζ�Ҫ��ʹ�ã����ǿ�����������ִ�С�

  c.sanme.timer���趨ֵ
  