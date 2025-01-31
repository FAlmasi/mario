#ifndef TEST_H
#define TEST_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

#define RESET "\033[0m"
#define BLUE "\033[34m"
#define TURQUOISE "\033[38;5;80m"
#define GREEN "\033[32m"
#define MINT "\033[38;5;121m"
#define RED "\033[31m"
#define YELLOW "\033[1;33m"
#define LIGHT_YELLOW "\033[38;5;227m"
#define ORANGE "\033[38;5;208m"
#define CYAN "\033[1;36m"
#define PURPLE "\033[0;35m"
#define LIGHT_PURPLE "\033[38;5;141m"
#define MAGENTA "\033[38;5;200m"
#define PINK "\033[38;5;205m"
#define HOT_PINK "\033[38;5;198m" 
#define GRAY "\033[90m"

#define MaxUser 500
#define MIN_PASSWORD_LENGTH 8
#define MaxGames 200

typedef struct game
{
    int point;
    int coin;
    int stat1;
    int stat2;
} game;

typedef struct user
{
    char username[60];
    unsigned long pass; // Use hashed password
    char email[60];
    int won;
    int lost;
    int gplayed;
    int coins;
    int highestscore;
    game *pglist;
} user;

extern int coin_count;
extern int cat_lives;
extern int offsetX;
extern int shield;
extern int score_count;
extern int mapindex;
extern int game_over;
extern int sizemario;
extern int retry_count;
extern int fail_count;
extern int shield_delete;
extern int changesizemario;

unsigned long hash(const char *str);
void clearScreen();
int getPassword(char *password, size_t max_len);
void playgame(user *puser);
int isUsernameTaken(user *plist, int num, const char *username);
void Change_Username(user *plist, int num, user *puser);
void displayLogo();
void history(user *puser);
void displaypanel(int selectedOption, user *puser);
void userpanel(user *currentUser, user *plist, int num);
int isEmailTaken(user *plist, int num, const char *email);
void signup(user *plist, int *pnum);
user *singin(user *plist, int *pnum);
void Forget_Pass(user *plist, int *pnum);
void saveUsers(user *plist, int num);
int loadUsers(user *plist, int *pnum);
void clearScreen();
void displayMenu(int selectedOption);
void freeUsers(user *plist, int num);


void moveCharacter(int *i, int *j, char board[][64], int newI, int newJ);
void moveCharacter2(int *i, int *j, char board[][64], int newJ, int *i2, int *j2);
void enableANSI();
void printTimeRemaining();
void moveCursor(int x, int y);
void drawfirstlevel(int select, int retry);
int firstlevelPassed(int *pusercoin, int *puserscore, int *puserstat1, int *puserstat2);
void drawsecondlevel(int select, int retry);
int secondlevelPassed(int *pusercoin, int *puserscore, int *puserstat1, int *puserstat2);
void drawfailedlevel(int select);
int levelfailed();
void coin_block(char map_1[][64], int char_i, int char_j, int map, int retry);
void destructible_block();
void printBoard(char board[][64], int cory);
void moveMush(char map_2[][64], int char_i, int char_j, int flag, int random);
int moveBlock5(char board[][64], int *block5_i, int *block5_j, DWORD *lastUpdate, int delay, int *catY, int *catX, int *direction);
void updateBlockStatus(char board[][64], DWORD *lastUpdate, int delay, int *toggle, int emoji1_i, int emoji1_j, int emoji2_i, int emoji2_j, int *i, int *j);
void checkCheatCode(char ch);

int map2(int *pusercoin, int *puserscore, int *puserstat1, int *puserstat2);
int map1(int *pusercoin, int *puserscore, int *puserstat1, int *puserstat2);
#endif