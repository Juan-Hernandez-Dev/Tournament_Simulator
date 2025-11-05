@echo off
echo ========================================
echo    Tournament Simulator - Build Script
echo ========================================
echo.

echo [1/5] Checking environment...
if not exist "CMakeLists.txt" (
    echo Error: CMakeLists.txt not found in current directory
    echo Current directory: %CD%
    pause
    exit /b 1
)
echo Done.
echo.

echo [2/5] Cleaning previous build...
rmdir /S /Q "build" 2>nul
echo Done.
echo.

echo [3/5] Creating build directory...
mkdir build
cd build
echo Current directory: %CD%
echo Done.
echo.

echo [4/5] Running CMake configuration...
cmake .. -DCMAKE_BUILD_TYPE=Debug
if %ERRORLEVEL% NEQ 0 (
    echo CMake configuration failed!
    echo Please check if all required files are present
    cd ..
    pause
    exit /b 1
)
echo Done.
echo.

echo [5/5] Building project...
cmake --build . --config Debug
if %ERRORLEVEL% NEQ 0 (
    echo Build failed!
    cd ..
    pause
    exit /b 1
)
echo Done.
echo.

echo [6/5] Locating and running executable...
echo ========================================
echo Searching for executable...
echo Current directory: %CD%

if exist "Debug\TournamentSim.exe" (
    echo Found in Debug folder
    Debug\TournamentSim.exe
) else if exist "Release\TournamentSim.exe" (
    echo Found in Release folder
    Release\TournamentSim.exe
) else if exist "TournamentSim.exe" (
    echo Found in build root
    TournamentSim.exe
) else (
    echo Error: Could not find TournamentSim.exe
    echo Current directory: %CD%
    echo Listing files in current directory:
    dir
    echo.
    echo Listing files in Debug directory:
    dir Debug 2>nul
    echo.
    echo Listing files in Release directory:
    dir Release 2>nul
)

cd ..
echo.
echo Build process completed.
pause