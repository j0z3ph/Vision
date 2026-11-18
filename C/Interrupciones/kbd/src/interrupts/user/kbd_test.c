/*
 * Programacion Avanzada: Linux device drivers
 * User-space test file
 */

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <asm/ioctl.h>

#define BUFFER_SIZE 256

#define MY_IOCTL_PRINT _IOC(_IOC_NONE, 'k', 1, 0)
#define MY_IOCTL_SET_BUFFER _IOC(_IOC_WRITE, 'k', 2, BUFFER_SIZE)
#define MY_IOCTL_GET_BUFFER _IOC(_IOC_READ, 'k', 3, BUFFER_SIZE)
#define MY_IOCTL_DOWN _IOC(_IOC_NONE, 'k', 4, 0)
#define MY_IOCTL_UP _IOC(_IOC_NONE, 'k', 5, 0)

#define DEVICE_PATH "/dev/kbd"


int main(void) {
    int fd;
    ssize_t ret;
    char buf[64] = {0};

    /* Device open */
    fd = open(DEVICE_PATH, O_RDWR);
    if (fd < 0) {
        perror("Fallo en open");
        return EXIT_FAILURE;
    }
    printf("[OK] open() exitoso (fd=%d)\n", fd);


    /* Device read */
    ret = read(fd, buf, sizeof(buf) - 1);
    if (ret < 0) {
        perror("Fallo en read");
    } else {
        buf[ret] = '\0';
        printf("[OK] read() leyo %zd bytes: '%s'\n", ret, buf);
    }


    /* Device release */
    if (close(fd) < 0) {
        perror("Fallo en close");
        return EXIT_FAILURE;
    }
    printf("[OK] close() exitoso\n");

    return EXIT_SUCCESS;
}
