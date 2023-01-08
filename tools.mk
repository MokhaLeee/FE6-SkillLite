EXE := .exe
PYTHON := python3

export PREFIX ?= arm-none-eabi-
export CC  := $(PREFIX)gcc
export CPP := $(PREFIX)cpp
export AS  := $(PREFIX)as
export CC1 := tools/agbcc/bin/agbcc

EA := tools/EventAssembler/ColorzCore$(EXE)

export PARSEFILE         := tools/EventAssembler/Tools/ParseFile$(EXE)
export PORTRAITFORMATTER :=tools/EventAssembler/Tools/PortraitFormatter$(EXE)
export PNG2DMP           := tools/EventAssembler/Tools/Png2Dmp$(EXE)
export COMPRESS          := tools/EventAssembler/Tools/compress$(EXE)
export LYN 				 := tools/EventAssembler/Tools/lyn$(EXE) -longcalls
export EADEP             := tools/EventAssembler/ea-dep$(EXE)

export PORTRAIT_PROCESS  := $(PYTHON) tools/FE-PyTools/portrait-process.py
export TEXT_PROCESS      := $(PYTHON) tools/FE-PyTools/text-process-classic.py
export C2EA              := $(PYTHON) tools/FE-PyTools/NMM2CSV/c2ea.py
export TMX2EA            := $(PYTHON) tools/FE-PyTools/TMX2EA/tmx2ea.py

NOTIFY_PROCESS = @echo "$(notdir $<) => $(notdir $@)"
