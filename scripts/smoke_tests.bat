@echo off

set BUILD_TYPE=%1

if [%1] == [] set BUILD_TYPE=Debug

set SCRIPTS_DIR=%~dp0
set REPO_DIR=%SCRIPTS_DIR%..
set EXAMPLE_APPS_BIN_DIR=%REPO_DIR%\examples\build\%BUILD_TYPE%

echo ----- Running parsing example application -----
%EXAMPLE_APPS_BIN_DIR%\parsing_example_app.exe
echo ----- Parsing example application done -----

echo ----- Running running example application -----
%EXAMPLE_APPS_BIN_DIR%\running_example_app.exe
echo ----- Running example application done -----