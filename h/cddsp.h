#ifndef	__CDDSP_H
#define	__CDDSP_H

//
// 1999 Apr30 definition
//

#ifdef	CDIF_SYNC
#define RF_CD_BCLK_rising_edge          0
#define RF_CD_BCLK_falling_edge 	0x0001
#else
#define RF_CD_BCLK_rising_edge          0x0001
#define RF_CD_BCLK_falling_edge 	0
#endif

#define RF_CD_DATA_MSB_first            0x0002 
#define RF_CD_DATA_LSB_first		0

#define RF_CD_DATA_left_justify         0x0004
#define	RF_CD_DATA_right_justify	0

#define RF_CD_DATA_one_delay            0x0008
#define	RF_CD_DATA_zero_delay		0

#define RF_CD_LRCK_low_right            0x0010
#define	RF_CD_LRCK_low_left		0

#define RF_CD_LRCK_pulse                0x0020
#define	RF_CD_LRCK_level		0

#define	RF_CD_C2P0_MSB_first		0x0040
#define RF_CD_C2P0_LSB_first            0

#define RF_CD_DATA_size_16              (0<<7)
#define	RF_CD_DATA_size_17		(1<<7)
#define	RF_CD_DATA_size_18		(2<<7)
#define	RF_CD_DATA_size_19		(3<<7)
#define	RF_CD_DATA_size_20		(4<<7)
#define	RF_CD_DATA_size_21		(5<<7)
#define	RF_CD_DATA_size_22		(6<<7)
#define	RF_CD_DATA_size_24		(7<<7)

	/* bit 12:11 */
#define RF_CD_DATA_container_16        	(0<<11)
#define	RF_CD_DATA_container_24		(1<<11)
#define	RF_CD_DATA_container_32		(2<<11)

#define RF_CD_DATA_raw			0x2000
#define RF_CD_DATA_descramble           0	/* default */

#define RF_CD_DATA_swap                 0x4000
#define RF_CD_DATA_noswap               0

#define	RF_CD_DATA_sync			0	/* default */
#define	RF_CD_DATA_nosync		0x8000

#define	CDDSP_I2S_raw	( \
		  RF_CD_DATA_noswap \
		| RF_CD_DATA_raw \
		| RF_CD_DATA_container_24 \
		| RF_CD_DATA_size_16 \
		| RF_CD_LRCK_level  \
		| RF_CD_LRCK_low_left \
		| RF_CD_DATA_one_delay \
		| RF_CD_DATA_left_justify \
		| RF_CD_DATA_MSB_first \
		| RF_CD_BCLK_rising_edge )

/*
** Philips I2S bus
*/
#define	CDDSP_I2S	( \
		  RF_CD_DATA_noswap \
		| RF_CD_DATA_descramble \
		| RF_CD_DATA_container_24 \
		| RF_CD_DATA_size_16 \
		| RF_CD_LRCK_level  \
		| RF_CD_LRCK_low_left \
		| RF_CD_DATA_one_delay \
		| RF_CD_DATA_left_justify \
		| RF_CD_DATA_MSB_first \
		| RF_CD_BCLK_rising_edge )


#define	CDDSP_SONY	( \
		  RF_CD_DATA_noswap \
		| RF_CD_DATA_descramble \
		| RF_CD_DATA_container_24 \
		| RF_CD_DATA_size_16 \
		| RF_CD_LRCK_level  \
		| RF_CD_LRCK_low_left \
		| RF_CD_DATA_zero_delay \
		| RF_CD_DATA_right_justify \
		| RF_CD_DATA_MSB_first \
		| RF_CD_BCLK_rising_edge )

#define	CDDSP_CONFIG	CDDSP_SONY

#endif/*__CDDSP_H*/
