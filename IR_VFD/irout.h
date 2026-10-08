#ifndef	__IROUT_H
#define	__IROUT_H

void	reset_irout(void);
void	send_irout(int data);

#include "ircode.h"

#define	IRO_PLAY	IRC_PLAY
#define	IRO_TRAYINOUT	8
#define	IRO_BROWSE	32
#define	IRO_PAUSE	IRC_PLAY	/* 0x28 PLAY/PAUSE	*/
#define	IRO_NEXT	IRC_FORWARD	/* 0x58			*/
#define	IRO_PREV	IRC_BACKWARD	/* 0x70			*/

#define	IRO_1		IRC_1		/* ...guess...		*/
#define	IRO_2		IRC_2		/* ...guess...		*/
#define	IRO_3		IRC_3		/* ...guess...		*/
#define	IRO_4		IRC_4		/* ...guess...		*/
#define	IRO_5		IRC_5		/* ...guess...		*/
#define	IRO_6		IRC_6		/* ...guess...		*/
#define	IRO_7		IRC_7		/* ...guess...		*/
#define	IRO_8		IRC_8		/* ...guess...		*/
#define	IRO_9		IRC_9		/* ...guess...		*/
#define	IRO_10		IRC_10		/* ...guess...		*/
#define	IRO_P10		IRC_P10		/* 0x68			*/

#define	irout_trayinout()	send_irout(IRO_TRAYINOUT)
#define	irout_pause()		send_irout(IRO_PAUSE)
#define	irout_next()		send_irout(IRO_NEXT)

#endif/*__IROUT_H*/

