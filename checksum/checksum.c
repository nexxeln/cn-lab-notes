#include <stdio.h>
#include <string.h>

int main()
{
    char first[50], second[50];
    int num1 = 0, num2 = 0, sum = 0;

    printf("Enter first binary string  : ");
    scanf("%s", first);

    printf("Enter second binary string : ");
    scanf("%s", second);

    // Convert binary strings to integers
    for (int i = 0; first[i] != '\0'; i++)
    {
        num1 = num1 * 2 + (first[i] - '0');
    }

    for (int i = 0; second[i] != '\0'; i++)
    {
        num2 = num2 * 2 + (second[i] - '0');
    }

    // Calculate sum
    sum = num1 + num2;

    // Print sum in binary
    printf("Sum                        = ");
    for (int i = 31; i >= 0; i--)
    {
        if ((sum >> i) & 1 || i < strlen(first))
        {
            printf("%d", (sum >> i) & 1);
        }
    }
    printf("\n");

    // Print checksum (1's complement)
    printf("Checksum                   = ");
    for (int i = 31; i >= 0; i--)
    {
        if ((sum >> i) & 1 || i < strlen(first))
        {
            printf("%d", !((sum >> i) & 1));
        }
    }
    printf("\n");

    return 0;
}
