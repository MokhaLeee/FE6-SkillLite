W.I.P to make a SkillLite-style buildfile for FE6.
See source code at [MokhaLeee@git](https://github.com/MokhaLeee/FE6-SkillLite)

# Compiling:

1. You must have a copy of the FE6 clean ROM named `fe6.gba` in the repository directory.
2. Install [devkitPro](https://devkitpro.org/wiki/Getting_Started) or [GNU Arm Embedded Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm).
```
# for Ubuntu/WSL users
apt install binutils-arm-none-eabi
```
3. Install EventAssembler:
```
# Install .Net SDK, see: https://learn.microsoft.com/en-us/dotnet/core/install/linux-ubuntu#2004
sudo apt install build-essential cmake re2c ghc cabal-install libghc-vector-dev libghc-juicypixels-dev && \
	cd tools && \
	git clone --recursive git@github.com:StanHash/EventAssembler.git && \
	cd EventAssembler && \
	./build.sh
```
4. Install PyTools:
```
cd tools &&\
	git clone --recursive git@github.com:StanHash/FE-PyTools.git
```
5. Install and build fe6 decompile project:
```
cd tools &&\
	git clone git@github.com:MokhaLeee/fe6.git &&\
	cd fe6 &&\
	cp ../../fe6.gba ./fe6-base.gba &&\
	cd tools &&\
	./install-agbcc.sh
```
6. Now your repo should has components as below:
```
./FE6-SkillLite
├── ./game-data
├── ./include
├── ./Tools
│   ├── ./EventAssembler
│   ├── ./fe6
│   └── ./FE-PyTools
├── ./wizardry
└── ./writans
```
7. `make -j8` in repository directory, then you will get **fe6-chax.gba** in your repo.

Q: `ModuleNotFoundError: No module named 'elftools'`

A: `sudo apt install python3-pip && pip install pyelftools`

# Advantage on working on FE6

1. Only 8MB occupied by Vanilla and result in a more flexible space control.

2. Succinct system without any check on Nightmare or eggs.

3. Scalability on system design with lots of free-space on item/unit/class attr and others.

# Wizardy to-do list:
- [ ] **skill-system**
	- [x] skill infos
	- [x] skill stat-screen
	- [x] skill ROM list
	- [ ] skill RAM list
	- [ ] skill prep-screen selection
	- [ ] skill activation animations
- [ ] **combat-arts**
	- [ ] combat-art infos
	- [ ] combat-art tester
	- [ ] combat-art prep-screen selection
	- [ ] combat-art battle-forcast selection
- [ ] **status-getter**
	- [x] modular status getter
	- [ ] mov & con getter
- [ ] **battle-system**
	- [ ] pre-battle calculation
	- [ ] battle order
	- [ ] battle can-counter
	- [ ] weapon tri-angle
	- [ ] effective judgement
	- [ ] battle forcast
- [ ] **stat-screen**
	- [x] UI rework
	- [ ] negative stat boosts UI
- [ ] **weapon range**
- [ ] **str / mag split**
- [ ] **promotion list**
- [ ] **buff & debuff rework**
	- [ ] unit-status rework
	- [ ] unit-status UI
	- [ ] HP bars
- [ ] **item effect rework**
	- [ ] bm effect
	- [ ] prep-screen effect
- [ ] **save-data**
	- [ ] expanded modular save
	- [x] null-bwl
	- [ ] bwl-support
- [x] **unit-menu**
- [x] **unit-action**
- [x] **icon-rework**
- [ ] **popup-rework**

# Credits:
* [StanH](https://github.com/StanHash) and his arts: [FE6-Decomp](https://github.com/StanHash/fe6), [FE6-+Wizardry](https://github.com/StanHash/fe6-wizardry)

* [laqieer](https://github.com/laqieer) and his [FE8U-Decomp work](https://github.com/laqieer/fireemblem8u) and advices.

* All of FEU friends and SkillSystem developers.