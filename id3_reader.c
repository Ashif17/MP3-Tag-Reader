/**
 * @file id3_reader.c
 * @brief Implementation of functions for reading ID3 tags from MP3 files.
 */

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "id3_reader.h"
#include "error_handling.h"
#include"main.h"

/**
TODO: Add documention as sample given
 */
TagData* read_id3_tags(const char *filename) 
{
    // Implementation for reading ID3 tags
    FILE *fptr=fopen(filename,"rb");
    int choice;
    TagData *data = create_tag_data();
    //To check how much bytes reader
    int bytes_read=0;
    unsigned char main_header[10];
    if(fptr)
    {
        if(fread(main_header,1,10,fptr)==10)
        {
            if(strncmp((char*)main_header,"ID3",3)==0)
            {
                choice=2;
            }
            else if(strncmp((char*)main_header,"TAG",3)==0)
            {
                choice=1;
            }
            else
            {
                fclose(fptr);
                return 0;
            }
        }
        else
        {
            fclose(fptr);
            return 0;
        }
    }
    else
    {
        printf("\n\nFailed to open file so ");
        return 0;
    }
    
    //To extract the size of the meta data (convert from synchsafe integer)
    //we need to add each bit after leftshif to get the exact size
    long int MetaData_size=(((main_header[6] & 0x7f)<<21)|((main_header[7] & 0x7f)<<14)|((main_header[8] & 0x7f)<<7)|(main_header[9] & 0x7f));
    //printf("**%ld**\n",MetaData_size);       
    //switch case to choose  ID3V1 or 1D3V2

    switch(choice)
    {
        case 1:
        {
            //To extract all the tags from ID3v1
        }
        case 2:
        {
            //Read the version and store it in the version variable created inside datatype TagData
            data->version=malloc(1);
            sprintf(data->version, "ID3v2.%d.%d", main_header[3], main_header[4]);
            int version=main_header[3],frame_size=0;
            unsigned char frame_header[10];
            while(bytes_read<MetaData_size)
            {
             //Read 10 bytes - frame header of 1st TAG
                fread(frame_header,1,10,fptr);
                bytes_read=bytes_read+10;
                char frame_id[5];
                memcpy(frame_id,(char*)frame_header,4);
                frame_id[4]='\0';
                if(frame_id[1]==0 && frame_id[2]==0 && frame_id[3]==0 && frame_id[4]==0)
                {
                    break;
                }
                if (version == 3) 
                {
                    frame_size = (frame_header[4] << 24) |
                    (frame_header[5] << 16) |
                    (frame_header[6] << 8)  |
                    frame_header[7];
                }  
                else if (version == 4) 
                {
                    frame_size = ((frame_header[4] & 0x7F) << 21) |
                    ((frame_header[5] & 0x7F) << 14) |
                    ((frame_header[6] & 0x7F) << 7)  |
                    (frame_header[7] & 0x7F);
                }
               // printf("**/%d/**\n",frame_size);

                    unsigned char *frame_data = malloc(frame_size + 1);
                    fread(frame_data, 1, frame_size, fptr);
                    frame_data[frame_size] = '\0';

                    if(strcmp(frame_id,"TIT2")==0)
                    {
                        data->title=malloc(frame_size+1);
                        strncpy(data->title,frame_data+1,frame_size-1);
                        data->title[frame_size-1]='\0';
                    }
                    else if(strcmp(frame_id,"TPE1")==0)
                    {
                        data->artist=malloc(frame_size+1);
                        strncpy(data->artist,frame_data+1,frame_size-1);
                        data->artist[frame_size-1]='\0';
                    }
                    else if(strcmp(frame_id,"TALB")==0)
                    {
                        data->album=malloc(frame_size+1);
                        strncpy(data->album,(char*)frame_data+1,frame_size-1);
                        data->album[frame_size-1]='\0';
                    }
                    else if(strcmp(frame_id,"TYER")==0 || strcmp(frame_id,"TDRC")==0)
                    {
                        data->year=malloc(frame_size+1);
                        strncpy(data->year,frame_data+1,frame_size-1);
                        data->year[frame_size-1]='\0';
                    }
                    else if(strcmp(frame_id,"TCON")==0)
                    {
                        data->genre=malloc(frame_size+1);
                        strncpy(data->genre,frame_data+1,frame_size-1);
                        data->genre[frame_size-1]='\0';
                    }
                    else if(strcmp(frame_id,"COMM")==0)
                    {
                        data->comment=malloc(frame_size+1);
                        strncpy(data->comment,frame_data+1,frame_size-1);
                        data->comment[frame_size-1]='\0';
                    }
                    else if(strcmp(frame_id,"TRCK")==0)
                    {
                        data->track=malloc(frame_size+1);
                        strncpy(data->track,frame_data+1,frame_size-1);
                        data->track[frame_size-1]='\0';
                    }
                    else if(strcmp(frame_id,"APIC")==0)
                    {
                        int point=0;
                        point++; //skip encoding bit
                        while(point<frame_size && frame_data[point]!=0)
                        {
                            point++; //skip mime
                        }
                        point++; //skip null character
                        point++; //skip picture byte
                        while(point<frame_size && frame_data[point]!=0)
                        {
                            point++; //skip discrition string
                        }
                        point++; //skip null character

                        data->picture=malloc(point);
                        strncpy(data->picture,frame_data+1,point-1);
                        data->picture[point-1]='\0';
                        FILE *pic=fopen("pic.jpg","wb");
                        fwrite(frame_data+point,1,frame_size-point,pic);
                        fclose(pic);
                    }
                    free(frame_data);
            
                bytes_read=bytes_read+frame_size;
               // printf("//*%d*//\n",bytes_read);
            }
            return data;
            break;
        }
        fclose(fptr);
    }
}

/**
TODO: Add documention as sample given
 */
void display_metadata(const TagData *data) 
{
    // Implementation for displaying metadata
    printf("\n%30s\n","SONG DETAILS : ");
    printf("_____________________________________________________\n\n");
    printf("%-10s: %s\n","Version ",data->version);
    if(data->title)
    printf("%-10s: %s\n","Title ",data->title);
    if(data->track)
    printf("%-10s: %s\n","Track ",data->track);
    if(data->artist)
    printf("%-10s: %s\n","Artist ",data->artist);
    if(data->album)
    printf("%-10s: %s\n","Album ",data->album);
    if(data->year)
    printf("%-10s: %s\n","Year ",data->year);
    if(data->comment)
    printf("%-10s: %s\n","Comments ",data->comment);
    if(data->genre)
    printf("%-10s: %s\n","Genre ",data->genre);
    printf("_____________________________________________________\n"); 
    printf("_____________________________________________________\n\n");
    //if(data->picture)
    //printf("Image : %s\n",data->picture);
}

/**
TODO: Add documention as sample given
 */
void view_tags(const char *filename) 
{
    TagData *data = read_id3_tags(filename);
    if (!data) {
        display_error("Failed to read ID3 tags.");
        display_help();
        return;
    }
    display_metadata(data);
    free_tag_data(data);
}
