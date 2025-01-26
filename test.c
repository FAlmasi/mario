#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
int coin = 0;
void moveCharacter(int *i, int *j, char board[][64], int newI, int newJ)
{
    if (board[newI][newJ] == ' ' || board[newI][newJ] == '3')
    {
        if (board[newI][newJ] == '3')
            coin++;
        board[*i][*j] = ' ';
        *i = newI;
        *j = newJ;
        board[*i][*j] = '$';
    }
}
void printBoard(char board[][64])
{
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 64; j++)
        {
            switch (board[i][j])
            {
            case '1':
                printf("🟫");
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
                printf("🟪");
                break;
            default:
                break;
            }
        }
        printf("\n");
    }
}
void fall(int *i, int *j, char board[][64], HANDLE *hStdout)
{
    hStdout = *hStdout;
    while (1)
    {
        if (board[*i + 1][*j] == ' ' || board[*i + 1][*j] == '3')
        {
            COORD origin = {0, 1};
            SetConsoleCursorPosition(hStdout, origin);
            printBoard(board);
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
            return;
        }
    }
}
void jump(int *i, int *j, char board[][64], HANDLE *hStdout)
{
    hStdout = *hStdout;
    int jumpHeight = 4;
    int originalI = *i;
    for (int f = 1; f <= jumpHeight; f++)
    {
        COORD origin = {0, 1};
        SetConsoleCursorPosition(hStdout, origin);
        printBoard(board);
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
    COORD origin = {0, 1};
    SetConsoleCursorPosition(hStdout, origin);
    board[catY][catX] = '$';
    printBoard(board);
    while (1)
    {
        COORD origin = {0, 1};
        SetConsoleCursorPosition(hStdout, origin);
        printBoard(board);
        if (_kbhit())
        {
            char ch = _getch();
            if (ch == 'w' && catY > 0)
                jump(&catY, &catX, board, &hStdout);
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
            fall(&catY, &catX, board, &hStdout);
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