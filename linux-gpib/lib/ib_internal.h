/***************************************************************************
                              lib/ib_internal.h
                             -------------------

    copyright            : (C) 2001,2002 by Frank Mori Hess
    email                : fmhess@users.sourceforge.net
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef _IB_INTERNAL_H
#define _IB_INTERNAL_H

#include "ib.h"
#include "ibP.h"
#include "gpib_types.h"
#include "gpib_ioctl.h"
#include <unistd.h>
#include <sys/ioctl.h>

#include "ibConf.h"

enum internal_gpib_addr
{
	SAD_DISABLED = -1,
	ADDR_INVALID = -2
};

void init_async_op( struct async_operation *async );
int ibCheckDescriptor(int ud);
int ibBdChrConfig( ibBoard_t *board );
int initIbBoardAtFork( void );
int ibBoardOpen( ibBoard_t *board );
int ibBoardClose( ibBoard_t *board );
int ibGetNrBoards(void);
void yyerror(char *s);
int iblcleos( const ibConf_t *conf );
char *ibVerbCode(int code);
void ibPutMsg (char *format,...);
void ibPutErrlog(int ud,char *routine);
int ibParseConfigFile( void );
int ibGetDescriptor(ibConf_t conf);
int ibFindDevIndex( const char *name );
ssize_t my_ibcmd( ibConf_t *conf, const uint8_t *buffer, size_t length);
unsigned int send_setup_string( const ibConf_t *conf, uint8_t *cmdString );
unsigned int create_send_setup( const ibBoard_t *board,
	const Addr4882_t addressList[], uint8_t *cmdString );
int send_setup( ibConf_t *conf );
void init_ibconf( ibConf_t *conf );
void init_ibboard( ibBoard_t *board );
int my_ibdev( int minor, int pad, int sad, unsigned int usec_timeout,
	int send_eoi, int eos, int eosflags);
int my_ibbna( ibConf_t *conf, unsigned int new_board_index );
unsigned int timeout_to_usec( enum gpib_timeout timeout );
unsigned int ppoll_timeout_to_usec( unsigned int timeout );
unsigned int usec_to_ppoll_timeout( unsigned int usec );
int set_timeout( const ibBoard_t *board, unsigned int usec_timeout );
int close_gpib_device( ibConf_t *conf );
int open_gpib_device( ibConf_t *conf );
int gpibi_change_address( ibConf_t *conf,
	unsigned int pad, int sad );
int lock_board_mutex( ibBoard_t *board );
int unlock_board_mutex( ibBoard_t *board );
int conf_lock_board( ibConf_t *conf );
int conf_unlock_board( ibConf_t *conf );
int exit_library( int ud, int error );
int general_exit_library( int ud, int error, int keep_lock );
ibConf_t * enter_library( int ud );
ibConf_t * general_enter_library( int ud, int no_lock_board, int ignore_eoip );
void setIbsta( int status );
void setIberr( int error );
void setIbcnt( long count );
unsigned int usec_to_timeout( unsigned int usec );
int query_ppc( const ibBoard_t *board );
int query_ist( const ibBoard_t *board );
int conf_online( ibConf_t *conf, int online );
int configure_autopoll( ibConf_t *conf, int enable );
int extractPAD( Addr4882_t address );
int extractSAD( Addr4882_t address );
Addr4882_t packAddress( unsigned int pad, int sad );
int addressIsValid( Addr4882_t address );
int addressListIsValid( const Addr4882_t addressList[] );
unsigned int numAddresses( const Addr4882_t addressList[] );
int remote_enable( const ibBoard_t *board, int enable );
int config_read_eos( ibBoard_t *board, int use_eos_char,
	int eos_char, int compare_8_bits );
void sync_globals( void );
int create_autopoll_thread( ibBoard_t *board );
int destroy_autopoll_thread( ibBoard_t *board );
int is_system_controller( const ibBoard_t *board );
int is_cic( const ibBoard_t *board );
int assert_ifc( ibBoard_t *board, unsigned int usec );
int request_system_control( ibBoard_t *board, int request_control );

int internal_ibpad( ibConf_t *conf, unsigned int address );
int internal_ibsad( ibConf_t *conf, int address );
int internal_ibtmo( ibConf_t *conf, int timeout );
void internal_ibeot( ibConf_t *conf, int send_eoi );
int internal_ibist( ibConf_t *conf, int ist );
int internal_ibppc( ibConf_t *conf, int v );
int internal_ibsre( ibConf_t *conf, int v );
int internal_ibrsv( ibConf_t *conf, int v );
int internal_iblines( ibConf_t *conf, short *line_status );
int internal_ibgts( ibConf_t *conf, int shadow_handshake );
int internal_ibrsc( ibConf_t *conf, int request_control );
int internal_ibsic( ibConf_t *conf );
int InternalDevClearList( ibConf_t *conf, const Addr4882_t addressList[] );
int InternalReceiveSetup( ibConf_t *conf, Addr4882_t address );
int InternalSendSetup( ibConf_t *conf, const Addr4882_t addressList[] );
int InternalSendList( ibConf_t *conf, const Addr4882_t addressList[],
	const void *buffer, long count, int eotmode );
int InternalEnableRemote( ibConf_t *conf, const Addr4882_t addressList[] );
int InternalReceive( ibConf_t *conf, Addr4882_t address,
	void *buffer, long count, int termination );

static __inline__ ibBoard_t* interfaceBoard( const ibConf_t *conf )
{
	return &ibBoard[ conf->settings.board ];
}

#include <stdio.h>
int gpib_yyparse( void *parse_arg );
void gpib_yyrestart( FILE* );
int parse_gpib_conf( const char *filename, ibConf_t *configs,
	unsigned int configs_length, ibBoard_t *boards, unsigned int boards_length );
#define YY_DECL int gpib_yylex( YYSTYPE *gpib_lvalp, YYLTYPE *gpib_llocp )

#endif	/* _IB_INTERNAL_H */
