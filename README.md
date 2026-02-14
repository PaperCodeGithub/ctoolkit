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

## C-Zen Toolkit: cio.h
The cio.h header simplifies how you interact with the console and the file system.

## Module Documentation

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

## C-Zen Toolkit: carray.h

Dynamic and Type-Safe Arrays for C.
The ```carray.h``` module provides a flexible wrapper around standard C arrays, allowing for dynamic resizing, multiple data types, and built-in searching and sorting algorithms. It manages memory allocation and reallocations automatically.

## Supported Data Types
- ```TYPE_INT``` Integer
- ```TYPE_FLOAT``` Float
- ```TYPE_DOUBLE``` Double
- ```TYPE_CHAR``` Character
- ```TYPE_STRING``` String/Character Pointer

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

# C-Zen Toolkit: cstring.h
Advanced String Manipulation Library for C.

The cstring.h module provides a suite of functions to handle strings with the ease of a high-level language. It includes utilities for case conversion, pattern matching, splitting, trimming, and complex transformations like replacement and shuffling.

## Module Documentation

### Case Conversion
- ```str_lower(str)```: Converts all characters in a string to lowercase in-place.
- ```str_upper(str)```: Converts all characters in a string to uppercase in-place.

### Predicates and Checks
- ```str_starts_with(str, prefix)```: Returns 1 if the string begins with the specified prefix.
- ```str_ends_with(str, suffix)```: Returns 1 if the string ends with the specified suffix.
- ```str_is_numeric(str)```: Returns 1 if the string contains only numeric digits.
- ```str_is_alpha(str)```: Returns 1 if the string contains only alphabetic characters.
- ```str_contains(haystack, needle)```: Returns 1 if a substring exists within the main string.

### Transformation and Cleaning
- ```str_trim(str)```: Returns a new heap-allocated string with leading and trailing whitespace removed.
- ```str_replace(str, old_sub, new_sub)```: Returns a new string where all occurrences of a substring are replaced with another.
- ```str_rev(str)```: Reverses the characters of a string in-place.
- ```str_shuffle(str)```: Randomizes the order of characters in a string in-place.

### Analysis and Splitting
- ```str_count(str, sub)```: Returns the total number of non-overlapping occurrences of a substring.
- ```str_split(str, token)```: Splices a string at every occurrence of the token and returns a C-Zen array (TYPE_STRING).

## Usage Example
```
// Splitting a sentence into words
const char *sentence = "C-Zen is powerful";
array *words = str_split(sentence, ' ');

// Transformation
char name[] = "aritra";
str_upper(name); // "ARITRA"

// Cleanup and Replace
char *raw = "   Durgapur, India   ";
char *clean = str_trim(raw);
char *replaced = str_replace(clean, "India", "WB");

printf("Result: %s\n", replaced); // "Durgapur, WB"

// Memory Management
free(clean);
free(replaced);
free_array(words);
```
## Implementation Details
Functions that return a new pointer (like str_trim, str_replace, and str_split) use heap allocation. The user is responsible for calling free() or free_array() to prevent memory leaks. The str_split function uses an internal 1024-byte buffer for parsing tokens.

# C-Zen Toolkit: cmath.h
Comprehensive Mathematical and Matrix Library for C.

The cmath.h module provides high-level mathematical utilities, ranging from standard number theory functions to a complete matrix manipulation suite and a string-based expression evaluator.

## Module Documentation

### Matrix Operations
- ```create_matrix(rows, cols)```: Allocates a 2D matrix on the heap.
- ```free_matrix(m)```: Deallocates matrix memory.
- ```matrix_from_input(rows, cols)```: Creates a matrix and populates it via user console input.
- ```matrix_rand(rows, cols, min, max)```: Generates a matrix with random values in a specified range.
- ```matrix_add(a, b)```: Returns a new matrix representing the sum of A and B.
- ```matrix_sub(a, b)```: Returns a new matrix representing the difference of A and B.
- ```matrix_mult(a, b)```: Performs matrix multiplication (Dot Product) and returns the result.
- ```matrix_transpose(m)```: Returns the transposed version of the input matrix.
- ```matrix_print(m)```: Displays the matrix in a clean, formatted grid.

### Sparse Matrix Support
- ```to_sparse(m, count)```: Converts a standard dense matrix into a Coordinate List (COO) sparse format to save memory on zero-heavy data.

### Number Theory and Utilities
- ```math_gcd(a, b)```: Calculates the Greatest Common Divisor using the Euclidean algorithm.
- ```math_factorial(n)```: Calculates the factorial of n using recursion.
- ```math_is_prime(n)```: Checks if a number is prime using optimized trial division.
- ```math_clamp(val, min, max)```: Constrains a value within a defined range.

### Expression Evaluation
- ```evaluate_expression(exp)```: A robust calculator that parses a string expression (e.g., "(10 + 2) * 5") and returns a double. It correctly handles operator precedence and parentheses.

## Usage Example
```
// Matrix Math
matrix *A = matrix_rand(2, 2, 1, 5);
matrix *B = matrix_rand(2, 2, 1, 5);
matrix *C = matrix_mult(A, B);
matrix_print(C);

// Expression Parsing
double result = evaluate_expression("3.5 * (10 + 2) / 4");
printf("Result: %.2f\n", result); // 10.50

// Cleanup
free_matrix(A);
free_matrix(B);
free_matrix(C);
```
## Implementation Details
The expression evaluator uses a Shunting-yard inspired logic with internal stacks for values and operators to manage precedence. Matrix multiplication checks for compatible dimensions (rows/cols) before execution and returns NULL on mismatch.

# C-Zen Toolkit: cmaps.h
Fast Key-Value Store (Dictionary) for C.

The cmaps.h module implements a high-performance hash table using the DJB2 string hashing algorithm. It allows for near-instantaneous data retrieval by associating string keys with generic pointers, making it ideal for caches, session management, and database-like structures.

## Module Documentation

### Initialization and Memory
- ```create_hashmap(size)```: Allocates a new hashmap with a specified number of buckets. A larger size reduces collisions but uses more memory.
- ```hashmap_put(map, key, value)```: Inserts a key-value pair into the map. If the key already exists, the value is updated.

### Retrieval
- ```hashmap_get(map, key)```: Searches for a key and returns the associated generic (void*) pointer. Returns NULL if the key is not found.

## Usage Example
```
// Create a map with 100 buckets
hashmap *user_sessions = create_hashmap(100);

// Store data
char *user_id = "user_123";
char *session_data = "active_session_payload";
hashmap_put(user_sessions, user_id, session_data);

// Retrieve data
char *retrieved = (char*)hashmap_get(user_sessions, "user_123");
if (retrieved) {
    printf("Session Status: %s\n", retrieved);
}
```
## Implementation Details
The library uses "Separate Chaining" to handle hash collisions. When two keys produce the same hash index, they are stored in a linked list within that bucket. The hash function uses the DJB2 algorithm (hash * 33 + c) for efficient distribution of string keys.

---

## Technical Architecture
C-Zen is built with a modular philosophy. Each header is designed to be independent where possible, allowing you to include only what you need. The toolkit prioritizes readability and ease of use, making it an ideal starting point for first-year students or developers looking to prototype quickly in C.

## Performance Notes
While C-Zen provides high-level abstractions, it remains close to the metal:
- String operations are optimized for O(n) complexity.
- Hashmap lookups maintain an average O(1) time complexity.
- Matrix operations use contiguous memory blocks for cache efficiency.

## License
This project is open-source and available under the MIT License. Feel free to fork, modify, and use it in your own projects.

## Contributions
If you find a bug or have a suggestion for a new high-level feature (like a specific string helper or math algorithm), feel free to open an issue or submit a pull request!

---
**Maintained by Aritra**
Contact: GitHub @PaperCodeGithub
