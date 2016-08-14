#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

long hexToDec(char*,int);
void decToHex(long,char*);
int makeValid(long*,int);
void usage();

/* usage */
void usage()
{
    printf("%s", "usage: colort [-s <index>] ([-l] <value> <color> | -i <color>)\n");
    exit(1);
}

/* convert hexidecimal to character, eg ff -> 255. */
long hexToDec(char *input, int index)
{
    char hex[2] = {input[index++], input[index]};
    return strtol(hex, NULL, 16);
}

/* convert deximal to hex char. */
void decToHex(long value, char *destination)
{
    /* sprintf appends terminator by default, so we'll replace with what was prev there. */
    char original = destination[2];
    sprintf(destination, "%02lX", value);
    destination[2] = original;
}

/* make a color valid post tinting, limit if enabled. */
/* return 1 if limit enabled and limited. */
int makeValid(long *input, int limit)
{
    if (limit) {
        if (*input > 255) {
            *input = 255;
            return 1;
        } else if (*input < 0) {
            *input = 0;
            return 1;
        }
        return 0;
    } else {
        while(*input < 0)
              *input += 256;

        *input = *input % 256;
        return 0;
    }
}

int main(int argc, char *argv[])
{
    int i, selectIndex, tintValue, optionSwitch, negativeIndex,
        yiq, terse, enableRed, enableBlue, enableGreen, ret, exitStatus;

    i = yiq = terse = tintValue = optionSwitch = negativeIndex =
        enableRed = enableBlue = enableGreen = ret = exitStatus = 0;

    selectIndex = -1;

    long red, blue, green;
    red = blue = green = 0;

    char *colorString, *inputString;
    char negativeTintInput[10] = "";

    /* -l (limit), -i (invert), -s (select) */
    while ((i = getopt  (argc, argv, ":rghbtlis:c")) != -1)
        switch(i) {
            case 'l': optionSwitch =  1; break;
            case 'i': optionSwitch = -1; break;
            case 'c': optionSwitch =  2; break;
            case 'r': enableRed    =  1; break;
            case 'g': enableGreen  =  1; break;
            case 'b': enableBlue   =  1; break;
            case 's': selectIndex  =  atoi(optarg); break;
            case 'h': usage();
            case 't': terse = 1; break;
            case '?':
                /* here we hand number arguments to a string to parse */
                /* because we want to do negative args without escaping (--) */
                switch(optopt) {
                    case '1': case '2': case '3': case '4': case '5':
                    case '6': case '7': case '8': case '9': case '0':
                        negativeTintInput[negativeIndex++] = optopt;
                        break;
                    default: usage();
                }
        }

    /* always gonna need an input string. */
    if (argv[optind] == NULL)
        usage();

    /* if not inverting, need tint value. */
    if (optionSwitch != -1 && optionSwitch != 2 && !negativeIndex)
        if (argv[optind] == NULL)
            usage();

    /* default to all colors. */
    if (!enableRed && !enableGreen && !enableBlue)
         enableRed = enableGreen = enableBlue = 1;

    /* set input and color strings, default to last 6 characters. */
    inputString = argv[argc - 1];
    selectIndex = selectIndex == -1 ? strlen(inputString) - 6 : selectIndex;
    colorString = &inputString[selectIndex];

    /* set color handles. */
    red   = hexToDec(colorString, 0);
    green = hexToDec(colorString, 2);
    blue  = hexToDec(colorString, 4);

    /* set and apply the tint value if we're using it */
    if (optionSwitch != -1 && optionSwitch != 2) {
        tintValue = negativeIndex ? -1 * atoi(negativeTintInput) : atoi(argv[optind]);
        red   += tintValue;
        green += tintValue;
        blue  += tintValue;
    }

    /* do the thing */
    switch(optionSwitch) {
        case -1: /* invert */
            red   = 255 - red;
            green = 255 - green;
            blue  = 255 - blue;
            break;

        case 0: /* normal */
        case 1: /* limit */
            ret = makeValid(&red,   optionSwitch);
            ret += makeValid(&green, optionSwitch);
            ret += makeValid(&blue,  optionSwitch);
            exitStatus = ret >=2 ? 1 : 0;
            break;

        case 2: /* contrast - ref: https://24ways.org/2010/calculating-color-contrast/ */
            yiq = ((red * 299) + (green * 587) + (blue * 114)) / 1000;
            exit(yiq >= 128 ? 1 : 0);
    }

    /* insert result if enabled */
    if (enableRed)
        decToHex(red,   &colorString[0]);
    if (enableGreen)
        decToHex(green, &colorString[2]);
    if (enableBlue)
        decToHex(blue,  &colorString[4]);

    /* print color only */
    if (terse) {
        colorString[6] = '\0';
        inputString = colorString;
    }

    printf("%s", inputString);
    exit(exitStatus);
}
