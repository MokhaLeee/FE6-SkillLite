#include "common-chax.h"
#include "proc.h"
#include "chapterinfo.h"
#include "event.h"
#include "map.h"
#include "bm.h"

#include "rng-ext.h"

typedef void (*cih_func)(ProcPtr proc);
extern cih_func ChapterInitHooks[];

void PrepPhase_Init(ProcPtr proc)
{
    int i = 0;

    if (!GetChapterInfo(gPlaySt.chapter)->has_prep) {
        Proc_End(proc);
        return;
    }

    if (!(gPlaySt.flags & PLAY_FLAG_4)) {
        func_fe6_0807A07C();
        InitPlayerDeployUnits();

        gPlaySt.flags |= PLAY_FLAG_4;
    }

    gBmSt.flags |= BM_FLAG_4;
    gPlaySt.vision = GetChapterInfo(gPlaySt.chapter)->fog;

    /* Internal modular */
#ifdef CONFIG_RNG_EXT
    RandInitExt();
#endif

    /* External modular */
    while (ChapterInitHooks[i])
        ChapterInitHooks[i++](proc);

    RefreshEntityMaps();
    RenderMap();
}
