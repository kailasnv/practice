#include <stdio.h>

int main()
{

    unsigned char A[8] =
        {
            /* The hexadecimal value 0x18 converts to binary as: 00011000
            (in 8-bit representation) */
            0x18, // 0
            0x24, // 1   =>  0010 0100
            0x42, // 2   =
            0x7E,
            0x42,
            0x42,
            0x42,
            0x00,
        };

    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            printf("*");
        }

        printf("\n");
    }

    return 0;
}