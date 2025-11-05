@echo off
if exist build\TournamentSim.exe (
    call build\TournamentSim.exe
) else (
    echo TournamentSim.exe not found, running compile_run.bat

    call compile_run.bat
    if errorlevel 1 (
        echo Error: compile_run.bat failed, make sure you have CMake installed and your project has every dependency

        exit /b 1
    )
)