#include "common-chax.h"
#include "debugtext.h"

#include <stdarg.h>

#include "hardware.h"
#include "move.h"
#include "oam.h"
#include "ramfunc.h"
#include "sprite.h"
#include "sram.h"

#include "constants/videoalloc_global.h"
extern u8 CONST_DATA Img_DebugFont[];

#ifdef CONFIG_USE_DEBUG_TEXT

struct DebugTextSramHead {
    /* 00 */ int vramOffset;
    /* 04 */ short bg;
    /* 06 */ u16 chr;

    /* 08 */ int hcur;
    /* 0C */ u32 vcur;
    /* 10 */ u32 vdisp;
};

struct DebugTextSramSt {
    struct DebugTextSramHead head;
    char screen[256][32];
};

void InitDebugTextData()
{
    int size, left_size = sizeof(struct DebugTextSramSt);
    u32 cur = DebugTextSramSt_ptr;

    while (left_size > 0) {
        size = left_size > sizeof(gBuf) ? sizeof(gBuf) : left_size;

        CpuFastFill16(0, gBuf, size);
        WriteAndVerifySramFast(gBuf, (u8 *)cur, size);

        left_size -= size;
        cur += size;
    }
}

struct DebugTextSramSt const * const gDebugTextSramSt = (void *)DebugTextSramSt_ptr;

void DebugInitBg(int bg, int vramOffset)
{
    struct DebugTextSramHead head;
    ReadSramFast((u8 *)gDebugTextSramSt, (u8 *)&head, sizeof(struct DebugTextSramHead));

    if (vramOffset == 0)
        vramOffset = BGCHR_DEBUGTEXT_DEFAULT * CHR_SIZE;

    SetBgChrOffset(bg, 0);
    SetBgScreenSize(bg, BG_SIZE_256x256);

    RegisterVramMove(Img_DebugFont, vramOffset, 0x40 * CHR_SIZE);

    PAL_BG_COLOR(0, 0) = RGB(0, 0, 0);
    PAL_BG_COLOR(0, 2) = RGB(31, 31, 31);

    EnablePalSync();

    TmFill(GetBgTilemap(bg), 0);

    head.bg = bg;
    head.vramOffset = vramOffset;
    head.chr = GetBgChrId(bg, vramOffset);
    
    WriteAndVerifySramFast((u8 *)&head, (u8 *)gDebugTextSramSt, sizeof(struct DebugTextSramHead));
}

void DebugPutStr(u16 *tm, char const *str)
{
    struct DebugTextSramHead head;
    ReadSramFast((u8 *)gDebugTextSramSt, (u8 *)&head, sizeof(struct DebugTextSramHead));

    while (*str) {
        *tm = *str > '`'
            ? *str - '`' + (head.chr + 0x20)
            : *str - ' ' + (head.chr);

        tm++;
        str++;
    }

    EnableBgSyncById(head.bg);
}

void DebugScreenInit()
{
    int i;
    struct DebugTextSramHead head;

    ReadSramFast((u8 *)gDebugTextSramSt, (u8 *)&head, sizeof(struct DebugTextSramHead));
    ReadSramFast((u8 *)gDebugTextSramSt->screen, gBuf, 256 * 32);

    for (i = 0; i < 256; i++)
        gBuf[i] = '\0';

    head.hcur = 0;
    head.vcur = 0;

    TmFill(gBg2Tm, 0);
    EnableBgSync(BG2_SYNC_BIT);

    WriteAndVerifySramFast(gBuf, (u8 *)gDebugTextSramSt->screen, 256);
    WriteAndVerifySramFast((u8 *)&head, (u8 *)gDebugTextSramSt, sizeof(struct DebugTextSramHead));
}

void DebugPrintStr(char const *str)
{
    struct DebugTextSramHead head;
    
    ReadSramFast((u8 *)gDebugTextSramSt, (u8 *)&head, sizeof(struct DebugTextSramHead));
    ReadSramFast((u8 *)gDebugTextSramSt->screen, gBuf, 256 * 32);

    while (*str) {
        char chr = *str;

        if (head.hcur == 0x30)
            chr = 0;
        else
            str++;

        if (chr == '\n')
            chr = 0;

        gBuf[(head.vcur & 0xFF) + head.hcur * 32] = chr;
        head.hcur++;

        if (chr == 0) {
            head.hcur = 0;
            head.vcur++;
        }
    }

    if (head.vcur > head.vdisp + 20)
        head.vdisp = head.vcur - 20;
    
    WriteAndVerifySramFast(gBuf, (u8 *)gDebugTextSramSt->screen, 256 * 32);
    WriteAndVerifySramFast((u8 *)&head, (u8 *)gDebugTextSramSt, sizeof(struct DebugTextSramHead));
}

void DebugPutScreen()
{
    u16 *tm;
    u16 chr;
    int ih, iv;
    struct DebugTextSramHead head;
    
    ReadSramFast((u8 *)gDebugTextSramSt, (u8 *)&head, sizeof(struct DebugTextSramHead));
    ReadSramFast((u8 *)gDebugTextSramSt->screen, gBuf, 256 * 32);

    TmFill(gBg2Tm, 0);

    for (iv = 0; iv < 20; iv++) {
        tm = gBg2Tm + TM_OFFSET(0, iv);

        for (ih = 0; gBuf[((iv + head.vdisp) & 0xFF) + ih * 32]; ++tm, ++ih) {
            chr = gBuf[((iv + head.vdisp) & 0xFF) + ih * 32];

            if (chr > '`')
                chr = chr - 0x40;
            else
                chr = chr - 0x20;

            *tm = chr + head.chr;
        }
    }

    EnableBgSync(BG2_SYNC_BIT);
}

bool DebugUpdateScreen(u16 held, u16 pressed)
{
    int top, bottom;
    struct DebugTextSramHead head;

    if (pressed & KEY_BUTTON_B)
        return FALSE;

    ReadSramFast((u8 *)gDebugTextSramSt, (u8 *)&head, sizeof(struct DebugTextSramHead));
    DebugPutScreen();

    top = head.vcur - 256;
    if (top < 0)
        top = 0;

    bottom = head.vcur - 20;
    if (bottom < 0)
        bottom = 0;

    if ((held & KEY_DPAD_UP) && top < head.vdisp)
        head.vdisp--;

    if ((held & KEY_DPAD_DOWN) && bottom > head.vdisp)
        head.vdisp++;

    WriteAndVerifySramFast((u8 *)&head, (u8 *)gDebugTextSramSt, sizeof(struct DebugTextSramHead));
    return TRUE;
}

#endif /* CONFIG_USE_DEBUG_TEXT */
