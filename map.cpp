#include "include.h"
#include "h.h"

extern map<string,long long> hash;
extern map<string,int> sudu;

int pushmap(const string &x,int y)
{
  map<string,long long>::iterator p=hash.find(x);
  if (p!=hash.end())
    (*p).second+=y;
  else
  {
    hash.insert(map<string,long long>::value_type(x,y));
    // sudu.insert(map<string,int>::value_type(x,0));
  }
  return hash.size();
}

int setmap()
{
  for (map<string,long long>::iterator i=hash.begin();i!=hash.end();i++)
    (*i).second=0;
  return hash.size();
}



