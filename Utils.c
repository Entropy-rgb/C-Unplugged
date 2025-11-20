#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Albums.h"
#include "Logging.h"
#include "Playlist.h"
#include "Songs.h"
#include "C-Unplugged.h"

playlist_song *Clone_album_songs(playlist_song *head)
{
    playlist_song *temp = head;
    if (head == NULL)
    {
        return NULL;
    }
    playlist_song *head_copy = NULL;
    head_copy = (playlist_song *)malloc(sizeof(playlist_song));
    // head_copy->Name = (char *)malloc(100);
    // head_copy->album = (char *)malloc(100);
    // head_copy->artist = (char *)malloc(100);
    head_copy->Name = strdup(temp->Name);
    // head_copy->album = strdup(temp->album);
    head_copy->artist = strdup(temp->artist);
    head_copy->duration = temp->duration;
    head_copy->id = temp->id;
    head_copy->next = NULL;
    head_copy->prev = NULL;
    playlist_song *temp_copy = head_copy;
    temp = temp->next;
    while (temp != NULL)
    {
        playlist_song *new_copy = (playlist_song *)malloc(sizeof(playlist_song));
        // new_copy->Name = (char *)malloc(100);
        // new_copy->album = (char *)malloc(100);
        // new_copy->artist = (char *)malloc(100);
        new_copy->Name = strdup(temp->Name);
        // new_copy->album = strdup(temp->album);
        new_copy->artist = strdup(temp->artist);
        new_copy->duration = temp->duration;
        new_copy->id = temp->id;
        new_copy->next = NULL;
        new_copy->prev = temp_copy;
        temp_copy->next = new_copy;
        temp = temp->next;
        temp_copy = temp_copy->next;
    }
    return head_copy;
}

void free_playlist_songs(playlist_song *head)
{
    if (head == NULL)
        return;
    playlist_song *current = head;
    playlist_song *first = head;
    if (head->prev)
    {
        head->prev->next = NULL;
    }
    while (current != NULL)
    {
        playlist_song *next = current->next;
        free(current->Name);
        free(current->artist);
        free(current);
        if (next == first)
            break;
        current = next;
    }
}

void free_album_songs(playlist_song *head)
{
    playlist_song *current = head;
    while (current != NULL)
    {
        playlist_song *next = current->next;
        free(current->Name);
        free(current->artist);
        free(current);
        current = next;
    }
}

void free_everything()
{
    song *current_song = head;
    while (current_song != NULL)
    {
        song *next = current_song->next;
        free(current_song->Name);
        free(current_song->artist);
        free(current_song);
        current_song = next;
    }
    head = NULL;
    album *current_album = albums_head;
    while (current_album != NULL)
    {
        album *next = current_album->next;
        free_album_songs(current_album->first_song);
        free(current_album->name);
        free(current_album);
        current_album = next;
    }
    albums_head = NULL;
    free_playlist_songs(playlist_head);
    playlist_head = NULL;
}