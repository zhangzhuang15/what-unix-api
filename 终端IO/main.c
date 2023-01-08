#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("/dev/tty", O_RDWR);

    if (fd < 0)
        printf("open /dev/tty failed\n");
    else {
        printf("open tty at fd %d\n", fd);
        write(fd, "okey", 4);
        close(fd);
    }

    return 0;
    
}