#include <stdio.h>
#include <cs50.h>
//#include "bmp.h"

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        fprintf(stderr, "Needs 2 args");
        return 1;
    }
    // open input file
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open file");
        return 2;
    }

    int count = 0;
    unsigned char block[512];
    FILE *outptr = NULL;

    while (fread(block, 1, 512, inptr) != 0x00)
    {
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
        {

            if (outptr != NULL)
            {
                fclose(outptr);
            }

            char outfile[8];
            sprintf(outfile, "%03d.jpg", count++);
            outptr = fopen(outfile, "w");

            if (outptr == NULL)
            {
                fclose(inptr);
                fprintf(stderr, "Could not create %s.\n", outfile);
                return 3;
            }

            fwrite(block, 1, 512, outptr);

        }
        else if (outptr != NULL)
        {
            fwrite(block, 1, 512, outptr);
        }
    }
    fclose(inptr);
    fclose(outptr);
    return 0;
}
