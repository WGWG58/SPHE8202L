/* ----------------------------------------------------------
playbasic.c

Common variables and functions for
Media Browsing Programs and Media Playing Programs
---------------------------------------------------------- */
//#include "system.h"
#include "sio.h"
#include "cdfs.h"
#include "shuffle_new.h"

/* ----------------------------------------------------------
Shuffle
We want to create a non-repeating sequence of numbers between
1 and max, without storing the sequence
---------------------------------------------------------- */
int shuffle_max;
int shuffle_mod;
int shuffle_seed;
int shuffle_pos;



/* ----------------------------------------------------------
Start a new shuffled sequence, returning the first number
If 0 < start <= max, then first number = start,
Otherwise, first number will be random from [1, max]
---------------------------------------------------------- */
int shuffle_new(int start, int max)//, BYTE shuffle_status)
{
	int temp, mask, offset;
	int done = 0;
	
	shuffle_max = max;
	shuffle_mod = 32;
	shuffle_pos = 1;
	
	while (max > 16)
	{
		max = max >> 1;
		shuffle_mod = shuffle_mod << 1;
	}
	mask = shuffle_mod - 1;
	
	offset = (regs0->stc_15_0) & mask;
	shuffle_seed = (regs0->rtc_15_0) & mask;

	do
	{
		temp = ((offset + shuffle_seed) & mask) + 1;
		if ((start > 0) && (temp != start))
			shuffle_seed = (shuffle_seed + start - temp) & mask;
		else if (temp <= shuffle_max)
			done = temp;
		else
			shuffle_seed = (shuffle_seed * 109 + 57) & mask;
	} while (!done);
	return done;
}

/* ----------------------------------------------------------
Given the current number, return the next number, in [1, max].
Also update seed and pos. If pos > max, return 0
---------------------------------------------------------- */
int shuffle_next(int num)//,BYTE shuffle_status)
{
 	int temp = 0;
	int mask = shuffle_mod - 1;
	int offset = ((num - 1) - shuffle_seed) & mask;
	
	if (++shuffle_pos <= shuffle_max)
	{
		do
		{
			shuffle_seed = (shuffle_seed * 109 + 57) & mask;
			temp = ((offset + shuffle_seed) & mask) + 1;
		} while (temp > shuffle_max);
	}
	return temp;
}

/* ----------------------------------------------------------
Given the current number, return the previous number, in [1, max].
Also update seed and pos. If pos < 1, return 0

Inverses for (109x + 57) mod n:
n = 16:		(5x + 131) mod 16
n = 32:		(5x + 131) mod 32
n = 64:		(37x + 131) mod 64
n = 128:	(101x + 131) mod 128
n = 256:	(101x + 131) mod 256
n = 512:	(357x + 131) mod 512
n = 1024:	(357x + 131) mod 1024
n = 2048:	(357x + 131) mod 2048
---------------------------------------------------------- */
int shuffle_prev(int num)//,BYTE shuffle_status)
{
  	int temp = 0;
	int mask = shuffle_mod - 1;
	int offset = ((num - 1) - shuffle_seed) & mask;
	
	if (--shuffle_pos > 0)
	{
		int mult = 5;
		
		if (shuffle_mod > 256)
			mult = 357;
		else if (shuffle_mod > 64)
			mult = 101;
		else if (shuffle_mod > 32)
			mult = 37;
		do
		{
			shuffle_seed = (shuffle_seed * mult + 131) & mask;
			temp = ((offset + shuffle_seed) & mask) + 1;
		} while (temp > shuffle_max);
	}
	return temp;
}

