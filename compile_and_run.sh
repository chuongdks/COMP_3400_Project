#!/bin/bash

# Check if java is installed
if ! command -v java &> /dev/null; then
    echo "Java not found. Please install Java and try again."
    exit 1
fi

# Check if javac is installed
if ! command -v javac &> /dev/null; then
    echo "Java compiler not found. Please install Java Development Kit (JDK) and try again."
    exit 1
fi

# Create lib directory if it doesn't exist
mkdir -p lib

# Check if sqlite-jdbc jar exists, download if not
if [ ! -f "lib/sqlite-jdbc-3.36.0.3.jar" ]; then
    echo "Downloading SQLite JDBC driver..."
    curl -L "https://github.com/xerial/sqlite-jdbc/releases/download/3.36.0.3/sqlite-jdbc-3.36.0.3.jar" -o "lib/sqlite-jdbc-3.36.0.3.jar"
    if [ $? -ne 0 ]; then
        echo "Failed to download SQLite JDBC driver. Please check your internet connection and try again."
        exit 1
    fi
fi

# Compile
echo "Compiling Java code..."
javac -cp ".:lib/sqlite-jdbc-3.36.0.3.jar" HospitalManagementGUI.java
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# Run
echo "Running Hospital Management GUI..."
java -cp ".:lib/sqlite-jdbc-3.36.0.3.jar" HospitalManagementGUI 