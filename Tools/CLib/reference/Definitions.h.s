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
SET_FUNC Proc_Break, 0x8003E61
SET_FUNC Proc_SetRepeatFunc, 0x80049C9


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
SET_FUNC UnitSyncMovement, 0x8017C61


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
SET_DATA DecodeStringRamFunc, 0x003780 @ RAM function
SET_FUNC DecodeMsg, 0x8013AD1
SET_FUNC ResetTextFont, 0x800573D


@ event
SET_FUNC RunPostMoveEvents, 0x806B471


