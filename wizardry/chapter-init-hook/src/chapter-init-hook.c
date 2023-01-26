#include "common-chax.h"
#include "proc.h"
#include "chapterinfo.h"
#include "event.h"
#include "map.h"
#include "bm.h"

#include "rng-ext.h"

typedef void (*cih_func)(ProcPtr proc);
extern cih_func ChapterInitHooks[];

void ChapterInitHookloop(ProcPtr proc)
{
    cih_func *it;

    /* Internal modular */
#ifdef CONFIG_RNG_EXT
    RandInitExt();
#endif

    /* External modular */
    for (it = ChapterInitHooks; *it; it++)
        (*it)(proc);
}
