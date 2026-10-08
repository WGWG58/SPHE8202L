#ifndef	__FASTMATH_H
#define	__FASTMATH_H

#define	__DIVF(x,f,l)	( ((unsigned)(x)*(f)+((unsigned)(f)-1)) >> (l))

#define	DIV3_B(x)	__DIVF(x,341,10)		/* 0-1022	*/
#define	DIV5_B(x)	__DIVF(x,409,11)		/* 0-684	*/
#define	DIV7_B(x)	__DIVF(x,73,9)			/* 0-510	*/
#define	DIV9_B(x)	__DIVF(x,227,11)		/* 0-413	*/
#define	DIV10_B(x)	__DIVF(x,51,9)			/* 0-259	*/
#define	DIV11_B(x)	__DIVF(x,93,10)			/* 0-1022	*/

#define	DIV3_W(x)	__DIVF(x,1365,12)		/* 0-4094	*/
#define	DIV5_W(x)	__DIVF(x,819,12)		/* 0-4094	*/
#define	DIV7_W(x)	__DIVF(x,585,12)		/* 0-4094	*/
#define	DIV9_W(x)	__DIVF(x,455,12)		/* 0-4094	*/
#define	DIV10_W(x)	__DIVF(x,819,13)		/* 0-4109	*/
#define	DIV11_W(x)	__DIVF(x,5957,16)		/* 0-7281	*/

#define	DIV3(x)		DIV3_B(x)
#define	DIV5(x)		DIV5_B(x)
#define	DIV7(x)		DIV7_B(x)
#define	DIV9(x)		DIV9_B(x)
#define	DIV10(x)	DIV10_B(x)
#define	DIV11(x)	DIV11_B(x)

#endif/*__FASTMATH_H*/
