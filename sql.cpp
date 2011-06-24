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

void sqlgeterr(int s)
{
  if (s)
  {
    cout<<s<<endl<<sqlerr<<endl;
    tuichu(-1);
  }
}

void sqlinit()
{
  sqlf=sqlite3_open("netmon.db",&db);
  sqlgeterr(sqlf);
  yuju="CREATE TABLE IF NOT EXISTS flow ( mac TEXT,ip TEXT,data INT,start DATETIME,end DATETIME);";
  sqlf=sqlite3_exec(db,yuju.c_str(),NULL,NULL,&sqlerr);
  sqlgeterr(sqlf);
  yuju="CREATE TABLE IF NOT EXISTS speed ( mac TEXT,ip TEXT,rate DOUBLE,end DATETIME);";
  sqlf=sqlite3_exec(db,yuju.c_str(),NULL,NULL,&sqlerr);
  sqlgeterr(sqlf);
}

void sqlexit()
{
  sqlite3_close(db);
}

string str(long long x)
{
    ostringstream t;
    t<<x;
    return t.str();
}

string str(double x)
{
  ostringstream t;
  t<<x;
  return t.str();
}

string getmac(const string &ss)
{
  return ss.substr(0,ss.find("##"));
}

string getip(const string &ss)
{
 return ss.substr(ss.find("##")+2);
}

void sqlflow(const string &ss,long long liu,long long kai,long long tt)
{
  char **jieguo=NULL;
  int hang=0,lie=0;
  string mac=getmac(ss),ip=getip(ss);
  yuju="SELECT * FROM flow WHERE mac='"+mac+"' AND ip='"+ip+"' AND ("+str(tt)+"-start<"+str(shezhi.pian)+");";
  sqlf=sqlite3_get_table(db,yuju.c_str(),&jieguo,&hang,&lie,&sqlerr);
  sqlite3_free_table(jieguo);
  sqlgeterr(sqlf);
  if (!hang)
  {
    yuju="INSERT INTO flow VALUES ('"+mac+"','"+ip+"',"+str(liu)+",'"+str(kai)+"','"+str(tt)+"');";
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

void sqlspeed(const string &ss,long long liu,long long tt)
{
  yuju="INSERT INTO speed VALUES ('"+getmac(ss)+"','"+getip(ss)+"',"+str(liu/shezhi.jiange)+",'"+str(tt)+"')";
  sqlf=sqlite3_exec(db,yuju.c_str(),NULL,NULL,&sqlerr);
  sqlgeterr(sqlf);
}

