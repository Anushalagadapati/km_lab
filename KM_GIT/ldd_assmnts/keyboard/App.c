#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
	int fd, rt;
	char *buf;
	fd = open("/dev/keypad", O_RDWR);
        if(fd<0) {
                printf("open failed\n");
                return -1;
        }

	rt = read(fd, buf, 1);
	if(rt<0) {
		printf("read failed\n");
		return -1;
	}
	
	printf("buff data: %s",buf);

	close(fd);
}
