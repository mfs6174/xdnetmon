const char tmp[]="netmontmp",conf[]="~/.netmon.conf";

void shishi(long long x)
{
  ofstream ioff;
  if (!ioff.open(tmp))
    cerr<<"无法写入临时文件，可能会导致统计不准确"<<endl;
  ioff<<setw(64)<<setfill('0')<<right<<x;
  ioff.close();
}

long long dubenyue()
{
  return 0;
}

void xiebenyue(long long x)
{
}

void xiegongzuo(long long x)
{
}

void chushidu()
{
  ifstream ioff;
  long long t;
  if (ioff.open(tmp))
    if (ioff>>t)
      if (t)
        xiebenyue(benyue+=t);
  ioff.close();
}

void guanbixie()
{
  xiebenyue(benyue+gongzuo);
  shishi(0);
}

void dushezhi()
{

}

      
  
