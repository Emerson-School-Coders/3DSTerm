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
#include <cstring>
#include <map>
#include <vector>
#include <3ds.h>
#include <sys/unistd.h>
#ifndef _SYS_UNISTD_H_
#include <unistd.h>
#endif
#include "../3DSTerm.hpp"

std::string current_directory = "/";
std::vector<char> command;
char text_buf;
std::ofstream out;

int main(int argc, char** argv[]) {
    gfxInitDefault();
    //Initialize console on top screen. Using NULL as the second argument tells the console library to use the internal console structure as current one
    consoleInit(GFX_TOP, &console);
    consoleInit(GFX_BOTTOM,&keyboard);
    consoleSelect(&keyboard);
    printf(keyboardLow.c_str());
    consoleSelect(&console);
    printf("Console type: %s\nWelcome to 3DSTerm! Use the keyboard below to type your command, and press A to enter the command.\nType 'help' for more help. Press B to delete a character, Start to quit, and the X button is the control key.\nIf your letter does not pop up, press somewhere else on the key.\n",consoletype?"New3DS. Good job!":"Old3DS. This may be a bit slow.");
    // Main loop
    while (aptMainLoop()) {
        printf("3DSTerm: %s $ _", current_directory.c_str());
        // Get the inputted command
        do {
			/*printf("new loop");
			usleep(5000000);
			printf("\b\b\b\b\b\b\b\b");*/
			text_buf = '\0';
            text_buf = getChar(caps);
            if ((caps == 0 && text_buf == 'E') || (caps != 0 && text_buf == 'e')) {command.pop_back(); printf("\b\b_"); continue;}
            if ((caps == 0 && text_buf == 'D') || (caps != 0 && text_buf == 'd')) {
                printf("Would you like to quit? Press B to quit, or anything else to continue.");
                if (isButtonPressed('b')) goto end;
            }
			if ((caps == 0 && text_buf == '!') || (caps != 0 && text_buf == '1')) {printf("return pressed\n"); break;}
            else if (((caps == 0 && text_buf != 'A') || (caps != 0 && text_buf != 'a')) && ((caps == 0 && text_buf != 'B') || (caps != 0 && text_buf != 'b')) && ((caps == 0 && text_buf != 'C') || (caps != 0 && text_buf != 'c')) && ((caps == 0 && text_buf != 'D') || (caps != 0 && text_buf != 'd')) && text_buf != '\0') {command.push_back(text_buf); if (text_buf != '\0') printf("\b%c_", text_buf);}
			//else {if (text_buf != '\0') printf("Other key pressed: %c", text_buf); else printf("Other key pressed: X"); usleep(1000000); printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");}
			usleep(500000);
        } while (true);
		if ((caps == 0 && text_buf == '!') || (caps != 0 && text_buf == '1')) {printf("done!"); usleep(5000000); printf("\b\b\b\b\b");}
        // Now to run it
        std::string commandst(command.begin(), command.end());
		char commandch[command.size()];
		for (int i = 0; i < command.size(); i++) commandch[i] = command[i];
		char *current_dirch=new char[current_directory.size()+1];
		current_dirch[current_directory.size()]=0;
		memcpy(current_dirch,current_directory.c_str(),current_directory.size());
        if (fexists(std::string(strcat(current_dirch, commandch)))) system(current_dirch);
		if (fexists(std::string(strcat("/dsterm/usr/bin/", commandch)))) system(strcat("/dsterm/usr/bin/", commandch));
		if (fexists(std::string(strcat("/dsterm/bin/", commandch)))) system(strcat("/dsterm/bin/", commandch));
        else if (command[0] == 'c' && command[1] == 'd' && command[2] == ' ') {
            if (command[3] == '/') current_directory = commandst.substr(4);
            else current_directory += commandst.substr(4);
			out.open("/dsterm/curdir", std::fstream::trunc);
			out << current_directory;
			out.close();
        }
        else if (command[0] == 'h' && command[1] == 'e' && command[2] == 'l' && command[3] == 'p') {
            // Help
        }
        else printf("3DSTerm: unrecognized command %s. Please check that it exists.\n", commandst.c_str());
        command.clear();
    }
end:
    gfxExit();
    return 0;
}