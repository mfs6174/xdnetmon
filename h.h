/*
 * File: h.h 
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

struct Shezhi
{
  string dev;
  bool mode,zhiding,log;
  long long  jiange,pian;
};

struct D
{
  long long liu,kai;
};

void pcapinit();
void huidiao(u_char *a,const struct pcap_pkthdr *b,const u_char *c);
int pushmap(const string &a,int b);
int setmap();
void tuichu(int a);
void timer(int no);
void sqlflow(const string &,long long, long long, long long);
void sqlspeed(const string &,long long, long long);
void sqlinit();
void sqlexit();
double _mb(long long x);
double _kb(long long x);
   

