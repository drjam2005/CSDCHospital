# CSDCHospitalManagement

### Key Features

- [X] Key Features:
    - [X] Patient Record Management: Add, edit, view, & remove patient records.
    - [X] Doctor Management: Add, edit, view, & remove doctor records.
    - [X] Appointment Setting: Assign a patient to a doctor at a particular schedule.
    - [X] Treatment Recording: Record symptoms of a patient and the treatment given by his doctor on a certain appointment.
    - [X] Data persistence: Store records in a file for future use. When the program runs, it must load all existing data from the file.

##

### Person
- [x] Attributes
    - [x] ID Number
    - [x] Name
    - [x] Age
    - [x] Gender
- [x] Methods
    - [x] Constructor
    - [x] Getter and Setter Methods

### Patient (Inherits from Person)
- [X] Attributes
    - [X] Appointment and Symptoms
    - [X] Appointment and Treatments
    - [X] Doctor Assigned to Each Appointment
- [X] Methods
    - [X] Constructor
    - [X] Getter and Setter Methods

### Doctor (Inherits from Person)
- [X] Attributes
    - [X] Specalization
    - [X] Available Times
- [X] Methods
    - [X] Constructor
    - [X] Getter and Setter Methods

### Appointment
- [X] Attributes
    - [X] Appointment ID Number
    - [X] Patient ID
    - [X] Doctor ID
    - [X] Date and Time
- [X] Method
    - [X] Scheduling of Appointment
    - [X] Cancelling of Appointment
    - [X] View Appointment

### HospitalManager
- [X] Attributes
    - [X] Vector/Array of Patients
    - [X] Vector/Array of Doctors
    - [X] Strings for fileName saves
- [X] Methods
    - [X] Constructor to get existing patient and doctor records from file/s
    - [X] Method to save data into files.
    - [X] Methods to add, remove, search, and update a patient records
    - [X] Methods to add, remove, search, and update a doctor records
    - [X] Method/s to manage appointments

