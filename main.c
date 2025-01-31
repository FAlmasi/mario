#include "header.h"


int main()
{
    PlaySoundA(TEXT("MarioMainTheme.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    int selectedOption = 1;
    int totalOptions = 4;
    char ch;
    int pnum = 0;
    int flag = 1;
    user *plist = (user *)malloc(sizeof(user) * MaxUser);
    loadUsers(plist, &pnum);
    SetConsoleOutputCP(CP_UTF8);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
    while (1)
    {
        displayMenu(selectedOption);

        ch = _getch();

        if (ch == 'w' || ch == 'W')
        {
            if (selectedOption > 1)
            {
                selectedOption--;
            }
        }
        else if (ch == 's' || ch == 'S')
        {
            if (selectedOption < totalOptions)
            {
                selectedOption++;
            }
        }
        else if (ch == '\r')
        {
            switch (selectedOption)
            {
            case 1:
                system("cls");
                signup(plist, &pnum);
                break;
            case 2:
            {
                system("cls");
                user *pcurrentuser = singin(plist, &pnum);
                if (pcurrentuser != NULL)
                {
                    userpanel(pcurrentuser, plist, pnum);
                }
                break;
            }
            case 3:
                system("cls");
                Forget_Pass(plist, &pnum);
                break;
            case 4:
                printf(HOT_PINK "\nExiting the game... Goodbye!\n\n" RESET);
                flag = 0;
                break;
            default:
                break;
            }
        }
        if (flag == 0)
        {
            break;
        }
    }
    PlaySoundA(TEXT("lm_inventory-close.wav"), NULL, SND_FILENAME | SND_ASYNC);
    Sleep(1500);
    saveUsers(plist, pnum);
    freeUsers(plist, pnum);
    return 0;
}
