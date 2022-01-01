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
.ends

.section ".rodata3" superfree
.ends

.section ".rodata4" superfree
.ends

.section ".rodata5" superfree
.ends
