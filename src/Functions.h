#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<string.h>

struct binary_info
{
	u_int8_t *mem_offset;
	int binary_size;
};


void map_binary(char *binary_name,struct binary_info *binary);

void store_message_length(struct binary_info *binary,char length);

char extract_message_length(struct binary_info *binary);

void lsb_basic_infection(char *message,int message_length,struct binary_info *binary);

void extract_message_lsb(struct binary_info *binary,int message_length);

