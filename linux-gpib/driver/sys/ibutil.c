
#include "gpibP.h"
#include "autopoll.h"
/*
 * IBPAD
 * change the GPIB address of the interface board.  The address
 * must be 0 through 30.  ibonl resets the address to PAD.
 */
int ibpad( gpib_board_t *board, unsigned int addr )
{
	if ( addr > 30 )
	{
		printk("gpib: invalid primary address %u\n", addr );
		return -1;
	}else
	{
		board->pad = addr;
		if( board->online )
			board->interface->primary_address( board, board->pad );
		GPIB_DPRINTK( "set primary addr to %i\n", board->pad );
	}
	return 0;
}


/*
 * IBSAD
 * change the secondary GPIB address of the interface board.
 * The address must be 0 through 30, or negative disables.  ibonl resets the
 * address to SAD.
 */
int ibsad( gpib_board_t *board, int addr )
{
	if( addr > 30 )
	{
		printk("gpib: invalid secondary address %i, must be 0-30\n", addr);
		return -1;
	}else
	{
		board->sad = addr;
		if( board->online )
		{
			if( board->sad >= 0 )
			{
				board->interface->secondary_address( board, board->sad, 1 );
			}else
			{
				board->interface->secondary_address( board, 0, 0 );
			}
		}
		GPIB_DPRINTK( "set secondary addr to %i\n", board->sad );
	}
	return 0;
}

/*
 * IBEOS
 * Set the end-of-string modes for I/O operations to v.
 *
 */
int ibeos( gpib_board_t *board, int eos, int eosflags )
{
	if( eosflags & ~EOS_MASK )
	{
		printk( "bad EOS modes\n" );
		return -EINVAL;
	}else
	{
		if( eosflags & EOS_RD )
		{
			board->interface->enable_eos( board, eos, eosflags & EOS_BIN );
		}else
			board->interface->disable_eos( board );
	}
	return 0;
}

unsigned int ibstatus( gpib_board_t *board )
{
	if( board->private_data == NULL )
		return 0;

	return board->interface->update_status( board );
}

unsigned int full_ibstatus( gpib_board_t *board, const gpib_device_t *device )
{
	unsigned int status;

	status = ibstatus( board );

	if( num_status_bytes( device ) ) status |= RQS;

	return status;
}
