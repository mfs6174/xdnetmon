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
extern pcap_t *pp;//pcapinit.cpp中的全局变量,此处声明用于关闭句柄
extern Shezhi shezhi;//var.cpp中的全局变量,设置信息的结构体
extern long long zonghe;//全局变量,工作过程中的总流量
void tuichu(int s)//正常退出的处理函数,s为状态
{
  if (s==-1)
  {
    //如果状态为-1,则为错误退出,之前错误信息应该已经输出
    pcap_close(pp);//关闭pcap的句柄
    alarm(0);//关闭定时器
    sqlexit();//执行sql.cpp中的sqlexit(),释放内存,正常关闭sqlite文件
    exit(-1);//错误退出
  }
  //否则,则为截获了会导致程序退出的系统信号
  cout<<"收到信号"<<s<<"是否让程序退出?y or n ";
  char ct;
  cin>>ct;
  if (ct=='y'||ct=='Y')
  {
    //用户确认退出,执行与上面错误退出一样的退出过程
    if (pp!=NULL)
      pcap_close(pp);
    alarm(0);
    setmap();//在关闭sqlite连接之前,可能位于两次数据库操作中间,所以最后一次清空缓存,写入数据库,防止流量丢失
    sqlexit();
    cout<<"程序终止,本次运行期间共产生外网流量"<<fixed<<setprecision(3)<<_mb(zonghe)<<"MB"<<endl;
    exit(0);
    //输出产生的从流量,正常退出
  }
}

