#include "include.h"
#include "h.h"
const int changdu=60;
char ebuf[PCAP_ERRBUF_SIZE];
char filter_exp[] = "(not (net 202.117.112.0 mask 255.255.240.0)) and (not (net 222.25.128.0 mask 255.255.192.0)) and (not (net 219.245.64.0 mask 255.255.192.0)) and (not (net 219.244.112.0 mask 255.255.240.0)) and (not ( (dst net 192.168.0.0 mask 255.255.252.0) and (src net 192.168.0.0 mask 255.255.252.0) ) ) and (not (net 210.27.0.0 mask 255.255.240.0))"; /* 过 滤表达式 */
extern Shezhi shezhi;
struct bpf_program fp;
bpf_u_int32 mask; /* 网 络掩码 */
bpf_u_int32 net; /* IP */
struct pcap_pkthdr header; /* pcap头 */
const u_char *packet; /* 数据包 */
string dev(shezhi.zhiding?(shezhi.dev):(pcap_lookupdev(ebuf)));
pcap_t *pp;

void pcapinit()
{
  pp=pcap_open_live(dev.c_str(),changdu,0,0,ebuf);
  pcap_lookupnet(dev.c_str(),&net,&mask,ebuf);
  pcap_compile(pp, &fp, filter_exp, 1, net);
  pcap_setfilter(pp, &fp);
}

void huidiao(u_char *args, const struct pcap_pkthdr *tou,const u_char *bao)
{
  gongzuo+=tou->len;
  jiange+=tou->len;
  cout<<tou->len<<endl;
  /*
  if (jiange>=_jiange)
  {
    shishi(gongzuo);
    jiange=0;
  }
  */
}



  
