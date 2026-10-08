#ifndef _HDMI_API_H
#define _HDMI_API_H
typedef enum{
    HDMI_STATE_NO_RX,
    HDMI_STATE_HDCP_AUTH,
    HDMI_STATE_HDCP_FAIL,
} t_HDMI_State;
void ResetAuthentStates(void);
void HDCP_polling(void);
//void UpDateHDMI_StateDisplay(void);
t_HDMI_State HDMI_State(void);
#endif//_HDMI_API_H

