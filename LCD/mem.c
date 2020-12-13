#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

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

	unsigned int ret_val = *(map_base + (addr & MAP_MASK));
	if(size > 2) ret_val = ret | ((*(map_base + (addr & MAP_MASK))) << 8);
	if(size == 4){
		ret_val = ret | ((*(map_base + (addr & MAP_MASK))) << 16);
		ret_val = ret | ((*(map_base + (addr & MAP_MASK))) << 24);
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
	for(i = 0; i < 8; i++){
		switch(adr[i]){
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
			default: addr |= (atoi(adr[i]) & 0x0f) | (addr << (i * 4));
				  break;
		}
	}
#ifdef DEBUG
	printf("Register address is : %x.\n",addr);
#endif
	return adr;
}

int main(int argc, char **argv){
	uintptr_t reg_addr;
	int size, data;
	if(argc < 3){
		printf("Invalid Argument.\n\tUsage : mem[byte size] <R/W> <reg addr>");
		return 0;
	}

	if(argc[0][4] == 'w') size = 2;
	else if(argc[0][4] == 'l') size = 4;
	else size = 1;

	reg_addr = get_addr(argv[2]);

	switch(argv[1][1]){
		case 'R':
		case 'r': data = read_data(reg_addr, size);
			  printf("Recieved Data is : %d.\n", data);
			  break;
		default : printf("Operation Reserved for Future use.\n");
	}
}
