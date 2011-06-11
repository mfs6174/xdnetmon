/*
 * File: exit.cpp 
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
extern pcap_t *pp;
extern Shezhi shezhi;
extern long long zonghe;
void tuichu(int s)
{
  if (s==-1)
  {
    pcap_close(pp);
    alarm(0);
    sqlexit();
    exit(-1);
  }
  cout<<"收到信号"<<s<<"是否让程序退出?y or n ";
  char ct;
  cin>>ct;
  if (ct=='y'||ct=='Y')
  {
    pcap_close(pp);
    alarm(0);
    setmap();
    sqlexit();
    cout<<"程序终止,本次运行期间共产生外网流量"<<fixed<<setprecision(3)<<_mb(zonghe)<<"MB"<<endl;
    exit(0);
  }
}

