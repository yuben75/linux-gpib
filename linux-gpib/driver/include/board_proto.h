/* Automatically created by mkproto.sh. DONT EDIT */
/***** Public Functions ******/
extern  void bdDMAAdjCnt(ibio_op_t *rwop);
extern  void bdPIOAdjCnt(ibio_op_t *rwop);
extern  void bdSendAuxCmd(int cmd);
extern  void bdSendAuxACmd(int cmd);
extern  void bdcmd(ibio_op_t *cmdop);
extern  int bdDMAwait(ibio_op_t *rwop, int noWait);
extern  void bdDMAstart(ibio_op_t *rwop);
extern  int bdDMAstop(ibio_op_t *rwop);
extern  void bd_PCIInfo(void);
extern  void bdPCIDetach(void);
extern  void pci_EnableIRQ ();
extern  void pci_ResetIRQ ();
extern  void pci_DisableIRQ ();
extern  void pci_EnableIRQ ();
extern  void pci_ResetIRQ ();
extern  void pci_DisableIRQ ();
extern  int bdonl(int v);
extern  int bdlines(void);
extern  void bdDMAread(ibio_op_t *rdop);
extern  void bdPIOread(ibio_op_t *rdop);
extern  int bdSRQstat(void);
extern  void bdsc(void);
extern  uint8 bdGetDataByte(void);
extern  uint8 bdGetCmdByte(void);
extern  uint8 bdGetAdrStat(void);
extern  uint8 bdCheckEOI(void);
extern  void bdSetEOS(int ebyte);
extern  uint8 bdGetEOS(void);
extern  void bdSetSPMode(int v);
extern  void bdSetPAD(int v);
extern  void bdSetSAD(int mySAD,int enable);
extern  void bdwait(unsigned int mask);
extern  int bdWaitIn(void);
extern  void bdWaitOut(void);
extern  void bdWaitATN(void);
extern  void bdDMAwrt(ibio_op_t *wrtop);
extern  void bdPIOwrt( ibio_op_t *wrtop);