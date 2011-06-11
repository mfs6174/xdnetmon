/*
 * File: map.cpp 
 * Author: Zhang Xijin(mfs6174)
 * Email: mfs6174@gmail.com
 *
 * Copyright (C) 2011 Zhang Xijin(mfs6174)
 *
 * This file is part of XDnetmon.
 *
 * XDnetmon is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * XDnetmon is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with XDnetmon.  If not, see <http://www.gnu.org/licenses/>.
 */

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
    //strcpy(sss,(*i).first.c_str());
    sqlflow((*i).first,tmp,(*i).second.kai,t);
    sqlspeed((*i).first,tmp,t);
    (*i).second.kai=t;
    i++;
  }
  return hash.size();
}



