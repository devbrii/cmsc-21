#include <stdio.h>
#include <string.h>

struct song
{
    char title[30];
    char artist[30];
    char album[30];
};

struct playlist
{
    char name[30];
    int song_count;
    struct song songs[10];
};

// Function Prototypes - User Prompts
void noPlaylistPrompt();
void availablePlaylist(struct playlist*, int, int*);

// Function Prototypes - Choices
void addPlaylist(struct playlist*, int*); // choice 1
void addSongs(struct playlist*, int, int); // choice 2
void removeSong(struct playlist*, int, int); // choice 3
void viewPlaylist(struct playlist*, int, int); // choice 4
void viewAll(struct playlist*, int); // choice 5

// Function Prototypes - Files
void save(struct playlist*, int); // for saving into a file
void load(struct playlist*, int*); // for file reading

int main()
{
    struct playlist records[10]; // user can add upto 10 playlists
    int user_input = 0, playlist_count = 0, index;

    load(records, &playlist_count); // load file at the start of the program

    while (1)
    {
        printf("\n======= MENU =======\n");
        printf("[1] Add Playlist\n");
        printf("[2] Add Song to Playlist\n");
        printf("[3] Remove Song from Playlist\n");
        printf("[4] View a Playlist\n");
        printf("[5] View All Data\n");
        printf("[6] Exit\n\n");

        printf("Choice: ");
        scanf("%d", &user_input);
        printf("\n");

        if (user_input == 1) addPlaylist(records, &playlist_count); // Adding a playlist
        
        else if (user_input == 2) // Add at most 10 songs per playlist 
        {   
            if (playlist_count == 0) noPlaylistPrompt();
            else
            {
                availablePlaylist(records, playlist_count, &index);
                addSongs(records, playlist_count, index);
            }
        }

        else if (user_input == 3) // remove a song in a given playlist
        {
            if (playlist_count == 0) noPlaylistPrompt();
            else
            {
                availablePlaylist(records, playlist_count, &index);
                removeSong(records, playlist_count, index);
            }
        }

        else if (user_input == 4) // view all songs of a certain playlist
        {
            if (playlist_count == 0) noPlaylistPrompt();
            else
            {
                availablePlaylist(records, playlist_count, &index);
                viewPlaylist(records, playlist_count, index);   
            }
        }

        else if (user_input == 5) // view all playlists including songs, if any.
        {
            if (playlist_count == 0) noPlaylistPrompt();
            else viewAll(records, playlist_count);
        }

        else if (user_input == 6) // terminating the program
            break;

        else
            printf("Invalid Choice!\n");

    }

    save(records, playlist_count); // save file before terminating the program.
    printf("Program terminated.\n");

    return 0;
}

void addPlaylist(struct playlist *records, int *playlist_count)
{
    if ((*playlist_count) == 10) // the array can handle at most 10 playlists
        printf("Your playlist is already full!\n");
    else
    {
        char duplicate_checker[30], temp;

        printf("Enter playlist name: ");
        scanf("%c", &temp); // temp statement to clear buffer
        scanf("%[^\n]", duplicate_checker); // this will hold the user input for playlist name

        for (int i = 0; i <= (*playlist_count); i++) // loop to check if the user input has a duplicate playlist
        {
            if (strcmp(duplicate_checker, records[i].name) == 0) // just compares if a playlist i is the same with the user input duplicate_checker
            {
                printf("Playlist %s is already in your records!\n", duplicate_checker); 
                break;
            }
            else if (i == (*playlist_count))
            {
                strcpy(records[(*playlist_count)].name, duplicate_checker); // copies the contents of duplicate_checker to records[(*playlist_count)].name
                records[(*playlist_count)].song_count = 0; // initialize the songCount to 0, for later purposes of adding songs

                printf("%s is successfully added.\n", records[(*playlist_count)].name);

                (*playlist_count)++; // playlist_count is incremented by 1, which will be the index of the next playlist

                break;

                // for instance, user inputs his/her first playlist, the index is 0.
                    // so, records[platlist_count].name will be  records[0].name.
            }
        }
    }
}

void noPlaylistPrompt() // if playlist_count is 0, and user chose to add a song or view a playlist
{
    printf("You don't have any playlist yet!\n");
    printf("Add one first.\n");
}

void availablePlaylist(struct playlist *records, int playlist_count, int *index)
{
    printf("THE PLAYLISTS AVAILABLE ARE:\n");
    for (int x = 0; x < playlist_count; x++)
    {
        printf("[%d] %s\n", x, records[x].name);
    }

    printf("\nEnter playlist number: ");
    scanf("%d", index);
    printf("\n");

    // prints all of the playlists available (according to their indeces)
        // then, the user will be prompt for their chosen palylist given the index
}

void addSongs(struct playlist *records, int playlist_count, int index)
{
    char temp;
    
    // the index must not be greater than or equal or less than 0 for we will access an invalid index
    if (index >= playlist_count || index < 0) printf("Invalid input!\n"); // the index must be greater than or equal 
    else
    {
        int counter = records[index].song_count; // passing it as index will be too long, so we just set it to a variable

        if (counter == 10) // number of songs must not be greater than 10. We will be accessing the 10 + nth index 
            printf("You've exceeded the maximum number of songs in your playlist!\n");
        else
        {
            scanf("%c", &temp); // temp statement to clear buffer
            printf("Enter song title: ");
            scanf("%[^\n]", records[index].songs[counter].title); // scanf nth (counter) song title of the given playlist (represented by the index)

            scanf("%c", &temp); // temp statement to clear buffer
            printf("Enter song artist: ");
            scanf("%[^\n]", records[index].songs[counter].artist); // scanf nth (counter) song artist of the given playlist (represented by the index)

            scanf("%c", &temp); // temp statement to clear buffer
            printf("Enter song album: ");
            scanf("%[^\n]", records[index].songs[counter].album); // scanf nth (counter) song album of the given playlist (represented by the index)

            printf("\nSong is successfully added to playlist.\n");

            records[index].song_count++; // song count will be incremented by 1, up to 10 songs per playlist
        }
    }
} 

void viewPlaylist(struct playlist *records, int playlist_count, int index)
{
    // the index must not be greater than or equal or less than 0 for we will access an invalid index
    if (index >= playlist_count || index < 0)
        printf("\nInvalid input!\n");
    else
    {
        printf("PLAYLIST: %s\n", records[index].name); // prints the name of the playlist given the index inputted by the user
        printf("SONG COUNT: %d\n", records[index].song_count); // prints the number of songs in the playlist given the index inputted by the user
        for (int j = 0; j < records[index].song_count; j++) // for every iteration up until the number of songs in the given playlist
        {
            printf("   SONG TITLE: %s\n", records[index].songs[j].title); // prints the title of the song in the playlist given the index inputted by the user
            printf("   SONG ARTIST: %s\n", records[index].songs[j].artist); // prints the artist of that song in the playlist given the index inputted by the user
            printf("   SONG ALBUM: %s\n\n", records[index].songs[j].album); // prints the abum of that song in the playlist given the index inputted by the user
        }
    }
}

void viewAll(struct playlist *records, int playlist_count)
{
    for (int i = 0; i < playlist_count; i++)
    {
        printf("PLAYLIST: %s\n", records[i].name);
        printf("SONG COUNT: %d\n", records[i].song_count);
        for (int j = 0; j < records[i].song_count; j++)
        {
            printf("   SONG TITLE: %s\n", records[i].songs[j].title);
            printf("   SONG ARTIST: %s\n", records[i].songs[j].artist);
            printf("   SONG ALBUM: %s\n\n", records[i].songs[j].album);
        }
        printf("\n");
    }

    // prints all playlist and songs in the current playlist in the iteration
        // playlist index 0 -> print all songs (up until song count index)
        // playlist index 1 -> print all songs (up until song count index)
        // playlist index 2 -> print all songs (up until song count index)
        // etc. up until playlist last index
}

void removeSong(struct playlist *records, int playlist_count, int index)
{
    // the index must not be greater than or equal or less than 0 for we will access an invalid index
    if (index >= playlist_count || index < 0) printf("\nInvalid input!\n");
    else
    {   
        if (records[index].song_count == 0) // there are no songs in the given playlist
            printf("You have no songs to delete in this playlist!\n");
        else
        {
            int song_index;

            // prints all songs in the given playlist.
            printf("SONGS IN %s playlist:\n", records[index].name);
            for (int x = 0; x < records[index].song_count; x++)
            {
                printf("[%d] %s\n", x, records[index].songs[x].title);
            }

            printf("\nSelect a song to delete: ");
            scanf("%d", &song_index); // song_index for removing a song
            
            // the index must not be greater than or equal or less than 0 for we will access an invalid index
            if (song_index >= records[index].song_count || song_index < 0)
                printf("\nInvalid input!\n");
            else
            {
                for (int y = song_index; y < records[index].song_count; y++)
                {
                    if (song_index == (records[index].song_count) - 1) break;
                    else
                    {
                        strcpy(records[index].songs[y].title, records[index].songs[y + 1].title);
                        strcpy(records[index].songs[y].artist, records[index].songs[y + 1].artist);
                        strcpy(records[index].songs[y].album, records[index].songs[y + 1].album);
                    }

                    // move the contents of every next index one index backwards (if that makes sense HAHAHA)
                        // Given index & contents:
                        // 0 1 2 3 4 5
                        // a b c d e f
                        // delete index 2
                        // move contents of index 3 to index 2, index 4 to index 3, index 5 to index 4
                        // we now have a b d e f YAY!
                }
                (records[index].song_count) --; // decrement the song count because we will now have n-1 songs after deletions
                 
                printf("\nSong is successfully deleted!\n");
            }
        }
    }
}

void save(struct playlist *records, int playlist_count)
{
    FILE *fp = fopen("songs.txt", "w");

    // puts the number of playlist to the file (0 if there aren't any playlists available)
    fprintf(fp, "%d\n", playlist_count);    
    
    if (playlist_count == 0) printf("There are no data to be saved.\n");
    else
    {
        for (int i = 0; i < playlist_count; i++)
        {   
            fprintf(fp, "%s\n", records[i].name);
            fprintf(fp, "%d\n", records[i].song_count);
            for (int j = 0; j < records[i].song_count; j++)
            {
                fprintf(fp, "%s\n", records[i].songs[j].title);
                fprintf(fp, "%s\n", records[i].songs[j].artist);
                fprintf(fp, "%s\n", records[i].songs[j].album);
            }
        }

        printf("Successfully saved data.\n");
    }

    fclose(fp);

    // for every playlist, the playlist name will be put to the file first, then the number of songs, then the title, artist, and album, if any.
        // in order of user inputs
    // close the file so it cannot be updated by any means
}

void load(struct playlist *records, int *playlist_count)
{
    FILE *fp = fopen("songs.txt", "r");

    if (fp == NULL) printf("File was not opened!\n");
    else
    {   
        fscanf(fp, "%d\n", playlist_count);

        // the file is empty except for the playlist number 0 if there arent any playlists available
            // the value of playlist_count will still be 0.
        if (*playlist_count == 0) printf("There are no data to be loaded.\n");
        else
        {
            for (int i = 0; i < *playlist_count; i++)
            {   
                fscanf(fp, "%[^\n]\n", records[i].name);
                fscanf(fp, "%d\n", &records[i].song_count);
                for (int j = 0; j < records[i].song_count; j++)
                {
                    fscanf(fp, "%[^\n]\n", records[i].songs[j].title);
                    fscanf(fp, "%[^\n]\n", records[i].songs[j].artist);
                    fscanf(fp, "%[^\n]\n", records[i].songs[j].album);
                }
            }

            printf("Successfully loaded data.\n");
        }

        fclose(fp);

         // for every playlist, the playlist name will be fetched from the file first, then the number of songs, then the title, artist, and album, if any.
            // in order of placing in the file.
        // close the file so it cannot be updated by any means
    }
}