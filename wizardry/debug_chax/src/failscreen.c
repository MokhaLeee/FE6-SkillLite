#include "common.h"
#include "common-chax.h"

#include "hardware.h"
#include "move.h"
#include "m4a.h"
#include "debug_chax.h"

#ifdef CONFIG_DEBUG

static void FailScreenOnVBlank(void)
{
    INTR_CHECK = INTR_FLAG_VBLANK;

    SyncDispIo();
    SyncBgsAndPal();
    ApplyDataMoves();
    m4aSoundVSync();
    m4aSoundMain();
}

noreturn void FailScreen(void)
{
    SetOnVBlank(FailScreenOnVBlank);
    gDispIo.disp_ct.mode = 0;
    gDispIo.disp_ct.forced_blank = 0;
    DebugInitBg(2, 0);
    RegisterVramFill(0, 0, 0x40);
    SetBgOffset(2, 0, 0);
    SetDispEnable(0, 0, 1, 0, 0);
    SetWinEnable(0, 0, 0);
    SetBlendNone();

    while (TRUE) {
        RefreshKeySt(gKeySt);
        DebugUpdateScreen(gKeySt->held, gKeySt->pressed);
        VBlankIntrWait();
        SoftResetIfKeyCombo();
    }
}

#endif /* CONFIG_DEBUG */
