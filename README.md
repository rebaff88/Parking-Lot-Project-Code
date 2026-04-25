Parking Management System (C++ Project)

The Parking Management System is a console-based application developed in C++ to efficiently manage user accounts and parking-related operations. The purpose of this project is to demonstrate the practical implementation of Object-Oriented Programming (OOP) concepts along with file handling for persistent data storage. The system allows users to register, log in, and manage their accounts while maintaining records in a structured text file.

This project is divided among team members, where each member is responsible for a specific module. Member 1 handles the overall system design and architecture. Member 2 is responsible for user management and file handling, while Member 3 focuses on implementing parking operations logic. This division ensures modular development and better understanding of each component.

The system provides several key features including user sign-up, secure login functionality, logout option, and account deletion. During sign-up, user details such as name, password, and role (Admin or Customer) are stored in a file named RecordOfUserData.txt. For login, the system verifies the entered credentials by reading from the stored file data. Additionally, users can safely log out or delete their accounts, with proper file handling techniques used to update records without data corruption.

The project utilizes C++ programming language along with standard libraries such as iostream, fstream, and string. File handling plays a crucial role in storing and managing user data, while OOP principles are used to structure the system in a clean and organized way. The application runs entirely in a console environment and provides a simple user interface for interaction.

In terms of working logic, when a user signs up, their information is appended to a file. During login, the system reads and compares the input data with stored records. If the credentials match, access is granted; otherwise, appropriate error messages are displayed. For account deletion, a temporary file is created, and all data except the deleted user is copied into it. The original file is then replaced with the updated one to ensure safe deletion.

In the future, this system can be further improved by adding a graphical user interface (GUI), implementing password encryption for enhanced security, and integrating a database instead of text files for better scalability. Advanced role-based access control and real-time parking slot management can also be incorporated to make the system more robust and professional.
