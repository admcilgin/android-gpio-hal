#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

#define BUFFER_LENGTH 256
static char receive[BUFFER_LENGTH];

int main(int argc, char** argv) {

    int ret, fd;
    char stringToSend[BUFFER_LENGTH];

    printf("Starting Gpio Device..\n");

    fd = open("/dev/stormmxgpio", O_RDWR);
    if (fd < 0) {
        perror("Failed to open Gpio device...");
        return errno;
    }

    printf("Type in a command to send to the kernel module:\n");
    scanf("%[^\n]%*c", stringToSend);                // Read in a string (with spaces)
    printf("Sending command to the device [%s].\n", stringToSend);

    ret = write(fd, stringToSend, strlen(stringToSend)); // Send the string to the LKM
    if (ret < 0) {
        perror("Failed to write the message to the device.");
        return errno;
    }

    printf("Press ENTER to read back from the device...\n");
    getchar();

    printf("Reading from the device...\n");
    ret = read(fd, receive, BUFFER_LENGTH);        // Read the response from the LKM
    if (ret < 0) {
        perror("Failed to read the message from the device.");
        return errno;
    }

    printf("The received message is: [%s]\n", receive);
    printf("End of the program\n");

    return 0;
}
