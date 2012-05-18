#include <unistd.h>

int main()
{
	pid_t pid;
	pid = fork();
	if (pid == 0) {
		execl("./busybox", "echo acm > /dev/usb_device_mode", NULL);
		sleep(1);
		pid = fork();
		if (pid == 0) {
			execl("./busybox", 
			"echo charge_adb > /dev/usb_device_mode", NULL);
			sleep(1);
			pid == fork();
			if (pid == 0)
				execl("./adbd.orig", "", NULL);
		}
	}
	return 0;
}
