#ifndef SKILL_DEF_H
#define SKILL_DEF_H

// Status Getters(0x00)
#define SID_HpBonus  0x01
#define SID_StrBonus 0x02
#define SID_MagBonus 0x03
#define SID_SklBonus 0x04
#define SID_SpdBonus 0x05
#define SID_LckBonus 0x06
#define SID_DefBonus 0x07
#define SID_ResBonus 0x08
#define SID_MovBonus 0x09

// Battle Status(0x10)
// Blow Skills
#define SID_BlowDarting 0x12			// Darting Blow: 	AS +6
#define SID_BlowDeath 0x13				// Death Blow: 		Str +6
#define SID_BlowArmored 0x14			// Armored Blow: 	Def +6
#define SID_BlowFiendish 0x15			// Fiendish Blow: 	Mag +6
#define SID_BlowWarding 0x16			// Warding Blow: 	Res +6
#define SID_BlowDuelist 0x17			// Duelist's Blow: 	Avo +20
#define SID_BlowUncanny 0x18			// Uncanny Blow: 	Hit +30


// Battle Order(0x20)
#define SID_Vantage 0x20				// 待伏
#define SID_Desperation 0x21			// 猛攻	
#define SID_QuickRiposte 0x22			// 回击
#define SID_CloseCounter 0x23
#define SID_CounterAttack 0x24			// 迎击
#define SID_WindSweep 0x25				// 风扫
#define SID_WaryFighter 0x26
#define SID_DoubleLion 0x27

#define SID_SwordBreaker 0x28
#define SID_AxeBreaker 0x29
#define SID_LanceBreaker 0x2A
#define SID_BowBreaker 0x2B
#define SID_TomeBreaker 0x2C


// Battle Misc(0x30)
#define SID_CritUp 0x30					// Crit+15
#define SID_Discipline 0x31				// WpnExp*2

#endif // SKILL_DEF_H
