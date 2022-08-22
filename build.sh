# Build script for engine
set echo on

# Get a list of all the .c files.
cFilenames=$(find . -type f -name "*.cpp")

assembly="engine"
compilerFlags=""
# -fms-extensions 
# -Wall -Werror
includeFlags=""
linkerFlags=""
defines=""

echo "Building $assembly..."

rm -rf ./main ./image.ppm
clang++ $cFilenames $compilerFlags -o main $defines $includeFlags $linkerFlags