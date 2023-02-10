# Skill-System Dev

Skill system is a system that get additional effects to the game which can vary from person to person. A simplist skill-system may as this:

```c
bool skill_tester(struct Unit *unit)
{
    if (unit->pinfo->id == PID_ROY)
        return true;
    
    return false;
}
```

Then we will give Roy unique effect such as:

```c
int GetUnitPower(struct Unit * unit)
{
    int status;
    status = unit->pow + GetItemPowBonus(GetUnitEquippedWeapon(unit));

    if (skill_tester(unit))
        status += 2;
    
    return status;
}
```

Hack function `GetUnitPower()` by lyn and decomp reference, then you will give Roy a `pow + 2` buff.

That is just a prototype, maybe we would like to add other effects, such as `def + 2`, `atk + 6 when attacking somebody`, etc. So we need to introduce a index to identify each skill effect.

Thus, here we need to introduce a skill_index <---> unit matrix matrix for judgement. A simplist judgment method is via hard-coded ROM table as below:

```c
#define SKILL_LIST_SIZE 5

struct skill_list {
    u8 skills[SKILL_LIST_SIZE];
};

extern const struct skill_list skill_rom_list[0xFF];

bool skill_tester(struct Unit *unit, const u8 skill_id)
{
    int i;
    for (i = 0; i < SKILL_LIST_SIZE; i++) {
        if (skill_rom_list[unit->pinfo->id].skills[i] == skill_id)
            return true;
    }

    return false;
}
```

Thus, what we need to do is just introduce this consistant:

```c
#define SKILLID_POW_BONUS 0x1

const struct skill_list skill_rom_list[0xFF] = {
    [PID_ROY] = {
        .skills = {
            SKILLID_POW_BONUS,
        },
    },
};
```
