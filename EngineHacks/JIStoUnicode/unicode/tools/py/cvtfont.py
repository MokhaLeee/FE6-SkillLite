import sys, cvttab

def read_int(input, count, signed = False):
    return int.from_bytes(input.read(count), byteorder = 'little', signed = signed)

GLYPH_COLOR_CHARS = ['  ', '██', '▒▒', '░░']

def read_pixels(f):
    pixels = [0 for _ in range(16*16)]

    for iy in range(16):
        line = read_int(f, 4)

        for ix in range(16):
            pixels[ix + 16 * iy] = 0x3 & (line >> (ix*2))

    return pixels

def pixels_repr(pixels, w, h):
    result = ''

    for iy in range(h):
        for ix in range(w):
            result += GLYPH_COLOR_CHARS[pixels[ix + 16 * iy]]

        result += '\n'

    return result

def decode_font(f, table_offset, byte_info_tab):
    result = {}

    for i in range(192):
        byte_2 = 0x40 + i

        f.seek((table_offset & 0x1FFFFFF) + 4 * i)
        glyph_addr = read_int(f, 4)

        while glyph_addr != 0:
            f.seek(glyph_addr & 0x1FFFFFF)

            new_glyph_addr = read_int(f, 4)
            byte_1 = read_int(f, 1)

            #_ = read_int(f, 1)
            #_ = read_int(f, 2)
            #print(f"{byte_1:02X} {byte_2:02X}")
            #print(pixels_repr(read_pixels(f), 16, 16))

            unic = byte_info_tab[byte_1].double_byte[byte_2]
            result[unic] = glyph_addr

            glyph_addr = new_glyph_addr

    return result

UNICODE_PAGES = [
    (0x0080, 0x00FF, "Latin-1 Supplement"),
    (0x0370, 0x03FF, "Greek and Coptic"),
    (0x0400, 0x04FF, "Cyrillic"),
    (0x2150, 0x218F, "Number Forms"),
    (0x2190, 0x21FF, "Arrows"),
    (0x2200, 0x22FF, "Mathematical Operators"),
    (0x2460, 0x24FF, "Enclosed Alphanumerics"),
    (0x25A0, 0x25FF, "Geometric Shapes"),
    (0x3000, 0x303F, "CJK Symbols and Punctuation"),
    (0x3040, 0x309F, "Hiragana"),
    (0x30A0, 0x30FF, "Katakana"),
    (0x4E00, 0x9FFF, "CJK Unified Ideographs"),
    (0xFF00, 0xFFEF, "Halfwidth and Fullwidth Forms")]

def print_font_old(font_glyphs, prefix):
    pages = []

    processed_keys = set()

    for beg, end, desc in UNICODE_PAGES:
        glyphs = []

        for i in range(beg, end + 1):
            if i in font_glyphs:
                glyph = font_glyphs[i]
                glyphs.append(glyph)
                processed_keys.add(i)

            else:
                glyphs.append(0)

        local_beg = 9999999
        local_end = -1

        for i, val in enumerate(glyphs):
            if val != 0:
                local_beg = i
                break

        for i in range(len(glyphs)):
            if glyphs[-(i + 1)] != 0:
                local_end = len(glyphs) - (i + 1)
                break

        if local_beg > local_end:
            continue

        glyphs = glyphs[local_beg:local_end + 1]
        real_end = beg + local_end
        real_beg = beg + local_beg

        page = (real_beg, real_end, f"{prefix}Glyphs_UnicodePage_{real_beg:04X}", desc)

        print(f"{page[2]}: @ {desc}")

        for i, glyph in enumerate(glyphs):
            if glyph == 0:
                print(f"    .4byte 0 @ '{chr(real_beg + i)}'")

            else:
                print(f"    .4byte 0x{glyph:08X} @ '{chr(real_beg + i)}'")

        pages.append(page)

    print(f"    .global {prefix}GlyphPages")
    print(f"    .type {prefix}GlyphPages, object")
    print(f"{prefix}GlyphPages:")

    for real_beg, real_end, label, desc in pages:
        print(f"    @ {desc}")
        print(f"    .4byte 0x{real_beg:04X}, 0x{real_end:04X}")
        print(f"    .4byte {label}")

    print(f"    @ end")
    print(f"    .4byte 0, 0, 0")

    for key in font_glyphs:
        if key not in processed_keys:
            print(f"@ ERROR: {key:04X} unmapped!")

def print_font_new(font_glyphs, prefix):
    keys = [k for k in font_glyphs]
    keys.sort()

    print(f"    .global Unicode{prefix}Font")
    print(f"    .type Unicode{prefix}Font, object")
    print(f"Unicode{prefix}Font:")

    for key in keys:
        print(f"    .4byte 0x{key:04X}, 0x{font_glyphs[key]:08X} @ '{chr(key)}'")

    print(f"    .global Unicode{prefix}FontEnd")
    print(f"    .type Unicode{prefix}FontEnd, object")
    print(f"Unicode{prefix}FontEnd:")
    print("")

def main(args):
    try:
        cvt_txt = args[1]
        fe6_gba = args[2]

    except IndexError:
        sys.exit(f"Usage: {args[0]} cp932.txt fe6.gba")

    with open(cvt_txt, 'r') as f:
        byte_info_tab = cvttab.decode_byte_map(f)

    with open(fe6_gba, 'rb') as f:
        talk_font = decode_font(f, 0x085A82B0, byte_info_tab)
        print_font_new(talk_font, "Talk")

        system_font = decode_font(f, 0x0859027C, byte_info_tab)
        print_font_new(system_font, "System")

if __name__ == '__main__':
    main(sys.argv)
