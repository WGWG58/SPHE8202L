#ifndef	__UPDATE_INFO_H
#define __UPDATE_INFO_H

//********************************************************************
// CUSTM(9735) page will display the code update date and update week
// added by JSLin //2004
// jslin moved to here from SET.h	//20050304 
//********************************************************************
    #define UPDATE_DATE					"20061015"			//code update date in VSS
    #define UPDATE_WEEK					"W642"//kernel ver.= 441				//code update week in VSS
    #ifdef DVB_DVD_8202
        #define DVB_UPDATE_DATE					"20061014"			//code update date in VSS
        #define DVB_UPDATE_WEEK					"W642"				//code update week in VSS
    #endif     
#endif
