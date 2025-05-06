# CSDCHospitalManagement

## // TODO
### Key Features

- [ ] Key Features:
    - [ ] Patient Record Management: Add, edit, view, & remove patient records.
    - [ ] Doctor Management: Add, edit, view, & remove doctor records.
    - [ ] Appointment Setting: Assign a patient to a doctor at a particular schedule.
    - [ ] Treatment Recording: Record symptoms of a patient and the treatment given by his doctor on a certain appointment.
    - [ ] Data persistence: Store records in a file for future use. When the program runs, it must load all existing data from the file.

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
- [ ] Attributes
    - [ ] Appointment and Symptoms
    - [ ] Appointment and Treatments
    - [ ] Doctor Assigned to Each Appointment
- [ ] Methods
    - [ ] Constructor
    - [ ] Getter and Setter Methods

### Doctor (Inherits from Person)
- [ ] Attributes
    - [ ] Specalization
    - [ ] Available Times
- [ ] Methods
    - [ ] Constructor
    - [ ] Getter and Setter Methods

### Appointment
- [ ] Attributes
    - [ ] Appointment ID Number
    - [ ] Patient ID
    - [ ] Doctor ID
    - [ ] Date and Time
- [ ] Method
    - [ ] Scheduling of Appointment
    - [ ] Cancelling of Appointment
    - [ ] View Appointment

### HospitalManager
- [ ] Attributes
    - [ ] Vector/Array of Patients
    - [ ] Vector/Array of Doctors
    - [ ] Strings for fileName saves
- [ ] Methods
    - [ ] Constructor to get existing patient and doctor records from file/s
    - [ ] Method to save data into files.
    - [ ] Methods to add, remove, search, and update a patient records
    - [ ] Methods to add, remove, search, and update a doctor records
    - [ ] Method/s to manage appointments

## Other Class/es
### MainWindow
- [ ] // TODO
