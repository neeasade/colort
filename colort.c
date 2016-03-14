#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

long hexToDec(char*,int,int);
void decToHex(long,char*);
void limit(long*);
void makeValid(long*);
void usage();

// usage
void usage()
{
    printf("%s", "usage: colort [-s <index>] ([-l] <value> <color> | -i <color>)\n");
    exit(1);
}

// convert hexidecimal to character, eg ff -> 255.
long hexToDec(char *input, int start, int end)
{
    char hex[3] = {input[start], input[end], '\0'};
    return strtol(hex, NULL, 16);
}

// convert deximal to hex char.
void decToHex(long value, char *destination)
{
    // replace the null char with what should be there.
    char original = destination[2];
    sprintf(destination, "%02lX", value);
    destination[2] = original;
}

// make a color valid without rotating.
void limit(long *input)
{
    if (*input > 255)
        *input = 255;
    else if (*input < -1)
        *input = 0;
}

// make a color valid post rotating.
void makeValid(long *input)
{
    while(*input < 0)
        *input += 256;

    *input = *input % 256;
}

int main(int argc, char *argv[])
{
    int i, selectIndex, tintValue, optionSwitch, negativeIndex;
    i = selectIndex = tintValue = optionSwitch = negativeIndex = 0;

    long red, blue, green;
    red = blue = green = 0;

    int enableRed, enableBlue, enableGreen;
    enableRed = enableBlue = enableGreen = 0;

    char *colorString, *inputString;
    char negativeTintInput[10] = "          ";

    // -l (limit), -i (invert), -s (select)
    while ((i = getopt  (argc, argv, ":rgblis:")) != -1)
        switch(i)
        {
            case 'l': optionSwitch =  1; break;
            case 'i': optionSwitch = -1; break;
            case 'r': enableRed = 1; break;
            case 'g': enableGreen = 1; break;
            case 'b': enableBlue = 1; break;
            case 's': selectIndex = atoi(optarg); break;
            case '?':
                // here we hand number arguments to a string to parse
                // because we want to do negative args without escaping (--)
                switch(optopt)
                {
                    case '1': case '2': case '3': case '4': case '5':
                    case '6': case '7': case '8': case '9': case '0':
                    negativeTintInput[negativeIndex++] = optopt;
                    break;
                    default: abort();
                }
        }

    // always gonna need an input string.
    if (argv[optind] == NULL)
        usage();

    // if not inverting, need tint value.
    if (optionSwitch != -1 && !negativeIndex)
        if (argv[optind] == NULL || argv[optind + 1] == NULL)
            usage();

    if (!enableRed && !enableGreen && !enableBlue)
        enableRed = enableGreen = enableBlue = 1;

    tintValue = negativeIndex ?  -1 * atoi(negativeTintInput) : atoi(argv[optind]);
    inputString = argv[argc - 1];

    // default to last 6 characters.
    if (!selectIndex)
        selectIndex = strlen(inputString) - 6;

    colorString = &inputString[selectIndex];

    // parse
    red   = hexToDec(colorString, 0, 1);
    green = hexToDec(colorString, 2, 3);
    blue  = hexToDec(colorString, 4, 5);

    // do the thing
    switch(optionSwitch)
    {
        case 0:
        case 1:
            red   += tintValue;
            green += tintValue;
            blue  += tintValue;

            if (optionSwitch)
            {
                limit(&red);
                limit(&green);
                limit(&blue);
            }
            else
            {
                makeValid(&red);
                makeValid(&green);
                makeValid(&blue);
            }
            break;

        case -1:
            red   = 255 - red;
            green = 255 - green;
            blue  = 255 - blue;
    }

    // insert result if enabled
    if (enableRed)
        decToHex(red,   &colorString[0]);
    if (enableGreen)
        decToHex(green, &colorString[2]);
    if (enableBlue)
        decToHex(blue,  &colorString[4]);

    printf("%s\n", inputString);
    return 0;
}
