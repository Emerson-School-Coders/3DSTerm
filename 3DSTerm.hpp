//
//  3DSTerm.hpp
//  3DSTerm
//
//  Created by Homework User on 1/21/16.
//
//  Core functionality for 3DSTerm and all applications.

#ifndef _DSTerm_h
#define _DSTerm_h


#endif /* _DSTerm_h */
#include <cstdlib>
#include <string>
#include <map>
#include <3ds.h>

PrintConsole console, keyboard;
bool flase = false; //failsafe
int caps = 0;   // 0 means lowercase, 1 means caps lock, 2 means shift
void cls() {
    consoleSelect(&console);
    consoleClear();
}

void clk() {
    consoleSelect(&keyboard);
    consoleClear();
}

std::tuple<u32, u32, u32> dsIn() {
	hidScanInput();
	return std::make_tuple(hidKeysDown(), hidKeysHeld(), hidKeysUp());
}

bool isButtonPressed(char button, bool wait = true) {
    /*
     The letter mappings:
     'a' = A
     'b' = B
     'x' = X
     'y' = Y
     't' = Start
     'e' = Select
     'l' = Left
     'r' = Right
     'u' = Up (Circle Pad or D-Pad)
     'd' = Down
     'q' = Left
     'e' = Right
     On New 3DS:
     'c' = ZR
     'z' = ZL
     */
	std::tuple<u32, u32, u32> input = dsIn();
	u32 kDown = std::get<0>(input);
	u32 kHeld = std::get<1>(input);
	u32 kUp	  = std::get<2>(input);
	while (!kDown && wait) {hidScanInput(); u32 kDown = hidKeysDown(); u32 kHeld = hidKeysHeld(); u32 kUp = hidKeysUp();}
	if (kDown && KEY_A && button == 'a') return 0;
	else if (kDown && KEY_B && button == 'b') return 0;
	else if (kDown && KEY_X && button == 'x') return 0;
	else if (kDown && KEY_Y && button == 'y') return 0;
	else if (kDown && KEY_L && button == 'l') return 0;
	else if (kDown && KEY_R && button == 'r') return 0;
	else if (kDown && KEY_START && button == 't') return 0;
	else if (kDown && KEY_SELECT && button == 'e') return 0;
	else if (kDown && KEY_UP && button == 'u') return 0;
	else if (kDown && KEY_DOWN && button == 'd') return 0;
	else if (kDown && KEY_LEFT && button == 'q') return 0;
	else if (kDown && KEY_RIGHT && button == 'e') return 0;
	else if (consoletype) {
		if (kDown && KEY_ZR && button == 'c') return 0;
		else if (kDown && KEY_ZL && button == 'z') return 0;
	}
	return 1;
}

bool input(std::string text = "") {
	bool retval = false;
	printf(text.c_str());
	while (!isButtonPressed('a', false)) if (isButtonPressed('t', false)) retval = true;
	printf("\n");
	return retval;
}
std::map<int, std::map<int, char> > char_low = {
    {2, {
        {2, '`'},
        {6, '1'},
        {10, '2'},
        {14, '3'},
        {18, '4'},
        {22, '5'},
        {26, '6'},
        {30, '7'},
        {34, '8'},
        {38, '9'},
        {42, '0'},
        {46, '-'},
        {50, '='},
    }},
    {4, {
        {8, 'q'},
        {12, 'w'},
        {16, 'e'},
        {20, 'r'},
        {24, 't'},
        {28, 'y'},
        {32, 'u'},
        {36, 'i'},
        {40, 'o'},
        {44, 'p'},
        {48, '['},
        {52, ']'},
        {56, '\\'},
    }},
    {6, {
        {11, 'a'},
        {15, 's'},
        {19, 'd'},
        {23, 'f'},
        {27, 'g'},
        {31, 'h'},
        {35, 'j'},
        {39, 'k'},
        {43, 'l'},
        {47, ';'},
        {51, '\''},
    }},
    {8, {
        {12, 'z'},
        {16, 'x'},
        {20, 'c'},
        {24, 'v'},
        {28, 'b'},
        {32, 'n'},
        {36, 'm'},
        {40, ','},
        {44, '.'},
        {48, '/'},
    }}
};
std::map<int, std::map<int, char> > char_up = {
    {2, {
        {2, '~'},
        {6, '!'},
        {10, '@'},
        {14, '#'},
        {18, '$'},
        {22, '%'},
        {26, '^'},
        {30, '&'},
        {34, '*'},
        {38, '('},
        {42, ')'},
        {46, '_'},
        {50, '+'},
    }},
    {4, {
        {8, 'Q'},
        {12, 'W'},
        {16, 'E'},
        {20, 'R'},
        {24, 'T'},
        {28, 'Y'},
        {32, 'U'},
        {36, 'I'},
        {40, 'O'},
        {44, 'P'},
        {48, '{'},
        {52, '}'},
        {56, '|'},
    }},
    {6, {
        {11, 'A'},
        {15, 'S'},
        {19, 'D'},
        {23, 'F'},
        {27, 'G'},
        {31, 'H'},
        {35, 'J'},
        {39, 'K'},
        {43, 'L'},
        {47, ':'},
        {51, '\"'},
    }},
    {8, {
        {12, 'Z'},
        {16, 'X'},
        {20, 'C'},
        {24, 'V'},
        {28, 'B'},
        {32, 'N'},
        {36, 'M'},
        {40, '<'},
        {44, '>'},
        {48, '?'},
    }}
};
std::string keyboardLow = "\
-----------------------------------------------------------\n\
| ` | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = | del |\n\
|---------------------------------------------------------|\n\
|     | q | w | e | r | t | y | u | i | o | p | [ | ] | \\ |\n\
|---------------------------------------------------------|\n\
|o caps | a | s | d | f | g | h | j | k | l | ; | \' | ret |\n\
|---------------------------------------------------------|\n\
| shift  | z | x | c | v | b | n | m | , | . | / |  shift |\n\
|---------------------------------------------------------|\n\
| fn | cn | alt | ds |                   | ds | alt | cn  |\n\
-----------------------------------------------------------";
std::string keyboardUp = "\
-----------------------------------------------------------\n\
| ~ | ! | @ | # | $ | % | ^ | & | * | ( | ) | _ | + | del |\n\
|---------------------------------------------------------|\n\
|     | Q | W | E | R | T | Y | U | I | O | P | { | } | | |\n\
|---------------------------------------------------------|\n\
|I caps | A | S | D | F | G | H | J | K | L | : | \" | ret |\n\
|---------------------------------------------------------|\n\
| shift  | Z | X | C | V | B | N | M | < | > | ? |  shift |\n\
|---------------------------------------------------------|\
| fn | cn | alt | ds |                   | ds | alt | cn  |\n\
-----------------------------------------------------------";
bool intBetween(int number, int min, int max) {
    if (number >= min && number <= max) return true;
    else return false;
}
char getChar(int caps_stat) {
    touchPosition touch;
    hidTouchRead(&touch);
    int keyX = touch.x / 6;
    int keyY = touch.y / 6;
    if (caps_stat == 0) std::map<int, std::map<int, char> > char_locs = char_low;
    else std::map<int, std::map<int, char> > char_locs = char_up;
    try char typedKey = char_locs[keyY][keyX];
    catch (const std::out_of_range& oor) {
        try char typedKey = char_locs[keyY][keyX + 1];
        catch (const std::out_of_range& oor) {
            try char typedKey = char_locs[keyY][keyX - 1];
            catch (const std::out_of_range& oor) {
                if (keyY == 2 && intBetween(keyX, 53, 57)) typedKey = '\x10';
                else if (keyY == 6) {
                    if (intBetween(keyX, 2, 8)) caps = 1;
                    else if (intBetween(keyX, 54, 58)) typedKey = '\x11';
                }
                else if (keyY == 8) {
                    if (intBetween(keyX, 2, 9) || intBetween(keyX, 51, 58)) caps = 2;
                }
                else if (keyY == 10) {
                    if (intBetween(keyX, 2, 5)) typedKey = '\x12';
                    else if (intBetween(keyX, 7, 10)) typedKey = '\x13';
                    else if (intBetween(keyX, 12, 16)) typedKey = '\x14';
                    else if (intBetween(keyX, 18, 21)) typedKey = '\x15';
                    else if (intBetween(keyX, 23, 41)) typedKey = ' ';
                    else if (intBetween(keyX, 43, 46)) typedKey = '\x15';
                    else if (intBetween(keyX, 48, 52)) typedKey = '\x14';
                    else if (intBetween(keyX, 54, 58)) typedKey = '\x13';
                }
            }
        }
    }
    if (caps_stat == 2) {
        caps = 0;
        clk();
        printf(keyboardLow);
        consoleSelect(&console)
    }
    if (caps == 1 && caps_stat == 0) {
        clk();
        printf(keyboardUp);
        consoleSelect(&console);
    }
    if (caps == 2) {
        clk();
        printf(keyboardUp);
        consoleSelect(&console);
    }
    return typedKey;
}

inline bool fexists (const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}