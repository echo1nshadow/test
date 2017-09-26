#include<pcap.h>
#include<time.h>
#include<stdlib.h>
void getPacket(u_char* , const struct pcap_pkthdr *, const u_char *);
void display(const struct  pcap_pkthdr * , const u_char * );
void analyse(const u_char *);
void getDestAddr(const u_char * );
void getSrcAddr(const u_char * );
void getType(const u_char * );
void getIphead(const u_char *);
void getTranHead(const u_char *);



int main(int argc , char **argv)
{
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
	
/*	获取网络号	*/
/*
	bpf_u_int32 netp , maskp;
	if((pcap_lookupnet(device,&netp,&maskp,err_message) == -1))
	{
		printf("error:%s\n",err_message);
		exit(-1);
	}
	printf("net : %d\n",netp);
	printf("mask: %d\n",maskp);
*/
	

	handle = pcap_open_live(device,65535,1,0,err_message);
	if(handle == NULL)
		printf("%s\n",err_message);
	else
		printf("pcap_open_live success\n");

	/*		fliter		*/
	struct bpf_program filter;

	pcap_compile(handle,&filter, "src port 80",1,0);
	pcap_setfilter(handle,&filter);



	struct pcap_pkthdr pkthdr;
	const unsigned char* packet_content = NULL;
	int count = -1;
	int id = 0;
	int datalink_type = 0;
	datalink_type = pcap_datalink(handle);
	printf("Data link type:%s	",pcap_datalink_val_to_name(datalink_type));
	printf("%s\n",pcap_datalink_val_to_description(datalink_type));
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
	printf("IP header:\n");
	getIphead(packet);
	getTranHead(packet);
	display(pkthdr, packet);

}

void display(const struct pcap_pkthdr * pkthdr , const u_char * packet)
{
	int i = 0 ;
	int j = 0;
	for( ; i< pkthdr->len ; i++)
	{
		printf(" %02x",packet[i]);
		if((i+1)%8 == 0)
			printf("  ");
		if((i+1)%16 == 0)
			printf("\n");
	}
/*
	for( ; j<pkthdr->len ; j++)
	{
		printf("%c",packet[j]);
		if((i+1)%8 == 0)
			printf("  ");
		if((i+1)%16 == 0)
			printf("\n");
	}
*/
	printf("\n");
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
	if(packet[12] == 0x08&&packet[13] == 0x00)
	{
		printf("(IPv4)");
	}
	if(packet[12] == 0x08&&packet[13] == 0x06)
	{
		printf("(ARP ： Address Resolution Protocol)");
	}
	if(packet[12] == 0x86&&packet[13] == 0xdd)
	{
		printf("(IPv6)");
	}
	if(packet[12] == 0x88&&packet[13] == 0x0b)
	{
		printf("(PPP：Point-to-Point Protocol)");
	}
	if(packet[12] == 0x88&&packet[13] == 0x64)
	{
		printf("(PPPoE)");
	}
	printf("\n");
}

void getIphead(const u_char * packet)
{
	int version = 0;
	version = packet[14] & 0xf0;
	version >>= 4;
	int header_length = 0;
	header_length = packet[14] & 0x0f;
	printf("Version:IPv%d\n",version);
	printf("Header length:%d\n",header_length * 4);
	printf("Differentiated Services Field: %02x\n",packet[15]);
	printf("Differentiated Services Codepoint: %d\n",(packet[15]&0xfc)>>2);
	printf("Explicit Congestion Notification: %d\n",(packet[15]&0x03));
	int total_length = 0;
	total_length |= packet[16];
	total_length <<= 8;
	total_length |= packet[17];
	printf("Total length:%d\n",total_length);
	printf("Identification:0x%02x%02x\n",packet[18],packet[19]);
	printf("Flags:\n");
	printf("Reserved bit   : %d\n",(packet[20] & 0x80)!=0);
	printf("Don't fragment : %d\n",(packet[20] & 0x40)!=0);
	printf("More fragments : %d\n",(packet[20] & 0x20)!=0);
	printf("Fragment offset: %d\n",packet[21]);
	printf("Time to live   : %d\n",packet[22]);
	printf("Protocol:TCP(%d)\n",packet[23]);
	printf("Head checksum:%02x%02x\n",packet[24],packet[25]);
	printf("Source IP       :");
	printf("%d.",packet[26]);
	printf("%d.",packet[27]);
	printf("%d.",packet[28]);
	printf("%d\n",packet[29]);
	printf("Destination IP  :");
	printf("%d.",packet[30]);
	printf("%d.",packet[31]);
	printf("%d.",packet[32]);
	printf("%d\n",packet[33]);
}

void getTranHead(const u_char * packet)
{
	int src_port = 0;
	src_port = packet[34] | src_port ;
	src_port <<= 8;
	src_port = packet[35] | src_port ;
	printf("Source port     :%d\n",src_port);
	int dest_port = 0;
	dest_port = packet[36] | dest_port ;
	dest_port <<= 8;
	dest_port = packet[37] | dest_port ;
	printf("Destination port:%d\n",dest_port);
}
	








