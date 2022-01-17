import sys, re

class ByteInfo:
    def __init__(self, i):
        self.single_byte = i
        self.double_byte = {}

def decode_byte_map(f):
    byte_info_tab = [ByteInfo(i) for i in range(0x100)]

    for line in f.readlines():
        line = line[:line.find("#")]
        line = line.strip()

        if len(line) == 0:
            continue

        m = re.match(r"0x(?P<sjis>\w+)\s+(?P<unicode>\w+)", line)

        if m:
            sjis_val = int(m.group('sjis'), base = 16)
            unic_val = int(m.group('unicode'), base = 16)

            if sjis_val < 0x100:
                byte_info_tab[sjis_val].single_byte = unic_val

            else:
                byte_0 = 0xFF & (sjis_val >> 8)
                byte_1 = 0xFF & (sjis_val)

                byte_info_tab[byte_0].single_byte = 0
                byte_info_tab[byte_0].double_byte[byte_1] = unic_val

    return byte_info_tab

def tablist(byte_map):
    result = [0 for _ in range(0x100)]

    for byte in byte_map:
        result[byte] = byte_map[byte]

    beg = 0xFF
    end = 0

    for i, val in enumerate(result):
        if val != 0:
            beg = i
            break

    for i in range(len(result)):
        if result[-(i + 1)] != 0:
            end = len(result) - (i + 1)
            break

    return (beg, end, result[beg:end+1])

def main(args):
    try:
        cvt_txt = args[1]

    except IndexError:
        sys.exit(f"Usage: {args[0]} cp932.txt")

    with open(cvt_txt, 'r') as f:
        byte_info_tab = decode_byte_map(f)

    tables = {}

    print("    .global Utf8TranscoderSjisToUnicodeTable")
    print("    .type Utf8TranscoderSjisToUnicodeTable, object")
    print("Utf8TranscoderSjisToUnicodeTable:")

    for i, byte_info in enumerate(byte_info_tab):
        print(f"    @ entry {i:02X}")

        if byte_info.single_byte == 0 and i != 0:
            beg, end, tab = tablist(byte_info.double_byte)

            table_name = f"tab_{i:02X}"

            tables[table_name] = tab

            print(f"    .2byte 0")
            print(f"    .byte {beg}, {end}")
            print(f"    .4byte {table_name} - {beg*2}")

        else:
            print(f"    .2byte 0x{byte_info.single_byte:04X}")
            print(f"    .byte 0, 0")
            print(f"    .4byte 0")

    print("")

    for table_name in tables:
        table = tables[table_name]

        print(f"{table_name}:")

        for val in table:
            print(f"    .2byte 0x{val:04X}")

        print("")

    #for i in range(0x100):
        #if byte_info_tab[i].single_byte == 0:
        #    _, _, tab = tablist(byte_info.double_byte)

        #    print(f"tab_{i:02X}:")

        #    for val in tab:
        #        print("    .2byte 0x{val:04X}")

if __name__ == '__main__':
    main(sys.argv)
