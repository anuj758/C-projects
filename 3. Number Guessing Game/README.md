# 🎮 Number Guessing Game in C++

A beginner-friendly console application where the player attempts to guess a randomly generated number. It's a fun way to get hands-on experience with user input, control flow, and random number generation in C++.

---

## 🧩 Game Mechanics

- The program generates a random number using the system clock as a seed via `srand(time(0))`.
- The user is repeatedly prompted to enter a guess.
- After each guess, feedback is provided:
  - "Guessed number is too low" 🔽
  - "Guessed number is too high" 🔼
  - "Correct Answer" 🎉 when the guess is right

The game continues until the user guesses the correct number.

