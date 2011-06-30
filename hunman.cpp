/*
 * File: hunman.cpp 
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

const int _mb_=1024*1024,_kb_=1024,_gb_=_mb_*1024;//三个常量,分别为KB,MB,GB与字节的换算倍数

double _kb(long long x)//把字节换算为kb,x为字节,返回double为kb
{
  return (double)x/_kb_;
}

double _mb(long long x)//把字节换算为mb,x为字节,返回double为kb
{
  return (double)x/_mb_;
}

double _gb(long long x)//把字节换算为gb,x为字节,返回double为kb
{
  return (double)x/_gb_;
}

