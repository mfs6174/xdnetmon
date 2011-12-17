/*
 * File: conf.cpp 
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
extern char ebuf[PCAP_ERRBUF_SIZE];
extern Shezhi shezhi;

void checkset(bool re=0)
{
  if (re)
  {
    ebuf[0]=0;
    shezhi.dev=pcap_lookupdev(ebuf);
    if (strlen(ebuf)>0)
      shezhi.dev="eth1";
    shezhi.outmode=0;
    shezhi.wat=0;
    shezhi.jiange=30;
    shezhi.pian=600;
    shezhi.nospd=0;
    shezhi.dff=1;
    shezhi.ftfile.clear();
    return;
  }
  ebuf[0]=0;
  if (shezhi.dev.size()<1)
     shezhi.dev=pcap_lookupdev(ebuf);
    // shezhi.dev="eth0";
  if (strlen(ebuf)>0)
    shezhi.dev="eth1";
  if (shezhi.outmode>2)
    shezhi.outmode=0;
  if (shezhi.wat>1||shezhi.wat<0)
    shezhi.wat=0;
  if (shezhi.jiange<1)
    shezhi.jiange=1;
  if (shezhi.pian<10)
    shezhi.pian=0;
  if (shezhi.nospd<0||shezhi.nospd>1)
    shezhi.nospd=0;
  if (shezhi.dff<0||shezhi.dff>1)
    shezhi.dff=1;
}

void writeset()
{
  checkset(0);
  sqlws();
}

void readset()
{
  int sta;
  sta=sqlrs();
  if (sta==0)
    checkset(0);
  else
  {
    checkset(1);
    writeset();
  }
}

void setset(int n,string v)
{
  static bool isstr[10]={0,1,0,0,0,0,0,1,0};
  if (isstr[n])
  {
    switch(n)
    {
    case 1:
      shezhi.dev=v;
      break;
    case 7:
      shezhi.dff=0;
      shezhi.ftfile=v;
      break;
    }
  }
  else
  {
    switch(n)
    {
    case 2:
      shezhi.outmode=val(v);
      break;
    case 3:
      shezhi.wat=val(v);
      break;
    case 4:
      shezhi.jiange=val(v);
      break;
    case 5:
      shezhi.pian=val(v);
      break;
    case 6:
      shezhi.nospd=val(v);
      break;
    }
  }
  checkset(0);
}
