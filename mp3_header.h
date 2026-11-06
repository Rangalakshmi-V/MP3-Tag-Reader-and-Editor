#ifndef MP3_HEADER_H
#define MP3_HEADER_H

#include <stdio.h>
#include <string.h>


#define VIEW 	1
#define EDIT 	2
#define HELP    3


struct MP3
{
    char *mp3_filename;
    FILE *org_mp3_fptr;
    FILE *dup_mp3_fptr;
    char *tag_option;
    char *new_content;
};

int validate_cla(int argc, char *argv[], struct MP3 *mp3);
void view(struct MP3 *mp3);
void edit(struct MP3 *mp3);
void toggle_endianess(int *size);
void print_tag_data(FILE * org_mp3_fptr,int frame_size);
void tag_to_name(char *);
char *option_to_frame(char *option);
char *option_to_name(char *option);

#endif
