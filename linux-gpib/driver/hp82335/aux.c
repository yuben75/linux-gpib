

#include <board.h>





/* -- bdSendAuxCmd(int cmd)
 * Performs single auxiliary commands (nec7210)
 *
 *
 */

IBLCL void bdSendAuxCmd(int cmd)
{
  DBGin("bdSendAuxCmd");
  switch(cmd){

  case AUX_GTS:
    DBGprint(DBG_BRANCH,("Aux Send GTS"));
    GPIBout(AUXCR,AUX_GTS); 
    break;
  case AUX_TCS:
    DBGprint(DBG_BRANCH,("Aux Send TCS"));
    GPIBout(AUXCR,AUX_TCS);
    break;
  case AUX_TCA:
    DBGprint(DBG_BRANCH,("Aux Send TCA"));
    GPIBout(AUXCR,AUX_TCA);
    break;
  case AUX_SIFC:
    DBGprint(DBG_BRANCH,("Aux Send IFC"));
    GPIBout(AUXCR,AUX_SIFC); 
    break;
  case AUX_SREN:
    DBGprint(DBG_BRANCH,("Aux Send REM"));
    GPIBout(AUXCR,AUX_SREN); 
    break;
  case AUX_CREN:
    DBGprint(DBG_BRANCH,("Aux Send unset REM"));
    GPIBout(AUXCR,AUX_CREN); 
    break;
  case AUX_CIFC:
    DBGprint(DBG_BRANCH,("Aux Send unset IFC"));
    GPIBout(AUXCR,AUX_CIFC); 
    break;
  case AUX_SEOI:
    if( pgmstat & PS_NOEOI){ 
      DBGprint(DBG_BRANCH,("Aux Send SEOI disabled"));
    } else {
      DBGprint(DBG_BRANCH,("Aux Send EOI"));
      GPIBout(AUXCR, AUX_SEOI);
    }
    break;  
#if 0
  case AUX_EPP:
    DBGprint(DBG_BRANCH,("Aux Send EPP"));
    GPIBout(AUXCR,AUX_EPP);
    break;
#endif


  case AUX_FH:
    DBGprint(DBG_BRANCH,("Aux Send FH"));
    GPIBout(AUXCR,AUX_FH);
    break;


  default:
    DBGprint(DBG_BRANCH,(" warning: illegal auxiliary command"));
    GPIBout(AUXCR,cmd);
    break;
  }
  /*bdlines();*/
  DBGout();
}



/* -- bdSendAuxACmd(int cmd)
 * Set Auxiliary A Register not for hp82335
 *
 *
 */

IBLCL void bdSendAuxACmd(int cmd)
{
  DBGin("bdSendAuxACmd not implemented");
#if 0
  DBGprint(DBG_BRANCH,("Aux Send=0x%x",cmd));

  GPIBout(AUXCR, cmd);
#endif
  DBGout();
}



