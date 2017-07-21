#include "mylib.h"

u16 *videoBuffer = (unsigned short*)0x6000000;

void drawChar(int row, int col, char ch, unsigned short color) {
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 6; c++) {
			if (fontdata_6x8[OFFSET(r, c, 6) + ch * 48]) {
				videoBuffer[OFFSET(r + row, c + col, 240)] = color;
			}
		}
	}
}

void drawString(int row, int col, char *str, unsigned short color) {
	while(*str) {
		drawChar(row, col, *str++, color);
		col += 6;
	}
}

void clearScoreText() {
	DMA[3].src = (u32) 0;
	DMA[3].dst = &videoBuffer[0];
	DMA[3].cnt = (30 * 72) | DMA_ON | DMA_DESTINATION_INCREMENT;	
}

int checkForCollision(int dinoPos, int spritePos, int score) {
	if (dinoPos == (spritePos - 12) || dinoPos == (spritePos + 12)) {
		drawImage3(0,0, GAME_OVER_PIC_WIDTH, GAME_OVER_PIC_HEIGHT, game_over_pic);
		char str[15];
		sprintf(str, "Score: %d", score);
		drawString(0, 0, str, RED);
		return 1;
	}
	return 0;
}

void drawImage3(int x, int y, int width, int height, volatile u16 *image) {
	for (int i = 0; i < height; i++) {
		DMA[3].src = &image[OFFSET(i, 0, width)];
		DMA[3].dst = &videoBuffer[OFFSET(y + i, x, 240)];
		DMA[3].cnt = width | DMA_ON | DMA_SOURCE_INCREMENT;
	}
}

void fillScreen3(unsigned short color) {
	for (int i = 0; i < 160; i++) {
		for (int j = 0; j < 240; j++) {
			videoBuffer[OFFSET(i,j,240)] = color;
		}
		DMA[3].src = (u32) 0;
		DMA[3].dst = &videoBuffer[OFFSET(144, 0, 240)];
		DMA[3].cnt = 240 | DMA_ON | DMA_DESTINATION_INCREMENT;
	}
	drawImage3(190, 15, CLOUD_WIDTH, CLOUD_HEIGHT, cloud);
	drawImage3(100, 25, CLOUD_WIDTH, CLOUD_HEIGHT, cloud);
}


void waitForVblank()
{
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}


