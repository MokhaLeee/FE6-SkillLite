#include "common-chax.h"

#include "msg.h"
#include "ramfunc.h"

#include "macros.h"
#include "failscreen.h"

#include <string.h>

struct SjisToUnicodeEnt
{
    /* 00 */ u16 single_char;
    /* 02 */ u8 byterange_beg, byterange_end;
    /* 04 */ u16 const * lut;
};

extern struct SjisToUnicodeEnt const Utf8TranscoderSjisToUnicodeTable[];

u32 Sjis2Utf8CvtSjis(char const * * strptr)
{
    u32 byte_0 = *(*strptr)++;

    struct SjisToUnicodeEnt const * ent = &Utf8TranscoderSjisToUnicodeTable[byte_0];

    if (ent->single_char != 0)
    {
        return ent->single_char;
    }

    u32 byte_1 = *(*strptr)++;

    if (byte_1 < ent->byterange_beg || byte_1 > ent->byterange_end || ent->lut[byte_1] == 0)
    {
        DebugPrintStr("==============================\n");
        DebugPrintStr("===  UTF-8 TRANSCODE ERROR ===\n");
        DebugPrintStr("==============================\n");
        DebugPrintStr(" Failed to convert character\n");
        DebugPrintStr(" No Unicode character mapped\n");
        DebugPrintStr(" Bytes found: ");
        DebugPrintNumberHex(byte_0, 2);
        DebugPrintStr(" ");
        DebugPrintNumberHex(byte_1, 2);
        DebugPrintStr(" ...\n");
        DebugPrintStr(" Address: ");
        DebugPrintNumberHex(((int) (*strptr)) - 2, 7);
        DebugPrintStr("\n");
        FailScreen();
    }

    return ent->lut[byte_1];
}

void Sjis2Utf8WriteUtf8(char * * dst, u32 character)
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

static u32 my_strlen(char * str)
{
    u32 len = 0;

    while (str[len] != '\0')
    {
        len += 1;
    }

    return len;
}

void Sjis2Utf8(char * buf, int len)
{
    int orig_len = my_strlen(buf) + 1;

    // memmove(buf + len - orig_len, buf, orig_len);
    for (int i = orig_len - 1; i >= 0; i--)
    {
        buf[len - orig_len + i] = buf[i];
    }

    char * dst = buf;
    char const * src = buf + len - orig_len;

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
                Sjis2Utf8WriteUtf8(&dst, Sjis2Utf8CvtSjis(&src));
                continue;
        }
    }
}

// replaces
LYN_REPLACE_CHECK(DecodeStringRam);
void DecodeStringRam(char const * src, char * dst)
{
    if ((((u32) src) & 0x80000000) != 0)
    {
        strcpy(dst, (char const *) (((u32) src) & 0x7FFFFFFF));
    }
    else
    {
        extern void (* DecodeStringRamFunc)(char const * src, char * dst);

        DecodeStringRamFunc(src, dst);
        Sjis2Utf8(dst, 0x1000); // NOTE: assumes dst len is 0x1000
    }
}
