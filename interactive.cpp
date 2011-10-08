/*
 * File: interactive.cpp 
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

void pfhelp()
{
  cout<<endl<<"用法:netmon 选项"<<endl<<endl;
  cout<<"-d 网络设备名 指定网络设备 双网卡网关应指定对内网卡 不指定将使用第一个"<<endl;
  cout<<"-w 开启数据包内容嗅探过滤"<<endl;
  cout<<"-o 1,2,3输出模式 屏幕输出(默认) html网页 csv表格"<<endl;
  cout<<"-i 秒数 指定写数据库的频率 默认为30s"<<endl;
  cout<<"-t 秒数 指定流量记录的时间片宽度 时间片内的流量只计算总量 单位秒 默认600s"<<endl;
  cout<<"-s 保存设置 否则参数只对本次运行有效"<<endl;
  cout<<"-h 打印本帮助信息"<<endl;
  cout<<"-p 进入交互打印结果模式"<<endl<<endl;
  cout<<"每行一条命令 以go结束 输入q退出 "<<endl;
  cout<<"-m [MAC] -i [IP] -b [begintime] -e [endtime] -v -V go"<<endl;
  cout<<"按顺序输入或不输入:查询指定MAC 查询指定IP 指定时间范围 显示详细记录(否则显示总和) 显示速度"<<endl;
}

void prout(bool fmac,string &mac,bool fip,string &ip,bool fbt,string &bt,bool fet,string &et,bool vb)
{
  string csql;
  char **rr=NULL;
  if (!fbt)
    bt="0";
  if (!fet)
    et="2147483647";
  if (vb)
    csql="SELECT mac,ip,data/1024/1024.0,end FROM flow ";
  else
    csql="SELECT mac,ip,sum(data)/1024/1024.0,end FROM flow ";
  csql=csql+"WHERE ";
  csql+="(start>"+bt+") ";
  csql+="AND (end<"+et+") ";
  if (fmac)
    csql+="AND mac='"+mac+"' ";
  if (fip)
    csql+="AND ip='"+ip+"'";
  csql+=" GROUP BY mac;";
  int ii=0,i,j,hang=0,lie=0;
  rr=sqlqr(csql,hang,lie);
  string html="<html> <head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" /> <link rel=\"stylesheet\" type=\"text/css\" media=\"all\" href=\"css/style.css\" /> <title>netmon result</title> </head> <body> <table> <tr>";
  for (i=1;i<=lie;i++)
    html+="<td>"+string(rr[ii++])+"</td>";
  for (i=1;i<=hang;i++)
  {
    html+="</tr> <tr>";
    for (j=1;j<=lie;j++)
      html+="<td>"+string(rr[ii++])+"</td>";
  }
  if (rr!=NULL)
    sqlite3_free_table(rr);
  html+="</tr> </table> </body> </html>";
  ofstream ouf("result.html");
  ouf<<html<<endl;
}

void itof()
{
  string ss,mac,ip,bt,et;
  bool vb,fmac,fip,fbt,fet;
  while(1)
  {
    cin>>ss;
    if (ss[0]=='q')
      break;
    vb=fmac=fip=fbt=fet=false;
    while (ss!="go")
    {
      switch(ss[1])
      {
      case 'm':
        cin>>mac;
        fmac=true;
        break;
      case 'i':
        cin>>ip;
        fip=true;
        break;
      case 'b':
        cin>>bt;
        fbt=true;
        break;
      case 'e':
        cin>>et;
        fet=true;
        break;
      case 'v':
        vb=true;
        break;
      default:
        cout<<"命令错误,无效输入,本行输入被抛弃"<<endl;
      }
      cin>>ss;
    }
    prout(fmac,mac,fip,ip,fbt,bt,fet,et,vb);
  }
}


