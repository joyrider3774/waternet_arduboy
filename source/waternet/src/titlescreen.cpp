#include <stdint.h>
#include <time.h>
#include <Arduboy2.h>

#include "../res/titlescreenmap.h"
#include "commonvars.h"
#include "helperfuncs.h"
#include "sound.h"
#include "printfuncs.h"
#include "savestate.h"
#include "level.h"

void drawTitleScreen()
{
    arduboy.clear();
    set_bkg_tiles(0, 0, titlescreenMap);

    if (titleStep == tsMainMenu)
    {
        printMessage(5, 4, F("START"));
        printMessage(5, 5, F("HELP"));
        printMessage(5, 6, F("OPTIONS"));
        printMessage(5, 7, F("CREDITS"));
    }
    else
    {
        if (titleStep == tsDifficulty)
        {
            printMessage(3, 3, F("VERY EASY"));
            printMessage(3, 4, F("EASY"));
            printMessage(3, 5, F("NORMAL"));
            printMessage(3, 6, F("HARD"));
            if(difficulty <= diffVeryHard)
            {
                printMessage(3, 7, F("VERY HARD"));
            }
            else
            {
                printMessage(3, 7, F("RANDOM"));
            }
        }
        else
        {
            if (titleStep == tsGameMode)
            {
                printMessage(5, 4, F("ROTATE"));
                printMessage(5, 5, F("SLIDE"));
                printMessage(5, 6, F("ROSLID"));

            }
            else
            {
                if (titleStep == tsCredits)
                {
                    printMessage(3, 5, F("CREATED BY"));
                    printMessage(2, 6, F("WILLEMS DAVY"));
                    printMessage(2, 7, F("JOYRIDER3774"));
                }
                else
                {
                    if(isMusicOn())
                    {
                        printMessage(4, 4, F("MUSIC ON"));
                    }
                    else
                    {
                        printMessage(4, 4, F("MUSIC OFF"));
                    }

                    if(isSoundOn())
                    {
                        printMessage(4, 5, F("SOUND ON"));
                    }
                    else
                    {
                        printMessage(4, 5, F("SOUND OFF"));
                    }

                }
            }
        }
    }

    //set menu tile
    if (titleStep == tsMainMenu)
    {
        set_bkg_tile_xy(4, 4 + mainMenu, leftMenu); 
    }
    else
    {
        //set menu tile
        if (titleStep == tsGameMode)
        {
            set_bkg_tile_xy(4, 4 + gameMode, leftMenu); 
        }
        else
        {
            if(titleStep == tsDifficulty)
            {
                if(difficulty >= diffVeryHard)
                {
                    set_bkg_tile_xy(2, 7, leftMenu);
                }
                else
                {
                    set_bkg_tile_xy(2, 3 + difficulty, leftMenu);
                }
            }
            else
            {
                if(titleStep == tsOptions)
                {
                    set_bkg_tile_xy(2, 4 + option, leftMenu);
                }    
            }
        }    
    }
}

void initTitleScreen()
{   
    setBlockTilesAsBackground();
    SelectMusic(musTitle);
    needRedraw = 1;
}

void titleScreen()
{
    if(gameState == gsInitTitle)
    {
        initTitleScreen();
        gameState -= gsInitDiff;
    }
    
    if(needRedraw)
    {
        drawTitleScreen();
        needRedraw = 0;
    }

    if (arduboy.justReleased(UP_BUTTON))
    {
        if (titleStep == tsMainMenu)
        {
            if(mainMenu > mmStartGame)
            {
                playMenuSelectSound();
                mainMenu--;
                needRedraw = 1;
            }
        } 
        else
        {
            if (titleStep == tsGameMode)
            {
                if(gameMode > gmRotate)
                {
                    playMenuSelectSound();
                    gameMode--;
                    needRedraw = 1;
                }
            } 
            else
            {
                if(titleStep == tsDifficulty)
                {
                    if(difficulty > diffVeryEasy)
                    {
                        playMenuSelectSound();
                        difficulty--;
                        needRedraw = 1;
                    }
                }
                else
                {
                    if(titleStep == tsOptions)
                    {
                        if(option > opMusic)
                        {
                            playMenuSelectSound();
                            option--;
                            needRedraw = 1;
                        }
                    }
                }
            }
        }
    }

    if (arduboy.justReleased(DOWN_BUTTON))
    {
        if (titleStep == tsMainMenu)
        {
            if(mainMenu < mmCount-1)
            {
                playMenuSelectSound();
                mainMenu++;
                needRedraw = 1;
            }
        }
        else
        {
            if (titleStep == tsGameMode)
            {
                if(gameMode < gmCount-1)
                {
                    playMenuSelectSound();
                    gameMode++;
                    needRedraw = 1;
                }
            } 
            else
            {
                if(titleStep == tsDifficulty)
                {
                    if(difficulty < diffCount-1)
                    {
                        playMenuSelectSound();
                        difficulty++;
                        needRedraw = 1;
                    }
                }
                else
                {
                    if(titleStep == tsOptions)
                    {
                        if(option < opCount-1)
                        {
                            playMenuSelectSound();
                            option++;
                            needRedraw = 1;
                        }
                    }
                }
            }
        }
    }

    if (arduboy.justReleased(B_BUTTON))
    {
        if ((titleStep == tsOptions) ||
            (titleStep == tsCredits))
        {
            titleStep = tsMainMenu;
            playMenuBackSound();
            needRedraw = 1;
        }
        else
        {
            if (titleStep > tsMainMenu)
            {
                titleStep--;
                playMenuBackSound();
                needRedraw = 1;
            }
        }
    }

    if (arduboy.justReleased(A_BUTTON))
    {
        playMenuAcknowlege();
        if (mainMenu == mmOptions)
        {
            if(titleStep != tsOptions)
            {
                titleStep = tsOptions;
                needRedraw = 1;
            }
            else
            {
                switch(option)
                {
                    case opMusic:
                        setMusicOn(!isMusicOn());
                        setMusicOnSaveState(isMusicOn());
                        needRedraw = 1;
                        break;
                    case opSound:
                        setSoundOn(!isSoundOn());
                        setSoundOnSaveState(isSoundOn());
                        needRedraw = 1;
                        break;
                }
            }
        }

        if (mainMenu == mmCredits)
        {
            if(titleStep != tsCredits)
            {
                titleStep = tsCredits;
                needRedraw = 1;
            }
            else
            {
                titleStep = tsMainMenu;
                needRedraw = 1;
            }
        }

        if(mainMenu == mmHelp)
        {
            if (titleStep < tsGameMode)
            {
                titleStep++;
                needRedraw = 1;
            }
            else
            {
                switch (gameMode)
                {
                    case gmRotate:
                        gameState = gsInitHelpRotate;
                        break;
                    case gmSlide:
                        gameState = gsInitHelpSlide;
                        break;
                    case gmRotateSlide:
                        gameState = gsInitHelpRotateSlide;
                        break; 
                }
            }
        }

        if(mainMenu == mmStartGame)
        {
        
            if (titleStep < tsDifficulty)
            {
                titleStep++;
                needRedraw = 1;
            }
            else
            {
                if (difficulty == diffRandom)
                {
                    selectedLevel = 1;
                }
                else
                {
                    selectedLevel = lastUnlockedLevel(gameMode, difficulty);
                }
                
                if (gameMode == gmRotate)
                {
                    posAdd = 0;
                }
                else
                {
                    posAdd = 1;
                }
                //set randomseet to systime here
                //it will be reused all the time
                //with the level generating
                //but not when going back from
                //level playing to level selector
                //when calling init level there
                randomSeedGame = arduboy.generateRandomSeed();
                initLevel(randomSeedGame);

                gameState = gsInitLevelSelect;                   
            } 
        }  
    }
}
