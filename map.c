#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
void map1()
{
    SetConsoleOutputCP(CP_UTF8);
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
        "1111111111111111111111111111111111111111111111111111111111111111"};

    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 64; j++)
        {
            if (board[i][j] == '1')
                printf("🧱");
            else if (board[i][j] == '2')
                printf("🟩");
            else if (board[i][j] == '3')
                printf("🪙 ");
            else if (board[i][j] == '4')
                printf("⬜");
            else if (board[i][j] == '5')
                printf("🐙");
            else if (board[i][j] == '6')
                printf("🐲");
            else if (board[i][j] == '7')
                printf("🌱");
            else if (board[i][j] == '8')
                printf("🟧");
            else if (board[i][j] == '9')
                printf("🚩");
            else if (board[i][j] == '!')
                printf("🟨");
            else if (board[i][j] == ' ')
                printf("  ");
            else if (board[i][j] == '$')
                printf("😃");
        }
        printf("\n"); // به خط بعدی بروید
    }
}

void map2()
{
    SetConsoleOutputCP(CP_UTF8);
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
        "1 $          5  3           22              5     1   3        1",
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

    for (int i = 0; i < 27; i++)
    {
        for (int j = 0; j < 64; j++)
        {
            if (board[i][j] == '1')
                printf("🧱");
            else if (board[i][j] == '2')
                printf("🟩");
            else if (board[i][j] == '3')
                printf("🪙 ");
            else if (board[i][j] == '4')
                printf("⬜️");
            else if (board[i][j] == '5')
                printf("🐙");
            else if (board[i][j] == '6')
                printf("🐲");
            else if (board[i][j] == '7')
                printf("🎑");
            else if (board[i][j] == '8')
                printf("🟧");
            else if (board[i][j] == '9')
                printf("🚩");
            else if (board[i][j] == '!' || board[i][j] == '&')
                printf("🟨");
            else if (board[i][j] == '*')
                printf("🛡️");
            else if (board[i][j] == '@')
                printf("🟦");
            else if (board[i][j] == '$')
                printf("🐱");
            else if (board[i][j] == ' ')
                printf("  ");
        }
        printf("\n"); // به خط بعدی بروید
    }
}

int main()
{
    map2();
    return 0;
}