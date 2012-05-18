#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define ACM		"acm\n"
#define CHARGE_ADB	"charge_adb\n"
#define BIN		"logwrapper.orig"

#define DEBUG

void init_excute()
{
	int fd;
	pid_t pid;

	fd = open("/dev/usb_device_mode", O_WRONLY);
	write(fd, ACM, sizeof(ACM) - 1);
	sleep(1);
	write(fd, CHARGE_ADB, sizeof(CHARGE_ADB) - 1);
	sleep(1);
	
	pid = fork();
	if (pid == 0) {
		execl("/sbin/adb", NULL);
	}	
}

int main()
{
	pid_t pid;
#ifndef DEBUG
	pid = getppid();
	if (pid == 1) {/* excute by init */
		init_excute();
	}
#else
	init_excute();
#endif
	
#ifndef DEBUG
	pid = fork();
	if (pid == 0) {
		execl(BIN, NULL);
	}
#endif
	return 0;
}
