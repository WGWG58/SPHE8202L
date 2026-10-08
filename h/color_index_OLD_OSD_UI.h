

#ifdef SETUP_COLOR_TYPE2  //liulifeng add 2004-10-10 14:44
//to solve when undefine SETUP_COLOR_TYPE2 the color of setup menu unnormal

// setup menu color map
#ifdef ALCO_DVD_UI
#define setupBGcolorH	0		//background color - Head Area
#define setupBGcolorI	0		//background color - icon bar
#define setupBGcolorT	0		//background color - Title area
#define setupBGcolorB	0		//background color - Body area
#define setupBGcolorF	0		//background color - Foot area		
#define	setupBGcolorL2	0		//background color - level 2 area (items)
#define	setupBGcolorL3	0		//background color - level 3 area (selections)
#define setupBGcolorSL  0		////background color - Separate Line	


#define setupFcolorT	7		//font color - Title

#define setupFcolorIN	10		//font color - Item Normal
#define	setupBGcolorIN	0		//background color - Item Normal
#define setupFcolorIM	1		//font color - Item Marked
#define	setupBGcolorIM	5		//background color - Item Marked
#define setupFcolorIS	7		//font color - Item Selected
#define	setupBGcolorIS	0		//background color - Item Selected

#define setupFcolorSN	10		//font color - Selection Normal
#define	setupBGcolorSN	0		//background color - Selection Normal
#define setupFcolorSM	1		//font color - Selection Marked
#define	setupBGcolorSM	5		//background color - Selection Marked
#define setupFcolorSS	7		//font color - Selection Selected
#define	setupBGcolorSS	0		//background color - Selection Selected

#define setupFcolorAL2	5		//font clolr - Arrow level 2 
#define	setupBGcolorAL2	0		//background color - Arrow level 2
#define setupFcolorAL3	5		//font clolr - Arrow level 3 
#define	setupBGcolorAL3	0		//background color - Arrow level 3

#define setupFcolorSSU	10		//font color - Scale String Up
#define setupFcolorSSD	1		//font color - Scale String Down
#define	setupBGcolorSPU	3		//background color - Scale Panel Up
#define	setupBGcolorSPD	5		//background color - Scale Panel Down

#define setupEcolorSPTLU 2		//edge color - Scale Panel Top Left Up
#define setupEcolorSPTLD 1		//edge color - Scale Panel Top Left Down
#define setupEcolorSPBRU 1		//edge color - Scale Panel Bottom Right Up
#define setupEcolorSPBRD 2		//edge color - Scale Panel Bottom Right Down

#define setupBGcolorSCU 14		//background color - Scale Cursor Up
#define setupBGcolorSCD 14		//background color - Scale Cursor Down

#define setupEcolorSCTLU 2		//edge color - Scale Cursor Top Left Up
#define setupEcolorSCTLD 2		//edge color - Scale Cursor Top Left Down
#define setupEcolorSCBRU 3		//edge color - Scale Cursor Bottom Right Up
#define setupEcolorSCBRD 3		//edge color - Scale Cursor Bottom Right Down
#define setupBGcolorSCBU 2		//back color - Scale Cursor Bar Up  
#define setupBGcolorSCBD 1		//back color - Scale Cursor Bar Down

#define	setupBGcolorCUSTM 0		//background color - CUSTM page 
#define setupFcolorCN	10		//font color - CUSTM Normal 
#define	setupBGcolorCN	0		//background color - CUSTM Normal 
#define setupFcolorCS	7		//font color - CUSTM Special
#define	setupBGcolorCS	0		//background color - CUSTM Special

#else //end ALCO_DVD_UI

#define setupBGcolorH	0		//background color - Head Area
#define setupBGcolorI	13		//background color - icon bar
#define setupBGcolorT	0		//background color - Title area
#define setupBGcolorB	14		//background color - Body area
#define setupBGcolorF	13		//background color - Foot area		
#define	setupBGcolorL2	14		//background color - level 2 area (items)
#define	setupBGcolorL3	14		//background color - level 3 area (selections)
#define setupBGcolorSL  12		////background color - Separate Line	


#define setupFcolorT	7		//font color - Title

#define setupFcolorIN	2		//font color - Item Normal
#define	setupBGcolorIN	14		//background color - Item Normal
#define setupFcolorIM	1		//font color - Item Marked
#define	setupBGcolorIM	5		//background color - Item Marked
#define setupFcolorIS	4		//font color - Item Selected
#define	setupBGcolorIS	14		//background color - Item Selected

#define setupFcolorSN	2		//font color - Selection Normal
#define	setupBGcolorSN	14		//background color - Selection Normal
#define setupFcolorSM	1		//font color - Selection Marked
#define	setupBGcolorSM	5		//background color - Selection Marked
#define setupFcolorSS	4		//font color - Selection Selected
#define	setupBGcolorSS	14		//background color - Selection Selected

#define setupFcolorAL2	2		//font clolr - Arrow level 2 
#define	setupBGcolorAL2	14		//background color - Arrow level 2
#define setupFcolorAL3	2		//font clolr - Arrow level 3 
#define	setupBGcolorAL3	14		//background color - Arrow level 3

#define setupFcolorSSU	2		//font color - Scale String Up
#define setupFcolorSSD	4		//font color - Scale String Down
#define	setupBGcolorSPU	14		//background color - Scale Panel Up
#define	setupBGcolorSPD	5		//background color - Scale Panel Down

#define setupEcolorSPTLU 2		//edge color - Scale Panel Top Left Up
#define setupEcolorSPTLD 3		//edge color - Scale Panel Top Left Down
#define setupEcolorSPBRU 3		//edge color - Scale Panel Bottom Right Up
#define setupEcolorSPBRD 2		//edge color - Scale Panel Bottom Right Down

#define setupBGcolorSCU 14		//background color - Scale Cursor Up
#define setupBGcolorSCD 14		//background color - Scale Cursor Down

#define setupEcolorSCTLU 2		//edge color - Scale Cursor Top Left Up
#define setupEcolorSCTLD 2		//edge color - Scale Cursor Top Left Down
#define setupEcolorSCBRU 3		//edge color - Scale Cursor Bottom Right Up
#define setupEcolorSCBRD 3		//edge color - Scale Cursor Bottom Right Down
#define setupBGcolorSCBU 2		//back color - Scale Cursor Bar Up  
#define setupBGcolorSCBD 1		//back color - Scale Cursor Bar Down

#define	setupBGcolorCUSTM 14		//background color - CUSTM page 
#define setupFcolorCN	2		//font color - CUSTM Normal 
#define	setupBGcolorCN	14		//background color - CUSTM Normal 
#define setupFcolorCS	7		//font color - CUSTM Special
#define	setupBGcolorCS	14		//background color - CUSTM Special
#endif //end ALCO_DVD_UI
#ifdef SELECT_MEDIA_IN_SETUPMENU   //denghg  add 2005-2-15 17:31
#define SGRAYCOLOR		setupEcolorSPBRU  //font color - NO USB 0R NO CARD
#endif
#ifdef USE_SETUP_ITEM_ENABLE_FLAG //Added by chenzhao on 2005-3-31 16:14  
    #ifdef HIDE_DISNABLE_ITEM
    #define setupFcolorID   setupBGcolorIN  //font color - Item Disnable
    #else
    #define setupFcolorID   setupEcolorSPBRU //font color - Item Disnable
    #endif
#endif


#else  //liulifeng add 2004-10-10 14:44
//to solve when undefine SETUP_COLOR_TYPE2 the color of setup menu unnormal

// setup menu color map

#define setupBGcolorH	6		//background color - Head Area
#define setupBGcolorI	6		//background color - icon bar
#define setupBGcolorT	6		//background color - Title area
#define setupBGcolorB	6		//background color - Body area
#define setupBGcolorF	6		//background color - Foot area
#define	setupBGcolorL2	6		//background color - level 2 area (items)
#define	setupBGcolorL3	6		//background color - level 3 area (selections)
#define setupBGcolorSL  6		////background color - Separate Line


#define setupFcolorT	7		//font color - Title

#define setupFcolorIN	0		//font color - Item Normal
#define	setupBGcolorIN	6		//background color - Item Normal
#define setupFcolorIM	2		//font color - Item Marked
#define	setupBGcolorIM	5		//background color - Item Marked
#define setupFcolorIS	4		//font color - Item Selected
#define	setupBGcolorIS	6		//background color - Item Selected

#define setupFcolorSN	0		//font color - Selection Normal
#define	setupBGcolorSN	6		//background color - Selection Normal
#define setupFcolorSM	2		//font color - Selection Marked
#define	setupBGcolorSM	5		//background color - Selection Marked
#define setupFcolorSS	4		//font color - Selection Selected
#define	setupBGcolorSS	6		//background color - Selection Selected

#define setupFcolorAL2	0		//font clolr - Arrow level 2
#define	setupBGcolorAL2	6		//background color - Arrow level 2
#define setupFcolorAL3	0		//font clolr - Arrow level 3
#define	setupBGcolorAL3	6		//background color - Arrow level 3

#define setupFcolorSSU	0		//font color - Scale String Up
#define setupFcolorSSD	2		//font color - Scale String Down
#define	setupBGcolorSPU	6		//background color - Scale Panel Up
#define	setupBGcolorSPD	5		//background color - Scale Panel Down

#define setupEcolorSPTLU 2		//edge color - Scale Panel Top Left Up
#define setupEcolorSPTLD 0		//edge color - Scale Panel Top Left Down
#define setupEcolorSPBRU 0		//edge color - Scale Panel Bottom Right Up
#define setupEcolorSPBRD 2		//edge color - Scale Panel Bottom Right Down

#define setupBGcolorSCU 6		//background color - Scale Cursor Up
#define setupBGcolorSCD 5		//background color - Scale Cursor Down

#define setupEcolorSCTLU 2		//edge color - Scale Cursor Top Left Up
#define setupEcolorSCTLD 0		//edge color - Scale Cursor Top Left Down
#define setupEcolorSCBRU 0		//edge color - Scale Cursor Bottom Right Up
#define setupEcolorSCBRD 2		//edge color - Scale Cursor Bottom Right Down
#define setupBGcolorSCBU 0		//back color - Scale Cursor Bar Up
#define setupBGcolorSCBD 2		//back color - Scale Cursor Bar Down

#define	setupBGcolorCUSTM 6		//background color - CUSTM page
#define setupFcolorCN	2		//font color - CUSTM Normal
#define	setupBGcolorCN	6		//background color - CUSTM Normal
#define setupFcolorCS	7		//font color - CUSTM Special
#define	setupBGcolorCS	6		//background color - CUSTM Special
#ifdef SELECT_MEDIA_IN_SETUPMENU  //denghg  add 2005-2-15 17:10
#define SGRAYCOLOR		setupEcolorSPBRU //font color - NO USB 0R NO CARD
#endif
#ifdef USE_SETUP_ITEM_ENABLE_FLAG //Added by chenzhao on 2005-3-31 16:14  
    #ifdef HIDE_DISNABLE_ITEM
    #define setupFcolorID   setupBGcolorIN  //font color - Item Disnable
    #else
    #define setupFcolorID   setupEcolorSPBRU //font color - Item Disnable
    #endif
#endif

#endif
//===========================================ending=================================


