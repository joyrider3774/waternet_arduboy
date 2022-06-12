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
        if (number[c] == '\0')
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
            if (number[c] == '\0')
                break;

            set_bkg_tile_xy(c + (3 - len), 0, number[c] + 32);
        }
        
        //restore the previous tiles
        set_bkg_data(tiles);
    }
}

//print a message on the title screen on ax,ay, the tileset from titlescreen contains an alphabet
void printMessage(uint8_t ax, uint8_t ay, const __FlashStringHelper* amsg)
{
    // based on input from @Pharap
    PGM_P p = reinterpret_cast<PGM_P>(amsg);
    size_t index = 0;
    uint8_t goOn = 1;

    while (goOn)
    {
        char fChar = pgm_read_byte(p++);

        switch (fChar)
        { 
            case '\0':
                goOn = 0;
                break;

            case ' ':
                set_bkg_tile_xy(ax + index, ay, 61U);
                break;

            case 'A' ... 'Z':
                set_bkg_tile_xy(ax + index, ay, fChar + 25U);
                break;

            case '0' ... '9':
                set_bkg_tile_xy(ax + index, ay, fChar + 32U);
                break;

            case '[':
                set_bkg_tile_xy(ax + index, ay, 70U);
                break;

            case ']':
                set_bkg_tile_xy(ax + index, ay, 64U);
                break;

            case '<':
                set_bkg_tile_xy(ax + index, ay, 73U);
                break;

            case '>':
                set_bkg_tile_xy(ax + index, ay, 67U);
                break;

            case '+':
                set_bkg_tile_xy(ax + index, ay, 63U);
                break;

            case '*':
                set_bkg_tile_xy(ax + index, ay, 62U);
                break;

            case '|':
                set_bkg_tile_xy(ax + index, ay, 69U);
                break;

            case '#':
                set_bkg_tile_xy(ax + index, ay, 65U);
                break;

            case ':':
                set_bkg_tile_xy(ax + index, ay, 116U);
                break;

            case 'a':
                set_bkg_tile_xy(ax + index, ay, 119U);
                break;

            case 'b':
                set_bkg_tile_xy(ax + index, ay, 117U);
                break;
        }
        index++;
    }
}

//print a message on the CongratsScreen on ax,ay, the tileset from Congrats Screen contains an alphabet in another font
void printCongratsScreen(uint8_t ax, uint8_t ay, const __FlashStringHelper* amsg)
{
    // based on input form @Pharap
    PGM_P p = reinterpret_cast<PGM_P>(amsg);
    size_t index = 0;
    uint8_t goOn = 1;

    while (goOn)
    {
        char fChar = pgm_read_byte(p++);

        switch (fChar) 
        {
            case '\0':
                goOn = 0;
                break;

            case ' ':
                set_bkg_tile_xy(ax + index, ay, 26);
                break;

            case 'A' ... 'Z':
                set_bkg_tile_xy(ax + index, ay, fChar - 'A');
                break;
        }
        index++;
    }
}