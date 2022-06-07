 #include <stdint.h>
#include <Arduboy2.h>

#include "helperfuncs.h"
#include "commonvars.h"
#include "printfuncs.h"
#include "sound.h"

#include "../res/titlescreenmap.h"
#include "../res/blocktiles.h"

uint16_t frames = 0;
float titlePosY = 8*8;
constexpr uint8_t FRAMEDELAY = 16 * FRAMERATE / 15;    

void initIntro()
{
    set_bkg_data(blockTiles);   
}

void intro() 
{
    if (gameState == gsInitIntro)
    {
        initIntro();
        gameState -= gsInitDiff;
    }
    
    frames++;
    arduboy.clear();
    if (frames < FRAMEDELAY)
    {
        printMessage((16-12) >> 1, 4, F("WILLEMS DAVY"));
    }
    else
    {
        if (frames < FRAMEDELAY *2)
        {
            printMessage((16-8) >> 1, 4, F("PRESENTS"));
        }
        else
        {
            set_bkg_tiles(0, (uint8_t)titlePosY, titlescreenMap);
            if(titlePosY > 0)
            {
                titlePosY -= (float)30/(float)FRAMERATE;
            }
            else
            {
                gameState = gsInitTitle;
            }
        }
    }
    
    if (arduboy.justReleased(A_BUTTON) || 
        arduboy.justReleased(B_BUTTON)) 
    {            
        gameState = gsInitTitle;
    }
    if(arduboy.justReleased(UP_BUTTON))
    {
        debugMode = 1;
    }
}
