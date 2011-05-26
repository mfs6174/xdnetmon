#include "include.h"
#include "h.h"

extern Shezhi shezhi;

int timer()
{
  alarm(0);
  long long chuo=time(NULL);
  setmap(chuo);
  alarm(shezhi.jiange);
  return 0;
}

