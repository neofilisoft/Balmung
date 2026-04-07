@echo off

rem Copyright (c) Neofilisoft. All rights reserved.

if not exist "Development\Scripts\Windows\GetMSBuildPath.bat" goto Error_InvalidLocation

for %%I in (Source\Logo.png) do if %%~zI LSS 2000 (
	goto Error_MissingLFS
)

call "Development\Scripts\Windows\GetMSBuildPath.bat"
if errorlevel 1 goto Error_NoVisualStudioEnvironment

:Compile
md Cache\Intermediate >nul 2>nul
dir /s /b Source\Tools\Balmung.Build\*.cs >Cache\Intermediate\Balmung.Build.Files.txt
fc /b Cache\Intermediate\Build\Balmung.Build.Files.txt Cache\Intermediate\Build\Balmung.Build.PrevFiles.txt >nul 2>nul
if not errorlevel 1 goto SkipClean

copy /y Cache\Intermediate\Build\Balmung.Build.Files.txt Cache\Intermediate\Build\Balmung.Build.PrevFiles.txt >nul
%MSBUILD_PATH% /nologo /verbosity:quiet Source\Tools\Balmung.Build\Balmung.Build.csproj /property:Configuration=Release /target:Restore,Clean /property:RestorePackagesConfig=True /p:RuntimeIdentifiers=win-x64
:SkipClean
%MSBUILD_PATH% /nologo /verbosity:quiet Source\Tools\Balmung.Build\Balmung.Build.csproj /property:Configuration=Release /target:Build /property:SelfContained=False /property:RuntimeIdentifiers=win-x64
if errorlevel 1 goto Error_CompilationFailed

Binaries\Tools\Balmung.Build.exe %*
if errorlevel 1 goto Error_BalmungBuildFailed
exit /B 0

:Error_MissingLFS
echo CallBuildTool ERROR: Repository was not cloned using Git LFS
goto Exit
:Error_InvalidLocation
echo CallBuildTool ERROR: The script is in invalid directory.
goto Exit
:Error_NoVisualStudioEnvironment
echo CallBuildTool ERROR: Missing Visual Studio 2022 or newer.
goto Exit
:Error_CompilationFailed
echo CallBuildTool ERROR: Failed to compile Balmung.Build project.
goto Exit
:Error_BalmungBuildFailed
echo CallBuildTool ERROR: Balmung.Build tool failed.
goto Exit
:Exit
exit /B 1




