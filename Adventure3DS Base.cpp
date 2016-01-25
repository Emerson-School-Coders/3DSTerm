//
//  main.cpp
//  N3DS Program
//
//  Created by Jack Bruienne on 1/15/16.
//  Copyright © 2016 MCJack123. All rights reserved.
//

#include <stdio.h>
#include <3ds.h>
#include <sys/unistd.h>
#include <string>
#include <vector>

int lives=5;
int gold=10;
std::string move="None";
bool rdone=false;
bool ldone=false;
int damagem=1;
std::vector<std::string> special;
int healthm=1;

void cls() {
	consoleSelect(&topScreen);
	consoleClear();
	initscreens();
}
int randint(int sinput, int einput) {return rand() % einput + sinput;}
void rendscreen(std::string text) {
    cls();
    printf("--------------------------------------------------------------------------------\n");
    printf("Gold: %i Lives: %i\n", gold, lives);
	printf("Special items: ");
	for (item : special) printf("%s, ", item);
	printf("\n");
    printf("--------------------------------------------------------------------------------\n");
    printf(text);
	printf("\n");
}
void rendscreenf() {
    cls();
    printf("--------------------------------------------------------------------------------\n");
    printf("Gold: %i Lives: %i\n", gold, lives);
    printf("Special items: ");
	for (item : special) printf("%s, ", item);
	printf("\n");
    printf("Health: %i Enemy Health: %i\n", health, enemyh);
    printf("--------------------------------------------------------------------------------\n");
}
void rendscreenx(std::string text) {
    cls();
    printf("--------------------------------------------------------------------------------\n");
    printf("Gold: %i Lives: %i XP: %i\n", gold, lives, xp);
	printf("Special items: ");
	for (item : special) printf("%s, ", item);
	printf("\n");
    printf("--------------------------------------------------------------------------------\n");
    printf(text);
	printf("\n");
}
void dsIn() {
	hidScanInput();

		//hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
		u32 kDown = hidKeysDown();
		//hidKeysHeld returns information about which buttons have are held down in this frame
		u32 kHeld = hidKeysHeld();
		//hidKeysUp returns information about which buttons have been just released
		u32 kUp = hidKeysUp();
}
bool isButtonPressed(char button) {
	dsIn();
	if (kDown & KEY_A & button == 'a') return 0;
	else if (kDown & KEY_B & button == 'b') return 0;
	else if (kDown & KEY_X & button == 'x') return 0;
	else if (kDown & KEY_Y & button == 'y') return 0;
	else if (kDown & KEY_L & button == 'l') return 0;
	else if (kDown & KEY_R & button == 'r') return 0;
	else if (kDown & KEY_START & button == 't') return 0;
	else if (kDown & KEY_SELECT & button == 'e') return 0;
	else if (kDown & KEY_UP & button == 'u') return 0;
	else if (kDown & KEY_DOWN & button == 'd') return 0;
	else if (kDown & KEY_LEFT & button == 'q') return 0;
	else if (kDown & KEY_RIGHT & button == 'e') return 0;
	else if (consoletype) {
		if (kDown & KEY_ZR & button == 'c') return 0;
		else if (kDown & KEY_ZL & button == 'z') return 0;
	}
	else return 1;
}
void input(std::string text = "") {
	printf(text);
	while (!isButtonPressed('a')) if (isButtonPressed('t')) goto exit;
	printf("\n");
}
void print(std::string text) {printf("%s\n", text);}

int main() {
	gfxInitDefault();
	PrintConsole topScreen, bottomScreen;
	//Initialize console on top screen. Using NULL as the second argument tells the console library to use the internal console structure as current one
	consoleInit(GFX_TOP, &topScreen);
	consoleInit(GFX_BOTTOM,&bottomScreen);
	u32 kDownOld = 0, kHeldOld = 0, kUpOld = 0; //In these variables there will be information about keys detected in the previous frame
	int Frames = 0;
	consoleSelect(&topScreen);
	
	void initscreens(){
		printf("Y to clear both screen, X to clear upper,\nB to clear lower.\n\n");
	}
	u8 consoletype=0;
	initscreens();
	APT_CheckNew3DS(NULL,&consoletype);
	printf("Console type:%s\n",consoletype?"New3DS. Good job!":"Old3DS. This may be a bit slow.");
	// Main loop
	while (aptMainLoop())
	{
		printf("Welcome to the adventure. Press A to continue, or any other key to exit.\n");
		hidScanInput();

		//hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
		u32 kDown = hidKeysDown();
		//hidKeysHeld returns information about which buttons have are held down in this frame
		u32 kHeld = hidKeysHeld();
		//hidKeysUp returns information about which buttons have been just released
		u32 kUp = hidKeysUp();

		if (kDown & KEY_START)	break;
		else if (kDown & !KEY_A) break;
		else {
			notknow:
			rendscreen("\n\nYou are walking in a forest. You come to a part you don't know. You can go three ways. Do you go left, right, or straight? (Use the D-Pad to select) ");
			hidScanInput();

			//hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
			kDown = hidKeysDown();
			//hidKeysHeld returns information about which buttons have are held down in this frame
			kHeld = hidKeysHeld();
			//hidKeysUp returns information about which buttons have been just released
			kUp = hidKeysUp();
			if (kDown & KEY_LEFT) {
				if (ldone) {
					rendscreen("You've already gone here! (A)");
					isButtonPressed('a');
					move="0";
					goto notknow;
				}
				else {
					rendscreen("You found a chest! Inside it was 5 bars of gold. (A to continue)");
					input();
					gold +=5;
					rendscreen("It's at a dead end, however. You walk back.");
					input();
					move="0";
					ldone=true;
					goto notknow;
				}
			}
			else if (kDown & KEY_RIGHT) {
				if (rdone) {
					rendscreen("You've already gone here!");
					input();
					move="0";
				}
				else {
					rendscreen("You walk into a trap and lose a life.(A to continue)");
					input();
					lives+=-1;
					rendscreen("You walk back.");
					input();
					move="0";
					rdone=true;
				}
			}
			else if (kDown & KEY_UP) continue;
			else if (kDown & KEY_START) goto exit;
			else goto notknow;
			rendscreen("You walk forward for a while.(A to continue)");
			input();
			rendscreen("The ground begins to shake...(A to continue)");
			input();
			cls();
			print("Louder...");
			usleep(1000);
			rendscreen("You come up to a monster!");
			usleep(1000);
			rendscreen("'I will eat you!'");
			usleep(1000);
			rendscreen("How to fight: Press A to kick and B to punch.");
			input();
			rendscreen("When it's your enemy's turn, hope for the best!");
			input();
			rendscreen("Press A to start.");
			input();
			int health=1000;
			int enemyh=200;
			while (enemyh>0) {
				rendscreenf();
				fmove="0";
				while (fmove != "K" & fmove != "P" & fmove != "adminpass") {
					printf("Kick or punch? \n");
					dsIn();
					if (kDown & KEY_A) fmove == "K";
					else if (kDown & KEY_B) fmove == "P";
					else if (kDown & KEY_SELECT) {
						if (isButtonPressed('l')) fmove = "adminpass";
					}
					else if (kDown & KEY_START) goto exit;
				}
				if (fmove=="K") {
					int sub=floor(random.random()*10)+5;
					int enemyh=enemyh-sub*10;
					printf("Damage dealt: %i\n",sub*10);
					input();
				}
				elif fmove=="adminpass":
					enemyh=0;
				else:
					sub=floor(random.random()*10);
					enemyh+=-sub*18;
					printf("Damage dealt: %i\n", sub*18);
					input();
				rendscreenf();
				usleep(200);
				if enemyh>0:
					health+=-floor(random.random()*100);
					health+=-60;
					printf("Monster attacks! Damage dealt: %i\n", sub+60));
					input();
			}
			rendscreen("You won the battle!");
			input();
			rendscreen("The monster had 20 gold and you gained two lives from defeating him!");
			gold+=20;
			lives+=2;
			input();
			rendscreen("You continue along the path.");
			input();
			int ebhealth=0;
			int berries=0;
			printf("Unfortunately, this is an *alpha* release for debugging only. This is the end of the program.\n\n\n");
			usleep(2000);
			printf("Exiting...\n");
			usleep(500);
			goto exit;
		}
	}
	exit:
	// Exit services
	gfxExit();
	return 0;
}