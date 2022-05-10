脚本文件查找:
一、which:
which -a [command]
-a:将所有由PATH目录中可以找到的命令均列出。
alias which ='alias......'
/usr/bin/alias
/usr/bin/which
结果有可能出现并非command的单词，这是所谓的命令别名。
意思是输入which会等于后面接的那串命令。

二、type: