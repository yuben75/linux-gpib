
#include <ib.h>
#include <ibP.h>

int ibSdbg(int ud,int mode)
{
  return ibBoardFunc( CONF(ud,board),IBSDBG, mode );
}
