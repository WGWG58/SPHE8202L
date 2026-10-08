#include "user_init.h"

#ifdef DIVX_DRM

#include "global.h"
#include "drm.h"
#include "osd_palette.h"
#include "IR_VFD/ircmd.h"
#include "osd.h"
#include "memmap0.h"

char buf_save_drm_code[20];              //WSLEE for generate drm code 050615

#ifdef DRM_CODE               //WSLEE for generate drm code 050615
void Gen_RegCode(void){
        set_divx_drm_model_id(Divx_drm_modelID);//linrc change for change this ID needn't update fs_mp4.a 2005-8-11 17:15
		//set_divx_drm_model_id(DIVX_DRM_MODEL_ID);		
        generate_registration_code( buf_save_drm_code );
}
#endif

void divx_func_left()
{
    sys_cmd = CMD_SELECT | CMD_FUNC_GAME_L;
}

void divx_func_right()
{
    sys_cmd = CMD_SELECT | CMD_FUNC_GAME_R;
}


void divx_func_select()
{
    sys_cmd = CMD_FUNC | CMD_FUNC_SELECT;

    if( full_scrn & DIVX_DRM_MENU )
    {
#ifdef SDRAM_16Mb_Mode          // 2005/06/18 yltseng
        regs0->osd_base_addr=GetOSDBackUpAddress();
#endif
        full_scrn = 0;
        osd_init();
    }
}
#ifndef DRM_SHOW_FOLLOW_OSD_LANGUAGE_SET
#ifndef DRM_UI_FIVE_LANG
int osd_divx_drm_display( int iPage, int iCode )
{
	char buffer[20];
    #define DRM_FONT_COLOR          1
    #define DRM_BACK_COLOR          0

    extern BYTE    osd0_state;
    osd0_state = 0;
    t_disp = 0;

#ifdef NEW_OSD_DRIVER

    #ifdef OSD_SUPPORT_2_COLOR  // 2005/06/18 yltseng
	const _t_osd_hdr osd_divx_menu_hdr[] = {
        { 36 * 4 * 4, 32 * 5, 32, 80, SIMPLE_HEADER, OSD_FORMAT_2COLOR,  OSD_INTERLACED },
	};
    #else
	const _t_osd_hdr osd_divx_menu_hdr[] = {
        { 36 * 4 * 4, 32 * 5, 32, 80, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED },
	};
    #endif
    
    #ifdef SDRAM_16Mb_Mode
    regs0->osd_base_addr=OSD_BASE_USE_ADDR;
    #endif
    
	osd_init_regions( sizeof( osd_divx_menu_hdr ) / sizeof( _t_osd_hdr ), (_t_osd_hdr *) &osd_divx_menu_hdr );
	osd_set_palette_color( 0, DRM_BACK_COLOR, __palette4F( 150,210, 141, 0xe0 ) );
	osd_set_palette_color( 0, DRM_FONT_COLOR, __palette4F( 0, 70, 0,0xff ) );
    
    #ifdef SUPPORT_SW_OSD_SCALING  // for HD OSD, by robert.chang, 2006-09-28
    if( GET_TV_RESOLUTION()  == HD_720 )
        osd_init_scaling(sizeof( osd_divx_menu_hdr ) / sizeof( _t_osd_hdr ), 1);	
    else if(GET_TV_RESOLUTION()  == HD_1080)
        osd_init_scaling(sizeof( osd_divx_menu_hdr ) / sizeof( _t_osd_hdr ), 2);		
    #endif

    osd_tog_region( 0, OSD_ON );
#else

    extern void osd_init_regions(int n, const _t_osd_hdr *hdrp);
    
	const _t_osd_hdr osd_divx_menu_hdr[] = {
        { 18 * 4, 24, 32, 34, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED },
        { 36 * 8, 32 * 5, 32, 80, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED },
	};

	osd_init_regions( sizeof( osd_divx_menu_hdr ) / sizeof( _t_osd_hdr ), (_t_osd_hdr *) &osd_divx_menu_hdr );

    SetOsdCol( 1, 1, DRM_BACK_COLOR, __palette4F( 150,210, 141, 0xe0 ) );
    SetOsdCol( 1, 1, DRM_FONT_COLOR, __palette4F( 0, 70, 0,0xff ) );

    #ifdef SUPPORT_SW_OSD_SCALING  // for HD OSD, by robert.chang, 2006-09-28
    if( GET_TV_RESOLUTION()  == HD_720 )
        osd_init_scaling(sizeof( osd_divx_menu_hdr ) / sizeof( _t_osd_hdr ), 1);	
    else if(GET_TV_RESOLUTION()  == HD_1080)
        osd_init_scaling(sizeof( osd_divx_menu_hdr ) / sizeof( _t_osd_hdr ), 2);
    #endif
    
#endif    

    switch( iPage )
    {
    case DRM_DISPLAY_REGISTRATION_CODE:
        
		set_divx_drm_model_id(Divx_drm_modelID);//linrc change for change this ID needn't update fs_mp4.a 2005-8-11 17:15
		//set_divx_drm_model_id(DIVX_DRM_MODEL_ID);		
        generate_registration_code( buffer );
        #ifdef ALCO_PORTABLE//sheny add for alco 11/23
        osd_DrawString( 0, 0, "      DIVX[R] VIDEO ON DEMAND     ", DRM_FONT_COLOR, DRM_BACK_COLOR ); //23 char
        #else
        osd_DrawString( 0, 0, "      -DIVX[R] VIDEO ON DEMAND-     ", DRM_FONT_COLOR, DRM_BACK_COLOR ); //23 char
        #endif
        osd_DrawString( 0, 1, " YOUR REGISTRATION CODE IS:XXXXXXXX", DRM_FONT_COLOR, DRM_BACK_COLOR ); //33 char
        osd_DrawString( 0, 2, "TO LEARN MORE VISIT WWW.DIVX.COM/VOD", DRM_FONT_COLOR, DRM_BACK_COLOR );
        osd_DrawString( 27, 1, buffer, DRM_FONT_COLOR, DRM_BACK_COLOR );
        break;

    case DRM_DISPLAY_AUTHORIZATION_ERROR:

        osd_DrawString( 0, 0, "      -AUTHORIZATION ERROR-         ", DRM_FONT_COLOR, DRM_BACK_COLOR );
        iCode %= 100;
        
        if( iCode == 1 )
        {
            osd_DrawString( 0, 1, "    THIS PLAYER IS NOT AUTHORIZED", DRM_FONT_COLOR, DRM_BACK_COLOR );//19
            osd_DrawString( 0, 2, "         TO PLAY THIS VIDEO.", DRM_FONT_COLOR, DRM_BACK_COLOR );//19
        }
        else if( iCode == 2 )
            osd_DrawString( 0, 2, "       NOT FOR ACTIVATING", DRM_FONT_COLOR, DRM_BACK_COLOR );//18
        else
            osd_DrawString( 0, 2, "       ERROR OR UNSUPPORT", DRM_FONT_COLOR, DRM_BACK_COLOR );//18
        break;

    case DRM_DISPLAY_RENTAL_EXPIRED:
        
        osd_DrawString( 0, 2, "          -RENTAL EXPIRED-          ", DRM_FONT_COLOR, DRM_BACK_COLOR );        //16
        break;

    case DRM_DISPLAY_RENTAL_CONFIRMATION:

        osd_DrawString( 0, 0, "     -VIEW DIVX[R] VOD RENTAL-      ", DRM_FONT_COLOR, DRM_BACK_COLOR );
            
            psprintf( linebuf, "   THIS RENTAL HAS %02d VIEWS LEFT.", iCode % 100 );
        osd_DrawString( 0, 1, linebuf, DRM_FONT_COLOR, DRM_BACK_COLOR );

        osd_DrawString( 0, 2, "     DO YOU WANT TO USE ONE OF", DRM_FONT_COLOR, DRM_BACK_COLOR );
            psprintf( linebuf, "       YOUR %02d VIEWS NOW?", iCode % 100 );
        osd_DrawString( 0, 3, linebuf, DRM_FONT_COLOR, DRM_BACK_COLOR );
        
        osd_DrawString( 10, 4, "[YES]", DRM_BACK_COLOR, DRM_FONT_COLOR );
        osd_DrawString( 22, 4, "[NO]",  DRM_FONT_COLOR, DRM_BACK_COLOR );
        goto DRM_MENU_START;
        break;

    case DRM_DISPLAY_HW_UNSUPPORTED:
    
        osd_DrawString( 0, 2, "        -DIVX DRM UNSUPPORT-        ", DRM_FONT_COLOR, DRM_BACK_COLOR );
        break;

    case DRM_DISPLAY_AES_ONLY:
        
        osd_DrawString( 0, 2, "         -ONLY AES SUPPORT-         ", DRM_FONT_COLOR, DRM_BACK_COLOR );
        break;

    default:
        return -1;
        break;
    }

    osd_DrawString( 15, 4, "[DONE]", DRM_BACK_COLOR, DRM_FONT_COLOR );

DRM_MENU_START:

    full_scrn = DIVX_DRM_MENU;
    
    //Maoyong added for IR U/D/L/R/Sel proc func setting 2004-9-24 10:14
    SetFullscrnCmdFuncPtr( ircmd_null, ircmd_null, divx_func_left,
                                   divx_func_right, divx_func_select);
    int iRet = 0;

    if( iPage != DRM_DISPLAY_REGISTRATION_CODE )
    {
        int iBtnYes = 1;
        
        while( 1 )
        {
            polling();
            
            if( sys_cmd == ( CMD_SELECT | CMD_FUNC_GAME_L ) )
                iBtnYes = 1;
            else if( sys_cmd == ( CMD_SELECT | CMD_FUNC_GAME_R ) )
                iBtnYes = 0;
            else if( sys_cmd == ( CMD_FUNC | CMD_FUNC_SELECT ) )
                break;

            if( iPage == DRM_DISPLAY_RENTAL_CONFIRMATION )
            {
                if( iBtnYes )
                {
                    osd_DrawString( 10, 4, "[YES]", DRM_BACK_COLOR, DRM_FONT_COLOR );
                    osd_DrawString( 22, 4, "[NO]",  DRM_FONT_COLOR, DRM_BACK_COLOR );
                }
                else
                {
                    osd_DrawString( 10, 4, "[YES]", DRM_FONT_COLOR, DRM_BACK_COLOR );
                    osd_DrawString( 22, 4, "[NO]",  DRM_BACK_COLOR, DRM_FONT_COLOR );                    
                }

                iRet = iBtnYes;
            }

            sys_cmd = 0;
        }
    }
    
    return iRet;
}	
#else//#ifndef DRM_UI_FIVE_LANG

    t_osd_str DivxStr1[5][10] = 
{
     {
        { 0, 0, "DIVX VIDEO ON DEMAND" },
        { 0, 1, "REGISTRATION CODE" },
        { 0, 2, "YOUR REGISTRATION CODE IS A ONE TIME" },
        { 0, 3, "CODE USED TO SETUP YOUR VIDEO ON" },
        { 0, 4, "DEMAND ACCOUNT. THIS WILL ALLOW YOU TO"},
        { 0, 5, "PURCHASE AND RENT VIDEOS TO THIS" },
        { 0, 6, "PLAYER. WHEN ASKED FOR YOU" },
        { 0, 7, "REGISTRATION CODE IT IS: " },
        { 0, 8, "" },
        { 0, 0, NULL }
    },
    {
        { 0, 0, "'DIVX-VIDEO AUF ABRUF'" },
        { 0, 1, "REGISTRIERUNGSCODE" },
        { 0, 2, "SIE ERHALTEN EINEN EINMALIGEN CODE."},
        { 0, 3, "MIT DEM SIE IHR 'VIDEO ON DEMAND'-" },
        { 0, 4, "KONTO EINRICHTEN.DAMIT K""\xd6""NNEN SIE" },
        { 0, 5, "DIVX-VIDEOS KAUFEN UND LEIHEN." },
        { 0, 6, "IHR REGISTRIERUNGSCODE LAUTET:" },
        { 0, 7, "" },
        { 0, 8, "" },
        { 0, 0, NULL }
    },
    {
        { 0, 0, "'DIVX-V""\xcd""DEO A LA CARTA'" },
        { 0, 1, "C""\xd3""DIGO DE REGISTRO" },
        { 0, 2, "RECIBE UN ""\xda""NICO C""\xd3""DIGO CON EL QUE"},
        { 0, 3, "PUEDE CONFIGURAR SU CUENTA 'VIDEO ON"},
        { 0, 4, "DEMAND'. DE ESE MODO PUEDE ADQUIRIR O" },
        { 0, 5, "ALQUILAR V""\xcd""DEOS." },
        { 0, 6, "SU C""\xd3""DIGO DE REGISTRO ES:" },
        { 0, 7, "" },
        { 0, 8, "" },
        { 0, 0, NULL }
    },        
    {
        { 0, 0, "'VID""\xc9""O DIVX ""\xc0"" LA DEMANDE'" },
        { 0, 1, "CODE D'ENREGISTREMENT VOTRE CODE ""\xc0"},
        { 0, 2, "UTILISATION UNIQUE VOUS PERMET DE"},
        { 0, 3, "CR""\xc9""ER VOTRE COMPTE 'VID""\xc9""O ""\xc0"" LA "},
        { 0, 4, "DEMANDE'.IL VOUS PERMETTRA D'ACHETER " },
        { 0, 5, "ET DE LOUER DES VID""\xc9""OS DIVX "},
        { 0, 6, "VOTRE CODE 'ENREGISTREMENT :" },
        { 0, 7, ""},
        { 0, 8, "" },
        { 0, 0, NULL }
    },
    {
        { 0, 0, "'VIDEO DIVX SU RICHIESTA' CODICE" },
        { 0, 1, "DI REGISTRAZIONE VIENE FORNITO UN" },
        { 0, 2, "CODICE VALIDO UNA VOLTA PER"},
        { 0, 3, "INSTALLARE IL CONTO 'VIDEO ON DEMAND'"},
        { 0, 4, ".IN TAL MODO ""\xc8"" POSSIBILE" },
        { 0, 5, "COMPRARE E NOLEGGIARE VIDEO DIVX."},
        { 0, 6, "IL SUO CODICE DI REGISTRAZIONE ""\xc8"":" },
        { 0, 7, "" },
        { 0, 8, "" },
        { 0, 0, NULL }
    }
};

    t_osd_str DivxStr2[5][8] = 
{
   {
        { 0, 0, "ACCESS NOT PERMITTED" },
        { 0, 1, "THE DVD PLAYER CAN NOT PLAY THE " },
        { 0, 2, "DISC BECAUSE THERE IS NO REGISTRATION"},
        { 0, 3, "CODE FOR THE DIVX FILE.               "},
        { 0, 4, "  PLEASE REFER TO THE INSTRUCTION  " },
        { 0, 5, "MANUAL FOR MORE INFORMATION        " },
        { 0, 6, "" },
        { 0, 0, NULL }
    },
    {
        { 0, 0, "ZUGRIFFSVERLETZUNG" },
        { 0, 1, "DER DVD-PLAYER KANN DIE DISC NICHT" },
        { 0, 2, "ABSPIELEN.DA F""\xdc""R DIE DIVX-DATEI" },
        { 0, 3, "KEIN REGISTRIERUNGSCODE EXISTIERT." },
        { 0, 4, "N""\xc4""HERE INFORMATIONEN IN DER" },
        { 0, 5, "BEDIENUNGSANLEITUNG.    " },
        { 0, 6, "" },
        { 0, 0, NULL }
    },
     {
        { 0, 0, "INFRACCI""\xd3""N DE ACCESO" },
        { 0, 1, "EI REPRODUCTOR DVD NO PUEDE REPRODUCIR" },
        { 0, 2, "EL DISCO.PUESTO QUE NO EXISTE NING""\xda""N " },
	 	{ 0, 3, "C""\xd3""DIGO DE REGISTRO PARA EL ARCHIVO " },	
	 	{ 0, 4, "DIVX. PARA M""\xc1""S INFORMACI""\xd3""N " },	
	 	{ 0, 5, "CONSULTE EL  MANUAL DE INSTRUCCIONES." },	
	 	{ 0, 6, "" },
        { 0, 0, NULL }
    },
    {
        { 0, 0, "VIOLATION D'ACC""\xc8""S" },
        { 0, 1, "LE LECTEUR DVD NE PEUT PAS LIRE LE" },
        { 0, 2, "DISQUE: AUCUN CODE D'ENREGISTREMENT" },
	 	{ 0, 3, "N'EXISTE POUR LE FICHIER DIVX. DE  " },
	 	{ 0, 4, " PLUS AMPLES INFORMATIONS DANS LE MODE " },
	 	{ 0, 5, " D'EMPLOI.                         " },
	 	{ 0, 6, "" },
        { 0, 0, NULL }
    },
       {
        { 0, 0, "ERRORE DI AUTORIZZAZIONE -IL " },
        { 0, 1, "LETTORE  DVD NON ""\xc8"" AUTORIZZATO " },
        { 0, 2, "A RIPRODURRE QUESTO DISCO.POICH""\xc9" },
        { 0, 3, "ON ESISTE ALCUN CODICE DI RIFERIMENTO" },
        { 0, 4, "PER IL FILE DIVX.PER ULTERIORI " },
        { 0, 5, "INFORMAZIONI CONSULTARE  IL MANUALE " },
        { 0, 6, "DELL'UTENTE. " },
        { 0, 0, NULL }
    }
};
    t_osd_str DivxStr3[5][6] = 
{
    {
    	{ 0, 0, "" },
    	{ 0, 1, "" },
    	{ 0, 2, "" },
        { 0, 3, "RENTAL EXPIRED" },
        { 0, 4, "THIS RENTAL IS EXPIRED." },
        { 0, 0, NULL }
    },
    {
    	{ 0, 0, "" },
    	{ 0, 1, "" },
    	{ 0, 2, "" },
        { 0, 3, "LEIHGEB""\xdc""HR AUSGELAUFEN." },
        { 0, 4, "" },
        { 0, 0, NULL }
    },
    {
    	{ 0, 0, "" },
    	{ 0, 1, "" },
    	{ 0, 2, "" },
        { 0, 3, "ALQUILER CADUCADO." },
        { 0, 4, "" },
        { 0, 0, NULL }
    },
    {
    	{ 0, 0, "" },
    	{ 0, 1, "" },
    	{ 0, 2, "" },
        { 0, 3, "LA LOCATION A EXPIR""\xc9""." },
        { 0, 4, "" },
        { 0, 0, NULL }
    },
    {
    	{ 0, 0, "" },
    	{ 0, 1, "" },
    	{ 0, 2, "" },
        { 0, 3, "NOLEGGIO CONCLUSO" },
        { 0, 4, "" },
        { 0, 0, NULL }
    }
};
//liumzh 2005-5-5 13:54,modify DivxStr4 from t_osd_str to char*,due to it can't work normal
    t_osd_str DivxStr4[] = 
    {
        { 0, 0, "" },
	    { 0, 1, "" },	// "THIS RENTED VIDEO HAS XX"
        { 0, 2, "" },
        { 0, 3, "" },
        { 0, 4, "" },
        { 0, 5, "" },
        { 0, 6, "" },
        { 0, 7, "" },
        { 0, 0, NULL }
    };

char*  Divxstr4_1[5][10] = 
{
	{
	 	"VIEW LIMITED RENTAL",
        "THIS RENTED VIDEO HAS 00",
        "VIEW ENDS WHEN YOU PLAY A DIFFERENT",
        "VIDEO OR TURN OFF YOUR PLAYER. YOU",
        "CAN SEEK PAUSE STOP AS MANY TIMES",
        "AS YOU WANT DURING A VIEW.",
        "DO YOU WANT TO USE ONE OF YOUR USES",
        "NOW?",
        "",
        ""
    },
  	{
        "NUTZUNGSBESCHR""\xc4""NKUNG. SIE K""\xd6""NNEN",
        "DAS LEIH-VIDEO 00 MAL ANSCHAUEN. WENN",
        "SIE DAS GER""\xc4""T AUSSCHALTEN ODER",
        "ZWISCHENDURCH EIN ANDERES VIDEO SEHEN.",
        "IST DAMIT EINE NUTZUNG AUFGEBRAUCHT.",
        "DIE NORMALEN STOPP-. PAUSE- UND",
        "SUCHFUNKTIONEN K""\xd6""NNEN SIE JEDOCH",
        "BELIEBIG OFT VERWENDEN.",
        "M""\xd6""CHTEN SIE DAS VIDEO JETZT SEHEN?" ,
		""
    },
    {
		"LIMITACI""\xd3""N DE USO.PUEDE VER ESTE V""\xcd""DEO" ,
        "00 VECES. SI DURANTE EL VISIONADO",
        "DESCONECTA EL APARATO O MIRA OTRO",
        "V""\xcd""DEO. HABR""\xc1"" CONSUMIDO UNO DE LOS TRES",
        "USOS. SIN EMBARGO. PUEDE UTILIZAR LAS",
        "FUNCIONES NORMALES DE PARADA. PAUSA Y",
        "B""\xda""SQUEDA TANTAS VECES COMO DESEE.",
        "DESEA VER EL V""\xcd""DEO AHORA?" ,
        "",
      	""
    },
    {
	 	"RESTRICTION DUTILISATION.",
        "VOUS POUVEZ VISIONNER 00 FOIS LA",
        "VID""\xc9""O LOU""\xc9""E. EN ""\xc9""TEIGNANT LAPPAREIL" ,
        "OU EN VISIONNANT UNE AUTRE VID""\xc9""O. VOUS",
        "PERDEZ UN DROIT DUTILISATION.",
        "VOUS POUVEZ TOUTEFOIS UTILISER LES",
        "FONCTIONS CLASSIQUES[STOP. PAUSE ET",
        "RECHERCHE]AUTANT DE FOIS QUE SOUHAIT""\xc9"".",
        "VOULEZ-VOUS VISIONNER LA VID""\xc9""O?" ,
	 	""
    },
    {
        "LIMITAZIONE DI USO.",
        "QUESTO VIDEO A NOLEGGIO PU""\xd2"" ESSERE",
        "VISTO PER 00 VOLTE. SE SI SPEGNE",
        "L APPARECCHIO O SI VEDE UN ALTRO",
        "VIDEO SI UTILIZZA UNA DELLE TRE",
        "VOLTE.""\xc8"" POSSIBILE UTILIZZARE LE",
        "NORMALI FUNZIONI DI STOP. PAUSA E",
        "RICERCA TUTTE LE VOLTE CHE SI",
        "DESIDERA. VISUALIZZARE ORA IL VIDEO?",
        ""
    }
};

int osd_divx_drm_display( int iPage, int iCode )
{
    extern BYTE    osd0_state;
    osd0_state = 0;
    t_disp = 0;
    
    t_osd_str DivxStr5[] = 
    {
        { 0, 0, "DIVX DRM UN-SUPPORTED" },
        { 0, 0, NULL }
    };

    t_osd_str DivxStr6[] = 
    {
        { 0, 0, "ONLY AES SUPPORTED" },
        { 0, 0, NULL }
    };
    
	const _t_osd_hdr osd_divx_menu_hdr[] = {
        { 18 * 4, 24, 32, 34, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED },
        { 38 * 8, 28 * 12, 25, 34, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED },
	};
	    
    t_osd_str* pOsdStr = NULL;
    int iCount = 0;
	char buffer[40];
    int i;
	int count_icode;
	int count_line;
	char cert_code[3];
	
	osd_init_regions( sizeof( osd_divx_menu_hdr ) / sizeof( _t_osd_hdr ), (_t_osd_hdr *) &osd_divx_menu_hdr );
   
    switch( iPage )
    {
    case DRM_DISPLAY_REGISTRATION_CODE:
        pOsdStr = DivxStr1[osd_font_mode];
        iCount = sizeof( DivxStr1[osd_font_mode] ) / sizeof( t_osd_str );

		set_divx_drm_model_id(Divx_drm_modelID);//linrc change for change this ID needn't update fs_mp4.a 2005-8-11 17:15
		//set_divx_drm_model_id(DIVX_DRM_MODEL_ID);		
        generate_registration_code( buffer );
 
        // transform from 12345678 to 1234-5678
        //for( i = 8; i > 4; i-- )
        //    buffer[i] = buffer[i-1];
        //buffer[4] = '-';
        buffer[8] = '\0';  //liumzh 2005-4-27 13:39

        DivxStr1[osd_font_mode][8].str = "";//&buffer[0];

		osd_DrawString( 15, 8, buffer, 2, 0 );//liumzh 2005-4-27 13:39
		
		switch(osd_font_mode)
		{
		case 0: osd_DrawString( 16, 9, "[DONE]", 11, 7 );break;
		case 1: osd_DrawString( 15, 9, "[FERTIG]", 11, 7 );break;
		case 2: osd_DrawString( 15, 9, "[LISTO]", 11, 7 );break;
		case 3: osd_DrawString( 16, 9, "[FIN]", 11, 7 );break;
		case 4: osd_DrawString( 13, 9, "[COMPLETATO]", 11, 7 );break;
		default:osd_DrawString( 16, 9, "[DONE]", 11, 7 );break;
		}
		
        //osd_DrawString( 16, 9, "[DONE]", 11, 7 );
        break;
        
    case DRM_DISPLAY_AUTHORIZATION_ERROR:
        {
        pOsdStr = DivxStr2[osd_font_mode];
        
        strcpy(buffer, "REFERENCE CODE XX");
        psprintf(buffer+15, "%02d", iCode%100);
        //pOsdStr[3].str = buffer;

        iCount = sizeof( DivxStr2[osd_font_mode] ) / sizeof( t_osd_str );
        switch(osd_font_mode)
		{
		case 0: osd_DrawString( 16, 9, "[DONE]", 11, 7 );break;
		case 1: osd_DrawString( 15, 9, "[FERTIG]", 11, 7 );break;
		case 2: osd_DrawString( 15, 9, "[LISTO]", 11, 7 );break;
		case 3: osd_DrawString( 16, 9, "[FIN]", 11, 7 );break;
		case 4: osd_DrawString( 13, 9, "[COMPLETATO]", 11, 7 );break;
		default:osd_DrawString( 16, 9, "[DONE]", 11, 7 );break;
		}
        //osd_DrawString( 16, 9, "[DONE]", 11, 7 );
        }
        break;

    case DRM_DISPLAY_RENTAL_EXPIRED:
        pOsdStr = DivxStr3[osd_font_mode];
        iCount = sizeof( DivxStr3[osd_font_mode] ) / sizeof( t_osd_str );
        switch(osd_font_mode)
		{
		case 0: osd_DrawString( 16, 9, "[DONE]", 11, 7 );break;
		case 1: osd_DrawString( 15, 9, "[FERTIG]", 11, 7 );break;
		case 2: osd_DrawString( 15, 9, "[LISTO]", 11, 7 );break;
		case 3: osd_DrawString( 16, 9, "[FIN]", 11, 7 );break;
		case 4: osd_DrawString( 13, 9, "[COMPLETATO]", 11, 7 );break;
		default:osd_DrawString( 16, 9, "[DONE]", 11, 7 );break;
		}
        //osd_DrawString( 16, 9, "[DONE]", 11, 7 );
        break;

    case DRM_DISPLAY_RENTAL_CONFIRMATION:
        {
        pOsdStr = DivxStr4;
        
        strcpy(buffer, "THIS RENTED VIDEO HAS XX");
        psprintf(buffer+22, "%02d", iCode%100);
        //pOsdStr[1].str = buffer;
        
        iCount = sizeof( DivxStr4 ) / sizeof( t_osd_str );

	switch(osd_font_mode)
		{
		case 0: count_icode =29;break;
		case 1: count_icode =15;break;
		case 2: count_icode =2;break;
		case 3: count_icode =25;break;
		case 4: count_icode =13;break;
		default:count_icode=0;break;
		}
	
	for(i=0;i<10;i++)
	osd_DrawString( (38-strlen(Divxstr4_1[osd_font_mode][i]))/2, i, Divxstr4_1[osd_font_mode][i], 11, 0 );
		
		//psprintf(Divxstr4_1[osd_font_mode][1], "%02d", iCode%100);
		if(osd_font_mode==4)
		count_line = 2;
		else
		count_line = 1;
		
		cert_code[2] = '\0';
		psprintf(cert_code, "%02d", iCode%100);

		osd_DrawString( count_icode, count_line, cert_code, 11, 0 );

		switch(osd_font_mode)
		{
		case 0: osd_DrawString( 14, 9, "[YES]", 11, 7 );osd_DrawString( 21, 9, "[NO]",  11, 0 );break;
		case 1: osd_DrawString( 14, 9, "[JA]", 11, 7 );osd_DrawString( 21, 9, "[NEIN]",  11, 0 );break;
		case 2: osd_DrawString( 14, 9, "[SI]", 11, 7 );osd_DrawString( 21, 9, "[NO]",  11, 0 );break;
		case 3: osd_DrawString( 14, 9, "[OUI]", 11, 7 );osd_DrawString( 21, 9, "[NON]",  11, 0 );break;
		case 4: osd_DrawString( 14, 9, "[SI]", 11, 7 );osd_DrawString( 21, 9, "[NO]",  11, 0 );break;
		default:osd_DrawString( 14, 9, "[YES]", 11, 7 );osd_DrawString( 21, 9, "[NO]",  11, 0 );break;
		}
        //osd_DrawString( 14, 9, "[YES]", 11, 7 );
        //osd_DrawString( 21, 9, "[NO]",  11, 0 );
        }
        break;

    case DRM_DISPLAY_HW_UNSUPPORTED:
        pOsdStr = DivxStr5;
        iCount = sizeof( DivxStr5 ) / sizeof( t_osd_str );
        osd_DrawString( 16, 9, "[DONE]", 11, 7 );
        break;

    case DRM_DISPLAY_AES_ONLY:
        pOsdStr = DivxStr6;
        iCount = sizeof( DivxStr6 ) / sizeof( t_osd_str );
        osd_DrawString( 16, 9, "[DONE]", 11, 7 );
        break;

    default:
        return -1;
        break;
    }

    full_scrn = DIVX_DRM_MENU;
    
    //Maoyong added for IR U/D/L/R/Sel proc func setting 2004-9-24 10:14
    SetFullscrnCmdFuncPtr( ircmd_null, ircmd_null, divx_func_left,
                                   divx_func_right, divx_func_select);
    
    // align all lines to center
    for( i = 0; i < iCount - 1; i++ )
    {
        int iLen = strlen( pOsdStr[i].str );
        pOsdStr[i].xst = ( 38 - iLen ) / 2;
    }

    osd_DrawStrings( pOsdStr, 11, 0 );  

    int iRet = 0;

    if( iPage != DRM_DISPLAY_REGISTRATION_CODE )
    {
        int iBtnYes = 1;
        
        while( 1 )
        {
            polling();

            if( sys_cmd == ( CMD_SELECT | CMD_FUNC_GAME_L ) )
                iBtnYes = 1;
            else if( sys_cmd == ( CMD_SELECT | CMD_FUNC_GAME_R ) )
                iBtnYes = 0;
            else if( sys_cmd == ( CMD_FUNC | CMD_FUNC_SELECT ) )
                break;

            if( iPage == DRM_DISPLAY_RENTAL_CONFIRMATION )
            {
            	/*
                osd_DrawString( 14, 9, "[JA]", 11, iBtnYes ? 7 : 0 );
                osd_DrawString( 21, 9, "[NEIN]",  11, iBtnYes ? 0 : 7 );
                */
                //liumzh 2005-5-7 10:19
       switch(osd_font_mode)
		{
		case 0: osd_DrawString( 14, 9, "[YES]", 11, iBtnYes ? 7 : 0 );osd_DrawString( 21, 9, "[NO]",  11, iBtnYes ? 0 : 7 );break;
		case 1: osd_DrawString( 14, 9, "[JA]", 11, iBtnYes ? 7 : 0 );osd_DrawString( 21, 9, "[NEIN]",  11, iBtnYes ? 0 : 7 );break;
		case 2: osd_DrawString( 14, 9, "[SI]", 11, iBtnYes ? 7 : 0 );osd_DrawString( 21, 9, "[NO]",  11, iBtnYes ? 0 : 7 );break;
		case 3: osd_DrawString( 14, 9, "[OUI]", 11, iBtnYes ? 7 : 0 );osd_DrawString( 21, 9, "[NON]",  11, iBtnYes ? 0 : 7 );break;
		case 4: osd_DrawString( 14, 9, "[SI]", 11, iBtnYes ? 7 : 0 );osd_DrawString( 21, 9, "[NO]",  11, iBtnYes ? 0 : 7 );break;
		default:osd_DrawString( 14, 9, "[YES]", 11, iBtnYes ? 7 : 0 );osd_DrawString( 21, 9, "[NO]",  11, iBtnYes ? 0 : 7 );break;
		}
                iRet = iBtnYes;
            }

            sys_cmd = 0;
        }
    }
    
    return iRet;
}	
#endif//#ifndef DRM_UI_FIVE_LANG

#else//#ifndef DRM_SHOW_FOLLOW_OSD_LANGUAGE_SET
//xujf-060420-modify for select osd language
EXTERN t_osd_str DivxStrn[N_OSD_LANGS][16];
int osd_divx_drm_display( int iPage, int iCode )
{
	char buffer[20];
    #define DRM_FONT_COLOR          1
    #define DRM_BACK_COLOR          0

    extern BYTE    osd0_state;
    osd0_state = 0;
    t_disp = 0;

#ifdef NEW_OSD_DRIVER

    #ifdef OSD_SUPPORT_2_COLOR  // 2005/06/18 yltseng
	const _t_osd_hdr osd_divx_menu_hdr[] = {
        { 36 * 4 * 4, 32 * 5, 32, 80, SIMPLE_HEADER, OSD_FORMAT_2COLOR,  OSD_INTERLACED },
	};
    #else
	const _t_osd_hdr osd_divx_menu_hdr[] = {
        { 36 * 4 * 4, 32 * 5, 32, 80, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED },
	};
    #endif
    
    #ifdef SDRAM_16Mb_Mode
    regs0->osd_base_addr=OSD_BASE_USE_ADDR;
    #endif
    
	osd_init_regions( sizeof( osd_divx_menu_hdr ) / sizeof( _t_osd_hdr ), (_t_osd_hdr *) &osd_divx_menu_hdr );
	osd_set_palette_color( 0, DRM_BACK_COLOR, __palette4F( 150,210, 141, 0xe0 ) );
	osd_set_palette_color( 0, DRM_FONT_COLOR, __palette4F( 0, 70, 0,0xff ) );

    osd_tog_region( 0, OSD_ON );
#else

    extern void osd_init_regions(int n, const _t_osd_hdr *hdrp);
    
	const _t_osd_hdr osd_divx_menu_hdr[] = {
        { 18 * 4, 24, 32, 34, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED },
        { 36 * 8, 32 * 5, 32, 80, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED },
	};

	osd_init_regions( sizeof( osd_divx_menu_hdr ) / sizeof( _t_osd_hdr ), (_t_osd_hdr *) &osd_divx_menu_hdr );

    SetOsdCol( 1, 1, DRM_BACK_COLOR, __palette4F( 150,210, 141, 0xe0 ) );
    SetOsdCol( 1, 1, DRM_FONT_COLOR, __palette4F( 0, 70, 0,0xff ) );
#endif    

    switch( iPage )
    {
    case DRM_DISPLAY_REGISTRATION_CODE:
        
		set_divx_drm_model_id(Divx_drm_modelID);//linrc change for change this ID needn't update fs_mp4.a 2005-8-11 17:15
		//set_divx_drm_model_id(DIVX_DRM_MODEL_ID);		
        generate_registration_code( buffer );		
	    osd_DrawString( DivxStrn[osd_font_mode][0].xst, DivxStrn[osd_font_mode][0].yst, DivxStrn[osd_font_mode][0].str, DRM_FONT_COLOR, DRM_BACK_COLOR ); //23 char
        osd_DrawString( DivxStrn[osd_font_mode][1].xst, DivxStrn[osd_font_mode][1].yst, DivxStrn[osd_font_mode][1].str, DRM_FONT_COLOR, DRM_BACK_COLOR ); //33 char
        osd_DrawString( DivxStrn[osd_font_mode][2].xst, DivxStrn[osd_font_mode][2].yst, DivxStrn[osd_font_mode][2].str, DRM_FONT_COLOR, DRM_BACK_COLOR );
        osd_DrawString( 27, 1, buffer, DRM_FONT_COLOR, DRM_BACK_COLOR );
        break;

    case DRM_DISPLAY_AUTHORIZATION_ERROR:

        osd_DrawString( DivxStrn[osd_font_mode][3].xst, DivxStrn[osd_font_mode][3].yst, DivxStrn[osd_font_mode][3].str, DRM_FONT_COLOR, DRM_BACK_COLOR );
        iCode %= 100;
        
        if( iCode == 1 )
        {
            osd_DrawString( DivxStrn[osd_font_mode][4].xst, DivxStrn[osd_font_mode][4].yst, DivxStrn[osd_font_mode][4].str, DRM_FONT_COLOR, DRM_BACK_COLOR );//19
            osd_DrawString( DivxStrn[osd_font_mode][5].xst, DivxStrn[osd_font_mode][5].yst, DivxStrn[osd_font_mode][5].str, DRM_FONT_COLOR, DRM_BACK_COLOR );//19
        }
        else if( iCode == 2 )
            osd_DrawString( DivxStrn[osd_font_mode][6].xst, DivxStrn[osd_font_mode][6].yst, DivxStrn[osd_font_mode][6].str, DRM_FONT_COLOR, DRM_BACK_COLOR );//18
        else
            osd_DrawString( DivxStrn[osd_font_mode][7].xst, DivxStrn[osd_font_mode][7].yst, DivxStrn[osd_font_mode][7].str, DRM_FONT_COLOR, DRM_BACK_COLOR );//18
        break;

    case DRM_DISPLAY_RENTAL_EXPIRED:
        
        osd_DrawString( DivxStrn[osd_font_mode][8].xst, DivxStrn[osd_font_mode][8].yst, DivxStrn[osd_font_mode][8].str, DRM_FONT_COLOR, DRM_BACK_COLOR );        //16
        break;

    case DRM_DISPLAY_RENTAL_CONFIRMATION:

        osd_DrawString( DivxStrn[osd_font_mode][9].xst, DivxStrn[osd_font_mode][9].yst,DivxStrn[osd_font_mode][9].str, DRM_FONT_COLOR, DRM_BACK_COLOR );
            
            psprintf( linebuf, "   THIS RENTAL HAS %02d VIEWS LEFT.", iCode % 100 );
        osd_DrawString( 0, 1, linebuf, DRM_FONT_COLOR, DRM_BACK_COLOR );

        osd_DrawString( DivxStrn[osd_font_mode][10].xst, DivxStrn[osd_font_mode][10].yst, DivxStrn[osd_font_mode][10].str, DRM_FONT_COLOR, DRM_BACK_COLOR );
            psprintf( linebuf, "       YOUR %02d VIEWS NOW?", iCode % 100 );
        osd_DrawString( 0, 3, linebuf, DRM_FONT_COLOR, DRM_BACK_COLOR );
        
        osd_DrawString( DivxStrn[osd_font_mode][11].xst, DivxStrn[osd_font_mode][11].yst, DivxStrn[osd_font_mode][11].str, DRM_BACK_COLOR, DRM_FONT_COLOR );
        osd_DrawString( DivxStrn[osd_font_mode][12].xst, DivxStrn[osd_font_mode][12].yst, DivxStrn[osd_font_mode][12].str,  DRM_FONT_COLOR, DRM_BACK_COLOR );
        goto DRM_MENU_START;
        break;

    case DRM_DISPLAY_HW_UNSUPPORTED:
    
        osd_DrawString( DivxStrn[osd_font_mode][13].xst, DivxStrn[osd_font_mode][13].yst, DivxStrn[osd_font_mode][13].str, DRM_FONT_COLOR, DRM_BACK_COLOR );
        break;

    case DRM_DISPLAY_AES_ONLY:
        
        osd_DrawString( DivxStrn[osd_font_mode][14].xst, DivxStrn[osd_font_mode][14].yst, DivxStrn[osd_font_mode][14].str, DRM_FONT_COLOR, DRM_BACK_COLOR );
        break;

    default:
        return -1;
        break;
    }

    osd_DrawString( DivxStrn[osd_font_mode][15].xst, DivxStrn[osd_font_mode][15].yst, DivxStrn[osd_font_mode][15].str, DRM_BACK_COLOR, DRM_FONT_COLOR );

DRM_MENU_START:

    full_scrn = DIVX_DRM_MENU;
    
    //Maoyong added for IR U/D/L/R/Sel proc func setting 2004-9-24 10:14
    SetFullscrnCmdFuncPtr( ircmd_null, ircmd_null, divx_func_left,
                                   divx_func_right, divx_func_select);
    int iRet = 0;

    if( iPage != DRM_DISPLAY_REGISTRATION_CODE )
    {
        int iBtnYes = 1;
        
        while( 1 )
        {
            polling();

            if( sys_cmd == ( CMD_SELECT | CMD_FUNC_GAME_L ) )
                iBtnYes = 1;
            else if( sys_cmd == ( CMD_SELECT | CMD_FUNC_GAME_R ) )
                iBtnYes = 0;
            else if( sys_cmd == ( CMD_FUNC | CMD_FUNC_SELECT ) )
                break;

            if( iPage == DRM_DISPLAY_RENTAL_CONFIRMATION )
            {
                if( iBtnYes )
                {
                    osd_DrawString( DivxStrn[osd_font_mode][11].xst, DivxStrn[osd_font_mode][11].yst, DivxStrn[osd_font_mode][11].str, DRM_BACK_COLOR, DRM_FONT_COLOR );
                    osd_DrawString( DivxStrn[osd_font_mode][12].xst, DivxStrn[osd_font_mode][12].yst, DivxStrn[osd_font_mode][12].str,  DRM_FONT_COLOR, DRM_BACK_COLOR );
                }
                else
                {
                    osd_DrawString( DivxStrn[osd_font_mode][11].xst, DivxStrn[osd_font_mode][11].yst, DivxStrn[osd_font_mode][11].str, DRM_FONT_COLOR, DRM_BACK_COLOR );
                    osd_DrawString( DivxStrn[osd_font_mode][12].xst, DivxStrn[osd_font_mode][12].yst, DivxStrn[osd_font_mode][12].str,  DRM_BACK_COLOR, DRM_FONT_COLOR );                    
                }

                iRet = iBtnYes;
            }

            sys_cmd = 0;
        }
    }
    
    return iRet;
}
#endif//#ifndef DRM_SHOW_FOLLOW_OSD_LANGUAGE_SET

#endif//#ifdef DIVX_DRM


