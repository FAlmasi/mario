#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
int coin_count = 0;
int cat_lives = 3;
int offsetX = 0;
int shield = 0;
int score_count = 0;
int mapindex = 1;
int game_over = 0; // flag for game over

void moveCharacter(int *i, int *j, char board[][64], int newI, int newJ);
void printheaet(int n)
{
    for (int i = 0; i < n; ++i)
    {
        printf("❤️");
    }
}

// Function to display the remaining time on the screen
void printTimeRemaining(DWORD startTime)
{
    DWORD elapsedTime = GetTickCount() - startTime;
    int timeLeftInSeconds = 1200 - (elapsedTime / 1000); // 120 seconds = 2 minutes

    if (timeLeftInSeconds <= 0)
    {
        timeLeftInSeconds = 0;
        game_over = 1; // Set game over flag
    }

    // Calculate minutes and seconds
    int minutes = timeLeftInSeconds / 60;
    int seconds = timeLeftInSeconds % 60;

    // Print time in 1:50 format
    printf("Time: %02d:%02d\n", minutes, seconds);
}

void moveMush(char map_2[][64], int char_i, int char_j, int flag, int random)
{

    map_2[char_i - 2][char_j] = '^'; // as mushroom
    if (random == 1)
    {
        switch (flag)
        {
        case 1:
            map_2[char_i - 2][char_j] = '^'; // as mushroom
            Sleep(200);
            break;
        case 2:
            map_2[char_i - 2][char_j] = ' ';
            map_2[char_i - 2][char_j] = ' ';
            map_2[char_i - 2][char_j + 1] = '^';
            Sleep(200);
            break;
        case 3:
            map_2[char_i - 2][char_j] = ' ';
            map_2[char_i - 2][char_j + 1] = ' ';
            map_2[char_i - 2][char_j + 2] = '^';
            Sleep(200);
            break;
        case 4:
            map_2[char_i - 2][char_j] = ' ';
            map_2[char_i - 2][char_j + 2] = ' ';
            map_2[char_i - 1][char_j + 2] = '^';
            Sleep(30);
            break;
        case 5:
            map_2[char_i - 2][char_j] = ' ';
            map_2[char_i - 1][char_j + 2] = ' ';
            map_2[char_i][char_j + 2] = '^';
            Sleep(30);
            break;
        }
    }
    else if (random == 0)
    {
        switch (flag)
        {
        case 1:
            map_2[char_i - 2][char_j] = '^'; // as mushroom
            Sleep(200);
            break;
        case 2:
            map_2[char_i - 2][char_j] = ' ';
            map_2[char_i - 2][char_j - 1] = '^';
            Sleep(200);
            break;
        case 3:
            map_2[char_i - 2][char_j] = ' ';
            map_2[char_i - 2][char_j - 1] = ' ';
            map_2[char_i - 2][char_j - 2] = '^';
            Sleep(200);
            break;
        case 4:
            map_2[char_i - 2][char_j] = ' ';
            map_2[char_i - 2][char_j - 2] = ' ';
            map_2[char_i - 1][char_j - 2] = '^';
            Sleep(30);
            break;
        case 5:
            map_2[char_i - 2][char_j] = ' ';
            map_2[char_i - 1][char_j - 2] = ' ';
            map_2[char_i][char_j - 2] = '^';
            Sleep(30);
            break;
        }
    }
}

void coin_block1(char map_1[][64], int char_i, int char_j)
{
    static int hit_num = 0;
    if (hit_num >= 5)
    {
        return;
    }
    hit_num++;
    if (char_i > 0 && map_1[char_i - 1][char_j] == '!')
    {
        coin_count++;
    }
}
void coin_block2(char map_2[][64], int char_i, int char_j)
{
    static int hit_num = 0;
    if (hit_num >= 5)
    {
        return;
    }
    hit_num++;
    if (char_i > 0 && map_2[char_i - 1][char_j] == '!')
    {
        coin_count++;
    }
}
void printBoard(char board[][64], int cory)
{
    for (int i = 0; i < cory; i++)
    {
        for (int j = 0; j < 64; j++)
        {
            switch (board[i][j])
            {
            case '1':
                printf("🧱");
                break;
            case '2':
                printf("🟩");
                break;
            case '3':
                printf("📀");
                break;
            case '4':
                printf("⬜");
                break;
            case '5':
                printf("🐙");
                break;
            case '6':
                printf("🐲");
                break;
            case '7':
                printf("🎑");
                break;
            case '8':
                printf("🟧");
                break;
            case '9':
                printf("🚩");
                break;
            case '!':
                printf("🟨");
                break;
            case '&':
                printf("🟨");
                break;
            case '$':
                printf("🐱");
                break;
            case ' ':
                printf("  ");
                break;
            case '*':
                printf("🛡️");
                break;
            case '@':
                printf("🟦");
                break;
            case '^':
                printf("🍄");
                break;
            default:
                break;
            }
        }
        printf("\n");
    }
    printf("coin: %d        score: %d        lives: %d      ", coin_count, score_count, cat_lives);
}
void moveBlock5(char board[][64], int *block5_i, int *block5_j, DWORD *lastUpdate, int delay, int *catY, int *catX, int *direction)
{
    int new_j = *block5_j;
    if (*block5_i == 12 && *block5_j == 44 && *direction == -1)
    {
        *direction *= -1;
    }
    else if (*block5_i == 10 && *block5_j == 38 && *direction == 1)
    {
        *direction *= -1;
    }
    if (GetTickCount() - *lastUpdate >= delay)
    {

        if (*direction == 1 && new_j > 0 && board[*block5_i][new_j - 1] == ' ')
        {
            new_j--;
        }
        else if (*direction == -1 && new_j < 63 && board[*block5_i][new_j + 1] == ' ')
        {
            new_j++;
        }
        else
        {
            *direction *= -1;
        }
        if (new_j != *block5_j)
        {
            board[*block5_i][*block5_j] = ' ';
            *block5_j = new_j;
            board[*block5_i][*block5_j] = '5';
        }
        // else if ()
        // {
        //     board[*][*] = ' ';
        //     if (mapindex == 1)
        //         *i = 13;
        //     else
        //         *i = 12;
        //     *j = 1;
        //     board[*i][*j] = '$';
        // }

        *lastUpdate = GetTickCount();
    }
    if (*direction == 1 && new_j > 0 && (board[*block5_i][new_j - 1] == '$' || board[*block5_i][new_j + 1] == '$'))
    {
        cat_lives--;
        board[*catY][*catX] = ' ';
        if (mapindex == 1)
            *catY = 13;
        else
            *catY = 12;
        *catX = 1;
        board[*catY][*catX] = '$';
    }
    else if (*direction == -1 && new_j < 63 && board[*block5_i][new_j - 1] == '$' || board[*block5_i][new_j + 1] == '$')
    {
        cat_lives--;
        board[*catY][*catX] = ' ';
        if (mapindex == 1)
            *catY = 13;
        else
            *catY = 12;
        *catX = 1;
        board[*catY][*catX] = '$';
    }
}
void updateBlockStatus(char board[][64], DWORD *lastUpdate, int delay, int *toggle, int emoji1_i, int emoji1_j, int emoji2_i, int emoji2_j, int *i, int *j)
{
    if (GetTickCount() - *lastUpdate >= delay)
    {
        *toggle = !*toggle;
        if (*toggle)
        {
            if (board[emoji1_i][emoji1_j] == '$')
            {
                --cat_lives;
                *i = 13;
                *j = 1;
                board[*i][*j] = '$';
            }
            board[emoji1_i][emoji1_j] = '7';
            if (board[emoji2_i][emoji2_j] == '$')
            {
                --cat_lives;
                *i = 13;
                *j = 1;
                board[*i][*j] = '$';
            }
            board[emoji2_i][emoji2_j] = '7';
        }
        else
        {
            board[emoji1_i][emoji1_j] = ' ';
            board[emoji2_i][emoji2_j] = ' ';
        }
        *lastUpdate = GetTickCount();
    }
}
void map2()
{
    SetConsoleOutputCP(CP_UTF8);
    DWORD bytes_written;
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    mapindex = 2;
    char board[27][64] = {
        "1111111111111111111111111111111111111111111111111111111111111111",
        "1                                                       1    @ 1",
        "1                                                       1    @@1",
        "1                                                       1    @@1",
        "1                      @@@@        118                  1    @ 1",
        "1                       @@  111                         1 9    1",
        "1       11811           @@ 1   111     1&1              11111111",
        "1                      11111     11        6                   1",
        "1   111   1                     3 111111111111111!11111        1",
        "1  3                             1                    11       1",
        "1  1                      2222  11                 11 1 11  *111",
        "1                          22 11      111111111111111 1  111   1",
        "1              3           22                     1   3        1",
        "1111111111111111111111111111 11111111111111111111 11111111111111",
        "1111111111111111111111111111 11111111111111111111 11111111111111",
        "                           1                     21",
        "                           1                     21",
        "                           1                     21",
        "                           1                     21",
        "                           1                     21",
        "                           1                   3 21",
        "                           1                  31 21",
        "                           1             611 11  21",
        "                           1           6111      21",
        "                           1         311        221",
        "                           1         1         3221",
        "                           111111111111111111111111",

    };
    int catX = 1;
    int catY = 12;
    COORD origin = {0, 1};
    SetConsoleCursorPosition(hStdout, origin);
    board[catY][catX] = '$';
    int block5_1i = 12; // موقعیت اولیه بلوک ۵ (ردیف)
    int block5_1j = 12;
    int block5_2i = 25; // موقعیت اولیه بلوک ۵ (ردیف)
    int block5_2j = 36;
    int block5_3i = 12; // موقعیت اولیه بلوک ۵ (ردیف)
    int block5_3j = 44;
    int block5_4i = 10;
    int block5_4j = 49;
    // موقعیت اولیه بلوک ۵ (ستون)
    DWORD lastBlock5Update1 = GetTickCount();
    DWORD lastBlock5Update2 = GetTickCount();
    DWORD lastBlock5Update3 = GetTickCount();
    DWORD lastBlock5Update4 = GetTickCount();
    int block5Delay = 300; // تأخیر بین حرکات بلوک ۵ (میلی‌ثانیه)
    int block5_1Removed = 0;
    int block5_2Removed = 0;
    int block5_3Removed = 0;
    int block5_4Removed = 0;
    SetConsoleCursorPosition(hStdout, origin);
    board[catY][catX] = '$';
    board[block5_1i][block5_1j] = '5';
    board[block5_2i][block5_2j] = '5';
    board[block5_3i][block5_3j] = '5';
    board[block5_4i][block5_4j] = '5';
    int direction1 = -1;
    int direction2 = -1;
    int direction3 = -1;
    int direction4 = -1;
    printBoard(board, 27);
    DWORD startTime = GetTickCount(); // Start time for the 2-minute timer
    DWORD lastUpdate = GetTickCount();
    DWORD delay = 2000;
    int toggle = 0;
    int jumpflag = 0;
    int height = 0;
    int flagfall = 0;
    int mushflag = 0;
    int mushX = 0;
    int mushY = 0;

    srand(time(NULL));
    int random = rand() % 2;
    while (!game_over) // Continue until game over
    {
        SetConsoleCursorPosition(hStdout, origin);
        printBoard(board, 27);
        printTimeRemaining(startTime); // Display remaining time

        if (!block5_1Removed)
        {
            moveBlock5(board, &block5_1i, &block5_1j, &lastBlock5Update1, block5Delay, &catY, &catX, &direction1);
        }
        if (!block5_2Removed)
        {
            moveBlock5(board, &block5_2i, &block5_2j, &lastBlock5Update2, block5Delay, &catY, &catX, &direction2);
        }
        if (!block5_3Removed)
        {
            moveBlock5(board, &block5_3i, &block5_3j, &lastBlock5Update3, block5Delay, &catY, &catX, &direction3);
        }
        if (!block5_4Removed)
        {
            moveBlock5(board, &block5_4i, &block5_4j, &lastBlock5Update4, block5Delay, &catY, &catX, &direction4);
        }
        if (jumpflag)
        {
            if (flagfall == 0)
            {
                if (board[catY - 1][catX] == '&' && board[mushY][mushX - 2] != '^' && board[mushY][mushX - 2] != '^')
                {
                    if (mushflag == 0)
                    {
                        mushflag++;
                        mushX = catX;
                        mushY = catY;
                    }
                    jumpflag = 0;
                }
                if (board[catY - 1][catX] == '!')
                {
                    coin_block1(board, catY, catX);
                    jumpflag = 0;
                }
                else if (board[catY - 1][catX] != ' ' && board[catY - 1][catX] != '3' && board[catY - 1][catX] != '*')
                {
                    jumpflag = 0;
                }
                else if (height == 4)
                {
                    jumpflag = 0;
                }
                if (jumpflag == 1)
                {
                    moveCharacter(&catY, &catX, board, catY - 1, catX);
                    Sleep(20);
                    ++height;
                }
                else
                {
                    height = 0;
                    flagfall = 1;
                }
            }
        }
        if (mushflag <= 5 && mushflag >= 1)
        {
            moveMush(board, mushY, mushX, mushflag, random);
            if (mushflag >= 5)
            {
                mushflag = 0;
                random = rand() % 2;
            }
            else
                mushflag++;
        }
        if (_kbhit())
        {
            char ch = _getch();
            if (ch == 'w' && catY > 0)
            {
                if (flagfall == 0)
                    jumpflag = 1;
            }
            else if (ch == 's' && catY < 14)
            {
                moveCharacter(&catY, &catX, board, catY + 1, catX);
                Sleep(20);
            }
            else if (ch == 'a' && catX > 0)
            {
                moveCharacter(&catY, &catX, board, catY, catX - 1);
                Sleep(20);
            }
            else if (ch == 'd' && catX < 63)
            {
                moveCharacter(&catY, &catX, board, catY, catX + 1);
                Sleep(20);
            }
        }
        if (catY == 9 && 26 < catX && catX < 29)
        {
            moveCharacter(&catY, &catX, board, 13, 28);
        }
        else if (catX == 47 && 23 < catY && catY < 26)
        {
            moveCharacter(&catY, &catX, board, 14, 49);
            for (int f = 0; f < 3; ++f)
            {
                if (f == 2)
                {
                    moveCharacter(&catY, &catX, board, catY, catX - 1);
                    COORD origin = {0, 1};
                    SetConsoleCursorPosition(hStdout, origin);
                    printBoard(board, 27);
                    break;
                }
                COORD origin = {0, 1};
                SetConsoleCursorPosition(hStdout, origin);
                printBoard(board, 27);
                moveCharacter(&catY, &catX, board, catY - 1, catX);
                Sleep(20);
            }
        }
        else if (catY == 14 && 48 < catX && catX < 50)
        {
            moveCharacter(&catY, &catX, board, 25, 46);
        }
        else if (catY == 3 && 23 < catX && catX < 27)
        {
            moveCharacter(&catY, &catX, board, 3, 60);
        }
        if (jumpflag)
        {
            continue;
        }
         if (board[catY + 1][catX] == ' ' || board[catY + 1][catX] == '3' || board[catY + 1][catX] == '*' || board[catY + 1][catX] == '5'|| board[catY + 1][catX] == '^')
        {
            flagfall = 1;
            moveCharacter(&catY, &catX, board, catY + 1, catX);
            if (board[catY + 1][catX] == '5')
            {
                if (catX == block5_1j)
                {
                    block5_1Removed = 1;
                }
                else if (catX == block5_2j)
                {
                    block5_2Removed = 1;
                }
                else if (catX == block5_3j)
                {
                    block5_3Removed = 1;
                }
                else if (catX == block5_4j)
                {
                    block5_4Removed = 1;
                }
                score_count += 100;
            }
            Sleep(20);
        }
        if (board[catY + 1][catX] != ' ' && board[catY + 1][catX] != '3')
        {
            flagfall = 0;
        }
        if (board[catY + 1][catX] == '7' || board[catY + 1][catX] == '6' || board[catY + 1][catX] == '9')
        {
            moveCharacter(&catY, &catX, board, catY + 1, catX);
        }
    }
}
/*while (1)
{
    COORD origin = {0, 1};
    SetConsoleCursorPosition(hStdout, origin);
    printBoard(board, 27);
    SetConsoleCursorPosition(hStdout, origin);
    updateBlockStatus(board, &lastUpdate, delay, &toggle, emoji1_i, emoji1_j, emoji2_i, emoji2_j, &catY, &catX);
    printBoard(board, 15);
}*/
void map1()
{
    SetConsoleOutputCP(CP_UTF8);
    DWORD bytes_written;
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    char board[15][64] = {
        "1111111111111111111111111111111111111111111111111111111111111111",
        "1                     22                                       1",
        "1                     22                                       1",
        "1                    2222                                      1",
        "1                                           7                  1",
        "1                 9      33               4444                 1",
        "1                111     111               44                  1",
        "1                    111              4444 44                  1",
        "1                                      44  44                  1",
        "1   11133                          7   44  44                  1",
        "1      11!1                       4444 44  44   1881           1",
        "1          111                     44  44  44   1  1      2222 1",
        "1                            4444  44  44  44   1  1       22  1",
        "1               33            44 6 446 446 446  1          22  1",
        "1111111111111111111111111111111111111111111111111111111111111111"};

    int catX = 1;
    int catY = 13;
    int emoji1_i = 4;
    int emoji1_j = 44;
    int emoji2_i = 9;
    int emoji2_j = 35;
    int block5_1i = 13; // موقعیت اولیه بلوک ۵ (ردیف)
    int block5_1j = 20;
    int block5_2i = 13; // موقعیت اولیه بلوک ۵ (ردیف)
    int block5_2j = 53;
    int block5_3i = 13; // موقعیت اولیه بلوک ۵ (ردیف)
    int block5_3j = 54; // موقعیت اولیه بلوک ۵ (ستون)
    DWORD lastBlock5Update1 = GetTickCount();
    DWORD lastBlock5Update2 = GetTickCount();
    DWORD lastBlock5Update3 = GetTickCount(); // زمان آخرین به‌روزرسانی حرکت بلوک ۵
    int block5Delay = 300;                    // تأخیر بین حرکات بلوک ۵ (میلی‌ثانیه)
    int block5_1Removed = 0;
    int block5_2Removed = 0;
    int block5_3Removed = 0;
    COORD origin = {0, 1};
    SetConsoleCursorPosition(hStdout, origin);
    board[catY][catX] = '$';
    board[block5_1i][block5_1j] = '5';
    board[block5_2i][block5_2j] = '5';
    board[block5_3i][block5_3j] = '5';
    int direction1 = 1;
    int direction2 = 1;
    int direction3 = -1;
    printBoard(board, 15);
    DWORD startTime = GetTickCount(); // Start time for the 2-minute timer
    DWORD lastUpdate = GetTickCount();
    DWORD delay = 2000;
    int toggle = 0;
    int jumpflag = 0;
    int height = 0;
    int flagfall = 0;
    srand(time(NULL));
    int random = rand() % 2;
    while (!game_over) // Continue until game over
    {
        COORD origin = {0, 1};
        SetConsoleCursorPosition(hStdout, origin);
        updateBlockStatus(board, &lastUpdate, delay, &toggle, emoji1_i, emoji1_j, emoji2_i, emoji2_j, &catY, &catX);
        printBoard(board, 15);
        printTimeRemaining(startTime); // Display remaining time

        if (!block5_1Removed)
        {
            moveBlock5(board, &block5_1i, &block5_1j, &lastBlock5Update1, block5Delay, &catY, &catX, &direction1);
        }
        if (!block5_2Removed)
        {
            moveBlock5(board, &block5_2i, &block5_2j, &lastBlock5Update2, block5Delay, &catY, &catX, &direction2);
        }
        if (!block5_3Removed)
        {
            moveBlock5(board, &block5_3i, &block5_3j, &lastBlock5Update3, block5Delay, &catY, &catX, &direction3);
        }
        if (jumpflag)
        {
            if (flagfall == 0)
            {
                if (board[catY - 1][catX] == '!')
                {
                    coin_block1(board, catY, catX);
                    jumpflag = 0;
                }
                else if (board[catY - 1][catX] != ' ' && board[catY - 1][catX] != '3' && board[catY - 1][catX] == '*')
                {
                    jumpflag = 0;
                }
                else if (height == 4)
                {
                    jumpflag = 0;
                }
                if (jumpflag == 1)
                {
                    moveCharacter(&catY, &catX, board, catY - 1, catX);
                    Sleep(20);
                    ++height;
                }
                else
                {
                    height = 0;
                    flagfall = 1;
                }
            }
        }
        if (_kbhit())
        {
            char ch = _getch();
            if (ch == 'w' && catY > 0)
            {
                if (flagfall == 0)
                    jumpflag = 1;
            }
            else if (ch == 's' && catY < 14)
            {
                moveCharacter(&catY, &catX, board, catY + 1, catX);
                Sleep(20);
            }
            else if (ch == 'a' && catX > 0)
            {
                moveCharacter(&catY, &catX, board, catY, catX - 1);
                Sleep(20);
            }
            else if (ch == 'd' && catX < 63)
            {
                moveCharacter(&catY, &catX, board, catY, catX + 1);
                Sleep(20);
            }
            if (catY == 10 && 58 < catX && catX < 61)
            {
                moveCharacter(&catY, &catX, board, 4, 22);
            }
        }
        if (jumpflag)
        {
            continue;
        }
        if (board[catY + 1][catX] == ' ' || board[catY + 1][catX] == '3' || board[catY + 1][catX] == '*' || board[catY + 1][catX] == '5')
        {
            flagfall = 1;
            moveCharacter(&catY, &catX, board, catY + 1, catX);
            if (board[catY + 1][catX] == '5')
            {
                if (catX == block5_1j)
                {
                    block5_1Removed = 1;
                }
                else if (catX == block5_2j)
                {
                    block5_2Removed = 1;
                }
                else if (catX == block5_3j)
                {
                    block5_3Removed = 1;
                }
                score_count += 100;
            }
            Sleep(20);
        }
        if (board[catY + 1][catX] != ' ' && board[catY + 1][catX] != '3')
        {
            flagfall = 0;
        }
        if (board[catY + 1][catX] == '7' || board[catY + 1][catX] == '6' || board[catY + 1][catX] == '9')
        {
            moveCharacter(&catY, &catX, board, catY + 1, catX);
        }
    }
}
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
    map2();
    return 0;
}
void moveCharacter(int *i, int *j, char board[][64], int newI, int newJ)
{
    static int check = 1;
    if (board[newI][newJ] == ' ' || board[newI][newJ] == '3' || board[newI][newJ] == '*' || board[newI][newJ] == '5'|| board[newI][newJ] == '^')
    {
        if (board[newI][newJ] == '3')
            coin_count++;
        else if (board[newI][newJ] == '*')
        {
            shield = 1;
        }
        board[*i][*j] = ' ';
        *i = newI;
        *j = newJ;
        board[*i][*j] = '$';
    }
    else if (board[newI][newJ] == '6' || board[newI][newJ] == '7')
    {
        if (shield == 0)
        {
            cat_lives--;
            board[*i][*j] = ' ';
            if (mapindex == 1)
                *i = 13;
            else
                *i = 12;
            *j = 1;
            board[*i][*j] = '$';
        }
        else
        {
            shield = 0;
        }
    }

    else if (board[newI][newJ] == '9')
    {
        system("cls");
        map2();
    }
}