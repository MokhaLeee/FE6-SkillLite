include tools.mk

CLEAN_FILES :=
CLEAN_DIRS  :=

EVENT_MAIN := Main.event
ROM_SOURCE := fe6.gba
ROM_TARGET := fe6-chax.gba

# EAFLAGS := -raws:Tools/EA-Raws --nocash-sym
EAFLAGS :=
EVENT_DEPENDS := $(shell $(EADEP) $(EVENT_MAIN) -I tools/EventAssembler --add-missings)

$(ROM_TARGET): $(EVENT_MAIN) $(EVENT_DEPENDS) $(ROM_SOURCE)
	$(NOTIFY_PROCESS)
	@cp -f $(ROM_SOURCE) $(ROM_TARGET)
	@$(EA) A FE8 -output:$(ROM_TARGET) -input:$(EVENT_MAIN) $(EAFLAGS) || (rm $(ROM_TARGET) && false)
	@echo "cat $(ROM_SOURCE:.gba=.sym) >> $(ROM_TARGET:.gba=.sym)" > /dev/null

CLEAN_FILES += $(ROM_TARGET)  $(ROM_TARGET:.gba=.sym)


# ============
# = Wizardry =
# ============
INC_DIRS := tools/CLib/include include tools/agbcc/include
INC_FLAG := $(foreach dir, $(INC_DIRS), -I $(dir))
LYNREF := tools/CLib/reference/Definitions.h.o

ARCH    := -mcpu=arm7tdmi -mthumb -mthumb-interwork
CFLAGS  := $(ARCH) $(INC_FLAG) -Wall -Wextra -Wno-unused -O2 -mtune=arm7tdmi -ffreestanding -mlong-calls
ASFLAGS := $(ARCH) $(INC_FLAG)

%.lyn.event: %.o $(LYNREF)
	$(NOTIFY_PROCESS)
	@$(LYN) $< $(LYNREF) > $@

%.dmp: %.o
	$(NOTIFY_PROCESS)
	@$(OBJCOPY) -S $< -O binary $@

%.o: %.s
	$(NOTIFY_PROCESS)
	@$(AS) $(ASFLAGS) $< -o $@

%.o: %.c
	$(NOTIFY_PROCESS)
	@$(CC) $(CFLAGS) -g -c $< -o $@

CFILES := $(shell find -type f -name '*.c')
CLEAN_FILES += $(CFILES:.c=.o) $(CFILES:.c=.asm) $(CFILES:.c=.dmp) $(CFILES:.c=.lyn.event)

SFILES := $(shell find -type f -name '*.s')
CLEAN_FILES += $(SFILES:.s=.o) $(SFILES:.s=.dmp) $(SFILES:.s=.lyn.event)


# =============
# = Game Data =
# =============
%.event: %.csv %.nmm
	$(NOTIFY_PROCESS)
	@echo | $(C2EA) -csv $*.csv -nmm $*.nmm -out $*.event $(ROM_SOURCE) > /dev/null

NMM_FILES := $(shell find -type f -name '*.nmm')
CLEAN_FILES += $(NMM_FILES:.nmm=.event)


# ===========
# = Writans =
# ===========
WRITANS_ALL_TEXT    := $(wildcard Texts/strings/*.txt)
WRITANS_TEXT_MAIN   := Texts/TextMain.txt
WRITANS_INSTALLER   := Texts/Text.event
WRITANS_DEFINITIONS := Texts/TextDefinitions.event

$(WRITANS_INSTALLER) $(WRITANS_DEFINITIONS): $(WRITANS_TEXT_MAIN) $(WRITANS_ALL_TEXT)
	$(NOTIFY_PROCESS)
	@$(TEXT_PROCESS) $(WRITANS_TEXT_MAIN) --installer $(WRITANS_INSTALLER) --definitions $(WRITANS_DEFINITIONS) --parser-exe $(PARSEFILE)

%.fetxt.dmp: %.fetxt
	$(NOTIFY_PROCESS)
	@$(PARSEFILE) -i $< -o $@ > /dev/null

CLEAN_FILES += $(WRITANS_INSTALLER) $(WRITANS_DEFINITIONS)
CLEAN_DIRS  += Texts/.TextEntries


# ============
# = Spritans =
# ============
%.4bpp: %.png
	$(NOTIFY_PROCESS)
	@$(PNG2DMP) $< -o $@

%.gbapal: %.png
	$(NOTIFY_PROCESS)
	@$(PNG2DMP) $< -po $@ --palette-only

%.lz: %
	$(NOTIFY_PROCESS)
	@$(COMPRESS) $< $@

PNG_FILES := $(shell find -type f -name '*.png')
CLEAN_FILES += $(PNG_FILES:.png=.4bpp) $(PNG_FILES:.png=.4bpp.lz)


# ==============
# = MAKE CLEAN =
# ==============
clean:
	@rm -f $(CLEAN_FILES)
	@rm -rf $(CLEAN_DIRS)
	@echo "[RM]	$(notdir $(CLEAN_FILES)) $(notdir $(CLEAN_DIRS))"
