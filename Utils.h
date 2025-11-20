#include "Playlist.h"
#ifndef UTILS_H
#define UTILS_H

playlist_song *Clone_album_songs(playlist_song *head);
void free_everything();
void free_playlist_songs(playlist_song *head);
void free_album_songs(playlist_song *head);
void free_everything();
#endif