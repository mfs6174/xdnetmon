/*
 * File: sql.cpp 
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

sqlite3 *db=NULL;//数据库句柄
char *sqlerr=NULL;//指向错误信息的字符指针
int sqlf;//sql执行结果
string yuju;//存放执行语句
extern Shezhi shezhi;//var.cpp中的全局变量,设置

/*
 *如果修改或添加设置项 需要在本文件中修改 sqlinit sqlrs sqlws函数
 */

void sqlgeterr(int s) //sql错误处理,判断是否出错,参数s为sql执行状态,输出错误信息,每次执行完sql语句调用一次
{
  if (s) //如果返回的不是sql正常
  {
    cout<<s<<endl<<sqlerr<<endl; //输出错误信息
    tuichu(-1); //调用退出函数,尽量正常退出
  }
}

void sqlinit() //sql数据库初始化,打开或新建数据库,如果新建,新建表
{
  sqlf=sqlite3_open("netmon.db",&db);//打开数据库
  sqlgeterr(sqlf);
  //以下新建2个表
  yuju="CREATE TABLE IF NOT EXISTS flow ( mac TEXT,ip TEXT,data INT,start DATETIME,end DATETIME);";
  //表名:flow 表结构:mac ip为字符串,data为整数,单位是字节,start和end为起止时间,用unix时间戳表示
  sqlf=sqlite3_exec(db,yuju.c_str(),NULL,NULL,&sqlerr);
  sqlgeterr(sqlf);
  yuju="CREATE TABLE IF NOT EXISTS speed ( mac TEXT,ip TEXT,rate DOUBLE,end DATETIME);";
  //表名:speed 表结构: mac ip为字符串,rate为浮点数,单位是字节/秒,end为本速度区间的结束时刻,unix时间戳表示
  sqlf=sqlite3_exec(db,yuju.c_str(),NULL,NULL,&sqlerr);
  sqlgeterr(sqlf);
  yuju="CREATE TABLE IF NOT EXISTS conf ( dev TEXT,outmode INT,wat INT,jiange INT,pian INT,nospd INT,dff INT,ftfile TEXT );";
  //表名:settings 设置信息
  sqlf=sqlite3_exec(db,yuju.c_str(),NULL,NULL,&sqlerr);
  sqlgeterr(sqlf);
}

void sqlexit()//sql退出处理,关闭连接,释放内存
{
  sqlite3_close(db);
  if (sqlerr!=NULL)
    sqlite3_free(sqlerr);
}

string str(long long x)//长整形转为字符串,用于构造sql语句串
{
    ostringstream t;
    t<<x;
    return t.str();
}

string str(int x)//长整形转为字符串,用于构造sql语句串
{
    ostringstream t;
    t<<x;
    return t.str();
}

string str(double x)//浮点数转为字符串,构造sql语句用
{
  ostringstream t;
  t<<x;
  return t.str();
}

long long val(const string &x)//转换字符串为长整形
{
    istringstream t(x);
    long long  r;
    t>>r;
    return r;
}

string getmac(const string &ss)//在id串中提取mac地址部分 ss是构造好的ID串,返回mac字符串
{
  return ss.substr(0,ss.find("##"));
}

string getip(const string &ss) //在id串中提取ip地址部分 ss是构造好的ID串,返回ip字符串
{
 return ss.substr(ss.find("##")+2);
}

void sqlflow(const string &ss,long long liu,long long kai,long long tt) //向数据库写入流量信息
//ss是ID字符串,liu是流量,kai是起始时间,tt是终止时间
{
  char **jieguo=NULL;
  int hang=0,lie=0;
  string mac=getmac(ss),ip=getip(ss);
  yuju="SELECT * FROM flow WHERE mac='"+mac+"' AND ip='"+ip+"' AND ("+str(tt)+"-start<"+str(shezhi.pian)+");";
  //查询语句,用于检查是否含有间隔小于时间片的记录
  sqlf=sqlite3_get_table(db,yuju.c_str(),&jieguo,&hang,&lie,&sqlerr);
  if (jieguo!=NULL)
    sqlite3_free_table(jieguo);
  sqlgeterr(sqlf);
  if (!hang)//如果没有
  {
    yuju="INSERT INTO flow VALUES ('"+mac+"','"+ip+"',"+str(liu)+",'"+str(kai)+"','"+str(tt)+"');";
    //插入语句,插入一条记录
    sqlf=sqlite3_exec(db,yuju.c_str(),NULL,NULL,&sqlerr);
    sqlgeterr(sqlf);
  }
  else
  {
    if (hang>1)
    {
      exit(-1);
    }
    yuju="UPDATE flow SET data=data+"+str(liu)+",end='"+str(tt)+"' WHERE mac='"+mac+"' AND ip='"+ip+"' AND (";
    yuju+=str(tt)+"-start<"+str(shezhi.pian)+");";
    //更新语句,更新间隔小于时间片的记录,最后,同一个IP MAC组合的每条记录间隔都大于时间片,期间的流量累加
    sqlf=sqlite3_exec(db,yuju.c_str(),NULL,NULL,&sqlerr);
    sqlgeterr(sqlf);
  } 
}

void sqlspeed(const string &ss,long long liu,long long tt) //向数据库写入速度信息
//ss是ID串,liu是流量,tt是截止时间
{
  yuju="INSERT INTO speed VALUES ('"+getmac(ss)+"','"+getip(ss)+"',"+str(liu/shezhi.jiange)+",'"+str(tt)+"')";
  //插入语句,每次插入此IP MAC组合数据库更新间隔中的平均速度
  sqlf=sqlite3_exec(db,yuju.c_str(),NULL,NULL,&sqlerr);
  sqlgeterr(sqlf);
}

void sqlws()
{
  yuju="UPDATE conf SET dev='"+shezhi.dev+"',outmode="+str(shezhi.outmode)+",wat="+str(shezhi.wat)+",jiange="+str(shezhi.jiange)+",pian="+str(shezhi.pian)+",nospd="+str(shezhi.nospd)+",dff="+str(shezhi.dff)+",ftfile='"+shezhi.ftfile+"' ";
  cout<<yuju<<endl;
  sqlf=sqlite3_exec(db,yuju.c_str(),NULL,NULL,&sqlerr);
  sqlgeterr(sqlf);
}

int sqlrs()
{
  char **jieguo=NULL;
  int hang=0,lie=0;
  yuju="SELECT * FROM conf;";
  sqlf=sqlite3_get_table(db,yuju.c_str(),&jieguo,&hang,&lie,&sqlerr);
  if (hang<1)
  {
    if (jieguo!=NULL)
      sqlite3_free_table(jieguo);
    sqlgeterr(sqlf);
    return -1;
  }
  shezhi.dev=jieguo[lie];
  shezhi.outmode=val(string(jieguo[lie+1]));
  shezhi.wat=val(string(jieguo[lie+2]));
  shezhi.jiange=val(string(jieguo[lie+3]));
  shezhi.pian=val(string(jieguo[lie+4]));
  shezhi.nospd=val(string(jieguo[lie+5]));
  shezhi.dff=val(string(jieguo[lie+6]));
  shezhi.ftfile=string(jieguo[lie+7]);
  if (jieguo!=NULL)
    sqlite3_free_table(jieguo);
  return 0;
}

char ** sqlqr(const string &s,int &hang,int &lie)
{
  char **jieguo=NULL;
  hang=0,lie=0;
  sqlf=sqlite3_get_table(db,s.c_str(),&jieguo,&hang,&lie,&sqlerr);
  sqlgeterr(sqlf);
  return jieguo;
}

