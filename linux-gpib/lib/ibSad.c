
#include <ib.h>
#include <ibP.h>

PUBLIC int ibsad(int ud, int v)
{
#if NO_RSD_PATCH
  return  ibBoardFunc(CONF(ud,board),IBSAD, v);
#else
   if (CONF(ud,flags) & CN_ISCNTL)
      return ibBoardFunc(CONF(ud,board),IBSAD,v);
   else
   {
      /* enable ibsad also working on devices, not only on boards */
      if ( ((v > 0x00ff) &&  (v <= 0x00ff00)) ||  (v == 0x0))
      {
         /* remove network information of ud ???? */
         ud &= 0x0ff ;  
         ibBoard[ud].padsad &= 0xffff00ff ;
         ibBoard[ud].padsad |= v ;
      }
      else
      {
         ibsta = CMPL | ERR;
         iberr = EARG;
         ibcnt = errno;
         ibPutErrlog(-1,ibVerbCode(IBSAD));
      }
   }   
#endif
	return 0;	//XXX
}
