struct Shezhi
{
  string dev;
  bool mode,zhiding;
  int  jiange,shijianpian;
};

void pcapinit();
void huidiao(u_char *a,const struct pcap_pkthdr *b,const u_char *c);
int pushmap(const string &a,int b);
int setmap();


