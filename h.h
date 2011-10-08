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

//本文件为各全局结构体等数据类型的定义
//以及跨文件使用的函数的声明
//每个其他源码文件都应该包含本头文件

struct Shezhi//设置信息结构体
{
  string dev;//设备名字符串
  int outmode,wat;//工作模式等开关
  long long  jiange,pian;//写数据库间隔和时间片的设置数值
};
struct D //流量缓存中保存流量和时间信息的结构体
{
  long long liu,kai;//liu为流量,kai为本记录的开始时刻
};
//以下为跨文件使用的函数的声明
void prout(bool fmac,string mac,bool fip,string ip,bool fbt,string bt,bool fet,string et,bool vb);
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
void sqlws();
int sqlrs();
long long val(const string &x);   
void setset(int ,string );
void readset();
void writeset();
void pfhelp();
void itof();
char ** sqlqr(const string &,int &,int &);
