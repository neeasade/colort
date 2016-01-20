#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int i=0;
    int index = 0;
    int tintValue = 0;
    int original = 0;
    char *colorValues="0123456789abcdef";
    char *colorString;

    // 1 for -l (limit), -1 for -i (invert)
    int optionSwitch=0;

    // you're not going to specify -i and -l
    if (argc == 4){
        if (strcmp(argv[1], "-l") == 0)
            optionSwitch = 1;
        if (strcmp(argv[1], "-i") == 0)
            optionSwitch = -1;
    }

    // last will be color, second to last will be tint value.
    colorString = argv[argc - 1];
    tintValue = atoi(argv[argc -2]);

    for (i = 0; colorString[i] != 0; i++)
    {
        switch(colorString[i])
        {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9': index = colorString[i] - '0'; break;

            case 'a':
            case 'A': index = 10; break;

            case 'b':
            case 'B': index = 11; break;

            case 'c':
            case 'C': index = 12; break;

            case 'd':
            case 'D': index = 13; break;

            case 'e':
            case 'E': index = 14; break;

            case 'f':
            case 'F': index = 15; break;

            default: index = -1; break;
        }

        if (index != -1)
        {
            original = index;

            index += tintValue;

            while(index < 0)
                index += 16;

            index = index % 16;

            // limit
            if (optionSwitch == 1)
            {
                if (tintValue > 0 && index < original)
                    index = 15;
                else if (tintValue < 0 && original < index)
                    index = 0;
            }

            colorString[i] = colorValues[index];
        }
    }

    printf("%s\n", colorString);
    return 0;
}
