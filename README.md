# Analysis-and-Design-2025
CS-300 Course Work:

## Overview

This repository contains artifacts from my work in CS 300: Data Structures and Algorithms. It includes my analysis of runtime and memory usage for different data structures from Project One and the C++ Advising Assistance Program from Project Two, which sorts and displays course information in alphanumeric order.

---

### What was the problem you were solving in the projects for this course?

The main problem was to design and implement an advising assistance program that could efficiently store, search, and display course information for a university’s computer science department. I also needed to analyze how different data structures impact runtime and memory efficiency to make an informed design choice.


### How did you approach the problem?

I began by reviewing the different types of data structures—vectors, hash tables, and binary search trees—and analyzed their time and space complexity. I chose an **unordered_map (hash table)** because it provides fast O(1) average lookup and insertion times, which made it ideal for managing course data and prerequisites. Then, I built my program step by step—first reading from a CSV file, then loading data into the structure, sorting courses alphanumerically, and finally allowing users to look up specific courses.


### How did you overcome any roadblocks you encountered?

Some of the biggest challenges were related to file parsing and ensuring consistent data formatting, such as trimming extra spaces or handling case sensitivity in course searches. I overcame these issues by adding input validation, normalizing text by converting to uppercase, and testing the program with multiple input cases until it worked as expected.


### How has your work on this project expanded your approach to designing software and developing programs?

This project helped me appreciate the importance of **data structure selection** and **algorithm design** in real-world software. I learned how different design choices directly affect performance and how planning and pseudocode make coding smoother. I also started thinking more about scalability and how to design programs that can grow with larger datasets.


### How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?

I improved my use of consistent naming conventions, modular design, and inline comments. I also learned to handle user input errors gracefully and to design programs that are easy to update later. These habits will make my future programs more maintainable and professional.

---

### Artifacts Included

* **Project One:** Data Structure Runtime and Memory Analysis
* **Project Two:** Advising Assistance Program (`ProjectTwo.cpp`) – prints course list in alphanumeric order
