#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#define RESET "\033[0m"
#define BLUE "\033[34m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define MIN_PASSWORD_LENGTH 8

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

typedef struct game
{
    int point;
    int coin;
    int stat;
} game;

typedef struct user
{
    char username[60];
    unsigned long pass; // Use hashed password
    char email[60];
    int won;
    int lost;
    int gplayed;
    game *pglist;
} user;

int getPassword(char *password, size_t max_len)
{
    int i = 0, flag;
    char ch;
    char password2[60];

    while (1)
    {
        i = 0; // Reset counter
        flag = 1;
        printf("Enter password: ");
        while (i < max_len - 1 && (ch = _getch()) != '\r')
        {
            password[i++] = ch;
            printf("*");
        }
        password[i] = '\0'; // Null-terminate
        printf("\n");

        if (i < MIN_PASSWORD_LENGTH)
        {
            printf(RED "Password must contain at least %d characters\n" RESET, MIN_PASSWORD_LENGTH);
            flag = 0;
            continue;
        }

        i = 0; // Reset counter
        printf("Repeat password: ");
        while (i < max_len - 1 && (ch = _getch()) != '\r')
        {
            password2[i++] = ch;
            printf("*");
        }
        password2[i] = '\0'; // Null-terminate
        printf("\n");

        if (strcmp(password, password2) != 0)
        {
            printf(RED "Passwords do not match!\n" RESET);
            flag = 0;
        }

        if (flag)
            break;
    }

    return 1;
}

int isUsernameTaken(user *plist, int num, const char *username)
{
    for (int i = 0; i < num; ++i)
    {
        if (strcmp(username, plist[i].username) == 0)
        {
            return 1; // Username taken
        }
    }
    return 0;
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

void signup(user *plist, int *pnum)
{
    char buf[100];
    int flag;

    // Username
    while (1)
    {
        printf("Enter Username: ");
        fgets(buf, sizeof(buf), stdin);
        buf[strcspn(buf, "\n")] = '\0'; // Remove newline
        if (isUsernameTaken(plist, *pnum, buf))
        {
            printf(RED "Username has already been taken!\n" RESET);
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
        printf("Enter your Email: ");
        fgets(buf, sizeof(buf), stdin);
        buf[strcspn(buf, "\n")] = '\0'; // Remove newline

        if (strstr(buf, gmail) != NULL)
        {
            if (isEmailTaken(plist, *pnum, buf))
            {
                printf(RED "Email has already been taken!\n" RESET);
            }
            else
            {
                strcpy(plist[*pnum].email, buf);
                break;
            }
        }
        else
        {
            printf(RED "Email format is not supported\n" RESET);
        }
    }

    // Password
    while (1)
    {
        if (getPassword(buf, sizeof(buf)))
        {
            plist[*pnum].pass = hash(buf); // Store hashed password
            break;
        }
        printf(RED "Please try again!\n" RESET);
    }

    (*pnum)++;
    printf(GREEN "Signup successful!\n" RESET);
}

int singin(user *plist, int *pnum)
{
    char buf[100];
    char password[100];
    int i, temp;
    char ch;
    printf("Enter Username: ");
    fgets(buf, sizeof(buf), stdin);
    buf[strcspn(buf, "\n")] = '\0'; // Remove newline
    printf("Enter password: ");
    while (i < 100 - 1 && (ch = _getch()) != '\r')
    {
        password[i++] = ch;
        printf("*");
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
                printf(GREEN "LOG IN sucessfully" RESET);
                return 1;
            }
        }
    }
    printf(RED "Your username and password do not match. Please try again.\n" RESET);
}

void Change_Username(user *plist, int *pnum, int i)
{
    char buf[100];
    int i, flag;
    while (1)
    {
        printf("Enter Username: ");
        fgets(buf, sizeof(buf), stdin);
        buf[strcspn(buf, "\n")] = '\0'; // Remove newline
        flag = 0;
        for (int j = 0; j < i; ++j)
        {
            if (strcmp((plist + j)->username, buf) == 0)
            {
                ++flag;
                break;
            }
        }
        for (int j = i; j < *pnum; ++j)
        {
            if (strcmp((plist + j)->username, buf) == 0)
            {
                ++flag;
                break;
            }
        }
        if (flag)
        {
            printf("Please enter uniqe usename\n");
        }
        else
        {
            strcpy((plist + i)->username, buf);
            return;
        }
    }
}

void Foget_Pass(user *plist, int *pnum)
{
    char user[100], email[100], temp[100];
    int i, flag = 0;
    char ch;
    while (1)
    {
        flag = -1;
        printf("Enter Username: ");
        fgets(user, sizeof(user), stdin);
        user[strcspn(user, "\n")] = '\0'; // Remove newline
        printf("Enter Email: ");
        fgets(email, sizeof(email), stdin);
        email[strcspn(email, "\n")] = '\0'; // Remove newline

        for (i = 0; i < *pnum; ++i)
        {
            if (strcmp(user, (plist + i)->username) == 0)
            {
                if (strcmp(email, (plist + i)->email) == 0)
                {
                    flag = i;
                    // printf(GREEN "LOG IN sucessfully" RESET);
                }
            }
        }
        printf(RED "Your username and email do not match. Please try again.\n" RESET);
    }

    while (1)
    {
        if (getPassword(temp, sizeof(temp)))
        {
            (plist+flag)->pass = hash(temp); // Store hashed password
            return;
        }
        printf(RED "Please try again!\n" RESET);
    }
}