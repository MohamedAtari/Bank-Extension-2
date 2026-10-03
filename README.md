# 🏦 Bank Management System - C++

A complete console-based Bank Management System built from scratch using C++.

This project simulates real banking operations with file-based storage, user authentication, and role-based permissions.

### ✨ Features

**👤 Client Management:**
- Show Client List (formatted table with setw)
- Add New Client (with duplicate check)
- Delete / Update / Find Client

**💸 Transactions Module:**
- Deposit
- Withdraw (with balance validation)
- Total Balances Report

**🔐 User & Security System:**
- Login System with 3 attempts lockout
- User Management (Add, Delete, Update, Find)
- Advanced Permissions System using Bitwise Operators
- Protect Admin from deletion

**💾 Data Persistence:**
- All data saved in `Client.txt` & `Users.txt` using custom delimiter `#//#`

### 🛠️ Tech Stack
- Language: C++ 
- Concepts: Structs, Vectors, Enums, File Handling (fstream), iomanip, Bitwise Operators
- Storage: Text Files

### 🚀 How to Run

1. Clone the repo
2. Open with Visual Studio / VS Code
3. Compile and Run `main.cpp`
4. Default Login -> Username: `Admin` | Password: `Admin` (you can create it in Users.txt as `Admin#//#Admin#//-1)

### 🔮 Future Improvements
- [ ] Refactor to OOP (Classes)
- [ ] Encrypt passwords
- [ ] Use Database instead of text files
- [ ] Add Transaction History Log

---
Developed by [Mohamed Atari](https://www.linkedin.com/in/your-profile) - Feedback is welcome!
