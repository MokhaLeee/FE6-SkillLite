#pragma once

//#include "global.h"

enum
{
    MAP_MOVEMENT_MAX = 120,
    MAP_MOVEMENT_EXTENDED = 124,
};

enum
{
    HIDDEN_BIT_UNIT = (1 << 0),
    HIDDEN_BIT_TRAP = (1 << 1),
};

void InitChapterMap(int chapter);
void InitChapterPreviewMap(int chapter);
void func_08019624(void);
void func_08019778(void);
void MapFill(u8** map, int value);
void MapSetEdges(u8** map, u8 value);
void UnpackChapterMap(void* into, int chapter);
void ApplyChapterMapGraphics(int chapter);
void ApplyChapterMapPalettes(void);
void InitBaseTilesBmMap(void);
void RefreshTerrainMap(void);
int GetBaseTerrainAt(int x, int y);
void PutMapMetatile(u16* tm, int x_tm, int y_tm, int x, int y);
void nullsub_8(void);
void PutLimitViewSquare(u16* tm, int x, int y, int x_tm, int y_tm);
void RenderMap(void);
void RenderMapForFade(void);
void UpdateRenderMap(void);
void RefreshEntityMaps(void);
char const* GetTerrainName(int terrain);
int GetTerrainHealAmount(int terrain);
int DoesTerrainHealStatus(int terrain);
void func_0801A278(void);
void RevertMapChange(int id);

extern struct Vec2 gMapSize;

extern u8** gMapUnit;
extern u8** gMapTerrain;
extern u8** gMapMovement;
extern u8** gMapRange;
extern u8** gMapFog;
extern u8** gMapHidden;
extern u8** gMapOther;

extern u8* gMetatilesTerrainLut;
extern u16** gMapMetatiles;
