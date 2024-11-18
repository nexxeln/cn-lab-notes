#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5035
#define MAX_SIZE 30

int main()
{
    int sock_fd;
    struct sockaddr_in server_addr;
    char dividend[MAX_SIZE], divisor[MAX_SIZE];
    char quotient[MAX_SIZE], remainder[60], crc[10];

    // Create socket
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    // Get input
    printf("\nEnter the dividend: ");
    scanf("%s", dividend);
    printf("\nEnter the divisor: ");
    scanf("%s", divisor);

    // Send data
    write(sock_fd, dividend, MAX_SIZE);
    write(sock_fd, divisor, MAX_SIZE);

    printf("\nServer result:");

    // Receive results
    read(sock_fd, quotient, MAX_SIZE);
    read(sock_fd, remainder, 60);
    read(sock_fd, crc, 10);

    printf("\n\nQuotient=%s", quotient);
    printf("\n\nRemainder=%s", remainder);
    printf("\n\nCRC values=%s\n", crc);

    close(sock_fd);
    return 0;
}