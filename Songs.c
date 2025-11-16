#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Logging.h"
#include "C-Unplugged.h"
#include "Songs.h"

song *head = NULL;

void load_all_saved_songs()
{
    FILE *log_fp = fopen("log.txt", "a");
    fprintf(log_fp, "LOAD ALL SAVED SONGS\n");
    fclose(log_fp);
    int id, duration;
    char *name = (char *)malloc(sizeof(char) * 50);
    char *artist = (char *)malloc(sizeof(char) * 50);
    // char *album = (char *)malloc(sizeof(char) * 50);
    FILE *fp = fopen("data/songs.txt", "r");
    if (fp == NULL)
    {
        printf("%sERROR OPENING SAVED FILE%s\n", RED, RESET);
        free(name);
        free(artist);
        fclose(fp);
        return;
    }
    while (fscanf(fp, "ID=%d | Name=%s | Artist=%s | Duration:%d\n", &id, name, artist, &duration) == 4)
    {
        song *temp = head;
        if (head == NULL)
        {
            head = (song *)malloc(sizeof(song));
            head->Name = strdup(name);
            head->artist = strdup(artist);
            // head->album = strdup(album);
            head->id = id;
            head->duration = duration;
            head->next = NULL;
        }
        else
        {
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            song *newsong = (song *)malloc(sizeof(song));
            newsong->Name = strdup(name);
            newsong->artist = strdup(artist);
            // newsong->album = strdup(album);
            newsong->id = id;
            newsong->duration = duration;
            newsong->next = NULL;
            temp->next = newsong;
        }
    }
    fclose(fp);
    free(name);
    free(artist);
    return;
}

void song_menu()
{
    FILE *log_fp = fopen("log.txt", "a");
    fprintf(log_fp, "FETCH SONG MENU\n");
    fclose(log_fp);
    int userInput;
    while (1)
    {
        printf("%sWelcome to the Song Menu\n%s"
               "%sPress The Number in front of the option to select that option%s\n"
               "%s1) Add a song\n"
               "2) List all saved songs\n"
               "3) Play a song\n"
               "4) Return to Home Menu\n\n%s",
               GREEN, RESET, WHITE, RESET, YELLOW, RESET);
        if(scanf("%d", &userInput)!=1){
            while(getchar()!='\n');
            printf("%sInvalid input. Please enter a number.%s\n", RED, RESET);
            continue; 
        }
        if (userInput == 1)
        {
            add_song();
            song_menu();
        }
        else if (userInput == 2)
        {
            list_all_saved_songs();
            song_menu();
        }
        else if (userInput == 3)
        {
            list_all_saved_songs();
            printf("%s\nEnter the ID of song you want to play:\n%s",YELLOW,RESET);
            int a;
            scanf("%d", &a);
            playSong(a);
        }
        else if (userInput == 4)
        {
            home_menu();
            return;
        }
        else
        {
            printf("%sInvalid Input Displaying Menu Again\n%s", RED, RESET);
            song_menu();
        }
    }
    return;
}

void add_song()
{
    FILE *log_fp = fopen("log.txt", "a");
    fprintf(log_fp, "USER SAVED A SONG IN MEMORY\n");
    fclose(log_fp);
    char songName[50];
    disclaimer();
    printf("%sEnter Song Name : %s",GREEN,RESET);
    scanf("%s", songName);
    FILE *fp = fopen("data/songs.txt", "a");
    printf("%sEnter Artist Name : %s",GREEN,RESET);
    char ArtistName[50];
    scanf("%s", ArtistName);
    // printf("%sEnter Album to save in : %s",GREEN,RESET);
    // char AlbumName[50];
    // scanf("%s", AlbumName);
    int duration;
    printf("%sEnter Duration of song in seconds : %s",GREEN,RESET);
    scanf("%d", &duration);
    song *temp = head;
    if (temp == NULL)
    {
        head = (song *)malloc(sizeof(song));
        head->id = 1;
        head->next = NULL;
        head->Name = strdup(songName);
        head->artist = strdup(ArtistName);
        // head->album = strdup(AlbumName);
        head->duration = duration;
        fprintf(fp, "ID=%d | Name=%s | Artist=%s | Duration:%d\n", head->id, songName, ArtistName, duration);
        fclose(fp);
        return;
    }
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    song *newSong = (song *)malloc(sizeof(song));
    newSong->Name = strdup(songName);
    newSong->artist = strdup(ArtistName);
    // newSong->album = strdup(AlbumName);
    newSong->id = temp->id + 1;
    newSong->next = NULL;
    newSong->duration = duration;
    temp->next = newSong;
    fprintf(fp, "ID=%d | Name=%s | Artist=%s | Duration:%d\n", newSong->id, songName, ArtistName, duration);
    fclose(fp);
}

void list_all_saved_songs()
{
    FILE *log_fp = fopen("log.txt", "a");
    fprintf(log_fp, "USER LISTED ALL SAVED SONGS\n");
    fclose(log_fp);
    printf("%sTHIS IS THE LIST OF ALL SONGS\n\n%s", RED, RESET);
    FILE *fp = fopen("data/songs.txt", "r");
    char c = 0;
    printf("%s", WHITE);
    while (c != EOF)
    {
        printf("%c", c);
        // wait_one_second(1000);
        c = fgetc(fp);
    }
    printf("%s\n\n", WHITE);
    fclose(fp);
    return;
}

void playSong(int id)
{
    FILE *log_fp = fopen("log.txt", "a");
    fprintf(log_fp, "USER TRIED TO PLAY A SONG WITH ID=%d\n", id);
    fclose(log_fp);
    song *temp = head;
    while (temp != NULL && temp->id != id)
    {
        temp = temp->next;
    }
    if(temp == NULL){
        printf("%sSONG NOT FOUND\n%s", RED, RESET);
        return;
    }
    if (temp->id == id)
    {
        printf("%sNow Playing %s by %s\n%s", PINK, temp->Name, temp->artist, RESET);
    }
    else
    {
        printf("%sSONG NOT FOUND\n%s", RED, RESET);
    }
}