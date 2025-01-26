#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
int coin_count = 0;
int cat_lives = 3;
int offsetX = 0;
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
void printBoard(char board[][64], int corY)
{
    for (int i = 0; i < corY; i++)
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
            default:
                break;
            }
        }
        printf("\n");
    }
    printf("coin: %d", coin_count);
}
void fall(int *i, int *j, char board[][64], HANDLE *hStdout, int corY)
{
    hStdout = *hStdout;
    while (1)
    {
        if (board[*i + 1][*j] == ' ' || board[*i + 1][*j] == '3')
        {
            COORD origin = {0, 1};
            SetConsoleCursorPosition(hStdout, origin);
            printBoard(board, corY);
            moveCharacter(i, j, board, *i + 1, *j);
            Sleep(50);
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
                Sleep(25);
            }
        }
        else
        {
            return;
        }
    }
}
void jump(int *i, int *j, char board[][64], HANDLE *hStdout, int corY)
{
    hStdout = *hStdout;
    int jumpHeight = 4;
    int originalI = *i;
    for (int f = 1; f <= jumpHeight; f++)
    {
        COORD origin = {0, 1};
        SetConsoleCursorPosition(hStdout, origin);
        printBoard(board, corY);
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
        Sleep(50);
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
            Sleep(25);
        }
    }
}
void updateBlockStatus(char board[][64], DWORD *lastUpdate, int delay, int *toggle, int emoji1_i, int emoji1_j, int emoji2_i, int emoji2_j)
{
    if (GetTickCount() - *lastUpdate >= delay)
    {
        *toggle = !*toggle;
        if (*toggle)
        {
            board[emoji1_i][emoji1_j] = '7';
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
    char board[27][64] = {
        "1111111111111111111111111111111111111111111111111111111111111111",
        "1                                                       1    @ 1",
        "1                                                       1    @@1",
        "1                                                       1    @@1",
        "1                      @@@@                             1    @ 1",
        "1                       @@  111      118                1 9    1",
        "1       11811           @@ 1   111     1!1              11111111",
        "1                      11111     11        6                   1",
        "1   111   1                     3 111111111111111&11111        1",
        "1  3                             1                    11       1",
        "1  1                       2222 11                11  1 11  *111",
        "1                           2211     111111111111111  1  111   1",
        "1           5  3            22              5     1   3        1",
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
        "                           1        51         3221",
        "                           111111111111111111111111",

    };
    int catX = 1;
    int catY = 12;
    COORD origin = {0, 1};
    SetConsoleCursorPosition(hStdout, origin);
    board[catY][catX] = '$';
    printBoard(board, 27);
    while (1)
    {
        COORD origin = {0, 1};
        SetConsoleCursorPosition(hStdout, origin);
        printBoard(board, 27);
        if (_kbhit())
        {
            char ch = _getch();
            if (ch == 'w' && catY > 0)
                jump(&catY, &catX, board, &hStdout, 27);
            else if (ch == 's' && catY < 26)
                moveCharacter(&catY, &catX, board, catY + 1, catX);
            else if (ch == 'a' && catX > 0)
                moveCharacter(&catY, &catX, board, catY, catX - 1);
            else if (ch == 'd' && catX < 63)
                moveCharacter(&catY, &catX, board, catY, catX + 1);
            if (catY == 10 && 58 < catX && catX < 61)
            {
                moveCharacter(&catY, &catX, board, 4, 22);
            }
            fall(&catY, &catX, board, &hStdout, 27);
        }
    }
}
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
        "1      11!1                       4444 44  44    1881          1",
        "1          111                     44  44  44    1  1     2222 1",
        "1                            4444  44  44  44    1  1      22  1",
        "1               33       5    44 6 446 446 446   1         22  1",
        "1111111111111111111111111111111111111111111111111111111111111111"};

    int catX = 1;
    int catY = 13;
    int emoji1_i = 4;
    int emoji1_j = 44;
    int emoji2_i = 9;
    int emoji2_j = 35;
    COORD origin = {0, 1};
    SetConsoleCursorPosition(hStdout, origin);
    board[catY][catX] = '$';
    printBoard(board, 15);
    DWORD lastUpdate = GetTickCount();
    DWORD delay = 2000;
    int toggle = 0;
    while (1)
    {
        updateBlockStatus(board, &lastUpdate, delay, &toggle, emoji1_i, emoji1_j, emoji2_i, emoji2_j);
        COORD origin = {0, 1};
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
    map1();
    return 0;
}
void moveCharacter(int *i, int *j, char board[][64], int newI, int newJ)
{
    if (board[newI][newJ] == ' ' || board[newI][newJ] == '3')
    {
        if (board[newI][newJ] == '3')
            coin_count++;
        board[*i][*j] = ' ';
        *i = newI;
        *j = newJ;
        board[*i][*j] = '$';
    }
    if (board[newI][newJ] == '9')
    {
        system("cls");
        map2();
    }
}