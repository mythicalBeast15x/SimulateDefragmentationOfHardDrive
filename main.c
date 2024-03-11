//-----------------------------------------------------------------------------
//	Love-Divine Onwulata	Spring 2024
//
//	Code to simulate the Defragmentation Progress of a hard drive
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#define topLeft 201
#define topRight 187
#define bottomLeft 200
#define bottomRight 188
#define whitespace 32
#define horizontal 205
#define vertical 186
#define leftConnector 204
#define rightConnector 185
#define maxHorizontal 63
#define maxVertical 28
void gotoxy(short x, short y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void printRow(int length, short x, short y, int leftChar, int rightChar, int filler, bool hasFiller){
    //buffer
    /*
    for(int b = 0; b < bufferNum; b++){
        printf("%c", whitespace);
    }*/
    //first row
    gotoxy(x, y);
    printf("%c", leftChar);
    if(hasFiller){
        for(int c = 0; c < length; c++){
            gotoxy(x+c+1, y);
            printf("%c", filler);
        }
    }

    gotoxy(x+length, y);
    printf("%c", rightChar);
    printf("\n");
}
bool makeBox(int x, int y, int rows, int cols){
    bool canMake = false;
    if(x >= 0 && y >= 0 && x+cols < maxHorizontal-2 && (y+((2*rows)-1)) <= maxVertical-2){
        for(int b = 0; b < y; b++){
            printf("\n");
        }
        //top row
        printRow(cols, x, y, topLeft, topRight, horizontal, true);
        //rows
        for(int r = 0; r < rows-1; r++){
            printRow(cols, x, y+((2*r)+1), vertical, vertical, whitespace, true);
            printRow(cols, x, y+((2*r)+2), leftConnector, rightConnector, horizontal, true);
            //getchar();
        }

        //lastrow
        printRow(cols, x, y+((2*rows)-1), vertical, vertical, whitespace, true);
        printRow(cols, x, y+(2*rows),bottomLeft, bottomRight, horizontal, true);
        //getchar();

        canMake = true;
    }
    return canMake;
}

void clearBoxes(int x, int y, int rows, int cols){

    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols-1; c++){
            gotoxy((x+1+c), (y+(2*r)+1));
            printf("%c", whitespace);
        }
    }
}
struct process{
    char name;
    int startLocation;
    int fileSize;
};
int main() {
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, 480, 500, TRUE);

    char hard_drive[] = {'A', 'B', 'B', ' ', 'D',
                         ' ', 'X', 'X', ' ', 'E',
                         'F', 'G', ' ', 'H', 'H',
                         'J', 'J', ' ', ' ', ' ',
                         'J', 'K', 'K', 'J', 'L',
                         'L', 'L', ' ', 'M', 'M',
                         'P', 'P', 'M', 'P', 'P',
                         ' ', ' ', 'R', ' ', ' '};


    bool inProgress = true;
    printf("Welcome! This program will add, delete and defragment your hard drive.");
    while(inProgress){
        makeBox(10 ,10,2,40);
        struct process processInfo[40]; //maximum possible processes
        int infoIndex = -1;
        int freeSpace = 0;

        //initial print
        for(int x = 0; x < sizeof(hard_drive); x++){
            //print array
            if(x < 20){
                gotoxy(11+(2*x),11);
            }else{
                gotoxy((11+(2*(x-20))),13);
            }
            if(x == 19 || x == 39){
                printf("%c", hard_drive[x]);
            }else {
                printf("%c ", hard_drive[x]);
            }
            //index array
            bool inList = false;
            int y = 0;
            while(y <= infoIndex && !inList){
                if(hard_drive[x] == processInfo[y].name || hard_drive[x] == ' '){

                    inList = true;
                    if(hard_drive[x] == processInfo[y].name){
                        processInfo[y].fileSize++;

                    }else{
                        freeSpace++;
                    }

                }else{
                    //printf(".%c:%c no-match", hard_drive[x], processInfo[y].name);
                    y++;
                }
            }
            if(!inList){
                infoIndex++;
                struct process newProcess = {hard_drive[x], x, 1};
                processInfo[infoIndex] =  newProcess;
            }

        }

        gotoxy(0,1);
        printf("Enter (A) to Add a file\nEnter (B) to Delete a file\nEnter (C) to Defragment the hard drive\nEnter (D) to Exit\n");
        char option = getchar();
        getchar();
        switch(option){
            case 'A':
            case 'a':
                system("cls");
                printf("Filename(1 char): ");
                char filename = getchar();
                getchar();
                printf("file size: ");
                int fileSize;
                scanf("%d", &fileSize);

                getchar();

                for(int x = 0; x < sizeof(hard_drive); x++){
                    //index array
                    bool inList = false;
                    int y = 0;
                    while(y <= infoIndex && !inList){
                        if(hard_drive[x] == processInfo[y].name || hard_drive[x] == ' '){

                            inList = true;
                            if(hard_drive[x] == processInfo[y].name){
                                processInfo[y].fileSize++;

                            }else{
                                freeSpace++;
                            }

                        }else{
                            //printf(".%c:%c no-match", hard_drive[x], processInfo[y].name);
                            y++;
                        }
                    }
                    if(!inList){
                        infoIndex++;
                        struct process newProcess = {hard_drive[x], x, 1};
                        processInfo[infoIndex] =  newProcess;
                    }

                }
                if(freeSpace > fileSize){
                    bool exists = false;
                    for(int b = 0; b <= infoIndex; b++){
                        if(processInfo[b].name == filename){
                            exists = true;
                        }
                    }
                    if(!exists){
                        for(int t = 0; t < fileSize; t++){
                            for(int c = 0; c < sizeof(hard_drive); c++){
                                if(hard_drive[c] == ' '){
                                    hard_drive[c] = filename;
                                    break;
                                }
                            }
                        }
                        system("cls");

                        makeBox(10 ,10,2,40);
                        struct process processInfo[40]; //maximum possible processes
                        int infoIndex = -1;
                        int freeSpace = 0;

                        //initial print
                        for(int x = 0; x < sizeof(hard_drive); x++) {
                            //print array
                            if (x < 20) {
                                gotoxy(11 + (2 * x), 11);
                            } else {
                                gotoxy((11 + (2 * (x - 20))), 13);
                            }
                            if (x == 19 || x == 39) {
                                printf("%c", hard_drive[x]);
                            } else {
                                printf("%c ", hard_drive[x]);
                            }
                        }
                        gotoxy(0,15);
                        printf("File Added Successfully");
                    }else{
                        printf("File already exists!");
                    }
                }else{
                    printf("File exceeds space on hard drive!");
                }
                gotoxy(0,16);
                printf("Press Enter to Continue:");
                getchar();
                break;
            case 'B':
            case 'b':
                system("cls");
                printf("Filename(1 char): ");
                char delFile = getchar();
                getchar();
                for(int x = 0; x < sizeof(hard_drive); x++){
                    //index array
                    bool inList = false;
                    int y = 0;
                    while(y <= infoIndex && !inList){
                        if(hard_drive[x] == processInfo[y].name || hard_drive[x] == ' '){

                            inList = true;
                            if(hard_drive[x] == processInfo[y].name){
                                processInfo[y].fileSize++;

                            }else{
                                freeSpace++;
                            }

                        }else{
                            //printf(".%c:%c no-match", hard_drive[x], processInfo[y].name);
                            y++;
                        }
                    }
                    if(!inList){
                        infoIndex++;
                        struct process newProcess = {hard_drive[x], x, 1};
                        processInfo[infoIndex] =  newProcess;
                    }

                }
                bool exists = false;
                for(int b = 0; b <= infoIndex; b++){
                    if(processInfo[b].name == delFile){
                        exists = true;
                    }
                }
                if(exists){
                    int startingIndex = 0;
                    int u = 0;
                    while(processInfo[u].name != delFile){
                        u++;
                    }
                    startingIndex = processInfo[u].startLocation;
                    for(int h = startingIndex; h < sizeof(hard_drive); h++){
                        if(hard_drive[h] == delFile){
                            hard_drive[h] = ' ';
                        }
                    }
                    system("cls");
                    makeBox(10 ,10,2,40);
                    for (int x = 0; x < sizeof(hard_drive); x++) {
                        // Print array
                        if (x < 20) {
                            gotoxy(11 + (2 * x), 11);
                        } else {
                            gotoxy((11 + (2 * (x - 20))), 13);
                        }

                        if (x == 19 || x == 39) {
                            printf("%c", hard_drive[x]);
                        } else {
                            printf("%c ", hard_drive[x]);
                        }
                    }
                    gotoxy(0,15);
                    printf("File Deleted Successfully");
                }else{
                    printf("File does not exist!");
                }
                gotoxy(0,16);
                printf("Press Enter to Continue:");
                getchar();
                break;
            case 'C':
            case 'c':
                system("cls");
                makeBox(10 ,10,2,40);
                struct process processInfo[40]; //maximum possible processes
                int infoIndex = -1;
                int freeSpace = 0;

                //initial print
                for(int x = 0; x < sizeof(hard_drive); x++){
                    //print array
                    if(x < 20){
                        gotoxy(11+(2*x),11);
                    }else{
                        gotoxy((11+(2*(x-20))),13);
                    }
                    if(x == 19 || x == 39){
                        printf("%c", hard_drive[x]);
                    }else {
                        printf("%c ", hard_drive[x]);
                    }
                    //index array
                    bool inList = false;
                    int y = 0;
                    while(y <= infoIndex && !inList){
                        if(hard_drive[x] == processInfo[y].name || hard_drive[x] == ' '){

                            inList = true;
                            if(hard_drive[x] == processInfo[y].name){
                                processInfo[y].fileSize++;

                            }else{
                                freeSpace++;
                            }

                        }else{
                            //printf(".%c:%c no-match", hard_drive[x], processInfo[y].name);
                            y++;
                        }
                    }
                    if(!inList){
                        infoIndex++;
                        struct process newProcess = {hard_drive[x], x, 1};
                        processInfo[infoIndex] =  newProcess;
                    }

                }
                int nextProcessIndex = 0;
                int swaps = 0;
                for (int x = 0; x <= infoIndex; x++) {
                    char processChar = processInfo[x].name;
                    int numBits = processInfo[x].fileSize;
                    processInfo[x].startLocation = nextProcessIndex;
                    if (processChar != ' ') {
                        int fileLocations[numBits];
                        int next_loc_index = 0;

                        // Get file locations
                        for (int y = 0; y < sizeof(hard_drive); y++) {
                            if (hard_drive[y] == processChar) {
                                fileLocations[next_loc_index] = y;
                                next_loc_index++;
                            }
                        }

                        // Perform swaps
                        for (int z = 0; z < numBits; z++) {
                            if (hard_drive[nextProcessIndex] != processChar) {
                                // Swap
                                swaps++;
                                char tempChar = hard_drive[nextProcessIndex];
                                hard_drive[nextProcessIndex] = hard_drive[fileLocations[z]];
                                hard_drive[fileLocations[z]] = tempChar;
                            }
                            // Go to the next space
                            nextProcessIndex++;
                        }
                    } else {
                        // Skip empty spaces
                        nextProcessIndex++;
                    }
                }

                // Reprint Defrag
                for (int x = 0; x < sizeof(hard_drive); x++) {
                    // Print array
                    if (x < 20) {
                        gotoxy(11 + (2 * x), 11);
                    } else {
                        gotoxy((11 + (2 * (x - 20))), 13);
                    }

                    if (x == 19 || x == 39) {
                        printf("%c", hard_drive[x]);
                    } else {
                        printf("%c ", hard_drive[x]);
                    }
                }
                gotoxy(0,15);
                printf("Swaps: %d", swaps);
                gotoxy(0,16);
                for(int q = 0; q < infoIndex; q++){
                    printf("%c loc: %d ", processInfo[q].name, processInfo[q].startLocation);
                }
                gotoxy(0,18);
                printf("Press Enter to Continue:");
                getchar();
                break;
            case 'D':
            case 'd':
                inProgress = false;
                break;
            default:
                break;
        }
        system("cls");



    }
    // defragment
    //defragment hard drive;


    /*

    gotoxy(10, 15);
    for (int x = 0; x <= infoIndex; x++) {
        printf("%d ", processInfo[x].fileSize);
    }
     */



    getchar();

    return 0;
}
