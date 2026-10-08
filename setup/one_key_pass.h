#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE         
#define MAIN_SETUP_PAGE_BGCOLOR  0     
#define SETUP_HL_COLOR      5
#define ONE_KEY_PASS_X  	4//3
#define ONE_KEY_PASS_Y  	8
#define SETUP_X         	17
#define SETUP_Y         	8
#define EXIT_SETUP_MENU_X	8
#define EXIT_SETUP_MENU_Y	20//10
void draw_setup_Btn_HL(BYTE r,UINT32 xStart, UINT32 yStart,UINT32 xLen,UINT32 yLen, int LineWidth,BYTE color);
void ShowOneKeyPassPage();
void ShowProfessionalSetup();
int GetOneKeyPageSel(int index_y);
#endif


