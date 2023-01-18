#ifndef SKILL_DEF_H
#define SKILL_DEF_H

// Status Getters(0x00)
#define SKILLID_HpBonus  0x01
#define SKILLID_StrBonus 0x02
#define SKILLID_MagBonus 0x03
#define SKILLID_SklBonus 0x04
#define SKILLID_SpdBonus 0x05
#define SKILLID_LckBonus 0x06
#define SKILLID_DefBonus 0x07
#define SKILLID_ResBonus 0x08
#define SKILLID_MovBonus 0x09

// Battle Status(0x10)
// Blow Skills
#define SKILLID_BlowDarting 0x12			// Darting Blow: 	AS +6
#define SKILLID_BlowDeath 0x13				// Death Blow: 		Str +6
#define SKILLID_BlowArmored 0x14			// Armored Blow: 	Def +6
#define SKILLID_BlowFiendish 0x15			// Fiendish Blow: 	Mag +6
#define SKILLID_BlowWarding 0x16			// Warding Blow: 	Res +6
#define SKILLID_BlowDuelist 0x17			// Duelist's Blow: 	Avo +20
#define SKILLID_BlowUncanny 0x18			// Uncanny Blow: 	Hit +30


// Battle Misc(0x20)
#define SKILLID_Vantage 0x20				// 待伏
#define SKILLID_Desperation 0x21			// 猛攻	
#define SKILLID_QuickRiposte 0x22			// 回击
#define SKILLID_CounterAttack 0x23			// 迎击
#define SKILLID_WindSweep 0x24				// 风扫
#define SKILLID_Discipline 0x25				// WpnExp*2


// Battle Status(0x30)
#define SKILLID_CritUp 0x30					// Crit+15

#endif // SKILL_DEF_H
