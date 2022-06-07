#include <stdint.h>

#include "cursor.h"
#include "commonvars.h"
#include "helperfuncs.h"
#include "../res/selectortiles.h"

constexpr uint8_t MAXCURSORFRAMECOUNT = (uint8_t)(10 * FRAMERATE / 60);
constexpr uint8_t CURSORANIMCOUNT = 4;
constexpr uint8_t NUMTILES = 32;

uint8_t cursorFrameCount, cursorFrame;
uint8_t spriteTiles[NUMTILES];
uint8_t showCursor = 1;
uint8_t spritePos[NUMTILES][2];

void set_sprite_tile(uint8_t sprite, uint8_t tile)
{
    spriteTiles[sprite] = tile;
}

void move_sprite(uint8_t sprite, uint8_t x, uint8_t y)
{
    spritePos[sprite][0] = x;
    spritePos[sprite][1] = y;
}

void drawCursors()
{
    if(showCursor == 0)
        return;
    for (uint8_t i=0; i<NUMTILES; i++)
    {
        if (spritePos[i][1] < arduboy.height())
        {
            arduboy.drawBitmap(spritePos[i][0], spritePos[i][1], selectorTiles + 2 + (spriteTiles[i] * 8), 8, 8);
        }
    }
}

uint8_t updateCursorFrame()
{
    uint8_t tmpFrame;
    uint8_t result = 0;
    cursorFrameCount++;
    if (cursorFrameCount >= MAXCURSORFRAMECOUNT)
    {
        result = 1;
        cursorFrame++;
        cursorFrameCount = 0;
        if (cursorFrame >= CURSORANIMCOUNT)
        {
            cursorFrame = 0;
        }
        tmpFrame = (cursorFrame * 4);
       
        //cursor 0
        set_sprite_tile(0, 8 + tmpFrame);
        set_sprite_tile(1, 9 + tmpFrame);
        set_sprite_tile(2, 10 + tmpFrame);
        set_sprite_tile(3, 11 + tmpFrame);
        set_sprite_tile(4, 25 + tmpFrame);
        set_sprite_tile(5, 26 + tmpFrame);
        set_sprite_tile(6, 27 + tmpFrame);
        set_sprite_tile(7, 28 + tmpFrame);
        
        //cursor 1
        set_sprite_tile(8, 8 + tmpFrame);
        set_sprite_tile(9, 9 + tmpFrame);
        set_sprite_tile(10, 10 + tmpFrame);
        set_sprite_tile(11, 11 + tmpFrame);
        set_sprite_tile(12, 25 + tmpFrame);
        set_sprite_tile(13, 26 + tmpFrame);
        set_sprite_tile(14, 27 + tmpFrame);
        set_sprite_tile(15, 28 + tmpFrame);
       
        //cursor 2
        set_sprite_tile(16, 8 + tmpFrame);
        set_sprite_tile(17, 9 + tmpFrame);
        set_sprite_tile(18, 10 + tmpFrame);
        set_sprite_tile(19, 11 + tmpFrame);
        set_sprite_tile(20, 25 + tmpFrame);
        set_sprite_tile(21, 26 + tmpFrame);
        set_sprite_tile(22, 27 + tmpFrame);
        set_sprite_tile(23, 28 + tmpFrame);
       
        //cursor 3
        set_sprite_tile(24, 8 + tmpFrame);
        set_sprite_tile(25, 9 + tmpFrame);
        set_sprite_tile(26, 10 + tmpFrame);
        set_sprite_tile(27, 11 + tmpFrame);
        set_sprite_tile(28, 25 + tmpFrame);
        set_sprite_tile(29, 26 + tmpFrame);
        set_sprite_tile(30, 27 + tmpFrame);
        set_sprite_tile(31, 28 + tmpFrame);
    }
    return result;
}

void hideCursors()
{
    //HIDE CURSOR SPRITES
    //cursor 0
    setCursorPos(0, 0, (arduboy.height() / 8) + 1);
    
    //cursor 1
    setCursorPos(1, 0, (arduboy.height() / 8) + 1);
    
    //cursor 2
    setCursorPos(2, 0, (arduboy.height() / 8) + 1);
    
    //cursor 3
    setCursorPos(3, 0, (arduboy.height() / 8) + 1);

    showCursor = 0;
}

void showCursors()
{
    showCursor = 1;
}

void setCursorPos(uint8_t cursorNr, uint8_t xPos, uint8_t yPos)
{
    if (cursorNr > 3)
    {
        return;
    }
    move_sprite((cursorNr<<3) + 0, ((xPos) << 3),  ((yPos - 1) << 3));
    move_sprite((cursorNr<<3) + 1,  ((xPos + 1) << 3),  ((yPos) << 3));
    move_sprite((cursorNr<<3) + 2,  ((xPos) << 3),  ((yPos + 1) << 3));
    move_sprite((cursorNr<<3) + 3,  ((xPos - 1) << 3),  ((yPos) << 3)); 
    //corners
    move_sprite((cursorNr<<3) + 4, ((xPos + 1) << 3),  ((yPos - 1) << 3));
    move_sprite((cursorNr<<3) + 5, ((xPos + 1) << 3),  ((yPos + 1) << 3));
    move_sprite((cursorNr<<3) + 6, ((xPos - 1) << 3),  ((yPos - 1) << 3));
    move_sprite((cursorNr<<3) + 7, ((xPos - 1) << 3),  ((yPos + 1) << 3)); 
}

void initCursors()
{
    //cursor 0
    set_sprite_tile(0, 8);
    set_sprite_tile(1, 9);
    set_sprite_tile(2, 10);
    set_sprite_tile(3, 11);
    set_sprite_tile(4, 25);
    set_sprite_tile(5, 26);
    set_sprite_tile(6, 27);
    set_sprite_tile(7, 28);

    //cursor 1
    set_sprite_tile(8, 8);
    set_sprite_tile(9, 9);
    set_sprite_tile(10, 10);
    set_sprite_tile(11, 11);
    set_sprite_tile(12, 25);
    set_sprite_tile(13, 26);
    set_sprite_tile(14, 27);
    set_sprite_tile(15, 28);

    //cursor 2
    set_sprite_tile(16, 8);
    set_sprite_tile(17, 9);
    set_sprite_tile(18, 10);
    set_sprite_tile(19, 11);
    set_sprite_tile(20, 25);
    set_sprite_tile(21, 26);
    set_sprite_tile(22, 27);
    set_sprite_tile(23, 28);

    //cursor 3
    set_sprite_tile(24, 8);
    set_sprite_tile(25, 9);
    set_sprite_tile(26, 10);
    set_sprite_tile(27, 11);
    set_sprite_tile(28, 25);
    set_sprite_tile(29, 26);
    set_sprite_tile(30, 27);
    set_sprite_tile(31, 28);

    hideCursors();

    cursorFrameCount = 0;
    cursorFrame = 0;
}
