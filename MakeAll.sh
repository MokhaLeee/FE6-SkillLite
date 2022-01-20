# Credit for StanH

# On Init
base_dir=$(dirname "$(readlink -f "$0")")
Compile_Folder="$base_dir/EngineHacks/CoreHacks" 
main_event="$base_dir/Buildfile.event"
source_rom="$base_dir/FE6.gba"
target_rom="$base_dir/FE6-CHAX.gba"
ea_exe="$base_dir/Tools/EventAssembler/ColorzCore.exe"

# Compile C
echo "On Compiling C"
make clean
rm ./Tools/CLib/reference/Definitions.h.o
make lyn


# Download EA
cd Tools
git clone --recursive https://github.com/StanHash/EventAssembler.git
cd EventAssembler
./build.sh



# Assembling Tables
echo "Make C2EA"
cd "$base_dir/Tables"
rm *.event
python3 c2ea.py ../FE6.gba



# Assembling Text
echo "Make Text"
cd "$base_dir/Texts/strings"
python3 text-process-cn.py text_buildfile.txt InstallTextData.event TextDefinition.txt


# Make Hack
echo "Preparing ROM"
cp -f "$source_rom" "$target_rom"
echo "Assembling"
"$ea_exe" A FE8 "-output:$target_rom" "-input:$main_event"
echo "Done!"

