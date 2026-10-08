/**************************************************************
** FILE
** fsGUI_osd.c
**
** DESCRIPTION
**  build a GUI like PC with OSD for MP3/JPEG/WMA ,ect.
**
**
**   Creator:  zhaoyanhua
** 	 Date:     2004-4-2 11:04
****************************************************************/

#include "global.h"
#include "func.h"
#include "memmap.h"
#include "util.h"
#include "graph.h"
#include "memcfg.h"
#include "framebuf.h"
#include "macro.h"
#include "stc.h"
#include "cfont.h"
#include "vfdfunc.h"
#include "osd.h"
#include "image.h"
#include "nesinit.h"
#include "fs96602.h"
#include "fsNAV.h"
#include "fsGUI.h"
#include "fsGUI1.h"


#ifdef OP_UI
#include "menu_def.h"
#include "menu_page.h"
#include "fsGUI_osd_def.h"
#include "fsGUI_osd_func.h"
#include "fs_OSD_bmp.h"
#include "osdGUI_def.h"
#include "osdGUI_func.h"
#include "Infobanner_def.h"
//mainmenu related
extern int	menu_page;
extern int	menu_level;
extern int HL_menu;
extern BYTE index_y1;



UINT16 dir_set_top = 0;
BYTE selected_flag = NONE_SELECTED;
//define null funciton about fsGUI1.c
void FSGUI_JpgUpdateOSD(void)
{}



UINT16 CountSpecifyFile(int iDir)
{}
void Playing2Will(void)
{}

void FSGUI_UpdateInfoArea(BYTE* strInfo)
{}

void FSGUI_Refresh(void)
{}

int FSGUI_PreChangeDir(UINT16 *iDir,UINT16 iDirect)
{}



void FindPreSelectFileDir(UINT16 *iSelect)
{}

void FSGUI_Menu()
{
    FSGUI_OsdMenu();
}

int FSGUI_Select(int iSelect)
{}

void FSGUI_Stop()
{}

void FSGUI_JpgPreview()
{}

void FSGUI_CookFileItem(BYTE iItem)
{}

int  FSGUI_GetDispTrack()
{}

void Restore2PlayingDir(void)
{}

void Restore2PlayingFile(void)
{}

void FSGUI_Shuffle()
{}

UINT32  FSGUI_IsSelectable()
{}

void FSGUI_2Last()
{}

void FSGUI_FileSelect(int iSelect)
{}

void FSGUI_ProgSelect(UINT16 index)
{
    UINT16 iSel = 0;
    UINT16 i = 0;
    
    iSel = prog[index][1] - 1; //get real file index.
    if (iSel >= SUB_FOLDER_BASE)//current prog item is folder
    {    
        pFsJpeg->fsnav_dir_now = iSel - SUB_FOLDER_BASE;//get real dir index in iso9660_dir
        CalcDirFirstPage(pFsJpeg->fsnav_dir_now);
        dir_set_top = 0;
        //printf("#### progselect ,pFsJpeg->fsnav_dir_now:%d,pFsJpeg->fsnav_trk_now:%d--\n",pFsJpeg->fsnav_dir_now,pFsJpeg->fsnav_trk_now);
        //get dir_set[] index value
        for (i = 0; i < pFsJpeg->iso9660_dir_cnt; i++)
        {
            if(dir_set[i] == pFsJpeg->fsnav_dir_now)
            {   
                dir_set_top = i;
                break;
            }
        }
    }
    else//current prog item is file
    {
        pFsJpeg->fsnav_dir_now = prog[index][0]; 
        CalcDirFirstPage(pFsJpeg->fsnav_dir_now);
        pFsJpeg->fsnav_trk_now = iSel - pFsJpeg->first_mp3_entry;
    }
    
    //FSGUI_FileSelect();
    
    if(pFsJpeg->gifsFuncBtn == FS_FUNC_MP3)
        pFsJpeg->gifsState = FS_STATE_MP3;
        
    FSGUI_ShowCurrentSelection((pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry));
}


/*
 *  Description:
 *     to judge if the folder is in its end.
 *
 *  INPUT:
 *     Direction:  
 *          PAGE_UP----> judge if the current file of the folder(iDir) is  its first file
 *          PAGE_DOWN ---> judge if the current file of the folder(iDir) is in its final file.  
 *
 *  RETURN:
 *          TRUE or FALSE
 */
BYTE FSGUI_IsFolderEnd(UINT16 iDir, BYTE Direction)
{
    BYTE  EndFlag = FALSE;
    
    if ((Direction == PAGE_UP) 
    && (pFsJpeg->fsnav_trk_now <= 0))
    {
        EndFlag = TRUE;
    }
    else if ((Direction == PAGE_DOWN) 
    && (pFsJpeg->fsnav_trk_now >= (iso9660_dir[iDir].dir - 1)))
        EndFlag = TRUE;
        
    return EndFlag;
}

/*
 * Description:
 *    Find the first file in this dir
 *
 * INPUT:
 *    type :---> MP3
 *          ---> JPEG
 *
 *    iDir  ---> the dir index(in iso9660_dir)
 *
 * RETURN:
 *    If iDir has this type file, return first file index(in iso9660_file) 
 *    else return -1;
 */
INT16  FSGUI_FindFirstFileForDir(int type, int iDir)
{
    INT16 first_file_index = 0;
    
    if ((iso9660_dir[iDir].type) & (0x01 << type))  
    {
        do
        {
            if (iso9660_file[(first_file_index + pFsJpeg->first_mp3_entry)].type == type)
                break;
            else
                first_file_index ++;
        }while(1); 
    }
    else
    {
        first_file_index = -1;    
    } 

    return first_file_index;
}

/*
 * Description:
 *    when in slide JPEG, stop slide mode return to menu.
 *
 */
void FSGUI_Return2Menu(void)
{
    pFsJpeg->gbfsSlide	= 0;
   
    pFsJpeg->gifsbPreview = 0; 
    //play_state = VCD_STATE_MP3_FILELIST; 
    pFsJpeg->gifsFuncBtn = FS_FUNC_MP3;
    resumeMSF = 0;
#ifdef SURRORT_MP3_PREPLAY
	FS_ClearPreplayFlag();
#endif//#ifdef SURRORT_MP3_PREPLAY

    if (pFsJpeg->gifsState == FS_STATE_JPEG)
    {
        config_memory(MEMORY_GRAPH_SMALL);
    	setup_tv_format(tv_format);
        reset_zoom_state();  
        startup_vpp();
        AVD_ResetMediaStatus();
        #if defined(FALSE_POWER)&&defined(STOP_LOADER)//zhuyanfeng20041008	
		pFsJpeg->gifsbPreview = 0;
		ShowTitle();
        #else
		FS_ForceReturn2Menu();
		#endif
        //printf("#### 111111------RETURN 2 menu sys_cmd:%d--\n",sys_cmd);
        
        
        //NOTE:
        //must load the code again.
        //else  hang.
        //zhaoyanhua note 2004-5-8 11:43
        FSNav_MP3Init();
       
        ShowTitle();
        sys_cmd = 0;//must clear 0
    }
    pFsJpeg->gifsState = FS_STATE_LIST;
    
    //show GUI menu
    FSGUI_Osdinit();
    FSGUI_RefreshMenu(1);
    
}

int FSGUI_NormalPrev(void)
{
    int done = 0;
    UINT16 dir_real_index = 0;
    BYTE   need_new_dir = FALSE;
    UINT16 top = dir_set_top;
    int temp = 0x01 << pFsJpeg->gifsFuncBtn ;
 
    printf("##### FSGUI_NormalPrev ---############--\n");
    
    if (FSGUI_IsFolderEnd(pFsJpeg->fsnav_dir_now, PAGE_UP) == TRUE)//the first file in current dir
    {
        need_new_dir = TRUE;
    }
    else //if (FSGUI_IsFolderEnd() == FALSE)//not change dir
    {
        
        dir_real_index = dir_set[top];
        printf("\n-------not change dir---------\n");
        do
        {
            if (FSGUI_IsFolderEnd(pFsJpeg->fsnav_dir_now, PAGE_UP) == TRUE)//(pFsJpeg->fsnav_trk_now <= 0)
            {   
                need_new_dir = TRUE;
                
                break;
            } 
              
            pFsJpeg->fsnav_trk_now --;
            
            printf("file:%d------type:%d, name=%s, pFsJpeg->gifsFuncBtn:%d\n",pFsJpeg->fsnav_trk_now, iso9660_file[pFsJpeg->fsnav_trk_now+pFsJpeg->first_mp3_entry].type,iso9660_file[pFsJpeg->fsnav_trk_now+pFsJpeg->first_mp3_entry].name, pFsJpeg->gifsFuncBtn);
            if (iso9660_file[(pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry)].type == (pFsJpeg->gifsFuncBtn))
            {
                printf("\n### file FOUND---!!!!!!!!!!!\n");
                if (pFsJpeg->gifsFuncBtn == FS_FUNC_MP3)
                {//when playing MP3, must refresh GUI  
                    pFsJpeg->gifsState = FS_STATE_MP3;//after fs_MP3Mainloop, pFsJpeg->gifsState changed, must reset again.  
                    if (pFsJpeg->fsnav_dir_now == dir_real_index)//update GUI only when the dir in GUI is same with playing dir
			        {
                    	if ((info_mode == INFO_FULL) && (t_disp == 1))
                    		 show_info_banner_page();
			            else
			                FSGUI_OsdCmdUp();
			        }                    
                    FSGUI_ShowCurrentSelection((pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry));
                }
                break;
            }
           
        }while(1);
    }
    
    //change dir
    if (need_new_dir == TRUE)
    {
        printf("--------change dir----------------\n");
        do
        {
            if (top <= 0)
            {
                printf("############ all dir is played over --pFsJpeg->fsnav_trk_now:%d-\n",pFsJpeg->fsnav_trk_now);
                //top = 0;
                //pFsJpeg->fsnav_dir_now = 0;
                pFsJpeg->gbfsSlide = 0;
                sys_cmd = 0;
                pFsJpeg->gifsState = FS_STATE_LIST;
                //fsGUI_RefreshMenu(1); 
                done = 1;
                break;
            }
                
            top--;
            dir_real_index = dir_set[top];
            
            printf(" iso9660_dir[dir_real_index].type=%x, 0x01 << pFsJpeg->gifsFuncBtn :%d, pFsJpeg->gifsFuncBtn:%d, cnt :%d ,name :%s\n",iso9660_dir[dir_real_index].type, temp, pFsJpeg->gifsFuncBtn, dir_real_index, iso9660_dir[dir_real_index].name);
            //printf("Compare result ;%x",((iso9660_dir[dir_real_index].type)& temp));
            
            if (((iso9660_dir[dir_real_index].type) & (0x01 << pFsJpeg->gifsFuncBtn)))
            {
                dir_set_top = top;
                pFsJpeg->fsnav_dir_now = dir_real_index;
                CalcDirFirstPage(pFsJpeg->fsnav_dir_now);
                pFsJpeg->fsnav_trk_now = FSGUI_FindFirstFileForDir(pFsJpeg->gifsFuncBtn, pFsJpeg->fsnav_dir_now);
                //pFsJpeg->fsnav_trk_now = 0;
                if (pFsJpeg->gifsFuncBtn == FS_FUNC_MP3)//when playing MP3, must refresh GUI  
                {   
                    pFsJpeg->gifsState = FS_STATE_MP3; 
                    FSGUI_RefreshMenu(1);
                }          
                break; 
            }

        }while(1);

    }//if (need_new_dir == TRUE)

	return done;
}

int FSGUI_NormalNext(void)
{
    int done = 0;
    UINT16 dir_real_index = 0;
    BYTE   need_new_dir = FALSE;
    UINT16 top = dir_set_top;
    int temp = 0x01 << pFsJpeg->gifsFuncBtn ;
 
    printf("##### FSGUI_NormalNext ---############--\n");
    if (FSGUI_IsFolderEnd(pFsJpeg->fsnav_dir_now, PAGE_DOWN) == TRUE)//(pFsJpeg->fsnav_trk_now == pFsJpeg->last_mp3_entry)//the last file in current dir
    {
        need_new_dir = TRUE;
    }
    else //if (pFsJpeg->fsnav_trk_now < pFsJpeg->last_mp3_entry)//not change dir
    {
        
        dir_real_index = dir_set[top];
        printf("\n-------not change dir---------\n");
        do
        {
            if (FSGUI_IsFolderEnd(pFsJpeg->fsnav_dir_now, PAGE_DOWN) == TRUE)//(pFsJpeg->fsnav_trk_now >= (iso9660_dir[pFsJpeg->fsnav_dir_now].dir - 1))
            {   
                need_new_dir = TRUE;
                
                break;
            } 
              
            pFsJpeg->fsnav_trk_now ++;
            
            printf("file:%d------type:%d, name=%s, pFsJpeg->gifsFuncBtn:%d\n",pFsJpeg->fsnav_trk_now, iso9660_file[pFsJpeg->fsnav_trk_now+pFsJpeg->first_mp3_entry].type,iso9660_file[pFsJpeg->fsnav_trk_now+pFsJpeg->first_mp3_entry].name, pFsJpeg->gifsFuncBtn);
            if (iso9660_file[(pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry)].type == (pFsJpeg->gifsFuncBtn))
            {
                printf("\n### file FOUND---!!!!!!!!!!!\n");
                if (pFsJpeg->gifsFuncBtn == FS_FUNC_MP3)
                {//when playing MP3, must refresh GUI  
                    pFsJpeg->gifsState = FS_STATE_MP3;//after fs_MP3Mainloop, pFsJpeg->gifsState changed, must reset again.  
                    if (pFsJpeg->fsnav_dir_now == dir_real_index)//update GUI only when the dir in GUI is same with playing dir
			        {
                        if  ((info_mode == INFO_FULL) && (t_disp == 1))
                    	    show_info_banner_page();
                        else
                            FSGUI_OsdCmdDown();
                    		
                    }	
                    FSGUI_ShowCurrentSelection((pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry));
                }
                break;
            }
           
        }while(1);
    }
    
    //change dir
    if (need_new_dir == TRUE)
    {
        printf("--------change dir----------------\n");
        do
        {
            if (top >= (pFsJpeg->iso9660_dir_cnt-1))
            {
                printf("############ all dir is played over --pFsJpeg->fsnav_trk_now:%d-\n",pFsJpeg->fsnav_trk_now);
                top = 0;
                //pFsJpeg->fsnav_dir_now = 0;
                pFsJpeg->gbfsSlide = 0;
                sys_cmd = 0;
                pFsJpeg->gifsState = FS_STATE_LIST;
                //fsGUI_RefreshMenu(1); 
                done = 1;
                break;
            }
                
            top++;
            dir_real_index = dir_set[top];
            
            printf(" iso9660_dir[dir_real_index].type=%x, 0x01 << pFsJpeg->gifsFuncBtn :%d, pFsJpeg->gifsFuncBtn:%d, cnt :%d ,name :%s\n",iso9660_dir[dir_real_index].type, temp, pFsJpeg->gifsFuncBtn, dir_real_index, iso9660_dir[dir_real_index].name);
            //printf("Compare result ;%x",((iso9660_dir[dir_real_index].type)& temp));
            
            if (((iso9660_dir[dir_real_index].type) & (0x01 << pFsJpeg->gifsFuncBtn)))
            {
               
                //printf("dir-----pFsJpeg->fsnav_trk_now=%d,loc=%x\n", pFsJpeg->fsnav_trk_now,iso9660_file[pFsJpeg->fsnav_trk_now].loc);
               // printf(" New dir entry iso9660_dir[dir_real_index].type=%x, cnt :%d ,name :%s\n",iso9660_dir[dir_real_index].type, dir_real_index, iso9660_dir[dir_real_index].name);
                dir_set_top = top;
                pFsJpeg->fsnav_dir_now = dir_real_index;
                CalcDirFirstPage(pFsJpeg->fsnav_dir_now);
                pFsJpeg->fsnav_trk_now = FSGUI_FindFirstFileForDir(pFsJpeg->gifsFuncBtn, pFsJpeg->fsnav_dir_now);
                if (pFsJpeg->gifsFuncBtn == FS_FUNC_MP3)//when playing MP3, must refresh GUI  
                {   
                    pFsJpeg->gifsState = FS_STATE_MP3; 
                    FSGUI_RefreshMenu(1);
                }          
                break; 
            }

        }while(1);

    }//if (need_new_dir == TRUE)


	return done;
}



//UINT16 CurrentFiles[800];//record the index of subdir and files of current DIR
//some parameters explaination
//
//CurentFiles[]    ---> record all the real index of subdir and files of a parent DIR
//                      NOTE: 
//                      Here I treat the subdir as file. But their index is different.
//                                            
//                      if subdir   value = real index of subdir + SUBFOLDER_BASE
//                      if file     value = real fill index in iso9660_file[]                        
//
//file_count_in_dir       ---->total files count of a DIR
//
//file_index_in_dir       ---> record the reordered index of files in CurentFiles[]
//                      main for UP/DOWN/LEFT/RIGHT to get  correct file_current_in_page .
//                      range: 0 ~ file_count_in_dir          
// 
//fsnav_dir_now    ---> real dir index value in iso9660_dir[] 
//                      range: 0 ~ (ISO_DIR_MAX-1)
//                    
//
//file_current_in_page     ---->file offset in current page.main for draw GUI.
//                      range: 0 ~ (ONEPAGE -1)
//
//file_array_in_page[]    ----->record the indexs in current page, the value from CurentFiles[].
//                      
//                                           

/*
 *Func: fsGUI_Osd_init
 *
 *Description:
 *  init some parametres
 *
 */
void FSGUI_Osdinit()
{
	osd_init_mainmenu();
	//osd_tog_region(0,OSD_ON);//
	//osd_tog_region(1,OSD_ON);//
	//osd_draw_rect(0, 0, (MENU_BTN_XLEN+24)*16, BUTTON_Y_DIFF*8, 0);//clear the region.
	
	
}

void FSGUI_OsdExitGUI()
{
	//fsGUI_Osdinit();
	system_state = SYSTEM_SETTING;
	printf("### EXIT FSOSD GUI----\n");
	
	//osd_init_mainmenu();
	menu_level = 0;
	menu_page = PLAYPAGE;
	HL_menu = PARENT_MENU;
	index_y1 = 0;
	osd_draw_rect(0, 0, (MENU_BTN_XLEN+24)*16, BUTTON_Y_DIFF*8, 0);//clear the region.
	//clear operation message
    osd_draw_hline_region(0, region[1].osd_w*2-2, 0, 0, region[1].osd_h, 1);
	show_mainmenu();
	ShowPlayState(0);
}
/*
 * Func: fsGUI_OsdMenu()
 *
 * Description:
 *
 *  Show whole FSGUI
 *
 */
void FSGUI_OsdMenu()
{	
	FSNav_MP3Init();
	pFsJpeg->fsnav_dir_now =  FSGUI_GetRootDir(); 
	CalcDirFirstPage(pFsJpeg->fsnav_dir_now);
	printf("### fsGUI_osdMenu---\n");
    pFsJpeg->gbfsSlide = 0;
    //show GUI menu
    
    FSGUI_RefreshMenu(0);

}

/*
 * Description:
 *    if the playing dir change, refresh GUI.
 *
 * INPUT:
 *    mode :  0, show Dir content, HL in  the first item.
 *    mode :  1, Show Dir content , HL according to the 
 *                                            pFsJpeg->fsnav_trk_now  
 *                                            pFsJpeg->first_mp3_entry
 *
 */
void FSGUI_RefreshMenu(int mode)
{
    int i = 0;
    
    
     if (info_mode)	//feeling 2004-05-26
		exit_info_banner_page(0);
		
    OSDGUI_Init();
    //osd_draw_rect(0, 0, (MENU_BTN_XLEN+24)*16, BUTTON_Y_DIFF*8, 0);//clear the region.
    OSDGUI_ShowDirInitPara();
    FSGUI_GetOneDirContent(pFsJpeg->fsnav_dir_now);
    //printf("In Refreshmenu pFsJpeg->fsnav_dir_now:%d,--\n",pFsJpeg->fsnav_dir_now);
    if (mode == 1)
    {
        //Get the value of "pFsJpeg->file_index_in_dir"
        for (i = 0; i < pFsJpeg->file_count_in_dir; i++)
        {
            if ((pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry) == CurrentFiles[i])
            {
                pFsJpeg->file_index_in_dir = i;
                break;   
            }
        }
     }
    //printf("####in Refresh FsJpeg->file_index_in_dir:%d file_current_in_page:%d-pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry-:%d \n",pFsJpeg->file_index_in_dir, pFsJpeg->file_current_in_page, pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry);
	OSDGUI_GetCurrentPage(PAGE_DOWN);
	OSDGUI_DrawOnePage();
    //printf("### value : %d--\n",(pFsJpeg->file_array_in_page[pFsJpeg->file_current_in_page]));
	FSGUI_ShowCurrentSelection((pFsJpeg->file_array_in_page[pFsJpeg->file_current_in_page]));
    
    FSGUI_OperationInit();
}

/*
 * Description:
 *   after or before a operation, set initial state.
 *
 */
void FSGUI_OperationInit(void)
{
#ifdef SURRORT_MP3_PREPLAY
    FS_ClearPreplayFlag();
#endif//#ifdef SURRORT_MP3_PREPLAY
	
    FSGUI_ShowOperationMsg();
    
}


UINT32 FSGUI_OsdCmdSelect()
{
	UINT32 iRes = 0;
	//printf("****** FSGUI SELECT******\n");
	BYTE button_type;
	UINT16 file_now;//file in a page
    UINT16 file_total_now;//total file in array
    
    button_type = OSDGUI_GetSelButtonType(pFsJpeg->file_current_in_page);
    file_now = pFsJpeg->file_current_in_page;
    file_total_now = pFsJpeg->file_array_in_page[file_now];
      
	if(button_type == SUB_BUTTON)
        FSGUI_ShowCurrentSelection(file_total_now);
    else        
        FSGUI_OsdCmdRight();
        
        
    iRes = 0x20000 | sys_cmd;
    sys_cmd = 0;

    return iRes;
}


UINT32 FSGUI_OsdCmdPlay()
{
	UINT32 iRes = 0;
	UINT16 real_file_index = 0;
    UINT16 real_dir_index = 0;
    UINT16 current_file_index = 0;
	int i = 0;
	
    //set play state.    
    play_state = VCD_STATE_MP3_FILELIST;
    
    current_file_index = CurrentFiles[pFsJpeg->file_index_in_dir];
    
    //play file and folder
    if(current_file_index >= SUB_FOLDER_BASE)//if HL is folder,then get first file
    {
        real_dir_index = current_file_index - SUB_FOLDER_BASE;
        //printf("000000iso9660_dir[%d].name:%s\n",real_dir_index,iso9660_dir[real_dir_index].name);
        do
        {
            if(iso9660_dir[real_dir_index].dir > 0)
            {    
                real_file_index = pFsJpeg->Dir_entry[real_dir_index];
                break;
            }
            else
                real_dir_index ++;
        }while(1);
            
        //printf("111111iso9660_dir[%d].name:%s\n",real_dir_index,iso9660_dir[real_dir_index].name);
    }
    else//HL is file ,real file
        real_file_index = current_file_index;
    
    pFsJpeg->gifsFuncBtn = iso9660_file[real_file_index].type;
    real_dir_index = iso9660_file[real_file_index].parent_dir;
    
    if (real_dir_index == FSGUI_GetRootDir())//curent dir is root dir.
    { //main to show selection  
        FSGUI_GetOneDirContent(real_dir_index);
        OSDGUI_GetCurrentPage(PAGE_DOWN);
    }
   
    //get dir_set[] index value
    for (i = 0; i < pFsJpeg->iso9660_dir_cnt; i++)
    {
        if(dir_set[i] == real_dir_index)
        {   
            dir_set_top = i;
            break;
        }
    }

    //get the current dir,trk
    pFsJpeg->fsnav_dir_now = real_dir_index;
    CalcDirFirstPage(pFsJpeg->fsnav_dir_now);
    pFsJpeg->fsnav_trk_now = real_file_index - pFsJpeg->first_mp3_entry;
    
    FSGUI_ShowCurrentSelection((pFsJpeg->file_array_in_page[pFsJpeg->file_current_in_page]));
    
    //according to type,get some  base value
    if(pFsJpeg->gifsFuncBtn == FS_FUNC_MP3)
    {
        pFsJpeg->gifsState = FS_STATE_MP3;
        FSNav_MP3Init();
    }
    else  if(pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG)
    {
        //osd_init__(); 
        pFsJpeg->gifsState = FS_STATE_JPEG;
        cd_subtype = CDROM_JPEG;
        pFsJpeg->g_nJpegMode = JPEG_NORMAL_MODE;
        //close fsGUI
        osd_tog_region(0,OSD_OFF);
        osd_tog_region(1,OSD_OFF);
        osd_draw_rect(0, 0, (MENU_BTN_XLEN+24)*16, BUTTON_Y_DIFF*8, 0);//clear the region.
        pFsJpeg->gbfsSlide = 1;
    }
    
    
    //printf("IN fsGUI osd file:%d------type:%d, name=%s,parentdir :%s\n",pFsJpeg->fsnav_trk_now, iso9660_file[pFsJpeg->fsnav_trk_now+pFsJpeg->first_mp3_entry].type,iso9660_file[pFsJpeg->fsnav_trk_now+pFsJpeg->first_mp3_entry].name, iso9660_dir[real_dir_index].name);
    
    iRes = CMD_FUNC | CMD_FUNC_PLAY;
    
    return iRes;
}

UINT32 FSGUI_OsdCmdUp()
{
	UINT32 iRes = 0;
	
    iRes = OSDGUI_CmdUp();
    
    if (iRes != 0)
        FSGUI_OperationInit();
	
	return iRes;
}

UINT32 FSGUI_OsdCmdDown()
{
	UINT32 iRes = 0;
	
	iRes = OSDGUI_CmdDown();
	
	if (iRes != 0)
        FSGUI_OperationInit();

    return iRes;
}

UINT32 FSGUI_OsdCmdLeft()
{
	UINT32 iRes = 0;
	
	iRes = OSDGUI_CmdLeft();
	
	if (iRes != 0)
	{	
		//set first_mp3_entry and last_mp3_entry
	    //to find the track postion correctly
		if (pFsJpeg->gifsState == FS_STATE_LIST)//preloop state.   
		    CalcDirFirstPage(pFsJpeg->fsnav_dir_now);
	    
	    FSGUI_OperationInit();
    }
		
    return iRes;
}


UINT32 FSGUI_OsdCmdRight()
{
	UINT32 iRes = 0;
	//printf("---------- FSGUI RIGHT----\n");
	iRes = OSDGUI_CmdRight();
	
	if (iRes != 0)
	{
	    //set first_mp3_entry and last_mp3_entry
	    //to find the track postion correctly
        if (pFsJpeg->gifsState == FS_STATE_LIST)//preloop state.   
            CalcDirFirstPage(pFsJpeg->fsnav_dir_now);
    
        FSGUI_OperationInit();
    }
    return iRes;
}

/*
 * Description:
 *    find root dir.
 */
UINT16 FSGUI_GetRootDir(void)
{
    int 	i = 0;
	UINT16   root_dir = 0;
	
    //get the root dir.
	for(i = 0; i < pFsJpeg->iso9660_dir_cnt; i++)
	{
		if(iso9660_dir[i].parent_dir == -1) 
		{	
			root_dir  = i;
			//printf("### root-dir == %d",root_dir);
			break;
		}
	}    
	return root_dir;
}


/*
 * Function Description:
 *
 *    refresh selection GUI(on the right ) when enter"SELECT"
 *
 * INPUT:
 *  file_index : selected file real index.
 *
 *    type --->  FS_FUNC_MP3
 *               FS_FUNC_JPEG
 *                      Other
 *
 */
void FSGUI_ShowCurrentSelection(UINT16 file_index)
{
	const char * str = "";
	BYTE filename[50];
	BYTE dirname[100]; 
    //UINT16 file_now;//file in a page
    UINT16 file_total_now;//total file in array
    UINT16 dir_total_now;//total dir in array
    BYTE type = 0;
    
    //printf("#### Show current selection ---\n");
    //file_now = pFsJpeg->file_current_in_page;
    //file_total_now = pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry;//pFsJpeg->file_array_in_page[file_now];
    file_total_now = file_index;
    dir_total_now = iso9660_file[file_total_now].parent_dir;
	type = iso9660_file[file_total_now].type;
	 //Draw line
	osd_DrawRegionLine(FS_SUB_TXT_XSTART, FS_SUB_TXT_YSTART+26, FS_SUB_TXT_XSTART+300, FS_SUB_TXT_YSTART+26, FS_SUB_LINE_COLOR, 2,0);
	osd_DrawRegionLine(FS_SUB_TXT_XSTART, FS_SUB_TXT_YSTART+126, FS_SUB_TXT_XSTART+300, FS_SUB_TXT_YSTART+126, FS_SUB_LINE_COLOR, 2,0);
	osd_DrawRegionLine(FS_SUB_TXT_XSTART, FS_SUB_TXT_YSTART+226, FS_SUB_TXT_XSTART+300, FS_SUB_TXT_YSTART+226, FS_SUB_LINE_COLOR, 2,0);
	
	//Draw pic
	osd_draw_bmp_old(FS_SUB_TXT_XSTART ,FS_SUB_TXT_YSTART+42, song1_bmp, 0);//draw song
	osd_draw_bmp_old(FS_SUB_TXT_XSTART,FS_SUB_TXT_YSTART+142, picture1_bmp, 0);//draw picture

	 //Draw string
	 //"Current Selection"
	 str = _OsdMessegeFont1[osd_font_mode][STR_OS_FSGUI_SELECTION_MSG0];
	 osd_DrawRegionString(FS_SUB_TXT_XSTART, FS_SUB_TXT_YSTART, str, FS_SUB_TXT_FONT_COLOR, FS_SUB_TXT_BACKGROUND_COLOR,0);

	if (type == FS_FUNC_MP3)
	{
		//if (GetCurrentFileType() ==CDROM_MP3)
		//{
        //show folder name
        ClearString(FS_SUB_TXT_XSTART+38, FS_SUB_TXT_YSTART+50,16*16,FS_SUB_TXT_BACKGROUND_COLOR);
        //strcpy(dirname,iso9660_dir[dir_total_now].name);
        FSGUI_GetPathName(dirname, dir_total_now);
        osd_DrawRegionString(FS_SUB_TXT_XSTART+38, FS_SUB_TXT_YSTART+50, dirname, FS_SUB_TXT_FONT_COLOR, FS_SUB_TXT_BACKGROUND_COLOR,0);
        
		//show track name
        ClearString(FS_SUB_TXT_XSTART, FS_SUB_TXT_YSTART+94,18*16,FS_SUB_TXT_BACKGROUND_COLOR);
		strcpy(filename,iso9660_file[file_total_now].name);
		osd_DrawRegionString(FS_SUB_TXT_XSTART+38, FS_SUB_TXT_YSTART+94, filename, FS_SUB_TXT_FONT_COLOR, FS_SUB_TXT_BACKGROUND_COLOR,0);

        //show mp3 bmp
        if (GetCurrentFileType() == CDROM_WMA)
		    osd_draw_bmp_old(FS_SUB_TXT_XSTART,FS_SUB_TXT_YSTART+85, wma_bmp, 0);//draw mp3
        else 
            osd_draw_bmp_old(FS_SUB_TXT_XSTART,FS_SUB_TXT_YSTART+85, mp3_bmp, 0);//draw mp3

        if ((selected_flag & (0x01<< type)) == 0 )
	        selected_flag = selected_flag |(0x01 << type);
		//}
		
		/*if (GetCurrentFileType() ==CDROM_WMA)
		{
                    //show folder name
                        strcpy(dirname,iso9660_dir[dir_total_now].name);
                        osd_DrawRegionString(FS_SUB_TXT_XSTART+38, FS_SUB_TXT_YSTART+50, dirname, FS_SUB_TXT_FONT_COLOR, FS_SUB_TXT_BACKGROUND_COLOR,0);
        
		        //show track name
			strcpy(filename,iso9660_file[file_total_now].name);
			osd_DrawRegionString(FS_SUB_TXT_XSTART+38, FS_SUB_TXT_YSTART+90, filename, FS_SUB_TXT_FONT_COLOR, FS_SUB_TXT_BACKGROUND_COLOR,0);

                        //show wma bmp
			osd_draw_bmp_old(FS_SUB_TXT_XSTART,FS_SUB_TXT_YSTART+82, wma_bmp, 0);//draw wma

		}*/
	}
    else if (type== FS_FUNC_JPEG)
	{
        //show folder name
        ClearString(FS_SUB_TXT_XSTART+38, FS_SUB_TXT_YSTART+150,16*16,FS_SUB_TXT_BACKGROUND_COLOR);
        //strcpy(dirname,iso9660_dir[dir_total_now].name);
        FSGUI_GetPathName(dirname, dir_total_now);
        osd_DrawRegionString(FS_SUB_TXT_XSTART+38, FS_SUB_TXT_YSTART+150, dirname, FS_SUB_TXT_FONT_COLOR, FS_SUB_TXT_BACKGROUND_COLOR,0);
                
        //show track name
        ClearString(FS_SUB_TXT_XSTART+38, FS_SUB_TXT_YSTART+194,16*16,FS_SUB_TXT_BACKGROUND_COLOR);
        strcpy(filename,iso9660_file[file_total_now].name);
        osd_DrawRegionString(FS_SUB_TXT_XSTART+38, FS_SUB_TXT_YSTART+194, filename, FS_SUB_TXT_FONT_COLOR, FS_SUB_TXT_BACKGROUND_COLOR,0);
	 
	    if ((selected_flag & (0x01<< type)) == 0 )
	    {    
	        selected_flag = selected_flag |(0x01 << type);
	        printf("##### ------selected changed --%d\n",selected_flag);
	    }   
	 }
	 //else if( (type!= FS_FUNC_JPEG)&&(type!= FS_FUNC_MP3) )
	 str = _OsdMessegeFont1[osd_font_mode][STR_OS_FSGUI_NO_SEL_MSG0];
    if (selected_flag == 0)
	{
	    //draw string "Not Selected" for MP3 and JPEG
	 	osd_DrawRegionString(FS_SUB_TXT_XSTART+38, FS_SUB_TXT_YSTART+50, str, FS_SUB_TXT_FONT_COLOR, FS_SUB_TXT_BACKGROUND_COLOR,0);
	 	osd_DrawRegionString(FS_SUB_TXT_XSTART+38, FS_SUB_TXT_YSTART+150, str, FS_SUB_TXT_FONT_COLOR, FS_SUB_TXT_BACKGROUND_COLOR,0);
	}
	else 
	{
	    if (selected_flag == (0x01 << FS_FUNC_MP3))//only MP3 selected,JPEG has no selection
	        osd_DrawRegionString(FS_SUB_TXT_XSTART+38, FS_SUB_TXT_YSTART+150, str, FS_SUB_TXT_FONT_COLOR, FS_SUB_TXT_BACKGROUND_COLOR,0);
	    else if (selected_flag == (0x01 << FS_FUNC_JPEG))
	        osd_DrawRegionString(FS_SUB_TXT_XSTART+38, FS_SUB_TXT_YSTART+50, str, FS_SUB_TXT_FONT_COLOR, FS_SUB_TXT_BACKGROUND_COLOR,0);
	}
}


/*  
 * Funciton: FSGUI_GetOneDirContent() 
 *
 * Description:
 *   1)save the index of subdirs and files to CurrentFiles[]
 *   2)Get the total count : pFsJpeg->file_count_in_dir
 */
void FSGUI_GetOneDirContent(int iDir)
{
	int i = 0,j = 0;
	int iStart = 0, iEnd = 0;
	//NOTE:
	//When we read a dir, must record its subdir and files.
	//we save them in CurrentFiles[]
	
	//find its subdir
	for(i = 0; i < pFsJpeg->iso9660_dir_cnt;i++)
	{
		if((iso9660_dir[i].parent_dir == iDir) 
			&& (i != iDir))//parent dir of i can not be iDir.
		{	
			// record the index of subdir and files.
			//in order to distinguish dir and files, 
			//dir index  = index+ 400
			//file index = index;
			CurrentFiles[j] = i + SUB_FOLDER_BASE;
			j++;	
		}
	}	
	//printf("###### iDir %d -has files---%d---\n",iDir,iso9660_dir[iDir].dir);
	if(iso9660_dir[iDir].dir>0)
	{
		iStart = pFsJpeg->Dir_entry[iDir];
		iEnd = iStart + iso9660_dir[iDir].dir;
		//find its file.
		for(i = iStart; i < iEnd;i++)
		{
			//if(iso9660_file[i].parent_dir == iDir)
			if(iso9660_file[i].parent_dir == iDir)
			{	
				CurrentFiles[j]= i;
				j++;
			}
		}	
	}
	
	pFsJpeg->file_count_in_dir = j;//total file count.
 	//printf("#### pFsJpeg->file_count_in_dir---%d--\n",pFsJpeg->file_count_in_dir);
	//for( i = 0; i < j; i++)
 	   // printf("#### ---- CurrentFile[%d] :%d---\n",i,CurrentFiles[i]);	
	
	
}


/*
 * Description:
 *      Calculate location of the first file in Dir -> fsnav_trk_now
 *                                      and first_mp3_entry, last_mp3_entry, 
 *
 */
void CalcDirFirstPage(UINT16 iDir)
{
    pFsJpeg->fsnav_trk_now = 0;
    pFsJpeg->first_mp3_entry = pFsJpeg->Dir_entry[iDir];
        
    if (iDir < (pFsJpeg->iso9660_dir_cnt - 1))
        pFsJpeg->last_mp3_entry = pFsJpeg->first_mp3_entry + iso9660_dir[iDir].dir-1;
    else    
        pFsJpeg->last_mp3_entry = pFsJpeg->iso9660_file_cnt - 1;
    
    //printf("------ Excute CalcDirfirstPage : dir :%dfirst_mp3_entry:%d, last_mp3_entry:%d----\n",iDir,pFsJpeg->first_mp3_entry,pFsJpeg->last_mp3_entry);
	

}

/*
 * Description:
 *   Get path name (start from root dir) to show curent selection
 *
 */
void FSGUI_GetPathName(BYTE pathname[], UINT16 iDir)
{
    UINT16 root_dir = FSGUI_GetRootDir();
    UINT16 parent_dir = 0;
    UINT16 sub_dir = iDir;
    UINT16 i = 0;
    BYTE templen = 0, pathlen = 0;
    
    if (iDir == root_dir)    
        psprintf(pathname, "\\");//only show '\'
    else
    {
        psprintf(pathname, "%s\\", iso9660_dir[sub_dir].name);
        
        do
        {
            parent_dir = OSDGUI_GetParentDir(sub_dir, DIR);
            
            if (parent_dir == root_dir)
                psprintf(linebuf, "\\");
            else
                psprintf(linebuf, "%s\\", iso9660_dir[parent_dir].name);       
            
            templen = strlen(linebuf);
            pathlen = strlen(pathname);
            
            for (i = 0; i < pathlen; i++)
            {
                
                if ((templen + i) >= 44)//not exceed array range.
                    break;
                    
                linebuf[templen+i] = pathname[i];
            }
            //tempname[templen + pathlen] = ' ';
            linebuf[templen + pathlen] = '\0';
            
            strcpy(pathname, linebuf);
            sub_dir = parent_dir;
            
        }while(parent_dir != root_dir);
        
        
   }
    
}


/*
 * Description:
 *  Show operation msg for fsGUI
 *
 */
void FSGUI_ShowOperationMsg(void)
{
    int file_index = 0;
    UINT16 osd_id = 0;
    
    if (full_scrn)
        return;
    file_index = CurrentFiles[pFsJpeg->file_index_in_dir];
    
    if (file_index >=  SUB_FOLDER_BASE)//folder
    {   
        if (selected_flag == BUTTON_SELECTED)
            osd_id = STR_OS_FS_FOLDER_HAS_SEL;
        else
            osd_id = STR_OS_FS_FOLDER_NONE_SEL;
         
    }   
    else
    {
        if (selected_flag == BUTTON_SELECTED)
            osd_id = STR_OS_FS_FILE_HAS_SEL;
        else
            osd_id = STR_OS_FS_FILE_NONE_SEL;
        
    }
    
    ShowOperationMsg( osd_id, 1);
}

/*
 * Description:
 *   Confirm cd_type again to get cd_type_loaded value.
 *
 * RETURN:   
 *                 cd_type_loaded:
 *  if only has MP3 , CDMUSIC
 *     only has JPEG, CDPICTRUE
 *     MP3 & JPEG,    CDPICMUS
 *
 */
BYTE GetCDROMDiscType(void)
{
    BYTE DiscType;//terry,2005/4/1 12:00¤U¤È
    int MP3files = pFsJpeg->count_file[FS_FUNC_MP3 - FS_FUNC_MP3];
    int JPEGfiles = pFsJpeg->count_file[FS_FUNC_JPEG - FS_FUNC_MP3];
    
    if ((MP3files != 0) && (JPEGfiles == 0))
        DiscType = CDMUSIC;
    else if ((MP3files == 0) && (JPEGfiles != 0))
        DiscType = CDPICTRUE;
    else
        DiscType = CDPICMUS;
    
    return DiscType;
}

#ifdef SURRORT_MP3_PREPLAY
/*
 * Description:
 *  Get MP3 file index which has HL in it.
 *  for MP3 preplay
 *  
 * RETURN:
 *   iRes : ---> -1     current HL is not MP3 file
 *                >= 0   file index.  current HL is MP3 file
 *
 */
INT16 FSGUI_GetHLMp3File(void)
{
    INT16 iRes = 0;
    UINT16 track_index = 0;
    
    track_index = CurrentFiles[pFsJpeg->file_index_in_dir];
    
    if(track_index < SUB_FOLDER_BASE)//HL now in file
    {
        if(iso9660_file[track_index].type == FS_FUNC_MP3)
        {    
            pFsJpeg->fsnav_trk_now = track_index - pFsJpeg->first_mp3_entry;
            iRes = track_index;   
        }
    }
    else 
        iRes = -1; //current HL is not MP3 file
    
    return iRes;
}  
#endif //SURRORT_MP3_PREPLAY

#endif//ifdef OP_UI


