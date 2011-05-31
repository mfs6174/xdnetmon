#include "include.h"
#include "h.h"
extern Shezhi shezhi;
extern pcap_t *pp;
int main()
{
  shezhi.zhiding=true;
  shezhi.dev="eth0";
  shezhi.jiange=30;
  shezhi.pian=300;
  signal(SIGHUP,tuichu);
  signal(SIGINT,tuichu);
  //signal(SIGKILL,tuichu);
  signal(SIGSTOP,tuichu);
  signal(SIGTERM,tuichu);
  //signal(SIGTSTP,tuichu);
  signal(SIGALRM,timer);
  sqlinit();
  pcapinit();
  alarm(shezhi.jiange);
  pcap_loop(pp,-1,huidiao,NULL);
  return 0;
}


