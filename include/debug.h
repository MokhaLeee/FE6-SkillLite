#pragma once
#include <stdnoreturn.h>
#include "common-chax.h"

noreturn void FailScreen(void);

#ifdef CONFIG_USE_DEBUG_TEXT
void DebugInitBg(int bg, int vramOffset);
void DebugPutStr(u16 *tm, char const *str);
void DebugPutFmt(u16 *tm, char const *fmt, ...);
void GenNumberStr(int number);
void GenNumberOrBlankStr(int number);
void GenNumberHexStr(int number);
void DebugScreenInit(void);
void DebugPrintFmt(char const *fmt, ...);
void DebugPrintNumber(int number, int length);
void DebugPrintNumberHex(int number, int length);
void DebugPrintStr(char const *str);
void DebugPutScreen(void);
bool DebugUpdateScreen(u16 held, u16 pressed);
void DebugInitObj(int offset, int palid);
void DebugPutObjStr(int x, int y, char const *str);
void DebugPutObjNumber(int x, int y, int number, int length);
void DebugPutObjNumberHex(int x, int y, int number, int length);
#else
static inline void DebugInitBg(int bg, int vramOffset) {}
static inline void DebugPutStr(u16 *tm, char const *str) {}
static inline void DebugPutFmt(u16 *tm, char const *fmt, ...) {}
static inline void GenNumberStr(int number) {}
static inline void GenNumberOrBlankStr(int number) {}
static inline void GenNumberHexStr(int number) {}
static inline void DebugScreenInit(void) {}
static inline void DebugPrintFmt(char const *fmt, ...) {}
static inline void DebugPrintNumber(int number, int length) {}
static inline void DebugPrintNumberHex(int number, int length) {}
static inline void DebugPrintStr(char const *str) {}
static inline void DebugPutScreen(void) {}
static inline bool DebugUpdateScreen(u16 held, u16 pressed)
{
    return FALSE;
}
static inline void DebugInitObj(int offset, int palid) {}
static inline void DebugPutObjStr(int x, int y, char const *str) {}
static inline void DebugPutObjNumber(int x, int y, int number, int length) {}
static inline void DebugPutObjNumberHex(int x, int y, int number, int length) {}
#endif

// #include "debugtext.h"
