#include <stdint.h>
#include <string.h>
#include <ArduboyTonesPitches.h>
#include <Arduboy2Beep.h>

#include "commonvars.h"
#include "sound.h"
#include "savestate.h"


//I (joyrider3774) created the music in this tool : https://onlinesequencer.net
//and used this page to convert notes to frequencies for gameboy: http://www.devrs.com/gb/files/sndtab.html
//music uses channel 2 only using simple notes
//sound uses channel 1 only

uint8_t prev_music = 0, music_on = 0, sound_on = 0;
BeepPin2 beep;


constexpr uint8_t PAUSE = 250U;
constexpr uint8_t PAUSE2 = 100U;
constexpr uint8_t PAUSE3 = 233U;
constexpr uint8_t PAUSE4 = 216U;

//https://onlinesequencer.net/2498607
const uint16_t PROGMEM music_levelsCleared[] ={
    NOTE_D6,PAUSE4,
    NOTE_DS6,PAUSE4,
    NOTE_D6,PAUSE4,
    NOTE_REST,PAUSE4,
    NOTE_D6,PAUSE4,
    NOTE_E6,PAUSE4,
    NOTE_F6,PAUSE4,
    NOTE_E6,PAUSE4,
    NOTE_E6,PAUSE4,
    NOTE_E6,PAUSE4,
    NOTE_D6,PAUSE4,
    NOTE_REST,PAUSE4,
    NOTE_DS6,PAUSE4,
    NOTE_E6,PAUSE4,
    NOTE_DS6,PAUSE4,
    NOTE_REST,PAUSE4,
    NOTE_E6,PAUSE4,
    NOTE_F6,PAUSE4,
    NOTE_E6,PAUSE4,
    NOTE_REST,PAUSE4,
    NOTE_D6,PAUSE4,
    NOTE_DS6,PAUSE4,
    NOTE_D6,PAUSE4,
    NOTE_E6,PAUSE4,
    NOTE_E6,PAUSE4,
    NOTE_DS6,PAUSE4,
    NOTE_DS6,PAUSE4,
    NOTE_D6,PAUSE4,
    NOTE_D6,PAUSE4,
    NOTE_DS6,PAUSE4,
    NOTE_E6,PAUSE4,
    NOTE_DS6,PAUSE4,
    NOTE_REST,PAUSE4,
    NOTE_E6,PAUSE4,
    NOTE_DS6,PAUSE4,
    NOTE_E6,PAUSE4,
    NOTE_DS6,PAUSE4,
    NOTE_DS6,PAUSE4,
    NOTE_E6,PAUSE4,
    NOTE_REST,PAUSE4,
    NOTE_E6,PAUSE4,
    NOTE_F6,PAUSE4,
    NOTE_DS6,PAUSE4,
    NOTE_E6,PAUSE4,
    NOTE_REST,PAUSE4,
    NOTE_F6,PAUSE4,
    NOTE_E6,PAUSE4,
    NOTE_F6,PAUSE4,
    TONES_REPEAT
};

//https://onlinesequencer.net/2484974
const uint16_t PROGMEM music_won[] ={
  NOTE_DS6, PAUSE2,
  NOTE_D6,  PAUSE2,
  NOTE_DS6, PAUSE2,
  NOTE_E6, PAUSE2,
  NOTE_DS6, PAUSE2,
  NOTE_E6, PAUSE2,
  NOTE_F6, PAUSE2 << 2,
  NOTE_REST, PAUSE2,
  TONES_END  
};

//https://onlinesequencer.net/2485064
const uint16_t PROGMEM music_game[] ={ 
    NOTE_REST, PAUSE3,
    NOTE_C4, PAUSE3,
    NOTE_CS4, PAUSE3,
    NOTE_REST, PAUSE3,
    NOTE_C4, PAUSE3,
    NOTE_CS4, PAUSE3,
    NOTE_CS4, PAUSE3,
    NOTE_D4, PAUSE3,
    NOTE_REST, PAUSE3,
    NOTE_DS4, PAUSE3,
    NOTE_D4, PAUSE3,
    NOTE_REST, PAUSE3,
    NOTE_DS4, PAUSE3,
    NOTE_E4, PAUSE3,
    NOTE_REST, PAUSE3,
    NOTE_DS4, PAUSE3,
    NOTE_E4, PAUSE3,
    NOTE_E4, PAUSE3,
    NOTE_F4, PAUSE3,
    NOTE_REST, PAUSE3,

    NOTE_C4, PAUSE3,
    NOTE_CS4, PAUSE3,
    NOTE_REST, PAUSE3,
    NOTE_C4, PAUSE3,
    NOTE_CS4, PAUSE3,
    NOTE_CS4, PAUSE3,
    NOTE_D4, PAUSE3,
    NOTE_REST, PAUSE3,
    NOTE_DS4, PAUSE3,
    NOTE_D4, PAUSE3,
    NOTE_REST, PAUSE3,
    NOTE_DS4, PAUSE3,
    NOTE_E4, PAUSE3,
    NOTE_REST, PAUSE3,
    NOTE_DS4, PAUSE3,
    NOTE_E4, PAUSE3,
    NOTE_E4, PAUSE3,
    NOTE_F4, PAUSE3,
    NOTE_REST, PAUSE3,

    NOTE_D4, PAUSE3,
    NOTE_C4, PAUSE3,
    NOTE_E4, PAUSE3,
    NOTE_D4, PAUSE3,
    NOTE_REST,  PAUSE3,
    NOTE_E4, PAUSE3,
    NOTE_REST,  PAUSE3,
    NOTE_E4, PAUSE3,
    NOTE_D4, PAUSE3,
    NOTE_REST,  PAUSE3,
    NOTE_DS4, PAUSE3,
    NOTE_DS4, PAUSE3,
    NOTE_E4, PAUSE3,
    NOTE_REST, PAUSE3,
    NOTE_E4, PAUSE3,
    NOTE_DS4, PAUSE3,
    NOTE_D4, PAUSE3,
    NOTE_C4, PAUSE3,
    NOTE_DS4, PAUSE3,
    NOTE_E4,PAUSE3,
    NOTE_D4,PAUSE3,
    NOTE_REST,PAUSE3,
    NOTE_DS4,PAUSE3,
    NOTE_D4,PAUSE3,
    NOTE_C4,PAUSE3,
    NOTE_REST,PAUSE3,
    NOTE_D4,PAUSE3,
    NOTE_C4,PAUSE3,
    NOTE_E4,PAUSE3,
    NOTE_D4,PAUSE3,
    NOTE_REST,PAUSE3,
    NOTE_E4,PAUSE3,
    NOTE_REST,PAUSE3,
    NOTE_E4,PAUSE3,
    NOTE_D4,PAUSE3,
    NOTE_REST,PAUSE3,
    NOTE_DS4,PAUSE3,
    NOTE_DS4,PAUSE3,
    NOTE_E4,PAUSE3,
    NOTE_REST,PAUSE3,
    NOTE_E4,PAUSE3,
    NOTE_D4,PAUSE3,
    NOTE_C4,PAUSE3,
    NOTE_CS4,PAUSE3,
    NOTE_DS4,PAUSE3,
    NOTE_F4,PAUSE3,
    NOTE_E4,PAUSE3,
    NOTE_D4,PAUSE3,
    NOTE_DS4,PAUSE3,
    NOTE_DS4,PAUSE3,
    NOTE_REST, PAUSE3,
    NOTE_E4,PAUSE3,
    NOTE_D4,PAUSE3,
    NOTE_D4,PAUSE3,
    NOTE_REST, PAUSE3,
    NOTE_DS4,PAUSE3,
    NOTE_CS4,PAUSE3,
    NOTE_CS4,PAUSE3,
    NOTE_REST, PAUSE3,
    NOTE_D4,PAUSE3,
    TONES_REPEAT
};

//https://onlinesequencer.net/2484977
const uint16_t PROGMEM music_intro[] = {
    NOTE_C4,  PAUSE,
    NOTE_C4,  PAUSE * 2,
    NOTE_D4,  PAUSE,
    NOTE_DS4, PAUSE,
    NOTE_C4,  PAUSE,
    NOTE_REST, PAUSE * 8,
    
    NOTE_C4,  PAUSE,
    NOTE_C4,  PAUSE * 2,
    NOTE_D4,  PAUSE,
    NOTE_DS4, PAUSE,
    NOTE_C4,  PAUSE,
    NOTE_D4,  PAUSE,
    NOTE_C4,  PAUSE,
    NOTE_CS4, PAUSE,
    NOTE_REST, PAUSE * 4,

    NOTE_C4,  PAUSE,
    NOTE_C4,  PAUSE * 2,
    NOTE_D4,  PAUSE,
    NOTE_DS4, PAUSE,
    NOTE_C4,  PAUSE,
    NOTE_REST, PAUSE * 8,
    
    NOTE_C4,  PAUSE,
    NOTE_C4,  PAUSE * 2,
    NOTE_D4,  PAUSE,
    NOTE_DS4, PAUSE,
    NOTE_C4,  PAUSE,
    NOTE_D4,  PAUSE,
    NOTE_C4,  PAUSE,
    NOTE_CS4, PAUSE,
    NOTE_REST, PAUSE * 4,

    NOTE_D4,  PAUSE,
    NOTE_D4,  PAUSE, 
    NOTE_CS4, PAUSE,
    NOTE_C4,  PAUSE,
    NOTE_DS4, PAUSE,
    NOTE_CS4, PAUSE,
    NOTE_D4,  PAUSE,
    NOTE_DS4, PAUSE,
    NOTE_CS4, PAUSE,
    NOTE_DS4, PAUSE,
    NOTE_D4,  PAUSE,
    NOTE_D4,  PAUSE,
    NOTE_D4,  PAUSE,
    NOTE_E4, PAUSE,
    NOTE_C4,  PAUSE,
    NOTE_CS4, PAUSE,
    NOTE_E4,  PAUSE,
    NOTE_D4,  PAUSE * 3,
    NOTE_REST, PAUSE * 4,
    TONES_REPEAT 
};

void setMusicOn(uint8_t value)
{
    music_on = value;
    if(music_on)
    {
        arduboy.audio.on();
        arduboy.audio.saveOnOff();
        if (prev_music != 0)
        {
            SelectMusic(prev_music, 1);
        }
        else
        {
            //this can only happen on title screen
            //normally this does not belong here
            //but if music was off in eeprom no music was playing
            //before and you can only enable it in the main - options - menu
            //where title music plays
            if (gameState == gsTitle)
            {
                SelectMusic(musTitle, 1);
            }
        }
    }
    else
    {
        arduboySound.noTone();
        //both sound and music disabled turn audio off
        //and save the state to global flag
        if (!sound_on)
        {
            arduboy.audio.off();
            arduboy.audio.saveOnOff();
        }
    }
}

void setSoundOn(uint8_t value)
{
    sound_on = value;
    if(sound_on)
    {
        arduboy.audio.on();
        arduboy.audio.saveOnOff();
    }
    else
    {
        //both sound and music disabled turn audio off
        //and save the state to global flag
        if (!music_on)
        {
            arduboy.audio.off();
            arduboy.audio.saveOnOff();
        }
    }
}

uint8_t isMusicOn()
{
    return music_on;
}

uint8_t isSoundOn()
{
    return sound_on;
}

void initSound()
{
    sound_on = isSoundOnSaveState();
    beep.begin();
}

void soundTimer()
{
    beep.timer();
}

void SelectMusic(uint8_t musicFile, uint8_t force)
{
    if (((prev_music != musicFile) || force) && music_on)
    {
        prev_music = musicFile;
        switch (musicFile) 
        {
            case musTitle:
                arduboySound.tones(music_intro);
                break;
            case musLevelClear:
                arduboySound.tones(music_won);               
                break;
            case musAllLevelsClear:
                arduboySound.tones(music_levelsCleared);
                break;
            case musGame:
                arduboySound.tones(music_game);              
                break;
        }
    }
}

void initMusic()
{
    music_on = isMusicOnSaveState();
    prev_music = 0;
}

void playGameMoveSound()
{
    if(!sound_on)
    {
        return;
    }
    beep.tone(beep.freq(750), SFX_SUSTAIN);
}

void playErrorSound()
{
    if(!sound_on)
    {
        return;
    }
    beep.tone(beep.freq(300), SFX_SUSTAIN);

}

void playMenuSelectSound()
{
    if(!sound_on)
    {
        return;
    }
    beep.tone(beep.freq(1250), SFX_SUSTAIN);
}

void playMenuBackSound()
{
    if(!sound_on)
    {
        return;
    }
    beep.tone(beep.freq(1000), SFX_SUSTAIN);
}

void playMenuAcknowlege()
{
    if(!sound_on)
    {
        return;
    }
    beep.tone(beep.freq(900), SFX_SUSTAIN);
}

void playGameAction()
{
    if(!sound_on)
    {
        return;
    }
    beep.tone(beep.freq(600), SFX_SUSTAIN);
}
