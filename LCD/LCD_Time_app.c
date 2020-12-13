#include <stdio.h>
#include <linux/rtc.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[])
{

	int fd, retval;
	struct rtc_time rtc_tm;
	char *dt;

	/* Creating a file descriptor for RTC */
	fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		perror("Requested device cannot be opened!");
		_exit(errno);
	}

        int ret;
        ret = KM_LCD_Init();
        if (ret < 0){
        	printf("KM_LCD_Init Fails\n");
		return -1;
	}
	KM_LCD_ClrScr();
        KM_LCD_Str_XY(0,0," Kernel Masters");

	while(1){
		/* Reading Current RTC Date/Time */
		retval = ioctl(fd, RTC_RD_TIME, &rtc_tm);
		if (retval == -1) {
			perror("ioctl");
			_exit(errno);
		}
		KM_LCD_Str_XY(0,1,"                ");
		sprintf(dt, "DT : %d-%d-%d",rtc_tm.tm_mday, rtc_tm.tm_mon + 1, rtc_tm.tm_year + 1900);
                KM_LCD_Str_XY(0,1,dt);
		sleep(1);
                KM_LCD_Str_XY(0,1,"                ");
                sprintf(dt, "TM : %02d:%02d:%02d",rtc_tm.tm_hour, rtc_tm.tm_min, rtc_tm.tm_sec);
                KM_LCD_Str_XY(0,1,dt);
		sleep(1);
	}
	KM_LCD_Exit();
	close(fd);
	return 0;
}

