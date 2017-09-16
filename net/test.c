#include<pcap.h>
#include<time.h>
void getPacket(u_char* , const struct pcap_pkthdr *, const u_char *);
void display(const struct  pcap_pkthdr * , const u_char * );
void analyse(const u_char *);
void getDestAddr(const u_char * );
void getSrcAddr(const u_char * );
void getType(const u_char * );



int main(int argc , char **argv)
{
	
/*
	int id = 0;  
	int count = 5;
	int ch;
	while((ch=getopt(argc,argv,"a:hn")) != -1)
	{
		switch(ch)
		{
			case 'h'
				device 
		

*/
	pcap_t * handle;
	char err_message[PCAP_ERRBUF_SIZE] = {0};
	char * device ;
	if(!argv[1])
	{
		if((device = pcap_lookupdev(err_message)) == NULL)
			printf("error : %s\n",err_message);
		else
			printf("device : %s\n",device);
	}
	else
	{
		device = argv[1];
	}
	handle = pcap_open_live(device,65535,1,0,err_message);
	if(handle == NULL)
		printf("%s\n",err_message);
	else
		printf("pcap_open_live success\n");
	struct pcap_pkthdr pkthdr;
	const unsigned char* packet_content = NULL;
	int count = 5;
	int id = 0;
	pcap_loop(handle, count , getPacket, (u_char*)&id); 
	pcap_close(handle);
	return 0;
}
void getPacket(u_char* argv , const struct pcap_pkthdr * pkthdr, const u_char * packet)
{
	int * id =  (int *) argv;
	printf("\nid : %d\n",++(*id));
	printf("packet's length:%d\n",pkthdr->len);
	printf("time: %s",ctime((const time_t *)&(pkthdr->ts.tv_sec)));
	analyse(packet);
	display(pkthdr, packet);

}

void display(const struct pcap_pkthdr * pkthdr , const u_char * packet)
{
	int i = 0 ;
	for( ; i< pkthdr->len ; i++)
	{
		printf(" %02x",packet[i]);
		if((i+1)%8 == 0)
			printf("  ");
		if((i+1)%16 == 0)
			printf("\n");
	}
	printf("\n\n\n");
}

void analyse(const u_char * packet)
{
	getDestAddr(packet);
	getSrcAddr(packet);
	getType(packet);
	
}


void getDestAddr(const u_char * packet)
{
	int i = 0;
	printf("Ether dest addr:    ");
	for ( ; i < 6; ++i)
	{
		printf("%02x",packet[i]);
		if((i+1)%6)
			printf(":");
	}
	printf("\n");
}

void getSrcAddr(const u_char * packet)
{
	int i = 6;
	printf("Ether src  addr:    ");
	for( ; i < 12; ++i)
	{
		printf("%02x",packet[i]);
		if((i+1)%6)
			printf(":");
	}
	printf("\n");
}

void getType(const u_char * packet)
{
	int i = 12;
	printf("Type :");
	printf("0x");
	for( ; i < 14 ; ++i)
	printf("%02x",packet[i]);
	printf("  ");
	if(packet[12] == 0x88)
	{
		if(packet[13] == 0x64)
			printf("(PPPoE，PPP Over Ethernet<PPP Session Stage)");
	}
	printf("\n");
}












