#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h> 
#include <termios.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <time.h>

#define blocksize 255
#define DEBUG 1

int sfd;

char buf[blocksize];
int initWiFi();
int ATWiFi();
int getBlock();

int main(int argc, char** argv) {  initWiFi();
 ATWiFi();
 return (EXIT_SUCCESS);
}

 

int initWiFi() {
system("sudo systemctl stop serial-getty@ttyAMA0.service");

 sfd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY);

 if (sfd == -1) {
  printf("Error no is : %d\n", errno);
  printf("Error description is : %s\n", strerror(errno));
  return -1;
 }
 struct termios options;
 tcgetattr(sfd, &options);cfsetspeed(&options, B115200);
 cfmakeraw(&options);
 options.c_cflag &= ~CSTOPB;
 options.c_cflag |= CLOCAL;
 options.c_cflag |= CREAD;
 options.c_cc[VTIME] = 1;
 options.c_cc[VMIN] = blocksize;
 tcsetattr(sfd, TCSANOW, &options);
};

 

int getBlock() {
 int bytes;
 struct timespec pause;
 pause.tv_sec = 0;
 pause.tv_nsec = 100000000;
 nanosleep(&pause, NULL);
 memset(buf, '\0', sizeof (buf));
 ioctl(sfd, FIONREAD, &bytes);
 if (bytes == 0)return 0;
 int count = read(sfd, buf, blocksize - 1);
 printf("%d bytes were read\n", count); 
buf[count] = 0;
 if (DEBUG) {
  for (unsigned i = 0; i < strlen(buf); i++) {
	printf("%d %c\n", buf[i], buf[i]);
   }
  fflush(stdout);
 }
 return count;
}

int ATWiFi() {dprintf(sfd, "AT\r\n");
 return getBlock();
}
