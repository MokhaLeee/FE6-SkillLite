# Build in WSL & Ubuntu:
1. You must have a linux system as WSL(for Windows user, see [here](https://learn.microsoft.com/en-sg/windows/wsl/install)) or Ubuntu.
2. You must have a copy of the FE6 clean ROM named `fe6.gba` in the repository directory.
3. Install [.Net SDK](https://learn.microsoft.com/en-us/dotnet/core/install/linux-ubuntu#2004)
4. Build tools:
```
./build_tools.sh
```
5. `make -j8` in repository directory, then you will get **fe6-chax.gba** in your repo.


# Advantage on working on FE6

1. Only 8MB occupied by Vanilla and result in a more flexible space control.

2. Succinct system without any check on Nightmare or eggs.

3. Scalability on system design with lots of free-space on item/unit/class attr and others.

# Wizardy to-do list:
- [x] **skill-system**
	- [x] skill infos
	- [x] skill stat-screen
	- [x] skill ROM list
	- [x] skill RAM list
- [ ] **status-getter**
	- [x] modular status getter
	- [ ] mov & con getter
- [ ] **battle-system**
	- [x] pre-battle calculation
	- [ ] battle order
	- [x] battle can-counter
	- [ ] weapon tri-angle
	- [ ] effective judgement
	- [ ] battle forcast
- [ ] **weapon range**
	- [ ] weapon-range getter
	- [ ] draw-string
	- [ ] fill-map functions rework
	- [ ] check can cover range
	- [ ] staff range rework
- [x] **chapter-based random-number system**
- [ ] **stat-screen**
	- [x] UI rework
	- [ ] negative stat boosts UI
- [ ] **str / mag split**
	- [ ] combat hack
	- [ ] unit magic power getter
	- [ ] check cap
	- [ ] auto-level
	- [ ] level-up screen (map-anim)
	- [ ] level-up screen (banim)
	- [ ] magic booster item
- [ ] **promotion list**
- [ ] **buff & debuff rework**
	- [ ] unit-status rework
	- [ ] unit-status UI
	- [ ] HP bars
- [ ] **item effect rework**
	- [ ] bm effect
	- [ ] prep-screen effect
- [x] **save-data**
	- [x] expanded modular save
	- [x] null-bwl
	- [x] bwl-support
- [ ] **combat-arts**
	- [ ] combat-art infos
	- [ ] combat-art tester
	- [ ] combat-art prep-screen selection
	- [ ] combat-art battle-forcast selection
- [ ] **prep-screen rework**
	- [ ] prep-screen menu-items reorder
	- [ ] skill prep-screen selection
	- [ ] combat-art prep-screen selection
- [ ] **combat anims**
	- [ ] skill & combat-art activation animations
	- [ ] map banim item effects
- [x] **unit-menu**
- [x] **unit-action**
- [x] **icon-rework**
- [ ] **popup-rework**
- [x] **load unit hook**
- [x] **battle-unit hook**
- [x] **chapter init hook**
- [ ] **level-up rework**
	- [ ] Switch & 3DS style level up
	- [ ] level-up hook
	- [ ] promotion hook
	- [ ] modular growth getter
- [ ] **post-action procs**
- [x] **debug system**
	- [x] fail-screen (by StanH)
	- [x] debug-text move to SRAM free-space

# Credits:
* [StanH](https://github.com/StanHash) and his arts: [FE6-Decomp](https://github.com/StanHash/fe6), [FE6-Wizardry](https://github.com/StanHash/fe6-wizardry)

* [laqieer](https://github.com/laqieer) and his [FE8U-Decomp work](https://github.com/laqieer/fireemblem8u) and advices.

* All of FEU friends and SkillSystem developers.
