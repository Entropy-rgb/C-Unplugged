#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Albums.h"
#include "Playlist.h"
#include "Songs.h"
#include "C-Unplugged.h"

playlist_song *playlist_head = NULL;

void play_curr_playlist()
{
    FILE *log_fp = fopen("log.txt", "a");
    fprintf(log_fp, "USER STARTED PLAYING THE CURRENT PLAYLIST\n");
    playlist_song *curr = playlist_head;
    if (curr == NULL)
    {
        printf("%sERROR: PLAYLIST EMPTY\n%s", RED, RESET);
        playlist_menu();
        return;
    }
    else
    {
        int exit_status = 0;
        while (exit_status == 0)
        {
            printf("%sNow Playing %s from %s\n%s", PINK, curr->Name, curr->artist, RESET);
            printf("%sEnter 1 for previous track\n"
                   "Enter 2 to stop playing\n"
                   "Enter 3 to play next track\n%s",
                   GREEN, RESET);
            int a;
            scanf("%d", &a);
            if (a == 2)
            {
                exit_status = 1;
                continue;
            }
            else if (a == 1)
            {
                curr = curr->next;
                fprintf(log_fp, "USER STARTED PLAYING THE NEXT SONG IN CURRENT PLAYLIST\n");
                continue;
            }
            else if (a == 3)
            {
                curr = curr->prev;
                fprintf(log_fp, "USER STARTED PLAYING THE PREVIOUS SONG IN CURRENT PLAYLIST\n");
                continue;
            }
            else
            {
                printf("%sSUDHEERA SIR PLEASE DON'T PLAY WITH MY CODE, I AM CONTINUING PLAYING THE CURRENT SONG\n%s", RED, RESET);
                continue;
            }
        }
        fclose(log_fp);
        return;
    }
}

void remove_last_song_from_playlist()
{
    FILE *log_fp = fopen("log.txt", "a");
    fprintf(log_fp, "USER TRIED TO DELETE THE LAST SONG IN THE PLAYLIST\n");
    fclose(log_fp);
    if (playlist_head == NULL)
    {
        printf("%sTHE PLAYLIST IS ALREADY EMPTY\n%s", RED, RESET);
        return;
    }
    playlist_song *temp = playlist_head->prev;
    playlist_head->prev->prev->next = playlist_head;
    playlist_head->prev = playlist_head->prev->prev;
    free(temp);
}

void playlist_menu()
{
    FILE *log_fp = fopen("log.txt", "a");
    fprintf(log_fp, "ACCESSED PLAYLIST MENU\n");
    fclose(log_fp);
    printf("%sWelcome to the Playlist Menu\n"
           "%sENTER THE NUMBER IN FRONT OF THE OPTION TO SELECT THE OPTION\n%s"
           "%s1) Create a new playlist (Note : This dumps the current playlist )\n"
           "2) Add a song to current Playlist\n"
           "3) Remove last song from the current Playlist\n"
           "4) Play the current Playlist\n"
           "5) Add album to playlist\n"
           "6) Return back to Home Menu\n%s",
           GREEN, RED, RESET, YELLOW, RESET);
    int a;
    if(scanf("%d", &a)!=1){
            while(getchar()!='\n');
            printf("%sInvalid input. Please enter a number.%s\n", RED, RESET);
            playlist_menu();
            return; 
    }
    if (a == 1)
    {
        playlist_head = NULL;
        printf("%sNew Playlist Created, Previous playlist dumped ( if any )\n%s", RED, RESET);
        playlist_menu();
    }
    else if (a == 2)
    {
        list_all_saved_songs();
        printf("%sEnter the ID of song to add to the current playlist : \n%s", GREEN, RESET);
        int id;
        scanf("%d", &id);
        add_song_to_current_playlist(id);
        playlist_menu();
    }
    else if (a == 3)
    {
        remove_last_song_from_playlist();
        playlist_menu();
    }
    else if (a == 4)
    {
        play_curr_playlist();
        playlist_menu();
    }
    else if (a == 5)
    {
        display_all_albums();
        printf("%sEnter ALBUM_ID to be added to the playlist\n%s",GREEN,RESET);
        int id;
        scanf("%d", &id);
        add_album_to_playlist(id);
        playlist_menu();
    }
    else if (a == 6)
    {
        home_menu();
    }
    else
    {
        printf("%sWRONG INPUT, DISPLAYING PREVIOUS MENU AGAIN\n%s", RED, RESET);
        playlist_menu();
    }
}

int add_song_to_current_playlist(int id)
{
    FILE *log_fp = fopen("log.txt", "a");
    fprintf(log_fp, "USER ADDED SONG WITH ID=%d TO THE CURRENT PLAYLIST\n", id);
    fclose(log_fp);
    song *temp = head;
    while (temp != NULL && temp->id != id)
    {
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("%sCouldn't find the song with the ID, returning back to Playlist Menu\n%s", RED, RESET);
        playlist_menu();
        return 0;
    }
    playlist_song *playlist_temp = playlist_head;
    if (playlist_temp == NULL)
    {
        playlist_head = (playlist_song *)malloc(sizeof(playlist_song));
        playlist_head->id = temp->id;
        playlist_head->Name = strdup(temp->Name);
        playlist_head->artist = strdup(temp->artist);
        // playlist_head->album = strdup(temp->album);
        playlist_head->duration = temp->duration;
        playlist_head->next = playlist_head;
        playlist_head->prev = playlist_head;
        return 1;
    }
    else
    {
        while (playlist_temp->next != playlist_head)
        {
            playlist_temp = playlist_temp->next;
        }
        playlist_song *new = (playlist_song *)malloc(sizeof(playlist_song));
        new->id = temp->id;
        new->Name = strdup(temp->Name);
        new->artist = strdup(temp->artist);
        // new->album = strdup(temp->album);
        new->duration = temp->duration;
        new->next = playlist_head;
        new->prev = playlist_temp;
        playlist_head->prev = new;
        playlist_temp->next = new;
        return 1;
    }
    return 0;
}