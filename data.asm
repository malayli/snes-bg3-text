.include "hdr.asm"

.section ".rodata1" superfree

snesfontbg3_tiles: .incbin "res/font/pvsneslibfont.pic"
snesfontbg3_tiles_end:

snesfontbg3_map: .incbin "res/font/pvsneslibfont.map"
snesfontbg3_map_end:

snesfontbg3_pal: .incbin "res/font/bg3fontpalette.pal"
snesfontbg3_pal_end:

.ends

.section ".rodata2" superfree

bg1Tiles:
.incbin "res/map/bg1.pic"
bg1Tiles_end:

bg1Map:
.incbin "res/map/bg1.map"
bg1Map_end:

bg1Palette:
.incbin "res/map/bg1.pal"
bg1Palette_end:

.ends

.section ".rodata3" superfree
.ends

.section ".rodata4" superfree
.ends

.section ".rodata5" superfree
.ends
