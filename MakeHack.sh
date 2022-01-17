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


# Make Hack
echo "Preparing ROM"
cp -f "$source_rom" "$target_rom"
echo "Assembling"
"$ea_exe" A FE8 "-output:$target_rom" "-input:$main_event"
echo "Done!"

