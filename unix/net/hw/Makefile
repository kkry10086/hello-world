
OBJS = talk.o tftpd.o
SRCS= $(patsubst %.o,%.c,$(OBJS))

tftpd:$(OBJS)
	g++ $^ -o $@

talk.o:talk.cpp
	g++ -c $< -o $@

tftpd.o:tftpd.cpp
	g++ -c $< -o $@	
tftp_c:tftp_c.cpp
	g++ $< -o $@

.PHONY:clean
clean:
	rm $(OBJS) tftpd
