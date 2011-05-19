#include "include.h"
#include "var.h"
#include "h.h"
int main()
{
  /*
    dushezhi();
  chushidu();
  signal(SIGHUP,tuichu);
  signal(SIGINT,tuichu);
  signal(SIGKILL,tuichu);
  signal(SIGSTOP,tuichu);
  signal(SIGTERM,tuichu);
  signal(SIGTSTP,tuichu);
  */
  pcapinit();
  pcap_loop(pp,-1,huidiao,NULL);
  return 0;
}


