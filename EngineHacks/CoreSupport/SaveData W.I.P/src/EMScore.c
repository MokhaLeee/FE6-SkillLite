#include "bm.h"
#include "sram.h"
#include "save.h"
#include "EMS.h"

// SaveSu
void SaveSuspendedGame(unsigned slot){
	
	// if PrepScreen, return
	if (gPlaySt.flags & PLAY_FLAG_3)
		return;
	
	if ( !IsSramWorking() )
		return;
	
	void* const base = GetSaveTargetAddress(slot);
	
	// Actual save!
	for (const struct SaveChunkDecl* chunk = gSuspendSaveChunks; chunk->offset != 0xFFFF; ++chunk)
		if (chunk->save)
			chunk->save(base + chunk->offset, chunk->size);
	
	// Setup block metadata
	struct SaveBlockMetadata sbm;
	sbm.magic1 = SBM_MAGIC1_GAME;
	sbm.type   = SAVE_TYPE_SUSPEND;

	SaveMetadata_Save(&sbm, slot);
}




