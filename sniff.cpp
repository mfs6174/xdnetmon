/*
 * File: sniff.cpp 
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

tcphdr *dangtcp;
char *fuai;
bool yichuli;

#define TH_OFF(th) (((th)->th_offx2 & 0xf0) >> 4)

void dosnif(u_char *bao,bpf_u_int32 ip,u_char xieyi)
{
  if (xieyi!=6)
  {
    return;
  }
  dangtcp=(struct tcphdr *)(bao);
  unsigned hl=TH_OFF(dangtcp)*4;
  if (hl<20)
    return;
  fuzai=(u_char *)(bao+hl);
  
}


