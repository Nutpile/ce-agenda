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
#include <fileioc.h>

void drawstatusbar(void)
{
    uint8_t day = 0;
    uint8_t month = 0;
    uint16_t year = 0;
    gfx_SetTextXY(5, 8);
    gfx_SetColor(195);
    gfx_FillRectangle_NoClip(0, 0, 320, 22);
    gfx_SetColor(255);
    gfx_Rectangle_NoClip(1, 1, 318, 20);
    if(!rtc_IsBusy()){
        gfx_PrintUInt(rtc_Hours, 2);
        gfx_PrintChar(*":");
        gfx_PrintUInt(rtc_Minutes, 2);
        gfx_SetTextXY(235, 8);
        boot_GetDate(&day, &month, &year);
        gfx_PrintUInt(day, 2);
        gfx_PrintChar(*"/");
        gfx_PrintUInt(month, 2);
        gfx_PrintChar(*"/");
        gfx_PrintUInt(year, 4);
    }
}

void filedecode(void)
{
    char date[17] = "";
    char msg[33] = "";
    uint8_t AVid = 0;
    AVid = ti_Open("AgendaAV", "r");
    if(AVid == 0){
        gfx_End();
        exit(1);
    }
    ti_Rewind(AVid);
    gfx_SetColor(0);
    for(int i = 30; i < 200; i+=30){
        ti_Read(date, 17, 1, AVid);
        ti_Read(msg, 33, 1, AVid);
        gfx_PrintStringXY(date, 4, i);
        gfx_PrintStringXY(msg, 4, i+10);
        gfx_HorizLine_NoClip(0, i+20, 320);
    }
    ti_Close(AVid);
    AVid = 0;
}

int main(void)
{
    gfx_Begin();
    //temp code! for testing only, delete later.
    uint8_t AVid = 0;
    AVid = ti_Open("AgendaAV", "w");
    ti_Write(&"09/09/2009 05:27", 17, 1, AVid);
    ti_Write(&"Hi if you see this msg it worked", 33, 1, AVid);
    ti_Write(&"06/06/2012 12:12", 17, 1, AVid);
    ti_Write(&"shorter string test", 33, 1, AVid);
    ti_Close(AVid);
    //end of temp code
    filedecode();
    //draws bottom bar
    gfx_SetColor(195);
    gfx_FillRectangle_NoClip(0, 223, 320, 17);
    gfx_SetColor(255);
    gfx_Rectangle_NoClip(0, 224, 318, 15);
    gfx_PrintStringXY("Add", 4, 228);
    gfx_PrintStringXY("Exit", 288, 228);

    uint8_t barupdate = -1;
    while(os_GetCSC() != sk_Graph){
        if (barupdate != rtc_Minutes){
            drawstatusbar(); 
            barupdate = rtc_Minutes;
        }
    }
    gfx_End();
    return 0;
}
