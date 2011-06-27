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


extern map<string,D> hash; //var.cpp 中的全局变量,缓存,在两次数据库操作之间存储流量,first是ID字符串,second是保存起始时间和流量的结构体
extern long long zonghe; //var.cpp中的全局变量,保存工作期间的总流量

int pushmap(const string &x,int y) //每次收到数据包后将流量加入缓存,x是包对应的ID字符串,y是包大小(取int是因为单个包大小不会太大)
{
  map<string,D>::iterator p=hash.find(x);//寻找缓存内此ID的数据,得到对应的迭代器
  if (p!=hash.end())
    (*p).second.liu+=y;//如果有此ID,流量加上本次包的大小
  else
  {
    D tmp;//否则在缓存中增加此ID的记录
    tmp.liu=y;
    tmp.kai=time(NULL);//开始时间为当前时刻
    hash.insert(map<string,D>::value_type(x,tmp));
  }
  return hash.size();
}

int setmap() //每次定时器调用的将缓存数据写入数据库,并且清空缓存中的流量,删除缓存中不活动的ID的记录
{
  long long t=time(NULL);
  for (map<string,D>::iterator i=hash.begin();i!=hash.end();)//遍历整个缓存的所有记录
  {
    if ((*i).second.liu==0)
    {
      hash.erase(i++);//如果两次调用的间隔内新增流量为0,说明此ID的网络连接是不活动的,去除此ID的记录,加快缓存工作速度
      continue;
    }
    long long tmp=(*i).second.liu;//用临时变量保存流量,以便尽快清空缓存中的流量,增加时间和流量对应的准确性
    (*i).second.liu=0;//清空记录中的
    zonghe+=tmp;//增加流量总和
    sqlflow((*i).first,tmp,(*i).second.kai,t);//调用sql.cpp中的sqlflow函数向数据库存储流量
    sqlspeed((*i).first,tmp,t);//调用sql.cpp中的sqlspeed函数向数据库中存储速度信息
    (*i).second.kai=t;//将缓存中记录的开始时间修改成当前时间
    i++;
  }
  return hash.size();
}



