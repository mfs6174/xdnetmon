struct Shezhi
{
  string dev;
  bool mode,zhiding,log;
  long long  jiange,pian;
};

struct D
{
  long long liu,kai;
};

void pcapinit();
void huidiao(u_char *a,const struct pcap_pkthdr *b,const u_char *c);
int pushmap(const string &a,int b);
int setmap(long long a);
void tuichu();
int timer();
void sqlspeed(const string &a,long long b,long long c,long long d);
void sqlflow(const string &a,long long b,long long c);
void sqlinit();
void sqlexit();

   

