import sys, re

def read_int(input, count, signed = False):
    return int.from_bytes(input.read(count), byteorder = 'little', signed = signed)

def main(args):
    try:
        rom_gba = args[1]
        offset = int(args[2], base = 0) & 0x1FFFFFF
        end_offset = int(args[3], base = 0) & 0x1FFFFFF

    except IndexError:
        sys.exit(f"Usage: {args[0]} fe6.gba begin_offset end_offset")

    count = (end_offset - offset) // 4

    with open(rom_gba, 'rb') as f:
        f.seek(offset)

        printed = set()

        for i in range(count):
            addr = read_int(f, 4)

            if addr in printed:
                continue

            printed.add(addr)
            print(f"{addr:08X} TableEntry_{i}")

if __name__ == '__main__':
    main(sys.argv)
