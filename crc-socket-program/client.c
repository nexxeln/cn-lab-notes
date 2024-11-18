#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void calculate_crc(char *data, char *crc_result)
{
    // Simple XOR-based CRC calculation
    int crc = 0;
    for (int i = 0; i < strlen(data); i++)
    {
        crc ^= (data[i] - '0');
    }
    sprintf(crc_result, "%02d", crc);
}

int main()
{
    int sock = 0;
    struct sockaddr_in serv_addr;
    char dividend[BUFFER_SIZE] = {0};
    char divisor[BUFFER_SIZE] = {0};
    char buffer[BUFFER_SIZE] = {0};

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    printf("Enter the dividend: ");
    scanf("%s", dividend);

    printf("Enter the divisor: ");
    scanf("%s", divisor);

    // Send data to server
    send(sock, dividend, strlen(dividend), 0);
    send(sock, divisor, strlen(divisor), 0);

    // Receive server result
    read(sock, buffer, BUFFER_SIZE);
    printf("\nServer result:\n%s", buffer);

    close(sock);
    return 0;
}
