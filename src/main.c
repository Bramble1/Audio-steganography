#include "Functions.h"

int main(int argc, char **argv)
{
	
	struct binary_info AudioFile;
	struct binary_info efile;

	if(argc<2)
	{
		printf("./stegbot <i> <file.gpg> <audiofile.mp3>\n");
		printf("./stegbot <x> <audiofile.mp3>\n");
		printf("\ni=import\nx=export\n");
		exit(EXIT_FAILURE);
	} 

	if(strcmp(argv[1],"i")==0)
	{
		if(argc!=4)
		{
			printf("./stegbot <i> <textfile.gpg> <audiofile.mp3>\n");
			exit(EXIT_FAILURE);
		}

		/*map the soundfile and the gpg file into memory*/
		/*check to see if argv[2] contains .gpg file*/


		if(FileCheck(argv[2])==-1)
		{
			printf("[-]must be a .gpg encrypted file.\n");
			exit(EXIT_FAILURE);
		}else{
			map_binary(argv[2],&efile);
		
			map_binary(argv[3],&AudioFile);

			//lsb_basic_infection(argv[2],size,&binary);

			/*infect with gpg_file*/
			store_gpg_file(&efile,&AudioFile);

			store_file_length(&AudioFile,efile.binary_size);
		
			exit(EXIT_SUCCESS);
		}
	}
	else if(strcmp(argv[1],"x")==0)
	{
		if(argc!=3)
		{
			printf("./stegbot <x> <audiofile.mp3>\n");
			exit(EXIT_FAILURE);
		}

		

		map_binary(argv[2],&AudioFile);
	
		//char size = extract_message_length(&AudioFile);

		//extract_message_lsb(&binary,size);

		int size = extract_file_length(&AudioFile);

		extract_gpg_file(&AudioFile,size);

		exit(EXIT_SUCCESS);
	} 

	return 0;
}
