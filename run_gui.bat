@echo off
setlocal

echo Checking Java installation...
java -version >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo Java not found. Please install Java and try again.
    goto :eof
)

echo Checking Java compiler...
javac -version >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo Java compiler not found. Please install Java Development Kit (JDK) and try again.
    goto :eof
)

if not exist lib mkdir lib

if not exist lib\sqlite-jdbc-3.36.0.3.jar (
    echo Downloading SQLite JDBC driver...
    powershell -Command "Invoke-WebRequest -Uri 'https://github.com/xerial/sqlite-jdbc/releases/download/3.36.0.3/sqlite-jdbc-3.36.0.3.jar' -OutFile 'lib\sqlite-jdbc-3.36.0.3.jar'"
    if %ERRORLEVEL% NEQ 0 (
        echo Failed to download SQLite JDBC driver. Please check your internet connection and try again.
        goto :eof
    )
)

echo Compiling Java code...
javac -cp ".;lib\sqlite-jdbc-3.36.0.3.jar" HospitalManagementGUI.java
if %ERRORLEVEL% NEQ 0 (
    echo Compilation failed.
    goto :eof
)

echo Running Hospital Management GUI...
java -cp ".;lib\sqlite-jdbc-3.36.0.3.jar" HospitalManagementGUI

endlocal 