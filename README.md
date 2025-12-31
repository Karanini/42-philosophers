# 42-philosophers

A multithreaded simulation of the classic Dining Philosophers problem, implemented in C using POSIX threads and mutexes.

## 📖 Project Description

This project is an implementation of the famous **Dining Philosophers Problem**, a classic synchronization problem in computer science. The simulation demonstrates how to handle concurrent processes, avoid deadlocks, and prevent race conditions using threads and mutexes. 

Philosophers sit at a round table with a bowl of spaghetti in the center. There are as many forks as philosophers on the table.  Each philosopher alternates between three states:  eating, thinking, and sleeping.  To eat, a philosopher needs to pick up both their left and right forks. 

The challenge is to ensure: 
- No philosopher starves (dies from not eating in time)
- No deadlocks occur
- Proper synchronization between threads

## 🚀 Features

- Thread-based simulation of multiple philosophers
- Mutex-based synchronization for fork access
- Death monitoring system
- Precise timing with 5 ms accuracy
- Support for optional meal count limitation
- Handles edge case of a single philosopher
- Thread-safe message printing

## 📋 Useful Resources

A bit of theory about threads and mutexes (quite important to understand what's at stake):
- [Nice Notion article](https://medium.com/@jalal92/the-dining-philosophers-7157cc05315) of Youtuber and ex-42 Oceano
- Chapters 29 and 30 of the excellent book [The Linux Programming Interface](https://maktabkhooneh.org/mag/wp-content/uploads/2022/02/The-Linux-Programming-Interface-Michael-Kerrisk.pdf) (from page 617)

A [video of Oceano](https://www.youtube.com/watch?v=zOpzGHwJ3MU) where he codes the simulation (do NOT watch if you want to give it a try yourself first)

Your favorite AI LLM, but works even better with a real human!! Trust me, you will remember better what you've learned if you talked to somebody than to some AI

Do not hesitate to contact me if you have any questions on this project :) 

## 🛠️ Building

The project uses a Makefile for compilation.  Simply run: 

```bash
make
```

This will compile the project and create a `philo` executable. 

### Available Make Commands

- `make` - Compile the project
- `make clean` - Remove object files
- `make fclean` - Remove object files and executable
- `make re` - Recompile the project from scratch

## 📋 Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Arguments

1. **number_of_philosophers**: The number of philosophers (and forks)
2. **time_to_die**: Time in milliseconds before a philosopher dies from starvation
3. **time_to_eat**: Time in milliseconds a philosopher takes to eat
4. **time_to_sleep**: Time in milliseconds a philosopher spends sleeping
5. **[number_of_times_each_philosopher_must_eat]**: (Optional) Number of meals each philosopher must eat before simulation ends

### Examples

```bash
# 5 philosophers, dies after 800ms, eats for 200ms, sleeps for 200ms
./philo 5 800 200 200

# Same but simulation ends when each philosopher has eaten 7 times
./philo 5 800 200 200 7

# Testing with 199 philosophers
./philo 199 310 100 100
```

## 📁 Project Structure

```
42-philosophers/
├── includes/
│   └── philo.h              # Header file with structures and function prototypes
├── src/
│   ├── main.c               # Entry point and main logic
│   ├── init_data.c          # Data structure initialization
│   ├── init_mutexes.c       # Mutex initialization and fork assignment
│   ├── init_threads.c       # Thread creation and management
│   ├── parsing.c            # Input argument validation
│   ├── wisdom_lovers_life.c # Main philosopher routine
│   ├── solitary_life.c      # Edge case: single philosopher
│   ├── monitor.c            # Death and meal completion monitoring
│   ├── utils.c              # Utility functions (atoi, death_flag management)
│   ├── utils_eat.c          # Fork locking and eating utilities
│   ├── utils_time.c         # Time-related utilities
│   └── cleanup.c            # Memory and mutex cleanup
├── Makefile                 # Build configuration
├── .gitignore               # Git ignore rules
└── en.subject.philo.pdf     # Project subject (in English)
```

## 🏗️ Implementation Details

### Data Structures

- **t_args**: Stores input arguments (times, philosopher count, meal limit)
- **t_philo**: Contains philosopher-specific data (ID, forks, meal count, thread ID, meal mutex)
- **t_data**: Global simulation data (all philosophers, mutexes, death flag)

### Key Components

1. **Initialization**: Sets up data structures, mutexes, and creates threads
2. **Philosopher Routine**: Each philosopher eats, sleeps and thinks in a loop
3. **Fork Management**: Uses mutexes to prevent multiple philosophers from using the same fork
4. **Monitoring Thread**: Continuously checks for philosopher deaths or meals completion
5. **Synchronization**: Death flag, meal counters, lifetime left of each philosopher and print statements protected by mutexes
6. **Cleanup**: Properly destroys mutexes and frees allocated memory

### Test Cases to Try

```bash
# No one should die
./philo 5 800 200 200

# A philosopher should die
./philo 4 310 200 100

# No one should die, simulation should stop when everyone has eaten 5 times
./philo 5 800 200 200 5

# One philosopher should die
./philo 1 800 200 200
```

## 👤 Author

**bkaras-g** - [Karanini](https://github.com/Karanini)

## 📜 License

This is a 42 School project. Please refer to 42's policies regarding code sharing and academic integrity. If you are a 42 student, feel free to take a look at the code to inspire yourself, but do not copy-paste! The objective is to learn something ;)

---

*Part of the 42 School curriculum - a project exploring concurrent programming, thread synchronization, and resource management.*
