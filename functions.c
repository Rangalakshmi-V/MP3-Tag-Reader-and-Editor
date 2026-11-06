#include "mp3_header.h"

int validate_cla(int argc, char *argv[], struct MP3 *mp3)
{
    if( argc == 1 )
    {
	printf("------------------------------------------------------------------------------\n");
	printf("ERROR: ./a.out : INVALID ARGUMENTS\n");
	printf("USAGE : To view please pass like: ./a.out -v mp3filename\n");
	printf("To edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename\n");
	printf("To get help pass like : ./a.out --help\n");
	printf("------------------------------------------------------------------------------\n");
	return 0;
    }

    if( (strcmp(argv[1], "--help") == 0) )
    {
	printf("------------------------------->HELP<-----------------------------------------\n");
	printf("1. -v -> to view mp3 file contents\n");
	printf("2. -e -> to edit mp3 file contents\n");
	printf("\t\t2.1. -t -> to edit song title\n");
	printf("\t\t2.2. -a -> to edit artist name\n");
	printf("\t\t2.3. -A -> to edit album name\n");
	printf("\t\t2.4. -y -> to edit year\n");
	printf("\t\t2.5. -m -> to edit content\n");
	printf("\t\t2.6. -c -> to edit comment\n");
	printf("------------------------------------------------------------------------------\n");
	return 0; 
    }
//check for view operartion

    if(!strcmp(argv[1], "-v"))
    {
	// Do the necessary validation
	if(argc==3)
	{
	mp3->mp3_filename=argv[2];
	return VIEW;
	}
	else
	{
		printf("Error : invalid argument for view\n");
		return 0;

	}
}
//check for edit operation
    if(!strcmp(argv[1], "-e"))
    {
	// Do the necessary validation
	if(argc==5)
	{
		if(!strcmp(argv[2], "-a") ||
           !strcmp(argv[2], "-A") ||
           !strcmp(argv[2], "-t") ||
           !strcmp(argv[2], "-y") ||
           !strcmp(argv[2], "-c") ||
           !strcmp(argv[2], "-C"))
        {
            mp3->tag_option = argv[2];
            mp3->new_content = argv[3];
            mp3->mp3_filename = argv[4];
			return EDIT;
		}
		else
		{
          printf("Error : invalid tag option\n");
		  return 0;
		}
	}
	else
	{
      printf("Error: Invalid arguments for edit\n");
       return 0; 
	}
   
}
}
void toggle_endianess(int *size)
{
	char *ptr = (char*) size;
	char temp;
	
	for(int i=0;i<sizeof(int)/2;i++)
	{
		temp=ptr[i];
		ptr[i]=ptr[sizeof(int)-1-i];
		ptr[sizeof(int)-1-i]=temp;
	}

}

void tag_to_name(char *tag)
{
    if(strcmp(tag, "TIT2") == 0)
        printf("Title\t\t:");

    else if(strcmp(tag, "TPE1") == 0)
        printf("Artist\t\t:");

    else if(strcmp(tag, "TALB") == 0)
        printf("Album\t\t:");

    else if(strcmp(tag, "TYER") == 0)
        printf("Year\t\t:");

    else if(strcmp(tag, "TCON") == 0)
        printf("Genre\t\t:");

    else if(strcmp(tag, "COMM") == 0)
        printf("Comment\t\t:");
}

char *option_to_frame(char *option)
{
    if(strcmp(option, "-t") == 0)
        return "TIT2";

    else if(strcmp(option, "-a") == 0)
        return "TPE1";

    else if(strcmp(option, "-A") == 0)
        return "TALB";

    else if(strcmp(option, "-y") == 0)
        return "TYER";

    else if(strcmp(option, "-m") == 0)
        return "TCON";

    else if(strcmp(option, "-c") == 0)
        return "COMM";

    return NULL;
}

char *option_to_name(char *option)
{
    if(strcmp(option, "-t") == 0)
        return "Title";

    else if(strcmp(option, "-a") == 0)
        return "Artist";

    else if(strcmp(option, "-A") == 0)
        return "Album";

    else if(strcmp(option, "-y") == 0)
        return "Year";

    else if(strcmp(option, "-m") == 0)
        return "Genre";

    else if(strcmp(option, "-c") == 0)
        return "Comment";

    return "Unknown";
}

