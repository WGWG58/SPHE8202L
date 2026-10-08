#ifndef	__REGDEF_H__
#define	__REGDEF_H__


/* %Q% %M% %I% */
/*
 * Author	Mark I. Himelstein
 * Date started Wed Jun 19 15:37:59 PDT 1985
 * added fp reg's  8/15/86 kag
 * Module	regdef.h
 * Purpose	provide a set of reasonable names for assembler register
 *		variables.
 *
 * see botton for sony-specific changes
 */


#define zero	$0	/* wired zero */
#define AT	$at	/* assembler temp */
#define v0	$2	/* return value */
#define v1	$3
#define a0	$4	/* argument registers */
#define a1	$5
#define a2	$6
#define a3	$7
#define t0	$8	/* caller saved */
#define t1	$9
#define t2	$10
#define t3	$11
#define t4	$12
#define t5	$13
#define t6	$14
#define t7	$15
#define s0	$16	/* callee saved */
#define s1	$17
#define s2	$18
#define s3	$19
#define s4	$20
#define s5	$21
#define s6	$22
#define s7	$23
#define t8	$24	/* code generator */
#define t9	$25
#define k0	$26	/* kernel temporary */
#define k1	$27
#define gp	$28	/* global pointer */
#define sp	$29	/* stack pointer */
#define fp	$30	/* frame pointer */
#define ra	$31	/* return address */

#define	s8	fp	/* fp is unused in MIPS */

#define r0	$0
#define r1	$1
#define r2	$2
#define r3	$3
#define r4	$4
#define r5	$5
#define r6	$6
#define r7	$7
#define r8	$8
#define r9	$9
#define r10	$10
#define r11	$11
#define r12	$12
#define r13	$13
#define r14	$14
#define r15	$15
#define r16	$16
#define r17	$17
#define r18	$18
#define r19	$19
#define r20	$20
#define r21	$21
#define r22	$22
#define r23	$23
#define r24	$24
#define r25	$25
#define r26	$26
#define r27	$27
#define r28	$28
#define r29	$29
#define r30	$30
#define r31	$31

#define fp0	$f0
#define fp1	$f1
#define fp2	$f2
#define fp3	$f3
#define fp4	$f4
#define fp5	$f5
#define fp6	$f6
#define fp7	$f7
#define fp8	$f8
#define fp9	$f9
#define fp10	$f10
#define fp11	$f11
#define fp12	$f12
#define fp13	$f13
#define fp14	$f14
#define fp15	$f15
#define fp16	$f16
#define fp17	$f17
#define fp18	$f18
#define fp19	$f19
#define fp20	$f20
#define fp21	$f21
#define fp22	$f22
#define fp23	$f23
#define fp24	$f24
#define fp25	$f25
#define fp26	$f26
#define fp27	$f27
#define fp28	$f28
#define fp29	$f29
#define fp30	$f30
#define fp31	$f31

/*
#----------------------------------------------------------------------------
#
# sony section 
#
# Revision History:						      
#									      
# Rev	Date		Engineer	Comments
#
# 01	11/29/93	SR Cox		defined	 SUBREG as r19	
#----------------------------------------------------------------------------
*/
/*
#use r19 as the subtest register for reporting errors
#may have to change this later
*/
#define SUBREG r19


/* System Control Coprocessor (CP0) registers */
#define C0_SR           $12             /* Processor Status */
#define C0_STATUS       $12             /* Processor Status */
#define C0_CAUSE        $13             /* Exception Cause */
#define C0_EPC          $14             /* Exception PC */
#define C0_BADADDR      $8              /* Bad Address */
#define C0_BADVADDR     $8              /* Bad Virtual Address */
#define C0_BADVA	$8              /* Bad Virtual Address */
#define C0_PRID         $15             /* Processor Revision Indentifier	*/
#define	C0_CCTL		$20		/* LEXRA cache control extension	*/

#define		EXCCODE_Int	0x00
#define		EXCCODE_AdEL	0x04
#define		EXCCODE_AdES	0x05
#define		EXCCODE_Ov	0x0c
#define		EXCCODE_Sys	0x08
#define		EXCCODE_Bp	0x09
#define		EXCCODE_RI	0x0a
#define		EXCCODE_CpU	0x0b

#define         CAUSE_IP        0x0000ff00
#define         CAUSE_IP7       0x00008000
#define         CAUSE_IP6       0x00004000
#define         CAUSE_IP5       0x00002000
#define         CAUSE_IP4       0x00001000
#define         CAUSE_IP3       0x00000800
#define         CAUSE_IP2       0x00000400
#define         CAUSE_IP1       0x00000200
#define         CAUSE_IP0       0x00000100

#define		STATUS_COP3		0x80000000
#define		STATUS_COP2		0x40000000
#define		STATUS_COP1		0x20000000
#define		STATUS_COP0		0x10000000
#define		STATUS_ENDIAN_BIG	0x02000000
#define		STATUS_BEV		0x00400000
#define		STATUS_IEc		0x00000001
#define		STATUS_KUc		0x00000002
#define		STATUS_IM		0x0000ff00
#define		STATUS_IM7		0x00008000
#define         STATUS_IM6		0x00004000
#define         STATUS_IM5		0x00002000
#define         STATUS_IM4		0x00001000
#define         STATUS_IM3		0x00000800
#define         STATUS_IM2		0x00000400
#define         STATUS_IM1		0x00000200
#define         STATUS_IM0		0x00000100

#define		CCTL_DIvl	0x01
#define		CCTL_IIvl	0x02

#define	C3_DW_BASE	$0
#define	C3_DW_TOP	$1
#define	C3_IW_BASE	$2
#define	C3_IW_TOP	$3


#endif	// __REGDEF_H__
