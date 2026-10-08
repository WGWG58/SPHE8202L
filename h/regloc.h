#ifndef	__REGLOC_H
#define	__REGLOC_H

#define	REGLOCi_AT	1
#define	REGLOCi_v0	2
#define REGLOCi_v1	3
#define REGLOCi_a0	4	/* argument registers	*/
#define REGLOCi_a1	5
#define REGLOCi_a2	6
#define REGLOCi_a3	7
#define REGLOCi_t0	8	/* caller saved		*/
#define REGLOCi_t1	9
#define REGLOCi_t2	10
#define REGLOCi_t3	11
#define REGLOCi_t4	12
#define REGLOCi_t5	13
#define REGLOCi_t6	14
#define REGLOCi_t7	15
#define REGLOCi_t8	16
#define REGLOCi_t9	17
#define	REGLOCi_s6	18	/* register pointer	*/
//#define REGLOCi_k0	19	/* kernel temporary	*/
//#define REGLOCi_k1	20
#define REGLOCi_gp	19	/* global pointer	*/
#define REGLOCi_ra	20	/* return address	*/
#define	REGLOCi_EPC	21
#define	REGLOCi_NUM	22

#define	REGLOC_EPC	0
#define	REGLOC_AT	1
#define	REGLOC_v0	2
#define REGLOC_v1	3
#define REGLOC_a0	4	/* argument registers	*/
#define REGLOC_a1	5
#define REGLOC_a2	6
#define REGLOC_a3	7
#define REGLOC_t0	8	/* caller saved		*/
#define REGLOC_t1	9
#define REGLOC_t2	10
#define REGLOC_t3	11
#define REGLOC_t4	12
#define REGLOC_t5	13
#define REGLOC_t6	14
#define REGLOC_t7	15
#define REGLOC_s0	16	/* callee saved		*/
#define REGLOC_s1	17
#define REGLOC_s2	18
#define REGLOC_s3	19
#define REGLOC_s4	20
#define REGLOC_s5	21
#define REGLOC_s6	22
#define REGLOC_s7	23
#define REGLOC_t8	24	/* code generator	*/
#define REGLOC_t9	25
#define REGLOC_k0	26	/* kernel temporary	*/	/* save?? */
#define REGLOC_k1	27
#define REGLOC_gp	28	/* global pointer	*/
#define REGLOC_sp	29	/* stack pointer	*/
#define REGLOC_fp	30	/* frame pointer	*/
#define REGLOC_ra	31	/* return address	*/
#define	REGLOC_NUM	32	/* MAXIMUM */

#endif/*__REGLOC_H*/
