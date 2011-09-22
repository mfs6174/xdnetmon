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
int main()
{
  shezhi.dev="eth1";
  shezhi.jiange=30;
  shezhi.pian=300;
  signal(SIGHUP,tuichu);
  signal(SIGINT,tuichu);
  //signal(SIGKILL,tuichu);
  signal(SIGSTOP,tuichu);
  signal(SIGTERM,tuichu);
  //signal(SIGTSTP,tuichu);
  signal(SIGALRM,timer);
  sqlinit();
  pcapinit();
  alarm(shezhi.jiange);
  pcap_loop(pp,-1,huidiao,NULL);
  return 0;
}


