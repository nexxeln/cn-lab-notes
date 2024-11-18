#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 5035
#define MAX_SIZE 30

void calculate_crc(char *dividend, char *divisor, char *quotient, char *remainder)
{
    char temp[60] = {0};
    int div_len = strlen(divisor);
    int i, j = 0;

    // Copy dividend and append zeros
    strcpy(temp, dividend);
    for (i = 0; i < div_len - 1; i++)
        strcat(temp, "0");

    printf("\nDividend with zero appended: %s", temp);

    // Perform CRC division
    for (i = 0; i <= strlen(temp) - div_len; i++)
    {
        if (temp[i] == '1')
        {
            quotient[j++] = '1';
            for (int k = 0; k < div_len; k++)
            {
                temp[i + k] = (temp[i + k] == divisor[k]) ? '0' : '1';
            }
        }
        else
        {
            quotient[j++] = '0';
        }
    }
    quotient[j] = '\0';

    // Get remainder
    strcpy(remainder, temp + strlen(temp) - div_len + 1);
}

int main()
{
    int server_fd, client_fd;
    struct sockaddr_in address;
    char dividend[MAX_SIZE], divisor[MAX_SIZE];
    char quotient[MAX_SIZE] = {0}, remainder[60] = {0}, crc[10] = {0};

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    printf("\nBinding...");
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 1);

    client_fd = accept(server_fd, NULL, NULL);

    // Receive data
    read(client_fd, dividend, MAX_SIZE);
    read(client_fd, divisor, MAX_SIZE);

    printf("\nDividend: %s", dividend);
    printf("\nDivisor: %s", divisor);

    // Calculate CRC
    calculate_crc(dividend, divisor, quotient, remainder);

    // Extract CRC value
    int rem_len = strlen(remainder);
    int div_len = strlen(divisor);
    strncpy(crc, remainder + (rem_len - div_len + 1), div_len - 1);

    printf("\nQuotient: %s", quotient);
    printf("\nRemainder: %s", remainder);
    printf("\nCRC values: %s\n", crc);

    // Send results
    write(client_fd, quotient, MAX_SIZE);
    write(client_fd, remainder, 60);
    write(client_fd, crc, 10);

    close(client_fd);
    close(server_fd);
    return 0;
}