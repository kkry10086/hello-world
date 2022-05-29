dos 与 unix系统的换行符是不一样的，dos是^M$，即CR与LF
而unix是$，即LF。
换行符的不同，在shell脚本文件会导致程序无法执行。即误判
程序的命令内容。
当然也是有转换的命令：
dos2unix [-kn] file [newfile]
unix2dos [-kn] file [newfile]
-k ：保留该文件原本的mtime时间格式。
-n ：保留原本的旧文件，将转换后的内容输出到新文件。

语系编码转换：iconv
iconv --list
iconv -f 原来编码 -t 新编吗 filename [-o newfile]
--list ：列出iconv支持的语系数据。
-f ：from,来源之意。
-t ：to。
-o ：如果要保留原来的文件，就使用这个。