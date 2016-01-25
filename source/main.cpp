//
//  3DSTerm.cpp
//  3DSTerm
//
//  Created by Homework User on 1/20/16.
//
//

#include <fstream>
#include <cstdlib>
#include <string>
#include <map>
#include <vector>
#include <3ds.h>
#include "../3DSTerm.hpp"

std::string current_directory = "/";
std::vector<char> command;
char text_buf;

int main(int argc, char** argv[]) {
    gfxInitDefault();
    //Initialize console on top screen. Using NULL as the second argument tells the console library to use the internal console structure as current one
    consoleInit(GFX_TOP, &console);
    consoleInit(GFX_BOTTOM,&keyboard);
    u32 kDownOld = 0, kHeldOld = 0, kUpOld = 0; //In these variables there will be information about keys detected in the previous frame
    int Frames = 0;
    consoleSelect(&keyboard);
    printf(keyboardLow.c_str());
    consoleSelect(&console);
    u8 consoletype=0;
    APT_CheckNew3DS(NULL,&consoletype);
    printf("Console type:%s\nWelcome to 3DSTerm! Type 'help' for help.\n",consoletype?"New3DS. Good job!":"Old3DS. This may be a bit slow.");
    // Main loop
    while (aptMainLoop()) {
        printf("3DSTerm: %s $ ", current_directory);
        // Get the inputted command
        do {
            text_buf = getChar(caps);
            if (text_buf == '\x10') command.pop_back();
            else if (text_buf == '\x15') {
                printf("Would you like to quit? Press B to quit, or anything else to continue.");
                if (isButtonPressed('b')) goto end;
            }
            else if (text_buf != '\x11' && text_buf != '\x12' && text_buf != '\x13' && text_buf != '\x14') {command.push_back(text_buf); cls(); printf("3DSTerm: %s $ %s", current_directory, std::string commandst(command.begin(), command.end()));}
        } while (text_buf != '\x11');
        // Now to run it
        std::string commandst(command.begin(), command.end());
        if (fexists(std::string(sprintf("%s%s", current_directory, commandst.substr(0, commandst.find_first_of(" ")))))) system(sprintf("%s%s %s %s", current_directory, commandst.substr(0, commandst.find_first_of(" ")), current_directory, commandst.substr(commandst.find_first_of(" ") + 1)));
        else if (fexists(std::string(sprintf("/dsterm/usr/bin/%s", commandst.substr(0, commandst.find_first_of(" ")))))) system(sprintf("/dsterm/usr/bin/%s %s %s", current_directory, commandst.substr(0, commandst.find_first_of(" ")), current_directory, commandst.substr(commandst.find_first_of(" ") + 1)));
        else if (fexists(std::string(sprintf("/dsterm/bin/%s", current_directory, commandst.substr(0, commandst.find_first_of(" ")))))) system(sprintf("/dsterm/bin/%s %s %s", current_directory, commandst.substr(0, commandst.find_first_of(" ")), current_directory, commandst.substr(commandst.find_first_of(" ") + 1)));
        else if (command[0] == 'c' && command[1] == 'd' && command[2] == ' ') {
            if (command[3] == '/') current_directory = commandst.substr(4);
            else current_directory += commandst.substr(4);
        }
        else if (command[0] == 'h' && command[1] == 'e' && command[2] == 'l' && command[3] == 'p') {
            // Help
        }
        else printf("3DSTerm: unrecognized command %s. Please check that it exists.\n", commandst);
        command.clear();
    }
end:
    gfxEnd();
    return 0;
}