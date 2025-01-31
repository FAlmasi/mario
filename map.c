#include "header.h"

int coin_count = 0;
int cat_lives = 5;
int offsetX = 0;
int shield = 0;
int score_count = 0;
int mapindex = 1;
int game_over = 0;
int sizemario = 1;
int retry_count = 0;
int fail_count = 0;
int shield_delete = 0;
int changesizemario = 0;
int hit = 0;
DWORD startTime;

int map1(int *pusercoin, int *puserscore, int *puserstat1, int *puserstat2)
{

    coin_count = 0;
    offsetX = 0;
    shield = 0;
    score_count = 0;
    mapindex = 1;
    game_over = 0;
    sizemario = 1;
    retry_count = 0;
    fail_count = 0;
    shield_delete = 0;
    changesizemario = 0;

    cat_lives = 5;
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
    int block5_1i = 13;
    int block5_1j = 20;
    int block5_2i = 13;
    int block5_2j = 53;
    int block5_3i = 13;
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
    startTime = GetTickCount(); // Start time for the 2-minute timer
    DWORD lastUpdate = GetTickCount();
    DWORD delay = 2000;
    int toggle = 0;
    int jumpflag = 0;
    int height = 0;
    int flagfall = 0;
    DWORD time1 = 0;
    DWORD time2 = 0;
    float difftime;
    int maxscore = 100;
    srand(time(NULL));
    int random = rand() % 2;
    coin_block(board, catY, catX, 1, 0);
    while (!game_over) // Continue until game over
    {
        if (board[catY][catX - 1] == '9' || board[catY][catX + 1] == '9' || board[catY + 1][catX] == '9')
        {
            DWORD time_life = 300 - (GetTickCount() - startTime) / 1000;
            score_count = (time_life / 10) * 100 + cat_lives * 1000;
            system("cls");
            return firstlevelPassed(pusercoin, puserscore, puserstat1, puserstat2);
            break;
        }
        if (cat_lives <= 0)
            break;
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
                    coin_block(board, catY, catX, 1, 1);
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
            checkCheatCode(ch); // بررسی چیت کد

            if ((ch == 'w' || ch == 'W' || ch == ' ') && catY > 0)
            {
                if (flagfall == 0)
                    jumpflag = 1;
            }
            else if ((ch == 'a' || ch == 'A') && catX > 0)
            {

                if (board[catY][catX - 1] == '5')
                {
                    cat_lives--;
                    board[catY][catX] = ' ';
                    catY = 12;
                    catX = 1;
                    offsetX = 0;
                    board[catY][catX] = '$';
                    continue;
                }
                moveCharacter(&catY, &catX, board, catY, catX - 1);
                Sleep(20);
            }
            else if ((ch == 'd' || ch == 'D') && catX < 63)
            {

                if (board[catY][catX + 1] == '5')
                {
                    cat_lives--;
                    board[catY][catX] = ' ';
                    catY = 12;
                    catX = 1;
                    offsetX = 0;
                    board[catY][catX] = '$';
                    continue;
                }
                moveCharacter(&catY, &catX, board, catY, catX + 1);
                Sleep(20);
            }
            if (catY == 10 && 58 < catX && catX < 61)
            {
                moveCharacter(&catY, &catX, board, 4, 22);
                offsetX = 10;
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

                time2 = GetTickCount();
                difftime = (time2 - time1) / 1000;
                // printf("\n\ntime1:%11d    time2:%11d    difftime:%f    maxscore:%d", time1, time2, difftime, maxscore);

                if (difftime <= 5)
                {
                    maxscore *= 2;
                }
                else
                {
                    maxscore = 100;
                }

                score_count += maxscore;
                time1 = time2;
                // printf("\n\ntime1:%11d    time2:%11d    difftime:%f    maxscore:%d", time1, time2, difftime, maxscore);
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
    if (cat_lives <= 0 || game_over == 1)
    {
        system("cls");
        *pusercoin += coin_count;
        *puserscore += score_count;
        *puserstat1 = 0;
        *puserstat2 = 0;
        return levelfailed();
    }
}

int map2(int *pusercoin, int *puserscore, int *puserstat1, int *puserstat2)
{
    cat_lives = 5;
    SetConsoleOutputCP(CP_UTF8);
    DWORD bytes_written;
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    mapindex = 2;
    char board[27][64] = {
        "1111111111111111111111111111111111111111111111111111111111111111",
        "1                                                       1    @ 1",
        "1                                                       1    @@1",
        "1                                                       1    @@1",
        "1                      @@@@          118                1    @ 1",
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
        "                           1                     21             ",
        "                           1                     21             ",
        "                           1                     21             ",
        "                           1                     21             ",
        "                           1                     21             ",
        "                           1                   3 21             ",
        "                           1                  31 21             ",
        "                           1             611 11  21             ",
        "                           1           6111      21             ",
        "                           1         311        221             ",
        "                           1         1         3221             ",
        "                           111111111111111111111111             ",

    };
    int catX = 1;
    int catY = 12;
    int catY2 = 0, catX2 = 0;
    COORD origin = {0, 1};
    SetConsoleCursorPosition(hStdout, origin);
    board[catY][catX] = '$';
    int block5_1i = 12;
    int block5_1j = 12;
    int block5_2i = 25;
    int block5_2j = 36;
    int block5_3i = 12;
    int block5_3j = 44;
    int block5_4i = 10;
    int block5_4j = 49;

    DWORD lastBlock5Update1 = GetTickCount();
    DWORD lastBlock5Update2 = GetTickCount();
    DWORD lastBlock5Update3 = GetTickCount();
    DWORD lastBlock5Update4 = GetTickCount();
    int block5Delay = 300;
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
    printBoard(board, 14);
    startTime = GetTickCount(); // Start time for the 2-minute timer
    DWORD lastUpdate = GetTickCount();
    DWORD delay = 2000;
    int toggle = 0;
    int jumpflag = 0;
    int height = 0;
    int flagfall = 0;
    int mushflag = 0;
    int mushX = 0;
    int mushY = 0;
    DWORD time1 = 0;
    DWORD time2 = 0;
    float difftime;
    int maxscore = 100;
    int flags = 0;
    int cory = 14;
    srand(time(NULL));
    int random = rand() % 2;
    coin_block(board, catY, catX, 2, 0);
    while (!game_over) // Continue until game over
    {
        if (board[catY][catX - 1] == '9' || board[catY][catX + 1] == '9' || board[catY + 1][catX] == '9')
        {
            DWORD time_life = 300 - (GetTickCount() - startTime) / 1000;
            score_count += (time_life / 10) * 100 + cat_lives * 1000;
            system("cls");
            return secondlevelPassed(pusercoin, puserscore, puserstat1, puserstat2);
        }
        if (cat_lives <= 0)
            break;
        SetConsoleCursorPosition(hStdout, origin);
        printBoard(board, cory);
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
                if (sizemario == 1)
                {
                    if (board[catY - 1][catX] == '&' && board[catY][catX - 2] != '^' && board[catY][catX + 2] != '^')
                    {
                        if (mushflag == 0)
                        {
                            mushX = catX;
                            mushY = catY;
                            mushflag++;
                        }
                        jumpflag = 0;
                    }
                    if (board[catY - 1][catX] == '!')
                    {
                        coin_block(board, catY, catX, 2, 1);
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
                    if (sizemario == 2)
                    {
                        if (jumpflag)
                        {
                            jumpflag = 0;
                            flagfall = 1;
                        }
                        catY2 = catY - 1;
                        catX2 = catX;
                        board[catY2][catX2] = '$';
                    }
                }
                else if (sizemario == 2)
                {

                    if (board[catY - 2][catX] == '!')
                    {
                        coin_block(board, catY, catX, 2, 1);
                        jumpflag = 0;
                    }
                    else if (board[catY - 2][catX] != ' ' && board[catY - 2][catX] != '3' && board[catY - 2][catX] != '*')
                    {
                        jumpflag = 0;
                    }
                    else if (height == 4)
                    {
                        jumpflag = 0;
                    }
                    if (jumpflag == 1)
                    {

                        moveCharacter(&catY2, &catX2, board, catY2 - 1, catX2);
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
        }

        if (mushflag <= 5 && mushflag >= 1)
        {
            moveMush(board, mushY, mushX, mushflag, random);
            if (sizemario == 2)
            {
                catY2 = catY - 1;
                catX2 = catX;
                board[catY2][catX2] = '$';
            }
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
            checkCheatCode(ch); // بررسی چیت کد

            if ((ch == 'w' || ch == 'W' || ch == ' ') && catY > 0)
            {
                if (flags)
                {
                    board[catY2][catX2] = '$';
                    flags = 0;
                    continue;
                }
                if (flagfall == 0)
                    jumpflag = 1;
            }
            else if ((ch == 's' || ch == 'S') && catY < 26 && sizemario == 2)
            {
                board[catY2][catX2] = ' ';
                flags = 1;
                Sleep(20);
            }
            else if ((ch == 'a' || ch == 'A') && catX > 0)
            {
                if (flags)
                {
                    board[catY2][catX2] = '$';
                    flags = 0;
                    continue;
                }
                if (board[catY][catX - 1] == '5' && sizemario == 1)
                {
                    cat_lives--;
                    board[catY][catX] = ' ';
                    catY = 12;
                    catX = 1;
                    board[catY][catX] = '$';
                    offsetX = 0;
                    if (cat_lives > 0)
                    {
                        hit = 1;
                    }
                }
                if (sizemario == 2)
                {
                    moveCharacter2(&catY, &catX, board, catX - 1, &catY2, &catX2);
                }
                else
                {
                    moveCharacter(&catY, &catX, board, catY, catX - 1);
                }
                Sleep(20);
            }
            else if ((ch == 'd' || ch == 'D') && catX < 63)
            {
                if (flags)
                {
                    board[catY2][catX2] = '$';
                    flags = 0;
                    continue;
                }
                if (board[catY][catX + 1] == '5' && sizemario == 1)
                {
                    cat_lives--;
                    board[catY][catX] = ' ';
                    catY = 12;
                    catX = 1;
                    board[catY][catX] = '$';
                    offsetX = 0;
                    if (cat_lives > 0)
                    {
                        hit = 1;
                    }
                }
                if (sizemario == 2)
                {
                    moveCharacter2(&catY, &catX, board, catX + 1, &catY2, &catX2);
                }
                else
                {
                    moveCharacter(&catY, &catX, board, catY, catX + 1);
                }
                Sleep(20);
            }
            if (sizemario == 2 && flags == 0)
            {
                catY2 = catY - 1;
                catX2 = catX;
                board[catY2][catX2] = '$';
            }
        }
        if (catY == 9 && 26 < catX && catX < 29)
        {
            cory = 27;
            moveCharacter(&catY, &catX, board, 13, 28);
            system("cls");
            continue;
        }
        else if (catX == 47 && 23 < catY && catY < 26)
        {
            moveCharacter(&catY, &catX, board, 14, 49);
            cory = 14;
            system("cls");
            for (int f = 0; f < 3; ++f)
            {
                if (f == 2)
                {
                    moveCharacter(&catY, &catX, board, catY, catX - 1);
                    COORD origin = {0, 1};
                    SetConsoleCursorPosition(hStdout, origin);
                    printBoard(board, cory);
                    break;
                }
                COORD origin = {0, 1};
                SetConsoleCursorPosition(hStdout, origin);
                printBoard(board, cory);
                moveCharacter(&catY, &catX, board, catY - 1, catX);
                Sleep(20);
            }
        }
        else if (catY == 14 && 48 < catX && catX < 50)
        {
            moveCharacter(&catY, &catX, board, 25, 46);
            cory = 27;
            system("cls");
            continue;
        }
        else if (catY == 3 && 23 < catX && catX < 27)
        {
            if (sizemario == 2)
                moveCharacter(&catY2, &catX2, board, 2, 60);
            moveCharacter(&catY, &catX, board, 3, 60);
            offsetX = 30;
        }
        if (jumpflag)
        {
            continue;
        }
        if (board[catY + 1][catX] == '8' && sizemario == 2 && flagfall == 1)
        {
            board[catY + 1][catX] = ' ';
            destructible_block();
        }
        if (board[catY + 1][catX] == ' ' || board[catY + 1][catX] == '3' || board[catY + 1][catX] == '*' || board[catY + 1][catX] == '5' || board[catY + 1][catX] == '^')
        {
            flagfall = 1;
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
                time2 = GetTickCount();
                difftime = (time2 - time1) / 1000;
                // printf("\n\ntime1:%11d    time2:%11d    difftime:%f    maxscore:%d", time1, time2, difftime, maxscore);

                if (difftime <= 5)
                {
                    maxscore *= 2;
                }
                else
                {
                    maxscore = 100;
                }

                score_count += maxscore;
                time1 = time2;
                // printf("\n\ntime1:%11d    time2:%11d    difftime:%f    maxscore:%d", time1, time2, difftime, maxscore);
            }
            moveCharacter(&catY, &catX, board, catY + 1, catX);
            if (sizemario == 2)
            {
                moveCharacter(&catY2, &catX2, board, catY2 + 1, catX2);
            }
            Sleep(20);
        }
        if (board[catY + 1][catX] != ' ' && board[catY + 1][catX] != '3' && board[catY + 1][catX] != '*' && board[catY + 1][catX] != '^')
        {
            if (board[catY + 1][catX] == '8' && sizemario == 2 && flagfall == 1)
            {
                flagfall = 1;
            }
            else
                flagfall = 0;
        }
        if (board[catY + 1][catX] == '6' || board[catY + 1][catX] == '9')
        {
            moveCharacter(&catY, &catX, board, catY + 1, catX);
            if (changesizemario == 1)
            {
                board[catY2][catX2] = ' ';
                board[catY][catX] = ' ';
                catX2 = 0;
                catY2 = 0;
                catX = catX - 1;
                catY = catY + 1;
                board[catY][catX] = '$';
                changesizemario = 0;
            }
            if (shield_delete == 1 && sizemario == 2)
            {
                board[catY2][catX2] = ' ';
                board[catY][catX] = ' ';
                catX = catX - 1;
                catY = catY + 1;
                board[catY][catX] = '$';
                catX2 = catX2 - 1;
                catY2 = catY2 + 1;
                board[catY2][catX2] = '$';
                shield_delete = 0;
            }
            else if (shield_delete == 1 && sizemario == 1 && catX2 == 0)
            {
                board[catY][catX] = ' ';
                catX = catX - 1;
                catY = catY + 1;
                board[catY][catX] = '$';
                shield_delete = 0;
            }
        }
        if (sizemario == 2 && flags == 0)
        {
            catY2 = catY - 1;
            catX2 = catX;
            board[catY2][catX2] = '$';
        }

        if (hit == 1)
        {
            cory = 14;
            hit = 0;
            system("cls");
        }
    }
    if (cat_lives <= 0 || game_over == 1)
    {
        system("cls");
        *pusercoin += coin_count;
        *puserscore += score_count;
        *puserstat1 = 1;
        *puserstat2 = 0;
        return levelfailed();
    }
}

void enableANSI()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
        return;

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
        return;

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

void moveCursor(int x, int y)
{
    printf("\033[%d;%dH", y, x); // ANSI escape code to move cursor
}

void printTimeRemaining()
{
    DWORD elapsedTime = GetTickCount() - startTime;
    int timeLeftInSeconds = 300 - (elapsedTime / 1000); // 120 seconds = 2 minutes

    if (timeLeftInSeconds <= 0)
    {
        timeLeftInSeconds = 0;
        game_over = 1; // Set game over flag
    }

    // Calculate minutes and seconds
    int minutes = timeLeftInSeconds / 60;
    int seconds = timeLeftInSeconds % 60;

    // Print time in 1:50 format
    printf("\n\n🕐 Time: %02d:%02d\n", minutes, seconds);
}

void coin_block(char map_1[][64], int char_i, int char_j, int map, int retry)
{
    if (map == 1)
    {
        static int hit_num = 0;
        if (retry == 0)
        {
            hit_num = 0;
            return;
        }
        if (hit_num >= 5)
        {
            return;
        }
        hit_num++;
        if (char_i > 0 && map_1[char_i - 1][char_j] == '!')
        {
            PlaySoundA(TEXT("coin-block.wav"), NULL, SND_FILENAME | SND_ASYNC);
            coin_count++;
        }
    }
    if (map == 2)
    {
        static int hit_num = 0;
        if (retry == 0)
        {
            hit_num = 0;
            return;
        }
        if (hit_num >= 5)
        {
            return;
        }
        hit_num++;
        if (char_i > 0 && map_1[char_i - 1][char_j] == '!')
        {
            PlaySoundA(TEXT("coin-block.wav"), NULL, SND_FILENAME | SND_ASYNC);
            coin_count++;
        }
    }
}

void destructible_block()
{
    srand(time(NULL));
    int random = rand() % 5;
    if (random == 0)
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
                printf("🟡");
                break;
            case '4':
                printf("⬜");
                break;
            case '5':
                printf("🦀");
                break;
            case '6':
                printf("🦖");
                break;
            case '7':
                printf("🌱");
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
            case '$':
                printf("👻");
                break;
            case ' ':
                printf("  ");
                break;
            case '*':
                printf("🛡️");
                break;
            case '@':
                printf("🟪");
                break;
            case '&':
                printf("🟨");
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
    printf("🟡 coin: %d        💯 score: %d        ❤️  lives: %d      🛡️  shield: %d      ", coin_count, score_count, cat_lives, shield);
    // printf("\n\ntime1:%d    time2:%d    difftime:%d    maxscore:%d", time1, time2, difftime, maxscore);
}

void moveMush(char map_2[][64], int char_i, int char_j, int flag, int random)
{

    map_2[char_i - 2][char_j] = '^'; // as mushroom
    if (random == 1)
    {
        switch (flag)
        {
        case 1:
            map_2[char_i - 2][char_j] = '^';
            Sleep(100);
            break;
        case 2:
            map_2[char_i - 2][char_j] = ' ';
            map_2[char_i - 2][char_j] = ' ';
            map_2[char_i - 2][char_j + 1] = '^';
            Sleep(100);
            break;
        case 3:
            if (map_2[char_i - 2][char_j + 2] == '$')
            {
                map_2[char_i - 2][char_j] = ' ';
                map_2[char_i - 2][char_j + 1] = ' ';
                sizemario = 2;
            }
            else
            {
                map_2[char_i - 2][char_j] = ' ';
                map_2[char_i - 2][char_j + 1] = ' ';
                map_2[char_i - 2][char_j + 2] = '^';
            }
            Sleep(100);
            break;
        case 4:
            if (map_2[char_i - 1][char_j + 2] == '$')
            {
                map_2[char_i - 2][char_j] = ' ';
                map_2[char_i - 2][char_j + 2] = ' ';
                sizemario = 2;
            }
            else
            {
                map_2[char_i - 2][char_j] = ' ';
                map_2[char_i - 2][char_j + 2] = ' ';
                map_2[char_i - 1][char_j + 2] = '^';
            }
            Sleep(15);
            break;
        case 5:
            if (map_2[char_i][char_j + 2] == '$')
            {
                map_2[char_i - 2][char_j] = ' ';
                map_2[char_i - 1][char_j + 2] = ' ';
                sizemario = 2;
            }
            else
            {
                map_2[char_i - 2][char_j] = ' ';
                map_2[char_i - 1][char_j + 2] = ' ';
                map_2[char_i][char_j + 2] = '^';
            }
            Sleep(15);
            break;
        }
    }
    else if (random == 0)
    {
        switch (flag)
        {
        case 1:
            map_2[char_i - 2][char_j] = '^';
            Sleep(100);
            break;
        case 2:
            map_2[char_i - 2][char_j] = ' ';
            map_2[char_i - 2][char_j - 1] = '^';
            Sleep(100);
            break;
        case 3:
            if (map_2[char_i - 2][char_j - 2] == '$')
            {
                map_2[char_i - 2][char_j] = ' ';
                map_2[char_i - 2][char_j - 1] = ' ';
                sizemario = 2;
            }
            else
            {
                map_2[char_i - 2][char_j] = ' ';
                map_2[char_i - 2][char_j - 1] = ' ';
                map_2[char_i - 2][char_j - 2] = '^';
            }
            Sleep(100);
            break;
        case 4:
            if (map_2[char_i - 1][char_j - 2] == '$')
            {
                map_2[char_i - 2][char_j] = ' ';
                map_2[char_i - 2][char_j - 2] = ' ';
                sizemario = 2;
            }
            else
            {
                map_2[char_i - 2][char_j] = ' ';
                map_2[char_i - 2][char_j - 2] = ' ';
                map_2[char_i - 1][char_j - 2] = '^';
            }
            Sleep(15);
            break;
        case 5:
            if (map_2[char_i][char_j - 2] == '$')
            {
                map_2[char_i - 2][char_j] = ' ';
                map_2[char_i - 1][char_j - 2] = ' ';
                sizemario = 2;
            }
            else
            {
                map_2[char_i - 2][char_j] = ' ';
                map_2[char_i - 1][char_j - 2] = ' ';
                map_2[char_i][char_j - 2] = '^';
            }
            Sleep(15);
            break;
        }
    }
}

int moveBlock5(char board[][64], int *block5_i, int *block5_j, DWORD *lastUpdate, int delay, int *catY, int *catX, int *direction)
{
    int new_j = *block5_j;
    if (*block5_i == 12 && *block5_j == 3 && *direction == 1)
    {
        *direction *= -1;
    }
    else if (*block5_i == 12 && *block5_j == 44 && *direction == -1)
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
        *lastUpdate = GetTickCount();
    }

    if (*direction == 1 && new_j > 0 && board[*block5_i][new_j + 1] == '$')
    {
        cat_lives--;
        board[*catY][*catX] = ' ';
        if (mapindex == 1)
        {
            PlaySoundA(TEXT("ooh.wav"), NULL, SND_FILENAME | SND_ASYNC);
            *catY = 13;
        }
        else
        {
            PlaySoundA(TEXT("ooh.wav"), NULL, SND_FILENAME | SND_ASYNC);
            *catY = 12;
        }
        *catX = 1;
        offsetX = 0;
        board[*catY][*catX] = '$';
        if (cat_lives > 0)
        {
            hit = 1;
        }
    }
    else if (*direction == -1 && new_j < 63 && board[*block5_i][new_j - 1] == '$')
    {
        cat_lives--;
        board[*catY][*catX] = ' ';
        if (mapindex == 1)
        {
            PlaySoundA(TEXT("ooh.wav"), NULL, SND_FILENAME | SND_ASYNC);
            *catY = 13;
        }
        else
        {
            PlaySoundA(TEXT("ooh.wav"), NULL, SND_FILENAME | SND_ASYNC);
            *catY = 12;
        }
        *catX = 1;
        offsetX = 0;
        board[*catY][*catX] = '$';
    }
    return 0;
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
                offsetX = 0;
                board[*i][*j] = '$';
            }
            board[emoji1_i][emoji1_j] = '7';
            if (board[emoji2_i][emoji2_j] == '$')
            {
                --cat_lives;
                *i = 13;
                *j = 1;
                offsetX = 0;
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

void moveCharacter(int *i, int *j, char board[][64], int newI, int newJ)
{
    static int check = 1;
    if (board[newI][newJ] == ' ' || board[newI][newJ] == '3' || board[newI][newJ] == '*' || board[newI][newJ] == '5' || board[newI][newJ] == '^' || (sizemario == 2 && board[newI][newJ] == '8'))
    {
        if (board[newI][newJ] == '3')
            coin_count++;
        else if (board[newI][newJ] == '*')
        {
            shield = 1;
        }
        else if (board[newI][newJ] == '^')
        {
            sizemario = 2;
        }

        board[*i][*j] = ' ';
        *i = newI;
        *j = newJ;
        board[*i][*j] = '$';
    }

    else if (board[newI][newJ] == '6' || board[newI][newJ] == '7')
    {
        if (shield == 0 && sizemario == 1)
        {
            cat_lives--;
            board[*i][*j] = ' ';
            if (mapindex == 1)
            {
                PlaySoundA(TEXT("ooh.wav"), NULL, SND_FILENAME | SND_ASYNC);
                *i = 13;
            }
            else
            {
                PlaySoundA(TEXT("ooh.wav"), NULL, SND_FILENAME | SND_ASYNC);
                *i = 12;
            }
            *j = 1;
            offsetX = 0;
            board[*i][*j] = '$';
            if (cat_lives > 0)
            {
                hit = 1;
            }
        }
        else if (shield == 1)
        {
            shield = 0;
            shield_delete = 1;
        }
        else if (sizemario == 2)
        {
            sizemario = 1;
            changesizemario = 1;
        }
    }

    else if (board[newI][newJ] == '9' && mapindex == 1)
    {
        DWORD time_life = 300 - (GetTickCount() - startTime) / 1000;
        score_count = (time_life / 10) * 100 + cat_lives * 1000;
        board[newI][newJ] = ' ';
        system("cls");
        // PlaySoundA(TEXT("C:\\Users\\User\\Downloads\\won2.wav"), NULL, SND_FILENAME | SND_ASYNC);
    }
    else if (board[newI][newJ] == '9' && mapindex == 2)
    {
        DWORD time_life = 300 - (GetTickCount() - startTime) / 1000;
        score_count += (time_life / 10) * 100 + cat_lives * 1000;
        board[newI][newJ] = ' ';
        system("cls");
        // PlaySoundA(TEXT("C:\\Users\\User\\Downloads\\won2.wav"), NULL, SND_FILENAME | SND_ASYNC);
    }
}

void moveCharacter2(int *i, int *j, char board[][64], int newJ, int *i2, int *j2)
{
    if ((board[*i][newJ] == ' ' && board[*i2][newJ] == ' ') || (board[*i][newJ] == ' ' && board[*i2][newJ] == '3') || (board[*i][newJ] == '3' && board[*i2][newJ] == '3'))
    {
        if (board[*i][newJ] == '3')
            coin_count++;
        board[*i][*j] = ' ';
        board[*i2][*j2] = ' ';
        *j = newJ;
        *j2 = newJ;
        board[*i][*j] = '$';
        board[*i2][*j2] = '$';
    }
    else if (board[*i][newJ] == '6')
    {
        if (shield == 1)
        {
            PlaySoundA(TEXT("ooh.wav"), NULL, SND_FILENAME | SND_ASYNC);
            shield = 0;
        }
        else if (sizemario == 2)
        {
            PlaySoundA(TEXT("ooh.wav"), NULL, SND_FILENAME | SND_ASYNC);
            sizemario = 1;
            board[*i2][*j2] = ' ';
        }
    }
    else if (board[*i][newJ] == '9')
    {
        DWORD time_life = 300 - (GetTickCount() - startTime) / 1000;
        score_count += (time_life / 10) * 100 + cat_lives * 1000;
        system("cls");
    }
}

// score page functions
void drawfirstlevel(int select, int retry)
{
    static int reset = 0;
    if (retry == 0)
    {
        reset = 0;
        return;
    }
    system("cls");
    printf(GREEN "LEVEL COMPLETED SUCCESSFULLY!\n\n" YELLOW);

    if (reset == 0)
    {
        Sleep(500);
        printf("COINS: ");
        int currentCoinCount = 0;
        while (currentCoinCount <= coin_count)
        {
            moveCursor(8, 3);
            printf("%d", currentCoinCount);
            fflush(stdout);
            currentCoinCount++;
            Sleep(50);
        }
        Sleep(500);
        printf("\n");
        printf("SCORE: ");
        int currentscoreCount = 0;
        while (currentscoreCount <= score_count)
        {
            moveCursor(8, 4);
            printf("%d", currentscoreCount);
            fflush(stdout);
            currentscoreCount = currentscoreCount + 100;
            Sleep(50);
        }
        Sleep(300);
    }
    else if (reset == 1)
    {
        printf("COIN: %d", coin_count);
        printf("\n");
        printf("SCORE: %d", score_count);
    }
    reset = 1;
    printf(RESET "\n\n");
    if (select == 0)
    {
        printf(PINK "NEXT LEVEL\n" RESET);
    }
    else
    {
        printf("NEXT LEVEL\n");
    }

    if (select == 1)
    {
        printf(PINK "TRY AGAIN\n" RESET);
    }
    else
    {
        printf("RETRY\n");
    }
    if (select == 2)
    {
        printf(PINK "MENU\n" RESET);
    }
    else
    {
        printf("MENU\n");
    }
}

int firstlevelPassed(int *pusercoin, int *puserscore, int *puserstat1, int *puserstat2)
{
    PlaySoundA(TEXT("won2.wav"), NULL, SND_FILENAME | SND_ASYNC);

    int select = 0;
    char ch;
    while (1)
    {
        drawfirstlevel(select, 1);
        ch = getch();

        switch (ch)
        {
        case 'w':
            if (select > 0)
                select--;
            break;
        case 'W':
            if (select > 0)
                select--;
            break;
        case 's':
            if (select < 2)
                select++;
            break;
        case 'S':
            if (select < 2)
                select++;
            break;
        case 13: // Enter
            system("cls");
            switch (select)
            {
            case 0:
                for (int k = 0; k < 15; ++k)
                {
                    printf("NEXT LEVEL" GRAY "." RESET "."
                           "."
                           "\n");
                    Sleep(100);
                    system("cls");
                    printf("NEXT LEVEL"
                           "." GRAY "." RESET "."
                           "\n");
                    Sleep(100);
                    system("cls");
                    printf("NEXT LEVEL"
                           "."
                           "." GRAY "." RESET "\n");
                    Sleep(100);
                    system("cls");
                }
                // printf("NEXT LEVEL...\n");
                // Sleep(2000);
                // system("cls");
                return map2(pusercoin, puserscore, puserstat1, puserstat2);
            case 1:
                drawfirstlevel(1, 0);
                // printf("RETRY...\n");

                for (int k = 0; k < 15; ++k)
                {
                    printf("TRY AGAIN" GRAY "." RESET "."
                           "."
                           "\n");
                    Sleep(100);
                    system("cls");
                    printf("TRY AGAIN"
                           "." GRAY "." RESET "."
                           "\n");
                    Sleep(100);
                    system("cls");
                    printf("TRY AGAIN"
                           "."
                           "." GRAY "." RESET "\n");
                    Sleep(100);
                    system("cls");
                }
                *pusercoin += coin_count;
                *puserscore += score_count;
                *puserstat1 = 1;
                *puserstat2 = 0;
                retry_count++;
                coin_count = 0;
                score_count = 0;
                shield = 0;
                sizemario = 1;
                mapindex = 1;
                // Sleep(3000);
                // system("cls");
                return 1;
            case 2:
                *pusercoin += coin_count;
                *puserscore += score_count;
                *puserstat1 = 1;
                *puserstat2 = 0;
                // printf("MAIN MENU...\n");
                // Sleep(3000);

                for (int k = 0; k < 15; ++k)
                {
                    printf("MENU" GRAY "." RESET "."
                           "."
                           "\n");
                    Sleep(100);
                    system("cls");
                    printf("MENU"
                           "." GRAY "." RESET "."
                           "\n");
                    Sleep(100);
                    system("cls");
                    printf("MENU"
                           "."
                           "." GRAY "." RESET "\n");
                    Sleep(100);
                    system("cls");
                }

                coin_count = 0;
                score_count = 0;
                shield = 0;
                sizemario = 1;
                mapindex = 1;
                system("cls");
                return 0;
            }
            getch();
            // return;
        }
    }
}

void drawsecondlevel(int select, int retry)
{

    static int reset = 0;
    if (retry == 0)
    {
        reset = 0;
        return;
    }
    system("cls");
    printf(GREEN "YOU WON!\n\n" YELLOW);
    if (reset == 0)
    {
        Sleep(500);
        printf("COINS: ");
        int currentCoinCount = 0;
        while (currentCoinCount <= coin_count)
        {
            moveCursor(8, 3);
            printf("%d", currentCoinCount);
            fflush(stdout);
            currentCoinCount++;
            Sleep(50);
        }
        Sleep(500);
        printf("\n");
        printf("SCORE: ");
        int currentscoreCount = 0;
        while (currentscoreCount <= score_count)
        {
            moveCursor(8, 4);
            printf("%d", currentscoreCount);
            fflush(stdout);
            currentscoreCount = currentscoreCount + 100;
            Sleep(50);
        }
        Sleep(500);
    }
    else if (reset == 1)
    {
        printf("COINS: %d", coin_count);
        printf("\n");
        printf("SCORE: %d", score_count);
    }
    reset = 1;
    printf(RESET "\n\n");
    if (select == 0)
    {
        printf(PINK "TRY AGAIN\n" RESET);
    }
    else
    {
        printf("TRY AGAIN\n");
    }
    if (select == 1)
    {
        printf(PINK "MENU\n" RESET);
    }
    else
    {
        printf("MENU\n");
    }
}

int secondlevelPassed(int *pusercoin, int *puserscore, int *puserstat1, int *puserstat2)
{
    PlaySoundA(TEXT("won2.wav"), NULL, SND_FILENAME | SND_ASYNC);

    int select = 0;
    char ch;
    while (1)
    {
        drawsecondlevel(select, 1);
        ch = getch();

        switch (ch)
        {
        case 'w':
            if (select > 0)
                select--;
            break;
        case 'W':
            if (select > 0)
                select--;
            break;
        case 's':
            if (select < 1)
                select++;
            break;
        case 'S':
            if (select < 1)
                select++;
            break;
        case 13: // Enter
            system("cls");
            switch (select)
            {
            case 0:
                drawfirstlevel(1, 0);
                drawsecondlevel(0, 0);
                // printf("RETRY...\n");
                *pusercoin += coin_count;
                *puserscore += score_count;
                *puserstat1 = 1;
                *puserstat2 = 1;
                retry_count++;
                coin_count = 0;
                score_count = 0;
                shield = 0;
                sizemario = 1;
                mapindex = 1;

                for (int k = 0; k < 15; ++k)
                {
                    printf("TRY AGAIN" GRAY "." RESET "."
                           "."
                           "\n");
                    Sleep(100);
                    system("cls");
                    printf("TRY AGAIN"
                           "." GRAY "." RESET "."
                           "\n");
                    Sleep(100);
                    system("cls");
                    printf("TRY AGAIN"
                           "."
                           "." GRAY "." RESET "\n");
                    Sleep(100);
                    system("cls");
                }

                // Sleep(3000);
                // system("cls");
                return 1;
            case 1:
                *pusercoin += coin_count;
                *puserscore += score_count;
                *puserstat1 = 1;
                *puserstat2 = 1;
                printf("MAIN MENU...\n");
                Sleep(3000);
                system("cls");
                // first page function
                return 0;
            }
            getch();
        }
    }
}

void drawfailedlevel(int select)
{
    system("cls");
    printf(RED "GAME OVER!\n\n" RESET);
    if (select == 0)
    {
        printf(PINK "TRY AGAIN\n" RESET);
    }
    else
    {
        printf("TRY AGAIN\n");
    }
    if (select == 1)
    {
        printf(PINK "MENU\n" RESET);
    }
    else
    {
        printf("MENU\n");
    }
}
int levelfailed()
{
    PlaySoundA(TEXT("smb_mariodie.wav"), NULL, SND_FILENAME | SND_ASYNC);
    coin_count = 0;
    score_count = 0;
    fail_count++;
    int select = 0;
    char ch;
    while (1)
    {
        drawfailedlevel(select);
        ch = getch();

        switch (ch)
        {
        case 'w':
            if (select > 0)
                select--;
            break;
        case 'W':
            if (select > 0)
                select--;
            break;
        case 's':
            if (select < 1)
                select++;
            break;
        case 'S':
            if (select < 1)
                select++;
            break;
        case 13: // Enter
            system("cls");
            switch (select)
            {
            case 0:
                drawfirstlevel(1, 0);
                drawsecondlevel(0, 0);
                // printf("RETRY...\n");
                retry_count++;
                shield = 0;
                sizemario = 1;
                mapindex = 1;
                // Sleep(3000);
                // system("cls");
                for (int k = 0; k < 15; ++k)
                {
                    printf("TRY AGAIN" GRAY "." RESET "."
                           "."
                           "\n");
                    Sleep(100);
                    system("cls");
                    printf("TRY AGAIN"
                           "." GRAY "." RESET "."
                           "\n");
                    Sleep(100);
                    system("cls");
                    printf("TRY AGAIN"
                           "."
                           "." GRAY "." RESET "\n");
                    Sleep(100);
                    system("cls");
                }
                return 1;
            case 1:
                // printf("MAIN MENU...\n");
                // Sleep(3000);
                // system("cls");

                for (int k = 0; k < 15; ++k)
                {
                    printf("MENU" GRAY "." RESET "."
                           "."
                           "\n");
                    Sleep(100);
                    system("cls");
                    printf("MENU"
                           "." GRAY "." RESET "."
                           "\n");
                    Sleep(100);
                    system("cls");
                    printf("MENU"
                           "."
                           "." GRAY "." RESET "\n");
                    Sleep(100);
                    system("cls");
                }

                // first page function
                return 0;
            }
            getch();
        }
    }
}

void checkCheatCode(char ch)
{
    static char cheatCode[] = "mario"; // چیت کد معروف برای مثال
    static int index = 0;

    if (ch == cheatCode[index])
    {
        index++;
        if (index == strlen(cheatCode))
        {
            // چیت کد کامل وارد شده است
            printf("\nCheat Code Activated!😎\n");
            cat_lives = 10;      // مثلاً تعداد جان‌ها را به 999 تغییر می‌دهیم
            score_count += 10000; // امتیاز را افزایش می‌دهیم
            index = 0;            // ایندکس را برای چیت کد بعدی ریست می‌کنیم
        }
    }
    else
    {
        index = 0; // اگر کاراکتر اشتباه وارد شد، ایندکس ریست می‌شود
    }
}