#include<iostream>
#include<string>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netinet/ether.h>
#include<netinet/in.h>
#include<string.h>

using std::cout;using std::endl;using std::cin;
using std::string;

int main(int argc, char ** argv)
{
	//创建链路层套接字
	int eth_fd = socket(PF_PACKET,SOCK_RAW,htons(ETH_P_ALL)); 
	if(-1 == eth_fd){
		perror("socket:eth_fd");
		return 1;
	}

	unsigned char buf[1500];
    char srcmac[18];
	char dstmac[18];
	char src_ip[16];
	char dst_ip[16];

	while(1){
		memset(buf,0,sizeof(buf));
		//获取链路层上的数据，因为这里是链路层的，
		//所以只要是网卡收到的数据都会直接传上来
		//所以没有ip或port
	    recvfrom(eth_fd,buf,sizeof(buf),0,NULL,NULL);
		
		//解析buf
		/*
		//输出的都是乱码，改为16进制输出也没有改变
		memcpy(dstmac,buf,6);
		memcpy(srcmac,buf+6,6);
		cout<<setbase(16)<<std::setiosflags(std::cout.showbase)<<srcmac[0];
		for(int i = 1;i<sizeof(srcmac);i++){
			cout<<":"<<srcmac[i];
		}
		cout<<" ---> ";

		cout<<dstmac[0];
		for(int i = 1;i<sizeof(dstmac);i++){
			cout<<":"<<dstmac[i];
		}
		cout<<100<<endl;
		*/
		snprintf(dstmac,sizeof(dstmac),"%x:%x:%x:%x:%x:%x",
				buf[0],buf[1],buf[2],buf[3],buf[4],buf[5]);

		snprintf(srcmac,sizeof(srcmac),"%x:%x:%x:%x:%x:%x",
				buf[6],buf[7],buf[8],buf[9],buf[10],buf[11]);

		printf("srcmac = %s ---> dstmac = %s \n",srcmac,dstmac);

		if(0x08==buf[12] && 0x00 == buf[13]){
			printf("this is IP\n");
			snprintf(src_ip,sizeof(src_ip),
					"%d.%d.%d.%d",buf[26],buf[27],buf[28],buf[29]);
			snprintf(dst_ip,sizeof(dst_ip),
					"%d,%d,%d,%d",buf[30],buf[31],buf[32],buf[33]);

			printf("src_ip= %s --> dst_ip = %s\n",src_ip,dst_ip);

			if( 0x06 == buf[23]){
				printf("TCP\n");
				printf("src_port=%d -->",ntohs(*((unsigned short *)(buf+34))));
				printf("dst_port=%d\n",ntohs(*((unsigned short *)(buf+36))));
			}
			else if(0x17 == buf[23]){
				printf("UDP\n");
				printf("src_port=%d -->",ntohs(*((unsigned short *)(buf+34))));
				printf("dst_port=%d\n",ntohs(*((unsigned short *)(buf+36))));
			}
			else if(0x01 == buf[23]){
				printf("ICMP(ping)\n");
				printf("src_port=%d -->",ntohs(*((unsigned short *)(buf+34))));
				printf("dst_port=%d\n",ntohs(*((unsigned short *)(buf+36))));
			}

		}
		else if(0x08 == buf[12] && 0x06 == buf[13]){
			printf("this is ARP\n");
		}
		else if(0x08 == buf[12] && 0x35 == buf[13]){
			printf("this is RARP\n");
		}


	}



	return 0;
}
