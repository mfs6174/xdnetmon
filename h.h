struct Shezhi
{
  string dev;
  bool mode,zhiding;
  int  jiange;
};

void pcapinit();
void huidiao(u_char *a,const struct pcap_pkthdr *b,const u_char *c);
int pushmap(const string &a,int b);
int setmap();


