typedef unsigned short u16;
typedef unsigned int u32;

#include "game_title.h"
#include "game_over_pic.h"
#include "trex_char.h"
#include "cactus.h"
#include "cloud.h"
#include "many_cacti.h"
#include <stdio.h>
#include <stdlib.h>

#define REG_DISPCTL *(unsigned short*) 0x4000000
#define MODE3 3
#define BG2_ENABLE (1<<10)
#define DMA_ON (1 << 31)
#define DMA_SOURCE_FIXED (2 << 23)
#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_DESTINATION_FIXED (2 << 21)
#define DMA_DESTINATION_INCREMENT (0 << 21)
#define NUMOBS 3

#define OFFSET(r,c, rowlen) ((r)*rowlen+(c))

#define COLOR(r,g,b) ((r) | (g)<<5 | (b)<<10)
#define WHITE COLOR(31,31,31)
#define RED COLOR(31,0,0)
#define BLACK 0

extern u16 *videoBuffer;
extern unsigned char fontdata_6x8[12288];

#define SCANLINECOUNTER *(volatile unsigned short *)0x4000006

//Buttons

#define BUTTON_SELECT		(1<<2) //delete
#define BUTTON_START		(1<<3) //enter
#define BUTTON_RIGHT		(1<<4) 
#define BUTTON_LEFT		(1<<5)
#define BUTTON_A		(1<<0)
#define BUTTONS *(volatile unsigned int *)0x4000130
#define KEY_DOWN_NOW(key)  (~(BUTTONS) & key)

// prototypes

void drawChar(int row, int col, char ch, unsigned short color);
void drawString(int row, int col, char *str, unsigned short color);
void drawImage3(int x, int y, int width, int height, volatile u16 *image);
void fillScreen3(unsigned short color);
void waitForVblank();
void clearScoreText();
int checkForCollision(int dinoPos, int spritePos, int score);

typedef struct
{
	int x;
	int y;
} POINT;

typedef struct
{
	int score;
	POINT pos;
} DINO;

typedef struct
{
	int x;
	int y;
	int hgt;
	int wth;
	volatile unsigned short *data;
} SPRITE;

typedef struct
{
	const volatile void *src;
	volatile void *dst;
	unsigned int cnt;
} DMA_CONTROLLER;

#define DMA ((volatile DMA_CONTROLLER *) 0x040000B0)

