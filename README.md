# COMP_3400_Project: Hospital Management System 

Introduction:
HOSPTIAL!

How to use:
_ Run main.cpp

ISSUES:
_ 

FUTURE:
_ Add GUI using Qt
_ Could need figma as a demo

TODO:
_ main.cpp: Add a cli in main.cpp (while loop that takes cmd)

_ Program: program read data from hospital.db to fill the vector first

_ Patient, Doctor, Nurse class: 
    + All these class has-a each other. Check the class file for details
    + Also add an attribute that said which Hospital each class is admitted
    

_ Patient class:
    + Add an enum in Patient member that indicate the Patient status: Dead, Alive, Critical, Recovering, FUBAR
    + Find a way to increase daysInHospital by time

_ Doctor class:
    + Patient will remain admitted until Doctor discharged?

_ Pharmacy.cpp: Do thing with it?
_ HospitalManager: overload addHospital(Hospital* h) method with pointer to Hospital