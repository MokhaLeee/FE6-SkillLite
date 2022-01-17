#include "msg.h"

#include <string.h>

struct SjisToUnicodeEnt
{
    /* 00 */ u16 single_char;
    /* 02 */ u8 byterange_beg, byterange_end;
    /* 04 */ u16 const* lut;
};

extern struct SjisToUnicodeEnt const Utf8TranscoderSjisToUnicodeTable[];

static u32 CvtSjis(char const** strptr)
{
    u32 byte_0 = *(*strptr)++;

    struct SjisToUnicodeEnt const* ent = &Utf8TranscoderSjisToUnicodeTable[byte_0];

    if (ent->single_char != 0)
    {
        return ent->single_char;
    }

    u32 byte_1 = *(*strptr)++;

    return ent->lut[byte_1];
}

static void WriteUtf8(char** dst, u32 character)
{
    switch (character)
    {
        case 0x00 ... 0x7F:
            *(*dst)++ = character;
            return;

        case 0x80 ... 0x7FF:
            *(*dst)++ = 0xC0 + ((character) >> 6);
            *(*dst)++ = 0x80 + ((character) & 0x3F);
            return;

        case 0x800 ... 0xFFFF:
            *(*dst)++ = 0xE0 + ((character >> 12));
            *(*dst)++ = 0x80 + ((character >> 6) & 0x3F);
            *(*dst)++ = 0x80 + ((character) & 0x3F);
            return;

        default:
            *(*dst)++ = 0xF0 + ((character >> 18));
            *(*dst)++ = 0x80 + ((character >> 12) & 0x3F);
            *(*dst)++ = 0x80 + ((character >> 6) & 0x3F);
            *(*dst)++ = 0x80 + ((character) & 0x3F);
            return;
    }
}

static void Sjis2Utf8(char* buf, int len)
{
    // int orig_len = strlen(buf) + 1;
    int orig_len = 0;
    while (buf[orig_len] != '\0')
    {
        orig_len += 1;
    }
    orig_len += 1;

    // memmove(buf + len - orig_len, buf, orig_len);
    for (int i = orig_len - 1; i >= 0; i--)
    {
        buf[len - orig_len + i] = buf[i];
    }

    char* dst = buf;
    char const* src = buf + len - orig_len;

    while (src != buf + len)
    {
        switch (*src)
        {
            case 0x00 ... 0x0F:
            case 0x11 ... 0x1C:
                *dst++ = *src++;
                break;

            case 0x10:
                *dst++ = *src++;
                *dst++ = *src++;
                *dst++ = *src++;
                break;

            case 0x80:
                *dst++ = *src++;
                *dst++ = *src++;
                break;

            default:
                WriteUtf8(&dst, CvtSjis(&src));
                continue;
        }
    }
}

// replaces
void DecodeStringRam(char const* src, char* dst)
{
    extern void(*DecodeStringRamFunc)(char const* src, char* dst);

    DecodeStringRamFunc(src, dst);
    Sjis2Utf8(dst, 0x1000);
}
