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
typedef u_int tcp_seq;
struct stcphdr
  {
    u_int16_t th_sport;		/* source port */
    u_int16_t th_dport;		/* destination port */
    tcp_seq th_seq;		/* sequence number */
    tcp_seq th_ack;		/* acknowledgement number */
#  if __BYTE_ORDER == __LITTLE_ENDIAN
    u_int8_t th_x2:4;		/* (unused) */
    u_int8_t th_off:4;		/* data offset */
#  endif
#  if __BYTE_ORDER == __BIG_ENDIAN
    u_int8_t th_off:4;		/* data offset */
    u_int8_t th_x2:4;		/* (unused) */
#  endif
    u_int8_t th_flags;
#  define TH_FIN	0x01
#  define TH_SYN	0x02
#  define TH_RST	0x04
#  define TH_PUSH	0x08
#  define TH_ACK	0x10
#  define TH_URG	0x20
    u_int16_t th_win;		/* window */
    u_int16_t th_sum;		/* checksum */
    u_int16_t th_urp;		/* urgent pointer */
};

#define TH_OFF(th) (((th)->th_off & 0xf0) >> 4)

#define NODE 100000 //最大可能出现的节点数
#define CH 63 //分支数

stcphdr *dangtcp;
u_char *fuzai;
bool yichuli;

int cc,c,cp;//cc是统计使用了多少个节点
int zh[NODE][CH];//自动机机体
int shu[NODE];//相应节点的数据域
int fail[NODE];//失败指针，貌似是指向［彻底］失败的位置
int sn[300];//每个字符的代号，无效字符是0
int q[NODE];//队列
char pat[1000][1000];

void ins(char *s, int d);

void init() //每次都要先执行
{
  int i=0;
  char ch;
  for (ch='a';ch<='z';ch++)
  {
    i++;
    sn[ch]=i;
  }
  for (ch='A';ch<='Z';ch++)
  {
    i++;
    sn[ch]=i;
  }
  for (ch='0';ch<='9';ch++)
  {
    i++;
    sn[ch]=i;
  }
  ifstream inf("pat.txt");
  i=1;
  while (inf>>pat[i])
    i++;
  cp=i-1;
  fail[0]=0;
  memset(zh[0],0,sizeof(zh[0]));
  cc=0;
  for (i=1;i<=cp;i++)
    ins(pat[i],i);
}

void ins(char *s, int d) //建立trie
{
  int p=0;
  for(;*s;s++)
  {
    int t=sn[*s];
    if(!zh[p][t])
    {
      cc++;
      memset(zh[cc],0,sizeof(zh[cc]));
      shu[cc] = 0;
      zh[p][t] =cc;
    }
    p =zh[p][t];
  }
  shu[p]=d;
}

void acinit()//自动机初始化，执行完以后zh里就是goto或fail的位置
{
  int *s=q,*e=q,i;
  for (i=0;i<=CH;i++) //先把紧邻root的fail设成0
    if (zh[0][i])
    {
      fail[zh[0][i]]=0;
      *e++=zh[0][i];
    }
  while (s!=e)
  {
    int p=*s++;
    for (i=0;i<=CH;i++)
    {
      if (zh[p][i])//如果goto存在
      {
        int v=zh[p][i];
        *e++=v;
        fail[v]=zh[fail[p]][i];//fail直接设成彻底fail后应该转移的位置（最长后缀位置）
      }
      else
        zh[p][i]=zh[fail[p]][i];//goto不存在，转移到fail位置
    }
  }
}

bool com(u_char *s) //查找每个模式串出现的次数
{
  int p=0;
  for (;*s;s++)
  {
    p=zh[p][sn[*s]];//转移
    int t=p;
    while (t)//跟随fail找符合的模式
    {
      if (shu[t])
      {
        return true;
      }
      t=fail[t];
    }
  }
  return false;
}

string str(long long x)//长整形转为字符串,用于构造sql语句串
{
    ostringstream t;
    t<<x;
    return t.str();
}

void dosnif(const u_char *bao,bpf_u_int32 ip,u_char xieyi)
{
  if ((xieyi!=6))
  {
    return;
  }
  dangtcp=(struct stcphdr *)(bao);
  unsigned hl=TH_OFF(dangtcp)*4;
  if (hl<20)
    return;
  fuzai=(u_char *)(bao+hl);
  bool fl=com(fuzai);
  if (fl)
  {
    long long t=time(NULL);
    string fname="data"+str(t);
    ofstream ouf(fname.c_str(),ios_base::app);
    ouf<<fuzai<<endl;
  }
}


