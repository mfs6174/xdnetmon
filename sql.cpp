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

void sqlflow(std::basic_string<char, std::char_traits<char>, std::allocator<char> > const & ss,long long liu,long long kai,long long tt)
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

void sqlspeed(std::basic_string<char, std::char_traits<char>, std::allocator<char> > const & ss,long long liu,long long tt)
{
  yuju="INSERT INTO speed VALUES ('"+getmac(ss)+"','"+getip(ss)+","+str((double)liu/shezhi.jiange)+","+str(tt)+"')";
  sqlf=sqlite3_exec(db,yuju.c_str(),NULL,NULL,&sqlerr);
  sqlgeterr(sqlf);
}





