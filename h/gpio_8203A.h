#ifndef __GPIO_8202_H
#define __GPIO_8202_H

#ifdef USE_ROM_EXT_AS_GPIO_MUTE //hongfeng 2005-08-06
#include "rom_bus_io.h"
#endif
/***********************************SET RISC CTRL GPIO*************************/
//liumzh eastech used, for audio mute						    
    #define	SFT_CFG_GPIO12()						\
				do {								\
					GPIO_M_SET(12, 1);	            \
				} while (0)

    #define SFT_CFG_GPIO32()                        \
				do {								\
					regs0->sft_cfg0 &= ~(0x1 << 0);	\
					GPIO_M_SET(32, 1);	            \
				} while (0)
/*
*GPIO56:pin172(216pin)****pin200(256pin)
*/
    #define SFT_CFG_GPIO56()                        \
				do {								\
					regs0->sft_cfg3 &= ~(0x1 << 4);	\
					GPIO_M_SET(56, 1);	            \
				} while (0)
/*
*GPIO2:pin49(216pin)****pin59(256pin)
*/
    #define SFT_CFG_GPIO2()                        \
				do {								\
					regs0->sft_cfg4 &= ~(0x1 << 2);	\
					GPIO_M_SET(2, 1);	            \
				} while (0)
/*
*GPIO3:pin50(216pin)****pin60(256pin)
*/
    #define SFT_CFG_GPIO3()                        \
				do {								\
					regs0->sft_cfg4 &= ~(0x1 << 3);	\
					GPIO_M_SET(3, 1);	            \
				} while (0)

    #define SFT_CFG_GPIO58()                        \
				do {								\
					regs0->sft_cfg3 &= ~(0x1 << 7);	\
					GPIO_M_SET(58, 1);	            \
				} while (0)
/*
*GPIO50:pin193(256pin)***pin165(216pin)
*/
    #define SFT_CFG_GPIO50()                        \
				do {								\
					regs0->sft_cfg3 &= ~(0x1 << 5);	\
					GPIO_M_SET(50, 1);	            \
				} while (0)

	#define	SFT_CFG_GPIO14()						\
				do {								\
					regs0->sft_cfg6 &= ~(0x1 << 4);	\
					GPIO_M_SET(14, 1);	\
				} while (0)	
/*8200
	#define	SFT_CFG_GPIO15()						\
				do {								\
					regs0->sft_cfg6 &= ~(0x1 << 6);	\
					GPIO_M_SET(15, 1);	\
				} while (0)
*/
	#define	SFT_CFG_GPIO35()						\
				do {								\
					GPIO_M_SET(35, 1);	            \
				} while (0)

/*
*GPIO84:pin157(216pin)***pin178(256pin)
*/
    #define SFT_CFG_GPIO84()                        \
        do {                                        \
            regs0->sft_cfg4 &= ~(0x7 << 13);        \
            GPIO_M_SET(84, 1);                      \
        } while (0)		

/*
*GPIO85:pin158(216pin)***pin179(256pin)
*/
    #define SFT_CFG_GPIO85()                        \
        do {                                        \
            regs0->sft_cfg4 &= ~(0x7 << 13);        \
            GPIO_M_SET(85, 1);                      \
        } while (0)
/*
*GPIO88:pin183(256pin)
*/
    #define SFT_CFG_GPIO88()                        \
        do {                                        \
            GPIO_M_SET(88, 1);                      \
        } while (0)
/*
*GPIO89:pin184(256pin)
*/
    #define SFT_CFG_GPIO89()                        \
        do {                                        \
            GPIO_M_SET(89, 1);                      \
        } while (0)
/*
*GPIO90:pin185(256pin)
*/
    #define SFT_CFG_GPIO90()                        \
        do {                                        \
            GPIO_M_SET(90, 1);                      \
        } while (0)
/*
*GPIO91:pin186(256pin)
*/
    #define SFT_CFG_GPIO91()                        \
        do {                                        \
            GPIO_M_SET(91, 1);                      \
        } while (0)
/*
*GPIO92:pin225(256pin)
*/
    #define SFT_CFG_GPIO92()                        \
        do {                                        \
            GPIO_M_SET(92, 1);                      \
        } while (0)

/*
*GPIO93:pin226(256pin)
*Disable ROM_A21(Pin226),ROM_A22(Pin227) as GPIO93,94  
*             //regs0->sft_cfg1 &= ~(0x1 << 4);        
*			but now use:regs0->sdc_data_cnt[6][0] |= (1<<2);
*/
    #define SFT_CFG_GPIO93()                        \
        do {                                        \
            regs0->sdc_data_cnt[6][0] |= (0x0c);    \
			regs0->sdc_data_cnt[6][0] |= (1<<2);	\
            GPIO_M_SET(93, 1);                      \
        } while (0)
/*
*GPIO94:pin227(256pin)
*Disable ROM_A21(Pin226),ROM_A22(Pin227) as GPIO93,94  
*/
    #define SFT_CFG_GPIO94()                        \
        do {                                        \
            regs0->sdc_data_cnt[6][0] |= (0x0c);    \
            regs0->sft_cfg1 &= ~(0x1 << 5);         \
            GPIO_M_SET(94, 1);                      \
        } while (0)
/*
*GPIO95:pin228(256pin)
*/
    #define SFT_CFG_GPIO95()                        \
        do {                                        \
            GPIO_M_SET(95, 1);                      \
        } while (0)

/*
*GPIO8:pin55(8202s_216pin)  fangang added 2004-12-30 14:08
*/
    #define SFT_CFG_GPIO8()                        \
        do {                                        \
            regs0->sft_cfg4 &= ~(0x1 << 6);         \
            GPIO_M_SET(8, 1);                      \
        } while (0)

/*
*GPIO16:pin66(8202s_216pin)  fangang added 2004-12-30 14:08
*/
    #define SFT_CFG_GPIO16()                        \
        do {                                        \
            regs0->sft_cfg1 &= ~(0x1 << 3);         \
            GPIO_M_SET(16, 1);                      \
        } while (0)
        
/*//goto line 56
*GPIO15:pin65(8202s_216pin)  fangang added 2004-12-30 14:08
*/    
     #define SFT_CFG_GPIO15()                        \
        do {                                        \
            GPIO_M_SET(15, 1);                      \
        } while (0)
       
                
/***********************************SET RISC CTRL GPIO*************************/




// gpio mute function
#ifdef USE_A19_AS_GPIO_MUTE//pin66
	#define	USE_GPIO_MUTE					1
	#define	GPIO_MUTE_PORT					32
	#define	SFT_CFG_GPIO()							\
				do {								\
                    SFT_CFG_GPIO32();               \
					GPIO_E_SET(GPIO_MUTE_PORT, 1);	\
				} while (0)
#elif defined USE_AUD3_AS_GPIO_MUTE//pin172(216PIN)//pin200(256pin)
	#define	USE_GPIO_MUTE					1
	#define	GPIO_MUTE_PORT					56//60
	#define	SFT_CFG_GPIO()							\
				do {								\
                    SFT_CFG_GPIO56();	\
					GPIO_E_SET(GPIO_MUTE_PORT, 1);	\
				} while (0)
#elif defined USE_ROM_EXT_AS_GPIO_MUTE  //hongfeng 2005-08-06
        #define	USE_GPIO_MUTE					1
        //#define	GPIO_MUTE_PORT					56//60
        #define	SFT_CFG_GPIO()
#elif defined USE_AUD_AS_GPIO_MUTE//pin164
	#define	USE_GPIO_MUTE					1
	#define	GPIO_MUTE_PORT					58
	#define	SFT_CFG_GPIO()							\
				do {								\
                    SFT_CFG_GPIO58();           	\
					GPIO_E_SET(GPIO_MUTE_PORT, 1);	\
				} while (0)
#elif defined USE_AUD4_AS_GPIO_MUTE//pin163
	#define	USE_GPIO_MUTE					1
	#define	GPIO_MUTE_PORT					50

	#define	SFT_CFG_GPIO()							\
				do {								\
					SFT_CFG_GPIO50();           	\
					GPIO_E_SET(GPIO_MUTE_PORT, 1);	\
				} while (0)				
#elif defined USE_A11_AS_GPIO_MUTE//pin109
	#define	USE_GPIO_MUTE					1
	#define	GPIO_MUTE_PORT					14
	#define	SFT_CFG_GPIO()							\
				do {								\
                    SFT_CFG_GPIO14();	            \
					GPIO_E_SET(GPIO_MUTE_PORT, 1);	\
				} while (0)												
#elif 0//defined USE_SBA1_AS_GPIO_MUTE//pin121
	#define	USE_GPIO_MUTE					1
	#define	GPIO_MUTE_PORT					15
	#define	SFT_CFG_GPIO()							\
				do {								\
                    SFT_CFG_GPIO15();	            \
					GPIO_E_SET(GPIO_MUTE_PORT, 1);	\
				} while (0)
#elif defined USE_CS2_AS_GPIO_MUTE //pin70
	#define	USE_GPIO_MUTE					1
	#define	GPIO_MUTE_PORT					35
	#define	SFT_CFG_GPIO()							\
				do {								\
                    SFT_CFG_GPIO35();	            \
					GPIO_E_SET(GPIO_MUTE_PORT, 1);	\
				} while (0)
#elif defined(USE_ATARST_AS_GPIO_MUTE)      //pin29    //hq,20040216
    #define USE_GPIO_MUTE     1
    #define GPIO_MUTE_PORT    3
    #define SFT_CFG_GPIO()                  \
        do {                                \
            SFT_CFG_GPIO3();                \
            GPIO_E_SET(GPIO_MUTE_PORT, 1);  \
        } while (0)					
#elif defined(USE_SPDIF_OUT_AS_GPIO_MUTE)      
    #define USE_GPIO_MUTE     1
    #define GPIO_MUTE_PORT    52
    #define SFT_CFG_GPIO()                  \
        do {                                \
            regs0->sft_cfg3&=~((0x01)<<8);   \
            GPIO_E_SET(GPIO_MUTE_PORT, 1);  \
        } while (0)					

#elif defined(USE_PIN62_AS_GPIO_MUTE)      
    #define USE_GPIO_MUTE     1
    #define GPIO_MUTE_PORT    13
    #define SFT_CFG_GPIO()                  \
        do {                                \
            GPIO_M_SET(GPIO_MUTE_PORT, 1);  \
            GPIO_E_SET(GPIO_MUTE_PORT, 1);  \
        } while (0)	
#elif defined(USE_PIN172_AS_GPIO_MUTE)      
    #define USE_GPIO_MUTE     1
    #define GPIO_MUTE_PORT    53
    #define SFT_CFG_GPIO()                  \
        do {                                \
            regs0->sft_cfg3 &= ~(0x1);      \
            GPIO_M_SET(GPIO_MUTE_PORT, 1);  \
            GPIO_E_SET(GPIO_MUTE_PORT, 1);  \
        } while (0)	
#elif defined(USE_PIN174_AS_GPIO_MUTE)   //for alco pvs1090   
    #define USE_GPIO_MUTE     1
    #define GPIO_MUTE_PORT    54
    #define SFT_CFG_GPIO()                  \
        do {                                \
            GPIO_M_SET(GPIO_MUTE_PORT, 1);  \
            GPIO_E_SET(GPIO_MUTE_PORT, 1);  \
        } while (0)	        
#else
	#define	GPIO_MUTE_PORT					//0     //wanghaoying 2003-8-12 20:50
	#define	SFT_CFG_GPIO()					//0     //wanghaoying 2003-8-12 20:51
#endif

#ifdef	USE_GPIO_MUTE
	#ifdef LOW_MUTE
		#ifdef MUTE_PULL_HIGH						// ronnie 2004/09/09
			#define	GPIO_MUTE()	\
				do {                                \
            		GPIO_E_SET(GPIO_MUTE_PORT,1);   \
            		GPIO_O_SET(GPIO_MUTE_PORT,0);   \
        		} while (0)	
        	#define	GPIO_DEMUTE()				GPIO_E_SET(GPIO_MUTE_PORT,0)	
		#else
			#define	GPIO_MUTE()					GPIO_O_SET(GPIO_MUTE_PORT,0)
			#define	GPIO_DEMUTE()				GPIO_O_SET(GPIO_MUTE_PORT,1)	
		#endif	
        
    #elif defined(USE_ROM_EXT_AS_GPIO_MUTE) //for rom_ext_mute hongfeng 2005-08-06
            #define GPIO_MUTE()                         rom_bus_set_io(ROM_BUS_OUT_AMP_MUTE,1)
            #define GPIO_DEMUTE()                       rom_bus_set_io(ROM_BUS_OUT_AMP_MUTE,0)        
	#else//#ifdef LOW_MUTE
		#define	GPIO_MUTE()					GPIO_O_SET(GPIO_MUTE_PORT,1)
		#define	GPIO_DEMUTE()				GPIO_O_SET(GPIO_MUTE_PORT,0)
	#endif//#ifdef LOW_MUTE
#else//#ifdef	USE_GPIO_MUTE
	#define	GPIO_MUTE()						//0     //wanghaoying 2003-8-12 20:51
	#define	GPIO_DEMUTE()					//0     //wanghaoying 2003-8-12 20:51
#endif//#ifdef	USE_GPIO_MUTE


/**************************8202 SCART TV GPIO setting****************************/

#if defined(SCART_TV_216_USE_PIN172_157_158)

    #define SUPPORT_SCART_TV                1

    //PIN172 SIGNAL_SW//CVBS:RGB => 0:1//AUD3
    #define GPIO_SCART_RGB_SW               56
    #define SET_SCART_RGB_GPIO()                    \
        do {                                        \
            SFT_CFG_GPIO56() ;                      \
            GPIO_E_SET(GPIO_SCART_RGB_SW, 1);       \
        } while (0)					

    //PIN157 RELEASE_SCART//NORMAL PLAY = 0
    #define GPIO_SCART_RELEASE_SW               84
    #define SET_SCART_RELEASE_GPIO()                \
        do {                                        \
            SFT_CFG_GPIO84();                       \
            GPIO_E_SET(GPIO_SCART_RELEASE_SW, 1);   \
        } while (0)					

    //PIN158 DISPLAY_SW   // 16/9:4/3 => 0:1     
    #define GPIO_SCART_DISPLAY_SW               85
    #define SET_SCART_DISPLAY_GPIO()                \
        do {                                        \
            SFT_CFG_GPIO85();                       \
            GPIO_E_SET(GPIO_SCART_DISPLAY_SW, 1);   \
        } while (0)

#elif defined(SCART_TV_216_USE_PIN55_65_66) //8202S 216PIN SCART CONTROL

    #define SUPPORT_SCART_TV                1

    //PIN55 SIGNAL_SW//CVBS:RGB => 0:1//SERVO DFCT
    #define GPIO_SCART_RGB_SW                   8
    #define SET_SCART_RGB_GPIO()                    \
        do {                                        \
            SFT_CFG_GPIO8() ;                      \
            GPIO_E_SET(GPIO_SCART_RGB_SW, 1);       \
        } while (0)					

    //PIN66 RELEASE_SCART//NORMAL PLAY = 0 //R_CS4_B
    #define GPIO_SCART_RELEASE_SW               16
    #define SET_SCART_RELEASE_GPIO()                \
        do {                                        \
            SFT_CFG_GPIO16();                       \
            GPIO_E_SET(GPIO_SCART_RELEASE_SW, 1);   \
        } while (0)					

    //PIN65 DISPLAY_SW   // 16/9:4/3 => 0:1     
    #define GPIO_SCART_DISPLAY_SW               15
    #define SET_SCART_DISPLAY_GPIO()                \
        do {                                        \
            SFT_CFG_GPIO15();                       \
            GPIO_E_SET(GPIO_SCART_DISPLAY_SW, 1);   \
        } while (0)

#elif defined(SCART_TV_216_USE_PIN55_63_65) //8202S 216PIN SCART CONTROL

    #define SUPPORT_SCART_TV                1

    //PIN55 SIGNAL_SW//CVBS:RGB => 0:1//SERVO DFCT
    #define GPIO_SCART_RGB_SW                   8
    #define SET_SCART_RGB_GPIO()                    \
        do {                                        \
            SFT_CFG_GPIO8() ;                      \
            GPIO_E_SET(GPIO_SCART_RGB_SW, 1);       \
        } while (0)					

    //PIN63 RELEASE_SCART//NORMAL PLAY = 0 //R_CS4_B
    #define GPIO_SCART_RELEASE_SW               14
    #define SET_SCART_RELEASE_GPIO()                \
        do {                                        \
            GPIO_M_SET(GPIO_SCART_RELEASE_SW, 1);    \
            GPIO_E_SET(GPIO_SCART_RELEASE_SW, 1);   \
        } while (0)					

    //PIN65 DISPLAY_SW   // 16/9:4/3 => 0:1     
    #define GPIO_SCART_DISPLAY_SW               15
    #define SET_SCART_DISPLAY_GPIO()                \
        do {                                        \
            GPIO_M_SET(GPIO_SCART_DISPLAY_SW, 1);    \
            GPIO_E_SET(GPIO_SCART_DISPLAY_SW, 1);   \
        } while (0)
        

#elif defined(OP_SCART_TV_256_USE_PIN226_227_228)

         #define SUPPORT_SCART_TV                1

    //PIN228 SIGNAL_SW//CVBS:RGB => 0:1//AUD3
    #define GPIO_SCART_RGB_SW                   94
    #define SET_SCART_RGB_GPIO()                    \
        do {                                        \
             SFT_CFG_GPIO94();                      \
            GPIO_E_SET(GPIO_SCART_RGB_SW, 1);       \
        } while (0)					

    //PIN226 RELEASE_SCART//NORMAL PLAY = 0
    #define GPIO_SCART_RELEASE_SW               95
    #define SET_SCART_RELEASE_GPIO()                \
        do {                                        \
             SFT_CFG_GPIO95() ;                     \
            GPIO_E_SET(GPIO_SCART_RELEASE_SW, 1);   \
        } while (0)					

    //PIN227 DISPLAY_SW   // 16/9:4/3 => 0:1     
    #define GPIO_SCART_DISPLAY_SW               93
    #define SET_SCART_DISPLAY_GPIO()                \
        do {                                        \
             SFT_CFG_GPIO93();                       \
            GPIO_E_SET(GPIO_SCART_DISPLAY_SW, 1);   \
        } while (0)


#elif defined(SCART_TV_256_USE_PIN226_227_228)

    #define SUPPORT_SCART_TV                1

    //PIN228 SIGNAL_SW//CVBS:RGB => 0:1//AUD3
    #define GPIO_SCART_RGB_SW                   95
    #define SET_SCART_RGB_GPIO()                    \
        do {                                        \
            SFT_CFG_GPIO95() ;                      \
            GPIO_E_SET(GPIO_SCART_RGB_SW, 1);       \
        } while (0)					

    //PIN226 RELEASE_SCART//NORMAL PLAY = 0
    #define GPIO_SCART_RELEASE_SW               93
    #define SET_SCART_RELEASE_GPIO()                \
        do {                                        \
            SFT_CFG_GPIO93();                       \
            GPIO_E_SET(GPIO_SCART_RELEASE_SW, 1);   \
        } while (0)					

    //PIN227 DISPLAY_SW   // 16/9:4/3 => 0:1     
    #define GPIO_SCART_DISPLAY_SW               94
    #define SET_SCART_DISPLAY_GPIO()                \
        do {                                        \
            SFT_CFG_GPIO94();                       \
            GPIO_E_SET(GPIO_SCART_DISPLAY_SW, 1);   \
        } while (0)


#elif defined(SCART_TV_6500_USE_PIN110_111_112) //caoh 6500 control scart 

    #define SUPPORT_SCART_TV                1
    
    unsigned char temp;

    //PIN112 SIGNAL_SW//CVBS:RGB => 0:1//SERVO DFCT
    #define SET_SCART_RGB_GPIO()                    \
        do {                                        \
             temp = read_i2c(0x6a,0x06);            \
             temp &= 0xdf;                          \
             write_i2c(0x6a,0x06,temp );            \
        } while (0)					

    //PIN110 RELEASE_SCART//NORMAL PLAY = 0 //R_CS4_B
    #define SET_SCART_RELEASE_GPIO()                \
        do {                                        \
             temp = read_i2c(0x6a,0x06);            \
             temp &= 0xf7;                          \
             write_i2c(0x6a,0x06,temp );            \
        } while (0)					

    //PIN111 DISPLAY_SW   // 16/9:4/3 => 0:1     
    #define SET_SCART_DISPLAY_GPIO()                \
        do {                                        \
             temp = read_i2c(0x6a,0x06);            \
             temp &= 0xef;                          \
             write_i2c(0x6a,0x06,temp);             \
        } while (0)

#else//#if defined(SCART_TV_216_USE_PIN172_157_158)
	#define	GPIO_SCART_RGB_SW					        //0     ///NONO 4-3-26 23:35
	#define	GPIO_SCART_RELEASE_SW					    //0     ///NONO 4-3-26 23:35
	#define	GPIO_SCART_DISPLAY_SW					    //0     ///NONO 4-3-26 23:35
	#define	SET_SCART_RGB_GPIO()					    //0     //nono 4-3-26 23:35
	#define	SET_SCART_RELEASE_GPIO()					//0     //nono 4-3-26 23:35
	#define	SET_SCART_DISPLAY_GPIO()					//0     //nono 4-3-26 23:35
#endif


#ifdef	SUPPORT_SCART_TV

    #ifdef HI_CTRL_SCART_TO_RGB
        #define	SCART_TV_SET_TO_RGB()	            GPIO_O_SET(GPIO_SCART_RGB_SW,1)     //NONO 4-3-26 23:24
        #define	SCART_TV_SET_TO_CVBS()	            GPIO_O_SET(GPIO_SCART_RGB_SW,0)     //NONO 4-3-26 23:24
    #elif defined(LOW_CTRL_SCART_TO_RGB)
        #define	SCART_TV_SET_TO_RGB()	            GPIO_O_SET(GPIO_SCART_RGB_SW,0)     //NONO 4-3-26 23:24
        #define	SCART_TV_SET_TO_CVBS()	            GPIO_O_SET(GPIO_SCART_RGB_SW,1)     //NONO 4-3-26 23:24
    #endif

    #ifdef HI_CTRL_TO_RELEASE_SCART
        #define	SCART_TV_SET_TO_DVDPLAYER()	            GPIO_O_SET(GPIO_SCART_RELEASE_SW,1)     //NONO 4-3-26 23:24
        #define	SCART_TV_SET_TO_TV()	                GPIO_O_SET(GPIO_SCART_RELEASE_SW,0)     //NONO 4-3-26 23:24
    #elif defined(LOW_CTRL_TO_RELEASE_SCART)
        #define	SCART_TV_SET_TO_DVDPLAYER()	            GPIO_O_SET(GPIO_SCART_RELEASE_SW,0)     //NONO 4-3-26 23:24
        #define	SCART_TV_SET_TO_TV()	                GPIO_O_SET(GPIO_SCART_RELEASE_SW,1)     //NONO 4-3-26 23:24
     #elif defined(CTRL_SCART_TV_TO_RELEASE_SCART)//lijd 2005-4-13 13:36
    	#define	SCART_TV_SET_TO_DVDPLAYER()          \
    		do{                                      \
    			GPIO_O_SET(GPIO_SCART_RELEASE_SW,1); \
    		}while(0)	    
        #define	SCART_TV_SET_TO_TV()                 \
        	do{                                      \
    			GPIO_O_SET(GPIO_SCART_RELEASE_SW,0); \
    		}while(0)		
    #endif

    #ifdef HI_CTRL_SCART_TO_DISPLAY_16B9
        #define	SCART_TV_SET_TO_DISPLAY_16B9()	            GPIO_O_SET(GPIO_SCART_DISPLAY_SW,1)     //NONO 4-3-26 23:24
        #define	SCART_TV_SET_TO_DISPLAY_4B3()	            GPIO_O_SET(GPIO_SCART_DISPLAY_SW,0)     //NONO 4-3-26 23:24
    #elif defined(LOW_CTRL_SCART_TO_DISPLAY_16B9)
        #define	SCART_TV_SET_TO_DISPLAY_16B9()	            GPIO_O_SET(GPIO_SCART_DISPLAY_SW,0)     //NONO 4-3-26 23:24
        #define	SCART_TV_SET_TO_DISPLAY_4B3()	            GPIO_O_SET(GPIO_SCART_DISPLAY_SW,1)     //NONO 4-3-26 23:24
    #elif defined(CTRL_SCART_TO_DISPLAY_16B9)//lijd 2005-4-13 13:36
    	#define	SCART_TV_SET_TO_DISPLAY_16B9()       \
    		do{                                      \
    			GPIO_O_SET(GPIO_SCART_RELEASE_SW,1); \
    			GPIO_O_SET(GPIO_SCART_DISPLAY_SW,1); \
    		}while(0)        
        #define	SCART_TV_SET_TO_DISPLAY_4B3()        \
        	do{                                      \
    			GPIO_O_SET(GPIO_SCART_RELEASE_SW,1); \
    			GPIO_O_SET(GPIO_SCART_DISPLAY_SW,0); \
    		}while(0)                
    #endif

    #ifdef USE_6500_HI_CTRL_SCART_TO_RGB
        #define	SCART_TV_SET_TO_RGB()	             \
         do{                                         \
    			temp = read_i2c(0x6a,0x08);          \
    			temp|=0x04;                          \
    			write_i2c(0x6a,0x08,temp);           \
    		}while(0) 
        #define	SCART_TV_SET_TO_CVBS()	             \
         do{                                         \
    			temp = read_i2c(0x6a,0x08);          \
    			temp&=0xFB;                          \
    			write_i2c(0x6a,0x08,temp);           \
    		}while(0) 
    #elif defined(USE_6500_LOW_CTRL_SCART_TO_RGB)
        #define	SCART_TV_SET_TO_RGB()	             \
        do{                                          \
    			temp = read_i2c(0x6a,0x08);          \
    			temp&=0xFB;                          \
    			write_i2c(0x6a,0x08,temp);           \
    		}while(0) 
        #define	SCART_TV_SET_TO_CVBS()	             \
         do{                                         \
    			temp = read_i2c(0x6a,0x08);          \
    			temp|=0x04;                          \
    			write_i2c(0x6a,0x08,temp);           \
    		}while(0) 
    #endif

    #ifdef USE_6500_HI_CTRL_TO_RELEASE_SCART
        #define	SCART_TV_SET_TO_DVDPLAYER()	         \
         do{                                         \
    			temp = read_i2c(0x6a,0x08);          \
    			temp|=0x01;                          \
    			write_i2c(0x6a,0x08,temp);           \
    		}while(0) 
        #define	SCART_TV_SET_TO_TV()	             \
         do{                                         \
    			temp = read_i2c(0x6a,0x08);          \
    			temp&=0xFE;                          \
    			write_i2c(0x6a,0x08,temp);           \
    		}while(0) 
    #elif defined(USE_6500_LOW_CTRL_TO_RELEASE_SCART)
        #define	SCART_TV_SET_TO_DVDPLAYER()	         \
         do{                                         \
    			temp = read_i2c(0x6a,0x08);          \
    			temp&=0xFE;                          \
    			write_i2c(0x6a,0x08,temp);           \
    		}while(0)  
        #define	SCART_TV_SET_TO_TV()	             \
         do{                                         \
    			temp = read_i2c(0x6a,0x08);          \
    			temp|=0x01;                          \
    			write_i2c(0x6a,0x08,temp);           \
    		}while(0) 
    #endif

    #ifdef USE_6500_HI_CTRL_SCART_TO_DISPLAY_16B9
        #define	SCART_TV_SET_TO_DISPLAY_16B9()	     \
         do{                                         \
    			temp = read_i2c(0x6a,0x08);          \
    			temp|=0x02;                          \
    			write_i2c(0x6a,0x08,temp);           \
    		}while(0) 
        #define	SCART_TV_SET_TO_DISPLAY_4B3()	     \
         do{                                         \
    			temp = read_i2c(0x6a,0x08);          \
    			temp&=0xFD;                          \
    			write_i2c(0x6a,0x08,temp);           \
    		}while(0)  
    #elif defined(USE_6500_LOW_CTRL_SCART_TO_DISPLAY_16B9)
        #define	SCART_TV_SET_TO_DISPLAY_16B9()	     \
         do{                                         \
    			temp = read_i2c(0x6a,0x08);          \
    			temp&=0xFD;                          \
    			write_i2c(0x6a,0x08,temp);           \
    		}while(0)  
        #define	SCART_TV_SET_TO_DISPLAY_4B3()	     \
         do{                                         \
    			temp = read_i2c(0x6a,0x08);          \
    			temp|=0x02;                          \
    			write_i2c(0x6a,0x08,temp);           \
    		}while(0)            
    #endif


    #define SET_SCART_GPIO_SFT_CFG_CTRL()            \
        do {                                \
            SET_SCART_RGB_GPIO(); \
            SET_SCART_RELEASE_GPIO();  \
            SET_SCART_DISPLAY_GPIO();  \
        } while (0)

    #define SET_SCART_TO_RGB()            \
        do {                                \
            SCART_TV_SET_TO_RGB(); \
            SCART_TV_SET_TO_DVDPLAYER();  \
        } while (0)

    #define SET_SCART_TO_CVBS()            \
        do {                                \
            SCART_TV_SET_TO_CVBS(); \
            SCART_TV_SET_TO_DVDPLAYER();  \
        } while (0)

    #define SET_SCART_TO_TV()            \
        do {                                \
            SCART_TV_SET_TO_CVBS(); \
            SCART_TV_SET_TO_DISPLAY_4B3();  \
            SCART_TV_SET_TO_TV();  \
        } while (0)

    #define SET_SCART_TO_DISPLAY_16B9()            \
        do {                                \
            SCART_TV_SET_TO_DISPLAY_16B9(); \
            SCART_TV_SET_TO_DVDPLAYER();  \
        } while (0)

    #define SET_SCART_TO_DISPLAY_4B3()            \
        do {                                \
            SCART_TV_SET_TO_DISPLAY_4B3(); \
            SCART_TV_SET_TO_DVDPLAYER();  \
        } while (0)

#else//#ifdef	USE_GPIO_MUTE
	#define	SET_SCART_GPIO_SFT_CFG_CTRL()						//0     //NONO 4-3-26 23:24
    #define	SCART_TV_SET_TO_RGB()	                            //0     //NONO 4-3-26 23:24
    #define	SCART_TV_SET_TO_CVBS()	                            //0     //NONO 4-3-26 23:24
    #define	SCART_TV_SET_TO_DVDPLAYER()	                        //0     //NONO 4-3-26 23:24
    #define	SCART_TV_SET_TO_TV()	                            //0    //NONO 4-3-26 23:24
    #define	SCART_TV_SET_TO_DISPLAY_16B9()	                    //0     //NONO 4-3-26 23:24
    #define	SCART_TV_SET_TO_DISPLAY_4B3()	                    //0    //NONO 4-3-26 23:24	
#endif//#ifdef	USE_GPIO_MUTE

/**************************8202 SCART TV GPIO setting****************************/

 /****************************8202 D-TERMINAL OUT for JP setting*************************/ 
 ////////////jwk added this model 2005-9-29 14:05////////// 
 //this model named D-terminal,which used in Japan//                           
/**************************************************************************/
/*  ASPECT     FS1     FS2        VFORMAT   I/P   PROGRESSIVE/INTERRACE   */
/*   4:3PS      H	H            L        H       PROGRESSIVE         */
/*   4:3LB      L       H           									  */
/*   16:9       L       L            H        L       INTERRACE			  */
/**************************************************************************/
#ifdef SUPPORT_D_TERMINAL 
#define D_TERMINAL_FS1     			8      //pin55
#define D_TERMINAL_FS2     			15		//pin65
#define D_TERMINAL_VFORMAT			16		//pin66

//==================INIT SETTING=========================//
#define	D_TERMINAL_TV_SET_TO_DISPLAY_16B9()	           \
          do{                 					 \
			SFT_CFG_GPIO8(); 					\
			GPIO_E_SET(D_TERMINAL_FS1,1);			\
			GPIO_O_SET(D_TERMINAL_FS1,0) ; 		 \
			SFT_CFG_GPIO15();                      \
			GPIO_E_SET(D_TERMINAL_FS2,1);             \
			GPIO_O_SET(D_TERMINAL_FS2,0) ;  		\
    	        }while(0)
#define D_TERMINAL_TV_SET_TO_DISPLAY_4B3_LB()         \
	do{                                 \
			SFT_CFG_GPIO8(); 					\
			GPIO_E_SET(D_TERMINAL_FS1,1);			\
			GPIO_O_SET(D_TERMINAL_FS1,0) ;  \
			SFT_CFG_GPIO15();                      \
			GPIO_E_SET(D_TERMINAL_FS2,1);             \
			GPIO_O_SET(D_TERMINAL_FS2,1) ;  \
		}while(0)
#define D_TERMINAL_TV_SET_TO_DISPLAY_4B3_PS()     \
	do{                              \
	   		 SFT_CFG_GPIO8(); 					\
			GPIO_E_SET(D_TERMINAL_FS1,1);			\
			GPIO_O_SET(D_TERMINAL_FS1,1) ;  \
			SFT_CFG_GPIO15();                      \
			GPIO_E_SET(D_TERMINAL_FS2,1);             \
		GPIO_O_SET(D_TERMINAL_FS2,1) ;  \
		}while(0)
#define SET_D_TERMINAL_PSCAN_GPIO()            \
	do{                              \
		SFT_CFG_GPIO16();           \
		GPIO_E_SET(D_TERMINAL_VFORMAT,1);     \
		GPIO_O_SET(D_TERMINAL_VFORMAT,0) ;  \
		}while(0)
#define SET_D_TERMINAL_INTERRACE_GPIO()     \
		do{                              \
		SFT_CFG_GPIO16();					\
		GPIO_E_SET(D_TERMINAL_VFORMAT,1);	\
		GPIO_O_SET(D_TERMINAL_VFORMAT,1) ;  \
		}while(0)
                             
//=================INIT SETTING=============================//
//=================INTERFACE  MODEL============================//
#define SET_D_TERMINAL_VFORMAT_CTRL_PSCAN()            \
        do {                                \
            SET_D_TERMINAL_PSCAN_GPIO(); \
        } while (0)
#define SET_D_TERMINAL_VFORMAT_CTRL_INTERRACE()     \
 do {                                \
            SET_D_TERMINAL_INTERRACE_GPIO(); \
        } while (0)
#define SET_D_TERMINAL_TO_DISPLAY_16B9()            \
        do {                                \
            D_TERMINAL_TV_SET_TO_DISPLAY_16B9(); \
        } while (0)
#define SET_D_TERMINAL_TO_DISPLAY_4B3_LB()            \
        do {                                \
            D_TERMINAL_TV_SET_TO_DISPLAY_4B3_LB(); \
        } while (0)
#define SET_D_TERMINAL_TO_DISPLAY_4B3_PS()       \
	do {                                \
            D_TERMINAL_TV_SET_TO_DISPLAY_4B3_PS(); \
        } while (0)
//=================INTERFACE  MODEL============================//
#endif
/****************************8202 D-TERMINAL OUT for JP setting****jwk add for eastech*******************/ 
#endif/*__GPIO_8202_H*/
