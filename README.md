# C-Zen Toolkit
A high-level utility library for C developers.

C-Zen is a comprehensive C toolkit designed to simplify common tasks such as string manipulation, dynamic array management, matrix math, mapping, and file I/O. It provides a clean, high-level interface to speed up development while maintaining C's raw performance.

## Core Modules

- cio.h: High-level I/O and file system utilities.
- carray.h: Type-safe generic dynamic arrays with built-in iterators.
- cstring.h: Advanced string manipulation (trim, replace, search and much more...).
- cmath.h: Matrix operations, expression evaluation, and math helpers.
- cmaps.h: Fast key-value pair storage using DJB2 hashing.

## Installation

1. Clone the repository.
2. Include the desired header files in your C source code.
3. Link the corresponding implementation files during compilation.

## cio.h Documentation

The cio.h header simplifies how you interact with the console and the file system.

### Input and Conversion
- ```cio_input(format, ...)```: Formatted prompt that returns a dynamically allocated string from stdin.
- ```to_int(str)```: Converts string to integer (wrapper for atoi).
- ```to_float(str)```: Converts string to float (wrapper for atof).

### File System Operations
- ```file_exists(path)```: Returns a boolean if the file exists.
- ```read_file(filename)```: Reads an entire file into a heap-allocated string.
- ```write_file(filename, format, ...)```: Creates/overwrites a file using formatted input.
- ```append_file(filename, format, ...)```: Appends formatted text to an existing file.
- ```delete_file(filename)```: Removes a file from the system.

### UI Utilities
- ```clear_screen()```: Cross-platform console clearing (Windows/Linux/macOS).
- ```print_progress(current, total)```: Renders a visual progress bar in the terminal.


## Usage Example (cio.h)
```
char *name = cio_input("Enter your name: ");
if (name) {
    write_file("user.txt", "User: %s", name);
    free(name);
}

if (file_exists("user.txt")) {
    char *content = read_file("user.txt");
    printf("File contents: %s\n", content);
    free(content);
}
```

## Author
Aritra, NIT Durgapur.
