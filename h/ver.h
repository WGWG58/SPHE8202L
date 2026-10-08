/*
*
*/
#ifndef __VER_H
#define __VER_H

/*WMA/HDCD:
* "This product is protected by certain intellectual property rights of
* Microsoft and cannot be used or further
* distributed without a license from Microsoft.
*/

#define SPHE8202  1 //terry,2004/4/9 10:39AM

/*
* This file must use C language format,because it will be parser by cpp.exe
*/
//Maoyong 2004.04.17 move KERNER_VERSION to setup_tab_ui1.c, but it will at last
//rewrited and defined as an array in kernel part code.

//#define PMP_DVD
//#define DESKTOP_ESP  //wthsin, 2005/3/2 11:33am

// KERNEL_VERSION moved to libkern.a, leochen 2004/4/19 09:44¤U¤È
#if defined(SUPPORT_MIDI)    
    #define MPEG_UI_VERSION                     "302."//"3.02."      
#elif defined(PMP_DVD)  
    #define MPEG_UI_VERSION                     "001." //5-3-26 1:10  
#else//Desktop & Portable use
    //#define MPEG_UI_VERSION                   "1.00."     //20040416
    #define MPEG_UI_VERSION                     "018."      //2006-9-9
#endif  

#endif

