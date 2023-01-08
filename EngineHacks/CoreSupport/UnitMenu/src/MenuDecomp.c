#include "common.h"

#include "action.h"
#include "proc.h"
#include "unit.h"
#include "menu.h"
#include "map.h"
#include "bm.h"
#include "text.h"
#include "event.h"

static const u8 sItemCountYOffsetLookup[12] = { 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 3, 3 };

// FE6 8042018+1
struct MenuProc* StartMenu_AndDoSomethingCommands(MenuInfo const* info, int x, int left, int right){
	struct MenuProc* result = StartMenuAdjusted(info, x, left, right);
	int i;

	if (result->entry_count <= 6)
		return result;

	result->rect.y -= sItemCountYOffsetLookup[result->entry_count];

	for (i = 0; i < result->entry_count; ++i)
		result->entries[i]->y -= sItemCountYOffsetLookup[result->entry_count];

	return result;
}


// ProcScr_PlayerPhase
static void StartMenuOnEvent(ProcPtr proc)
{
	if (gAction.id != ACTION_TRAPPED)
		// Hack here to reset menu location
		StartMenu_AndDoSomethingCommands(
			&MenuInfo_UnitMenu, 
			gBmSt.cursor_sprite_target.x - gBmSt.camera.x, 
			// 1, 22);
			1, 20);

	Proc_Break(proc);
}


// When start menu after apply movement
void PlayerPhase_BeginActionSelect(ProcPtr proc)
{
	gActiveUnit->x = gAction.x_move;
	gActiveUnit->y = gAction.y_move;

	UnitSyncMovement(gActiveUnit);

	if (!(gActiveUnit->state & US_HAS_MOVED) && gAction.id == ACTION_NONE && gBmSt.partial_actions_taken == 0)
		gAction.move_count = gMapMovement[gAction.y_move][gAction.x_move];

	ResetTextFont();

    if (RunPostMoveEvents() == TRUE){
		Proc_SetRepeatFunc(proc, StartMenuOnEvent);
		return;
	}

	if (gAction.id != ACTION_TRAPPED)
		// Hack here to reset menu location
		StartMenu_AndDoSomethingCommands(
			&MenuInfo_UnitMenu, 
			gBmSt.cursor_sprite_target.x - gBmSt.camera.x, 
			// 1, 22);
			1, 20);

	Proc_Break(proc);
}



// When come back unit menu


