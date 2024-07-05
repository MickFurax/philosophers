# philosophers
This project is a C implementation of the classic Dining Philosophers problem, a synchronization problem that demonstrates the challenges of concurrency control in a multi-threaded environment.

## Problem Statement

The Dining Philosophers problem presents a scenario where multiple philosophers are seated at a circular table with a single fork placed between each pair. The philosophers alternate between thinking and eating. To eat, a philosopher needs to acquire the two forks adjacent to them. 

The challenge lies in designing a solution that prevents deadlock (where all philosophers are stuck holding one fork and waiting for the other) and starvation (where a philosopher is perpetually unable to acquire both forks).

## Solution Overview

This implementation addresses the Dining Philosophers problem using POSIX threads (pthreads) and mutexes to ensure synchronization and prevent race conditions. Here's a breakdown of the key components:

- **Philosophers:** Each philosopher is represented by a thread, allowing them to think and eat concurrently.
- **Forks:** Forks are represented by mutexes. Acquiring a fork is simulated by locking the corresponding mutex, and releasing a fork is simulated by unlocking the mutex.
- **Synchronization:** Mutexes are used to protect shared resources (the forks) from race conditions. Only one philosopher can hold a fork (i.e., have the corresponding mutex locked) at any given time.
- **Deadlock Prevention:**  The solution employs a strategy to prevent deadlock. Philosophers attempt to acquire the forks in a specific order (e.g., always picking up the left fork first). This ensures that if a philosopher acquires one fork, they will eventually be able to acquire the second fork and proceed to eat. 
- **Starvation Avoidance:**  The implementation includes mechanisms to avoid starvation, ensuring that no philosopher is indefinitely blocked from acquiring forks. This might involve techniques like prioritizing philosophers who have been waiting longer or using a fairness policy in fork acquisition.

## Code Structure

The code is organized into several files:

- **philo.h:** Contains the function prototypes, structure definitions, and necessary header includes.
- **main.c:** The main program file that parses input arguments, initializes data structures, creates philosopher threads, and manages the simulation.
- **srcs/utils/:** This directory contains utility functions for various tasks.
    - **data.c:** Functions for initializing and freeing data structures.
    - **philo.c:** Functions for creating and managing philosopher threads.
    - **action.c:** Functions simulating philosopher actions (eating, sleeping, thinking).
    - **time.c:** Functions for time-related operations.
    - **utils.c:**  General utility functions, including input validation.
    - **priority.c:** Functions to manage philosopher priority and prevent starvation.
    - **dead.c:** Functions to check for and handle philosopher death.

## Usage

To compile the program, use the provided Makefile:

```bash
make
```

To run the program, execute the following command with the required arguments:

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

- **number_of_philosophers:** The number of philosophers (and forks) to simulate.
- **time_to_die:** The time in milliseconds it takes for a philosopher to die of starvation.
- **time_to_eat:** The time in milliseconds it takes for a philosopher to eat.
- **time_to_sleep:** The time in milliseconds a philosopher sleeps after eating.
- **[number_of_times_each_philosopher_must_eat] (optional):** The number of times each philosopher must eat before the simulation ends. If not specified, the simulation runs indefinitely until a philosopher dies.

## Example

```bash
./philo 5 800 200 200 
```

This command will simulate 5 philosophers with the specified timings. The simulation will continue until a philosopher dies of starvation.
