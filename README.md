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

## carray.h

Dynamic and Type-Safe Arrays for C.
The ```carray.h``` module provides a flexible wrapper around standard C arrays, allowing for dynamic resizing, multiple data types, and built-in searching and sorting algorithms. It manages memory allocation and reallocations automatically.

## Supported Data Types
- TYPE_INT (Integer)
- TYPE_FLOAT (Float)
- TYPE_DOUBLE (Double)
- TYPE_CHAR (Character)
- TYPE_STRING (String/Character Pointer)

## Module Documentation

### Initialization and Memory
- ```create_array(size, type)```: Allocates a new array structure and data buffer.
- ```create_filled_array(size, type)```: Creates an array and populates it with random values.
- ```fill_array(arr, ...)```: Uses variadic arguments to populate an array with specific values.
- ```free_array(arr)```: Properly deallocates the array and its internal data (including individual strings for TYPE_STRING).

### Element Manipulation
- ```add_new_element(data, arr)```: Resizes the array and appends a new element to the end.
- ```push_element_at_pos(pos, data, arr)```: Overwrites an element at a specific index.
- ```delete_element_at_pos(pos, arr)```: Removes an element and shifts subsequent elements to fill the gap.
- ```get_element_at_pos(pos, arr)```: Returns a pointer to the element at the specified index.

### I/O and Interaction
- ```print_array(arr)```: Outputs the entire array to the console in a formatted block.
- ```get_array_input(arr)```: Prompts the user to fill the array via stdin.
- ```get_size(arr)```: Returns the current number of elements in the array.

### Algorithms
- ```search_pos_by_value(value, arr, indexes, count)```: Finds all occurrences of a value and returns their positions.
- ```search_value_exists(value, arr)```: Returns 1 if the value is present, otherwise 0.
- ```sort_array(arr)```: Sorts the array in ascending order using a recursive Quick Sort algorithm.

## Usage Example
```
// Create a dynamic list of strings
array *list = create_array(0, TYPE_STRING);

// Add elements
char *name = "Aritra";
add_new_element(&name, list);

char *college = "NIT Durgapur";
add_new_element(&college, list);

// Sort and Print
sort_array(list);
print_array(list);

// Clean up
free_array(list);
```
## Implementation Details
The library uses a Lomuto partition scheme for Quick Sort and handles type-casting internally to provide a clean API. When using TYPE_STRING, the library performs a strdup during input to ensure memory safety.
## Examples
To know more about carray.h useage follow this repo link given below:
https://github.com/PaperCodeGithub/array-operations-C
