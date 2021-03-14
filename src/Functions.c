#include "Functions.h"

/*Open the audiofile into memory*/
void map_binary(char *binary_name,struct binary_info *binary)
{
	/*open the file and map into memory*/

	int fd;
	if((fd=open(binary_name,O_RDWR))<0)
	{
		perror("[-]binary opened ");
		exit(EXIT_FAILURE);
	}
	else
		perror("[+]binary opened ");

	struct stat st;
	if((fstat(fd,&st))<0)
	{
		perror("[-]obtain file size ");
		exit(EXIT_FAILURE);
	}
	else{
		perror("[+]obtain file size ");
		binary->binary_size=st.st_size;
	}
	
	binary->mem_offset = mmap(NULL,st.st_size,PROT_READ|PROT_WRITE|PROT_EXEC,MAP_SHARED,fd,0);
	if(binary->mem_offset==MAP_FAILED)
	{
		perror("[-]map binary into memory ");
		exit(EXIT_FAILURE);
	}else
	{
		perror("[+]map binary into memory ");
	}

	printf("\nbinary (%d bytes) mapped into memory\n",binary->binary_size);

	
}


/*store encrypted gpg file*/
void store_gpg_file(struct binary_info *efile,struct binary_info *sound_file)
{
	int no_bytes = efile->binary_size;
	char on='1'; char off='0';
	char msg_bit; char audio_lsb;
	int pos = 0;

	/*bytes required*/
	int soundfile_bytes_required = (no_bytes * 8);

	/*check against soundfile to see if it's small enough*/
	if(soundfile_bytes_required > sound_file->binary_size)
	{
		printf("[-]encrypted file is to large");
		exit(EXIT_FAILURE);
	}
	
	/*if it's small enough then memcpy the entire file from offset of audiofile of size gfile*/
	for(int i=0;i<no_bytes;i++)
	{
		for(int y=7;y>=0;y--)
		{
			msg_bit = (efile->mem_offset[i] & 1<<y) ? on : off;
			audio_lsb = (sound_file->mem_offset[pos] & 1<<0) ? on : off;

			if(msg_bit != audio_lsb)
			{
				sound_file->mem_offset[pos] ^= 1<<0; pos+=1;
			}
			else
			{
				pos+=1;
			}
		}
	}

	printf("[+]Infect audio file: success\n");
}

void extract_gpg_file(struct binary_info *binary,int file_size)
{
	int no_bytes = file_size;
	char on='1'; char off='0';
	char msg_bit; char soundfile_lsb;
	char message[no_bytes];
	int pos=0; int bit_pos=7;
	int soundfile_byte_limit = no_bytes * 8;

	for(int i=0;i<soundfile_byte_limit;i++)
	{
		soundfile_lsb = (binary->mem_offset[i] & 1<<0) ? on : off;
		msg_bit = (message[pos] & 1<<bit_pos) ? on : off;

		if(soundfile_lsb != msg_bit)
		{
			message[pos] ^= 1<<bit_pos; bit_pos--;
		}
		else
		{
			bit_pos--;
		}

		if(((i+1)%8)==0)
		{
			bit_pos=7; pos++;
		}
	}
	 message[no_bytes]='\0';//may change

	/*store into file with .gpg extension*/
	FILE *fd = fopen("extracted.gpg","w+");

	fwrite(message,no_bytes,1,fd);

	fclose(fd);
	//printf("%s",message);
}

void store_file_length(struct binary_info *Audio_file,int size)
{
	char on='1'; char off='0';
	int position = Audio_file->binary_size - (4*8); int counter = 0;
	char bit; char binary_lsb;
	int ef_size = size;
	int number = 0;
	
	/*4 bytes = 4 * 7 = 28 >=0 thus essentially 4 * 8*/
	for(int y=28;y>=0;y--)
	{
		bit = (ef_size & 1<<y) ? on : off;
		binary_lsb = (Audio_file->mem_offset[position] & 1<<0) ? on : off;

		if(binary_lsb != bit)
		{
			Audio_file->mem_offset[position] ^= 1<<0; position++;
		}
		else
			position++;
	}



}

int extract_file_length(struct binary_info *Audio_file)
{
	char on='1'; char off='0';
	int position = Audio_file->binary_size - (4*8); int counter = 0;
	char bit; char binary_lsb;
	int result = 0;

	for(int y=28;y>=0;y--)
	{
		bit = (result & 1<<y) ? on : off;
		binary_lsb = (Audio_file->mem_offset[position] & 1<<0) ? on : off;

		if(bit != binary_lsb)
		{
			result ^= 1<<y; position++;
		}
		else
			position++;
	}

	return result;
}

void store_message_length(struct binary_info *binary,char length)
{
	/*always store at the end of the binary*/
	char on = '1'; char off='0';
	int position = binary->binary_size - 15; int counter = 0;
	char bit; char binary_lsb;
	char size = length;
	char number=0;


	position = binary->binary_size - 15;
	/*now changing the bits against the number's bits*/
	for(int y=7;y>=0;y--)
	{
		bit = (size & 1<<y) ? on : off;
		binary_lsb = (binary->mem_offset[position] & 1<<0) ? on : off;

		if(binary_lsb!=bit)
		{
			binary->mem_offset[position] ^= 1<<0;
			position++;
		}
		else
			position++;
	}

	
}

char extract_message_length(struct binary_info *binary)
{
	char on = '1'; char off='0';
	int position = binary->binary_size - 15;
	char bit; char binary_lsb;
	

	char result = 0;
	//iterate through
	for(int y=7;y>=0;y--)
	{
		bit = (result & 1<<y) ? on : off;
		binary_lsb = (binary->mem_offset[position] & 1<<0) ? on : off;

		if(binary_lsb!=bit)
		{
			result ^= 1<<y;
			position++;
		}
		else
			position++;
	}

//	printf("char result in extract_func() = %d\n",result);
	return result;
}

/*very basic infection by replacing each least significant bit of each byte of audio with out secret message*/
void lsb_basic_infection(char *message,int message_length,struct binary_info *binary)
{
		int no_bytes = message_length;	
		char on = '1'; char off='0';
		char msg_bits[no_bytes][8];
		char msg_bit; char audio_lsb;
		int pos = 0;
		
		
		int soundfile_bytes_required = (no_bytes * 8);

		
		for(int i=0;i<no_bytes;i++)
		{
			for(int y=7; y>=0;y--)
			{
				msg_bit = (message[i] & 1<<y) ? on : off;
				audio_lsb = (binary->mem_offset[pos] & 1<<0) ? on : off;

				if(msg_bit != audio_lsb)
				{	
					binary->mem_offset[pos] ^= 1<<0; pos+=1;
				
				}else
				{
					pos+=1;
				}

				
			}
		}

		printf("[+]Infect audio file: success\n");
}

/*extract and print the secret message*/
void extract_message_lsb(struct binary_info *binary,int message_length)
{
	const int no_bytes = message_length;
	char on = '1'; char off='0';
	char msg_bit; char soundfile_lsb; 
	char message[no_bytes];
	int pos=0; int bit_pos=7;
	int soundfile_byte_limit = no_bytes * 8;
	

/*	for(int i=0;i<soundfile_byte_limit;i++)
	{
	
		printf("%s",((binary->mem_offset[i] & 1<<0) ? "1" : "0"));

		if(((i+1)%8)==0)
			printf("\n");
		
	} printf("\n"); */


	for(int i=0;i<soundfile_byte_limit;i++)
	{
	
			
			soundfile_lsb = (binary->mem_offset[i] & 1<<0) ? on : off;

			msg_bit = (message[pos] & 1<<bit_pos) ? on : off;

			if(soundfile_lsb != msg_bit)
			{
				message[pos] ^= 1<<bit_pos; bit_pos--;	
			}
			else
			{
				bit_pos--;
			}

			
			if(((i+1)%8)==0)
			{
				bit_pos=7; pos++;
			}
		
	}
	message[no_bytes]='\0';

	printf("[+]Extract message:success\n");

	printf("\n%s\n",message);

}


/*regex function*/
int FileCheck(char *filename)
{

	/*use case for checking the extension of the file, so we know to check from the reverse of the array*/
	int i = (int)strlen(filename);

		if((filename[i-1]=='g') && (filename[i-2]=='p') && (filename[i-3]=='g') && (filename[i-4]=='.'))
		{
			return 0;
		}
		else
		{
			return -1;
		}
		

}



