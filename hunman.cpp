#include "include.h"
#include "h.h"

const int _mb_=1024*1024,_kb_=1024,_gb_=_mb_*1024;

double _kb(long long x)
{
  return (double)x/_kb_;
}

double _mb(long long x)
{
  return (double)x/_mb_;
}

double _gb(long long x)
{
  return (double)x/_gb_;
}

