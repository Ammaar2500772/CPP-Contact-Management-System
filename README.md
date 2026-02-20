# C++ Contact Management System
A terminal-based CRUD (Create, Read, Update, Delete) application built in C++ that manages user contacts with local file persistence.

## Technical Highlights:
* **File I/O (`fstream`):** Capable of saving contacts to a `.txt` file and loading them back into memory upon program restart.
* **Input Validation:** Robust checks for phone number formatting (ensuring 11-digit integer input) and handling of `std::cin` failure states to prevent infinite loops/crashes.
* **String Manipulation:** Custom functions for case-insensitive searching and parsing string data.
* **Memory Management:** Utilizes structured arrays and pointers to manage the contact list efficiently in memory.
