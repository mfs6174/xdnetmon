/*
 * File: main.cpp 
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
extern Shezhi shezhi;
extern pcap_t *pp;
bool fl_xsz,fl_dym,fl_zd,fl_hp;

int main(int argc, char *argv[])
{
  signal(SIGHUP,tuichu);
  signal(SIGINT,tuichu);
  //signal(SIGKILL,tuichu);
  signal(SIGSTOP,tuichu);
  signal(SIGTERM,tuichu);
  //signal(SIGTSTP,tuichu);
  signal(SIGALRM,timer);
  sqlinit();
  readset();
  int oc;
  string tp;
  while((oc=getopt(argc,argv,"d:i:t:o:wsph"))!=-1)
  {
    switch(oc)
    {
    case 'd':
      tp=optarg;
      setset(1,tp);
      fl_zd=true;
      break;
    case 'i':
      tp=optarg;
      setset(4,tp);
      break;
    case 't':
      tp=optarg;
      setset(5,tp);
      break;
    case 'o':
      tp=optarg;
      setset(2,tp);
      break;
    case 'w':
      setset(3,"1");
      break;
    case 's':
      fl_xsz=true;
      break;
    case 'p':
      fl_dym=true;
      break;
    case 'h':
      fl_hp=true;
      break;
    case '?':
      cout<<"命令参数错误,程序结束"<<endl;
      tuichu(-1);
      break;
    }
  }
  if (fl_hp)
  {
    pfhelp();
    exit(0);
  }
  if (fl_xsz)
    writeset();
  if (fl_dym)
  {
    itof();
    sqlexit();
    exit(0);
  }
  pcapinit();
  alarm(shezhi.jiange);
  if (shezhi.wat)
    acinit();
  pcap_loop(pp,-1,huidiao,NULL);
  return 0;
}


