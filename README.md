# ELECTROL-VOTING-MACHINE-USING-8051
This project implements an Electronic Voting Machine (EVM) using an 8051 microcontroller. The system allows users to securely cast votes for multiple candidates, view voting results, and maintain a voter log. The project includes password authentication to restrict access to voting and results display.


Features:

Voting for 4 Candidates (A, B, C, D)

Password Authentication for secured access

Live Vote Counting

Voter Log Display

LCD Display for user interaction

Keypad Input for password authentication and voting


Hardware Requirements:

8051 Microcontroller (AT89C51)

16x2 LCD Display

4x3 Keypad

Push Buttons for vote casting and results display

Power Supply (5V)


Software Requirements:

Keil uVision (for coding in Embedded C)

Proteus (for simulation)

8051 Compiler



Installation & Usage:

1. Compiling the Code

    Open Keil uVision.

    Load the provided evm2.c file.

    Compile and generate the HEX file.

2. Simulating in Proteus

    Open Proteus and load the evm2.pdsprj file.

    Attach the compiled HEX file to the 8051 microcontroller.

    Run the simulation to test the functionality.

How It Works:

Authentication: The system prompts the user to enter a 4-digit password before accessing the voting system.

Voting: Press a button to vote for a candidate.

Stopping Voting: Press the Stop Voting button when voting ends.

Results Display: Press the Show Results button to view the vote count for each candidate.

Voter Log: Press the Show Voter Log button to see the order of votes cast.


Future Enhancements:

Implementing RFID-based authentication for voters.

Storing votes in non-volatile memory (EEPROM).

Wireless communication for real-time result updates.


Author:

Developed by SAI CHIRAG  for Embedded Systems coursework.
