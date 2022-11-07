#include<net/if.h>
#include<sys/ioctl.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<iomanip>

#define ETH_NAME "eth0"

//get the interface of ether,return sockaddr_in stucture 
class IF{
	private:
		int sockfd;
		struct ifreq ifr;
		unsigned char *mac;

	public:
		IF();
		~IF();
		struct sockaddr_in getIf();
        unsigned char* getMac();


};
IF::IF(){
	//获得socket
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	//写入要获得相关数据的网卡名字
	strncpy(ifr.ifr_name,ETH_NAME,IFNAMSIZ);
	//给mac分配空间
	mac = (unsigned char *)malloc(6);
}
IF::~IF(){
	free(mac);
	close(sockfd);
}

//获取interface的相关信息
struct sockaddr_in IF::getIf(){
	struct sockaddr_in interface;
	int res = ioctl(sockfd,SIOCGIFADDR,&ifr);
	if(-1 == res){
		perror("ioctl-->get_interface_index:");
		exit(1);
	}
	memcpy(&interface,&ifr.ifr_addr,sizeof(ifr.ifr_addr));

	return interface;

}
//获取mac地址
unsigned char* IF::getMac(){
	memset(mac,0,sizeof(mac));
	int res = ioctl(sockfd,SIOCGIFHWADDR,&ifr);
	if(-1 == res){
		perror("ioctl-->get_hardware_address:");
		return NULL;
	}
	memcpy(mac,ifr.ifr_hwaddr.sa_data,6);
	return mac;
}
/*
int main(){
	IF iiff;
	struct sockaddr_in itfc = iiff.getIf();
	unsigned char t[6];
	memset(t,0,sizeof(t));
	memcpy(t,iiff.getMac(),6);
	
	std::cout<<"ip:"<<inet_ntoa(itfc.sin_addr)<<std::endl;
	printf("%02x:%02x:%02x:%02x:%02x:%02x\n",t[0],t[1],t[2],t[3],t[4],t[5]);
	return 0;
}
*/
