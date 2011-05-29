#include "h.h"
#include "include.h"

sqlite *db=NULL;
char *sqlerr=NULL;
int sqlf;
string yuju,ttt;

void sqlinit()
{
  sqlf=sqlite3_open("netmon.db",&db);
  if (sqlf)
  {
    sqlite3_close(db);
    exit(1);
  }
  yuju="CREATE TABLE IF NOT EXISTS flow ( mac TEXT,ip TEXT,data INT,start DATETIME,end DATETIME)";
  sqlf=sqlite3_exec(db,yuju.c_str(),NULL,NULL,&sqlerr);
  yuju="CREATE TABLE IF NOT EXISTS speed ( mac TEXT,ip TEXT,rate INT,end DATETIME)";
  sqlf=sqlite3_exec(db,yuju.c_str(),NULL,NULL,&sqlerr);
}

void sqlexit()
{
  sqlite3_close(db);
}

string getmac(const string &ss);
{
  return ss.substr(ss.begin(),ss.find("##"));
}

string getip(const string &ss)
{
  ss.substr(ss.find("##")+2);
}

void sqlflow(const string &ss,long long liu,long long kai,long long tt)
{
  bool cunzai=false;
  string mac=getmac(ss),ip=getip(ss);
  yuju="INSERT INTO flow SELECT * FROM flow WHERE mac='"+mac+"' AND ip='"+ip+"' AND ("+str(tt)+"-start<"+str(shezhi.pian);
  if (!cunzai)
  {
    yuju="INSERT INTO flow VALUES ('"+mac+"','"+ip+"','"+str(liu)+"','"+str(kai)+"','"+str(tt)+"')";
    sqlf=sqlite3_exec(db,yuju.c_str(),NULL,NULL,&sqlerr);
  }
  else
  {
    
  
}

void sqlspeed(const string &ss,long long liu,long long tt)
{
  yuju="INSERT INTO speed VALUES ('"+getmac(ss)+"','"+getip(ss)+"','"+str(liu)+"','"+str(tt)+"')";
  sqlf=sqlite3_exec(db,yuju.c_str(),NULL,NULL,&sqlerr);
}





