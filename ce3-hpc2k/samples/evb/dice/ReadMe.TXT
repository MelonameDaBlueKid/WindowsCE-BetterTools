Dice ReadMe
===========
This sample simulates a popular dice game and demonstrates the use of the PictureBox control.  The sample was adapted from the Webzee sample for VBScript for use with VBCE.  

Rules for Play
==============
Game play: A game consists of thirteen turns.  Each turn consists of three rolls of the dice.  After each turn you record the score for that turn on the scoreboard. After the first roll of each turn, you can choose to hold the value of individual dice in subsequent rolls by highlighting the dice with a single click.  After thirteen turns have been completed, your final score is tallied from the thirteen boxes.

Scoring: After you have finished your turn, you must record the turn on the scoreboard below the dice. The top row of the scoreboard tallies the quantity of a particular dice value.  For example, if you have finished your turn with three fours and two sixes, you could enter the roll in the "4's" box for a value of 12 (3x4) or you could enter the roll in the "6's" box for a value of 12 (2x6).  The bottom row of the scorecard tallies combinations of dice as listed below. If you choose to enter the value of your roll in a box and do not fill the requirements for scoring in that box, you will receive a score of zero in that box.  You can only enter the value of one turn in a scorecard box per game.

Combinations:
3 Kind-(Three of a kind) Three dice of the same value.
4 Kind-(Four of a kind) Four dice of the same value.
Sm Str-(Small Straight) Four dice of consecutive values (1, 2, 3, 4 or 2, 3, 4, 5).
Lg Str-(Large Straight) Five dice of consecutive values (1, 2, 3, 4, 5 or 2, 3, 4, 5, 6)
Full Hs-(Full House) Two of a kind and three of a kind (2, 2, 4, 4, 4).
Sweep-Five dice of the same value.
Chance-Sums the face value of the five dice.

To Install and Run the Sample
=============================
This application should run without further modification.

Additional Notes
================
This sample will run in the Windows CE emulator.

For information on the sndPlaySound API call see the Windows CE SDK Programmer's Reference and Guide.  For information on the PictureBox control see the Visual Basic for Windows CE online documentation.

