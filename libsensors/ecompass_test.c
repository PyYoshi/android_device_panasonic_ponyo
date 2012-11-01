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
	short data =0;

	fd = open("/dev/input/event0", O_RDONLY);
	for (;;) {
		printf("********************************************\n");
		result = ioctl(fd, ECOMPASS_IOC_GET_LFLAG, data);
		printf("Read result: %d\n", result);
		printf("[%04d]\n", data);
	}
	close(fd);

	return 0;
}

