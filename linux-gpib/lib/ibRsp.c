
#include "ib_internal.h"
#include <ibP.h>

int ibrsp(int ud, char *spr)
{
return  ibBoardFunc( CONF(ud,board),
                     ((CONF(ud,flags)&CN_AUTOPOLL) ? IBAPRSP : DVRSP),
                     CONF(ud,padsad), spr);
}
