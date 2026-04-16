*This project has been created as part of the 42 curriculum by fetraand.*

## DESCRIPTION

`get_next_line` is a C function that reads a single line from a file descriptor each time it is called. It handles any file descriptor — regular files, standard input, or others — and preserves state between calls using a `static` variable, so successive calls yield successive lines without re-reading already consumed data.

**Goal:** implement a reliable, memory-safe line-reader that works correctly regardless of the `BUFFER_SIZE` used at compile time (from 1 to very large values).

**Overview of files:**

| File | Role |
|---|---|
| `get_next_line.c` | Core logic: read & stash, extract line, update stash |
| `get_next_line_utils.c` | Helper functions: `ft_strlen`, `ft_strchr`, `ft_strdup`, `ft_substr`, `ft_strjoin` |
| `get_next_line.h` | Header — prototypes and `BUFFER_SIZE` macro |
| `main.c` | Test driver (not part of the submitted project) |

## INSTRUCTIONS

### Compilation

Compile with `cc` and optionally set a custom `BUFFER_SIZE`:

```bash
# Default BUFFER_SIZE (1024)
cc -Wall -Wextra -Werror -o gnl_test \
    main.c get_next_line.c get_next_line_utils.c

# Custom BUFFER_SIZE
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 -o gnl_test \
    main.c get_next_line.c get_next_line_utils.c
```

### Running the tests

```bash
# Make sure file.txt is present in the same directory
./gnl_test
```

The test suite covers:

- **Normal file** — reads every line from `file.txt` and prints them numbered.
- **Invalid fd** — calls `get_next_line(-1)` and expects `NULL`.
- **Empty file** — calls `get_next_line` on an empty file and expects `NULL`.
- **Stdin** (optional, uncomment in `main.c`) — reads lines interactively from the terminal until an empty line is entered.

To test with an empty file:

```bash
touch empty.txt
./gnl_test
```

### Using `get_next_line` in your own project

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int   fd = open("myfile.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

> **Note:** the caller is responsible for `free()`-ing each returned line.

---

## RESOURCES

### Documentation & references

- [POSIX `read(2)` — man page](https://man7.org/linux/man-pages/man2/read.2.html)
- [POSIX `open(2)` — man page](https://man7.org/linux/man-pages/man2/open.2.html)
- [C `static` variables — cppreference](https://en.cppreference.com/w/c/language/storage_duration)
- [Valgrind — memory leak detection](https://valgrind.org/docs/manual/quick-start.html)
- [42 Norm — coding standard](https://github.com/42School/norminette)

### Articles & tutorials

- *Understanding file descriptors in C* — [https://www.bottomupcs.com/file_descriptors.xhtml](https://www.bottomupcs.com/file_descriptors.xhtml)
- *Dynamic memory management in C* — [https://www.gnu.org/software/libc/manual/html_node/Memory-Allocation-and-C.html](https://www.gnu.org/software/libc/manual/html_node/Memory-Allocation-and-C.html)

### AI usage

AI was used during this project for:

    Debugging: Identifying logic errors in the main

    Testing: Generating edge-case scenarios (e.g., varying BUFFER_SIZE, empty files, and multiple file descriptors) to ensure robustness. 

> The AI was used as a learning companion, not as a replacement for understanding the concepts. Every function was implemented and tested manually to ensure proper understanding of C programming fundamentals.
