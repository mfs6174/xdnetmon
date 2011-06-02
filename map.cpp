#include "include.h"
#include "h.h"


extern map<string,D> hash;
extern long long zonghe;
extern char sss[255];

int pushmap(const string &x,int y)
{
  map<string,D>::iterator p=hash.find(x);
  if (p!=hash.end())
    (*p).second.liu+=y;
  else
  {
    D tmp;
    tmp.liu=y;
    tmp.kai=time(NULL);
    hash.insert(map<string,D>::value_type(x,tmp));
  }
  return hash.size();
}

int setmap()
{
  long long t=time(NULL);
  for (map<string,D>::iterator i=hash.begin();i!=hash.end();)
  {
    if ((*i).second.liu==0)
    {
      hash.erase(i++);
      continue;
    }
    long long tmp=(*i).second.liu;
    (*i).second.liu=0;
    zonghe+=tmp;
    strcpy(sss,(*i).first.c_str());
    sqlspeed(tmp,(*i).second.kai,t);
    sqlflow(tmp,t);
    (*i).second.kai=t;
    i++;
  }
  return hash.size();
}



