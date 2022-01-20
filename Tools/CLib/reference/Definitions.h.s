
@ FE6!


.macro SET_FUNC name, value
	.global \name
	.type   \name, function
	.set    \name, \value
.endm

.macro SET_DATA name, value
	.global \name
	.type   \name, object
	.set    \name, \value
.endm


@ lib-agb
SET_FUNC ArcTan2, 0x809DCD1
SET_FUNC BgAffineSet, 0x809DCD5
SET_FUNC CpuFastSet, 0x809DCD9
SET_FUNC CpuSet, 0x809DCDD
SET_FUNC Div, 0x809DCE1
SET_FUNC DivRem, 0x809DCE5
SET_FUNC HuffUnComp, 0x809DCED
SET_FUNC LZ77UnCompVram, 0x809DCF1
SET_FUNC LZ77UnCompWram, 0x809DCF5
SET_FUNC ObjAffineSet, 0x809DCF9
SET_FUNC RLUnCompVram, 0x809DCFD
SET_FUNC RLUnCompWram, 0x809DD01
SET_FUNC SoundBiasReset, 0x809DD1D
SET_FUNC SoundBiasSet, 0x809DD05
SET_FUNC Sqrt, 0x809DD2D
SET_FUNC VBlankIntrWait, 0x809DD31


@ Proc
SET_FUNC InitProcs, 0x8003909
SET_FUNC SpawnProc, 0x8003A05
SET_FUNC SpawnProcLocking, 0x8003AD9
SET_FUNC Proc_Break, 0x8003E61
SET_FUNC Proc_SetRepeatFunc, 0x80049C9



@ Game State & Chapter Data
SET_DATA gPlaySt, 0x0202AA48




@ Action
SET_DATA gAction, 0x203956C
SET_DATA ProcScr_CombatAction, 0x85C7D64

SET_FUNC DoAction, 0x802A029
SET_FUNC DoCombatAction, 0x802A30D
SET_FUNC DoItemAction, 0x8027F99
SET_FUNC DoRefreshAction, 0x802A371
SET_FUNC DoStealAction, 0x802A495
SET_FUNC DoRescueAction, 0x802A139
SET_FUNC DoRescueDropAction, 0x802A189
SET_FUNC DoTalkAction, 0x802A3C1
SET_FUNC DoSupportAction, 0x802A3ED


@ Menu
SET_DATA MenuInfo_UnitMenu, 0x85C7600

SET_FUNC StartMenu_AndDoSomethingCommands, 0x08042019
SET_FUNC StartMenuAdjusted, 0x80417E9
SET_FUNC StartMenu, 0x8041845



@ Unit
SET_DATA gActiveUnit, 0x30044B0

SET_FUNC GetUnit, 0x801860D
SET_FUNC GetUnitByPid, 0x8017ABD
SET_FUNC GetUnitCurrentHp, 0x8018389
SET_FUNC GetUnitMaxHp, 0x80183C9
SET_FUNC GetUnitPower, 0x80183E9
SET_FUNC GetUnitSkill, 0x8018409
SET_FUNC GetUnitSpeed, 0x8018449
SET_FUNC GetUnitDefense, 0x8018489
SET_FUNC GetUnitResistance, 0x80184A9
SET_FUNC GetUnitLuck, 0x80184D1
SET_FUNC GetUnitFid, 0x80184F1
SET_FUNC GetUnitEquippedWeaponSlot, 0x8016989
SET_FUNC UnitSyncMovement, 0x8017C61
SET_FUNC CountFactionUnitsWithoutState, 0x80209C9




@ item
SET_FUNC CanItemReachDistance, 0x80169BD
SET_FUNC IsItemEffectiveAgainst, 0x8016A11

SET_FUNC GetItemAttributes, 0x8017191
SET_FUNC GetItemUses, 0x80171A5
SET_FUNC GetItemMaxUses, 0x80171C9
SET_FUNC GetItemMight, 0x80171E9
SET_FUNC GetItemHit, 0x80171FD
SET_FUNC GetItemWeight, 0x8017211
SET_FUNC GetItemCrit, 0x8017225
SET_FUNC GetItemValue, 0x8017239
SET_FUNC GetItemMinRange, 0x801725D
SET_FUNC GetItemMaxRange, 0x8017271

SET_FUNC GetItemWeaponEffect, 0x80172F9



@ Battle
SET_DATA gBattleSt, 0x2039200
SET_DATA gBattleHitIt, 0x2039328
SET_DATA gBattleActor, 0x2039214
SET_DATA gBattleTarget, 0x2039290
SET_DATA gBattleUnitA, 0x2039214
SET_DATA gBattleUnitB, 0x2039290


SET_FUNC BattleGenerateSimulationInternal, 0x802407D
SET_FUNC BattleGenerateRealInternal, 0x8024145
SET_FUNC BattleGenerateSimulation, 0x8024249
SET_FUNC BattleGenerateReal, 0x8024281
SET_FUNC BattleGenerate, 0x80242C9
SET_FUNC BattleGenerateUiStats, 0x802430D
SET_FUNC SetBattleUnitWeapon, 0x80245A1

SET_FUNC ComputeBattleUnitStats, 0x8024791
SET_FUNC ComputeBattleUnitDefense, 0x8024845
SET_FUNC ComputeBattleUnitAttack, 0x802489D
SET_FUNC ComputeBattleUnitSpeed, 0x80248E9
SET_FUNC ComputeBattleUnitHitRate, 0x8024921
SET_FUNC ComputeBattleUnitAvoidRate, 0x8024959
SET_FUNC ComputeBattleUnitCritRate, 0x8024989
SET_FUNC ComputeBattleUnitDodgeRate, 0x80249C5
SET_FUNC ComputeBattleUnitSupportBonuses, 0x80247F1

SET_FUNC ClearBattleHits, 0x8024A89
SET_FUNC BattleUnwind, 0x8024AB5
SET_FUNC BattleGetFollowUpOrder, 0x8024B41
SET_FUNC BattleGenerateRoundHits, 0x8024BBD
SET_FUNC BattleGenerateHit, 0x8024FA9
SET_FUNC BattleApplyExpGains, 0x802503D
SET_FUNC BattleApplyUnitUpdates, 0x80254CD
SET_FUNC GetBattleUnitUpdatedWeaponExp, 0x8025555
SET_FUNC UpdateUnitFromBattle, 0x8025645
SET_FUNC GetBattleUnitExpGain, 0x8025881
SET_FUNC BattleApplyItemExpGains, 0x80258E9
SET_FUNC GetBattleUnitStaffExp, 0x8025941
SET_FUNC BattleApplyMiscActionExpGains, 0x80259A1
SET_FUNC BattleUnitTargetSetEquippedWeapon, 0x80259E5
SET_FUNC BattleUnitTargetCheckCanCounter, 0x8025A38
SET_FUNC BattleApplyWeaponTriangleEffect, 0x8025A91
SET_FUNC BattleInitTargetCanCounter, 0x8025B1D
SET_FUNC InitObstacleBattleUnit, 0x8025B89
SET_FUNC ComputeBattleObstacleStats, 0x8025BD9
SET_FUNC UpdateObstacleFromBattle, 0x8025C19
SET_FUNC BeginBattleAnimations, 0x8025C7D



@ Level Up
SET_FUNC CheckBattleUnitLevelUp, 0x8025105
SET_FUNC UnitPromote, 0x802529D





@ MAP_MAIN
@ SET_DATA ProcScr_PlayerPhase, 
SET_FUNC PlayerPhase_BeginActionSelect, 0x801BAF1



@ bm
SET_DATA gBmSt, 0x202AA08



@ map
SET_DATA gMapMovement, 0x202D20C




@ text
SET_DATA gActiveFont, 0x2027BCC

SET_FUNC Text_Skip, 0x8005A09
SET_DATA DecodeStringRamFunc, 0x3003780 @ RAM function
SET_FUNC DecodeMsg, 0x8013AD1
SET_FUNC ResetTextFont, 0x800573D
SET_FUNC SetTextFontGlyphs, 0x8005705
SET_FUNC GetStringTextLen, 0x8005B95
SET_FUNC GetCharTextLen, 0x8005C4D
SET_FUNC GetStringTextBox, 0x8005D05
SET_FUNC GetStringLineEnd, 0x8005D6D
SET_FUNC ClearText, 0x80058ED
SET_FUNC Text_SetColor, 0x8005A39
SET_FUNC Text_SetCursor, 0x80059E1
SET_FUNC Text_DrawString, 0x8005DA5
SET_FUNC Text_DrawCharacter, 0x8005F41
SET_FUNC Text_DrawNumber, 0x8005E79
SET_FUNC Text_DrawNumberOrBlank, 0x8005EFD
SET_FUNC Text_InsertDrawString, 0x8006455
SET_FUNC Text_SetParams, 0x8005A79
SET_FUNC PutText, 0x8005AB5
SET_FUNC SetTextFont, 0x8005769
@ SET_FUNC NumberToString, 
SET_FUNC GetStringTextCenteredPos, 0x8005CD9




@ event
SET_FUNC RunPostMoveEvents, 0x806B471



@ chapter info
SET_FUNC GetChapterInfo, 0x802BB0D


@ icon
SET_DATA sIconStTable, 0x20258EC
SET_DATA sIconDisplayList, 0x2025B6C
SET_DATA Img_Icons, 0x80F9D80
SET_DATA Pal_Icons, 0x80FED80

SET_FUNC PutIcon, 0x8004CF9
SET_FUNC GetIconChr, 0x8004BC1
SET_FUNC IconSlot2Chr, 0x8004B39
SET_FUNC GetNewIconSlot, 0x8004B61
SET_FUNC ClearIcon, 0x8004D91
SET_FUNC ClearIcons, 0x8004A65
SET_FUNC PutIconObjImg, 0x8004DD9




@ StatusScreen
SET_DATA gStatScreen, 0x2003108
SET_DATA gBmFrameTmap0, 0x2003238
SET_DATA gBmFrameTmap1, 0x2003C38
SET_DATA gProc_StatScreen, 0x8677680
SET_DATA gStatScreenDrawCallTable, 0x83195B8

SET_FUNC StartStatScreen, 0x80702BD
SET_FUNC DrawStatScreen, 0x806FFDD
SET_FUNC DrawStatScreenPage, 0x806F3DD
SET_FUNC DrawLeftStatScreen, 0x806EB49		@ Left Page
SET_FUNC DrawUnitStatScreen, 0x806ED35		@ Page 1
SET_FUNC DrawUnitItemScreen, 0x806EFE1		@ Page 2
SET_FUNC DrawUnitWeaponScreen, 0x806F325	@ Page 3

SET_FUNC StartStatScreenHelp, 0x807030D @ MakeStatScreenRText6C


@ HelpBox
SET_DATA HelpInfo_UnitPage, 0x8677824
SET_DATA HelpInfo_ItemPage, 0x8677A00
SET_DATA HelpInfo_WeaponPage, 0x8677BA4

SET_FUNC TryRelocateHbUp, 0x8070BED




@ HardWare
SET_DATA gBg0Tm, 0x2021B08	@ gBmFrameTmap0, gBg0MapBuffer
SET_FUNC EnableBgSync, 0x8000FD5
SET_FUNC TmFill, 0x8001551 @ FillBgMap





@ ram func
SET_FUNC DrawGlyphRam, 0x8003821
SET_FUNC DecodeStringRam, 0x800384D
SET_FUNC PutOamHiRam, 0x8003871
SET_FUNC PutOamLoRam, 0x800389D
SET_FUNC MapFloodCoreStepRam, 0x80038C9
SET_FUNC MapFloodCoreRam, 0x80038F1



@ m4a
SET_FUNC m4aSongNumStart, 0x809C861







@ save & sram
SET_DATA ReadSramFast, 0x3006640
SET_FUNC IsSramWorking, 0x8084271
SET_FUNC GetSaveTargetAddress, 0x8085F15
SET_FUNC GetSaveSourceAddress, 0x808460D
SET_FUNC SaveMetadata_Save, 0x80844D5
SET_FUNC SaveSuspendedGame, 0x80857B1
SET_FUNC LoadSuspendedGame, 0x80858E5





@ Misc
SET_FUNC RegisterDataMove, 0x8002B05
SET_FUNC RegisterDataFill, 0x8002B89


