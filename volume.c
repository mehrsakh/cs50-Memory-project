#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int header_size = 44;

int main(int argc, char *argv[])
{

    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }
    FILE *input = fopen(argv[1], "r");

    if (input == NULL)
    {
        printf("could not open file.\n");
        return 1;
    }
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    float factor = atof(argv[3]);
    uint8_t header[header_size];

    fread(&header, sizeof(header), 1, input);

    fwrite(&header, sizeof(header), 1, output);
    int16_t buffer;
    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        buffer *= factor;
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    fclose(input);
    fclose(output);
}
