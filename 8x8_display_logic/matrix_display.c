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
            0x00, // 7
        };

    for (int row = 0; row < 8; row++)
    {
        // first taking 7th posi, which is the 1st bit in each hexadec value
        for (int col = 7; col >= 0; col--)
        {
            // check each hexadecimal value from the char array
            // and perform logical rightshift operation to select each bits from it.
            // and do AND operation to get 1 or 0 values for each pixel.
            int bit = (A[row] >> col) & 1;
            // printf("%d", bit);
            if (bit == 0)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }

        printf("\n");
    }

    return 0;
}