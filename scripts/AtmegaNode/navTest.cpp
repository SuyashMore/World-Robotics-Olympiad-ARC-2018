#include "utility.h"

int main()
{
    BlockColor[0]=COLOR_YELLOW;
    BlockColor[1]=COLOR_RED;
    BlockColor[2]=COLOR_BLUE;
    BlockColor[3]=COLOR_BLUE;
    BlockColor[4]=COLOR_YELLOW;
    BlockColor[5]=COLOR_GREEN;


    fillNavMap();
    printNavMap();

    return 0;
}