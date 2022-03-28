<vector>
链表结构 
但是其存取，增删都是使用数组的方式来进行的；
修改，查看时是可以使用index，即vec[i];
存删时一般是在链表的最后执行，
但是，插入，删除中间数据会导致其想数组一样将数据一直往后、前移。
而vecter中iterator可以使用iter=iter+i来定位。

而其作为链表的结构 则 表现在：iterator
vec.begin()+vec.size()==vec.end();
vec.end()+1=vec.begin();
首位相连。

<list>就是我们认为的一般的链表结构。
增删减改就是链表的操作。
list中iterator不可以使用iter=iter+i的形式定位，只可以使用iter++/--;
list也是首尾相连的：
list.end()++=list.begin();
list.begin()+list.size()==list.end();
