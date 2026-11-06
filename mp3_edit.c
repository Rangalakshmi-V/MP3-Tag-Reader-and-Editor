#include "mp3_header.h"
void edit(struct MP3 *mp3)
{
  //open the original file binary mode
  mp3->org_mp3_fptr=fopen(mp3->mp3_filename,"rb");

  if(mp3->org_mp3_fptr==NULL)
  {
    printf("unable to open the original mp3 file\n");
    return;
  }
  //create temp.mp3 in binary write mode
  mp3->dup_mp3_fptr=fopen("temp.mp3","wb");
  if(mp3->dup_mp3_fptr==NULL)
  {
    printf("Error: Unable to create temporary MP3 file\n");
    fclose(mp3->org_mp3_fptr);
    return;
  }
  printf("Original and temporary files opened successfully\n");

  char header[10];
  //read the 10 bytes of header from original file
  fread(header,1,10,mp3->org_mp3_fptr);

  //write the 10 bytes of header into temporary file
  fwrite(header,1,10,mp3->dup_mp3_fptr);
  printf("Header copied successfully\n");


  char *selected_id = option_to_frame(mp3->tag_option);
  //read 6 frames
  for(int i=0;i<6;i++)
  {
    char frame_id[5];
    //read 4 bytes of frame id
    fread(frame_id,1,4,mp3->org_mp3_fptr);

    frame_id[4]='\0';

    char size_bytes[4];

    // Read 4 bytes of frame size
    fread(size_bytes, 1, 4, mp3->org_mp3_fptr);

   int frame_size;

   // Copy size bytes into integer
   memcpy(&frame_size, size_bytes, 4);

   // Convert big endian to little endian
   toggle_endianess(&frame_size);
    //read the two bytes of flag
    char flags[2];
    fread(flags,1,2,mp3->org_mp3_fptr);

    if(strcmp(frame_id, selected_id) == 0)
   {
    printf("Selected tag found\n");

    // Calculate new frame size including encoding byte
    int new_size = strlen(mp3->new_content) + 1;

    // Write the selected frame ID into temporary file
    fwrite(frame_id, 1, 4, mp3->dup_mp3_fptr);

    // Convert new frame size from little endian to big endian
    int temp_size = new_size;
    toggle_endianess(&temp_size);

    // Write the new frame size into temporary file
    fwrite(&temp_size, 1, 4, mp3->dup_mp3_fptr);

    // Write the original two bytes of flags
    fwrite(flags, 1, 2, mp3->dup_mp3_fptr);

    // Set encoding byte to 0 (ISO-8859-1)
    char encoding = 0;

    // Write encoding byte into temporary file
    fwrite(&encoding, 1, 1, mp3->dup_mp3_fptr);

    // Write the new tag content into temporary file
    fwrite(mp3->new_content, 1, strlen(mp3->new_content), mp3->dup_mp3_fptr);

    // Skip the old frame content in original MP3 file
    fseek(mp3->org_mp3_fptr, frame_size, SEEK_CUR);
   }
   else
   {
    printf("Other tag found\n");
    // Copy frame ID
    fwrite(frame_id, 1, 4, mp3->dup_mp3_fptr);

    // Copy original frame size
    fwrite(size_bytes, 1, 4, mp3->dup_mp3_fptr);

    // Copy flags
    fwrite(flags, 1, 2, mp3->dup_mp3_fptr);

    // Copy original frame data
    for(int j = 0; j < frame_size; j++)
    {
        char ch;

        fread(&ch, 1, 1, mp3->org_mp3_fptr);

        fwrite(&ch, 1, 1, mp3->dup_mp3_fptr);
    }
   }
  }
    // Copy the remaining data from original MP3 to temporary MP3
   char ch;

   while(fread(&ch, 1, 1, mp3->org_mp3_fptr) > 0)
   {
    fwrite(&ch, 1, 1, mp3->dup_mp3_fptr);
   }

   printf("Remaining data copied successfully\n" );
   fclose(mp3->org_mp3_fptr);
   fclose(mp3->dup_mp3_fptr);

   printf("\n-------- Select Edit option --------\n");

  printf("\n-------- Select %s change option --------\n",
       option_to_name(mp3->tag_option));

  printf("\n%s : %s\n",
       option_to_name(mp3->tag_option),
       mp3->new_content);

   
   if(rename("temp.mp3", mp3->mp3_filename) == 0)
   {
    printf("\n-------- %s changed successfully --------\n",
           option_to_name(mp3->tag_option));
   }
else
  {
    printf("Error: Unable to rename temporary file\n");
}

}

