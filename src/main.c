#include "Functions.h"

int main(int argc, char **argv)
{
	
	struct binary_info binary;

	if(argc<2)
	{
		printf("./stegbot <i> <\"message\"> <audiofile.mp3>\n");
		printf("./stegbot <x> <audiofile.mp3>\n");
		printf("\ni=import\nx=export\n");
		exit(EXIT_FAILURE);
	} 

	if(strcmp(argv[1],"i")==0)
	{
		if(argc!=4)
		{
			printf("./stegbot <i> <\"message\"> <audiofile.mp3>\n");
			exit(EXIT_FAILURE);
		}

		char size = strlen(argv[2]);
		
		map_binary(argv[3],&binary);

		lsb_basic_infection(argv[2],size,&binary);

		store_message_length(&binary,size);
		
		exit(EXIT_SUCCESS);
	}
	else if(strcmp(argv[1],"x")==0)
	{
		if(argc!=3)
		{
			printf("./stegbot <x> <audiofile.mp3>\n");
			exit(EXIT_FAILURE);
		}

		

		map_binary(argv[2],&binary);
	
		char size = extract_message_length(&binary);

		extract_message_lsb(&binary,size);

		exit(EXIT_SUCCESS);
	} 

	return 0;
}
