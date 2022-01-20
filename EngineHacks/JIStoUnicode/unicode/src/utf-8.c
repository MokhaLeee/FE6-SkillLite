#include <stdbool.h>
#include "text.h"


//#include "stan-failscreen.h"

struct UnicodeGlyphEnt
{
    u32 character;
    struct Glyph const* glyph;
};

struct UnicodeFontInfo
{
    struct UnicodeGlyphEnt const* beg;
    struct UnicodeGlyphEnt const* end;
};

extern struct UnicodeFontInfo const UnicodeFontInfoTable[];

u32 Utf8DecodeCharacter(char const** strptr)
{
    u32 byte_0, byte_1, byte_2, byte_3;

    byte_0 = *(*strptr)++;

    switch (byte_0 & 0xF0)
    {
        default:
            return byte_0;

        case 0x80: case 0x90: case 0xA0: case 0xB0:
            // continuation byte
            return 0;

        case 0xC0: case 0xD0:
            byte_0 = 0x1F & byte_0;
            byte_1 = 0x3F & *(*strptr)++;

            return (byte_0 << 6) + (byte_1);

        case 0xE0:
            byte_0 = 0x0F & byte_0;
            byte_1 = 0x3F & *(*strptr)++;
            byte_2 = 0x3F & *(*strptr)++;

            return (byte_0 << 12) + (byte_1 << 6) + (byte_2);

        case 0xF0:
            if ((byte_0 & 0x08) != 0)
            {
                return 0;
            }

            byte_0 = 0x07 & byte_0;
            byte_1 = 0x3F & *(*strptr)++;
            byte_2 = 0x3F & *(*strptr)++;
            byte_3 = 0x3F & *(*strptr)++;

            return (byte_0 << 18) + (byte_1 << 12) + (byte_2 << 6) + (byte_3);
    }

}

struct Glyph const* Utf8GetGlyph(u32 character)
{
    struct UnicodeFontInfo const* unicode_font_info = (struct UnicodeFontInfo const*) gActiveFont->glyphs;

    // binary search!

    // with vanilla glyph sets, this seems to take a maximum of 10 iterations to find the correct glyph
    // which is I think pretty good? a hash table may still be faster idk.

    // int iterations = 0;
	u32 m;
    u32 l = 0;
    u32 r = (unicode_font_info->end - unicode_font_info->beg) - 1;
    struct UnicodeGlyphEnt const* a = unicode_font_info->beg;

    while (l <= r)
    {
        m = (l + r) / 2;

        if (a[m].character < character)
        {
            l = m + 1;
        }
        else if (a[m].character > character)
        {
            r = m - 1;
        }
        else
        {
            break;
        }

        // iterations++;
    }
	return a[m].glyph;
}

// replaces
void SetTextFontGlyphs(int glyph_set)
{
    gActiveFont->glyphs = (struct Glyph const* const*) &UnicodeFontInfoTable[glyph_set];
}

// replaces
char const* GetCharTextLen(char const* str, int* out_width)
{
    u32 character = Utf8DecodeCharacter(&str);

    if (character < 0x20)
    {
        *out_width = 0;
        return str;
    }

    *out_width = Utf8GetGlyph(character)->width;

    return str;
}

// replaces
int GetStringTextLen(char const* str)
{
    int result = 0;

    while (*str > 1)
    {
        int tmp;
        str = GetCharTextLen(str, &tmp);

        result += tmp;
    }

    return result;
}

// replaces
char const* Text_DrawCharacter(struct Text* text, char const* str)
{
    u32 character = Utf8DecodeCharacter(&str);

    gActiveFont->draw_glyph(text, Utf8GetGlyph(character));

    return str;
}

// replaces
void Text_DrawString(struct Text* text, char const* str)
{
    while (*str > 1)
        str = Text_DrawCharacter(text, str);
}

// replaces
void Text_DrawNumber(struct Text* text, int number)
{
    if (number == 0)
    {
        Text_DrawCharacter(text, "0");
        return;
    }

    while (number != 0)
    {
        char buf = '0' + DivRem(number, 10);
        number = Div(number, 10);

        Text_DrawCharacter(text, &buf);

        text->x -= 15;
    }
}

// replaces
void Text_DrawNumberOrBlank(struct Text* text, int number)
{
    if (number == 0xFF || number == -1)
    {
        Text_Skip(text, -8);
        Text_DrawString(text, "ーー");

        return;
    }

    Text_DrawNumber(text, number);
}

static u32 log10(u32 number)
{
    if (number >= 100000000) return 9;
    if (number >= 10000000) return 8;
    if (number >= 1000000) return 7;
    if (number >= 100000) return 6;
    if (number >= 10000) return 5;
    if (number >= 1000) return 4;
    if (number >= 100) return 3;
    if (number >= 10) return 2;
    if (number >= 1) return 1;
    return 0;
}

// replaces
int NumberToString(int number, char* buf)
{
    u32 off, beg;

    off = 0;

    if (number == 0)
    {
        *buf++ = '0';
        *buf++ = '\0';
        return 1;
    }

    if (number < 0)
    {
        buf[off++] = '-';
        number = -number;
    }

    off += log10(number);
    beg = off;

    while (number > 0)
    {
        buf[off--] = '0' + DivRem(number, 10);
        number = Div(number, 10);
    }

    buf[beg + 1] = '\0';
    return beg + 1;
}





// Mokha Fix
char const* GetStringLineEnd(char const* str)
{
    while (*str > 1)
    {
        if (*str == 4)
        {
            str++;
            continue;
        }

        str += 1;
    }

    return str;
}
