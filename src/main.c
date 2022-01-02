#include <snes.h>

// ROM

// BG1
extern char bg1Tiles, bg1Tiles_end;
extern char bg1Palette, bg1Palette_end;
extern char bg1Map, bg1Map_end;

// BG3
#define bg3TileMapAddress 0x1000+2048 // so bg1 tile map can be on 0x1024 and bg2 tile map on 0x1024 + 1024
#define bg3TileSetAddress 0x4000 // so bg1 tile set can be on 0x2000 and bg2 tile set on 0x3000
extern char snesfontbg3_tiles, snesfontbg3_tiles_end;
extern char snesfontbg3_map, snesfontbg3_map_end;
extern char snesfontbg3_pal;

// RAM

// BG3
bool refreshBg3Text = FALSE;
u16 bg3StringMap[1024];
char *bg3TilePointer;
int bg3TileIndex;
u8 bg3PaletteNumber;
char *bg3FontTileMap;

// BG3 Text Functions

void bg3FontInit(char *fontTileSource,
    char *fontTileSource_end,
    char *fontTilePalette,
    u8 paletteNumber,
    char *fontTileMapSource) {
    bg3PaletteNumber = paletteNumber;
    bg3FontTileMap = fontTileMapSource;

    bgSetMapPtr(2, bg3TileMapAddress, SC_32x32);

    bgInitTileSet(2, fontTileSource,
        fontTilePalette,
        bg3PaletteNumber,
        (fontTileSource_end - fontTileSource),
        4*2,
        BG_16COLORS,
        bg3TileSetAddress);
}

void bg3PrintText(char *string, u16 x, u16 y) {
    bg3TilePointer = string;
    for (bg3TileIndex=0; *bg3TilePointer != 0; bg3TileIndex++) {
        bg3StringMap[(x+bg3TileIndex)*2 + y*32] = (*(bg3FontTileMap+(*bg3TilePointer-32)*2)) | (bg3PaletteNumber<<10) | (1<<13); // on bg 3 so priority high
        bg3TilePointer++;
    }
}

// VBlank

// Note: Don't call functions in superNintendoVblank to improve performance
void superNintendoVblank(void) {
    scanPads();

    if (refreshBg3Text) {
        dmaCopyVram((u8 *) bg3StringMap,bg3TileMapAddress, 2048);
        refreshBg3Text = FALSE;
    }

    // Refresh the sprite on the screen
    dmaCopyOAram((unsigned char *) &oamMemory, 0, 0x220);

    snes_vblank_count++;
}

// Main

int main(void) {
    // Initialize SNES
    consoleInit();

    setMode(BG_MODE1,BG3_MODE1_PRORITY_HIGH);
    bgSetEnable(0);
    bgSetDisable(1);
    bgSetEnable(2);
    bgSetDisable(3);

    // Display an image on BG1
    bgInitTileSet(0, &bg1Tiles, &bg1Palette, 2, (&bg1Tiles_end - &bg1Tiles), (&bg1Palette_end - &bg1Palette), BG_16COLORS, 0x2000);
    bgInitMapSet(0, &bg1Map, (&bg1Map_end - &bg1Map),SC_32x32, 0x1000);

    // Display text on BG3
    bg3FontInit(&snesfontbg3_tiles, &snesfontbg3_tiles_end, &snesfontbg3_pal, 0, &snesfontbg3_map);
    bg3PrintText(">", 4, 19);
    bg3PrintText("START", 5, 19);
    bg3PrintText("OPTIONS", 5, 21);
    refreshBg3Text = TRUE;

    setScreenOn();

    nmiSet(superNintendoVblank);

    while(1) {
        WaitForVBlank();
    }
    return 0;
}

