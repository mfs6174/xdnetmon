#include "include.h"
#include "h.h"
#define ETHER_ADDR_LEN 6
const int changdu=60;
const int Ethchangdu=14;
char ebuf[PCAP_ERRBUF_SIZE];
char filter_exp[] = "(not (net 202.117.112.0 mask 255.255.240.0)) and (not (net 222.25.128.0 mask 255.255.192.0)) and (not (net 219.245.64.0 mask 255.255.192.0)) and (not (net 219.244.112.0 mask 255.255.240.0)) and (not ( (dst net 192.168.0.0 mask 255.255.252.0) and (src net 192.168.0.0 mask 255.255.252.0) ) ) and (not (net 210.27.0.0 mask 255.255.240.0))"; /* 过 滤表达式 */
extern struct Shezhi shezhi;
struct bpf_program fp;
bpf_u_int32 mask; /* 网 络掩码 */
bpf_u_int32 net; /* IP */
struct pcap_pkthdr header; /* pcap头 */
const u_char *packet; /* 数据包 */
string dev(shezhi.zhiding?(shezhi.dev):(pcap_lookupdev(ebuf)));
pcap_t *pp;


//开始包转换部分

/* 以太网头 */
struct sniff_ethernet {
	u_char ether_dhost[ETHER_ADDR_LEN]; /* 目的地址 */
	u_char ether_shost[ETHER_ADDR_LEN]; /* 源地址 */
	u_short ether_type; /* IP? ARP? RARP? 等 */
};

/* IP 头 */
struct sniff_ip {
	u_char ip_vhl; /* version << 4 | header length >> 2 */
	u_char ip_tos; /* type of service */
	u_short ip_len; /* total length */
	u_short ip_id; /* identification */
	u_short ip_off; /* fragment offset field */
#define IP_RF 0x8000 /* reserved fragment flag */
#define IP_DF 0x4000 /* dont fragment flag */
#define IP_MF 0x2000 /* more fragments flag */
#define IP_OFFMASK 0x1fff /* mask for fragmenting bits */
	u_char ip_ttl; /* time to live */
	u_char ip_p; /* protocol */
	u_short ip_sum; /* checksum */
	struct in_addr ip_src,ip_dst; /* source and dest address */
};
#define IP_HL(ip) (((ip)->ip_vhl) & 0x0f)
#define IP_V(ip) (((ip)->ip_vhl) >> 4)

sniff_ip dangip;
sniff_ethernet dangeth;

void pcapinit() //初始化函数
{
  pp=pcap_open_live(dev.c_str(),changdu,0,0,ebuf);
  pcap_lookupnet(dev.c_str(),&net,&mask,ebuf);
  pcap_compile(pp, &fp, filter_exp, 1, net);
  pcap_setfilter(pp, &fp);
}

void zuoid(string &s,bool fl) //转换mac和ip为一个id字符串
{
  string ss;
  if (fl)
  {
    s=(char *)(dangeth.ether_shost);
    ss=inet_ntoa(dangip.ip_src);
    s=s+ss;
  }
  else
  {
    s=(char *)(dangeth.ether_dhost);
    ss=inet_ntoa(dangip.ip_dst);
    s=s+ss;
  }
}

void huidiao(u_char *args, const struct pcap_pkthdr *tou,const u_char *bao)//回调函数，解析数据包，写入map
{
  string id="";
  bool fl=false;
  static bpf_u_int32 pan=net&mask;
  // gongzuo+=tou->len;
  // jiange+=tou->len;
  // cout<<tou->len<<endl;
  dangeth=(struct sniff_ethernet *)(bao);
  dangip=(struct sniff_ip *)(bao+Ethchangdu);
  if ((dangip.ip_src.s_addr)&mask==pan)
    fl=true;
  else
    fl=false;
  zuoid(id,fl);
  pushmap(id,tou->len);
}



  
