#ifndef __GPIO_MUTE_8200_H
#define __GPIO_MUTE_8200_H

// gpio mute function
#ifdef USE_A19_AS_GPIO_MUTE//pin66
	#define	USE_GPIO_MUTE					1
	#define	GPIO_MUTE_PORT					32
	#define	SFT_CFG_GPIO()							\
				do {								\
					regs0->sft_cfg0 &= ~(0x1 << 0);	\
					GPIO_M_SET(GPIO_MUTE_PORT, 1);	\
					GPIO_E_SET(GPIO_MUTE_PORT, 1);	\
				} while (0)
#elif defined USE_AUD3_AS_GPIO_MUTE//pin170
	#define	USE_GPIO_MUTE					1
	#define	GPIO_MUTE_PORT					60
	#define	SFT_CFG_GPIO()							\
				do {								\
					regs0->sft_cfg3 &= ~(0x1 << 4);	\
					GPIO_M_SET(GPIO_MUTE_PORT, 1);	\
					GPIO_E_SET(GPIO_MUTE_PORT, 1);	\
				} while (0)
#elif defined USE_AUD_AS_GPIO_MUTE//pin164
	#define	USE_GPIO_MUTE					1
	#define	GPIO_MUTE_PORT					58
	#define	SFT_CFG_GPIO()							\
				do {								\
					regs0->sft_cfg3 &= ~(0x1 << 7);	\
					GPIO_M_SET(GPIO_MUTE_PORT, 1);	\
					GPIO_E_SET(GPIO_MUTE_PORT, 1);	\
				} while (0)
#elif defined USE_AUD4_AS_GPIO_MUTE//pin163
	#define	USE_GPIO_MUTE					1
	#define	GPIO_MUTE_PORT					57

	#define	SFT_CFG_GPIO()							\
				do {								\
					regs0->sft_cfg3 &= ~(0x1 << 5);	\
					GPIO_M_SET(GPIO_MUTE_PORT, 1);	\
					GPIO_E_SET(GPIO_MUTE_PORT, 1);	\
				} while (0)				
#elif defined USE_A11_AS_GPIO_MUTE//pin109
	#define	USE_GPIO_MUTE					1
	#define	GPIO_MUTE_PORT					14
	#define	SFT_CFG_GPIO()							\
				do {								\
					regs0->sft_cfg6 &= ~(0x1 << 4);	\
					GPIO_M_SET(GPIO_MUTE_PORT, 1);	\
					GPIO_E_SET(GPIO_MUTE_PORT, 1);	\
				} while (0)												
#elif defined USE_SBA1_AS_GPIO_MUTE//pin121
	#define	USE_GPIO_MUTE					1
	#define	GPIO_MUTE_PORT					15
	#define	SFT_CFG_GPIO()							\
				do {								\
					regs0->sft_cfg6 &= ~(0x1 << 6);	\
					GPIO_M_SET(GPIO_MUTE_PORT, 1);	\
					GPIO_E_SET(GPIO_MUTE_PORT, 1);	\
				} while (0)
#elif defined USE_CS2_AS_GPIO_MUTE //pin70
	#define	USE_GPIO_MUTE					1
	#define	GPIO_MUTE_PORT					35
	#define	SFT_CFG_GPIO()							\
				do {								\
					                                \
					GPIO_M_SET(GPIO_MUTE_PORT, 1);	\
					GPIO_E_SET(GPIO_MUTE_PORT, 1);	\
				} while (0)
#elif defined(USE_ATARST_AS_GPIO_MUTE)      //pin29    //hq,20040216
    #define USE_GPIO_MUTE     1
    #define GPIO_MUTE_PORT    3
    #define SFT_CFG_GPIO()                  \
        do {                                \
            regs0->sft_cfg1 &= ~(0x1 << 3); \
            GPIO_M_SET(GPIO_MUTE_PORT, 1);  \
            GPIO_E_SET(GPIO_MUTE_PORT, 1);  \
        } while (0)					
#elif defined(USE_A20_AS_GPIO_MUTE)//pin129 //freyman 2004-4-20 11:21
	#define USE_GPIO_MUTE     1
    #define GPIO_MUTE_PORT    37
    #define SFT_CFG_GPIO()                  \
        do {                                \
            regs0->sft_cfg0 &= ~(0xfffc << 1); \
            GPIO_M_SET(GPIO_MUTE_PORT, 1);  \
            GPIO_E_SET(GPIO_MUTE_PORT, 1);  \
        } while (0)					
#else
	#define	GPIO_MUTE_PORT					//0     //wanghaoying 2003-8-12 20:50
	#define	SFT_CFG_GPIO()					//0     //wanghaoying 2003-8-12 20:51
#endif

#ifdef	USE_GPIO_MUTE
	#ifdef LOW_MUTE
		
	  #ifdef MINTON_DEMUTE_GPIOIN	
		#define	GPIO_MUTE()							\
				do {								\
					regs0->sft_cfg6 &= ~(0x1 << 6);	\
					GPIO_M_SET(GPIO_MUTE_PORT, 1);	\
					GPIO_E_SET(GPIO_MUTE_PORT, 1);	\
					GPIO_O_SET(GPIO_MUTE_PORT,0);	\
				} while (0)
		
		#define	GPIO_DEMUTE()							\
				do {								\
					regs0->sft_cfg6 &= ~(0x1 << 6);	\
					GPIO_M_SET(GPIO_MUTE_PORT, 1);	\
					GPIO_E_SET(GPIO_MUTE_PORT, 0);	\
				} while (0)
	  #else	//#ifdef MINTON_DEMUTE_GPIOIN	
		#define	GPIO_MUTE()					GPIO_O_SET(GPIO_MUTE_PORT,0)
		#define	GPIO_DEMUTE()				GPIO_O_SET(GPIO_MUTE_PORT,1)
	  #endif//#ifdef MINTON_DEMUTE_GPIOIN	
	#else//#ifdef LOW_MUTE
		#define	GPIO_MUTE()					GPIO_O_SET(GPIO_MUTE_PORT,1)
		#define	GPIO_DEMUTE()				GPIO_O_SET(GPIO_MUTE_PORT,0)
	#endif//#ifdef LOW_MUTE
#else//#ifdef	USE_GPIO_MUTE
	#define	GPIO_MUTE()						//0     //wanghaoying 2003-8-12 20:51
	#define	GPIO_DEMUTE()					//0     //wanghaoying 2003-8-12 20:51
#endif//#ifdef	USE_GPIO_MUTE


                             
#endif/*__GPIO_MUTE_8200_H*/

