
/**
 * @file main.c
 * @brief Main entry point for the MP3 Tag Reader application.
 */

#include <stdio.h>
#include <string.h>
#include "main.h"
#include "id3_reader.h"
#include "id3_writer.h"
#include "error_handling.h"

/**
 * @brief Displays the help message for the MP3 Tag Reader application.
 */
void display_help() {
    printf("__________________________________________________________\n\n");
    printf("Usage: ./a.out [options] filename\n");
    printf("Options:\n");
    printf("  -h                                   Display help\n");
    printf("  -v                                   View tags\n");
    printf("  -e -t/-T/-a/-A/-y/-c/-g <value>      Edit tags\n\n");
    printf("Commands for Edit : \n\n");
    printf("-t : Edit title           -T : Edit track\n-a : Edit artist          -A : Edit album\n-y : Edit year            -g : Edit genre\n\n");
    printf("__________________________________________________________\n\n");
}

/**
 * @brief Main function to handle command-line arguments and execute appropriate actions.
 * 
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return 0 on success, non-zero on failure.
 */
int main(int argc, char *argv[]) 
{
    if (argc < 2)
     {
        display_help();
        return 1;
    }

    if (strcmp(argv[1], "-h") == 0) 
    {
        display_help();
        return 0;
    } 
    else if (strcmp(argv[1], "-v") == 0 && argc == 3 && strstr(argv[2],".mp3")) 
    {
        FILE *fptr=fopen(argv[2],"rb");
        view_tags(argv[2]);
        fclose(fptr);
    }
    else if (strcmp(argv[1], "-e") == 0 && argc == 5 && strstr(argv[4],".mp3"))
    {
        char *tag = argv[2];
        char *filename = argv[4];
        char *value = argv[3];
        if (edit_tag(filename, tag, value) != 0)
        {
            display_error("Failed to edit tag.");
            return 1;
        }
        printf("%35s\n","Tag edited successfully.");
        printf("_____________________________________________________\n");
        printf("_____________________________________________________\n\n");
    }
    else 
    {
        if(strstr(argv[4],".mp3") || strstr(argv[2],".mp3")==0)
        printf("\nEnter an .mp3 file!!!\n\n");
        display_help();
        return 1;
    }

    return 0;
}
