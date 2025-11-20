#ifndef PLAYLIST_H
#define PLAYLIST_H

typedef struct playlist_song
{
    int id;
    char *Name;
    char *artist;
    int duration;
    struct playlist_song *next;
    struct playlist_song *prev;
} playlist_song;

extern playlist_song *playlist_head;

void remove_last_song_from_playlist();
void playlist_menu();
int add_song_to_current_playlist(int id);

#endif