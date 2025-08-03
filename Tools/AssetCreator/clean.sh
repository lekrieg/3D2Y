#!/bin/bash
OBJDIR_DEBUG=cmake-build-debug
OBJDIR_RELEASE=cmake-build-release

echo "Cleaning objects..."
find "$OBJDIR_DEBUG" -type f \( -name "*.o" -o -name "*.d" \) -exec rm -f {} \;
find "$OBJDIR_RELEASE" -type f \( -name "*.o" -o -name "*.d" \) -exec rm -f {} \;
echo "Done"
