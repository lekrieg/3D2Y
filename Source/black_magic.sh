#!/bin/bash
CMD=$1
OBJDIR=Temp

clean_objects()
{
    echo "Cleaning objects..."
    find "$OBJDIR" -type f \( -name "*.o" -o -name "*.d" \) -exec rm -f {} \;
    echo "Done"
}

build_and_generate_files()
{
    echo "Building and generating clang files..."
    bear -- make -j$(nproc)
    echo "Done"
}

# MAIN BODY
if [[ "$CMD" == "clean" ]]; then
    clean_objects
elif [[ "$CMD" == "build" ]]; then
    build_and_generate_files
elif [[ "$CMD" == "all" ]]; then
    clean_objects
    build_and_generate_files
elif [[ "$CMD" == "run" ]]; then
    cd ..
    cd Game/linuxx86_64Debug/
    ./Game
elif [[ "$CMD" == "debug" ]]; then
    cd ..
    cd Game/linuxx86_64Debug/
    gdb ./Game
else
    echo "Invalid command. Please use 'clean', 'build', or 'all'."
fi
