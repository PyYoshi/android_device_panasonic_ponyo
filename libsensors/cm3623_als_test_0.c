#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <unistd.h>

#include "sensors.h"

int main()
{
	int fd;
	int result;
	int data[4] = {0};
	
	//system(command_ps_wake_enable);
	//system(command_ps_control_ps_up);

	fd = open("/dev/cm3623_als", O_RDWR);
	for (;;) {
		printf("********************************************\n");
		result = ioctl(fd, CM3623_CALI_0, data);
		printf("Read result: %d\n", result);
		printf("[A - %04d] [B - %04d] [C - %04d] [D - %04d]\n", data[0], data[1], data[2], data[3]);
	}
	close(fd);

	return 0;
}

