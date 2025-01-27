#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

int coin_count = 0;
int cat_lives = 3;
int offsetX = 0;
int mapindex = 1;
int score_count = 0;
int shield = 0;
int retry_count = 0;
int fail_count = 0;
int coin_reset = 0;

void moveCharacter(int *i, int *j, char board[][64], int newI, int newJ);

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
            default:
                break;
            }
        }
        printf("\n");
    }
    printf("coin: %d        lives:%d", coin_count, cat_lives);
}
void fall(int *i, int *j, char board[][64], HANDLE *hStdout, int cory)
{
    hStdout = *hStdout;
    while (1)
    {
        if (board[*i + 1][*j] == ' ' || board[*i + 1][*j] == '3')
        {
            COORD origin = {0, 1};
            SetConsoleCursorPosition(hStdout, origin);
            printBoard(board, cory);
            moveCharacter(i, j, board, *i + 1, *j);
            Sleep(30);
            if (_kbhit())
            {
                char ch = _getch();
                if (ch == 'a' && *j > 0 && (board[*i][*j - 1] == ' ' || board[*i][*j - 1] == '3'))
                {
                    moveCharacter(i, j, board, *i, *j - 1);
                }
                else if (ch == 'd' && *j < 63 && (board[*i][*j + 1] == ' ' || board[*i][*j + 1] == '3'))
                {
                    moveCharacter(i, j, board, *i, *j + 1);
                }
                Sleep(10);
            }
        }
        else
        {
            break;
        }
    }
    if (board[*i + 1][*j] == '7' || board[*i + 1][*j] == '6' || board[*i + 1][*j] == '9')
    {
        moveCharacter(i, j, board, *i + 1, *j);
    }
    return;
}

void jump(int *i, int *j, char board[][64], HANDLE *hStdout, int cory)
{
    hStdout = *hStdout;
    int jumpHeight = 4;
    int originalI = *i;
    for (int f = 1; f <= jumpHeight; f++)
    {
        COORD origin = {0, 1};
        SetConsoleCursorPosition(hStdout, origin);
        printBoard(board, cory);

        if (board[*i - 1][*j] == '!')
        {
            coin_block1(board, *i, *j);
            break;
        }
        if (board[*i - 1][*j] != ' ' && board[*i - 1][*j] != '3')
        {
            break;
        }
        moveCharacter(i, j, board, *i - 1, *j);
        Sleep(30);
        if (_kbhit())
        {
            char ch = _getch();
            if (ch == 'a' && *j > 0 && (board[*i][*j - 1] == ' ' || board[*i][*j - 1] == '3'))
            {
                moveCharacter(i, j, board, *i, *j - 1);
            }
            else if (ch == 'd' && *j < 63 && (board[*i][*j + 1] == ' ' || board[*i][*j + 1] == '3'))
            {
                moveCharacter(i, j, board, *i, *j + 1);
            }
            Sleep(10);
        }
    }
}

void moveBlock5(char board[][64], int *block5_i, int *block5_j, DWORD *lastUpdate, int delay, int catY, int catX)
{

    if (GetTickCount() - *lastUpdate >= delay)
    {
        static int direction = 1;

        int new_j = *block5_j;
        if (direction == 1 && new_j > 0 && board[*block5_i][new_j - 1] == ' ')
        { // حرکت به چپ
            new_j--;
        }
        else if (direction == 1 && new_j > 0 && board[*block5_i][new_j - 1] == '$')
        {
            cat_lives--;
        }
        else if (direction == -1 && new_j < 63 && board[*block5_i][new_j + 1] == ' ')
        { // حرکت به راست
            new_j++;
        }
        else if (direction == -1 && new_j < 63 && board[*block5_i][new_j + 1] == '$')
        {
            cat_lives--;
        }
        else
        {
            direction *= -1;
        }

        // به‌روزرسانی موقعیت بلوک ۵
        if (new_j != *block5_j)
        {
            board[*block5_i][*block5_j] = ' ';
            *block5_j = new_j;
            board[*block5_i][*block5_j] = '5';
        }

        *lastUpdate = GetTickCount();
    }
    if (cat_lives <= 0)
    {
        return; // پایان بازی اگر جان‌ها تمام شد
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

void White()
{
    printf("\033[0m");
}

void Green()
{
    printf("\033[1;32m");
}

void Cyan()
{
    printf("\033[1;36m");
}

void Yellow()
{
    printf("\033[1;33m");
}

void Red()
{
    printf("\033[1;31m");
}

void moveCursor(int x, int y)
{
    printf("\033[%d;%dH", y, x); // ANSI escape code to move cursor
}

void drawfirstlevel(int select)
{
    static int reset = 0;
    system("cls");
    Green();
    printf("LEVEL COMPLETED SUCCESSFULLY!\n\n");
    Yellow();
    if (reset == 0)
    {
        Sleep(500);
        printf("COINS: ");
        int currentCoinCount = 0;
        while (currentCoinCount <= coin_count)
        {
            moveCursor(8, 3);               // Move cursor to the position of the coin count
            printf("%d", currentCoinCount); // Update the coin count
            fflush(stdout);                 // Flush the output to ensure it's displayed immediately
            currentCoinCount++;
            Sleep(50);
        }
        Sleep(500);
        printf("\n");
        printf("SCORE: ");
        int currentscoreCount = 0;
        while (currentscoreCount <= score_count)
        {
            moveCursor(8, 4);                // Move cursor to the position of the coin count
            printf("%d", currentscoreCount); // Update the coin count
            fflush(stdout);                  // Flush the output to ensure it's displayed immediately
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
    White();
    printf("\n\n");
    if (select == 0)
    {
        Cyan();
        printf("NEXT LEVEL\n");
        White();
    }
    else
    {
        printf("NEXT LEVEL\n");
    }

    if (select == 1)
    {
        Cyan();
        printf("RETRY\n");
        White();
    }
    else
    {
        printf("RETRY\n");
    }
    if (select == 2)
    {
        Cyan();
        printf("MAIN MENU\n");
        White();
    }
    else
    {
        printf("MAIN MENU\n");
    }
}
void firstlevelPassed()
{
    int select = 0;
    char ch;
    while (1)
    {
        drawfirstlevel(select);
        ch = getch();

        switch (ch)
        {
        case 'w':
            if (select > 0)
                select--;
            break;
        case 's':
            if (select < 2)
                select++;
            break;
        case 13: // Enter
            system("cls");
            switch (select)
            {
            case 0:
                printf("NEXT LEVEL...\n");
                Sleep(3000);
                map2();
                return;
            case 1:
                printf("RETRY...\n");
                coin_count = 0;
                coin_reset = 0;
                retry_count++;
                Sleep(3000);
                map1();
                return;
            case 2:
                printf("MAIN MENU...\n");
                Sleep(3000);
                // first page function
                return;
            }
            getch();
            return;
        }
    }
}

void drawsecondlevel(int select)
{
    static int reset = 0;
    system("cls");
    Green();
    printf("YOU WON!\n\n");
    Yellow();
    if (reset == 0)
    {
        Sleep(500);
        printf("COINS: ");
        int currentCoinCount = 0;
        while (currentCoinCount <= coin_count)
        {
            moveCursor(8, 3);               // Move cursor to the position of the coin count
            printf("%d", currentCoinCount); // Update the coin count
            fflush(stdout);                 // Flush the output to ensure it's displayed immediately
            currentCoinCount++;
            Sleep(50);
        }
        Sleep(500);
        printf("\n");
        printf("SCORE: ");
        int currentscoreCount = 0;
        while (currentscoreCount <= score_count)
        {
            moveCursor(8, 4);                // Move cursor to the position of the coin count
            printf("%d", currentscoreCount); // Update the coin count
            fflush(stdout);                  // Flush the output to ensure it's displayed immediately
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
    White();
    printf("\n\n");
    if (select == 0)
    {
        Cyan();
        printf("RETRY\n");
        White();
    }
    else
    {
        printf("RETRY\n");
    }
    if (select == 1)
    {
        Cyan();
        printf("MAIN MENU\n");
        White();
    }
    else
    {
        printf("MAIN MENU\n");
    }
}
void secondlevelPassed()
{
    int select = 0;
    char ch;
    while (1)
    {
        drawsecondlevel(select);
        ch = getch();

        switch (ch)
        {
        case 'w':
            if (select > 0)
                select--;
            break;
        case 's':
            if (select < 2)
                select++;
            break;
        case 13: // Enter
            system("cls");
            switch (select)
            {
            case 0:
                printf("RETRY...\n");
                coin_count = coin_reset;
                retry_count++;
                Sleep(3000);
                map2();
                return;
            case 1:
                printf("MAIN MENU...\n");
                Sleep(3000);
                // first page function
                return;
            }
            getch();
            return;
        }
    }
}

void drawfailedlevel(int select)
{
    system("cls");
    Red();
    printf("YOU FAILED!\n\n");
    White();
    if (select == 0)
    {
        Cyan();
        printf("RETRY\n");
        White();
    }
    else
    {
        printf("RETRY\n");
    }
    if (select == 1)
    {
        Cyan();
        printf("MAIN MENU\n");
        White();
    }
    else
    {
        printf("MAIN MENU\n");
    }
}
void levelfailed(int map, int coin_reset)
{ // enterance would be 1 or 2 for map function call
    // reset coins
    coin_count = coin_reset;
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
        case 's':
            if (select < 2)
                select++;
            break;
        case 13: // Enter
            system("cls");
            switch (select)
            {
            case 0:
                printf("RETRY...\n");
                retry_count++;
                Sleep(3000);
                if (map == 1)
                {
                    map1();
                }
                else if (map == 2)
                {
                    map2();
                }
                return;
            case 1:
                printf("MAIN MENU...\n");
                Sleep(3000);
                // first page function
                return;
            }
            getch();
            return;
        }
    }
}

void map2()
{
    system("cls");
    SetConsoleOutputCP(CP_UTF8);
    DWORD bytes_written;
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
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
        "1  1    &&                2222  11                 11 1 11  *111",
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
    mapindex = 2;
    SetConsoleCursorPosition(hStdout, origin);
    board[catY][catX] = '$';
    // متغیرهای حرکت رندوم بلوک ۵ اول
    int block5_1_i = 12;                       // موقعیت اولیه بلوک ۵ اول (ردیف)
    int block5_1_j = 30;                       // موقعیت اولیه بلوک ۵ اول (ستون)
    DWORD lastBlock5_1Update = GetTickCount(); // زمان آخرین به‌روزرسانی حرکت بلوک ۵ اول
    int block5_1Delay = 300;                   // تأخیر بین حرکات بلوک ۵ اول (میلی‌ثانیه)
    int block5_1Removed = 0;                   // فلگ برای نشان دادن حذف بلوک ۵ اول

    // متغیرهای حرکت رندوم بلوک ۵ دوم
    int block5_2_i = 12;                       // موقعیت اولیه بلوک ۵ دوم (ردیف)
    int block5_2_j = 15;                       // موقعیت اولیه بلوک ۵ دوم (ستون)
    DWORD lastBlock5_2Update = GetTickCount(); // زمان آخرین به‌روزرسانی حرکت بلوک ۵ دوم
    int block5_2Delay = 300;                   // تأخیر بین حرکات بلوک ۵ دوم (میلی‌ثانیه)
    int block5_2Removed = 0;                   // فلگ برای نشان دادن حذف بلوک ۵ دوم

    // متغیرهای حرکت رندوم بلوک ۵ سوم
    int block5_3_i = 25;                       // موقعیت اولیه بلوک ۵ سوک (ردیف)
    int block5_3_j = 30;                       // موقعیت اولیه بلوک ۵ سوم (ستون)
    DWORD lastBlock5_3Update = GetTickCount(); // زمان آخرین به‌روزرسانی حرکت بلوک ۵ سوم
    int block5_3Delay = 300;                   // تأخیر بین حرکات بلوک ۵ سوم (میلی‌ثانیه)
    int block5_3Removed = 0;                   // فلگ برای نشان دادن حذف بلوک ۵ سوم

    printBoard(board, 27);

    int random = rand() % 2;
    int mushroomX = 8;
    int mushroomY = 10;
    int flag = 0;

    while (1)
    {
        char ch;
        if (cat_lives <= 0)
        {
            system("cls");
            levelfailed(2, coin_reset);
        }
        COORD origin = {0, 1};
        SetConsoleCursorPosition(hStdout, origin);
        printBoard(board, 27);
        if (!block5_1Removed)
        {
            moveBlock5(board, &block5_1_i, &block5_1_j, &lastBlock5_1Update, block5_1Delay, catY, catX); // حرکت رندوم بلوک ۵ اول
        }
        if (!block5_2Removed)
        {
            moveBlock5(board, &block5_2_i, &block5_2_j, &lastBlock5_2Update, block5_2Delay, catY, catX); // حرکت رندوم بلوک ۵ دوم
        }
        if (!block5_3Removed)
        {
            moveBlock5(board, &block5_3_i, &block5_3_j, &lastBlock5_3Update, block5_3Delay, catY, catX); // حرکت رندوم بلوک ۵ سوم
        }
        if (_kbhit())
        {
            ch = _getch();
            if (ch == 'w' && catY > 0)
                jump(&catY, &catX, board, &hStdout, 27);
            else if (ch == 's' && catY < 26)
                moveCharacter(&catY, &catX, board, catY + 1, catX);
            else if (ch == 'a' && catX > 0)
                moveCharacter(&catY, &catX, board, catY, catX - 1);
            else if (ch == 'd' && catX < 63)
                moveCharacter(&catY, &catX, board, catY, catX + 1);
            if (catY == 9 && 26 < catX && catX < 30)
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
                moveCharacter(&catY, &catX, board, 25, 47);
            }
            else if (catY == 3 && 23 < catX && catX < 27)
            {
                moveCharacter(&catY, &catX, board, 3, 60);
            }
            fall(&catY, &catX, board, &hStdout, 27);
        }
        // بررسی برخورد با بلوک‌های ۵
        if (catX == block5_1_j && catY == block5_1_i)
        {
            block5_1Removed = 1; // بلوک ۵ اول حذف شده است
        }
        if (catX == block5_2_j && catY == block5_2_i)
        {
            block5_2Removed = 1; // بلوک ۵ دوم حذف شده است
        }
        if (catX == block5_3_j && catY == block5_3_i)
        {
            block5_3Removed = 1; // بلوک ۵ سوم حذف شده است
        }

        if ((catX == 8 && catY == 10) && ch == 'w')
        {
            ++flag;
        }
        if (1 <= flag && flag <= 4)
        {
            if (random == 0)
            {
                switch (flag)
                {
                case 1:
                    board[mushroomX - 2 ][mushroomY] = ' ';
                    board[mushroomX - 2][mushroomY + 1] = '^';
                    Sleep(10);
                    break;
                case 2:
                    board[mushroomX - 2][mushroomY + 1] = ' ';
                    board[mushroomX - 2][mushroomY + 2] = '^';
                    Sleep(10);
                    break;
                case 3:
                    board[mushroomX - 2][mushroomY + 2] = ' ';
                    board[mushroomX - 1][mushroomY + 2] = '^';
                    Sleep(10);
                    break;
                case 4:
                    board[mushroomX - 1][mushroomY + 2] = ' ';
                    board[mushroomX][mushroomY + 2] = '^';
                    Sleep(10);
                    break;
                }
            }
            else if (random == 1)
            {
                switch (flag)
                {
                case 1:
                    board[mushroomX - 2][mushroomY] = ' ';
                    board[mushroomX - 2][mushroomY - 1] = '^';
                    Sleep(10);
                    break;
                case 2:
                    board[mushroomX - 2][mushroomY - 1] = ' ';
                    board[mushroomX - 2][mushroomY - 2] = '^';
                    Sleep(10);
                    break;
                case 3:
                    board[mushroomX - 2][mushroomY - 2] = ' ';
                    board[mushroomX - 1][mushroomY - 2] = '^';
                    Sleep(10);
                    break;
                case 4:
                    board[mushroomX - 1][mushroomY - 2] = ' ';
                    board[mushroomX][mushroomY - 2] = '^';
                    Sleep(10);
                    break;
                }
            }
            ++flag;
        }
    }
}
void map1()
{
    system("cls");
    int coin_reset = 0;
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
        "1      11!1                       4444 44  44    1881          1",
        "1          111                     44  44  44    1  1     2222 1",
        "1                            4444  44  44  44    1  1      22  1",
        "1               33            44 6 446 446 446   1         22  1",
        "1111111111111111111111111111111111111111111111111111111111111111"};

    int catX = 1;
    int catY = 13;
    int emoji1_i = 4;
    int emoji1_j = 44;
    int emoji2_i = 9;
    int emoji2_j = 35;
    mapindex = 1;

    // متغیرهای حرکت رندوم بلوک ۵
    int block5_i = 13;                       // موقعیت اولیه بلوک ۵ (ردیف)
    int block5_j = 20;                       // موقعیت اولیه بلوک ۵ (ستون)
    DWORD lastBlock5Update = GetTickCount(); // زمان آخرین به‌روزرسانی حرکت بلوک ۵
    int block5Delay = 300;                   // تأخیر بین حرکات بلوک ۵ (میلی‌ثانیه)
    int block5Removed = 0;                   // فلگ برای نشان دادن حذف بلوک ۵

    int harmTriggered = 0; // Flag to track if harm has been triggered
    COORD origin = {0, 1};
    SetConsoleCursorPosition(hStdout, origin);
    board[catY][catX] = '$';
    printBoard(board, 15);
    DWORD lastUpdate = GetTickCount();
    DWORD delay = 2000;
    int toggle = 0;
    while (1)
    {
        if (cat_lives <= 0)
        {
            system("cls");
            levelfailed(1, 0);
        }
        COORD origin = {0, 1};
        updateBlockStatus(board, &lastUpdate, delay, &toggle, emoji1_i, emoji1_j, emoji2_i, emoji2_j, &catY, &catX);
        if (!block5Removed)
        {
            moveBlock5(board, &block5_i, &block5_j, &lastBlock5Update, block5Delay, catY, catX); // حرکت رندوم بلوک ۵
        }
        SetConsoleCursorPosition(hStdout, origin);
        printBoard(board, 15);
        if (_kbhit())
        {
            char ch = _getch();
            if (ch == 'w' && catY > 0)
                jump(&catY, &catX, board, &hStdout, 15);
            else if (ch == 's' && catY < 14)
                moveCharacter(&catY, &catX, board, catY + 1, catX);
            else if (ch == 'a' && catX > 0)
                moveCharacter(&catY, &catX, board, catY, catX - 1);
            else if (ch == 'd' && catX < 63)
                moveCharacter(&catY, &catX, board, catY, catX + 1);
            if (catY == 10 && 58 < catX && catX < 61)
            {
                moveCharacter(&catY, &catX, board, 4, 22);
            }
            fall(&catY, &catX, board, &hStdout, 15);
        }
        if (catX == block5_j && catY == block5_i)
        {
            block5Removed = 1; // بلوک ۵ حذف شده است
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
    if (board[newI][newJ] == ' ' || board[newI][newJ] == '3')
    {
        if (board[newI][newJ] == '3')
            coin_count++;
        board[*i][*j] = ' ';
        *i = newI;
        *j = newJ;
        board[*i][*j] = '$';
    }
    else if (board[newI][newJ] == '6' || board[newI][newJ] == '7' || board[newI][newJ] == '5')
    {
        if (board[newI - 1][newJ] == '$')
        {
            board[*i][*j] = ' ';
            *i = newI;
            *j = newJ;
            board[newI][newJ] = ' '; // حذف بلوک ۵ پس از برخورد
            board[*i][*j] = '$';
            score_count += 100;
        }
        else
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
    }

    else if (board[newI][newJ] == '*')
    {
        if (check)
        {
            --check;
            shield = 1;
        }
    }
    else if (board[newI][newJ] == '9')
    {
        board[newI][newJ] = ' ';
        board[*i][*j] = '$';
        score_count = score_count + (cat_lives * 1000);
        system("cls");
        coin_reset = coin_count;
        firstlevelPassed();
    }
}