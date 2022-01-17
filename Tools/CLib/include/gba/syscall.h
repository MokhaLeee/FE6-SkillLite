#ifndef GUARD_GBA_SYSCALL_H
#define GUARD_GBA_SYSCALL_H

#define RESET_EWRAM      0x01
#define RESET_IWRAM      0x02
#define RESET_PALETTE    0x04
#define RESET_VRAM       0x08
#define RESET_OAM        0x10
#define RESET_SIO_REGS   0x20
#define RESET_SOUND_REGS 0x40
#define RESET_REGS       0x80
#define RESET_ALL        0xFF

void SoftReset(u32 resetFlags);

void RegisterRamReset(u32 resetFlags);

void VBlankIntrWait(void);

u16 Sqrt(u32 num);

u16 ArcTan2(i16 x, i16 y);

#define CPU_SET_SRC_FIXED 0x01000000
#define CPU_SET_16BIT     0x00000000
#define CPU_SET_32BIT     0x04000000

void CpuSet(const void *src, void *dest, u32 control);

#define CPU_FAST_SET_SRC_FIXED 0x01000000

void CpuFastSet(const void *src, void *dest, u32 control);

void BgAffineSet(struct BgAffineSrcData *src, struct BgAffineDstData *dest, i32 count);

void ObjAffineSet(struct ObjAffineSrcData *src, void *dest, i32 count, i32 offset);

void LZ77UnCompWram(u8 const* src, void* dst);

void LZ77UnCompVram(u8 const* src, void* dst);

void HuffUnComp(u8 const* src, void* dst);

void RLUnCompWram(u8 const* src, void* dst);

void RLUnCompVram(u8 const* src, void* dst);

void SoundBiasReset(void);
void SoundBiasSet(void);
int Div(int, int);
int DivRem(int, int);

#endif // GUARD_GBA_SYSCALL_H
