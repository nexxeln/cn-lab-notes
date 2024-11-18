#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void calculate_crc(char *data, char *crc_result)
{
    int crc = 0;
    for (int i = 0; i < strlen(data); i++)
    {
        crc ^= (data[i] - '0');
    }
    sprintf(crc_result, "%02d", crc);
}

void binary_division(char *dividend, char *divisor, char *quotient, char *remainder)
{
    int dividend_len = strlen(dividend);
    int divisor_len = strlen(divisor);
    int dividend_num = 0;
    int divisor_num = 0;

    // Convert binary strings to integers
    for (int i = 0; i < dividend_len; i++)
    {
        dividend_num = (dividend_num << 1) + (dividend[i] - '0');
    }

    for (int i = 0; i < divisor_len; i++)
    {
        divisor_num = (divisor_num << 1) + (divisor[i] - '0');
    }

    // Perform division
    int quot = dividend_num / divisor_num;
    int rem = dividend_num % divisor_num;

    // Convert results back to binary strings
    char temp_quot[BUFFER_SIZE] = {0};
    char temp_rem[BUFFER_SIZE] = {0};
    int idx = 0;

    // Convert quotient to binary
    while (quot > 0)
    {
        temp_quot[idx++] = (quot % 2) + '0';
        quot /= 2;
    }

    // Reverse the quotient string
    int len = strlen(temp_quot);
    for (int i = 0; i < len / 2; i++)
    {
        char temp = temp_quot[i];
        temp_quot[i] = temp_quot[len - 1 - i];
        temp_quot[len - 1 - i] = temp;
    }

    // If quotient is 0, make it "0"
    if (len == 0)
    {
        temp_quot[0] = '0';
        temp_quot[1] = '\0';
    }

    // Convert remainder to binary and pad with zeros if needed
    idx = 0;
    if (rem == 0)
    {
        temp_rem[0] = '0';
        temp_rem[1] = '0';
        temp_rem[2] = '0';
        temp_rem[3] = '\0';
    }
    else
    {
        while (rem > 0)
        {
            temp_rem[idx++] = (rem % 2) + '0';
            rem /= 2;
        }
        // Pad with zeros to make it 3 digits
        while (idx < 3)
        {
            temp_rem[idx++] = '0';
        }
        temp_rem[idx] = '\0';

        // Reverse the remainder string
        len = strlen(temp_rem);
        for (int i = 0; i < len / 2; i++)
        {
            char temp = temp_rem[i];
            temp_rem[i] = temp_rem[len - 1 - i];
            temp_rem[len - 1 - i] = temp;
        }
    }

    strcpy(quotient, temp_quot);
    strcpy(remainder, temp_rem);
}

int main()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char dividend[BUFFER_SIZE] = {0};
    char divisor[BUFFER_SIZE] = {0};
    char response[BUFFER_SIZE] = {0};
    char crc_value[3] = {0};

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    while (1)
    {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);

        read(new_socket, dividend, BUFFER_SIZE);
        read(new_socket, divisor, BUFFER_SIZE);

        printf("Binded...\n");
        printf("Dividend:%s\n", dividend);
        printf("Divisor:%s\n", divisor);

        char dividend_padded[BUFFER_SIZE];
        sprintf(dividend_padded, "%s000", dividend);
        printf("Dividend with zero appended:%s\n", dividend_padded);

        char quotient[BUFFER_SIZE] = {0};
        char remainder[BUFFER_SIZE] = {0};
        binary_division(dividend_padded, divisor, quotient, remainder);

        printf("Quotient=%s\n", quotient);
        printf("Remainder=%s\n", remainder);

        calculate_crc(dividend, crc_value);
        printf("CRC values: %s\n", crc_value);

        sprintf(response, "Quotient=%s\nRemainder=%s\nCRC values=%s\n",
                quotient, remainder, crc_value);
        send(new_socket, response, strlen(response), 0);

        close(new_socket);
    }
    return 0;
}
