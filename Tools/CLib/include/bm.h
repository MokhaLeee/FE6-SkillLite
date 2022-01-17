#pragma once

#include <stdbool.h>
#include "common.h"
#include "proc.h"

enum
{
    BM_FLAG_0 = (1 << 0),
    BM_FLAG_1 = (1 << 1),
    BM_FLAG_2 = (1 << 2),
    BM_FLAG_3 = (1 << 3),
    BM_FLAG_4 = (1 << 4),
    BM_FLAG_5 = (1 << 5),
    BM_FLAG_LINKARENA = (1 << 6),
};

enum
{
    PARTIAL_ACTION_RESCUE_TRANSFER = (1 << 0),
    PARTIAL_ACTION_TRADED = (1 << 1),
    PARTIAL_ACTION_SUPPLY = (1 << 2),
};

enum
{
    PLAY_FLAG_0    = (1 << 0),
    PLAY_FLAG_1    = (1 << 1),
    PLAY_FLAG_2    = (1 << 2),
    PLAY_FLAG_3    = (1 << 3),
    PLAY_FLAG_4    = (1 << 4),
    PLAY_FLAG_5    = (1 << 5),
    PLAY_FLAG_HARD = (1 << 6),
    PLAY_FLAG_7    = (1 << 7),
};


enum
{
    WEATHER_NONE,

    WEATHER_SNOW,
    WEATHER_SNOWSTORM,
    WEATHER_3,
    WEATHER_RAIN,
    WEATHER_FLAMES,
    WEATHER_SANDSTORM,
    WEATHER_CLOUDS,
}; 


enum
{
    MAP_CURSOR_DEFAULT,
    MAP_CURSOR_REGULAR,
    MAP_CURSOR_RED_MOVING,
    MAP_CURSOR_STRETCHED,
    MAP_CURSOR_RED_STATIC,
};

enum
{
    L_BMMAIN_INIT,
    L_BMMAIN_CHANGEPHASE,
    L_BMMAIN_2,
    L_BMMAIN_DURINGPHASE,
    L_BMMAIN_4,
    L_BMMAIN_5,
    L_BMMAIN_6,
    L_BMMAIN_STARTPHASE,
    L_BMMAIN_8,
};

struct BmSt
{
    /* 00 */ bool main_loop_ended;
    /* 01 */ i8 lock;
    /* 02 */ i8 lock_display;
    /* 03 */ u8 pad_03;
    /* 04 */ u8 flags;
    /* 05 */ // pad
    /* 06 */ u16 main_loop_end_scanline;
    /* 08 */ int pad_08;
    /* 0C */ struct Vec2 camera;
    /* 10 */ struct Vec2 camera_previous;
    /* 14 */ struct Vec2 cursor;
    /* 18 */ struct Vec2 cursor_previous;
    /* 1C */ struct Vec2 cursor_sprite_target;
    /* 20 */ struct Vec2 cursor_sprite;
    /* 24 */ struct Vec2 map_render_anchor;
    /* 28 */ struct Vec2 camera_max;
    /* 2C */ u16 inventory_item_overflow;
    /* 2E */ u16 convoy_item_overflow;
    /* 30 */ bool unk_30;
    /* 31 */ bool unk_31;
    /* 32 */ short unk_32;
    /* 34 */ short unk_34;
    /* 36 */ i8 unk_36;
    /* 37 */ i8 unk_37;
    /* 38 */ u8 alt_blend_a_ca;
    /* 39 */ u8 alt_blend_a_cb;
    /* 3A */ u8 alt_blend_b_ca;
    /* 3B */ u8 alt_blend_b_cb;
    /* 3C */ u8 unk_3C;
    /* 3D */ u8 partial_actions_taken;
    /* 3E */ u8 unk_3E;
    /* 3F */ i8 unk_3F;
};

struct PlaySt
{
    /* 00 */ u32 unk_00; // a time value
    /* 04 */ u32 unk_04; // a time value

    /* 08 */ int gold;
    /* 0C */ u8 save_slot;
    /* 0D */ u8 vision;
    /* 0E */ i8 chapter;
    /* 0F */ u8 faction;
    /* 10 */ u16 turn;
    /* 12 */ u8 x_cursor, y_cursor;
    /* 14 */ u8 flags;
    /* 15 */ u8 weather;
    /* 16 */ u16 support_gain;
    /* 18 */ u8 playthrough_id;
    /* 19 */ u8 ending_id:4;
    /* 1A */ u8 last_sort_id;
    /* 1B */ u8 unk_1B;

    /* 1C */ // option bits
    u32 unk_1C_1:1;
    u32 unk_1C_2:1;
    u32 unk_1C_3:2;
    u32 config_no_auto_cursor:1;
    u32 config_talk_speed:2;
    u32 config_walk_speed:1;
    u32 config_bgm_disable:1;
    u32 config_se_disable:1;
    u32 config_window_color:2;
    u32 unk_1D_5:1;
    u32 unk_1D_6:1;
    u32 config_no_auto_end_turn:1;
    u32 config_no_subtitle_help:1;
    u32 config_battle_anim:2;
    u32 config_battle_preview_kind:2;
    u32 unk_1E_5:1;
    u32 unk_1E_6:1;
    u32 debug_control_red:2;
    u32 debug_control_green:2;
    u32 unk_1F_3:6;
};

void OnVBlank(void);
void OnMain(void);
void LockGame(void);
void UnlockGame(void);
u8 GetGameLock(void);
void InitBmBgLayers(void);
void ApplySystemObjectsGraphics(void);
void ApplySystemGraphics(void);
void HandleMapCursorInput(u16 keys);
void HandleMoveMapCursor(int step);
void HandleMoveCameraWithMapCursor(int step);
u16 GetCameraAdjustedX(int x);
u16 GetCameraAdjustedY(int y);
u16 GetCameraCenteredX(int x);
u16 GetCameraCenteredY(int y);
void PutMapCursor(int x, int y, int kind);
void SetMapCursorPosition(int x, int y);
void PutSysArrow(int x, int y, u8 isDown);
void PutSysAButton(int x, int y, int palid);
bool CameraMoveWatchPosition(ProcPtr proc, int x, int y);
bool IsCameraNotWatchingPosition(int x, int y);
bool CameraMove_08016290(ProcPtr proc);
void Unused_08016344(int x, int y, int duration);
int GetActiveMapSong(void);
void StartMapSongBgm(void);

extern struct ProcScr ProcScr_BmMain[];
extern struct ProcScr ProcScr_CamMove[];

extern struct BmSt gBmSt;
extern struct PlaySt gPlaySt;
