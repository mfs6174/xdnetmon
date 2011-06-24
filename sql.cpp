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

sqlite3 *db=NULL;
char *sqlerr=NULL;
int sqlf;
string yuju;
extern Shezhi shezhi;

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
  sqlf=sqlite3_exec(db,yuju.c_str(),NULL,NULL,&sqlerr);
  sqlgeterr(sqlf);
  yuju="CREATE TABLE IF NOT EXISTS speed ( mac TEXT,ip TEXT,rate DOUBLE,end DATETIME);";
  sqlf=sqlite3_exec(db,yuju.c_str(),NULL,NULL,&sqlerr);
  sqlgeterr(sqlf);
}

void sqlexit()//sql退出处理,关闭连接,释放内存
{
  sqlite3_close(db);
}

string str(long long x)//长整形转为字符串,用于构造sql语句串
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

string getmac(const string &ss)//在id串中提取mac地址部分
{
  return ss.substr(0,ss.find("##"));
}

string getip(const string &ss) //在id串中提取ip地址部分
{
 return ss.substr(ss.find("##")+2);
}

void sqlflow(const string &ss,long long liu,long long kai,long long tt) //向数据库写入流量信息
{
  char **jieguo=NULL;
  int hang=0,lie=0;
  string mac=getmac(ss),ip=getip(ss);
  yuju="SELECT * FROM flow WHERE mac='"+mac+"' AND ip='"+ip+"' AND ("+str(tt)+"-start<"+str(shezhi.pian)+");";
  //查询语句,用于检查是否含有间隔小于时间片的记录
  sqlf=sqlite3_get_table(db,yuju.c_str(),&jieguo,&hang,&lie,&sqlerr);
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
    sqlf=sqlite3_exec(db,yuju.c_str(),NULL,NULL,&sqlerr);
    sqlgeterr(sqlf);
  } 
}

void sqlspeed(const string &ss,long long liu,long long tt) //向数据库写入速度信息
{
  yuju="INSERT INTO speed VALUES ('"+getmac(ss)+"','"+getip(ss)+"',"+str(liu/shezhi.jiange)+",'"+str(tt)+"')";
  sqlf=sqlite3_exec(db,yuju.c_str(),NULL,NULL,&sqlerr);
  sqlgeterr(sqlf);
}

