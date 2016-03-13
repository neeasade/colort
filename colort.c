#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

long hexToDec(char*,int,int);
void decToHex(long,char*);
void usage();
void limit(long*);
void makeValid(long*);

void usage()
{
    // ehhh
    printf("%s", "usage: colort ([-l] <value> <color> | -i <color>)\n");
    exit(1);
}

// convert hexidecimal to character, eg ff -> 255.
long hexToDec(char *input, int start, int end)
{
    char hex[3] = {input[start], input[end], '\0'};
    return strtol(hex, NULL, 16);
}

// convert deximal to hex char.
void decToHex(long value, char* destination)
{
    // todo
}

// make a color valid without rotating.
void limit(long *input)
{
    if (*input > 255)
        *input = 255;
    else if(*input < -1)
        *input = 0;
}

// make a color valid post rotating.
void makeValid(long *input)
{
    // todo
}

int main(int argc, char *argv[])
{
    int i, index, tintValue, original, optionSwitch;
    i = index = tintValue = original = optionSwitch = 0;
    char *colorString, *inputString;
    long *red, *blue, *green;
    red = blue = green = 0;

    // -l (limit), -i (invert)
    while ((i = getopt  (argc, argv, "l:i")) != -1)
        switch(i)
        {
            case 'l': optionSwitch =  1; tintValue = atoi(optarg); break;
            case 'i': optionSwitch = -1; break;
            default: abort();
        }

    // validate required args based on options.
    switch(optionSwitch)
    {
        case 0: // normal
            if (argv[optind] == NULL || argv[optind + 1] == NULL)
                usage();
            tintValue = atoi(argv[optind]);

        case  1: // limit
        case -1: // invert
            if (argv[optind] == NULL)
                usage();

        default: break;
    }

    // last will be color/input string, always required.
    // assume that the color will be in the last 6 characters of the string.
    inputString = argv[argc - 1];
    colorString = &colorString[strlen(colorString)-6];

    // parse
    *red   = hexToDec(colorString, 0, 1);
    *green = hexToDec(colorString, 2, 3);
    *blue  = hexToDec(colorString, 4, 5);

    // act
    switch(optionSwitch)
    {
        case 0:
        case 1:
            red   += tintValue;
            green += tintValue;
            blue  += tintValue;

            if (optionSwitch)
            {
                limit(red);
                limit(green);
                limit(blue);
            }
            else
            {
                makeValid(red);
                makeValid(green);
                makeValid(blue);
            }
            break;

        case -1:
            *red   = 255 - *red;
            *green = 255 - *green;
            *blue  = 255 - *blue;
    }

    printf("%s\n", colorString);
    return 0;
}
