#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "commonvars.h"
#include "printfuncs.h"
#include "helperfuncs.h"

//print a number on levelselect or game screen
void printNumber(uint8_t ax, uint8_t ay, uint16_t aNumber, uint8_t maxDigits)
{
    char number[10];
    itoa(aNumber, number, 10);

    uint8_t digits = strlen(number);
    for (uint8_t c=0; c < maxDigits; c++)
    {
        if (number[c] == 0)
            break;

        set_bkg_tile_xy(ax + (maxDigits - digits) + c, ay, number[c] + 32);
    }
}

void printDebug(uint8_t ax, uint8_t ay, const __FlashStringHelper* amsg)
 {
    if(debugMode)
    {
        //rememvber current tiles
        const unsigned char* tiles = get_bkg_data();
        setBlockTilesAsBackground();
        arduboy.clear();
        printMessage(ax, ay, amsg);
        arduboy.display();
        arduboy.delayShort(2500);
        //restore the previous tiles
        set_bkg_data(tiles);
    }
 }

//print a cpuload debug message anywhere on ax,ay using title tiles
void printDebugCpuLoad()    
{
    if(debugMode)
    {
        //rememvber current tiles
        const unsigned char* tiles = get_bkg_data();
        setBlockTilesAsBackground();
        
        //get cpuload
        char number[10];
        int load = arduboy.cpuLoad();
        itoa(load, number, 10);

        //get digits
        size_t len = strlen(number);
        if (len > 3)
            len = 3;

        //clear space for max 3 digits (i assume 100 is max or at least 999)
        arduboy.fillRect(0, 0, 3*8, 8, BLACK);
        
        //print load
        for (uint8_t c = 0; c < 3; c++)
        {
            if (number[c] == 0)
                break;

            set_bkg_tile_xy(c + (3 - len), 0, number[c] + 32);
        }
        
        //restore the previous tiles
        set_bkg_data(tiles);
    }
}

#define setTileAndContinue(ax, ay, tilenr) set_bkg_tile_xy(ax, ay, tilenr); continue;

//print a message on the title screen on ax,ay, the tileset from titlescreen contains an alphabet
void printMessage(uint8_t ax, uint8_t ay, const __FlashStringHelper* amsg)
{
    char fChar;
    size_t len = strlen_P((PGM_P)amsg);
    for (size_t c = 0; c < len; c++)
    {
        memccpy_P(&fChar, (PGM_P)amsg + c, 0, 1);
        if(fChar == 0)
            break;

        if (fChar == ' ')
        {
            setTileAndContinue(ax + c, ay, 61);
        }

        //A-Z
        if ((fChar >= 'A') && (fChar <= 'Z'))
        {
            setTileAndContinue(ax + c, ay, fChar + 25);
        }

        //0-9
        if ((fChar >= '0') && (fChar <= '9'))
        {
            setTileAndContinue(ax + c, ay, fChar + 32);
        }

        if (fChar == '[')
        {
            setTileAndContinue(ax + c, ay, 70);
        }
  
        if (fChar == ']')
        {
            setTileAndContinue(ax + c, ay, 64);
        }
  
        if (fChar == '<')
        {
            setTileAndContinue(ax + c, ay, 73);
        }
    
        if (fChar == '>')
        {
            setTileAndContinue(ax + c, ay, 67);
        }

        if (fChar == '+')
        {
            setTileAndContinue(ax + c, ay, 63);
        }

        if (fChar == '*')
        {
            setTileAndContinue(ax + c, ay, 62);
        }
     
        if (fChar == '|')
        {
            setTileAndContinue(ax + c, ay, 69);
        }
        
        if (fChar == '#')
        {
            setTileAndContinue(ax + c, ay, 65);
        }
        
        if (fChar == ':')
        {
            setTileAndContinue(ax + c, ay, 116);
        }
      
        if (fChar == 'a')
        {
            setTileAndContinue(ax + c, ay, 119);
        }
        
        if (fChar == 'b')
        {
            setTileAndContinue(ax + c, ay, 117);
        }
    }
}

//print a message on the CongratsScreen on ax,ay, the tileset from Congrats Screen contains an alphabet in another font
void printCongratsScreen(uint8_t ax, uint8_t ay, const __FlashStringHelper* amsg)
{
    char fChar;
    size_t len = strlen_P((PGM_P)amsg);
    for (size_t c = 0; c < len; c++)
    {
        memccpy_P(&fChar, (PGM_P)amsg + c, 0, 1);
        if (fChar == 0)
            break;

        if (fChar == ' ')
        {
            setTileAndContinue(ax + c, ay, 26);
        }

        if ((fChar >= 'A') && (fChar <= 'Z'))
        {
            setTileAndContinue(ax + c, ay, fChar-65);
        }
    }
}