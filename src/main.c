#include <sys/rtc.h>
#include <graphx.h>
#include <ti/getcsc.h>

int main()
{
    gfx_Begin();
    gfx_SetTextScale(5, 5);
    gfx_SetTextXY(30, 20);
    if(!rtc_IsBusy()){
         gfx_PrintUInt(rtc_Hours, 2);
         gfx_PrintChar(*":");
         gfx_PrintUInt(rtc_Minutes, 2);
    }
    while(!os_GetCSC());
    gfx_End();
    return 0;
}
