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
if [[ "$CMD" == "help" ]]; then
    echo "|clean| cleans the project"
    echo "|build| build everything"
    echo "|all| clean and build"
    echo "|run| intialize the game"
    echo "|editor| initialize the editor"
elif [[ "$CMD" == "clean" ]]; then
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
elif [[ "$CMD" == "editor" ]]; then
    cd ..
    cd EngineEditor/linuxx86_64Debug/
    ./EngineEditor
elif [[ "$CMD" == "debugG" ]]; then
    cd ..
    cd Game/linuxx86_64Debug/
    gdb ./Game
elif [[ "$CMD" == "debugE" ]]; then
    cd ..
    cd EngineEditor/linuxx86_64Debug/
    gdb ./EngineEditor
else
    echo "Invalid command. Please use 'clean', 'build', or 'all'."
fi
