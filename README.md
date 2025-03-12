# ComputerNetworks-Projects

## Assignment 1 - Two-Dimensional Parity Bits and CRC (Cyclic Redundancy Check)

This assignment contains two main problems illustrating fundamental error detection techniques in computer networks: **two-dimensional parity bits** and **Cyclic Redundancy Check (CRC)**.

---

## 🔹 Problem 1: Two-Dimensional Parity Bits

- The user inputs a binary string consisting of a multiple of 7 characters (validations are performed to ensure this condition).
- The message is placed in a matrix with **7 columns** and a variable number of rows (depending on the message length).
- Parity bits are computed for each row and column as follows:
  - If the number of `1`s in a row/column is **even**, a `0` is added.
  - If the number of `1`s is **odd**, a `1` is added.
  - The **most significant bit** is the one located in the **bottom-right corner** of the matrix.
- The final matrix, including parity bits, is displayed.
- **Error simulation:**  
  - A random position in the message is chosen, and the corresponding bit is flipped.
  - The receiver recalculates the parity bits and identifies the corrupted bit.
  - The program displays the **corrupted position**.

---

## 🔹 Problem 2: Cyclic Redundancy Check (CRC)

- The user inputs a binary message and a **generator polynomial** (with coefficients `0` and `1`).
- **Validations:**  
  - The message and the polynomial must be binary.
  - The message length must be greater than the number of coefficients in the generator polynomial.
- **Processing Steps:**  
  1. The message is **extended** by appending a number of `0`s equal to the degree of the polynomial.
  2. The program performs **successive XOR operations** between the extended message and the polynomial coefficients until the remainder length is strictly smaller than the polynomial length.
  3. The intermediate **XOR steps** are displayed.
  4. The final remainder is **added to the extended message** via XOR, with the remainder being positioned under the end of the extended message.
  5. The final result is displayed.

---

### 📌 Summary

- **Problem 1**: Displays a **matrix representation** of the message with row and column parity bits, simulates error corruption, and identifies the corrupted position.
- **Problem 2**: Shows a **step-by-step matrix representation** of the XOR operations and finally displays the **extended message** combined with the remainder from the polynomial division.

This project demonstrates basic **error detection techniques** used in computer networks.
