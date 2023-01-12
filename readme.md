W.I.P to make a SkillLite-style buildfile for FE6.
See source code at [MokhaLeee@git](https://github.com/MokhaLeee/FE6-SkillLite)

# Compiling:

1. You must have a copy of the FE6 clean ROM named `fe6.gba` in the repository directory.
2. Install [devkitPro](https://devkitpro.org/wiki/Getting_Started) or [GNU Arm Embedded Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm).
```
# for Ubuntu/WSL users
apt install binutils-arm-none-eabi
```
3. Install [Event-Assembler](https://github.com/StanHash/EventAssembler/releases/tag/1.0) and EA tools to this project. Just download the release and put them inside `<path-to-repo>/Tools/EventAssembler/`.
```
# for WSL user
cd Tools
wget https://github.com/StanHash/EventAssembler/releases/download/1.0/EventAssembler.zip
unzip EventAssembler.zip
rm EventAssembler.zip

# for Ubuntu user
# install .Net SDK: https://learn.microsoft.com/en-us/dotnet/core/install/linux-ubuntu#2004
cd Tools
git clone --recursive git@github.com:StanHash/EventAssembler.git
sudo apt install build-essential cmake re2c ghc cabal-install libghc-vector-dev libghc-juicypixels-dev
./build.sh
```
4. Install PyTools:
```
cd tools
git clone --recursive git@github.com:StanHash/FE-PyTools.git
```
5. Now your repo should has components as below:
```
├── ./EngineHacks
├── ./include
├── ./Tools
│   ├── ./CLib
│   ├── ./EventAssembler
│   └── ./FE-PyTools
├── ./Tables
└── ./Texts
```
6. `make`, then you will get **fe6-chax.gba** in your repo.

# Advantage on working on FE6

1. Only 8MB occupied by Vanilla and result in a more flexible space control.

2. Succinct system without any check on Nightmare or eggs.

3. Scalability on system design with lots of free-space on item/unit/class attr and others.

# Structure:

*  Core Support
	>+ Unit Action Rework
	>+ Unit Menu Rework
	>+ Icon Display
	>+ PopUp Rework (W.I.P)
	>+ Expanded Modular Save (W.I.P)
* Core Hacks
	>+ Battle System
		>>+ PreBattle Calc
		>>+ Check Can Counter
		>>+ Battle Unwind Rework
	>+ Modular Status Getter
* Skill System
	>+ Core
		>>+ SkillTester
	>+ Icon
	>+ Status Screen
		>>+ Skill Page
		>>+ Skill Help Box
	>+ Skill Installer
	>+ Skill Definitions
* JIS to Unicode (by StanH)

# Skill List:
| index | Name 	| Desc 	|
| ---	|---	|---	|
| 0x12	| Darting Blow 	| AS +6	as attacker	|
| 0x13	| Death Blow	| Str +6 as attacker |
| 0x14	| Armored Blow	| Def +6 as attacker |
| 0x15	| Fiendish Blow	| Mag +6 as attacker |
| 0x16	| Warding Blow	| Res +6 as attacker |
| 0x17	| Duelist's Blow| Avo +20 as attacker |
| 0x18	| Uncanny Blow	| Hit +30 as attacker |
| 0x20	| Vantage		| attack first when HP<50% as defender |
| 0x21	| Desperation	| double attack immediately if HP<50% as attacker |
| 0x22	| Quick Riposte	| attack double when HP>50% as defender |
| 0x23	| Counter Attack| can counter regardless of distance |
| 0x24	| Wind Sweep	| Target cannot counter as attacker but cannot double |
| 0x30	| Crit Boost	| crit+15% |


# Skill Tester:
For now can only judge for rom, cause for now I have no idea how to define Free-RAM-Space.

To Skill Tables are defined for now: one for character and one for class.

You can alse use NightMare to take skills to each unit.

# Credits:
* [StanH](https://github.com/StanHash) and his arts: [FE6-Decomp](https://github.com/StanHash/fe6), [FE6-+Wizardry](https://github.com/StanHash/fe6-wizardry)

* [laqieer](https://github.com/laqieer) and his [FE8U-Decomp work](https://github.com/laqieer/fireemblem8u) and advices.

* All of FEU friends and SkillSystem developers.