const int changdu=1;
char ebuf[PCAP_ERRBUF_SIZE];
char filter_exp[] = "src net 202.117.112.0 mask 255.255.240.0"; /* 过 滤表达式 */
bpf_u_int32 mask; /* 网 络掩码 */
bpf_u_int32 net; /* IP */
struct pcap_pkthdr header; /* pcap头 */
const u_char *packet; /* 数据包 */
string dev(shezhi.zhiding?(shezhi.dev):(pcap_lookupdev(ebuf)));
pcap_t *pp;

void pcapinit()
{
  pp=pcap_open_live(dev.c_str(),changdu,0,0,ebuf);
  pcap_lookupnet(NULL,&net,&mask,ebuf);
}

void huidiao(u_char *args, const struct pcap_pkthdr *tou,const u_char *bao)
{
  gongzuo+=tou->len;
  jiange+=tou->len;
  //cout<<tou->len<<endl;
    if (jiange>=_jiange)
    {
      shishi(gongzuo);
      jiange=0;
    }
}



  
