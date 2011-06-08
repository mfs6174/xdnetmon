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
int setmap();
void tuichu(int a);
void timer(int no);
void sqlflow(const string &,long long, long long, long long);
void sqlspeed(const string &,long long, long long);
void sqlinit();
void sqlexit();
double _mb(long long x);

   

