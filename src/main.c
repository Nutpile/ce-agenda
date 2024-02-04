#include <sys/rtc.h>
#include <graphx.h>
#include <ti/getcsc.h>

void drawstatusbar()
{
    uint8_t day = 0;
    uint8_t month = 0;
    uint16_t year = 0;
    gfx_SetTextXY(5, 4);
    gfx_SetColor(195);
    gfx_FillRectangle_NoClip(0, 0, 320, 15);
    if(!rtc_IsBusy()){
        gfx_PrintUInt(rtc_Hours, 2);
        gfx_PrintChar(*":");
        gfx_PrintUInt(rtc_Minutes, 2);
        gfx_SetTextXY(235, 4);
        boot_GetDate(&day, &month, &year);
        gfx_PrintUInt(day, 2);
        gfx_PrintChar(*"/");
        gfx_PrintUInt(month, 2);
        gfx_PrintChar(*"/");
        gfx_PrintUInt(year, 4);
    }
}

int main()
{
    gfx_Begin();
    uint8_t barupdate = -1;
    while(!os_GetCSC()){
        if (barupdate != rtc_Minutes){
            drawstatusbar(); 
            barupdate = rtc_Minutes;
        }
    }
    gfx_End();
    return 0;
}
