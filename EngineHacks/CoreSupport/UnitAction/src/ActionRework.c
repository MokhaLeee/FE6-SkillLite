#include "proc.h"
#include "unit.h"

#include "action.h"

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
	gActiveUnit->state |= US_HAS_MOVED;
	return TRUE;
}

bool ActionDefualt(ProcPtr proc)
{
	return TRUE;
}
