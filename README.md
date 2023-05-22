# Schelling's Segregation Model

This repository contains an implementation of Schelling's Segregation Model in C. The model simulates the segregation behavior of agents in a grid-based environment.

## Authors

- Paige Johnson
- Bryce Anthony

## Functionality

The program reads a text file containing the initial configuration of the grid and parameters for the simulation. It then simulates the segregation process according to the specified rules. The output is printed to the console.

## Installation

To compile and run the program, follow these steps:

1. Ensure you have a C compiler installed (e.g., GCC).
2. Clone this repository or download the source code file.
3. Open a terminal and navigate to the project directory.
4. Compile the source code using the following command:

   ```shell
   gcc -o schelling schelling.c
   ```

5. Run the program with the following command:

   ```shell
   ./schelling <filename> <verbosity_level>
   ```

   - `<filename>`: Path to the text file containing the initial configuration and simulation parameters.
   - `<verbosity_level>`: An integer value (0, 1, or 2) indicating the verbosity of the program's output.

## File Structure

The project consists of a single source code file, `schelling.c`, which contains the following functions:

- `fileToArray`: Helper function to create an array from a file.
- `printArray`: Helper function to print the contents of the array.
- `placeAgents`: Helper function to place agents in the array.
- `agentsToMove`: Helper function to calculate the satisfaction ratio of an agent's neighbors.
- `checkRatio`: Helper function to create an array of dissatisfied agent locations.
- `movingAgents`: Helper function to move agents to new positions.
- `schellingModel`: The main function that runs the simulation.
- `main`: The entry point of the program.

## Usage

The program expects a text file as input, which contains the following information:

1. Dimensions of the grid (number of rows and columns).
2. Number of iterations for the simulation.
3. Satisfaction threshold.
4. Number of cells initially occupied by agents.
5. Initial configuration of the grid, where `$` represents an agent and `.` represents an empty cell.

An example input file `small.txt` is provided in this repository.

The `<verbosity_level>` parameter controls the output verbosity:
- `0`: Only the final grid configuration is printed.
- `1`: Each grid configuration for every iteration is printed.
- `2`: Each grid configuration is printed with a delay between iterations.

## License

This project is licensed under the [MIT License](LICENSE).
