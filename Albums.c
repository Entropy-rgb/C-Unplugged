#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "C-Unplugged.h"
#include "Songs.h"
#include "Playlist.h"
#include "Logging.h"
#include "Albums.h"

album *albums_head = NULL;

void save_all_albums_to_file()
{
    FILE *fp = fopen("data/albums.txt", "w");
    if (fp == NULL)
    {
        printf("%sERROR ACCESSING SAVED FILES\n%s", RED, RESET);
    }
    album *temp = albums_head;
    while (temp != NULL)
    {
        fprintf(fp, "#AlbumName: %s #AlbumId=%d \n", temp->name, temp->album_id);
        playlist_song *pehla_song = temp->first_song;
        while (pehla_song != NULL)
        {
            fprintf(fp, "%d ", pehla_song->id);
            pehla_song = pehla_song->next;
        }
        fprintf(fp, "\n");
        temp = temp->next;
    }
    fclose(fp);
}

void load_all_saved_albums()
{
    album *temp;
    album* curr;
    FILE *fp = fopen("data/albums.txt", "r");
    if (fp == NULL)
    {
        printf("%sERROR OPENING SAVED FILES\n%s", RED, RESET);
    }
    char line_buffer[1024];
    while (fgets(line_buffer, sizeof(line_buffer), fp) != EOF)
    {
        if (strncmp(line_buffer, "#AlbumName:", 11) == 0)
        {
            album *newAlbum = (album *)malloc(sizeof(album));
            newAlbum->first_song = NULL;
            newAlbum->next = NULL;
            sscanf(line_buffer, "#AlbumName: %s #AlbumId=%d", newAlbum->name, newAlbum->album_id);
            if (albums_head == NULL)
            {
                albums_head = newAlbum;
                temp = newAlbum;
            }
            else
            {
                while(temp->next!=NULL){
                    temp = temp->next;
                }
                temp->next = newAlbum;
                temp = temp->next;
            }
            curr = newAlbum;
        }else if(curr != NULL){
            
        }
    }
}

void create_new_album()
{
}

void display_album_songs(int album_id)
{
}

void add_album_to_playlist(int id)
{
}

void display_all_albums()
{
}

void add_song_to_album(int song_id, int album_id)
{
}

void remove_song_from_album(int song_id, int album_id)
{
}

void delete_album(int album_id)
{
}

void album_menu()
{
    printf("%sWelcome to the ALBUM MENU\n%s", GREEN, RESET);
    printf("%s1) Create a new Album\n"
           "2) List all Albums\n"
           "3) View Songs in an album\n"
           "4) Add a song to an album\n"
           "5) Remove song from an album\n"
           "6) Delete an Album\n"
           "7) Return to Home menu\n%s",
           YELLOW, RESET);
    int a;
    scanf("%d", &a);
    if (a == 1)
    {
        create_new_album();
        album_menu();
    }
    else if (a == 2)
    {
        display_all_albums();
        album_menu();
    }
    else if (a == 3)
    {
        display_all_albums();
        int id;
        printf("\n%sEnter the ALBUM_ID of the album you would like to see the songs of : \n%s", GREEN, RESET);
        display_album_songs(id);
    }
    else if (a == 4)
    {
        display_all_albums();
        int id, Album_id;
        printf("\n%sEnter the ALBUM_ID of the album you would like to add a song to : \n%s", GREEN, RESET);
        scanf("%d", &Album_id);
        list_all_saved_songs();
        printf("\n%sEnter the ID of the song you would like to add to the selected album : \n%s", GREEN, RESET);
        scanf("%d", &id);
        add_song_to_album(id, Album_id);
        album_menu();
    }
    else if (a == 5)
    {
        display_all_albums();
        int id, Album_id;
        printf("\n%sEnter the ALBUM_ID of the album you would like to remove a song from : \n%s", GREEN, RESET);
        scanf("%d", &Album_id);
        display_album_songs(Album_id);
        printf("\n%sEnter the ID of the song you would like to delete from the album : \n%s", GREEN, RESET);
        scanf("%d", &id);
        remove_song_from_album(id, Album_id);
        album_menu();
    }
    else if (a == 6)
    {
        display_all_albums();
        printf("Enter ALBUM_ID of the album you would like to delete :\n");
        int id;
        scanf("%d", &id);
        delete_album(id);
    }
    else if (a == 7)
    {
        home_menu();
    }
    else
    {
        printf("%sInvalid Input, displaying album menu again\n%s", RED, RESET);
        album_menu();
    }
}