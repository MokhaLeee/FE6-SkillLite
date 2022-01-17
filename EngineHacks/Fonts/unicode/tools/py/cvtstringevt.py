import sys
import cvtstrings

def rom_words(f):
    while True:
        word = f.read(4)

        if word == b'':
            break

        yield int.from_bytes(word, byteorder = 'little', signed = False)

def main(args):
    try:
        rom_gba = args[1]
        str_txt = args[2]

    except IndexError:
        sys.exit(f"Usage: {args[0]} fe6.gba str.txt")

    with open(str_txt, 'r') as f:
        string_locations, _ = cvtstrings.parse_string_locations(f)

    print(f"PUSH")

    with open(rom_gba, 'rb') as f:
        last_word_offset = -999999

        for i, word in enumerate(rom_words(f)):
            word_offset = i * 4

            if word in string_locations:
                if word_offset != last_word_offset + 4:
                    print(f"    ORG ${word_offset:06X}")

                print(f"    POIN {string_locations[word]}")
                last_word_offset = word_offset

    print(f"POP")

if __name__ == '__main__':
    main(sys.argv)
