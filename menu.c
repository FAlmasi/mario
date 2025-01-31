#include "header.h"

void signup(user *plist, int *pnum)
{
    char buf[100];
    int flag;
    while (1)
    {
        printf("🔸Enter Username: ");
        fgets(buf, sizeof(buf), stdin);
        buf[strcspn(buf, "\n")] = '\0';
        if (isUsernameTaken(plist, *pnum, buf))
        {
            printf(HOT_PINK "Username has already been taken!\n" RESET);
        }
        else
        {
            strcpy(plist[*pnum].username, buf);
            break;
        }
    }

    // Email
    const char gmail[] = "@gmail.com";
    while (1)
    {
        printf("🔸Enter your Email: ");
        fgets(buf, sizeof(buf), stdin);
        buf[strcspn(buf, "\n")] = '\0';

        if (strstr(buf, gmail) != NULL)
        {
            if (isEmailTaken(plist, *pnum, buf))
            {
                printf(HOT_PINK "Email has already been taken!\n" RESET);
            }
            else
            {
                strcpy(plist[*pnum].email, buf);
                break;
            }
        }
        else
        {
            printf(HOT_PINK "Email format is not supported\n" RESET);
        }
    }
    while (1)
    {
        if (getPassword(buf, sizeof(buf)))
        {
            plist[*pnum].pass = hash(buf);
            break;
        }
        printf(HOT_PINK "Please try again!\n" RESET);
    }
    plist[*pnum].gplayed = 0;
    plist[*pnum].lost = 0;
    plist[*pnum].won = 0;
    plist[*pnum].coins = 0;
    plist[*pnum].highestscore = 0;
    plist[*pnum].pglist = (game *)malloc(sizeof(game) * MaxGames);
    (*pnum)++;
    printf(MINT "Signedup successfully!\n" RESET);
    Sleep(1000);
    system("cls");
}

user *singin(user *plist, int *pnum)
{
    char buf[100];
    char password[100];
    int i = 0, temp;
    char ch;
    printf("🔸Enter Username: ");
    fgets(buf, sizeof(buf), stdin);
    buf[strcspn(buf, "\n")] = '\0'; // Remove newline

    i = 0; // Reset counter
    printf("🔸Enter password: ");
    while (i < 99)
    {
        ch = _getch();

        if (ch == '\r') // Enter key
            break;
        else if (ch == '\b' && i > 0) // Backspace handling
        {
            printf("\b \b"); // Move cursor back, clear *, move back again
            i--;
        }
        else if (ch >= 32 && ch <= 126) // Printable characters
        {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0'; // Null-terminate
    printf("\n");

    for (i = 0; i < *pnum; ++i)
    {
        if (strcmp(buf, (plist + i)->username) == 0)
        {
            temp = hash(password);
            if (temp == (plist + i)->pass)
            {
                printf(MINT "LOGGED IN sucessfully\n" RESET);
                Sleep(1000);
                system("cls");
                return plist + i;
            }
        }
    }
    printf(HOT_PINK "Your username and password do not match. Please try again.\n" RESET);
    Sleep(1000);
    system("cls");
    return NULL;
}

unsigned long hash(const char *str)
{
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

int getPassword(char *password, size_t max_len)
{
    int i = 0, flag;
    char ch;
    char password2[60];

    while (1)
    {
        i = 0; // Reset counter
        flag = 1;
        printf("🔸Enter password: ");

        while (i < max_len - 1)
        {
            ch = _getch();

            if (ch == '\r') // Enter key
                break;
            else if (ch == '\b' && i > 0) // Backspace handling
            {
                printf("\b \b");
                i--;
            }
            else if (ch >= 32 && ch <= 126)
            {
                password[i++] = ch;
                printf("*");
            }
        }
        password[i] = '\0';
        printf("\n");

        if (i < MIN_PASSWORD_LENGTH)
        {
            printf(HOT_PINK "Password must contain at least %d characters\n" RESET, MIN_PASSWORD_LENGTH);
            flag = 0;
            continue;
        }

        i = 0; // Reset counter
        printf("🔸Repeat password: ");
        while (i < max_len - 1)
        {
            ch = _getch();

            if (ch == '\r')
                break;
            else if (ch == '\b' && i > 0)
            {
                printf("\b \b");
                i--;
            }
            else if (ch >= 32 && ch <= 126)
            {
                password2[i++] = ch;
                printf("*");
            }
        }
        password2[i] = '\0'; // Null-terminate
        printf("\n");

        if (strcmp(password, password2) != 0)
        {
            printf(HOT_PINK "Passwords do not match!\n" RESET);
            flag = 0;
        }

        if (flag)
            break;
    }
    system("cls");
    return 1;
}

void playgame(user *puser)
{
    PlaySoundA(TEXT("khali.wav"), NULL, SND_FILENAME | SND_ASYNC);

    SetConsoleOutputCP(CP_UTF8);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = FALSE;
    game *pgame;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
    int Max_Score = 0;
    while (1)
    {
        int gamesplayed = puser->gplayed;
        pgame = &(puser->pglist[gamesplayed]);
        ++(puser->gplayed);
        pgame->coin = 0;
        pgame->point = 0;
        if (map1(&(pgame->coin), &(pgame->point), &(pgame->stat1), &(pgame->stat2)) == 0)
        {
            break;
        }
    }
    puser->coins = 0;
    for (int i = 0; i < puser->gplayed; ++i)
    {
        if (puser->pglist[i].stat1 == 1 && puser->pglist[i].stat2 == 1)
        {
            ++(puser->won);
        }
        else
        {
            ++(puser->lost);
        }
        if (puser->pglist[i].point > Max_Score)
        {
            Max_Score = puser->pglist[i].point;
        }
        puser->coins += puser->pglist[i].coin;
    }
    puser->highestscore = Max_Score;
    return;
}

int isUsernameTaken(user *plist, int num, const char *username)
{
    for (int i = 0; i < num; ++i)
    {
        if (strcmp(username, plist[i].username) == 0)
        {
            return 1;
        }
    }
    return 0;
}

void Change_Username(user *plist, int num, user *puser)
{
    char buf[100];
    int j, flag;
    while (1)
    {
        printf("🔸Enter New Username: ");
        fgets(buf, sizeof(buf), stdin);
        buf[strcspn(buf, "\n")] = '\0';
        flag = 0;
        for (int j = 0; j < num; ++j)
        {
            if (strcmp((plist + j)->username, buf) == 0)
            {
                ++flag;
                break;
            }
        }
        if (flag)
            printf(RED"Please enter uniqe usename\n"RESET);
        else
        {
            strcpy(puser->username, buf);
            system("cls");
            return;
        }
    }
}

void history(user *puser)
{
    printf("Games Played: %d (Enter 0 to exit)\n", puser->gplayed);
    for (int i = 0; i < puser->gplayed; ++i)
    {
        printf(YELLOW "%d. " RESET, i + 1);

        if (puser->pglist[i].stat1 && puser->pglist[i].stat2)
        {
            printf(MINT "😃 You Won       " RESET);
        }
        else
        {
            if (puser->pglist[i].stat1)
            {
                printf(HOT_PINK "😞 Lost (Map2)" RESET);
            }
            else
            {
                printf(HOT_PINK "😞 Lost (Map1)" RESET);
            }
        }
        printf("\t💯 Score: %d\t🟡 Coin: %d\n", puser->pglist[i].point, puser->pglist[i].coin);
    }
    while (1)
    {
        char ch;
        ch = getch();
        if (ch == '0')
        {
            system("cls");
            return;
        }
    }
}
void displaypanel(int selectedOption, user *puser)
{
    int totalOptions = 5;
    clearScreen();
    displayLogo();
    printf("\n");
    printf(TURQUOISE "                    💯 Highest Score: " RESET "%d" TURQUOISE "            🟡 Coin: " RESET "%d\n\n", puser->highestscore, puser->coins);
    for (int i = 1; i <= totalOptions; i++)
    {
        if (i == selectedOption)
        {
            printf(ORANGE "                                       ");
        }
        else
        {
            printf("                                       ");
        }
        switch (i)
        {
        case 1:
            printf("  Play Game\n" RESET);
            break;
        case 2:
            printf(" Game History\n" RESET);
            break;
        case 3:
            printf("Change Password\n" RESET);
            break;
        case 4:
            printf("Change Username\n" RESET);
            break;
        case 5:
            printf("     Exit\n" RESET);
            break;
        }
    }
}

void userpanel(user *currentUser, user *plist, int num)
{
    int selectedOption = 1;
    int totalOptions = 5;
    char ch;
    SetConsoleOutputCP(CP_UTF8);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
    while (1)
    {
        displaypanel(selectedOption, currentUser);

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
                playgame(currentUser);
                break;
            case 2:
                system("cls");
                history(currentUser);
                break;
            case 3:
                system("cls");
                char buf[100];
                getPassword(buf, sizeof(buf));
                currentUser->pass = hash(buf);
                printf(MINT "Password Changed Successfully\n" RESET);
                break;
            case 4:
                system("cls");
                Change_Username(plist, num, currentUser);
                printf(MINT "Username Changed Successfully\n" RESET);
                break;
            case 5:
                system("cls");
                return;
                break;
            default:
                break;
            }
        }
    }
}

int isEmailTaken(user *plist, int num, const char *email)
{
    for (int i = 0; i < num; ++i)
    {
        if (strcmp(email, plist[i].email) == 0)
        {
            return 1; // Email taken
        }
    }
    return 0;
}

void Forget_Pass(user *plist, int *pnum)
{
    char user[100], email[100], temp[100];
    int i, flag = 0, choice = 0;
    char ch;
    while (1)
    {
        flag = -1;
        printf("🔸Enter Username: ");
        fgets(user, sizeof(user), stdin);
        user[strcspn(user, "\n")] = '\0'; // Remove newline
        printf("🔸Enter Email: ");
        fgets(email, sizeof(email), stdin);
        email[strcspn(email, "\n")] = '\0'; // Remove newline

        for (i = 0; i < *pnum; ++i)
        {
            if (strcmp(user, (plist + i)->username) == 0)
            {
                if (strcmp(email, (plist + i)->email) == 0)
                {
                    flag = i;
                    break;
                }
            }
        }
        if (flag < 0)
        {
            printf(HOT_PINK "Your username and email do not match. Please try again.\n" RESET);
            printf("1.Try again\n2. Exit\nEnter your choice: ");
            scanf("%d", &choice);
            if (choice == 2)
                return;
            Sleep(1000);
            system("cls");
        }
        else
        {
            break;
        }
    }

    while (1)
    {
        if (getPassword(temp, sizeof(temp)))
        {
            (plist + flag)->pass = hash(temp);
            printf(MINT "Password Changed Successfully!\n" RESET);
            Sleep(1000);
            system("cls");
            return;
        }
        printf(HOT_PINK "Please try again!\n" RESET);
    }
}

void clearScreen()
{
    printf("\033[H\033[J");
}

void displayMenu(int selectedOption)
{
    int totalOptions = 4;
    clearScreen();
    displayLogo();
    printf(MINT "                                       Welcome !\n" RESET);
    printf("\n");

    for (int i = 1; i <= totalOptions; i++)
    {
        if (i == selectedOption)
        {
            printf(ORANGE "                                   ");
        }
        else
        {
            printf("                                   ");
        }

        switch (i)
        {
        case 1:
            printf("    Sign Up\n" RESET);
            break;
        case 2:
            printf("    Sign In\n" RESET);
            break;
        case 3:
            printf("Forgot Password\n" RESET);
            break;
        case 4:
            printf("     Exit\n" RESET);
            break;
        }
    }
}

void freeUsers(user *plist, int num)
{
    for (int i = 0; i < num; i++)
    {
        free(plist[i].pglist);
        free(plist + i);
    }
}

void displayLogo()
{
    printf(MAGENTA "\n\n\n\n");
    printf("  ███╗   ███╗ █████╗ ██████╗ ██╗ ██████╗   ██████╗███████╗ ██████╗ █████╗ ███████╗██████╗ \n");
    printf("  ████╗ ████║██╔══██╗██╔══██╗██║██╔═══██╗  ██╔═══╝██╔════╝██╔════╝██╔══██╗██╔══██║██╔═══╝ \n");
    printf("  ██╔████╔██║███████║██████╔╝██║██║   ██║  ██████╗███████╗██║     ███████║███████║██████╗ \n");
    printf("  ██║╚██╔╝██║██╔══██║██╔══██╗██║██║   ██║  ██╔═══╝╚════██║██║     ██╔══██║██╔════╝██╔═══╝ \n");
    printf("  ██║ ╚═╝ ██║██║  ██║██║  ██║██║╚██████╔╝  ██████╗███████║╚██████╗██║  ██║██║     ██████╗ \n");
    printf("  ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝ ╚═════╝   ╚═════╝╚══════╝ ╚═════╝╚═╝  ╚═╝╚═╝     ╚═════╝ \n");
    printf("____________________________________________________________________________________________\n");
    printf("____________________________________________________________________________________________\n");
    printf(RESET "\n");
}

void saveUsers(user *plist, int num)
{
    FILE *file = fopen("C:\\Users\\User\\Desktop\\BP\\Mario\\users.txt", "w");
    if (!file)
    {
        printf(HOT_PINK "Error: Could not open file for writing!\n" RESET);
        return;
    }

    fprintf(file, "%d", num);
    // printf("num: %d\n", num);

    for (int i = 0; i < num; i++)
    {
        fprintf(file, "\n%s", plist[i].username);
        // printf("username: %s\n", plist[i].username);
        fprintf(file, "\n%lu", plist[i].pass);
        // printf("pass: %lu\n", plist[i].pass);
        fprintf(file, "\n%s", plist[i].email);
        // printf("email: %s\n", plist[i].email);
        fprintf(file, "\n%d", plist[i].won);
        // printf("won: %d\n", plist[i].won);
        fprintf(file, "\n%d", plist[i].lost);
        // printf("lost: %d\n", plist[i].lost);
        fprintf(file, "\n%d", plist[i].gplayed);
        // printf("gplayed: %d\n", plist[i].gplayed);
        fprintf(file, "\n%d", plist[i].coins);
        fprintf(file, "\n%d", plist[i].highestscore);

        for (int j = 0; j < plist[i].gplayed; j++)
        {
            fprintf(file, "\n%d", plist[i].pglist[j].point);
            // printf("point: %d\n", plist[i].pglist[j].point);
            fprintf(file, "\n%d", plist[i].pglist[j].coin);
            // printf("coin: %d\n", plist[i].pglist[j].coin);
            fprintf(file, "\n%d", plist[i].pglist[j].stat1);
            // printf("stat1: %d\n", plist[i].pglist[j].stat1);
            fprintf(file, "\n%d", plist[i].pglist[j].stat2);
            // printf("stat2: %d\n", plist[i].pglist[j].stat2);
        }
    }
    fclose(file);
    // printf(MINT "User data saved successfully!\n" RESET);
}

int loadUsers(user *plist, int *pnum)
{
    FILE *file = fopen("C:\\Users\\User\\Desktop\\BP\\Mario\\users.txt", "r");
    if (!file)
    {
        printf(HOT_PINK "Error: Could not open file for reading!\n" RESET);
        return 0;
    }
    if (feof(file))
    {
        *pnum = 0;
        printf("EOF");
        Sleep(1000);
        fclose(file);
        return 0;
    }

    fscanf(file, "%d", pnum);
    fgetc(file);
    // printf("num: %d\n", *pnum);

    for (int i = 0; i < *pnum; i++)
    {
        fgets(plist[i].username, sizeof(plist[i].username), file);
        plist[i].username[strcspn(plist[i].username, "\n")] = '\0';
        // printf("username: %s\n", plist[i].username);

        fscanf(file, "%lu", &plist[i].pass);
        fgetc(file);
        // printf("pass: %lu\n", plist[i].pass);

        fgets(plist[i].email, sizeof(plist[i].email), file);
        plist[i].email[strcspn(plist[i].email, "\n")] = '\0';
        // printf("email: %s\n", plist[i].email);

        fscanf(file, "%d", &plist[i].won);
        fgetc(file);
        // printf("won: %d\n", plist[i].won);

        fscanf(file, "%d", &plist[i].lost);
        fgetc(file);
        // printf("lost: %d\n", plist[i].lost);

        fscanf(file, "%d", &plist[i].gplayed);
        fgetc(file);

        fscanf(file, "%d", &plist[i].coins);
        fgetc(file);

        fscanf(file, "%d", &plist[i].highestscore);
        fgetc(file);
        // printf("gplayed: %d\n", plist[i].gplayed);

        plist[i].pglist = (game *)malloc((plist[i].gplayed + 1) * sizeof(game));
        if (!(plist[i].pglist))
        {
            printf(HOT_PINK "Error: Memory allocation failed!\n" RESET);
            fclose(file);
            return 0;
        }

        for (int j = 0; j < plist[i].gplayed; j++)
        {
            fscanf(file, "%d", &plist[i].pglist[j].point);
            fgetc(file);
            // printf("point: %d\n", plist[i].pglist[j].point);

            fscanf(file, "%d", &plist[i].pglist[j].coin);
            fgetc(file);
            // printf("coin: %d\n", plist[i].pglist[j].coin);

            fscanf(file, "%d", &plist[i].pglist[j].stat1);
            fgetc(file);
            // printf("stat1: %d\n", plist[i].pglist[j].stat1);

            fscanf(file, "%d", &plist[i].pglist[j].stat2);
            fgetc(file);
            // printf("stat2: %d\n", plist[i].pglist[j].stat2);
        }
    }

    fclose(file);
    // printf(MINT "User data loaded successfully!\n" RESET);
    // Sleep(11000);
    return 1;
}
