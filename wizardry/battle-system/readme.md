# 1. Function logic in vanilla
```
DoCombatAction
├── InitObstacleBattleUnit
├── BattleGenerateReal
│   └── BattleGenerateRealInternal
│       ├── InitBattleUnit                      ==> battle 2 unit hook
│       ├── SetBattleUnitWeapon
│       ├── BattleInitTargetCanCounter          ==> check can counter
│       ├── BattleApplyWeaponTriangleEffect     ==> WTA bonus
│       ├── BattleGenerate
│       │   ├── ComputeBattleUnitStats          ==> pre battle calc
│       │   │   ├── ...
│       │   │   ├── ComputeBattleUnitAttack
│       │   │   │   └── IsItemEffectiveAgainst  ==> effective attack
│       │   │   └── ...
│       │   ├── ComputeBattleUnitEffectiveStats
│       │   ├── ComputeBattleObstacleStats
│       │   └── BattleUnwind
│       │       ├── BattleGetFollowUpOrder
│       │       └── BattleGenerateRoundHits
│       │           ├── GetBattleUnitHitCount
│       │           └── BattleGenerateHit
│       └── BattleUnitTargetCheckCanCounter
└── ProcScr_CombatAction
    └── BattleApplyGameStateUpdates
        └── BattleApplyUnitUpdates
            └── UpdateUnitFromBattle            ==> battle 2 unit hook
```

# 2. Remember for potential obstacle target
In vanilla, function `InitObstacleBattleUnit()` init for this unit and function `ComputeBattleObstacleStats()` generate the real battle status after pre-battle calc.
You can judge for `bu->unit.pinfo->id == PID_WALL`.
