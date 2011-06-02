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
void sqlspeed(std::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, long long, long long, long long);
void sqlflow(std::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, long long, long long);
void sqlinit();
void sqlexit();
double _mb(long long x);

   

