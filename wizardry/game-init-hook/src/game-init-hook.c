#include "common-chax.h"
#include "gamecontroller.h"
#include "bm.h"
#include "hardware.h"

#include "debug.h"

typedef int (*const gih_func)();
extern gih_func GameInitHooks[];

struct GameController {
    /* 00 */ PROC_HEADER;

    /* 29 */ u8 nextAction;
    /* 2A */ u8 nextChapter;
    /* 2B */ u8 demoCnt;
    /* 2C */ u8 previousDemoClassSet;
    /* 2E */ short clock;
};

void StartGame()
{
    gih_func *it;
    struct GameController *proc;

    SetMainFunc(OnMain);
    SetOnVBlank(OnVBlank);

    /* Internal modular */


    /* External modular */
    for (it = GameInitHooks; *it; it++)
        (*it)();

    proc = SpawnProc(ProcScr_GameController, PROC_TREE_3);

    proc->nextAction = GAME_ACTION_0;
    proc->nextChapter = 0;

    proc->demoCnt = 0;
}
