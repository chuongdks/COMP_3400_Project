# Hospital Management System

A comprehensive hospital management system built in C++ with a Java GUI frontend. This system allows management of hospitals, patients, doctors, nurses, and pharmacies.

## Features

- Hospital management (add, view)
- Patient management (admit, discharge, view)
- Doctor management (add, assign, view)
- Nurse management (add, assign, view)
- Pharmacy management (add, deliver medicine, view bills)

## Components

### C++ Backend

The C++ backend provides the core functionality of the system:

- Hospital CRUD operations
- Patient management
- Staff (doctors & nurses) management
- Pharmacy integration with billing functionality

### Java GUI Frontend

The Java GUI provides a user-friendly interface for accessing all the features:

- Tab-based interface for different entity types
- Table views for data display
- Form-based data entry
- Integration with the SQLite database

## Requirements

### For C++ Backend

- C++ compiler (GCC or Clang recommended)
- SQLite3 library

### For Java GUI

- Java Development Kit (JDK) 8 or newer
- SQLite JDBC driver (automatically downloaded by the scripts)

## How to Run

### C++ Console Application

1. Compile the code:
   ```
   g++ -o hospital src/main.cpp -lsqlite3
   ```

2. Run the application:
   ```
   ./hospital
   ```

### Java GUI Application

#### On Windows

1. Double-click `run_gui.bat` or run it from the command prompt.
   This will automatically:
   - Check for Java installation
   - Download required dependencies
   - Compile the code
   - Run the application

#### On macOS/Linux

1. Make the script executable (if not already):
   ```
   chmod +x compile_and_run.sh
   ```

2. Run the script:
   ```
   ./compile_and_run.sh
   ```

## Database

The system uses SQLite for data storage. The database file is located at `db/hospital.db`.

## Pharmacy Functionality

The pharmacy system allows:
- Registering new pharmacies
- Tracking medicine deliveries to hospitals
- Managing billing between pharmacies and hospitals
- Viewing payment history

## Usage Examples

### Add a Hospital
1. Go to the "Hospitals" tab
2. Click "Add Hospital"
3. Enter the hospital name
4. Click OK

### Admit a Patient
1. Go to the "Patients" tab
2. Click "Admit Patient"
3. Select a hospital
4. Fill in patient details
5. Click OK

### Deliver Medicine
1. Go to the "Pharmacies" tab
2. Click "Deliver Medicine"
3. Select pharmacy and hospital
4. Enter medicine details and cost
5. Click OK

ISSUES:
_ GUI and CLI function may clash with each others
_ Some functionalities are not polish yet
