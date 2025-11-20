#ifndef SONGS_H
#define SONGS_H

typedef struct song
{
    int id;
    char *Name;
    char *artist;
    int duration;
    struct song *next;
} song;

extern song *head;
int get_song_id_by_serial(int serial);
void load_all_saved_songs();
void song_menu();
void add_song();
// void delete_song();
void list_all_saved_songs();
void playSong(int id);

#endif