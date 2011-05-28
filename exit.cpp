#include "include.h"
#include "h.h"
extern pcap_t *pp;
extern Shezhi shezhi;
void tuichu()
{
  pcap_close(pp);
  alarm(0);
  cout<<"本次运行期间共产生流量"<<fixed<<setprecision(3)<<_mb(zonghe)<<" 本月流量已用"<<_mb(getmon())<<" 剩余"<<_mb(shezhi.keyong-getmon())<<endl;
  sqlexit();
  exit(0);
}

