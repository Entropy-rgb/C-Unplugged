#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Albums.h"
#include "Logging.h"
#include "Playlist.h"
#include "Songs.h"
#include "C-Unplugged.h"
#include "Utils.h"

char *YELLOW = "\033[1;33m";
char *RESET = "\033[0m";
char *RED = "\033[1;31m";
char *GREEN = "\033[1;32m";
char *WHITE = "\033[1;37m";
char *PINK = "\033[1;35m";

#ifdef _WIN32
#include <windows.h>
void wait_one_second()
{
    Sleep(1000);
}
#else
#include <unistd.h>
// Unix sleep() takes seconds
void wait_one_second()
{
    sleep(1);
}
#endif

void disclaimer()
{
    printf("%sDisclaimer : Please Enter CamelCase Input , if you don't some random things may occur (for eg input CamelCase for Camel Case)%s\n", RED, RESET);
}

int home_menu()
{
    FILE *log_fp = fopen("log.txt", "a");
    fprintf(log_fp, "FETCH HOME MENU\n");
    fclose(log_fp);
    int userInput;
    printf("%sWelcome to C-Unplugged%s\n\n"
           "%sPress The Number in front of the option to select that option%s\n"
           "%sPress ctrl-C at any point of time to quit the program%s\n"
           "%s1) Songs (To go to the song menu)%s\n"
           "%s2) Albums (To Go to the Albums Menu)%s\n"
           "%s3) Playlist (To go to the Playlist menu)%s\n"
           "%s4) History (Revealing your secrets......)%s\n"
           "%s5) Quit (to not listen to me anymore :( )%s\n",
           GREEN, RESET, WHITE, RESET, RED, RESET, YELLOW, RESET, YELLOW, RESET, YELLOW, RESET, YELLOW, RESET, YELLOW, RESET);
    if(scanf("%d", &userInput)!=1){
            while(getchar()!='\n');
            printf("%sInvalid input. Please enter a number.%s\n", RED, RESET);
            home_menu();
    }
    if (userInput == 5)
    {
        FILE *log_fp = fopen("log.txt", "a");
        fprintf(log_fp, "EXIT PROGRAM\n");
        fclose(log_fp);
        exit(EXIT_SUCCESS);
    }
    if (userInput == 4)
    {
        display_history();
    }
    if (userInput == 1)
    {
        song_menu();
    }
    if (userInput == 2)
    {
        album_menu();
    }
    if (userInput == 3)
    {
        playlist_menu();
    }
    if (userInput == 1 || userInput == 2 || userInput == 3 || userInput == 4 || userInput == 5)
    {
        return userInput;
    }
    else
    {
        printf("%sInvalid input, kindly input correctly TA's, I'll display the menu again only for you <3%s\n", RED, RESET);
        home_menu();
    }
}

int main()
{
    FILE *fp = fopen("log.txt", "a");
    fprintf(fp, "APPLICATION STARTED\n");
    fclose(fp);
    load_all_saved_songs();
    // printf("loaded all songs correctly\n");
    load_all_saved_albums();
    // printf("loaded all albums correctly\n");
    advertisement();
    home_menu();
    return 0;
}