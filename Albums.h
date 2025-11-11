#ifndef ALBUMS_H
#define ALBUMS_H

typedef struct album{
    char* name;
    int number_of_songs;
    int album_id;
    struct playlist_song* first_song;
    struct album* next;
}album;

extern album* albums_head;

void create_new_album();
void display_album_songs(int album_id);
void add_song_to_album(int song_id, int album_id);
void remove_song_from_album(int song_id, int album_id);
void delete_album(int album_id);
void add_album_to_playlist(int id);
void display_all_albums();
void album_menu();
void load_all_saved_albums();
void save_all_albums_to_file();

#endif