
OBJS1 = tftpd.o talk.o download.o create_dgram.o 
OBJS2 = tftp_c.o download.o create_dgram.o
SRCS= $(patsubst %.o,%.c,$(OBJS))

tftpd:$(OBJS1)
	g++ $^ -o $@ -pthread


tftp_c:$(OBJS2)
	g++ $^ -o $@ -pthread

tftpd.o:tftpd.cpp
	g++ -c $< -o $@	 -pthread

tftp_c.o:tftp_c.cpp
	g++ -c $< -o $@ -pthread


talk.o:talk.cpp
	g++ -c $^ -o $@ -pthread

download.o:download.cpp
	g++ -c $< -o $@ -pthread

create_dgram.o:create_dgram.cpp 
	g++ -c $< -o $@ -pthread






.PHONY:clean
clean:
	rm $(OBJS) tftpd
