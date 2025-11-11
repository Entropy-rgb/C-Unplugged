#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Utils.h"
#include "C-Unplugged.h"
#include "Songs.h"
#include "Playlist.h"
#include "Logging.h"
#include "Albums.h"

album *albums_head = NULL;

void save_all_albums_to_file()
{
    FILE *log_fp = fopen("log.txt", "a");
    fprintf(log_fp, "SAVED ALL ALBUMS TO MEMORY\n");
    fclose(log_fp);
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
    FILE *log_fp = fopen("log.txt", "a");
    fprintf(log_fp, "USER LOADED ALL SAVED ALBUMS\n");
    fclose(log_fp);

    FILE *fp = fopen("data/albums.txt", "r");
    if (fp == NULL)
    {
        printf("%sERROR OPENING SAVED FILES\n%s", RED, RESET);
        return;
    }

    album *temp = NULL;
    album *curr = NULL;
    char line_buffer[1024];

    while (fgets(line_buffer, sizeof(line_buffer), fp))
    {
        if (strncmp(line_buffer, "#AlbumName:", 11) == 0)
        {
            album *newAlbum = malloc(sizeof(album));
            newAlbum->name = malloc(100);
            newAlbum->first_song = NULL;
            newAlbum->next = NULL;

            sscanf(line_buffer, "#AlbumName: %s #AlbumId=%d", newAlbum->name, &newAlbum->album_id);

            if (albums_head == NULL)
            {
                albums_head = newAlbum;
                temp = newAlbum;
            }
            else
            {
                temp = albums_head;
                while (temp->next != NULL)
                    temp = temp->next;
                temp->next = newAlbum;
            }

            curr = newAlbum;
        }
        else if (curr != NULL)
        {
            char *token = strtok(line_buffer, " ");
            while (token != NULL)
            {
                int id = atoi(token);
                song *findSong = head;
                while (findSong && findSong->id != id)
                    findSong = findSong->next;

                if (!findSong)
                {
                    token = strtok(NULL, " ");
                    continue;
                }

                playlist_song *newSong = malloc(sizeof(playlist_song));
                newSong->Name = strdup(findSong->Name);
                newSong->artist = strdup(findSong->artist);
                // newSong->album = strdup(findSong->album);
                newSong->duration = findSong->duration;
                newSong->id = findSong->id;
                newSong->next = NULL;
                newSong->prev = NULL;

                if (curr->first_song == NULL)
                    curr->first_song = newSong;
                else
                {
                    playlist_song *s = curr->first_song;
                    while (s->next != NULL)
                        s = s->next;
                    s->next = newSong;
                    newSong->prev = s;
                }

                token = strtok(NULL, " ");
            }
        }
    }
    fclose(fp);
}

void create_new_album()
{
    FILE *log_fp = fopen("log.txt", "a");
    fprintf(log_fp, "USER CREATED NEW ALBUM\n");
    fclose(log_fp);
    album *newAlbum = (album *)malloc(sizeof(album));
    char AlbumName[50];
    disclaimer();
    printf("%sEnter New Album Name : \n%s", GREEN, RESET);
    scanf("%s", AlbumName);
    newAlbum->name = strdup(AlbumName);
    newAlbum->first_song = NULL;
    newAlbum->next = NULL;
    album *temp = albums_head;
    if (temp == NULL)
    {
        albums_head = newAlbum;
        newAlbum->album_id = 1;
    }
    else
    {
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newAlbum;
        newAlbum->album_id = temp->album_id + 1;
        temp = temp->next;
    }
    save_all_albums_to_file();
}

void display_album_songs(int album_id)
{
    FILE *log_fp = fopen("log.txt", "a");
    fprintf(log_fp, "USER TRIED DISPLAYING ALL SONGS IN ALBUM WITH ALBUMID = %d\n", album_id);
    fclose(log_fp);
    album *temp = albums_head;
    while (temp != NULL && temp->album_id != album_id)
        temp = temp->next;
    if (temp == NULL)
    {
        printf("%sError : Specified Album Not found%s\n", RED, RESET);
        return;
    }
    else
    {
        playlist_song *songs = temp->first_song;
        while (songs != NULL)
        {
            printf("%sSongID = %d Song Name : %s\n%s", WHITE, songs->id, songs->Name, RESET);
            songs = songs->next;
        }
    }
}

void add_album_to_playlist(int id)
{
    FILE *log_fp = fopen("log.txt", "a");
    fprintf(log_fp, "USER ADDED ALBUM TO CURRENT PLAYLIST\n");
    fclose(log_fp);
    album *temp = albums_head;
    while (temp != NULL && temp->album_id != id)
        temp = temp->next;
    if (temp == NULL)
    {
        printf("%sError : Specified Album Not found%s\n", RED, RESET);
        return;
    }
    if (playlist_head == NULL)
    {
        playlist_song *duplicate = Clone_album_songs(temp->first_song);
        playlist_head = duplicate;
        playlist_song *tail = duplicate;
        while (tail->next != NULL)
            tail = tail->next;
        tail->next = duplicate;
        duplicate->prev = tail;
        return;
    }
    playlist_song *duplicate = Clone_album_songs(temp->first_song);
    playlist_song *last = playlist_head->prev;
    last->next = duplicate;
    duplicate->prev = last;
    playlist_song *findLastSong = duplicate;
    while (findLastSong->next != NULL)
        findLastSong = findLastSong->next;
    findLastSong->next = playlist_head;
    playlist_head->prev = findLastSong;
    return;
}

void display_all_albums()
{
    FILE *log_fp = fopen("log.txt", "a");
    fprintf(log_fp, "USER DISPLAYED ALL ALBUMS\n");
    fclose(log_fp);
    album *temp = albums_head;
    while (temp != NULL)
    {
        printf("%s#AlbumID = %d #AlbumName = %s\n%s", WHITE, temp->album_id, temp->name, RESET);
        temp = temp->next;
    }
}

void add_song_to_album(int song_id, int album_id)
{
    FILE *log_fp = fopen("log.txt", "a");
    fprintf(log_fp, "USER ADDED A SONG TO AN ALBUM\n");
    fclose(log_fp);
    album *temp = albums_head;
    while (temp != NULL && temp->album_id != album_id)
        temp = temp->next;
    if (temp == NULL)
    {
        printf("%sError : Specified Album Not found%s\n", RED, RESET);
        save_all_albums_to_file();
        return;
    }
    song *findsong = head;
    while (findsong != NULL && findsong->id != song_id)
        findsong = findsong->next;
    if (findsong == NULL)
    {
        printf("%sError : Specified Song Not found%s\n", RED, RESET);
        save_all_albums_to_file();
        return;
    }
    playlist_song *newsong = (playlist_song *)malloc(sizeof(playlist_song));
    newsong->id = findsong->id;
    newsong->Name = strdup(findsong->Name);
    newsong->next = NULL;
    // newsong->album = strdup(findsong->album);
    newsong->artist = strdup(findsong->artist);
    newsong->prev = NULL;
    playlist_song *add_song = temp->first_song;
    if (temp->first_song == NULL)
    {
        temp->first_song = newsong;
        save_all_albums_to_file();
        return;
    }
    while (add_song->next != NULL)
        add_song = add_song->next;
    add_song->next = newsong;
    newsong->prev = add_song;
    save_all_albums_to_file();
    return;
}

void remove_song_from_album(int song_id, int album_id)
{
    FILE *log_fp = fopen("log.txt", "a");
    fprintf(log_fp, "USER REMOVED SONG FROM AN ALBUM\n");
    fclose(log_fp);
    album *temp = albums_head;
    while (temp != NULL && temp->album_id != album_id)
        temp = temp->next;
    if (temp == NULL)
    {
        printf("%sError : Specified Album Not found%s\n", RED, RESET);
        return;
    }
    playlist_song *song_temp = temp->first_song;
    playlist_song *song_prev = NULL;
    if (song_temp == NULL)
    {
        printf("%sERROR: No Songs to delete.\n%s", RED, RESET);
        return;
    }
    if (temp->first_song->id == song_id)
    {
        temp->first_song = temp->first_song->next;
        // free(song_temp->album);
        free(song_temp->artist);
        free(song_temp->Name);
        free(song_temp);
        save_all_albums_to_file();
        return;
    }
    while (song_temp != NULL && song_temp->id != song_id)
    {
        song_prev = song_temp;
        song_temp = song_temp->next;
    }
    if (song_temp == NULL)
    {
        printf("%sError : Specified Song Not found in the Album mentioned.%s\n", RED, RESET);
        save_all_albums_to_file();
        return;
    }
    song_prev->next = song_temp->next;
    if (song_temp->next)
        song_temp->next->prev = song_prev;
    // free(song_temp->album);
    free(song_temp->artist);
    free(song_temp->Name);
    free(song_temp);
    save_all_albums_to_file();
}

void delete_album(int album_id)
{
    FILE *log_fp = fopen("log.txt", "a");
    fprintf(log_fp, "USER TRIED DELETED AN ALBUM\n");
    fclose(log_fp);
    album *temp = albums_head;
    album *prev = NULL;
    if (temp == NULL)
    {
        printf("%sERROR: No albums to delete.\n%s", RED, RESET);
        return;
    }
    if (temp->album_id == album_id)
    {
        albums_head = temp->next;
        free(temp);
        save_all_albums_to_file();
        return;
    }
    while (temp != NULL && temp->album_id != album_id)
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("%sERROR: Unable to find the album\n%s", RED, RESET);
        save_all_albums_to_file();
        return;
    }
    prev->next = temp->next;
    free(temp->name);
    free(temp);
    save_all_albums_to_file();
}

void album_menu()
{
    FILE *log_fp = fopen("log.txt", "a");
    fprintf(log_fp, "USER ACCESSED ALBUM MENU\n");
    fclose(log_fp);
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
    if (scanf("%d", &a) != 1)
    {
        while (getchar() != '\n')
            ;
        printf("%sInvalid input. Please enter a number.%s\n", RED, RESET);
        album_menu();
    }
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
        scanf("%d", &id);
        display_album_songs(id);
        album_menu();
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
        printf("%sEnter ALBUM_ID of the album you would like to delete :\n%s", GREEN, RESET);
        int id;
        scanf("%d", &id);
        delete_album(id);
        album_menu();
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