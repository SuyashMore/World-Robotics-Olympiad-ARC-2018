#include "utility.h"

int main()
{
    BlockColor[0]=COLOR_YELLOW;
    BlockColor[1]=COLOR_BLUE;
    BlockColor[2]=COLOR_YELLOW;
    BlockColor[3]=COLOR_BLUE;
    BlockColor[4]=COLOR_RED;
    BlockColor[4]=COLOR_GREEN;


    fillNavMap();
    printNavMap();

    return 0;
}