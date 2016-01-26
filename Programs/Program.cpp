//
//  Program.cpp
//  3DSTerm
//
//  Created by Tushar Chaudhary on 1/25/16.
//  Copyright © 2016 MCJack123. All rights reserved.
//

#include "../3DSTerm.hpp"
#include <cstdio>
#include <cstdlib>
int main() {
    gfxInitDefault();
    consoleInit(GFX_TOP, &console);
    consoleInit(GFX_BOTTOM, &keyboard);
    consoleSelect(&keyboard);
    printf(keyboardLow.c_str());
    consoleSelect(&console);
    while (aptMainLoop()) {
        printf("Welcome to Finish that sentence! Press A to start.");
        if (input()) break;
        printf("\n\nI like ________\n\
               \n\
               \n\
               \n\
               \n\
               A. Pie\n\
               B. Movies\n\
               X. Apples\n\
               Y. Turtles\n");
        std::string selection;
    ispress1:
        if (isButtonPressed('a', false)) selection = "Pie";
        else if (isButtonPressed('b', false)) selection = "Movies";
        else if (isButtonPressed('x')) selection = "Apples";
        else if (isButtonPressed('y')) selection = "Turtles";
        else if (isButtonPressed('t', false)) break;
        else goto ispress1;
        printf("You Selected: %s", selection.c_str());
        printf("Great! Here's the next one. Press B to show the next one.");
        if (isButtonPressed('t')) break;
            printf("On my Apple Watch I...\n\
                   A. Take a Run\n\
                   B. Text your friends\n\
                   X. Just look at it\n\
                   Y. None of the above");
            if (isButtonPressed('a')) selection = "Take a Run";
            else if (isButtonPressed('b')) selection = "Text your friends";
            else if (isButtonPressed('x')) selection = "Just look at it.";
            else if (isButtonPressed('y')) selection = "None of the above";
            else if (isButtonPressed('t')) break;
                printf("You Selected: %s", selection.c_str());
        printf("Great! Here's the next and last one. Press B.");
        if (isButtonPressed('t')) break;
            printf("In School i...\n\
                   A. Actually Work\n\
                   B. Play Games every second of school\n\
                   X. Watch YouTube :D\n\
                   Y. Talk with Friends");
        if (isButtonPressed('a')) selection = "Actually Work.";
        else if (isButtonPressed('b')) selection = "Play games every second of school";
        else if (isButtonPressed('x')) selection = "Watch YouTube :D";
        else if (isButtonPressed('y')) selection = "Talk with Friends";
        printf("You Selected: %s", selection.c_str());
        printf("OK thats the last sentence! Hope you had fun! Press Y to exit."
               );
        if (isButtonPressed('y')) break;
    
            
        
        
        
    }
    gfxExit();
    return 0;
}
        



