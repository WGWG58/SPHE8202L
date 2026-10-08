#ifndef __css_descramble_h_
#define __css_descramble_h_

#include "types.h"

struct playkey {
	int offset;
	UINT8 key[5];
};

extern int css_decrypttitlekey(UINT8 *tkey, UINT8 *dkey, struct playkey **pkey);
extern void css_descramble(UINT8 *sec,UINT8 *key);

#endif
