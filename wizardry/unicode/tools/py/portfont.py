import sys

def read_int(input, count, signed = False):
    return int.from_bytes(input.read(count), byteorder = 'little', signed = signed)

GLYPH_COLOR_CHARS = ['  ', '▒▒', '░░', '██']

class FEGlyph:
    def __init__(self):
        self.pixels = [0 for i in range(16 * 16)]
        self.length = -1

    def read_from_file(self, file):
        read_int(file, 4) # ignore that part
        read_int(file, 1) # and also that part

        self.length = read_int(file, 1)

        read_int(file, 2) # and also this part

        for iy in range(16):
            line = read_int(file, 4)

            for ix in range(16):
                self.pixels[ix + 16 * iy] = 0x3 & (line >> (ix*2))

def read_glyphs(f, offset):
    result = [FEGlyph() for _ in range(0x100)]

    for i in range(0x100):
        f.seek((offset & 0x1FFFFFF) + (i * 4))
        glyph_addr = read_int(f, 4)

        if glyph_addr != 0:
            f.seek(glyph_addr & 0x1FFFFFF)
            result[i].read_from_file(f)

    return result

def print_glyphs(glyphs, prefix):
    for i, glyph in enumerate(glyphs):
        if glyph.length >= 0:
            print(f"    decl_glyph {prefix}Glyph_Character_{i:02X} @ '{chr(i)}'")
            print(f"")

            words = []

            for iy in range(16):
                line = 0
                line_gfx = ""

                for ix in range(16):
                    line = line | (glyph.pixels[ix + 16 * iy] << (ix*2))
                    line_gfx += GLYPH_COLOR_CHARS[glyph.pixels[ix + 16 * iy]]

                words.append(line)
                print(f"    @ {line_gfx}")

            print(f"")

            print(f"    .word 0") 
            print(f"    .byte 0, {glyph.length}, 0, 0")
            print(f"    .word {', '.join(f'0x{word:08X}' for word in words[0:4])}")
            print(f"    .word {', '.join(f'0x{word:08X}' for word in words[4:8])}")
            print(f"    .word {', '.join(f'0x{word:08X}' for word in words[8:12])}")
            print(f"    .word {', '.join(f'0x{word:08X}' for word in words[12:16])}")

            print(f"")

    for i, glyph in enumerate(glyphs):
        if glyph.length >= 0:
            print(f"    .word 0x{i:04X}, {prefix}Glyph_Character_{i:02X} @ '{chr(i)}'")

def main(args):
    try:
        rom_gba = args[1]

    except IndexError:
        sys.exit(f"Usage: {args[0]} fe8-us.gba")

    glyphs = []

    with open(rom_gba, 'rb') as f:
        print_glyphs(read_glyphs(f, 0x0858C7EC), "System")
        print_glyphs(read_glyphs(f, 0x0858F6F4), "Talk")

if __name__ == '__main__':
    main(sys.argv)
