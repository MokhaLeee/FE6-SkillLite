import sys, re

def read_int(input, count, signed = False):
    return int.from_bytes(input.read(count), byteorder = 'little', signed = signed)

def main(args):
    try:
        rom_gba = args[1]
        first_offset = int(args[2], base = 0) & 0x1FFFFFF
        last_offset = int(args[3], base = 0) & 0x1FFFFFF

    except IndexError:
        sys.exit(f"Usage: {args[0]} fe6.gba first_menu_offset last_menu_offset")

    with open(rom_gba, 'rb') as f:
        for offset in range(first_offset, last_offset, 0x24):
            f.seek(offset + 8)
            entries_addr = read_int(f, 4)

            printed = set()

            for i in range(999):
                entry_offset = (entries_addr & 0x1FFFFFF) + i * 0x24

                f.seek(entry_offset + 12)
                available_addr = read_int(f, 4)

                if available_addr == 0:
                    break

                f.seek(entry_offset)
                addr = read_int(f, 4)

                if addr in printed:
                    continue

                printed.add(addr)
                print(f"{addr:08X} Menu_{offset + 0x08000000:08X}_Entry_{i}")

if __name__ == '__main__':
    main(sys.argv)
