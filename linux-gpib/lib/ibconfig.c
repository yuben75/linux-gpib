/***************************************************************************
                          lib/ibconfig.c
                             -------------------

    copyright            : (C) 2002 by Frank Mori Hess
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

#include "ib_internal.h"
#include "ibP.h"

static int set_spoll_timeout( ibConf_t *conf, int timeout )
{
	if( timeout < TNONE || timeout > T1000s )
	{
		setIberr( EARG );
		return -1;
	}

	conf->spoll_usec_timeout = timeout_to_usec( timeout );

	return 0;
}

static int set_ppoll_timeout( ibConf_t *conf, int timeout )
{
	if( timeout < TNONE || timeout > T1000s )
	{
		setIberr( EARG );
		return -1;
	}

	conf->ppoll_usec_timeout = ppoll_timeout_to_usec( timeout );

	return 0;
}

int ibconfig( int ud, int option, int value )
{
	ibConf_t *conf;
	int retval;

	conf = enter_library( ud );
	if( conf == NULL )
		return exit_library( ud, 1 );

	switch( option )
	{
		case IbcPAD:
			retval = internal_ibpad( conf, value );
			if( retval < 0 ) return exit_library( ud, 1 );
			return exit_library( ud, 0 );
			break;
		case IbcSAD:
			retval = internal_ibsad( conf, value );
			if( retval < 0 ) return exit_library( ud, 1 );
			return exit_library( ud, 0 );
			break;
		case IbcTMO:
			retval = internal_ibtmo( conf, value );
			if( retval < 0 ) return exit_library( ud, 1 );
			return exit_library( ud, 0 );
			break;
		case IbcEOT:
			internal_ibeot( conf, value );
			return exit_library( ud, 0 );
			break;
		case IbcEOSrd:
			if( value )
				conf->eos_flags |= EOS_RD;
			else
				conf->eos_flags &= ~EOS_RD;
			return exit_library( ud, 0 );
			break;
		case IbcEOSwrt:
			if( value )
				conf->eos_flags |= EOS_EOI;
			else
				conf->eos_flags &= ~EOS_EOI;
			return exit_library( ud, 0 );
			break;
		case IbcEOScmp:
			if( value )
				conf->eos_flags |= EOS_BIN;
			else
				conf->eos_flags &= ~EOS_BIN;
			return exit_library( ud, 0 );
			break;
		case IbcEOSchar:
			if( ( value & 0xff ) != value )
			{
				setIberr( EARG );
				return exit_library( ud, 1 );
			}
			conf->eos = value;
			return exit_library( ud, 0 );
			break;
		case IbcReadAdjust:
			// XXX
			if( value )
			{
				fprintf( stderr, "libgpib: byte swapping on reads not implemented\n");
				setIberr( ECAP );
				return exit_library( ud, 1 );
			}else
				return exit_library( ud, 0 );
			break;
		case IbcWriteAdjust:
			// XXX
			if( value )
			{
				fprintf( stderr, "libgpib: byte swapping on writes not implemented\n");
				setIberr( ECAP );
				return exit_library( ud, 1 );
			}else
				return exit_library( ud, 0 );
			break;
		case IbcEndBitIsNormal:
			if( value )
			{
				return exit_library( ud, 0 );
			}else
			{
				fprintf( stderr, "libgpib: no support for END on EOI only yet \n");
				setIberr( ECAP );
				return exit_library( ud, 1 );
			}
			break;
		default:
			break;
	}

	if( conf->is_interface )
	{
		switch( option )
		{
			case IbcPPC:
				retval = internal_ibppc( conf, value );
				if( retval < 0 ) return exit_library( ud, 1 );
				return exit_library( ud, 0 );
				break;
			case IbcAUTOPOLL:
				retval = configure_autopoll( conf, value );
				if( retval < 0 ) return exit_library( ud, 1 );
				return exit_library( ud, 0 );
				break;
			case IbcCICPROT:
				// XXX
				if( value )
				{
					fprintf( stderr, "libgpib: pass control protocol not supported\n");
					setIberr( ECAP );
					return exit_library( ud, 1 );
				}else
					return exit_library( ud, 0 );
				break;
			case IbcIRQ:
				// XXX
				if( value == 0 )
				{
					fprintf( stderr, "libgpib: disabling interrupts not supported\n");
					setIberr( ECAP );
					return exit_library( ud, 1 );
				}else
					return exit_library( ud, 0 );
				break;
			case IbcSC:
				// XXX
				fprintf( stderr, "libgpib: request/release control protocol not supported\n");
				setIberr( ECAP );
				return exit_library( ud, 1 );
				break;
			case IbcSRE:
				retval = internal_ibsre( conf, value );
				if( retval < 0 ) return exit_library( ud, 1 );
				return exit_library( ud, 0 );
				break;
			case IbcPP2:
				// XXX
				fprintf( stderr, "libgpib: local/remote parallel poll configuration not implemented\n");
				setIberr( ECAP );
				return exit_library( ud, 1 );
				break;
			case IbcTIMING:
				// XXX
				if( value == 1 )
				{
					return exit_library( ud, 0 );
				}else
				{
					fprintf( stderr, "libgpib: high-speed timing not implemented\n");
					setIberr( ECAP );
					return exit_library( ud, 1 );
				}
				break;
			case IbcDMA:
				// XXX
				if( value )
				{
					return exit_library( ud, 0 );
				}else
				{
					fprintf( stderr, "libgpib: disabling DMA not supported\n");
					setIberr( ECAP );
					return exit_library( ud, 1 );
				}
				break;
			case IbcEventQueue:
				// XXX
				fprintf( stderr, "libgpib: event queue not implemented\n");
				setIberr( ECAP );
				return exit_library( ud, 1 );
				break;
			case IbcSPollBit:
				// XXX
				fprintf( stderr, "libgpib: SPOLL bit support not implemented\n");
				setIberr( ECAP );
				return exit_library( ud, 1 );
				break;
			case IbcSendLLO:
				// XXX
				if( value )
				{
					fprintf( stderr, "libgpib: sending local lockout on device open not implemented\n");
					setIberr( ECAP );
					return exit_library( ud, 1 );
				}else
					return exit_library( ud, 0 );
				break;
			case IbcPPollTime:
				retval = set_ppoll_timeout( conf, value );
				if( retval < 0 )
				{
					setIberr( EARG );
					return exit_library( ud, 1 );
				}else
				{
					return exit_library( ud, 0 );
				}
				break;
			case IbcHSCableLength:
				// XXX
				if( value )
				{
					fprintf( stderr, "libgpib: HS protocol not supported\n" );
					setIberr( ECAP );
					return exit_library( ud, 1 );
				}else
					return exit_library( ud, 0 );
				break;
			case IbcIst:
				// XXX
				fprintf( stderr, "libgpib: ibist not implemented\n");
				setIberr( ECAP );
				return exit_library( ud, 1 );
				break;
			case IbcRsv:
				retval = internal_ibrsv( conf, value );
				if( retval < 0 )
					return exit_library( ud, 1 );
				else
					return exit_library( ud, 0 );
				break;
			default:
				break;
		}
	}else
	{
		switch( option )
		{
			case IbcREADDR:
				/* We always re-address.  To support only
				 * readdressing when necessary would require
				 * making the driver keep track of current addressing
				 * state.  Maybe someday, but low priority. */
				if( value )
					conf->readdr = 1;
				else
					conf->readdr = 0;
				return exit_library( ud, 0 );
				break;
			case IbcSPollTime:
				retval = set_spoll_timeout( conf, value );
				if( retval < 0 )
				{
					setIberr( EARG );
					return exit_library( ud, 1 );
				}else
				{
					return exit_library( ud, 0 );
				}
				break;
			case IbcUnAddr:
				// XXX
				if( value )
				{
					fprintf( stderr, "libgpib: no support for UNT/UNL at end of "
						"device read and writes\n" );
					setIberr( ECAP );
					return exit_library( ud, 1 );
				}else
					return exit_library( ud, 0 );
				break;
			default:
				break;
		}
	}

	setIberr( EARG );
	return exit_library( ud, 1 );
}