# Event Ticket Booking System with Seat-Category Pricing

Author: Nikhil Suthar  
Subject: Object Oriented Programming in C++ (OOPs)  
Language: C++  

---

## Project Description

This is an event ticket booking program written in C++ for concerts and seminars. The system handles bookings for different types of seat categories (Regular, VIP, and Student) where each category has its own pricing and convenience fee calculation.

The program blocks oversold seats using C++ exception handling and tracks the total tickets booked using static members.

---

## OOP Concepts Implemented

1. **Inheritance & Base Class:**
   - Base class `Ticket` contains common data like `ticketId`, `customerName`, `category`, and `basePrice`.
   - Three derived classes inherit from `Ticket`:
     - `RegularTicket`
     - `VIPTicket`
     - `StudentTicket`

2. **Virtual Functions & Overriding:**
   - The base class `Ticket` has a pure virtual function:
     ```cpp
     virtual double price() = 0;
     ```
   - Each derived class overrides `price()` to calculate the final price according to its own rules:
     - **Regular:** Base Price + 5% convenience fee.
     - **VIP:** Base Price + ₹300 (lounge & perks) + 10% convenience fee.
     - **Student:** Base Price - 20% discount + ₹20 flat convenience fee.

3. **Static Member Variable & Function:**
   - `static int totalTicketsSold;` is declared in class `Ticket` to keep track of total tickets booked across all categories.
   - `static int getTotalTicketsSold()` allows getting the count without an object.

4. **Constant Data Member:**
   - Inside the `Event` class, `const int venueCapacity;` represents the maximum capacity of the venue.
   - It cannot be modified once set, and is initialized using constructor member initializer list:
     ```cpp
     Event(string name, int capacity) : venueCapacity(capacity) { ... }
     ```

5. **Exception Handling:**
   - A custom exception class `OversoldException` is created.
   - If someone tries to book after venue capacity is full, or when a category has run out of seats, the program throws an `OversoldException`.
   - The exception is caught in `main()` using a `try-catch` block so the program does not crash.

---

## Category Pricing Summary

- **Regular Ticket:**
  - Base: ₹600
  - Fee: 5% (₹30)
  - Total: ₹630

- **VIP Ticket:**
  - Base: ₹1500
  - Lounge Perks: ₹300
  - Fee: 10% (₹150)
  - Total: ₹1950

- **Student Ticket:**
  - Base: ₹450
  - Discount: 20% (-₹90)
  - Fee: ₹20 flat
  - Total: ₹380

---

## How to Compile and Run

### 1. Terminal / Command Prompt (using g++)
```bash
g++ main.cpp -o ticket_app
./ticket_app
```
(On Windows Command Prompt or PowerShell, run `.\ticket_app.exe`)

### 2. Using Dev-C++ / Code::Blocks
1. Open Dev-C++ or Code::Blocks.
2. Open `main.cpp`.
3. Press `F11` (in Dev-C++) or `F9` (in Code::Blocks) to compile and run.

### 3. Using VS Code
1. Open the folder in VS Code.
2. Open terminal in VS Code (`Ctrl + ~`).
3. Compile using `g++ main.cpp` and run `a.exe` or `a.out`.

---

## Sample Program Output

### Menu & Booking:
```
========================================
   Event Ticket Booking System
   Made by: Nikhil Suthar
========================================
Event: College Live Concert 2026
Venue Capacity: 6 seats

1. Book Ticket
2. View Pricing Rules
3. View Venue Status
4. Show All Booked Tickets
5. Exit
Enter your choice (1-5): 1

Choose Category:
1. Regular (Base ₹600 + 5% fee)
2. VIP (Base ₹1500 + ₹300 perks + 10% fee)
3. Student (Base ₹450 - 20% discount + ₹20 fee)
Enter category (1-3): 2
Enter Attendee Name: Nikhil Suthar

----------------------------------------
Booking Confirmed for Nikhil Suthar!
Ticket ID    : #101
Category     : VIP
Final Price  : ₹1950 (Rs. 1950)
----------------------------------------
```

### Exception Triggered when Category is Full:
```
Choose Category:
1. Regular (Base ₹600 + 5% fee)
2. VIP (Base ₹1500 + ₹300 perks + 10% fee)
3. Student (Base ₹450 - 20% discount + ₹20 fee)
Enter category (1-3): 2
Enter Attendee Name: Rohan

[EXCEPTION CAUGHT] CATEGORY SOLD OUT: VIP tickets are completely sold out!
```

### Exception Triggered when Venue Capacity Reached:
```
Choose Category:
1. Regular (Base ₹600 + 5% fee)
2. VIP (Base ₹1500 + ₹300 perks + 10% fee)
3. Student (Base ₹450 - 20% discount + ₹20 fee)
Enter category (1-3): 1
Enter Attendee Name: Amit

[EXCEPTION CAUGHT] VENUE FULL: Total capacity of 6 seats reached for 'College Live Concert 2026'!
```

### Showing All Booked Tickets:
```
--- All Booked Tickets for College Live Concert 2026 ---
Ticket #101 | Nikhil Suthar | VIP | Base: ₹1500 | Final Amount: ₹1950 (Includes Lounge Perks)
Ticket #102 | Rahul | Regular | Base: ₹600 | Final Amount: ₹630
Ticket #103 | Priya | Student | Base: ₹450 | Final Amount: ₹380 (Student Discount Applied)
--------------------------------------------
```

---

## Author
Submitted by: Nikhil Suthar

