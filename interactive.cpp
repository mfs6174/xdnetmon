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
  cout<<"用法:netmon 选项"<<endl<<endl;
  cout<<"-d 网络设备名 指定网络设备 双网卡网关应指定对内网卡 不指定将使用第一个"<<endl;
  cout<<"-w 开启数据包内容嗅探过滤"<<endl;
  cout<<"-o 1,2,3输出模式 屏幕输出(默认) html网页 csv表格"<<endl;
  cout<<"-i 秒数 指定写数据库的频率 默认为30s"<<endl;
  cout<<"-t 秒数 指定流量记录的时间片宽度 时间片内的流量只计算总量 单位秒 默认600s"<<endl;
  cout<<"-s 保存设置 否则参数只对本次运行有效"<<endl;
  cout<<"-h 打印本帮助信息"<<endl;
  cout<<"-p 进入交互打印结果模式"<<endl<<endl;
  cout<<"每行一条命令 输入0退出"<<endl;
  cout<<"-m [MAC] -i [IP] -b [begintime] -e [endtime] -v -V"<<endl;
  cout<<"按顺序输入或不输入:查询指定MAC 查询指定IP 指定时间范围 显示详细记录(否则显示总和) 显示速度"<<endl;
}

void itof()
{
  string ss;
  while(1)
  {
    cin>>ss;
    if (ss[0]=='0')
      break;
    
  }
  
}


