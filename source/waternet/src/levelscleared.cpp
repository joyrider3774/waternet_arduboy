#include <stdint.h>

#include "helperfuncs.h"
#include "commonvars.h"
#include "printfuncs.h"
#include "sound.h"
#include "level.h"

#include "../res/congratsscreentiles.h"
#include "../res/congratsscreenmap.h"

void initLevelsCleared()
{
    set_bkg_data(congratsScreenTiles);
    arduboy.clear();
    arduboy.drawCompressed(0, 0, congratsMap);
    if(difficulty == diffVeryEasy)
    {
        printCongratsScreen(0, 3, F("VERY EASY LEVELS"));
    }
    if(difficulty == diffEasy)
    {
        printCongratsScreen(3, 3, F("EASY LEVELS"));
    }
    if(difficulty == diffNormal)
    {
        printCongratsScreen(2, 3, F("NORMAL LEVELS"));
    }
    if(difficulty == diffHard)
    {
        printCongratsScreen(3, 3, F("HARD LEVELS"));
    }
    if(difficulty == diffVeryHard)
    {
        printCongratsScreen(0, 3, F("VERY HARD LEVELS"));
    }
    SelectMusic(musAllLevelsClear);
}

void levelsCleared() 
{  
    if(gameState == gsInitLevelsCleared)
    {
        initLevelsCleared();
        gameState -= gsInitDiff;
    }
       
    if (arduboy.justReleased(A_BUTTON) || 
        arduboy.justReleased(B_BUTTON)) 
    {
        playMenuAcknowlege();
        titleStep = tsMainMenu;
        gameState = gsInitTitle;
    }
}