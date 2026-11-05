# Memory Allocator
A custom memory allocator implemented in C that manages dynamic memory allocation using sbrk() and mmap(), depending on the requested allocation size. Uses Linked List to keep track of the memory allocations.

### Features
__Small Allocations (< 4KB):__ Uses sbrk() to allocate memory directly from the process heap.
__Large Allocations (>= 4KB):__ Uses mmap() to allocate memory through virtual memory pages.
__Dummy Calloc:__ Provides a calloc()-like implementation that allocates memory and initializes all bytes to zero.
__Custom Free:__ Implements a free() function to release previously allocated memory.

### Installation & Usage
1. Clone the Repository


```bash
git clone https://github.com/Tack-12/Memalloc.git
cd Memalloc
```

2. Compile

Build the executable using GCC:

```bash
gcc memalloc.c -o memalloc -pthread
```

You can also use another C compiler that supports the required system calls and threading library.

3. Run

Execute the compiled program:

```bash
./memalloc
```