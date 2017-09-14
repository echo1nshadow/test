#include<pcap.h>
#include<time.h>



void getPacket(u_char * arg, const struct pcap_pkthdr * , const u_char * packet);  

int id = 0;  
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
		


	int net = 0;
	bpf_u_int32 netp = 0;
	bpf_u_int32 maskp = 0;
	
/*
	net = pcap_lookupnet(device , &netp , &maskp , err_message);
	if(net == -1)
	{
		printf("error :%s\n",err_message);
	}
	else
	{
		printf("net_id %d\n",net);
		printf("net_p %d\n",netp);
		printf("net_mask %d\n",maskp);	
	}

*/
	handle = pcap_open_live(device,65535,1,0,err_message);
	if(handle == NULL)
		printf("%s\n",err_message);
	else
		printf("pcap_open_live success\n");


/*
 *		pcap.h中定义过这个结构体
	struct pcap_pkthdr
	{
		struct timeval ts;
		bpf_u_int32 caplen;
		bpf_u_int32 len;
	};

*/

	struct pcap_pkthdr pkthdr;
	const unsigned char* packet_content = NULL;


//		test
/*
	printf("%x\n",handle);
	printf("time: %s\n",ctime((const time_t *)pkthdr.ts.tv_sec));
*/
/*
	packet_content = pcap_next(handle,&pkthdr);
	printf("timestamp : %s\n",ctime((const time_t *)&(pkthdr.ts.tv_sec)));
*/
	int id = 0;  

	pcap_loop(handle, 2, getPacket, (u_char*)&id); 
  
	

	
	pcap_close(handle);
	return 0;
}
void getPacket(u_char * arg, const struct pcap_pkthdr * pkthdr, const u_char * packet)  
{  
  int * id = (int *)arg;  
    
  printf("id: %d\n", ++(*id));  
  printf("Packet length: %d\n", pkthdr->len);  
  printf("Number of bytes: %d\n", pkthdr->caplen);  
  printf("Recieved time: %s", ctime((const time_t *)&(pkthdr->ts.tv_sec)));   
    
  int i;  
  for(i=0; i<pkthdr->len; ++i)  
  {  
    printf(" %02x", packet[i]);  
    if( (i + 1) % 16 == 0 )  
    {  
      printf("\n");  
    }  
  }  
    
  printf("\n\n");  
}  
	
	


























