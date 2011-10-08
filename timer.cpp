/*
 * File: timer.cpp 
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

void timer(int no)//main.cpp中signal函数对SIGALRM计时器信号的回调函数,no是接收信号标号
{
  alarm(0);//关闭计时器,防止执行下面功能时计时器再次启动(不合理的shezhi.jiange?)
  setmap();//调用map.cpp中的setmap()函数将缓存map中的数据存入sqlite数据库,清空缓存流量
  string s;
  prout(false,s,false,s,false,s,false,s,false);
  alarm(shezhi.jiange);//重新开启计时器
}

