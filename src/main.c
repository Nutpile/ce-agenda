#include <sys/rtc.h>
#include <ti/screen.h>
#include <ti/getcsc.h>

int main()
{
    while(!os_GetCSC()){
        os_ClrHome();
        os_DisableCursor();
        if(!rtc_IsBusy()){
            os_PutStrFull(rtc_Time());
        }
    }
    return 0;
}
