/**************************************************************
** FILE
** prog_advanced.c
**
** DESCRIPTION
**  prog play for MP3/CD/DVD
**  1)build a more beautiful GUI  for PROGRAM
**  2)opration mode like PC
** 
**  NOTE:
**     prog[0][0]
**     prog[0][1] is not use.
**     the same as primary file(prog_unmp3dir.c / prog_mp3dir.c)
**     
**   Creator:  zhaoyanhua
** 	 Date:     2004-4-9 9:00
****************************************************************/

#ifdef OP_UI
#include "fsGUI_osd_func.h"
#include "fsGUI_osd_def.h"
#include "menu_def.h"
#include "menu_page.h"
#include "fsNAV.h"
#include "fs96602.h"
#include "osdGUI_def.h"
#include "osdGUI_func.h"
//extern functions and variables
extern int	menu_page;
extern int	menu_level;
extern int HL_menu;
extern BYTE index_y1;
extern UINT16 dir_set_top;
extern void ShowMenuPage(UINT8 page, UINT8 level, UINT8 HL_y);
extern void osd_draw_root_button(UINT32 xStart, UINT32 yStart, UINT32 xLen, UINT32 yLen,BYTE color,BYTE flag);

//GUI position unit:pixels
#define PROG_GUI_XSTART     (MENU_XSTART+MENU_BTN_XLEN)*16+4
#define PROG_GUI_YSTART     (MENU_YSTART-1)*BUTTON_Y_DIFF
#define PROG_GUI_YLEN       8*BUTTON_Y_DIFF//5 button lenth
#define PROG_GUI_XLEN       22*16
#define ITEM0_XSTART        MENU_XSTART+MENU_BTN_XLEN+2
#define ITEM0_YSTART        MENU_YSTART
#define ITEM_Y_DIFF         BUTTON_Y_DIFF
#define ITEM_X_DIFF         10
//for button"Done" unit: pixels
#define DONEBTN_XSTART      (ITEM0_XSTART+ITEM_X_DIFF/2)*16   
#define DONEBTN_YSTART      (ITEM0_YSTART+5)*ITEM_Y_DIFF
#define DONEBTN_XLEN        (ITEM_X_DIFF/2)*16

//for cdda "All tracks "item
#define CD_ALL_TRACKS   0
/*
 * Descirption:
 *
 *   because its mode looks like fsGUI,so use some funcitons of FSGUI
 */
void prog_init(void)
{
    int i = 0;
    
    full_scrn = PROGRAM;
    OSDGUI_Init();
    OSDGUI_ShowDirInitPara();
    
    if (cd_type_loaded == CDROM)
    {
#ifdef SURRORT_MP3_PREPLAY
        FS_ClearPreplayFlag();
#endif//#ifdef SURRORT_MP3_PREPLAY    
    }
    //NOTE:
    // I use index_x to show HL
    // index_x = 0,            HL in items
    // index_x = SHOW_PROG_NO*2, HL in "DONE" BUTTON
    index_x = 0;//now HL in items
               
    if(prog_cnt == 0)
    {     
        for (i = 0; i <= SHOW_PROG_NO; i++)
        {    
            prog[i][0] = 0;
            prog[i][1] = 0;
        }          
    }
}

void ShowProgPage(void)
{
    UINT16 current_dir = 0;
    
    //printf("###### ------SHow PROGPAGE---\n");
    current_dir = FSGUI_GetRootDir();  
    if ((cd_type_loaded == CDROM) )//only mp3
    {
        pFsJpeg->fsnav_dir_now = current_dir;
    }
    else if(cd_type_loaded == CDDVD)
    {
        dvd_title = 0; 
    }    
    OSDGUI_ShowOneDirContent(current_dir);       
    
    
    if(prog_cnt >10)
        prog_ShowOnePage(11,20);
    else
        prog_ShowOnePage(1,10);
    
    ShowOperationMsg(STR_OS_PROG_UI_MSG1, 1);
}

/*
 * Function : prog_func_clear()
 *
 * Descirption:
 *  clear item from the last item
 *
 */
void prog_func_clear(void)
{
    if(prog_cnt <= 0 )
        return; 
    
    if(prog_cnt == 10)
        prog_ShowOnePage(1, 10); 
        
   
    //index_x is  the index of item
    //prog[index_x][0]: folder
    //prog[index_x][1]: file
    prog[prog_cnt][0] = 0;
    prog[prog_cnt][1] = 0;
    ShowProgItemSel(prog_cnt, 0);
   // printf("### ---CLeAR index:%d--\n",prog_cnt);
    prog_cnt--;
       
}

void prog_func_down(void)
{
    if(index_x == SHOW_PROG_NO*2)//HL in DOWN
        return;
        
    if (cd_type_loaded == CDROM)
        FSGUI_OsdCmdDown();
    else
        OSDGUI_CmdDown();
}


void prog_func_left(void)
{
    if(index_x == SHOW_PROG_NO*2)//HL in DOWN
    {
        index_x = 0;
        SetOsdCol(0, 0, BTN_SELECTED_COLOR, 0xa40050ff); //restore the color
        prog_draw_done_button(BUTTON_UNSELECTED);
    }  
    else
    {
        if (cd_type_loaded == CDROM)
            FSGUI_OsdCmdLeft();
        else
            OSDGUI_CmdLeft();    
    }    
}

void prog_func_right(void)
{
    BYTE button_type = 0;
    UINT16 index = 0;
    
    button_type = OSDGUI_GetSelButtonType(pFsJpeg->file_current_in_page);
    index = pFsJpeg->file_array_in_page[pFsJpeg->file_current_in_page];
    
    if(   (button_type == SUB_BUTTON)//file in subdir 
       || ((button_type == BLANK_BUTTON) && (index != END_FILE)))//file in root_dir
    {//only when HL in file, can select DONE
        
        if (prog_cnt)
        {
            index_x = SHOW_PROG_NO*2;//only a flag show current HL in button"Done"
            //draw "done" button
            SetOsdCol(0, 0, BTN_SELECTED_COLOR, 0x831b24ff); 
            prog_draw_done_button(BUTTON_SELECTED);
        }
    }   
    else
    {
        if (cd_type_loaded == CDROM)
            FSGUI_OsdCmdRight();
        else
            OSDGUI_CmdRight();
        
    }    
}

void prog_func_up(void)
{
    if(index_x == SHOW_PROG_NO*2)//HL in DOWN
        return;
    
    if (cd_type_loaded == CDROM)
        FSGUI_OsdCmdUp();
    else
        OSDGUI_CmdUp();
}


void prog_func_select(void)
{
    //printf("##### ---select prog_cnt:%d--\n",prog_cnt);
    //HL in DONE button
    if((index_x == SHOW_PROG_NO*2))
    {    
        prog_func_off(); 
        return;
    }
    
    if(prog_cnt >= 20)
        return;
    
    if ((cd_type_loaded == CDDVD) && (dvd_title == 0))
    {//if HL item is title, open this title.
        prog_func_right();        
        return;
    }
    
    
    if(prog_cnt == 10)
        prog_ShowOnePage(11,20);
            
    prog_cnt++;
    
    
    //index_x is  the index of item
    //prog[index_x][0]: parent dir
    //prog[index_x][1]: file
    prog[prog_cnt][0] = OSDGUI_GetCurrentDir();
    //"+1": if not "+1", when we record the file:0, 
    //                   can not read it correctly.
    prog[prog_cnt][1] = pFsJpeg->file_array_in_page[ pFsJpeg->file_current_in_page ] + 1;
    
    ShowProgItemSel(prog_cnt, 1);
    //printf("### ---SELECT index:%d--\n",prog_cnt);
}

void prog_func_off()
{
    
    index_x = 0;
    AVD_ResetMediaStatus();
    osd_init_mainmenu();
    printf("#### prog_func_off--prog_cnt:%d------\n",prog_cnt);
	if (full_scrn & SETUP)
	{    
	    menu_level = 1;
	    menu_page = PLAYMODEPAGE;
	    HL_menu = SUB_MENU;
	    index_y1 = PROGRAMITEM;
	    //printf("#### heheheheheheh ----SHOWMENUPAGE");
	    ShowMenuPage(PLAYMODEPAGE, menu_level-1, PROGRAMITEM);
    }
    else
    {
        full_scrn = 0;
        prog_index = 1;
        
        if (!prog_cnt)
        {    
            ircmd_play();
            return;
        }
        
        if(cd_type_loaded == CDROM)
        {       
            FSGUI_Return2Menu();
            //pFsJpeg->gifsState = FS_STATE_MP3;
            //pFsJpeg->fsnav_dir_now = prog[prog_index][0]; 
            play_state = VCD_STATE_MP3_FILELIST;
                
            //only for test
            int i = 0;
            for(i = 0; i<= prog_cnt; i++) 
            {
                printf("prog_item[%d][0]:%d--\n",i, prog[i][0]);    
                printf("prog_item[%d][1]:%d--\n",i, prog[i][1]);    
            }
            ircmd_post_func(CMD_FUNC | CMD_FUNC_PRG); 
            printf("Before exit pFsJpeg->fsnav_dir_now-%d-222,prog_index:%d,pFsJpeg->gifsFuncBtn :%d\n",pFsJpeg->fsnav_dir_now,prog_index,pFsJpeg->gifsFuncBtn );  
            
        }
        else if (cd_type_loaded == CDDVD)
        {
            dvd_title = 0;
            if (prog_cnt)
                ircmd_post_func(CMD_FUNC|CMD_FUNC_PRG);
            
             
        }
        else if (cd_type_loaded == CDDA)
        {
            //because in v11.c use prog[prog_index][0]record prog item
            //while I use prog[prog_index][1],so must copy prog[prog_index][1] --> prog[prog_index][0]
            //zhaoyanhua 2004-5-25 10:29
            if (prog_cnt)
            {    
                int i = 0;
            
                for (i = 1; i <= prog_cnt; i++)
                    prog[i][0] = prog[i][1] - 1;//because in select(), prog[prog_cnt][1] = pFsJpeg->file_array_in_page[ pFsJpeg->file_current_in_page ] + 1;
                
                cd_trk_now = 1;
                ircmd_post_func(CMD_FUNC|CMD_FUNC_PRG);
            }
            
            
        }
    }
}

/*
 * Function name: prog_ShowOnePage()
 *    
 * Description:
 *    Show one page for prog GUI 
 * 
 * INPUT:
 *  itemStart itemEnd
 *   1      ~  10      first page 
 *  11      ~  20     second page
 *
 */
void prog_ShowOnePage(int itemStart, int itemEnd)
{
    int i = 0;
    
    //draw the prog GUI 
    osd_draw_rect(PROG_GUI_XSTART, PROG_GUI_YSTART, PROG_GUI_XLEN, PROG_GUI_YLEN, GRAY);
    //draw items
    for ( i = itemStart; i <= itemEnd; i++)
        ShowProgItemSel(i, 0);
    //draw "DONE" button    
    prog_draw_done_button(BUTTON_UNSELECTED);
}

/*
 * Description:
 *    show string of prog selecition
 *
 *  INPUT:
 *   mode -->  0     read inital value in prog[][].     
 *                   if haved items in prog[][], show its string in GUI
 *                   else  show "--"
 ¡Á             1     for new seleciton. show its string in GUI 
 *
 *   sel_item -->  selected item
 */

void ShowProgItemSel(BYTE sel_item, UINT8 mode)
{
 
    BYTE str[35];
    BYTE temp_str[30];
    BYTE itemstr_xstart = 0;//unit: words
    BYTE itemstr_ystart = 0;//unit: words
    UINT16 file_index = 0;
    
    if(sel_item < 1)
        return;
    printf("### sel :%d, prog:%d---\n",sel_item, prog[(sel_item)][1]);
    if(mode == 0)
    {   
        if((prog[(sel_item)][1] == 0) )
           psprintf(temp_str, "--");
            //psprintf(str,"%d: %s",sel_item,"--");
        else//get saved items in prog[][]
        {
            file_index = prog[(sel_item)][1]-1;
            
            prog_GetSelItemStr(temp_str, file_index);
        }
    }
    else//mode = 1, get string of current selection.
    {    
        file_index = pFsJpeg->file_array_in_page[pFsJpeg->file_current_in_page];
      
        prog_GetSelItemStr(temp_str, file_index);
        
    }  
    psprintf(str,"%d: %s",sel_item, temp_str);
     
     //format is :
     //1--                2--
     //3--                4--
     //5--                6--ate == BUTTON_SELECTED)
    
     //7--                8--
     //9--                10--
     if(sel_item > 10)
        sel_item = sel_item - ((sel_item-1)/10)*10;//1~10
        
     itemstr_xstart = ITEM0_XSTART+((sel_item-1)%2)*ITEM_X_DIFF;
     itemstr_ystart = ITEM0_YSTART +(sel_item-1)/2;
     ClearString(itemstr_xstart*16, itemstr_ystart*ITEM_Y_DIFF,
                9*16+12,GRAY);
     osd_DrawRegionString(itemstr_xstart*16, itemstr_ystart*ITEM_Y_DIFF, str, WHITE, GRAY,0);      
}

void prog_draw_done_button(BYTE button_state)
{
    int bgColor = 0;
    
    if(button_state == BUTTON_SELECTED) 
        bgColor =  BTN_SELECTED_COLOR;
    else
        bgColor = BLACK;
  
    //draw "DONE" button
    osd_draw_rect(DONEBTN_XSTART, DONEBTN_YSTART, DONEBTN_XLEN, BUTTON_Y_DIFF, BLACK);//draw a black rect
    osd_draw_root_button(DONEBTN_XSTART+2, DONEBTN_YSTART+2,
                        DONEBTN_XLEN-4, BUTTON_Y_DIFF-4,
                        bgColor, BUTTON_SELECTED);
   
   // osd_DrawRegionString(button_xstart+2, button_ystart+15, "Done", WHITE, BLACK,0);    
    osd_DrawRegionString(DONEBTN_XSTART+16, DONEBTN_YSTART+14, "Done", WHITE, bgColor,0);      
}

/*
 * Description:
 *   Get the string of given file_index to show in PROGRAM GUI
 *
 * INPUT:
 *   file_index ---> NOTE: it may be FILE or DIR
 *
 * OUPUT:
 *   str
 */
void prog_GetSelItemStr(BYTE str[], int file_index)
{
    if(file_index == END_FILE)//file_index is invalid
        str = "";
    else 
    {
        if (file_index >= SUB_FOLDER_BASE)
            OSDGUI_GetDirName(str, file_index - SUB_FOLDER_BASE);
        else
        {
            if (cd_type_loaded == CDDVD)
                psprintf(str, "Title%d C%d", OSDGUI_GetParentDir(file_index,FILE), (file_index+1));
            else
                OSDGUI_GetFileName(str, file_index);    
        }
    }
}
/*
 * Description:
 *    when prog mode, "PREV" will excute the following funcrion
 *
 */
BYTE prog_func_prev(UINT16 index)
{
    UINT16 iSel = 0;
    BYTE    file_type = 0;
    BYTE  flag = FALSE;
    
    iSel = prog[index][1] - 1; //get real file index.
    if (cd_type_loaded == CDDA)
    {
        if (iSel == CD_ALL_TRACKS)//item"ALL tracks"
            file_type = FOLDER_TYPE;
        else
            file_type = FILE_TYPE;
    }
    else
    {    
    if (iSel >= SUB_FOLDER_BASE)//current prog item is folder    
    {    
        iSel = iSel - SUB_FOLDER_BASE;//get real dir index in iso9660_dir
        file_type = FOLDER_TYPE;
    }
    else 
        file_type = FILE_TYPE;
    }
    
    if (file_type == FOLDER_TYPE)
    {
        if (cd_type_loaded == CDROM)
        {
            UINT16  CurDir = dir_set[dir_set_top];
        
            if (FSGUI_IsFolderEnd(CurDir, PAGE_UP) == FALSE)     
                pFsJpeg->fsnav_trk_now--; 
            else
            {//according to the OP sample,
             //if prog mode, prev in the folder end will appear invalid.
                #if 0
                if (dir_set_top > 0)
                    dir_set_top--;
                CurDir = dir_set[dir_set_top];
                
                if ((CurDir == (iSel-1))//prev dir is same level as iSel.
                    || (CurDir < iSel)//iSel has no same level again. prev dir'level less than iSel.
                    )
                { //current prog item(Folder,including all subfolders and files) has been played out.        
                    prog_index--;//get prev prog item
                    flag = TRUE;
                }
                else
                {
                    pFsJpeg->fsnav_dir_now = CurDir;//get real dir index in iso9660_dir
                    CalcDirFirstPage(pFsJpeg->fsnav_dir_now);
                }
                #endif
            }
            FSGUI_ShowCurrentSelection((pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry)); 
        }
        else if (cd_type_loaded == CDDA)
        {
            if (cd_trk_now <= cd_trk_lo)
            {
                prog_index--;
                flag = TRUE;    
            }
            else
                cd_trk_now--;    
        }
          
        printf("Prev--   FOLDER ----flag :%d,prog_index :%d--pFsJpeg->fsnav_trk_now:%d,pFsJpeg->fsnav_dir_now:%d\n",flag,prog_index,pFsJpeg->fsnav_trk_now,pFsJpeg->fsnav_dir_now);
    }
    else//file 
    {    
        prog_index--;          
        flag = TRUE;
        printf("Prev --- FILE ----flag :%d,prog_index :%d--\n",flag, prog_index); 
    }                
    
    if ((cd_type_loaded == CDDA) && (flag == TRUE))
        cd_trk_now = 1;//when play prev prog_index, reset its value;
    
    if (adv_search_time < 0)
        adv_search_time = 0;
	
	if (prog_index < 1)
	{    
	    prog_index = prog_cnt;
	    flag = TRUE;
	}
	
	
	    
	return flag;			
}

/*
 * Description:
 *    when prog mode, "NEXT" will excute the following funcrion
 *
 */
BYTE prog_func_next(UINT16 index)
{
    UINT16 iSel = 0;
    BYTE    file_type = 0;
    BYTE    flag = FALSE;
    
    iSel = prog[index][1] - 1; //get real file index.
   
    
    if (cd_type_loaded == CDDA)
    {
        if (iSel == CD_ALL_TRACKS)//item"ALL tracks"
            file_type = FOLDER_TYPE;
        else
            file_type = FILE_TYPE;
    }    
    else
    {    
        if (iSel >= SUB_FOLDER_BASE)//current prog item is folder    
        {    
            iSel = iSel - SUB_FOLDER_BASE;//get real dir index in iso9660_dir
            file_type = FOLDER_TYPE;
        }
        else 
            file_type = FILE_TYPE;
    }    
    if (file_type == FOLDER_TYPE)
    {
        if (cd_type_loaded == CDROM)
        {
            UINT16  CurDir = 0;
            
            if (FSGUI_IsFolderEnd(pFsJpeg->fsnav_dir_now, PAGE_DOWN) == FALSE)     
                pFsJpeg->fsnav_trk_now++; 
            else
            {
                if (dir_set_top < (pFsJpeg->iso9660_dir_cnt-1))
                {    
                    dir_set_top++;
                    //if((iso9660_dir[dir_set[dir_set_top]].type) & (0x01 << pFsJpeg->gifsFuncBtn))
                     //   break;
                }
                CurDir = dir_set[dir_set_top];
                
                if ((CurDir == (iSel+1))//next dir is same level as iSel.
                    || (CurDir < iSel)//iSel has no same level again. next dir'level less than iSel.
                    ) 
                {//current prog item(Folder,including all subfolders and files) has been played out.     
                    prog_index++;//get next prog item
                    flag = TRUE;
                }
                else
                {
                    pFsJpeg->fsnav_dir_now = CurDir;//get real dir index in iso9660_dir
                    CalcDirFirstPage(pFsJpeg->fsnav_dir_now);
                }
                
            }  
            FSGUI_ShowCurrentSelection((pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry));   
        }
        else if (cd_type_loaded == CDDA)
        {
            if (cd_trk_now >= cd_trk_hi)
            {
                prog_index++;
                flag = TRUE;    
            }
            else
                cd_trk_now++;    
            
        }    
        
        printf("NExt --- FOLDER  iSel:%d---dir_set_top:%d, dir_set[dir_set_top]:%d---\n",iSel,dir_set_top, dir_set[dir_set_top]);
        printf("Next--   FOLDER ----flag :%d,prog_index :%d--pFsJpeg->fsnav_trk_now:%d,pFsJpeg->fsnav_dir_now:%d\n",flag,prog_index,pFsJpeg->fsnav_trk_now,pFsJpeg->fsnav_dir_now);
    }
    else//file 
    {    
        prog_index++;          
        flag = TRUE;
        
        printf("Next --- FILE ----flag :%d,prog_index :%d--\n",flag, prog_index); 
    }
    if ((cd_type_loaded == CDDA) && (flag == TRUE))
        cd_trk_now = 1;//when play next prog_index, reset its value;
    
    if (adv_search_time < 0)
        adv_search_time = 0;
	
	if (prog_index > prog_cnt)
	{    
	    prog_index = 1;
        flag = TRUE;
    } 
	
	printf("Next flag :%d--prog_index:%d\n",flag, prog_index);
    
    return flag;
}


int is_clear_pos(void)//2002-4-19 1:53
{}

void prog_func_play(void)
{}

void prog_func_input(UINT8 num)
{}
#endif//end ifdef OP_UI
