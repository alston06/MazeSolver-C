# Maze Solver in C

This project implements a maze-solving algorithm in C, showcasing different approaches to finding paths in a maze. It demonstrates the use of data structures such as **linked lists**, **stacks**, and **queues** for pathfinding and backtracking. The program can find all possible paths in the maze and determine the shortest path using **Breadth-First Search (BFS)**.

---

## Features

1. **Dynamic Maze Input**: Accepts custom maze dimensions and configurations from the user.
2. **Pathfinding Algorithms**:
   - **Find All Paths**: Lists all possible paths from the start `(0, 0)` to the end of the maze.
   - **Shortest Path**: Calculates the shortest path using BFS.
3. **Data Structures**:
   - **Linked List**: Stores explored paths.
   - **Stack**: Used for backtracking operations.
   - **Queue**: Facilitates BFS traversal.
4. **Memory Management**: Dynamically allocates and frees memory for the maze, visited array, and path storage.

---

## Usage

### Input

1. **Maze Dimensions**: 
   - Enter the number of rows and columns.
2. **Maze Configuration**:
   - Input the maze row by row, where:
     - `0` represents a path.
     - `1` represents a wall.

### Output

- Displays the input maze.
- Lists all possible paths from the start to the end.
- Shows the shortest path (if one exists).

---

## Build and Run

### Prerequisites
- A C compiler (e.g., GCC).

### Steps

1. Clone the repository:
   ```bash
   git clone https://github.com/alston06/MazeSolver-C.git
Compile the program:

gcc v4.c
Run the program:

Example Input:
Enter number of rows in the maze: 3
Enter number of columns in the maze: 4
Enter the maze row by row (0 for path, 1 for wall):

0 1 0 0

0 1 1 0

0 0 0 0

Output:

Maze:

0 1 0 0

0 1 1 0

0 0 0 0


Finding all paths:

Path: (0, 0) -> (1, 0) -> (2, 0) -> (2, 1) -> (2, 2) -> (2, 3) -> END

Finding shortest path using BFS:
Shortest Path using BFS:
(0, 0) -> (1, 0) -> (2, 0) -> (2, 1) -> (2, 2) -> (2, 3) -> END


Contributing:

Contributions are welcome! Feel free to submit a pull request or open an issue for any improvements or bugs.



License:

This project is licensed under the MIT License.
