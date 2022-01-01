#include <snes.h>

// ROM
#define bg3TileMapAddress 0x1024+2048 // so bg1 tile map can be on 0x1024 and bg2 tile map on 0x1024 + 1024
#define bg3TileSetAddress 0x4000 // so bg1 tile set can be on 0x2000 and bg2 tile set on 0x3000

extern char snesfontbg3_tiles, snesfontbg3_tiles_end;
extern char snesfontbg3_map, snesfontbg3_map_end;
extern char snesfontbg3_pal;

// RAM

// BG1
extern char patterns, patterns_end;
extern char palette, palette_end;
extern char map, map_end;

// BG3
bool refreshBg3Text = FALSE;
u8 bg3StringMap[2048];
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
		bg3StringMap[(x+bg3TileIndex)*2 + y*64] = (*(bg3FontTileMap+(*bg3TilePointer-32)*2)) | (bg3PaletteNumber<<10) | (1<<13); // on bg 3 so priority high
		bg3TilePointer++;
    }
}

void bg3UpdateText() {
	dmaCopyVram(bg3StringMap, bg3TileMapAddress, 2048);
}

// VBlank

void superNintendoVblank(void) {
	scanPads();

	if (refreshBg3Text) {
		bg3UpdateText();
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

	bgInitTileSet(0, &patterns, &palette, 2, (&patterns_end - &patterns), (&palette_end - &palette), BG_16COLORS, 0x2000);
	bgInitMapSet(0, &map, (&map_end - &map),SC_32x32, 0x1000);
	
	bg3FontInit(&snesfontbg3_tiles, &snesfontbg3_tiles_end, &snesfontbg3_pal, 0, &snesfontbg3_map);
	bg3PrintText(">", 6, 14);
	bg3PrintText("START", 8, 14);
	bg3PrintText("OPTIONS", 8, 16);
	refreshBg3Text = TRUE;

	setScreenOn();

	nmiSet(superNintendoVblank);
    
	while(1) {
		WaitForVBlank();
	}
	return 0;
}
