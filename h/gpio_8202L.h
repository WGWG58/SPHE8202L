#ifndef __GPIO_8202_H
#define __GPIO_8202_H

#if (!defined(DVDRELEASE) && defined(TASK_GBG))// || defined(ENABLE_UART0_IN_RELEASE_MODE)
    #undef USE_8202L_DQM2_AS_GPIO_MUTE
#endif

/************************************ AUDIO GPIO MUTE setting *************************/

// gpio mute function
#ifdef USE_8202L_DQM2_AS_GPIO_MUTE //pin21
	#define	USE_GPIO_MUTE					1
	#define	GPIO_MUTE_PORT					20
	#define	SFT_CFG_GPIO()							        \
				do {                                        \
				    	regs0->gpio_first[1]|= (0x1<<4);	\
				    GPIO_M_SET(GPIO_MUTE_PORT, 1);			\
                    GPIO_E_SET(GPIO_MUTE_PORT, 1);	        \
				} while (0)
#else
	#define	GPIO_MUTE_PORT					//0     //wanghaoying 2003-8-12 20:50
	#define	SFT_CFG_GPIO()					//0     //wanghaoying 2003-8-12 20:51
#endif

#ifdef	USE_GPIO_MUTE
	#ifdef LOW_MUTE
		#ifdef MUTE_PULL_HIGH						// ronnie 2004/09/09
			#define	GPIO_MUTE()	                    \
				do {                                \
            		GPIO_E_SET(GPIO_MUTE_PORT,1);   \
            		GPIO_O_SET(GPIO_MUTE_PORT,0);   \
        		} while (0)	
        	#define	GPIO_DEMUTE()				GPIO_E_SET(GPIO_MUTE_PORT,0)	
		#else
			#define	GPIO_MUTE()					GPIO_O_SET(GPIO_MUTE_PORT,0)
			#define	GPIO_DEMUTE()				GPIO_O_SET(GPIO_MUTE_PORT,1)	
		#endif	
        
    #else//#ifdef LOW_MUTE
		#define	GPIO_MUTE()					GPIO_O_SET(GPIO_MUTE_PORT,1)
		#define	GPIO_DEMUTE()				GPIO_O_SET(GPIO_MUTE_PORT,0)
	#endif//#ifdef LOW_MUTE
#else//#ifdef	USE_GPIO_MUTE
	#define	GPIO_MUTE()						//0     //wanghaoying 2003-8-12 20:51
	#define	GPIO_DEMUTE()					//0     //wanghaoying 2003-8-12 20:51
#endif//#ifdef	USE_GPIO_MUTE


/**************************8202L SCART TV GPIO setting****************************/

#if defined(SCART_TV_128_USE_PIN22_45_58)    //8202L 128PIN SCART CONTROL 16M

    #define SUPPORT_SCART_TV                1

    //PIN58 SIGNAL_SW//CVBS:RGB => 0:1
    #define GPIO_SCART_RGB_SW               25
    #define SET_SCART_RGB_GPIO()                    \
        do {                                        \
            regs0->gpio_first[1]|= (0x1<<9);	    \
            GPIO_M_SET(GPIO_SCART_RGB_SW, 1);       \
            GPIO_E_SET(GPIO_SCART_RGB_SW, 1);       \
        } while (0)					

    //PIN22 RELEASE_SCART//NORMAL PLAY = 0
    #define GPIO_SCART_RELEASE_SW               21
    #define SET_SCART_RELEASE_GPIO()                \
        do {                                        \
            regs0->gpio_first[1]|= (0x1<<5);        \
            GPIO_M_SET(GPIO_SCART_RELEASE_SW, 1);   \
            GPIO_E_SET(GPIO_SCART_RELEASE_SW, 1);   \
        } while (0)					

    //PIN45 DISPLAY_SW   // 16/9:4/3 => 0:1     
    #define GPIO_SCART_DISPLAY_SW               23
    #define SET_SCART_DISPLAY_GPIO()                \
        do {                                        \
            regs0->gpio_first[1]|= (0x1<<7);        \
            GPIO_M_SET(GPIO_SCART_DISPLAY_SW, 1);   \
            GPIO_E_SET(GPIO_SCART_DISPLAY_SW, 1);   \
        } while (0)

#elif defined(SCART_TV_128_USE_PIN16_19_22) //8202L 128PIN SCART CONTROL 64M

    #define SUPPORT_SCART_TV                1

    //PIN16 SIGNAL_SW//CVBS:RGB => 0:1
    #define GPIO_SCART_RGB_SW                   15
    #define SET_SCART_RGB_GPIO()                    \
        do {                                        \
            GPIO_M_SET(GPIO_SCART_RGB_SW, 1);       \
            GPIO_E_SET(GPIO_SCART_RGB_SW, 1);       \
        } while (0)					

    //PIN22 RELEASE_SCART//NORMAL PLAY = 0 //R_CS4_B
    #define GPIO_SCART_RELEASE_SW               21
    #define SET_SCART_RELEASE_GPIO()                \
        do {                                        \
            regs0->gpio_first[1]|= (0x1<<5);        \
            GPIO_M_SET(GPIO_SCART_RELEASE_SW, 1);   \
            GPIO_E_SET(GPIO_SCART_RELEASE_SW, 1);   \
        } while (0)					

    //PIN19 DISPLAY_SW   // 16/9:4/3 => 0:1     
    #define GPIO_SCART_DISPLAY_SW               18
    #define SET_SCART_DISPLAY_GPIO()                \
        do {                                        \
            GPIO_M_SET(GPIO_SCART_DISPLAY_SW, 1);   \
            GPIO_E_SET(GPIO_SCART_DISPLAY_SW, 1);   \
        } while (0)
        
#else
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
