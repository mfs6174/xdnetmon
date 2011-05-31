#include "include.h"
#include "h.h"
extern pcap_t *pp;
extern Shezhi shezhi;
extern long long zonghe;
void tuichu(int s)
{
  if (s==-1)
  {
    pcap_close(pp);
    alarm(0);
    sqlexit();
    exit(-1);
  }
  cout<<"收到信号"<<s<<"是否让程序退出?y or n";
  char ct;
  cin>>ct;
  if (ct=='y'||ct=='Y')
  {
    pcap_close(pp);
    alarm(0);
    sqlexit();
    cout<<"程序终止,本次运行期间共产生外网流量"<<fixed<<setprecision(3)<<_mb(zonghe)<<endl;
    exit(0);
  }
}

