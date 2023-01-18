FE6_GBA ?= ../../tools/fe6/fe6.gba

STRING_LOCATIONS := string-locations.txt

STRINGS_REPOINT := data/fe6-strings-repoint.event
STRINGS_SOURCES := data/fe6-strings.s

all: $(STRINGS_REPOINT) $(STRINGS_SOURCES)
.PHONY: all

clean:
	rm -f $(STRINGS_REPOINT) $(STRINGS_SOURCES)
.PHONY: clean

$(STRINGS_REPOINT): $(STRING_LOCATIONS) $(FE6_GBA)
	python tools/py/cvtstringevt.py $(FE6_GBA) $(STRING_LOCATIONS) > $(STRINGS_REPOINT)

$(STRINGS_SOURCES): $(STRING_LOCATIONS) $(FE6_GBA)
	python tools/py/cvtstrings.py $(FE6_GBA) $(STRING_LOCATIONS) > $(STRINGS_SOURCES)
