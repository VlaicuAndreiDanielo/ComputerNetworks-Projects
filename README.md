# ComputerNetworks-Projects

## Assignment 1 - Two-Dimensional Parity Bits and CRC (Cyclic Redundancy Check)
---
This assignment contains two main problems illustrating fundamental error detection techniques in computer networks: **two-dimensional parity bits** and **Cyclic Redundancy Check (CRC)**.


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

## Assignment 2 - Token Passing in a Network
---
This code simulates the transmission of a token in a network of 10 computers arranged in a circle. The user can choose the direction of circulation (clockwise or counterclockwise), and the token is moved to a new, randomly chosen source and destination.

### Main Components:

- **Function `generateRandomIP`**  
  This function generates a random IP address in the form of four numbers separated by dots. A `set` is used to ensure that each IP address is unique.

- **Class `Computer`**  
  Each `Computer` object has an identifier (`id`), an IP address (`ip`), and a buffer (`buffer`) that stores the current message. This buffer is displayed to show the state of each computer in the network.

- **Structure `Token`**  
  The `Token` structure holds information about the token's state:  
  - `srcIP`: The IP address of the current source computer (the token's location).  
  - `destIP`: The IP address of the destination to which the message is transmitted.  
  - `message`: The message that needs to be transmitted.  
  - `isFree` and `delivered`: Boolean flags that indicate whether the token has returned to the source and whether the message has been delivered to the destination, respectively.

- **Function `printNetworkState`**  
  This function iterates over the vector of computers and displays the state of each computer (ID, IP address, and the content of the buffer, or `null` if the buffer is empty).

### Main Logic

1. **Network Initialization:**  
   - A seed is set for the `rand()` function using `time(0)`.
   - A vector of 10 computers is created, each with a randomly generated IP address and a unique ID (e.g., `C0`, `C1`, etc.).

2. **Choosing the Direction of Circulation:**  
   - The user selects whether the token will circulate clockwise or counterclockwise.

3. **Entering the Message:**  
   - The user inputs a test message that will be transmitted across the network.

4. **Simulating Token Transmission (10 Steps):**  
   - For each step, the buffers of all computers are reset and the network state is displayed.
   - A new source (`newSrc`) and a destination (`dest`) are randomly selected (ensuring that the destination is different from the source).
   - **First Iteration:**  
     - The token is placed directly at the newly chosen source. The variable `current` is set to the source's index, and `token.srcIP` is updated accordingly.
   - **Subsequent Iterations:**  
     - If the new source differs from the token's current source address, the token is moved from the old source to the new source. This process is performed using a `while` loop that moves through the computers in the chosen direction and displays the network state at each step.
   - Once the token reaches the new source, the destination of the token is set, the message is assigned, and the `isFree` and `delivered` flags are reset.

5. **Transmitting the Message:**  
   - A state mechanism (states 0, 1, and 2) is used to simulate the transmission process:
     - **State 0:** The token moves toward the destination. Once the destination is reached, the message is marked as delivered (`delivered = true`), and the process moves to state 1.
     - **State 1:** The token begins returning to the source. If it reaches the new source, the token is marked as free (`isFree = true`), and transmission stops for that step; otherwise, it transitions to state 2.
     - **State 2:** The token continues its return to the source until it is confirmed to have arrived.
   
6. **Updating the Position:**  
   - After each movement, the `current` index is updated using the formula `(current + direction + n) % n` to maintain the circularity of the network.

This implementation simulates a token-passing process in a network, where the token is moved from one source to another based on a chosen direction, then used to transmit a message from the source to the destination, and finally returns to the source after delivery.

---

## Assignment 3 - Sliding Window Protocol

This assignment simulates the **Sliding Window Protocol**, a reliable data transfer technique in networks for efficient and orderly packet transmission.

### Key Features:

- **Customizable Parameters in code**:
  - **Number of Packets**: Total packets to be sent.
  - **Window Size**: Defines how many packets can be sent before waiting for ACKs.
  - **Packet Loss Chance**: Simulates the probability of packet loss during transmission.
  - **ACK Loss Chance**: Simulates the probability that an acknowledgment is lost.

### Protocol Logic:

- The sender uses a sliding window and sends packets within the window range.
- The window slides forward **only when an acknowledgment for the first packet in the window** is received.
- If any packet or its acknowledgment is lost, a timeout triggers retransmission of that packet.
- This continues until **all packets are successfully acknowledged**.

### Output:

- The program prints:
  - The **order in which packets were received**.
  - The **correctly sorted list of packets**, verifying successful delivery.
---
### 📌 Summary

- **Problem 1.1**: Displays a **matrix representation** of the message with row and column parity bits, simulates error corruption, and identifies the corrupted position.
- **Problem 1.2**: Shows a **step-by-step matrix representation** of the XOR operations and finally displays the **extended message** combined with the remainder from the polynomial division.
- **Problem 2**: This program displays and simulates the transmission of a token in a network of 10 computers arranged in a circle.
- **Problem 3**: This project showcases how the Sliding Window Protocol handles packet and acknowledgment loss while ensuring complete and in-order delivery.

This project demonstrates basic **error detection techniques** used in computer networks and a **token simulation in a network**.
