#include "h.h"
#include "include.h"

sqlite *db=NULL;
char *sqlerr=0;
int sqlf;

int sqlinit()
{
  sqlf=sqlite3_open("netmon.db",&db);
  if (sqlf)
  {
    sqlite3_close(db);
    exit(1);
  }
}

void sqlexit()
{
  sqlite3_close(db);
}




