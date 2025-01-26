#include <stdio.h>
#include <stdlib.h>
#include <windows.h> // For Sleep()
#include <conio.h>   // For _kbhit()

void printBoard(char board[][64]) {  
    for (int i = 0; i < 15; i++) {  
        for (int j = 0; j < 64; j++) {  
            switch (board[i][j]) {  
                case '1': printf("🟫"); break;  
                case '2': printf("🟩"); break;  
                case '3': printf("📀"); break;  
                case '4': printf("⬜️"); break;  
                case '5': printf("🐙"); break;  
                case '6': printf("🐲"); break;  
                case '7': printf("🎑"); break;  
                case '8': printf("🟧"); break;  
                case '9': printf("🚩"); break;  
                case '!': printf("🟨"); break;  
                case '$': printf("🐱"); break;  
                case ' ': printf("  "); break;  
                default: break;  
            }  
        }  
        printf("\n"); // Move to the next line
    }  
} 

void toggleEmoji(char board[][64], int i, int j, char newEmoji) {
    // Replace the emoji at position (i, j) with the new emoji
    board[i][j] = newEmoji;
}

void map1() {  
    SetConsoleOutputCP(CP_UTF8);  
    DWORD bytes_written;
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);  

    char board[15][64] = {  
        "1111111111111111111111111111111111111111111111111111111111111111",  
        "1                       22                                     1",  
        "1                       22                                     1",  
        "1                      2222                                    1",  
        "1                 9         33              7                  1",  
        "1                111        111           4444                 1",  
        "1                      111                 44                  1",  
        "1                                     4444 44                  1",  
        "1                                      44  44                  1",  
        "1   11133                          7   44  44                  1",  
        "1      11!1                       4444 44  44     1881         1",  
        "1          111                     44  44  44     1  1    2222 1",  
        "1                            4444  44  44  44     1  1     22  1",  
        "1 $             33       5    44 6 446 446 446    1        22  1",  
        "1111111111111111111111111111111111111111111111111111111111111111"  
    };  

    // Coordinates of the emojis '7' (🎑)
    int emoji1_i = 4;  // Row 4
    int emoji1_j = 44; // Column 42

    int emoji2_i = 9;  // Row 9
    int emoji2_j = 35; // Column 28

    // Print the initial board
    printBoard(board);

    // Loop to toggle the emojis every 2 seconds
    while (1) {  
        // Hide the emojis (replace with space)
        toggleEmoji(board, emoji1_i, emoji1_j, ' ');
        toggleEmoji(board, emoji2_i, emoji2_j, ' ');

        // Print the updated board
        COORD origin = {0, 1}; // Reset cursor to top-left corner
        SetConsoleCursorPosition(hStdout, origin);  
        printBoard(board);

        // Wait for 2 seconds
        Sleep(2000); // 2000 milliseconds = 2 seconds

        // Show the emojis (replace with '7')
        toggleEmoji(board, emoji1_i, emoji1_j, '7');
        toggleEmoji(board, emoji2_i, emoji2_j, '7');

        // Print the updated board
        SetConsoleCursorPosition(hStdout, origin);  
        printBoard(board);

        // Wait for 2 seconds
        Sleep(2000); // 2000 milliseconds = 2 seconds

    }  
}

int main() {  
    map1();  
    return 0;  
}