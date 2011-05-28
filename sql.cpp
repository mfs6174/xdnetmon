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

void sqlflow(const string &ss,long long liu,long long kai,long long tt)
{
  yuju="INSERT INTO flow SELECT * FROM flow WHERE mac='"+ss.substr(ss.begin(),ss.find("##"))+"' AND ip='"+ss.substr(ss.find("##")+2)+"' AND -start<";
}

void sqlspeed(const string &ss,long long liu,long long tt)
{
  yuju="INSERT INTO speed VALUES ('"+ss.substr(ss.begin(),ss.find("##"))+"','"+ss.substr(ss.find("##")+2)+"','"+str(liu)+"','"+str(tt)+"')";
  sqlf=sqlite3_exec(db,yuju.c_str(),NULL,NULL,&sqlerr);
}





