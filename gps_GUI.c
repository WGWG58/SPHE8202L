#include "user_init.h"
#include "global.h"
#include "memmap0.h"
#include "ircmd.h"
#include "types.h"
#include "memcfg.h"
#include "framebuf.h"
#include "memmap.h"
#include "osd.h"
#include "gps_GUI.h"
#include "fsNAV.h"
#include "avd.h"

#ifdef JPG_OLD_PARSER_FLOW
    #ifdef JPG_EFFECT
    #include "jpegeffect.h"
    #endif
#else
    #include "pic_effect.h"
#endif

#ifdef GPS_KEYBOARD
#define IRC_PREV		0x1d
#define	IRC_PLAY		0x16
#define	IRC_NEXT		0x1e
#define	IRC_STOP		0x19
#define IRC_BACKWARD	0x1b
#define IRC_FORWARD		0x1c
#define IRC_UP			0x29
#define IRC_LEFT		0x2b
#define	IRC_RIGHT		0x2c
#define IRC_DOWN		0x2a
#define IRC_SELECT		0x48
#define IRC_EJECT		0x0c
#define IRC_PAUSEPLAY	0x42
#define	IRC_PAUSE		0x15
#define IRC_PLAY_RESUME	0x17

void osd_init_gps_keyboard(void);
void fm_frequency_tune(BYTE flag);
void save_setting_val(BYTE index);
extern void call_ir_func(BYTE rx);
BYTE	value_chg;
BYTE	last_play_state;
BYTE	last_disc_type;

#define KEYBOARD_BUTTON_WIDTH_STEP  86
#define KEYBOARD_BUTTON_HEIGHT_STEP 50
#define BOARD_REGION  2
#define ACK	1
UINT32 timer_counter;
COM_PACKET packet;
BYTE keyboardtype;//frank.huang 050923 add to be flag of touch keybo



#define KEY_BACKGROUND_COLOR    0   //
#define BUTTON_COLOR_B     		10   //ORANGE
#define BUTTON_COLOR_Y     		11   //BLACK
#define KEY_DISABLE_COLOR       8   //WHITE

#define KEY_REGION         	3

#define KEY_BOARD_L_XSTART	25
#define KEY_BOARD_L_YSTART	195
#define KEY_BOARD_L_XSTEP	85
#define KEY_BOARD_XSTEP_M  97
#define KEY_BOARD_R_XSTART	450
#define KEY_BOARD_R_YSTART	100
#define KEY_BOARD_R_XSTEP	85
#define KEY_BOARD_R_YSTEP	47

#define KEY_BOARD_R_YSTART_M	14
#define KEY_BOARD_R_YSTEP_M		60
#define KEY_BOARD_R_XSTART_M  610



#define	KEYTYPE_CD_DVD_VCD	0
#define	KEYTYPE_CDROM_NORMAL	1
#define	KEYTYPE_CDROM_CHANGE_PAGE	2
#define KEYTYPE_OFF	3

/*const BYTE *const button_icon[] = 
{
	button_up,      //0
	button_down,    //1
	button_left,    //2
	button_right,   //3
	button_enter,   //4
	button_backward,//5
	button_forward, //6
	button_prev,    //7
	button_next,    //8
	button_pause,   //9
	button_stop,    //10
	button_subtitle,//11
	button_audio,   //12
	button_angle,   //13
	button_menu,    //14
	button_title,   //15
	button_ok,      //16
};*/
/*
void osd_draw_button_icon(BYTE row, BYTE col, const BYTE* bmp)
{
    coordinate start;
    
    start.x = col * KEYBOARD_BUTTON_WIDTH_STEP+5;
    start.y = row * KEYBOARD_BUTTON_HEIGHT_STEP+5;
    
    osd_draw_bmp(&start, bmp,  BOARD_REGION);
}
*/

//-----------------------------total col: 7, total row: 4 ------------------------------------
//          col 0       col 1       col 2       col 3       col 4       col 5       col 6
// row 0                up          
// row 1    left        enter       right
// row 2    backward    down        forward     stop        menu        angle
// row 3    prev        play/pause  next        subtitle    audio       title       ok
//--------------------------------------------------------------------------------------------
/*void osd_draw_touch_keyboard(void)
{
    //BYTE row, col;
  
    osd_init_gps_cmdboard();
    osd_draw_button_icon(0, 1, button_up);
    osd_draw_button_icon(1, 0, button_left);
    osd_draw_button_icon(1, 1, button_enter);
    osd_draw_button_icon(1, 2, button_right);
    osd_draw_button_icon(2, 0, button_backward);
    osd_draw_button_icon(2, 1, button_down);
    osd_draw_button_icon(2, 2, button_forward);
    osd_draw_button_icon(2, 3, button_stop);
    osd_draw_button_icon(2, 4, button_menu);
    osd_draw_button_icon(2, 5, button_angle);
    osd_draw_button_icon(3, 0, button_prev);
    osd_draw_button_icon(3, 1, button_pause);
    osd_draw_button_icon(3, 2, button_next);
    osd_draw_button_icon(3, 3, button_subtitle);
    osd_draw_button_icon(3, 4, button_audio);
    osd_draw_button_icon(3, 5, button_title);
    osd_draw_button_icon(3, 6, button_ok);
    
    //frank.huang mark, and use new keyboard ui
//-----------------------------total col: 7, total row: 4 ------------------------------------
//          col 0       col 1       col 2       col 3       col 4       col 5       col 6
// row 0                						up          
// row 1    						left        enter       right
// row 2    			backward    forward		down        menu        angle
// row 3    play/paus	stop		prev        next        subtitle    audio       title      
//--------------------------------------------------------------------------------------------
	osd_init_gps_cmdboard();
    osd_draw_button_icon(0, 3, button_up);
    osd_draw_button_icon(1, 2, button_left);
    osd_draw_button_icon(1, 3, button_enter);
    osd_draw_button_icon(1, 4, button_right);
    osd_draw_button_icon(2, 1, button_backward);
    osd_draw_button_icon(2, 2, button_forward);
    osd_draw_button_icon(2, 3, button_down);
    osd_draw_button_icon(2, 4, button_menu);
    osd_draw_button_icon(2, 5, button_angle);
    osd_draw_button_icon(3, 0, button_pause);
    osd_draw_button_icon(3, 1, button_stop);
    osd_draw_button_icon(3, 2, button_prev);
    osd_draw_button_icon(3, 3, button_next);
    osd_draw_button_icon(3, 4, button_subtitle);
    osd_draw_button_icon(3, 5, button_audio);
    osd_draw_button_icon(3, 6, button_title);
	
    //osd_draw_bmp(&start, button_icon[0],  2);
    osd_tog_region(BOARD_REGION, OSD_ON); 
}
*/

void show_keyboard_background(void)
{
	coordinate start;
	dimension size;
	font_palette color;
	if(keyboardtype==KEYTYPE_CD_DVD_VCD)//frank.huang add to show different keyboard 050922
	{
		start.x = 0;
		start.y = 90;
		size.x_length = 720;
		size.y_length = 160;
		osd_draw_rectangle(&start,&size,KEY_BACKGROUND_COLOR,KEY_REGION);
		

		
		start.x = 0;
		start.y = 186;
		size.x_length = 720;
		size.y_length = 60;
		osd_draw_rectangle(&start,&size,KEY_DISABLE_COLOR,KEY_REGION);


		start.x = 450;
		start.y = 139;
		size.x_length = 250;
		size.y_length = 47;
		osd_draw_rectangle(&start,&size,KEY_DISABLE_COLOR,KEY_REGION);

		start.x -= 24;
		start.y = 139;
		size.x_length = 24;
		size.y_length = 47;
		color.background_color=KEY_BACKGROUND_COLOR;
		color.font_color=KEY_DISABLE_COLOR;
		osd_draw_font_bitmap(keylayl, &start, &size,&color,KEY_REGION,0);



		start.x = 533;
		start.y = 92;
		size.x_length = 85;
		size.y_length = 47;
		osd_draw_rectangle(&start,&size,KEY_DISABLE_COLOR,KEY_REGION);


		

		start.x -= 25;
		start.y = 92;
		size.x_length = 24;
		size.y_length = 47;
		color.background_color=KEY_BACKGROUND_COLOR;
		color.font_color=KEY_DISABLE_COLOR;
		osd_draw_font_bitmap(keylayl, &start, &size,&color,KEY_REGION,0);

		
		start.x += 24+85;
		start.y = 92;
		size.x_length = 24;
		size.y_length = 47;
		color.background_color=KEY_BACKGROUND_COLOR;
		color.font_color=KEY_DISABLE_COLOR;
		osd_draw_font_bitmap(keylayr, &start, &size,&color,KEY_REGION,0);
	}
	else if(keyboardtype==KEYTYPE_CDROM_CHANGE_PAGE)
	{
		start.x = 616;
		start.y = 0;
		size.x_length = 100;
		size.y_length = 250;
		osd_draw_rectangle(&start,&size,KEY_DISABLE_COLOR,KEY_REGION);
		start.x = 600;
		start.y = 21;
		size.x_length = 100;
		size.y_length = 229;
		osd_draw_rectangle(&start,&size,KEY_DISABLE_COLOR,KEY_REGION);
		start.x = 600;
		start.y = 0;
		osd_draw_bmp(&start, round_corner, KEY_REGION);
		
	}

}
void show_keyboard_buttonL(BYTE row,const BYTE* bmp)
{
	coordinate start;
	if(keyboardtype==KEYTYPE_CD_DVD_VCD)
		start.x = KEY_BOARD_L_XSTART+row*KEY_BOARD_L_XSTEP;
	else
		start.x = KEY_BOARD_L_XSTART+row*KEY_BOARD_XSTEP_M;
	start.y = KEY_BOARD_L_YSTART;

	osd_draw_bmp(&start, bmp, KEY_REGION);
	
}

void show_keyboard_buttonR(BYTE row, BYTE col, const BYTE* bmp)
{

	coordinate start;
	if(keyboardtype==KEYTYPE_CDROM_CHANGE_PAGE)
	{	
        start.x = KEY_BOARD_R_XSTART_M;
		start.y = KEY_BOARD_R_YSTART_M+col*KEY_BOARD_R_YSTEP_M;
	}

	else
	{
		start.x = KEY_BOARD_R_XSTART+row*KEY_BOARD_R_XSTEP;
		start.y = KEY_BOARD_R_YSTART+col*KEY_BOARD_R_YSTEP;
	}
	
	osd_draw_bmp(&start, bmp, KEY_REGION);
	
}


void show_gps_keyboard(void)
{	//osd_active_regions=4;
	
	
	//osd_tog_region(2, OSD_OFF); 
	//osd_tog_region(1, OSD_OFF); 
	//osd_tog_region(0, OSD_OFF); 

   	osd_tog_region(KEY_REGION, OSD_ON); 
    osd_fill_region(KEY_REGION,0);//KEY_BACKGROUND_COLOR);

	if(keyboardtype==KEYTYPE_CD_DVD_VCD)
	{
		show_keyboard_background();
		show_keyboard_buttonL(0,button_prev);
		show_keyboard_buttonL(1,button_pause);
		show_keyboard_buttonL(2,button_next);
		show_keyboard_buttonL(3,button_stop);
		show_keyboard_buttonL(4,button_backward);
		show_keyboard_buttonL(5,button_forward);
		show_keyboard_buttonL(6,button_down);
		show_keyboard_buttonL(7,button_eject);
	
		show_keyboard_buttonR(1,0,button_up);
		show_keyboard_buttonR(0,1,button_left);
		show_keyboard_buttonR(1,1,button_enter);
		show_keyboard_buttonR(2,1,button_right);
	}
	else if(keyboardtype==KEYTYPE_CDROM_NORMAL)
	{
		show_keyboard_buttonL(0,button_prev_m);
		show_keyboard_buttonL(1,button_play_m);
		show_keyboard_buttonL(2,button_next_m);
		show_keyboard_buttonL(3,button_stop_m);
		show_keyboard_buttonL(4,button_backward_m);
		show_keyboard_buttonL(5,button_forward_m);
		show_keyboard_buttonL(6,button_mode_m);
		
	}
	else if(keyboardtype==KEYTYPE_CDROM_CHANGE_PAGE)
	{
		show_keyboard_background();
		show_keyboard_buttonL(0,button_prev_m);
		show_keyboard_buttonL(1,button_play_m);
		show_keyboard_buttonL(2,button_next_m);
		show_keyboard_buttonL(3,button_stop_m);
		show_keyboard_buttonL(4,button_backward_m);
		show_keyboard_buttonL(5,button_forward_m);
		show_keyboard_buttonL(6,button_mode_m);

		show_keyboard_buttonR(2,0,button_video_page_m);
		show_keyboard_buttonR(2,1,button_jpg_page_m);
		show_keyboard_buttonR(2,2,button_mp3_page_m);
		
		
	}
	
}

void GPS_key_board(void)
{
	extern int get_rtc_val(void);
    if (full_scrn & TOUCH_KEYBOARD)
	{
		extern UINT32 save_srn_start_t;
	    ClearOsdMsg(KEY_REGION);
	    osd_tog_region(KEY_REGION, OSD_OFF);
		full_scrn &= (~TOUCH_KEYBOARD);
       	osd_init();
		save_srn_start_t = get_rtc_val();
		keyboardtype=KEYTYPE_OFF;
	}
	else
	{
		if((full_scrn & MARK)||(full_scrn & GOTO))
		{
			invalid_key();
			return;
		}
		else if(full_scrn & SETUP)
		{
		    ircmd_setup();
		}
		else if(full_scrn & PROGRAM)
		{
		    ircmd_prog();   
		}
		full_scrn = TOUCH_KEYBOARD;
		//osd_draw_touch_keyboard();

        timer_counter = 0;
		if(cd_type_loaded==CDROM)
			keyboardtype=KEYTYPE_CDROM_NORMAL;
		else
			keyboardtype=KEYTYPE_CD_DVD_VCD;
		osd_init_gps_keyboard();
		show_gps_keyboard();
	}
}



#endif//#ifdef GPS_KEYBOARD

#ifdef GPS_MENU

#include "setup_VA.h"

extern void osd_init_gps_menu(void);
extern void osd_init_gps_keyboard(void);
extern int AUDIF_Set_Volume(UINT8 x);
//extern void SetBrightness(BYTE nVal);
//extern void SetContrast(BYTE nVal);
extern void run_save_sel_cmd(BYTE value __attribute__((unused)), BYTE index);
extern void exe_setup_function(UINT8 tt_id, UINT8 sub_id, UINT8 exe);

void brightness_auto_switch(BYTE power);

//define menu page
#define VOLUME_PAGE         0
#define BRIGHTNESS_PAGE     1
#define CONTRAST_PAGE       2
#define BUZZER_PAGE         3
#define FM_PAGE             4
#define NTSC_MODE_PAGE      5  

//define button type
#define ADD_BUTTON          0
#define DECREASE_BUTTON     1 
#define ON_BUTTON           2
#define OFF_BUTTON          3
#define NTSC_16_9_BUTTON    4
#define NTSC_4_3_BUTTON     5

//define the location for button
//to edit ELIPSE_BUTTON's shape

#define ELIPSE_BUTTON_YSTART    230//90+18
#define ELIPSE_BUTTON_XSTART_L  23//24-12 
#define ELIPSE_BUTTON_XSTART_R  297//288-6
#define ROUND_BUTTON_YSTART     245//120
#define ROUND_BUTTON_XSTART_L   76//42
#define ROUND_BUTTON_XSTART_R   206//242
#define ROUND_BUTTON_W   96//242
#define ROUND_BUTTON_H   48//242


//define the location for menu icon
#define MENU_ICON_STEP      60
#define MENU_ICON_XSTART    15
#define MENU_ICON_YSTART    32

//define color
#define BACKGROUND_COLOR    3   //WHITE
#define HIGHLIGHT_COLOR     1   //ORANGE
#define FONT_COLOR          2   //BLACK
#define DISABLE_COLOR       0   //GRAY



//define the location of bar in page0~2
#define TOTAL_BAR_NUMBER    13
#define BAR_XSTART          88
#define BAR_YSTART          253
#define BAR_STEP            16

#define MENU_REGION         2



//define fm frequency and switch button location
#define FM_MAX_FREQUENCY            1080//120MHZ
#define FM_MIN_FREQUENCY            913//91.3MHZ
//#define FM_SWITCH_BUTTON_XSTART     92
//#define FM_SWITCH_BUTTON_YSTART_U   136
//#define FM_SWITCH_BUTTON_YSTART_D   175
//#define FM_SWITCH_BUTTON_W          60
//#define FM_SWITCH_BUTTON_H          30
//add brightness auto button frank.huang 2005.7.27


#define BR_SWITCH_BUTTON_XSTART 	144
#define BR_SWITCH_BUTTON_YSTART 	300
#define BR_SWITCH_BUTTON_W 		88
#define BR_SWITCH_BUTTON_H		39





//#define SENSOR_BUTTON_XSTART        96
//#define SENSOR_BUTTON_YSTART        140
//#define SENSOR_BUTTON_W             76
//#define SENSOR_BUTTON_H             30

#define FM_POWER_BUTTON_XSTART	90
#define FM_POWER_BUTTON_YSTART	280
#define FM_POWER_BUTTON_XSTEP	100
#define FM_POWER_BUTTON_W		88
#define FM_POWER_BUTTON_H		39

#define KEYBARD_REGION_XSTART   (0*2)
#define KEYBARD_REGION_YSTART   (115*2)

#define MENU_REGION_XSTART      (90*2)
#define MENU_REGION_YSTART      (34*2)

#define X_SCALE_RATE        150//720/480=1.5, need divide 100 if use this rate to scale coordination
#define Y_SCALE_RATE        205//480/234=2.05, need divide 100 if use this rate to scale coordination
#define X_FIXED_OFFSET      0

#define KEYBOARD_BUTTON_W   80
#define KEYBOARD_BUTTON_H   44

#define MENU_ICON_W         40
#define MENU_ICON_H         54
//#define ON_OFF_BUTTON_W     96  
//#define ON_OFF_BUTTON_H     96

#define ADD_DEC_BUTTON_W    48//80//56
#define ADD_DEC_BUTTON_H    64//100//136

#define INFO_STR_HEIGHT		34




//define setting value
BYTE menu_page_index;
//BYTE audio_volume;
BYTE bright_value;
BYTE brightness_autodetect;
BYTE contrast_value;
BYTE buzzer_state;
BYTE fm_power;


UINT16 fm_frequency;
BYTE display_mode; 


const BYTE *const menu_icon[]=
{
    volume_icon,
    brightness_icon,
    contrast_icon,
    buzzer_icon,
    fm_icon,
    display_icon,
    volume_icon_hl,
    brightness_icon_hl,
    contrast_icon_hl,
    buzzer_icon_hl,
    fm_icon_hl,
    display_icon_hl,
    
//    buzzer_icon_off,//frank.huang 050826
};
void draw_freq_num(UINT16 frequency)
{
	BYTE i,j;
	coordinate start;
	font_palette color;
	dimension len;

	color.background_color=BACKGROUND_COLOR;
	color.font_color=DISABLE_COLOR;
	
	len.x_length = 8;
	len.y_length = 26;

	start.y=225;
	start.x=158;
	osd_draw_font_bitmap(big_num_fontnp, &start, &len, &color,MENU_REGION,0);

	len.x_length = 72;
		
	start.x=205;
	osd_draw_font_bitmap(big_num_mhz, &start, &len, &color,MENU_REGION,0);


	len.x_length = 16;
	
	start.x=168;
	j = frequency%10;

	
	osd_draw_font_bitmap(big_num_font[j], &start, &len, &color,MENU_REGION,0);
	start.x -= 8;
	//frequency = frequency/10;
	for(i=0;i<3;i++)
	{	start.x -= 20;
		frequency = frequency/10;
		j=frequency%10;
		if(i!=2||j!=0)
			osd_draw_font_bitmap(big_num_font[j],&start, &len, &color,MENU_REGION,0);
		if(j==0&&i==2)//frank.huang add 051014 del "1" when "100" change to "99"
			osd_draw_rectangle(&start, &len, BACKGROUND_COLOR, MENU_REGION);
		
	}
		
}

void osd_draw_button(BYTE button_index, coordinate start, UINT16 button_color, UINT16 font_color,BYTE region)
{

    font_palette color;
    color.font_color = font_color;
    color.background_color = button_color;//HIGHLIGHT_COLOR;//BACKGROUND_COLOR;
    if( (button_index == ADD_BUTTON)||(button_index == DECREASE_BUTTON) )
    {
        //dimension len;
        //len.x_length = ADD_DEC_BUTTON_W;//48;//80;//56
        //len.y_length = ADD_DEC_BUTTON_H;//48;//100;//136
        //osd_draw_rectangle(&start,&len, BACKGROUND_COLOR, MENU_REGION);
		//osd_draw_font_bitmap(elipse_button, &start,&len, &color, region,0);
        //osd_draw_horizontal_line( (start.x+17+12) ,(start.x+41+12) , (start.y+68-18), font_color, 3, region);
		if(button_index == ADD_BUTTON)
        {         
        	if(button_color==DISABLE_COLOR)
        	osd_draw_bmp(&start, elipse_button_add_g, region);
			else
			osd_draw_bmp(&start, elipse_button_add, region);
        }
		else
		{
			if(button_color==DISABLE_COLOR)
			osd_draw_bmp(&start, elipse_button_dec_g, region);
			else
			osd_draw_bmp(&start, elipse_button_dec, region);
   		}
    }
    else
    {
        dimension len;
        len.x_length = ROUND_BUTTON_W;//96;
        len.y_length = ROUND_BUTTON_H;//48;
		start.x=ROUND_BUTTON_XSTART_L;
		start.y=ROUND_BUTTON_YSTART;
		//color.font_color=FONT_COLOR;
		//color.background_color=HIGHLIGHT_COLOR;
		//osd_draw_rectangle(&start,&len, BACKGROUND_COLOR, MENU_REGION);
       
        if(button_index == ON_BUTTON)
        {  

			osd_draw_font_bitmap(borderline_m, &start,&len, &color, region,0);
            start.x +=30;
            start.y +=12;
			//osd_draw_font_bitmap(borderline, &start,&len, &color, region,0);
            osd_draw_string(&start,"ON",font_color,button_color,region,0);       
        }
        else if(button_index == OFF_BUTTON)
        {

			start.x = ROUND_BUTTON_XSTART_R;
			osd_draw_font_bitmap(borderline_m, &start,&len, &color, region,0);
			
			start.x +=24;
            start.y +=12;
			osd_draw_string(&start,"OFF",font_color,button_color,region,0);
        }
        else if(button_index == NTSC_16_9_BUTTON)
        {
			osd_draw_font_bitmap(borderline_m, &start,&len, &color, region,0);
			//start.x += 20;
            //start.y += 24;
            //osd_draw_string(&start,"NTSC",font_color,button_color,region,0);
            start.x += 13;
            start.y += 12;
            osd_draw_string(&start,"16:9",font_color,button_color,region,0);
        }
        else if(button_index == NTSC_4_3_BUTTON)
        {
        	start.x = ROUND_BUTTON_XSTART_R;
        	osd_draw_font_bitmap(borderline_m, &start,&len, &color, region,0);
            //start.x +=20;
            //start.y +=24;
            //osd_draw_string(&start,"NTSC",font_color,button_color,region,0);
            start.x += 23;
            start.y += 12;
            osd_draw_string(&start,"4:3",font_color,button_color,region,0);
            
        }
    }    
}

void osd_draw_menu_icon(BYTE icon_index, BYTE highlight)
{

    coordinate start;
    dimension size;
    font_palette color;
    
    start.x = MENU_ICON_XSTART + (icon_index*MENU_ICON_STEP);
    start.y = MENU_ICON_YSTART;
    
    size.x_length = MENU_ICON_W;
    size.y_length = MENU_ICON_H;
    
    color.font_color = FONT_COLOR;

	if(highlight)
        icon_index += 6;
    
 
    //osd_draw_font_bitmap(menu_icon[icon_index], &start, &size, &color, MENU_REGION, 0);    
    osd_draw_bmp(&start,menu_icon[icon_index], MENU_REGION);
    
}

//frank.huang 2005.7.27 for new buzz_icon which can change when buzz'state change
/*
void osd_draw_buzz_icon(BYTE highlight)
{
	coordinate start;
	dimension size;
	font_palette color;
		
	start.x = MENU_ICON_XSTART + (3*MENU_ICON_STEP);
	start.y = MENU_ICON_YSTART;
		
	size.x_length = 40;
	size.y_length = 40;
		
	color.font_color = 2;
	if(highlight)
	    color.background_color = 1;
	else
		color.background_color = 3;
	if(buzzer_state==0)
		osd_draw_font_bitmap(menu_icon[6], &start, &size, &color, MENU_REGION, 0);    
	else
		osd_draw_font_bitmap(menu_icon[3], &start, &size, &color, MENU_REGION, 0);    
	
}*/

//select flag is for round button
void show_page_button(BYTE page_index)
{
    coordinate start;
    font_palette color;
    if( (page_index == VOLUME_PAGE)||(page_index == BRIGHTNESS_PAGE)||(page_index == CONTRAST_PAGE) ||(page_index == FM_PAGE) )
    {
        start.x = ELIPSE_BUTTON_XSTART_L;
        start.y = ELIPSE_BUTTON_YSTART;
        osd_draw_button(DECREASE_BUTTON, start, HIGHLIGHT_COLOR,  FONT_COLOR, MENU_REGION );
        start.x = ELIPSE_BUTTON_XSTART_R;
        osd_draw_button(ADD_BUTTON, start, HIGHLIGHT_COLOR, FONT_COLOR, MENU_REGION );
        if(page_index == FM_PAGE)
        {
            dimension len;
            //len.x_length = FM_SWITCH_BUTTON_W;
            //len.y_length = FM_SWITCH_BUTTON_H;
            //start.x = FM_SWITCH_BUTTON_XSTART;
            //start.y = FM_SWITCH_BUTTON_YSTART_U;
            
            if(fm_power == 0)
            {
                //osd_draw_rectangle(&start,&len, HIGHLIGHT_COLOR, MENU_REGION);
                //start.x +=8;
                //start.y +=2;
                //osd_draw_string(&start,"OFF",BACKGROUND_COLOR,HIGHLIGHT_COLOR,MENU_REGION,0);
                //start.x = 92;
                //start.y = 175;
                //osd_draw_rectangle(&start,&len, DISABLE_COLOR, MENU_REGION);
                //start.x +=16;
                //start.y +=2;
                //osd_draw_string(&start,"ON",BACKGROUND_COLOR,DISABLE_COLOR,MENU_REGION,0);
                start.x = ELIPSE_BUTTON_XSTART_L;
                start.y = ELIPSE_BUTTON_YSTART;
                osd_draw_button(DECREASE_BUTTON, start, DISABLE_COLOR,  FONT_COLOR, MENU_REGION );
                start.x = ELIPSE_BUTTON_XSTART_R;
                osd_draw_button(ADD_BUTTON, start, DISABLE_COLOR, FONT_COLOR, MENU_REGION );
                len.x_length = FM_POWER_BUTTON_W;
		        len.y_length = FM_POWER_BUTTON_H;
				
				start.x = FM_POWER_BUTTON_XSTART;//100;
				start.y = FM_POWER_BUTTON_YSTART;//201;
				color.font_color = FONT_COLOR;
				color.background_color=DISABLE_COLOR;
				osd_draw_font_bitmap(borderline_s, &start, &len, &color, MENU_REGION, 0);
				start.x +=24;
				start.y +=6;
				osd_draw_string(&start,"ON",FONT_COLOR,DISABLE_COLOR,MENU_REGION,0);
				
				
		        start.x = FM_POWER_BUTTON_XSTART+FM_POWER_BUTTON_XSTEP;//200;
		        start.y = FM_POWER_BUTTON_YSTART;//201;
				color.font_color = FONT_COLOR;
				color.background_color=HIGHLIGHT_COLOR;
		        osd_draw_font_bitmap(borderline_s, &start, &len, &color, MENU_REGION, 0);
				start.x +=19;
		        start.y +=6;
				osd_draw_string(&start,"OFF",FONT_COLOR,HIGHLIGHT_COLOR,MENU_REGION,0);
            }
            else
            {
            	len.x_length = FM_POWER_BUTTON_W;
		        len.y_length = FM_POWER_BUTTON_H;
                //osd_draw_rectangle(&start,&len, DISABLE_COLOR, MENU_REGION);
                //start.x +=8;
                //start.y +=2;
                //osd_draw_string(&start,"OFF",BACKGROUND_COLOR,DISABLE_COLOR,MENU_REGION,0);
                //start.x = 92;
                //start.y = 175;
                //osd_draw_rectangle(&start,&len, HIGHLIGHT_COLOR, MENU_REGION);
                //start.x +=16;
                //start.y +=2;
                //osd_draw_string(&start,"ON",BACKGROUND_COLOR,HIGHLIGHT_COLOR,MENU_REGION,0);
                
                start.x = FM_POWER_BUTTON_XSTART;//100;
				start.y = FM_POWER_BUTTON_YSTART;//201;
				color.font_color = FONT_COLOR;
				color.background_color=HIGHLIGHT_COLOR;
				osd_draw_font_bitmap(borderline_s, &start, &len, &color, MENU_REGION, 0);
				start.x +=24;
				start.y +=6;
				osd_draw_string(&start,"ON",FONT_COLOR,HIGHLIGHT_COLOR,MENU_REGION,0);

				
		        start.x = FM_POWER_BUTTON_XSTART+FM_POWER_BUTTON_XSTEP;//200;
		        start.y = FM_POWER_BUTTON_YSTART;//201;
				color.font_color = FONT_COLOR;
				color.background_color=DISABLE_COLOR;
		        osd_draw_font_bitmap(borderline_s, &start, &len, &color, MENU_REGION, 0);
				start.x +=19;
		        start.y +=6;
				osd_draw_string(&start,"OFF",FONT_COLOR,DISABLE_COLOR,MENU_REGION,0);
				fm_frequency_tune(2);
            }
        }
	
        else if(page_index == BRIGHTNESS_PAGE)//frank.huang 2005.7.27
        {	
	        dimension len;
			//len.x_length = BR_SWITCH_BUTTON_ON_W;//35
			//len.y_length = BR_SWITCH_BUTTON_ON_H;//30
			//start.x = BR_SWITCH_BUTTON_ON_XSTART;//180
			//start.y = BR_SWITCH_BUTTON_YSTART_U;//115
			//font_palette color;
			if(brightness_autodetect)
	           { 
	            //osd_draw_rectangle(&start,&len, HIGHLIGHT_COLOR, MENU_REGION);
	            //start.y +=2;
		        //osd_draw_string(&start,"ON",BACKGROUND_COLOR,HIGHLIGHT_COLOR,MENU_REGION,0);
		 	    //len.x_length = BR_SWITCH_BUTTON_OFF_W;//50
			    //len.y_length = BR_SWITCH_BUTTON_OFF_H;//30
			    //start.x = BR_SWITCH_BUTTON_OFF_XSTART;//230
			    //start.y = BR_SWITCH_BUTTON_YSTART_U;//115
		        //osd_draw_rectangle(&start,&len, DISABLE_COLOR, MENU_REGION);
		            
		        //start.y +=2;
		        //osd_draw_string(&start,"OFF",BACKGROUND_COLOR,DISABLE_COLOR,MENU_REGION,0);
				start.x = ELIPSE_BUTTON_XSTART_L;
		        start.y = ELIPSE_BUTTON_YSTART;
		        osd_draw_button(DECREASE_BUTTON, start, DISABLE_COLOR,  FONT_COLOR, MENU_REGION );
		        start.x = ELIPSE_BUTTON_XSTART_R;
		        osd_draw_button(ADD_BUTTON, start, DISABLE_COLOR, FONT_COLOR, MENU_REGION );

			 	len.x_length = BR_SWITCH_BUTTON_W;//72;
		        len.y_length = BR_SWITCH_BUTTON_H;//32;
		        start.x = BR_SWITCH_BUTTON_XSTART;//145;
		        start.y = BR_SWITCH_BUTTON_YSTART;//197;
				color.font_color = FONT_COLOR;
				color.background_color=HIGHLIGHT_COLOR;
		        osd_draw_font_bitmap(borderline_s, &start, &len, &color, MENU_REGION, 0);
				start.x +=9;
		        start.y +=6;
				osd_draw_string(&start,"AUTO",FONT_COLOR,HIGHLIGHT_COLOR,MENU_REGION,0);
			}

			else
			{
	            /*osd_draw_rectangle(&start,&len, HIGHLIGHT_COLOR, MENU_REGION);
	            osd_draw_rectangle(&start,&len, DISABLE_COLOR, MENU_REGION);
	            start.y +=2;
	            osd_draw_string(&start,"ON",BACKGROUND_COLOR,DISABLE_COLOR,MENU_REGION,0);
		    	len.x_length = BR_SWITCH_BUTTON_OFF_W;//50
		    	len.y_length = BR_SWITCH_BUTTON_OFF_H;//30
				
	            start.x = BR_SWITCH_BUTTON_OFF_XSTART;//230
				start.y = BR_SWITCH_BUTTON_YSTART_U;//115
	            osd_draw_rectangle(&start,&len, HIGHLIGHT_COLOR, MENU_REGION);
	            
	            start.y +=2;
	            osd_draw_string(&start,"OFF",BACKGROUND_COLOR,HIGHLIGHT_COLOR,MENU_REGION,0);

				len.x_length = 76;
	            len.y_length = 40;
	            start.x = 96;
	            start.y = 110;
	            osd_draw_rectangle(&start,&len, DISABLE_COLOR, MENU_REGION);
	            start.x +=8;
	            start.y +=7;
	            osd_draw_string(&start,"AUTO",BACKGROUND_COLOR,DISABLE_COLOR,MENU_REGION,0);*/
	            start.x = ELIPSE_BUTTON_XSTART_L;
		        start.y = ELIPSE_BUTTON_YSTART;
		        osd_draw_button(DECREASE_BUTTON, start, HIGHLIGHT_COLOR,  FONT_COLOR, MENU_REGION );
		        start.x = ELIPSE_BUTTON_XSTART_R;
		        osd_draw_button(ADD_BUTTON, start, HIGHLIGHT_COLOR, FONT_COLOR, MENU_REGION );
	            len.x_length = BR_SWITCH_BUTTON_W;
		        len.y_length = BR_SWITCH_BUTTON_H;
		        start.x = BR_SWITCH_BUTTON_XSTART;
		        start.y = BR_SWITCH_BUTTON_YSTART;
				color.font_color = FONT_COLOR;
				color.background_color=BACKGROUND_COLOR;////HIGHLIGHT_COLOR;
		        osd_draw_font_bitmap(borderline_s, &start, &len, &color, MENU_REGION, 0);
				start.x +=12;
		        start.y +=6;
				osd_draw_string(&start,"AUTO",FONT_COLOR,BACKGROUND_COLOR,MENU_REGION,0);
				
			
			}
        }

    }
    else
    {
        
        start.y = ROUND_BUTTON_YSTART;
        if( (page_index == BUZZER_PAGE))//||(page_index == FM_PAGE) )
        {            
            if( ((page_index == BUZZER_PAGE)&&(buzzer_state == 1))
                ||((page_index == FM_PAGE)&&(fm_power == 1)) )
            {
                start.x = ROUND_BUTTON_XSTART_L;
                osd_draw_button(ON_BUTTON, start, HIGHLIGHT_COLOR,  FONT_COLOR, MENU_REGION );
                start.x = ROUND_BUTTON_XSTART_R;
                osd_draw_button(OFF_BUTTON, start, DISABLE_COLOR, FONT_COLOR, MENU_REGION );
            }
            else
            {
                start.x = ROUND_BUTTON_XSTART_L;
                osd_draw_button(ON_BUTTON, start, DISABLE_COLOR,  FONT_COLOR, MENU_REGION );
                start.x = ROUND_BUTTON_XSTART_R;
                osd_draw_button(OFF_BUTTON, start, HIGHLIGHT_COLOR, FONT_COLOR, MENU_REGION );
            }
        }
        else
        {
            if(display_mode==0)
            {
                start.x = ROUND_BUTTON_XSTART_L;
                osd_draw_button(NTSC_16_9_BUTTON, start, HIGHLIGHT_COLOR,  FONT_COLOR, MENU_REGION );
                start.x = ROUND_BUTTON_XSTART_R;
                osd_draw_button(NTSC_4_3_BUTTON, start, DISABLE_COLOR, FONT_COLOR, MENU_REGION );
            }
            else
            {
                start.x = ROUND_BUTTON_XSTART_L;
                osd_draw_button(NTSC_16_9_BUTTON, start, DISABLE_COLOR,  FONT_COLOR, MENU_REGION );
                start.x = ROUND_BUTTON_XSTART_R;
                osd_draw_button(NTSC_4_3_BUTTON, start, HIGHLIGHT_COLOR, FONT_COLOR, MENU_REGION );
            }
        }
    }
    
}


void osd_draw_bar(int enable_value,BYTE enable_colour)//frank.huang 2005.7.27
{
    BYTE n;
    coordinate start;
    dimension size;
    
    start.x = BAR_XSTART;
    start.y = BAR_YSTART;
    size.x_length = 8;
    size.y_length = 20;
    
    if((enable_value<0)||(enable_value > TOTAL_BAR_NUMBER))
        return;
        
    for(n=0; n < TOTAL_BAR_NUMBER; n++)
    {
        start.x = BAR_XSTART + n*BAR_STEP;
        if(n<enable_value)
           osd_draw_rectangle(&start,&size, enable_colour, MENU_REGION);
        else
           osd_draw_rectangle(&start,&size, DISABLE_COLOR, MENU_REGION); 
    }
       
}

void gps_menu_init(void)
{
    audio_volume = setup_VA[MENU_VA_AUD_VOL];
    bright_value = setup_VA[MENU_VA_BRIGHTNESS];
    contrast_value = setup_VA[MENU_VA_CONTRAST];
    buzzer_state = setup_VA[MENU_VA_BUZZ];
   
		//for 16:9 & 4:3 display
    display_mode = setup_VA[MENU_VA_TV_RATIO]; 
      	//frank.huang 2005.7.27
	fm_power =  setup_VA[MENU_VA_FM_POWER];
	fm_frequency = setup_VA[MENU_VA_FM_FREQ_H]*256+setup_VA[MENU_VA_FM_FREQ_L];
	brightness_autodetect = setup_VA[MENU_VA_BR_AUTO];

}

void set_menu_default_value(void)
{
    menu_page_index = 0;
    //audio_volume = 8;
    bright_value = 6;
    contrast_value = 6;
    buzzer_state = 1;  
    display_mode = 0; 
	// fm_power = 1;
}

void show_menu_page(BYTE index)
{
    int i;
    coordinate info_start;
	font_palette color;
	coordinate start;
	dimension size;
    
    if((index < VOLUME_PAGE)||(index > NTSC_MODE_PAGE))//filter the error page index
        return;
    osd_tog_region(1, OSD_ON); 
    //osd_init_gps_menu();
    osd_fill_region(MENU_REGION,0);
	
	info_start.x = 114;
    info_start.y = 152; 
	start.x = 0;
	start.y = 0;
	size.x_length = 368;
	size.y_length = 113;
	osd_draw_rectangle(&start,&size, DISABLE_COLOR, MENU_REGION); 

	start.x = 0;
	start.y = 114;
	size.x_length = 368;
	size.y_length = 238;
	osd_draw_rectangle(&start,&size, BACKGROUND_COLOR, MENU_REGION); 
    for(i=0;i<6;i++)
    {
        if(i == index)
            osd_draw_menu_icon(i,1);//with highlight
        else
            osd_draw_menu_icon(i,0);//without highlight
    }

	//frank.huang 2005.7.27
	//if(index==3)
   //     osd_draw_buzz_icon(1);
   	//else
   	//    osd_draw_buzz_icon(0);

	
    osd_draw_horizontal_line( 0 ,368 , 113, 1, 3, MENU_REGION);
	osd_draw_horizontal_line( 0 ,368 , 349, 1, 3, MENU_REGION);
    show_page_button(index);
   
    switch(index)//show srting in each page
    {
        case VOLUME_PAGE:
			info_start.x = 114;
            info_start.y = 160;
            osd_draw_bar(audio_volume,HIGHLIGHT_COLOR);
		    //osd_draw_string(&info_start,"VOLUME",FONT_COLOR,BACKGROUND_COLOR,MENU_REGION,0);
			size.x_length = 128;
			size.y_length = INFO_STR_HEIGHT;
			color.background_color=BACKGROUND_COLOR;
			color.font_color=FONT_COLOR;
			osd_draw_font_bitmap(volume_font, &info_start, &size,&color,MENU_REGION,0);//frank.huang 050826
            break;
        
        case BRIGHTNESS_PAGE:
            info_start.x = 89;
            info_start.y = 160;
			//frank.huang 2005.7.27
	    if(brightness_autodetect)
           	osd_draw_bar(bright_value,FONT_COLOR);
	    else
	        osd_draw_bar(bright_value,HIGHLIGHT_COLOR);

			size.x_length = 200;
			size.y_length = INFO_STR_HEIGHT;
			color.background_color=BACKGROUND_COLOR;
			color.font_color=FONT_COLOR;
			osd_draw_font_bitmap(brightness_font, &info_start, &size,&color,MENU_REGION,0);//frank.huang 050826
			//osd_draw_string(&info_start,"BRIGHTNESS",FONT_COLOR,BACKGROUND_COLOR,MENU_REGION,0);
            break;
        
        case CONTRAST_PAGE:
			info_start.x = 96;
            info_start.y = 160;
            osd_draw_bar(contrast_value,HIGHLIGHT_COLOR);

			size.x_length = 168;
			size.y_length = INFO_STR_HEIGHT;
			color.background_color=BACKGROUND_COLOR;
			color.font_color=FONT_COLOR;
			osd_draw_font_bitmap(contrast_font, &info_start, &size,&color,MENU_REGION,0);//frank.huang 050826

			
            //osd_draw_string(&info_start,"CONTRAST",FONT_COLOR,BACKGROUND_COLOR,MENU_REGION,0);
            break;
        
        case BUZZER_PAGE:
            info_start.x = 17;
            info_start.y = 165; 
			
			size.x_length = 336;
			size.y_length = INFO_STR_HEIGHT;
			color.background_color=BACKGROUND_COLOR;
			color.font_color=FONT_COLOR;
			osd_draw_font_bitmap(buzz_font, &info_start, &size,&color,MENU_REGION,0);//frank.huang 050826
			
            //osd_draw_string(&info_start,"TOUCH SCREEN SOUND",FONT_COLOR,BACKGROUND_COLOR,MENU_REGION,0);
            break;
        
        case FM_PAGE:
            info_start.x = 53;
            info_start.y = 154; 
			size.x_length = 280;
			size.y_length = INFO_STR_HEIGHT;
			color.background_color=BACKGROUND_COLOR;
			color.font_color=FONT_COLOR;
			osd_draw_font_bitmap(fm_font, &info_start, &size,&color,MENU_REGION,0);//frank.huang 050826

			
            //osd_draw_string(&info_start,"FM TRANSMITTER",FONT_COLOR,BACKGROUND_COLOR,MENU_REGION,0);
            
            break;
        case NTSC_MODE_PAGE:
            info_start.x = 80;
            info_start.y = 154; 
			size.x_length = 224;
			size.y_length = INFO_STR_HEIGHT;
			color.background_color=BACKGROUND_COLOR;
			color.font_color=FONT_COLOR;
			osd_draw_font_bitmap(ratio_font, &info_start, &size,&color,MENU_REGION,0);
            //osd_draw_string(&info_start,"ASPECT RATIO",FONT_COLOR,BACKGROUND_COLOR,MENU_REGION,0);
            break;
              
    }
    
}

//variable add_flag only used for page0~2
//add_flag: 1--add, 0--decrease
void change_value(BYTE add_flag)
{
    switch(menu_page_index)
    {
        case VOLUME_PAGE:
            if((add_flag)&&(audio_volume<TOTAL_BAR_NUMBER))
            {
            	audio_volume++;
				//send_setting_info(AUDIO_SETTING);
			}
            else if((!add_flag)&&(audio_volume>0))
            {
            	audio_volume--;
				//send_setting_info(AUDIO_SETTING);
			}
            else
            {
				
                return;
            }
			value_chg=AUDIO_SETTING;//frank.huang 050826 change value will send to GPS, and GPS will chage the LCD,AUDIO,FM driver
			//audio_volume = audio_volume;
            osd_draw_bar(audio_volume,HIGHLIGHT_COLOR);
            AUDIF_Set_Volume(audio_volume);
            save_setting_val(AUDIO_SETTING);
            break;
        
        case BRIGHTNESS_PAGE:
		    if(brightness_autodetect==1)
		   {
				brightness_autodetect = 0;
			   	brightness_auto_switch(0);
		       	show_menu_page(menu_page_index);
				save_setting_val(LCD_SETTING);
			}

			
	            if((add_flag)&&(bright_value<TOTAL_BAR_NUMBER))
	            {	
	            	bright_value++;
				}
				else if((!add_flag)&&(bright_value>0))
	            {
	            	bright_value--;
				}
				else
				{
				    return;
				}
				value_chg=LCD_SETTING;
				
	            osd_draw_bar(bright_value,HIGHLIGHT_COLOR);
	            //SetBrightness(bright_value);
	            
	            save_setting_val(LCD_SETTING);
		    
			break;
        
        case CONTRAST_PAGE:
            if((add_flag)&&(contrast_value<TOTAL_BAR_NUMBER))
            {
            	contrast_value++;
            }
            else if((!add_flag)&&(contrast_value>0))
            {
            	contrast_value--;
            }
			else
			{
				
				return;
			}
			value_chg=LCD_SETTING;
			
			osd_draw_bar(contrast_value,HIGHLIGHT_COLOR);
            //SetContrast(contrast_value);
			//send_setting_info(LCD_SETTING);
            
			save_setting_val(LCD_SETTING);
            break;
        case BUZZER_PAGE:
            buzzer_state = (~buzzer_state) & 0x01;

			value_chg=AUDIO_SETTING;
			
			//send_setting_info(AUDIO_SETTING);
            show_page_button(BUZZER_PAGE);
	    	//osd_draw_buzz_icon(1);//frank.huang 2005.7.27
	    	
	    	
			save_setting_val(AUDIO_SETTING);
            break;
        case FM_PAGE:
            if(fm_power)
            {
                if(add_flag)
                    fm_frequency_tune(1);
                else
                    fm_frequency_tune(0);
           }
			
            break;
        case NTSC_MODE_PAGE:
            display_mode = (~display_mode) & 0x01;
			
            show_page_button(NTSC_MODE_PAGE);
            if(display_mode)
            {
                exe_setup_function(STR_OS_TV_RATIO,STR_OS_4_3LB,1);
            }
            else
            {
                exe_setup_function(STR_OS_TV_RATIO,STR_OS_16_9,1);
            }
			value_chg=LCD_SETTING;
			save_setting_val(LCD_SETTING);
	        break;
    }
    //save_change_value(); 
}

void show_gps_menu(void)
{
	
    gps_menu_init();
    osd_init_gps_menu(); 
    show_menu_page(menu_page_index);
}
/*
void show_default_page(void)
{
    set_menu_default_value(); 
    osd_init_gps_menu();  
    show_menu_page(menu_page_index);
}
*/
void GPS_key_menu(void)
{extern int get_rtc_val(void);
    if (full_scrn & TOUCH_MENU)
	{extern UINT32 save_srn_start_t;
	    
	    ClearOsdMsg(MENU_REGION);
	    osd_tog_region(MENU_REGION, OSD_OFF);
		full_scrn &= (~TOUCH_MENU);
		osd_init_gps_keyboard();
		save_srn_start_t=get_rtc_val();
	}
	else
	{
		if((full_scrn & MARK)||(full_scrn & GOTO))
		{
			invalid_key();
			return;
		}
		else if(full_scrn&SETUP)
		{
		    ircmd_setup();
		}
		else if(full_scrn & PROGRAM)
		{
		    ircmd_prog();   
		}
		full_scrn = TOUCH_MENU;
		show_gps_menu();
	}
}

//power:1--on, 0--off
void fm_switch(BYTE power)
{
    if(power^fm_power)
    {
        fm_power = (~fm_power) & 0x01;
		//send_setting_info(FM_SETTING);
        show_menu_page(FM_PAGE);
    }
}

void brightness_auto_switch(BYTE power)
{
    if(power^brightness_autodetect)
    {
        brightness_autodetect = (~brightness_autodetect) & 0x01;
	    show_menu_page(BRIGHTNESS_PAGE);
		value_chg=LCD_SETTING;
    }
}


//flag: 0--decrease, 1--increase, 2--just show current frequency
void fm_frequency_tune(BYTE flag)
{
    BYTE freq1,freq2;
    
    if( (flag == 1) && (fm_frequency < FM_MAX_FREQUENCY))
        {
        fm_frequency++;
		value_chg=FM_SETTING;
		if(fm_frequency==924)
			fm_frequency=931;
		if(fm_frequency==982)
			fm_frequency=989;
		if(fm_frequency==1023)
			fm_frequency=1066;
		}
    else if( (flag == 0) && (fm_frequency > FM_MIN_FREQUENCY))
         {
        fm_frequency--;
		value_chg=FM_SETTING;
		if(fm_frequency==930)
			fm_frequency=923;
		if(fm_frequency==988)
			fm_frequency=981;
		if(fm_frequency==1065)
			fm_frequency=1022;
		
		}
    else if(flag == 2)
        ;
    else
        return;
	save_setting_val(FM_SETTING);

    freq1 = fm_frequency/10;
    freq2 = fm_frequency%10;
    psprintf(linebuf, "%3d%s%d%s", freq1,".",freq2,"MHZ");
    //start.x = 105;
    //start.y = 153; 
    //osd_draw_string(&start,linebuf,DISABLE_COLOR,BACKGROUND_COLOR,MENU_REGION,0);
    draw_freq_num(fm_frequency);
    
}
#endif//#ifdef GPS_MENU

#ifdef GPS_DVD
#include "io_uart0.h"
extern UINT8  safe_on;




TOUCH_DATA scale_coordinate(TOUCH_DATA cor)
{
    TOUCH_DATA pos;
    pos.xCoor = (cor.xCoor*X_SCALE_RATE)/100 + X_FIXED_OFFSET;
    pos.yCoor = (cor.yCoor*Y_SCALE_RATE)/100;
    
    return pos;
}
void show_chang_page(void)
{
	if(keyboardtype==KEYTYPE_CDROM_CHANGE_PAGE)
		keyboardtype=KEYTYPE_CDROM_NORMAL;
	else if(keyboardtype==KEYTYPE_CDROM_NORMAL)
		keyboardtype=KEYTYPE_CDROM_CHANGE_PAGE;
	else
		return;
	show_gps_keyboard();
}
void chang_media_page(BYTE page_index)//frank.huang 050922 add to use touch keyboard to change media page
{	
	
	switch(page_index)//frank.huang 050927
	{
	case	FS_FUNC_MP3:
			if(pFsJpeg->gifsFuncBtn != FS_FUNC_MP3&&pFsJpeg->gifsMP3Count!=0)
			{
				pFsJpeg->ControlArea = CNT_AREA_MP3BUTTON;
				ircmd_post_func(CMD_FUNC|CMD_FUNC_SELECT);
				pFsJpeg->ControlArea = CNT_AREA_FILE;
				pFsJpeg->gifsbPreview = 1;
			}
			show_chang_page();
       break;

	case	FS_FUNC_JPEG:
            if(pFsJpeg->gifsFuncBtn != FS_FUNC_JPEG&&pFsJpeg->gifsJPEGCount!=0)
			{
				pFsJpeg->ControlArea = CNT_AREA_JPEGBUTTON;
				ircmd_post_func(CMD_FUNC|CMD_FUNC_SELECT);
				pFsJpeg->ControlArea = CNT_AREA_FILE;
				pFsJpeg->gifsbPreview = 1;
			}
		show_chang_page();
        
		break;
	#ifdef SUPPORT_FILE_SYSTEM_MODE
	case	FS_FUNC_OTHER:
            if(pFsJpeg->gifsFuncBtn != FS_FUNC_OTHER&&pFsJpeg->gifsOtherCount!=0)
			{
				pFsJpeg->ControlArea = CNT_AREA_OTHERBUTTON;
				ircmd_post_func(CMD_FUNC|CMD_FUNC_SELECT);
				pFsJpeg->ControlArea = CNT_AREA_FILE;
				pFsJpeg->gifsbPreview = 1;
			}
		show_chang_page();
		break;
		#endif//#ifdef SUPPORT_FILE_SYSTEM_MODE
	}
	


	
	
}

	

//frank.huang update the keypad as the requirement from malata
//KEY_BOARD_L
//-----------------------------total col: 6, total row: 1 ------------------------------------
//          col 0        col 1          col 2 		col 3		col 4		col 5     
// row 0    prev         play_pause     next        stop 		backward	forward
//--------------------------------------------------------------------------------------------


//KEY_BOARD_R
//-----------------------------total col: 3, total row: 3 ------------------------------------
//          col 0        col 1          col 2      
// row 0                 up(1)          
// row 1    left(7)      enter(8)       right(9)
// row 2    			 down(15)     
//--------------------------------------------------------------------------------------------

void execute_keyboard(TOUCH_DATA pos)
{
	BYTE key_val;
	
	

	if(keyboardtype==KEYTYPE_CD_DVD_VCD)
	{
		if(pos.yCoor >= KEY_BOARD_L_YSTART && pos.xCoor >= KEY_BOARD_L_XSTART
		&& pos.xCoor <= KEY_BOARD_R_XSTART)
    		key_val = pos.xCoor / KEY_BOARD_L_XSTEP;//00---05

		else if(pos.xCoor >= KEY_BOARD_R_XSTART && pos.yCoor >= KEY_BOARD_R_YSTART)
			key_val=(((pos.yCoor-KEY_BOARD_R_YSTART) / KEY_BOARD_R_YSTEP)+1)*10 + (pos.xCoor-KEY_BOARD_R_XSTART)/KEY_BOARD_R_XSTEP;
		else//										up(11)
			return;//				left(20)		enter(21)	right(22)
					//				forward(30)		down(31)	eject(32)
	}
	else 
	{
		if(pos.yCoor >= KEY_BOARD_L_YSTART && pos.xCoor >= KEY_BOARD_L_XSTART
		&& pos.xCoor <= KEY_BOARD_R_XSTART_M)
    		key_val = pos.xCoor / KEY_BOARD_XSTEP_M;//00---05

		else if(pos.xCoor >= KEY_BOARD_R_XSTART_M&& pos.yCoor >= KEY_BOARD_R_YSTART_M)
			key_val=40+((pos.yCoor-KEY_BOARD_R_YSTART_M )/ KEY_BOARD_R_YSTEP_M);
		else//																		
			return;//
	}
//****************************************KEY VALUE TABLE********************************************************
//																					up(11)						*
//																	left(20)		enter(21)	right(22)		*	
//prev(00)	play/pause(01)	next(02)	stop(03)	backward(04)	forward(05)		down(31)	eject(32)		*
//																												*
//______________________________________________________________________________________________________________*
//																					movie(40)					*
//																					pciture(41)					*
//																					music(32)					*
//prev(00)	play/pause(01)	next(02)	stop(03)	backward(04)	forward(05)		mode(43)					*
//***************************************************************************************************************

	

	timer_counter = 0;
	
    switch(key_val)
    {   case 00:
			call_ir_func(IRC_PREV);
			//ircmd_prev();
            break;
        case 01:
			call_ir_func(IRC_PAUSEPLAY);
			//ircmd_play();

			break;
        case 02:
			call_ir_func(IRC_NEXT);
            
            break;
        case 03:
			call_ir_func(IRC_STOP);
            //ircmd_stop();
            break;
        case 04:
			call_ir_func(IRC_BACKWARD);
            //ircmd_backward();
            break;
        case 05:
			call_ir_func(IRC_FORWARD);
            //ircmd_forward();
            break;
		case 10:
            
            break;
        case 11:
            call_ir_func(IRC_UP);
			//ircmd_up();
            break;
        case 20:
			call_ir_func(IRC_LEFT);
            //ircmd_left();
            break;
        case 21:
			call_ir_func(IRC_SELECT);
            //ircmd_select();
            break;
        case 22:
			call_ir_func(IRC_RIGHT);
            //ircmd_right();
            break;
        case 30:
			call_ir_func(IRC_FORWARD);
           	//ircmd_forward();
            break;
        case 31:
			call_ir_func(IRC_DOWN);
            //ircmd_down();
            break;
        case 32:
			call_ir_func(IRC_EJECT);
           	//ircmd_eject_toggle();
            break;
		case 40:
			if(keyboardtype==KEYTYPE_CDROM_CHANGE_PAGE)//frank.huang 050927
				chang_media_page(FS_FUNC_OTHER);
			break;
		case 41:
			if(keyboardtype==KEYTYPE_CDROM_CHANGE_PAGE)//frank.huang 050927
				chang_media_page(FS_FUNC_JPEG);
			break;
		case 42:
			if(keyboardtype==KEYTYPE_CDROM_CHANGE_PAGE)//frank.huang 050927
				chang_media_page(FS_FUNC_MP3);
			break;
		case 43:
			show_chang_page();
			break;
      
        }
}
void execute_menu(TOUCH_DATA pos)
{
    UINT16 temp;
    BYTE page_index = 0;
    //execute the change menu page function if coordinate is appropriate
    if((pos.yCoor >= MENU_ICON_YSTART)&&(pos.yCoor <= MENU_ICON_YSTART+MENU_ICON_H))
    {
        
        if(pos.xCoor >= MENU_ICON_XSTART)
           page_index =(pos.xCoor-MENU_ICON_XSTART)/MENU_ICON_STEP;
        temp = (UINT16)(MENU_ICON_XSTART+page_index*MENU_ICON_STEP+MENU_ICON_W);    
        if((pos.xCoor <= temp)&&(page_index!=menu_page_index))
        {
            menu_page_index = page_index;
            show_menu_page(menu_page_index);
        }
    }
    
    //execute the value change function in different menu page
    if( ((menu_page_index == VOLUME_PAGE)||(menu_page_index == CONTRAST_PAGE)||(menu_page_index == BRIGHTNESS_PAGE)||(menu_page_index == FM_PAGE)) 
        && ((pos.yCoor >= ELIPSE_BUTTON_YSTART)&&(pos.yCoor <= ELIPSE_BUTTON_YSTART+ADD_DEC_BUTTON_H)))
    {
        if((pos.xCoor >= ELIPSE_BUTTON_XSTART_R)&&(pos.xCoor <= ELIPSE_BUTTON_XSTART_R+ADD_DEC_BUTTON_W))//touch add button
            change_value(1);
        else if((pos.xCoor >= ELIPSE_BUTTON_XSTART_L)&&(pos.xCoor <= ELIPSE_BUTTON_XSTART_L+ADD_DEC_BUTTON_W))//touch decrease button
            change_value(0);
    }
    else if( ((menu_page_index == BUZZER_PAGE)||(menu_page_index == NTSC_MODE_PAGE))
        && ((pos.yCoor >= ROUND_BUTTON_YSTART)&&(pos.yCoor <= ROUND_BUTTON_YSTART+ROUND_BUTTON_H)) )
    {
        if((pos.xCoor >= ROUND_BUTTON_XSTART_R)&&(pos.xCoor <= ROUND_BUTTON_XSTART_R+ROUND_BUTTON_W))
        {
            if( ((menu_page_index == BUZZER_PAGE)&&(buzzer_state == 1))
                ||((menu_page_index == NTSC_MODE_PAGE)&&(display_mode == 0))
                )
            	change_value(1);
        }
        else if((pos.xCoor >= ROUND_BUTTON_XSTART_L)&&(pos.xCoor <= ROUND_BUTTON_XSTART_L+ROUND_BUTTON_W))
        {
            if( ((menu_page_index == BUZZER_PAGE)&&(buzzer_state == 0))
                ||((menu_page_index == NTSC_MODE_PAGE)&&(display_mode == 1))
                )
            	change_value(0);
        }
    }

    //for special function in special page
    if(menu_page_index == BRIGHTNESS_PAGE)
    {
       /* if((pos.xCoor >= SENSOR_BUTTON_XSTART)&&(pos.xCoor <= SENSOR_BUTTON_XSTART+SENSOR_BUTTON_W)
            &&(pos.yCoor >= SENSOR_BUTTON_YSTART)&&(pos.yCoor <= SENSOR_BUTTON_YSTART+SENSOR_BUTTON_H))
        {//execute the auto dectect brightness function by sensor
            
        }*/

//frank.huang 2005.7.27
		if(brightness_autodetect==0&&pos.yCoor >= BR_SWITCH_BUTTON_YSTART&&pos.yCoor <= BR_SWITCH_BUTTON_YSTART+BR_SWITCH_BUTTON_H
			&&pos.xCoor >= BR_SWITCH_BUTTON_XSTART&&pos.xCoor <= BR_SWITCH_BUTTON_XSTART+BR_SWITCH_BUTTON_W)
		{
	        brightness_auto_switch(1);
	       	show_menu_page(menu_page_index);
		 	save_setting_val(LCD_SETTING);
		}
	   
    }
    else if((menu_page_index == FM_PAGE)&&(pos.yCoor >= FM_POWER_BUTTON_YSTART)&&(pos.yCoor <= FM_POWER_BUTTON_YSTART+FM_POWER_BUTTON_H)) 
    {
        if((fm_power==1)&&(pos.xCoor >= FM_POWER_BUTTON_XSTART+FM_POWER_BUTTON_XSTEP)&&(pos.xCoor <= FM_POWER_BUTTON_XSTART+FM_POWER_BUTTON_W+FM_POWER_BUTTON_XSTEP))
        {
            fm_power = 0;
			value_chg=FM_SETTING;
            show_menu_page(menu_page_index);
        }
        else if((fm_power==0)&&(pos.xCoor >= FM_POWER_BUTTON_XSTART)&&(pos.xCoor <= FM_POWER_BUTTON_XSTART+FM_POWER_BUTTON_W))
        {
            fm_power = 1;
			value_chg=FM_SETTING;
            show_menu_page(menu_page_index);
        }
	   	save_setting_val(FM_SETTING);
    }
}
int process_touch_panel(TOUCH_DATA ipos)
{
    TOUCH_DATA position;
    
    position = scale_coordinate(ipos);
    
    if((full_scrn&TOUCH_KEYBOARD)&&(position.xCoor >= KEYBARD_REGION_XSTART)&&(position.yCoor >= KEYBARD_REGION_YSTART))
    {
       	position.xCoor -= KEYBARD_REGION_XSTART;
        position.yCoor -= KEYBARD_REGION_YSTART;
       	execute_keyboard(position);
		return 1;
		
    }
    else if((full_scrn&TOUCH_MENU)&&(position.xCoor >= MENU_REGION_XSTART)&&(position.yCoor >= MENU_REGION_YSTART))
    {
        position.xCoor -= MENU_REGION_XSTART;
        position.yCoor -= MENU_REGION_YSTART;
        execute_menu(position);
        return 1;
    }
	
    	return 0;

}

void press_keypad(BYTE key)
{
    if(key == 0x70)//dvd,keyboard?
    {
        GPS_key_board();
		}
    else if(key == 0x71)//nav
        return;
    else if(key == 0x72)//setup
        ircmd_setup();
    else if(key == 0x73)//map
        return;
    else if(key == 0x74)//menu
        GPS_key_menu();
    else if(key == 0x75)//back
        ircmd_return();
    else if(key == 0x25)//left
        ircmd_left();
    else if(key == 0x26)//up
        ircmd_up();
    else if(key == 0x27)//right
        ircmd_right();
    else if(key == 0x28)//down
        ircmd_down();
    else if(key == 0x2b)//enter
        ircmd_select();
}

//set paramters according the receiving results from GPS
void setting_paramater(COM_PACKET *packet)
{
    switch(packet->data_type)
    {
        case  LCD_SETTING:
            brightness_autodetect = packet->data[0];
            bright_value = packet->data[1];
            contrast_value = packet->data[2];
			if(display_mode!=packet->data[3])//UPDATE DISPLAY MODE AT ONCE
				change_value(NTSC_MODE_PAGE);
			display_mode = packet->data[3];
			save_setting_val(LCD_SETTING);
            break;
        case  AUDIO_SETTING:
            audio_volume = packet->data[0];
            buzzer_state = packet->data[1];
			save_setting_val(AUDIO_SETTING);
			break;
        case  FM_SETTING:
            fm_frequency = (packet->data[0]<<8)|(packet->data[1]);
            fm_power = packet->data[2];
			save_setting_val(FM_SETTING);
            break;
    }
	if(full_scrn&TOUCH_MENU)
		show_menu_page(menu_page_index);//to updata menu frank.huang 050729
}
void save_setting_val(BYTE index)
{
	switch(index)
	{
		
		case AUDIO_SETTING:
			
			setup_VA[MENU_VA_AUD_VOL] = audio_volume;
			run_save_sel_cmd(setup_VA[MENU_VA_AUD_VOL],MENU_VA_AUD_VOL);
			
			setup_VA[MENU_VA_BUZZ] = buzzer_state;
			run_save_sel_cmd(setup_VA[MENU_VA_BUZZ],MENU_VA_BUZZ);

			break;
		case FM_SETTING:

			setup_VA[MENU_VA_FM_FREQ_H] = fm_frequency/256;
			run_save_sel_cmd(setup_VA[MENU_VA_FM_FREQ_H],MENU_VA_FM_FREQ_H);
			
			setup_VA[MENU_VA_FM_FREQ_L] = fm_frequency%256;
			run_save_sel_cmd(setup_VA[MENU_VA_FM_FREQ_L],MENU_VA_FM_FREQ_L);

			setup_VA[MENU_VA_FM_POWER] = fm_power;
			run_save_sel_cmd(setup_VA[MENU_VA_FM_POWER],MENU_VA_FM_POWER);
			break;
		case LCD_SETTING:
			
			setup_VA[MENU_VA_BR_AUTO] = brightness_autodetect;
			run_save_sel_cmd(setup_VA[MENU_VA_BR_AUTO],MENU_VA_BR_AUTO);
			
			setup_VA[MENU_VA_BRIGHTNESS] = bright_value;
			run_save_sel_cmd(setup_VA[MENU_VA_BRIGHTNESS],MENU_VA_BRIGHTNESS);

			setup_VA[MENU_VA_CONTRAST] = contrast_value;
			run_save_sel_cmd(setup_VA[MENU_VA_CONTRAST],MENU_VA_CONTRAST);
			
			setup_VA[MENU_VA_TV_RATIO] = display_mode;
			run_save_sel_cmd(setup_VA[MENU_VA_TV_RATIO],MENU_VA_TV_RATIO);
			

			break;
		
	}
	

}

//transfer the changed settings to GPS system after setting parameters on DVD platform
COM_PACKET transfer_paramater(BYTE type)
{
    COM_PACKET packet;
    
    switch(type)
    {
        case  LCD_SETTING:
            packet.data[0] = brightness_autodetect;
            packet.data[1] = bright_value;
            packet.data[2] = contrast_value;
            packet.data[3] = display_mode;
            break;
        case  AUDIO_SETTING:
            packet.data[0] = audio_volume;
            packet.data[1] = buzzer_state;
            packet.data[2] = 0;
            packet.data[3] = 0;
            break;
        case  FM_SETTING:
            packet.data[0] = (fm_frequency>>8)&0xff;
            packet.data[1] = fm_frequency&0xff;
            packet.data[2] = fm_power;
            packet.data[3] = 0;
            break;
        case DISK_INFO:
			if((system_state==SYSTEM_NODISC)||(system_state==SYSTEM_OPEN))
            	packet.data[0] = DISK_NODISK;
			else
				packet.data[0] = cd_type_tab[cd_type_loaded];//cd_type_loaded;//
            packet.data[1] = cd_play_state_tab[play_state];//play_state;//
            packet.data[2] = 0;
            packet.data[3] = 0;
            break;
    }
    
    packet.data_type = type;
    packet.checksum = ((packet.data_type+packet.data[0]+packet.data[1]+packet.data[2]+packet.data[3]));
    return packet;
}


int get_packet(COM_PACKET *packet)
{
    UINT32 nIndex = 0;
    BYTE checksum;

    while (!IsEPPRxEmpty())
    {
        if (!IsEPPRxEmpty())
        {
            BYTE c = EPP_GETC();            
            if(nIndex==0)
                packet->data_type = c;
            else if(nIndex==5)
                packet->checksum = c;
            else 
                packet->data[nIndex-1] = c;
            nIndex++;
        }
        if (nIndex == 6) break;
    }
    
    checksum = (packet->data_type+packet->data[0]+packet->data[1]+packet->data[2]+packet->data[3]);
    
    if(checksum != packet->checksum)
        return 0;
    else if(packet->data_type == 0x44)
        return -2;
    else if(packet->data_type == 0x88)
        return 2;
    else 
        return 1;
}
BYTE buf[6];
void sent_packet(COM_PACKET *packet)
{
    /*
    buf[0]=packet->data_type;
    buf[1]=packet->data[0];
    buf[2]=packet->data[1];
    buf[3]=packet->data[2];
    buf[4]=packet->data[3];
    buf[5]=packet->checksum;
    UART0_puts(buf);*/
//frank.huang 2005.7.27 to avoid send nothing after 0x00 sent 
    UART0_putc(packet->data_type);
    UART0_putc(packet->data[0]);
    UART0_putc(packet->data[1]);
    UART0_putc(packet->data[2]);
    UART0_putc(packet->data[3]);
    UART0_putc(packet->checksum);
}


void sent_setting_packet(DATA_PACKET	*packet)
{
	UART0_putc(packet->data[0]);
	UART0_putc(packet->data[1]);
	UART0_putc(packet->data[2]);
	UART0_putc(packet->data[3]);
	
}
void send_setting_info(BYTE SETTING_TYPE)
{
	COM_PACKET			setting_va;
	
	switch(SETTING_TYPE)
	{
		case	LCD_SETTING:
			
			setting_va.data_type=LCD_SETTING;
			setting_va.data[0]=brightness_autodetect;
			setting_va.data[1]=bright_value;
			setting_va.data[2]=contrast_value;
			setting_va.data[3]=display_mode;
			break;

			
		case	AUDIO_SETTING:
			
			setting_va.data_type=AUDIO_SETTING;
			setting_va.data[0]=audio_volume;
			setting_va.data[1]=buzzer_state;
			break;

		case	FM_SETTING:
			
			setting_va.data_type=FM_SETTING;
			setting_va.data[0]=fm_frequency%256;
			setting_va.data[1]=fm_frequency/256;
			setting_va.data[2]=fm_power;
			
			break;



		
	}
	setting_va.checksum=setting_va.data_type+setting_va.data[0]+setting_va.data[1]+setting_va.data[2]+setting_va.data[3];
	sent_packet(&setting_va);

}

void send_disk_info(void)
{

COM_PACKET	packet;
packet=transfer_paramater(DISK_INFO);
sent_packet(&packet);

}


void send_ack(BYTE ack_type,BYTE data_type)
{
	ACK_PACKET	ack_packet;


	if(ack_type==1)//ack_type == ACK)
	{
		ack_packet.ack = 0x88;
	}
	else
	{
		ack_packet.ack = 0x44;
	}
	ack_packet.data_type = data_type;

	switch(data_type)
	{


		case	KEYPAD:
			
			
			ack_packet.data[0] = packet.data[0];
			ack_packet.data[1] = 0;
			ack_packet.data[2] = 0;
			ack_packet.data[3] = 0;
			break;

		case	TOUCH:
					
					
			ack_packet.data[0] = packet.data[0];
			ack_packet.data[1] = packet.data[1];
			ack_packet.data[2] = packet.data[2];
			ack_packet.data[3] = packet.data[3];
					break;

			
		case	LCD_SETTING:
			
			
			ack_packet.data[0] = brightness_autodetect;
			ack_packet.data[1] = bright_value;
			ack_packet.data[2] = contrast_value;
			ack_packet.data[3] = display_mode;
			break;

			
		case	AUDIO_SETTING:
			
			ack_packet.data[0]=audio_volume;
			ack_packet.data[1]=buzzer_state;
			ack_packet.data[2] = 0;
			ack_packet.data[3] = 0;
			break;

		case	FM_SETTING:
			
			ack_packet.data[0]=fm_frequency%256;
			ack_packet.data[1]=fm_frequency/256;
			ack_packet.data[2]=fm_power;
			ack_packet.data[3] = 0;
			break;

		case	DISK_INFO:
			 
		
			if((system_state==SYSTEM_NODISC)||(system_state==SYSTEM_OPEN))
            	ack_packet.data[0] = DISK_NODISK;
			else
				ack_packet.data[0] = cd_type_tab[cd_type_loaded];
			ack_packet.data[1] = cd_play_state_tab[play_state];
			ack_packet.data[2] = 0;
			ack_packet.data[3] = 0;
			break;
		}

		
			UART0_putc(ack_packet.ack);
			UART0_putc(ack_packet.data_type);
			UART0_putc(ack_packet.data[0]);
			UART0_putc(ack_packet.data[1]);
			UART0_putc(ack_packet.data[2]);
			UART0_putc(ack_packet.data[3]);
		
}


void send_ack_info(void)
{
    UART0_putc(0x88);  
}

void send_nak_info(void)
{
    UART0_putc(0x44);  
}
void polling_GPS_DVD(void) 
{ 	
	
	value_chg=0;
	//COM_PACKET packet;
	packet.data_type=0;
	packet.checksum=0;
	packet.data[0]=0;
	packet.data[1]=0;
	packet.data[2]=0;
	packet.data[3]=0;
	if(keyboardtype!=KEYTYPE_CD_DVD_VCD&&keyboardtype!=KEYTYPE_OFF&&(full_scrn==0)&&(pFsJpeg->File_Count!=0))
	{	
		full_scrn = TOUCH_KEYBOARD;
		osd_init_gps_keyboard();
		show_gps_keyboard();
	}
	//sent_packet(&packet);
	//if play state changed , send disk_info to gps 
	
	if((cd_play_state_tab[last_play_state]!=cd_play_state_tab[play_state])&&(cd_type_tab[last_disc_type]!=DISK_UNKNOWN))//frank.huang 050927
	{
		send_disk_info();
		last_play_state=play_state;
		last_disc_type=cd_type_loaded;
		if(cd_type_loaded == CDROM)
			keyboardtype=KEYTYPE_CDROM_NORMAL;
		else
			keyboardtype=KEYTYPE_CD_DVD_VCD;

	}
	else if(last_disc_type!=cd_type_loaded&&last_disc_type!=10)
	{	send_disk_info();
		last_disc_type=cd_type_loaded;
		last_play_state=play_state;
		if(cd_type_loaded == CDROM&&keyboardtype==KEYTYPE_CD_DVD_VCD)//frank.huang 050927
			keyboardtype=KEYTYPE_CDROM_NORMAL;
		else
			keyboardtype=KEYTYPE_CD_DVD_VCD;
		
	}
	else if(((system_state==SYSTEM_NODISC)||(system_state==SYSTEM_OPEN))&&(last_disc_type!=DISK_NODISK_INDEX))
	{
		send_disk_info();
		last_disc_type=DISK_NODISK_INDEX;
	}
		
	else
	{
		if((get_packet(&packet))&&(packet.data_type==0))//packet no change
       	{	
       		return;
		}	
		else if((get_packet(&packet) == 0)&&(packet.data_type>=1)&&(packet.data_type<=8))//if checksum is error,return
    	{
    	//sent_packet(&packet);
		send_ack(0,packet.data_type);
	
		return;
		}
	}
     
    if((packet.data_type >= 1)&&(packet.data_type <= 8))
    {
        
            safe_srn_off();
		
        //psprintf(RegionValStr[REGION1],"ACK:%x %x %x %x %x %x",packet.data_type,packet.data[0],packet.data[1],packet.data[2],packet.data[3],packet.checksum);
        //PrintOsdMsg(STR_OS_SPACE, REGION0, 2, 1);
		//PrintOsdMsg(STR_OS_SPACE, REGION1, 2, 1);
        

    }
    
   
    if(packet.data_type == KEYPAD)
    {
        //packet.data_type = 0;
        press_keypad(packet.data[0]);
		send_ack(1,KEYPAD);
    }
    else if(packet.data_type == TOUCH)
    {
      
        if(!(full_scrn & TOUCH_KEYBOARD) && !(full_scrn & TOUCH_MENU))
            {
				 send_ack(1,TOUCH);
				return;
			}
		
		//send_ack(1,TOUCH);
        TOUCH_DATA cor;
        cor.xCoor = (packet.data[0])|(packet.data[1]<<8);
        cor.yCoor = (packet.data[2])|(packet.data[3]<<8);
        //if(process_touch_panel(cor))//;
            //sent_packet(&packet);
        process_touch_panel(cor);
		
//send XXXSETTING ack when XXXSETTING value is changed;send touch ack when else frank.huang 050801
		 if(value_chg)   
		 	send_ack(1,value_chg);
		 else
		 	send_ack(1,TOUCH);
		 //send_setting_info(value_chg);
       	 //packet.data_type = 0;
    }
    else if(packet.data_type == LCD_SETTING)
    {
        
        setting_paramater(&packet);
        
        send_ack(1,LCD_SETTING);
    }
    else if(packet.data_type == AUDIO_SETTING)
    {

        
        setting_paramater(&packet);
      
        send_ack(1,AUDIO_SETTING);
		AUDIF_Set_Volume(audio_volume);
    }
    else if(packet.data_type == FM_SETTING)
    {
       
        setting_paramater(&packet);
        
        send_ack(1,FM_SETTING);
    }
    else if(packet.data_type == DISK_INFO)
    {
        //packet = transfer_paramater(packet.data_type);
        //sent_packet(&packet);
        //send_disk_info();
        //packet.data_type = 0;
    }
    else if(packet.data_type == DATA_REQUEST)
    {	
    	send_ack(1,packet.data[0]);
        
    }
    else if(packet.data_type == MAP_COMMAND)
    {
        ;
    }
	
} 
#endif

