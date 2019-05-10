#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>

#define DISP_BLANK 0x0C

int main(int argc, char *argv[])
{
        int fd_disp, ret;
        unsigned long buffer[4] = {0};

        if (strcasecmp(argv[1], "off") == 0) buffer[1] = 1;
        else if (strcasecmp(argv[1], "on") == 0) buffer[1] = 0;
        else return 0;

        fd_disp = open("/dev/disp", O_RDWR);
        if (fd_disp == -1) {
                fprintf(stderr, "Error: Failed to open /dev/disp: %s\n", strerror(errno));
                return errno;
        }

        if (ioctl(fd_disp, DISP_BLANK, buffer)) ret = errno;
        else ret = 0;

        close(fd_disp);

        return ret;
}