/*
**	freyman delete this file from Makefile 2004-3-23 15:07
*/

#include "user_init.h"

#ifdef SVA_SAMPLE

#include "global.h"
#include "osd.h"
#include "func.h"
#include "ircmd.h"
#include "memmap.h"
#include "dsp3_if.h"
#include "cchar.h"

#define LFront      0
#define RFront      1
#define LSurround   2
#define RSurround   3
#define CCenter     4
#define SWoofer     5

#define TOPLEVEL    16

BYTE amp_enter_flag = 0;

typedef void (*AMPFUNC) ();

extern void osd_init_ampvol(void);
extern void strcat1(char *,char *);
extern void set_lfront(void);
extern void set_rfront(void);
extern void set_lrear(void);
extern void set_rrear(void);
extern void set_center(void);
extern void set_woofer(void);


void ShowAmpvolPage(void);
void ampvol_show_level(int id,INT8 level,BYTE total_level) ;

/*
** WARNING!!!!
** If you want to modify following two lists,
** You must be sure that you have known the meaning of them and how they
** be used in functions,
** OR,
** DON'T MOVE! HANDS BEHIND YOUR HEAR!  

** You must make the three list in the same sequence 

** you can't declar lev_list to const type ,for the levels could be modified.
*/
BYTE * lev_list[6] = 
{
    &lfront_level,&rfront_level,
    &lrear_level,&rrear_level,
    &center_level,&woofer_level, 
};

const AMPFUNC amp_func_table[6] = 
{
    set_lfront,
    set_rfront,
    set_lrear,
    set_rrear,
    set_center,
    set_woofer,
};
const UINT16 id_list[6] = 
{
    STR_OS_LF,
    STR_OS_RF,
    STR_OS_LR,
    STR_OS_RR,
    STR_OS_CC,
    STR_OS_SW
};

void ampvol_func(void)
{
    full_scrn=AMPVOL;
    
    if(amp_enter_flag==0)
    {
        set_volume(80);
        amp_enter_flag++;
    }
    else if(amp_enter_flag==1)
    {
        ampvol_init();
        amp_enter_flag++;
    }
    else if(amp_enter_flag==2)
    {
        ampvol_exit();
        amp_enter_flag = 0;
    }
}
/*
** Function ampvol_init: 
** 1.set index_y to 0 means active line at present;
** 2.init osd for ampvol that is different to others, coordinate and quantity of regions
** 3.show the page on screen
*/
void ampvol_init(void)
{
	index_y = 0;
//    full_scrn=AMPVOL;	
	osd_init_ampvol();
    ShowAmpvolPage();
}
/*
** show six lines that we need, the sequence is 
** according to the list of level
*/
void ShowAmpvolPage(void)
{
	BYTE temp;
	for(temp=0;temp<6;temp++)
		ampvol_show_level(temp,*lev_list[temp],TOPLEVEL);
}
/*
** func_left to responce to the iremote of left button 
** both display and set pt2322 register
*/
void ampvol_func_left(void)
{   
    
    if(amp_enter_flag==1)
    {
        set_volume(0);
        return;
    }
       
    if((*lev_list[index_y])==0)
        return;
    
    (*lev_list[index_y])--;
    ampvol_show_level(index_y,*lev_list[index_y],TOPLEVEL);
    amp_func_table[index_y]();
}
/*
** func_right to responce to the iremote of right button 
** both display and set pt2322 register
*/
void ampvol_func_right(void)
{
    if(amp_enter_flag==1)
    {
        set_volume(1);
        return;
    }

    if((*lev_list[index_y])==15)
        return;
    
    (*lev_list[index_y])++;
    ampvol_show_level(index_y,*lev_list[index_y],TOPLEVEL);
    amp_func_table[index_y]();
}
/*
** func_up to responce to the iremote of up button 
** display the line active present and renew the line before
*/
void ampvol_func_up(void)
{
    if(index_y==0)
        return;
    index_y--;
    ampvol_show_level(index_y+1,*lev_list[index_y+1],TOPLEVEL);
    ampvol_show_level(index_y,*lev_list[index_y],TOPLEVEL);
}
/*
** func_down to responce to the iremote of down button 
** display the line active present and renew the line before
*/
void ampvol_func_down(void)
{
    if(index_y==5)
        return;
    index_y++;
    ampvol_show_level(index_y-1,*lev_list[index_y-1],TOPLEVEL);
    ampvol_show_level(index_y,*lev_list[index_y],TOPLEVEL);    
}
/*
** exit function :
** 1.reset index_y to 0
** 2.init osd to ready for other application
** 
*/
void ampvol_exit(void)
{
    index_y = 0;
    
	osd_disable();

	full_scrn=0;  

	amp_enter_flag = 0;

	osd_init();
}

/*
**
*/
void ampvol_show_level(int id,INT8 level,BYTE total_level) 
{ 
    BYTE i;
    int pos;
    BYTE buf[5];

    linebuf[0] = ' ';
    linebuf[1] = '[';
    pos = 2;

    for(i=pos;i<level+pos;i++) 
		linebuf[i] = N_longbar; //long bar         

    for(i=level+pos;i<total_level-1+pos;i++) 
        linebuf[i] = N_shortbar; //short bar          

    linebuf[total_level-1+pos] = 0;

    psprintf(RegionValStr[id+1],"] %02d",level);
    strcat1(linebuf,RegionValStr[id+1]);
    if(index_y==id)
    {
        strcpy(buf,_OsdMessegeFont1[osd_font_mode][STR_OS_DIR7]);
        strcat1(linebuf,buf);
    }

    strcpy(RegionValStr[id+1], linebuf);
    PrintOsdMsg(id_list[id], (id+1),0,1);
} 



#endif //SVA_SAMPLE
