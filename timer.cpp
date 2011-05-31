#include "include.h"
#include "h.h"

extern Shezhi shezhi;

void timer(int no)
{
  alarm(0);
  setmap();
  alarm(shezhi.jiange);
}

