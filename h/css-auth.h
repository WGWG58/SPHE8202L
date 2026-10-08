#ifndef __CSSAUTH_H_
#define __CSSAUTH_H_

#include "types.h"

struct block {
	UINT8	b[5];
};

extern void CryptKey1(int varient, UINT8 const *challenge, struct block *key);
extern void CryptKey2(int varient, UINT8 const *challenge, struct block *key);
extern void CryptBusKey(int varient, UINT8 const *challenge, struct block *key);

#endif
