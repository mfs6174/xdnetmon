#include "include.h"
#include "h.h"
extern pcap_t *pp;
void tuichu()
{
  alarm(0);
  pcap_close(pp);
  timer();
  cout<<"本次运行期间共产生流量"<<fixed<<setprecision(3)<<_mb(zonghe)<<" 本月流量已用"<<_mb(gongzuo+benyue)<<" 剩余"<<_mb(shezhi.keyong-gongzuo-benyue)<<endl;
  exit(0);
}

