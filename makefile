CACHE_DIR := .cache_dir
$(shell mkdir -p $(CACHE_DIR) > /dev/null)

FE6_DIR := tools/fe6
FE6_GBA := $(FE6_DIR)/fe6.gba
FE6_ELF := $(FE6_DIR)/fe6.elf
FE6_REF := $(CACHE_DIR)/fe6-ref.s
FE6_SYM := $(CACHE_DIR)/fe6.sym

MAIN    := Main.event
FE6_CHX := fe6-chax.gba

CLEAN_FILES :=
CLEAN_DIRS  := $(CACHE_DIR)


# =========
# = Tools =
# =========
TOOLCHAIN ?= $(DEVKITARM)
ifneq (,$(TOOLCHAIN))
  export PATH := $(TOOLCHAIN)/bin:$(PATH)
endif

EXE :=

ifeq ($(shell python3 -c 'import sys; print(int(sys.version_info[0] > 2))'),1)
  PYTHON3 := python3
else
  PYTHON3 := python
endif

PREFIX ?= arm-none-eabi-
CC  := $(PREFIX)gcc
CPP := $(PREFIX)cpp
AS  := $(PREFIX)as

EA_DIR := tools/EventAssembler
EA := $(EA_DIR)/ColorzCore$(EXE)

PARSEFILE         := $(EA_DIR)/Tools/ParseFile$(EXE)
PORTRAITFORMATTER := $(EA_DIR)/Tools/PortraitFormatter$(EXE)
PNG2DMP           := $(EA_DIR)/Tools/Png2Dmp$(EXE)
COMPRESS          := $(EA_DIR)/Tools/compress$(EXE)
LYN               := $(EA_DIR)/Tools/lyn$(EXE) -longcalls
EA_DEP            := $(EA_DIR)/ea-dep$(EXE)

PORTRAIT_PROCESS  := $(PYTHON3) tools/FE-PyTools/portrait-process.py
TEXT_PROCESS      := $(PYTHON3) tools/FE-PyTools/text-process-classic.py
C2EA              := $(PYTHON3) tools/FE-PyTools/NMM2CSV/c2ea.py
TMX2EA            := $(PYTHON3) tools/FE-PyTools/TMX2EA/tmx2ea.py

ELF2REF           := $(PYTHON3) tools/scripts/elf2ref.py
ELF2SYM           := $(PYTHON3) tools/scripts/elf2sym.py

NOTIFY_PROCESS = @echo "$(notdir $<) => $(notdir $@)"


# ========
# = Main =
# ========
MAIN_DEPS := $(shell $(EA_DEP) $(MAIN) -I $(EA_DIR) --add-missings)

$(FE6_CHX): $(MAIN) $(MAIN_DEPS) $(FE6_GBA) $(FE6_SYM)
	$(NOTIFY_PROCESS)
	@cp -f $(FE6_GBA) $(FE6_CHX)
	@$(EA) A FE6 -input:$(MAIN) -output:$(FE6_CHX) --nocash-sym || rm -f $(FE6_CHX)
	@cat $(FE6_SYM) >> $(FE6_CHX:.gba=.sym)

CLEAN_FILES += $(FE6_CHX)  $(FE6_CHX:.gba=.sym)


# ==========
# = DECOMP =
# ==========
$(FE6_ELF): FORCE
	@echo "[BUILD]	$(notdir $@)"
	@$(MAKE) -s -C $(FE6_DIR)

$(FE6_REF): $(FE6_ELF)
	$(NOTIFY_PROCESS)
	@$(ELF2REF) $(FE6_ELF) > $(FE6_REF)

$(FE6_SYM): $(FE6_ELF)
	$(NOTIFY_PROCESS)
	@$(ELF2SYM) $(FE6_ELF) > $(FE6_SYM)

$(FE6_GBA): $(FE6_ELF)
	$(NOTIFY_PROCESS)
	@touch $(FE6_GBA)


# ============
# = Wizardry =
# ============
INC_DIRS := include $(FE6_DIR)/include
INC_FLAG := $(foreach dir, $(INC_DIRS), -I $(dir))
LYNREF := $(FE6_REF)

ARCH    := -mcpu=arm7tdmi -mthumb -mthumb-interwork
CFLAGS  := $(ARCH) $(INC_FLAG) -Wall -O2 -mtune=arm7tdmi -ffreestanding -mlong-calls
ASFLAGS := $(ARCH) $(INC_FLAG)

%.lyn.event: %.o $(LYNREF)
	$(NOTIFY_PROCESS)
	@$(LYN) $< $(LYNREF) > $@

%.dmp: %.o
	$(NOTIFY_PROCESS)
	@$(OBJCOPY) -S $< -O binary $@

%.o: %.s
	$(AS) $(ASFLAGS) $(SDEPFLAGS) -I $(dir $<) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(CDEPFLAGS) -g -c $< -o $@

%.asm: %.c
	$(CC) $(CFLAGS) $(CDEPFLAGS) -S $< -o $@ -fverbose-asm

# Avoid make deleting objects it thinks it doesn't need anymore
# Without this make may fail to detect some files as being up to date
.PRECIOUS: %.o;

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
WRITANS_DIR         := Writans
WRITANS_ALL_TEXT    := $(wildcard $(WRITANS_DIR)/strings/*.txt)
WRITANS_TEXT_MAIN   := $(WRITANS_DIR)/TextMain.txt
WRITANS_INSTALLER   := $(WRITANS_DIR)/Text.event
WRITANS_DEFINITIONS := $(WRITANS_DIR)/TextDefinitions.event

$(WRITANS_INSTALLER) $(WRITANS_DEFINITIONS): $(WRITANS_TEXT_MAIN) $(WRITANS_ALL_TEXT)
	$(NOTIFY_PROCESS)
	@$(TEXT_PROCESS) $(WRITANS_TEXT_MAIN) --installer $(WRITANS_INSTALLER) --definitions $(WRITANS_DEFINITIONS) --parser-exe $(PARSEFILE)

%.fetxt.dmp: %.fetxt
	$(NOTIFY_PROCESS)
	@$(PARSEFILE) -i $< -o $@ > /dev/null

CLEAN_FILES += $(WRITANS_INSTALLER) $(WRITANS_DEFINITIONS)
CLEAN_DIRS  += $(WRITANS_DIR)/.TextEntries


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

FORCE:
