#include <proto/intuition.h>
#include <proto/graphics.h>

#include <stdio.h>

int main(void){
    struct Screen *screen;
    struct ViewPort *viewPort;
    struct ColorMap *colorMap;

    unsigned char screenName[] = "Workbench";
    unsigned long colorTable[3];
    
    int count;
    const unsigned short targetColor = 0xc00;
    unsigned short currentColor;

    screen = LockPubScreen(screenName);
    if (screen){
        viewPort = &screen->ViewPort;
        colorMap = viewPort->ColorMap;
        count = colorMap->Count;
        printf("WB Screen has %d Colors\n", count);

        if (count>4){
            // try to set pen 4 color
            SetRGB4(viewPort, 4,
                  ((targetColor & 0x0f00) >> 8),
                  ((targetColor & 0x00f0) >> 4),
                  (targetColor & 0x000f));

            currentColor = GetRGB4(viewPort->ColorMap,4);

            if (currentColor == targetColor){
                puts("---\nPen was changed");
            }else{
                puts("---\nPen was not changed");
            }

        }
         
        UnlockPubScreen(NULL, screen);
    }
    return 0;
}
