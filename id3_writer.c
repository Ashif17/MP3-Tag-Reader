/**
 * @file id3_writer.c
 * @brief Implementation of functions for writing and editing ID3 tags in MP3 files.
 */

#include <stdio.h>
#include <string.h>
#include "id3_writer.h"
#include "id3_reader.h"
#include "id3_utils.h"

/**
 * @brief Writes the ID3 tags to an MP3 file.
 * 
 * @param filename The name of the MP3 file.
 * @param data Pointer to the TagData structure containing the ID3 tags.
 * @return 0 on success, non-zero on failure.
 */
int write_id3_tags(const char *filename, const TagData *data, const char *tag) 
{
    // Implementation for writing ID3 tags
    FILE *fptr=fopen(filename,"rb+");
    unsigned char main_header[10];
    fread(main_header,1,10,fptr);
    long int MetaData_size=(((main_header[6] & 0x7f)<<21)|((main_header[7] & 0x7f)<<14)|((main_header[8] & 0x7f)<<7)|(main_header[9] & 0x7f));
    int bytes_read=10;
    int version=main_header[3],frame_size=0;
    unsigned char frame_header[10];
    while(bytes_read<MetaData_size)
    {
        int i=0;
        i++;
        fseek(fptr,bytes_read,SEEK_SET);
        fread(frame_header,1,10,fptr);
        bytes_read=bytes_read+10;
        char frame_id[5];
        memcpy(frame_id,(char*)frame_header,4);
        frame_id[4]='\0';
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
    if(strcmp(tag,"-t")==0)
    {
        if(data->title && strcmp(frame_id,"TIT2")==0)
        {
            fseek(fptr,bytes_read+1,SEEK_SET);
            fwrite(data->title,1,frame_size-1,fptr);
            break;
        }
        else
        {
            bytes_read=bytes_read+frame_size;
        }
    }
    else if(strcmp(tag,"-T")==0)
    {
        if(data->track && strcmp(frame_id,"TRCK")==0)
        {
            fseek(fptr,bytes_read+1,SEEK_SET);
            fwrite(data->track,1,frame_size-1,fptr);
            break;
        }
        else
        {
            bytes_read=bytes_read+frame_size;
        }
    }
    else if(strcmp(tag,"-a")==0)
    {
        if(data->artist && strcmp(frame_id,"TPE1")==0)
        {
            fseek(fptr,bytes_read+1,SEEK_SET);
            fwrite(data->artist,1,frame_size-1,fptr);
            break;
        }
        else
        {
            bytes_read=bytes_read+frame_size;
        }
    }
     else if(strcmp(tag,"-A")==0)
    {
        if(data->album && strcmp(frame_id,"TALB")==0)
        {
            fseek(fptr,bytes_read+1,SEEK_SET);
            fwrite(data->album,1,frame_size-1,fptr);
            break;
        }
        else
        {
            bytes_read=bytes_read+frame_size;
        }
    }
     else if(strcmp(tag,"-y")==0)
    {
        if(data->year && (strcmp(frame_id,"TDRC")==0 || strcmp(frame_id,"TYER")==0))
        {
            fseek(fptr,bytes_read+1,SEEK_SET);
            fwrite(data->year,1,frame_size-1,fptr);
            break;
        }
        else
        {
            bytes_read=bytes_read+frame_size;
        }
    }
     else if(strcmp(tag,"-c")==0)
    {
        if(data->comment && strcmp(frame_id,"COMM")==0)
        {
            fseek(fptr,bytes_read+1,SEEK_SET);
            fwrite(data->comment,1,frame_size-1,fptr);
            break;
        }
        else
        {
            bytes_read=bytes_read+frame_size;
        }
    }
    else if(strcmp(tag,"-g")==0)
    {
        if(data->genre && strcmp(frame_id,"TCON")==0)
        {
            fseek(fptr,bytes_read+1,SEEK_SET);
            fwrite(data->genre,1,frame_size-1,fptr);
            break;
        }
        else
        {
            bytes_read=bytes_read+frame_size;
        }
    }
    }
    display_metadata(data);
    fclose(fptr);
    return 0;
}

/** TODO: Add documentation as sample given above */
int edit_tag(const char *filename, const char *tag, const char *value) 
{
    TagData *data = read_id3_tags(filename);
    if (!data) {
        return 1;
    }
    // Implementation for writing ID3 tags to file
    if(strcmp(tag,"-t")==0)
    {
        if(data->title)
        {
            int size=strlen(value);
            strncpy(data->title,value,size);
             for(int i=size;i<8;i++)
            {
                 data->title[i]='\0';
            }
            write_id3_tags(filename,data,tag);
        }
        else
        {
            printf("Tag not found\n");
            return 1;
        }
    }
    else if(strcmp(tag,"-T")==0)
    {
         if(data->track)
        {
            int size=strlen(value);
            strncpy(data->track,value,size);
             for(int i=size;i<frame_size-1;i++)
            {
                 data->track[i]='\0';
            }
            write_id3_tags(filename,data,tag);
        }
        else
        {
            printf("Tag not found\n");
            return 1;
        }
    }
     else if(strcmp(tag,"-a")==0)
    {
        if(data->artist)
        {
            int size=strlen(value);
            strncpy(data->artist,value,size);
             for(int i=size;i<8;i++)
            {
                 data->artist[i]='\0';
            }
            write_id3_tags(filename,data,tag);
        }
        else
        {
            printf("Tag not found\n");
            return 1;
        }
    }
     else if(strcmp(tag,"-A")==0)
    {
         if(data->album)
        {
            int size=strlen(value);
            strncpy(data->album,value,size);
             for(int i=size;i<8;i++)
            {
                 data->album[i]='\0';
            }
            write_id3_tags(filename,data,tag);
        }
        else
        {
            printf("Tag not found\n");
            return 1;
        }
    }
     else if(strcmp(tag,"-y")==0)
    {
         if(data->year)
        {
            int size=strlen(value);
            strncpy(data->year,value,size);
            for(int i=size;i<8;i++)
            {
                 data->year[i]='\0';
            }
            write_id3_tags(filename,data,tag);
        }
        else
        {
            printf("Tag not found\n");
            return 1;
        }
    }
     else if(strcmp(tag,"-c")==0)
    {
         if(data->comment)
        {
            int size=strlen(value);
            strncpy(data->comment,value,size);
             for(int i=size;i<8;i++)
            {
                 data->comment[i]='\0';
            }
            write_id3_tags(filename,data,tag);
        }
        else
        {
            printf("Tag not found\n");
            return 1;
        }
    }
     else if(strcmp(tag,"-g")==0)
    {
         if(data->genre)
        {
            int size=strlen(value);
            strncpy(data->genre,value,size);
             for(int i=size;i<8;i++)
            {
                 data->genre[i]='\0';
            }
            write_id3_tags(filename,data,tag);
        }
        else
        {
            printf("Tag not found\n");
            return 1;
        }
    }
    /* else if(strcmp(tag,"-T")==0)
    {
         if(data->title)
        {
            data->title=value;
            write_id3_tags(filename,data);
        }
        else
        {
            return 0;
        }
    }
     else if(strcmp(tag,"-T")==0)
    {
         if(data->title)
        {
            data->title=value;
            write_id3_tags(filename,data);
        }
        else
        {
            return 0;
        }
    }
     else if(strcmp(tag,"-T")==0)
    {
         if(data->title)
        {
            data->title=value;
            write_id3_tags(filename,data);
        }
        else
        {
            return 0;
        }
    }*/
}
