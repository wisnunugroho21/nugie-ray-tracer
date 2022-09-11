REM Build script for testbed
@ECHO OFF
SetLocal EnableDelayedExpansion

REM Get a list of all the .c files.
SET cFilenames=
FOR /R %%f in (*.cpp) do (
    SET cFilenames=!cFilenames! %%f
)

REM echo "Files:" %cFilenames%

SET assembly=engine
SET compilerFlags=
REM -Wall -Werror
SET includeFlags=-Isrc
SET linkerFlags=
SET defines=

ECHO "Building %assembly%%..."
clang++ %cFilenames% %compilerFlags% -o %assembly%.exe %defines% %includeFlags% %linkerFlags%