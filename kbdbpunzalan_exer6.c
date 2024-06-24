#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct song_tag
{
    char title[20];
    char artist[20];
    char album[20];
    struct song_tag *nextSong;
} song;

typedef struct playlist_tag
{
    char name[50];
    int songCount;
    song *songHead;
    struct playlist_tag *next;
} playlist;

// user Prompts
void noPlaylistPrompt();
void availablePlaylist(playlist *, int, int *);

// user input 
void addPlaylist(int *, playlist **); // choice 1
void addSong(playlist **, int, int); // choice 2
void removeSong(playlist *, int, int); // choice 3
void viewPlaylist(playlist *, int, int); // choice 4
void viewAll(playlist *); // choice 5

// before terminating the program
void deleteAll(playlist **);

// file Implementation
void loadFile(playlist**, int*);
void saveFile(playlist*, int);

int main()
{
    int user_input = 0, playlist_count = 0, index;
    char temp;

    playlist *playlist_head = NULL; // will serve as the start of the linked list.

    loadFile(&playlist_head, &playlist_count); // loads saved file, if any.

    while (1)
    {
        // user choices
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

        if (user_input == 1) // add playlist -> no prompts yet
            addPlaylist(&playlist_count, &playlist_head); // function which updates the values of playlist_count and playlist_head

        else if (user_input == 2) // add song to the chosen playlist
        {
            if (playlist_count == 0) // there are no playlist yet to add songs to
                noPlaylistPrompt();
            else // user may now add a song
            {
                availablePlaylist(playlist_head, playlist_count, &index); // user will be asked what playlist to add song to
                addSong(&playlist_head, index, playlist_count);
            }
        }

        else if (user_input == 3) // remove a song
        {
            if (playlist_count == 0) // there are no playlist yet to remove songs from
                noPlaylistPrompt();
            else
            {
                availablePlaylist(playlist_head, playlist_count, &index); // user will be asked what playlist to remove song from
                removeSong(playlist_head, index, playlist_count);
            }
        }

        else if (user_input == 4) // view a playlist
        {
            if (playlist_count == 0)  // there are no playlist yet
                noPlaylistPrompt();
            else
            {
                availablePlaylist(playlist_head, playlist_count, &index); // user will be asked what playlist to view
                viewPlaylist(playlist_head, index, playlist_count);
            }
        }

        else if (user_input == 5) // view all playlists
        {
            if (playlist_count == 0) // there are no playlist yet
                noPlaylistPrompt();
            else
                viewAll(playlist_head); // view all playlists
        }

        else if (user_input == 6) // exit
        {
            saveFile(playlist_head, playlist_count); // save first before exiting
            deleteAll(&playlist_head); // all contents of playlisyt head will be deleted
            break;
        }

        else
            printf("Invalid choice!\n");
    }
}

// just a user prompt if playlist_count == 0
void noPlaylistPrompt()
{
    printf("You don't have any playlist yet!\n");
    printf("Add one first.\n");
}

// available playlisys to choose from
void availablePlaylist(playlist *playlist_head, int playlist_count, int *index)
{
    printf("THE PLAYLISTS AVAILABLE ARE:\n");
    int x = 0;
    for (playlist *h = playlist_head; h != NULL; h = h->next) // iterate over the linked list
    {
        printf("[%d] %s\n", x, h->name);
        x++;
    }

    printf("\nEnter playlist number: ");
    scanf("%d", index); // index will be updated
    printf("\n");
}

// add playlist
void addPlaylist(int *playlist_count, playlist **playlist_head)
{
    char playlist_temp;

    playlist *new = (playlist *)malloc(sizeof(playlist)); // new instance of playlist structure
    playlist *temp = (*playlist_head);

    printf("Enter playlist name: ");
    scanf("%c", &playlist_temp); // temp statement to clear buffer
    scanf("%[^\n]", new->name); // access the member 'name' in the structure

    while (temp != NULL) // while we are not at the end of the linked list
    {
        if (strcasecmp(temp->name, new->name) == 0) // compare the name of the current instance to the name of the 'new' structure (case sensitive)
        {
            printf("\nPlaylist %s is already in your records!\n", new->name);
            break;
        }

        else
            temp = temp->next; // update temp
    }

    if (temp == NULL) // temp is already at the end of the linked list, and there are no same playlist name
    {
        if ((*playlist_head) == NULL || ((*playlist_head) != NULL && strcasecmp((*playlist_head)->name, new->name) > 0))
        { // add at head
            new->next = (*playlist_head);
            (*playlist_head) = new;
        }

        else
        { // add at middle or at tail
            temp = (*playlist_head);
            while (temp->next != NULL && strcmp(temp->next->name, new->name) < 0) // traverse up until the condition
            {
                temp = temp->next;
            }

            new->next = temp->next;
            temp->next = new;
        }

        printf("\n%s is successfully added to your records.\n", new->name);

        new->songCount = 0; // set the songCount of that playlist to 0
        new->songHead = NULL; // we set it to NULL so that we will encounter no problems later on

        // free dynamic allocation
        new = NULL;
        free(new);

        (*playlist_count)++; // update playlist_count
        
    }
}

// add songs to current playlist
void addSong(playlist **playlist_head, int index, int playlist_count)
{
    char buffer;

    playlist *access = (*playlist_head); // needed for accessing the desired instance to add song to
    song *new_song = (song *)malloc(sizeof(song)); // create instance of the 'song' structure

    if (index >= playlist_count || index < 0) // accessing an invalid playlist index
        printf("Invalid input!\n");
    else
    {
        for (int i = 0; i < index; i++) // traverse until we are accessing the desired playlist to add song to
            access = access->next;

        scanf("%c", &buffer); // temp statement to clear buffer
        printf("Enter song title: ");
        scanf("%[^\n]", new_song->title); // user input will be scanfed to the song title

        song *temp = access->songHead;
        while (temp != NULL)
        {
            if (strcasecmp(temp->title, new_song->title) == 0)
            {
                printf("\nSong title %s is already in %s!\n", new_song->title, access->name);
                break;
            }

            else
                temp = temp->nextSong;
        }

        if (temp == NULL) // temp is already at the end of the linked list, and there are no same song name in the playlist
        {
            // we will just proceed scanf-ing the song artist and album
                // if we are already sure that there are no song title duplicates
            scanf("%c", &buffer); // temp statement to clear buffer
            printf("Enter song artist: ");
            scanf("%[^\n]", new_song->artist);

            scanf("%c", &buffer); // temp statement to clear buffer
            printf("Enter song album: ");
            scanf("%[^\n]", new_song->album);

            if (access->songHead == NULL || (access->songHead != NULL && strcasecmp(access->songHead->title, new_song->title) > 0))
            { // add at head
                new_song->nextSong = access->songHead;
                access->songHead = new_song;
            }

            else
            { // add at middle or at tail
                temp = access->songHead;
                while (temp->nextSong != NULL && strcmp(temp->nextSong->title, new_song->title) < 0)
                { // traverse until the condition
                    temp = temp->nextSong;
                }

                new_song->nextSong = temp->nextSong; 
                temp->nextSong = new_song;
            }

            printf("\n%s is successfully added to your records.\n", new_song->title);
            access->songCount++; // the number of songs in this playlist will be updated
        }
    }

    // free dynamic allocation
    new_song = NULL;
    free(new_song);
}

// will serve as the inner loop of viewAll function and the loop of viewPlaylist
void printSongs(playlist *playlist_name)
{
    printf("\nPLAYLIST: %s\n", playlist_name->name);
    printf("SONG COUNT: %d\n", playlist_name->songCount);

    // loop through all songs in the desired playlist for viewPlaylist
        // or current playlist in viewAll
    for (song *j = playlist_name->songHead; j != NULL; j = j->nextSong)
    {
        printf("   SONG TITLE: %s\n", j->title);
        printf("   SONG ARTIST: %s\n", j->artist);
        printf("   SONG ALBUM: %s\n\n", j->album);
    }
}

// view all playlists
void viewAll(playlist *playlist_head)
{
    for (playlist *i = playlist_head; i != NULL; i = i->next) // iterate over all playlist
    {
        printSongs(i); // the previous function
    }
    printf("\n");
}

// view desired playlist
void viewPlaylist(playlist *playlist_head, int index, int playlist_count)
{
    if (index >= playlist_count || index < 0) 
        printf("Invalid input!\n");
    else
    {
        playlist *access = playlist_head;
        for (int i = 0; i < index; i++) // loop through the linked list for the desired playlist to view
            access = access->next;

        printSongs(access); 
    }
}

// remove song from a playlist
void removeSong(playlist *playlist_head, int index, int playlist_count)
{
    playlist *access = playlist_head;

    if (index >= playlist_count || index < 0) // invalid "index"
        printf("Invalid input!\n");
    else
    {
        for (int i = 0; i < index; i++)
            access = access->next;

        if (access->songCount == 0)
            printf("There are no songs to delete in this playlist!\n");

        else
        {
            char song_title[20], song_artist[20], buffer;

            // song title and artist will be inputted by the user --> find title and artist to delete a song
            scanf("%c", &buffer); // temp statement to clear buffer
            printf("Enter song title: ");
            scanf("%[^\n]", song_title); // 

            scanf("%c", &buffer); // temp statement to clear buffer
            printf("Enter song artist: ");
            scanf("%[^\n]", song_artist);

            song *del = access->songHead; // the instance that "del" holds will be removed.
           
            while (del != NULL)
            {
                if (strcasecmp(del->title, song_title) == 0 & strcasecmp(del->artist, song_artist) == 0)
                    // same artist and title as the one inputted by the user
                    break;
                del = del->nextSong;
            }

            if (del == NULL) // already looped through the linked list and title and artist inputted by the user cannot be found
                printf("\nWe couldn't find %s in this playlist.\n", song_title);
            else
            {
                if (del == access->songHead)
                { // delete at head
                    access->songHead = del->nextSong;
                    free(del);
                }

                else
                { // delete at middle or at tail
                    song *temp = access->songHead;

                    while (temp->nextSong != del)
                        temp = temp->nextSong;

                    temp->nextSong = del->nextSong;
                    free(del);

                }

                printf("\nSong is successfully deleted!\n");
                access->songCount--; // decrement number of songs in this playlist since we deleted one.
            }
        }
    }
}

// file implementation -> save file
void saveFile(playlist *playlist_head, int playlist_count)
{
    FILE *fp = fopen("songs.txt", "w"); // writing to a file

    fprintf(fp, "%d\n", playlist_count); // first prints the playlist_count to the file
                                            // 0 if linked list is empty

    if (playlist_count == 0) printf("There are no data to be saved.\n");
    else
    {
        for (playlist *i = playlist_head; i != NULL; i = i->next)
        {   
            fprintf(fp, "%s\n", i->name);
            fprintf(fp, "%d\n", i->songCount);
            for (song *j = i->songHead; j != NULL; j = j->nextSong)
            {
                fprintf(fp, "%s\n", j->title);
                fprintf(fp, "%s\n", j->artist);
                fprintf(fp, "%s\n", j->album);
            }
        }

        // print playlist before printing all songs of that playlist (if any)
            // print yet another playlist (if any) before printing all songs of that playlist (if any)

        printf("Successfully saved data.\n");
    }

    fclose(fp);
}

// file implementation -> load file
void loadFile(playlist **playlist_head, int *playlist_count)
{
    FILE *fp = fopen("songs.txt", "r"); // open for reading

    if (fp == NULL) printf("File was not opened!\n"); // no file in the same directory as the C file
    else
    {   
        fscanf(fp, "%d\n", playlist_count); // playlist count will be loaded first (value will be updated)

        if (*playlist_count == 0) printf("There are no data to be loaded.\n");
        else
        {
            // create instance/s of the playlist structure until the number of playlists (add at head)
                // so that all members can be accessed
            for (int i = 0; i < (*playlist_count); i++)
            {
                playlist *new = (playlist *)malloc(sizeof(playlist));
                new->next = (*playlist_head);
                (*playlist_head) = new;

                new = NULL;
                free(new);
            }

            // accessing and updating the ith instance of the structure
            for (playlist *i = *playlist_head; i != NULL; i = i->next)
            {   
                fscanf(fp, "%[^\n]\n", i->name);
                fscanf(fp, "%d\n", &i->songCount);

                // create instance/s of the song structure per playlist structure until the number of songs (add at head)
                    // so that all members can be accessed
                for (int j = 0; j < i->songCount; j++)
                {
                    song *new_song = (song *)malloc(sizeof(song));
                    new_song->nextSong = i->songHead;
                    i->songHead = new_song;

                    new_song = NULL;
                    free(new_song);
                }

                // accessing and updating the ith instance of the structure
                for (song *j = i->songHead; j != NULL; j = j->nextSong)
                {
                    fscanf(fp, "%[^\n]\n", j->title);
                    fscanf(fp, "%[^\n]\n", j->artist);
                    fscanf(fp, "%[^\n]\n", j->album);
                }
            }

            printf("Successfully loaded data.\n");
        }

        fclose(fp);
    }
}

// delete all instances of the strucutre (before exiting the program)
void deleteAll(playlist **playlist_head)
{
    while ((*playlist_head) != NULL)
    {
        playlist *temp = (*playlist_head);
        (*playlist_head) = (*playlist_head)->next;
        free(temp);
    }
}