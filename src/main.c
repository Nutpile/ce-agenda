/*MIT License

Copyright (c) 2024 Valerio "Nutpile" Casalino

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

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
