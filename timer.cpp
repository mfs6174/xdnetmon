#include "include.h"
#include "h.h"

extern Shezhi shezhi;

int timer()
{
  alarm(0);
  setmap();
  alarm(shezhi.jiange);
  return 0;
}

