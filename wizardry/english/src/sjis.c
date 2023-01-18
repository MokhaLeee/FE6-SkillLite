
#include "text.h"

/*
 * Changes to glyph array structure:
 *
 * Before this, the glyph array indexed glyphs based on the second SJIS byte starting at 0x40.
 * Now, the first 0x80 indices are used for ASCII characters, while the everything after that is indexed as before.
 */

extern struct Glyph const* const* const NuTextGlyphTable[];

static struct Glyph const* GetGlyph(u32 character)
{
    if (character < 0x80)
        return gActiveFont->glyphs[character];

    if (character < 0x100)
        return NULL;

    unsigned const byte_1 = 0xFF & (character >> 8);
    unsigned const byte_2 = 0xFF & (character);

    struct Glyph const* glyph = gActiveFont->glyphs[0x80 + (byte_2 - 0x40)];

    while (glyph)
    {
        if (glyph->sjis_byte_1 == byte_1)
            return glyph;

        glyph = glyph->next;
    }

    return GetGlyph(0x81A7);
}

void SetTextFontGlyphs(int glyph_set)
{
    gActiveFont->glyphs = NuTextGlyphTable[glyph_set];
}

char const* GetCharTextLen(char const* str, int* out_width)
{
    u32 character = *str++;

    if (character < 0x20)
    {
        *out_width = 0;
        return str;
    }

    struct Glyph const* glyph = NULL;

    while (!(glyph = GetGlyph(character)))
        character = (character << 8) + *str++;

    *out_width = glyph->width;

    return str;
}

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

char const* Text_DrawCharacter(struct Text* text, char const* str)
{
    u32 character = *str++;

    if (character < 0x20)
        return str;

    struct Glyph const* glyph = NULL;

    while (!(glyph = GetGlyph(character)))
        character = (character << 8) + *str++;

    gActiveFont->draw_glyph(text, glyph);

    return str;
}

void Text_DrawString(struct Text* text, char const* str)
{
    while (*str > 1)
        str = Text_DrawCharacter(text, str);
}
