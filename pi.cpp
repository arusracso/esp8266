#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
using namespace std;

static int kDefaultFlags = O_RDWR;
int main(int argc, char *argv[]) {
	int fd = open(argv[1], kDefaultFlags);
	cout << "opened the file descriptor: " << fd << endl;
	cout << "on the port: " << argv[1] << endl;
	
	char buffer[1024];
	const char *payload = "AT\r\n";
	for (size_t i = 0; i < strlen(payload); i++) {
		buffer[i] = payload[i];
	}
	buffer[strlen(payload)] = '\0';
	cout << "the payload is: " << buffer;
	cout << "bytes to write: " << strlen(buffer) << endl;
	while(1) {
		unsigned char b;
		while(read(fd, &b, 1) == 1) cout << "char: " << b << endl;
		int bytesWritten = 0;
		int bytesToWrite = strlen(payload);	
		while (bytesWritten < bytesToWrite) {
			bytesWritten += write(fd, buffer + bytesWritten, bytesToWrite - bytesWritten);
		}
		cout << "sent the payload: " << payload << endl;
		char response[1024];
		cout << "retrieving response: " << endl;
		while (true) {
			ssize_t numRead = read(fd, response, sizeof(response));
			//if (numRead == 0) break;
			response[numRead] = '\0';
			cout << "read this many bytes: " << numRead << endl;
			cout << "response was: " << response << endl;
		}
		break;
	}
}
