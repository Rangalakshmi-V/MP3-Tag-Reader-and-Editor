#include "mp3_header.h"



void view(struct MP3 *mp3)
{
    //open the mp3 file in read mode
    mp3->org_mp3_fptr=fopen(mp3->mp3_filename,"rb");
    if(mp3->org_mp3_fptr==NULL)
    {
        printf("Unable to open mp3 file\n");
        return;
    }
    printf("mp3 file opened successfully\n");

    // Print heading
    printf("MP3 Tag Reader and Editor for ID3v2\n");
    printf("--------------------------------------------------\n");

    //skip the 10 byte header
    fseek(mp3->org_mp3_fptr,10,SEEK_SET);

    //loop 6 times to read 6 tag frame
    for(int i=0;i<6;i++)
    {
        char tag[5];  //first 4 position store tag id last stores the \0

        //read 4 byte frame ID
        fread(tag,1,4,mp3->org_mp3_fptr);
        tag[4]='\0';  //add null character at the end

        //read the 4bytes of frame size                          
        int frame_size;
        fread(&frame_size, 1, 4, mp3->org_mp3_fptr);   //frame_size is an integer variable.
                                                       //&frame_size gives its memory address.
                                                       //fread() needs the address where the data should be stored.
        // Convert Big Endian to Little Endian
         toggle_endianess(&frame_size);
    

    //skip 2 bytes from current position
    fseek(mp3->org_mp3_fptr,2,SEEK_CUR); //that is flag
    
    // Identify the tag name
    tag_to_name(tag);

    // Print the frame content
    print_tag_data(mp3->org_mp3_fptr, frame_size);
    }
    printf("--------------------------------------------------\n");

    fclose(mp3->org_mp3_fptr);

}

void print_tag_data(FILE *org_mp3_fptr,int frame_size)
{
    char content[frame_size+1];

    fread(content,1,frame_size,org_mp3_fptr);

    content[frame_size]='\0';

    printf("%s\n",content+1);

}
