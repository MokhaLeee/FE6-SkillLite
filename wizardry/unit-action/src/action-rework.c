#include "common-chax.h"
#include "unit.h"
#include "action.h"
#include "proc.h"

typedef int (*ActionFunc) (ProcPtr);
extern const ActionFunc UnitActionCallTable[];

static int RequiresProcYield(ActionFunc func)
{
    const u32 raw = (u32)(func);
    return (raw >> 28) ? 1 : 0;
}

static ActionFunc FilterFunc(ActionFunc func)
{
    const u32 raw           = (u32)(func);
    const ActionFunc result = (ActionFunc)(raw & 0xFFFFFFF);

    return result;
}

LYN_REPLACE_CHECK(DoAction);
bool DoAction(ProcPtr proc)
{
    ActionFunc func;

    gActiveUnit = GetUnit(gAction.instigator);

    func = UnitActionCallTable[gAction.id];
    if (func) {
        if (RequiresProcYield(func)) {
            func = FilterFunc(func);
            func(proc);

            return FALSE;
        }

        return func(proc);
    }

    return TRUE;
}

bool WaitAction(ProcPtr proc)
{
    gActiveUnit->flags |= UNIT_FLAG_HAD_ACTION;
    return TRUE;
}

bool ActionDefualt(ProcPtr proc)
{
    return TRUE;
}
