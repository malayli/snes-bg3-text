ifeq ($(strip $(PVSNESLIB_HOME)),)
$(error "Please create an environment variable PVSNESLIB_HOME with path to its folder and restart application. (you can do it on windows with <setx PVSNESLIB_HOME "/c/snesdev">)")
endif

include ${PVSNESLIB_HOME}/devkitsnes/snes_rules

.PHONY: bitmaps all

#---------------------------------------------------------------------------------
# ROMNAME is used in snes_rules file
export ROMNAME := snesbg3text

all: bitmaps $(ROMNAME).sfc

clean: cleanBuildRes cleanRom cleanGfx cleanAudio
	
#---------------------------------------------------------------------------------
pvsneslibfont.pic: res/font/pvsneslibfont.bmp
	@echo convert font with no tile reduction ... $(notdir $@)
	$(GFXCONV) -pr -pc4 -n -gs8 -pe0 -fbmp -mp  $<

bg3fontpalette.pic: res/font/bg3fontpalette.bmp
	@echo convert font with no tile reduction ... $(notdir $@)
	$(GFXCONV) -pr -pc4 -n -gs8 -pe0 -fbmp -mp  $<

bg1.pic: res/map/bg1.bmp
	@echo convert bitmap ... $(notdir $@)
	$(GFXCONV) -pc16 -po16 -n -gs8 -pe2 -fbmp -m $<

bitmaps : pvsneslibfont.pic bg3fontpalette.pic bg1.pic
