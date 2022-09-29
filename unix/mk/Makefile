OBJS=add.o sub.o test.o

#$@表示目标
#$^表示所有的依赖
#$<表示第一个依赖


#模式匹配 所有的.o都依赖相应的.c
#将所有的.c生成对应的.o

#wildcard查找指定目录下的执行类型的文件
#src=$(wildcard *.c)
#patsubst 匹配替换
#obj=$(patsubst %.c,%.o,$(src))

#当目标与当前目录下的文件同名，那么此时就不会执行该目标的命令
#所以可以使用伪目标
#伪目标声明:.PHONY:target
#此时就不会去
#

#特殊符号：-,@
#-词条命令出错，make也会继续执行那个后续的命令
#@不显示命令的执行过程，只有结果


SRC=$(wildcard ./*.c)
objs=$(patsubst %.c,%.o,$(SRC))

%.o:%.c
	g++ -c $< -o $@

test:$(objs)
	g++ $^ -o $@

#add.o:add.c
#	g++ -c $< -o $@

#sub.o:sub.c
#	g++ -c $< -o $@

#test.o:test.c
#	g++ -c $< -o $@

.PHONY:clean

clean:
	rm $(objs) test
