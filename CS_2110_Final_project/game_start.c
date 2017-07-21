// Kaley Findley
// start game screen

#include "mylib.h"

int main() {
	REG_DISPCTL = MODE3 | BG2_ENABLE;

	//setup game
	drawImage3(0, 0, GAME_TITLE_WIDTH, GAME_TITLE_HEIGHT, game_title);
	drawString(80, 60, "Press Enter to Start", RED);
	DINO dino = {0, {10, 120}};
	SPRITE sprites[2] = {{0,0, CACTUS_HEIGHT, CACTUS_WIDTH, cactus}, {0,0, MANY_CACTI_HEIGHT, MANY_CACTI_WIDTH, many_cacti}};
	for (int i = 0; i < 2; i++) {
		sprites[i].x = rand()%70 + 160;
		sprites[i].y = 160 - (sprites[i].hgt + 17);
	}

	while(1) { //game play
		if (KEY_DOWN_NOW(BUTTON_START)) { //start game
			fillScreen3(WHITE);
			drawImage3(dino.pos.x, dino.pos.y, TREX_CHAR_WIDTH, TREX_CHAR_HEIGHT, trex_char);
			while(1) {
				char str[15];
				dino.score++;
				clearScoreText();
				sprintf(str, "Score: %d", dino.score);
				drawString(0, 0, str, RED);
				drawImage3(dino.pos.x, dino.pos.y, TREX_CHAR_WIDTH, TREX_CHAR_HEIGHT, trex_char);	
				
				//draw cacti
				for (int i = 0; i < NUMOBS; i++) {
					SPRITE randSprite = sprites[rand()%2];
					drawImage3(randSprite.x, randSprite.y, randSprite.wth, randSprite.hgt, randSprite.data);
					if (randSprite.x <= 0) {
						randSprite.x = 220;					
					} 
				}
				sprites[0].x--;
				sprites[1].x--;
				if (sprites[0].x <= 0) {
					sprites[0].x = rand()%20 + 165;	
					fillScreen3(WHITE);			
				}
				if (sprites[1].x <= 0) {
					sprites[1].x = rand()%10 + 200;	
					fillScreen3(WHITE);			
				}
				
			
				
				if (KEY_DOWN_NOW(BUTTON_A) && KEY_DOWN_NOW(BUTTON_LEFT)) { 
					//super jump left
					dino.pos.y -= 40;
					dino.pos.x -= 70;
					if (dino.pos.x <= 0) {
						dino.pos.x = 0;
					}
					drawImage3(dino.pos.x, dino.pos.y, TREX_CHAR_WIDTH, TREX_CHAR_HEIGHT, trex_char);
					fillScreen3(WHITE);
					dino.pos.y += 40;
				} else if (KEY_DOWN_NOW(BUTTON_A) && KEY_DOWN_NOW(BUTTON_RIGHT)) { //super jump right
					dino.pos.y -= 40;
					dino.pos.x += 70;
					drawImage3(dino.pos.x, dino.pos.y, TREX_CHAR_WIDTH, TREX_CHAR_HEIGHT, trex_char);
					fillScreen3(WHITE);
					dino.pos.y += 40;
				} else if (KEY_DOWN_NOW(BUTTON_A)) { // regular jump right
					dino.pos.y -= 40;
					dino.pos.x += 40;
					drawImage3(dino.pos.x, dino.pos.y, TREX_CHAR_WIDTH, TREX_CHAR_HEIGHT, trex_char);
					
					fillScreen3(WHITE);
					dino.pos.y += 40;
				} else if (KEY_DOWN_NOW(BUTTON_LEFT)) {
					dino.pos.x--;
					if (dino.pos.x <= 0) {
						dino.pos.x = 0;
					}
				} else if (KEY_DOWN_NOW(BUTTON_RIGHT)) {
					dino.pos.x++;
					if (dino.pos.x >= 240) {
						dino.pos.x = 0;

					}
				} else if (KEY_DOWN_NOW(BUTTON_SELECT)) {
					main();
				}
		
				//check for collision
				for (int i = 0; i < NUMOBS; i++) {
					SPRITE sprite = sprites[i];
					if (checkForCollision(dino.pos.x, sprite.x, dino.score) == 1) {
						while(1) {
							if (KEY_DOWN_NOW(BUTTON_SELECT) || KEY_DOWN_NOW(BUTTON_START)) {
								main();
							}
						}					
					}
				}
				waitForVblank();
			}

		} else if (KEY_DOWN_NOW(BUTTON_SELECT)) {
			main();			
		}
	}

	return 0;
	
}

