#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

#include "GPIObank.h"

#define DEBUG

unsigned int read_data(uintptr_t addr, int size)
{
	const size_t MAP_SIZE = 4096UL;
	const size_t MAP_MASK = MAP_SIZE - 1;

	int fd = open("/dev/mem", O_RDWR | O_SYNC);

	if (fd == -1)
	{
		perror("can't open /dev/mem");
		abort();
	}

	unsigned char *map_base = mmap(0, MAP_SIZE, PROT_READ, MAP_SHARED,
		fd, addr & ~MAP_MASK);

	if (map_base == (void*)-1)
	{
		perror("mmap() failed");
		abort();
	}

	unsigned int ret_val;
	ret_val = *(map_base + (addr & MAP_MASK));
	if(size >= 2) ret_val |= ((*(map_base + (addr & MAP_MASK) + 1)) << 8);
	if(size == 4){
		ret_val |= ((*(map_base + (addr & MAP_MASK) + 2)) << 16);
		ret_val |= ((*(map_base + (addr & MAP_MASK) + 3)) << 24);
	}

	if (munmap(map_base, MAP_SIZE) != 0)
	{
		perror("munmap() failed");
		abort();
	}

	close(fd);

	return ret_val;
}

uintptr_t get_addr(char *adr){
	int i, addr;
	addr = 0;
	for(i = 0; i < 8; i++){
		char s[2] = {};
		switch(adr[i+2]){
			case 'A':
			case 'a': addr = (addr << 4) | (0x0f & 0x0a);
				  break;
			case 'B':
			case 'b': addr = (addr << 4) | (0x0f & 0x0b);
				  break;
			case 'C':
			case 'c': addr = (addr << 4) | (0x0f & 0x0c);
				  break;
			case 'D':
			case 'd': addr = (addr << 4) | (0x0f & 0x0d);
				  break;
			case 'E':
			case 'e': addr = (addr << 4) | (0x0f & 0x0e);
				  break;
			case 'F':
			case 'f': addr = (addr << 4) | (0x0f & 0x0f);
				  break;
			default:  s[0] = adr[i + 2];
				  addr = (atoi(s) & 0x0f) | (addr << 4);
				  break;
		}
#ifdef DEBUG
		printf("I : %d, addr[%d] : %c, addr : %x.\n", i, i+2, adr[i + 2], addr);
#endif
	}
#ifdef DEBUG
	printf("Register address is : 0x%x.\n",addr);
#endif
	return addr;
}

int main(int argc, char *argv[]){
	uintptr_t reg_addr;
	int size = 1, data;
	if(argc < 3){
		printf("Invalid Argument.\n\tUsage : mem <R/W> <reg addr> [.Size]\n");
		return 0;
	}

	if(argv[3][1] == 'w' && argc > 3) size = 2;
	else if(argv[3][1] == 'l' && argc > 3) size = 4;
	else size = 1;

	reg_addr = get_addr(argv[2]);

	switch(argv[1][1]){
		case 'R':
		case 'r': data = read_data(reg_addr, size);
			  printf("Recieved Data is : %d, in hex : 0x%x.\n", data, data);
			  break;
		default : printf("Operation Reserved for Future use.\n");
	}
}

