# File-Descriptors-C
A Small Program in C to Demonstrate the Use of File Descriptors.

## File Descriptors
There are two primary ways to access files in C, **file descriptors** and **filestreams**.
File descriptors use a set of low-level I/O functions, and filestreams are a higher level
form of buffered I/O that is built on the lower-level functions. 
The filestream functions easier to program with, however, file
descriptors are more direct.

**File Descriptor** is a number that is used to reference open
files. Four common functions that use file descriptors are `open()`, `close()`,
`read()`, and `write()`. All of these functions will return –1 if there is an error.
The `open()` function opens a file for reading and/or writing and returns a file
descriptor. The returned file descriptor is just an integer value, but it is unique
among open files. The file descriptor is passed as an argument to the other
functions like a pointer to the opened file. For the `close()` function, the file
descriptor is the only argument. The `read()` and `write()` function's arguments
are the file descriptor, a pointer to the data to read or write, and the number of
bytes to read or write from that location. The arguments to the `open()` function
are a pointer to the filename to open and a series of predefined flags that specify
the access mode.

## filedescriptor.c 
This program accepts a filename and a note as commandline arguments and
then adds it to the end of the file "filename" . This program uses several functions,
including a `Errorchecked heap memory allocation function`.
Other functions are used to display a usage message and to handle fatal errors.

## Run filedescriptor.c
Use

`gcc -o filedesc filedescriptor.c` //add -g switch for debugging with gdb

`./filedesc note1 "Some Random Note"`

### Output
![image](https://user-images.githubusercontent.com/33039708/143430943-0127e258-0753-4acb-a2f9-434f2b292036.png)

The files `fcntl.h` and `sys/stat.h` had to be included, since those files define the flags used with the
`open()` function. 
The first set of flags is found in `fcntl.h` and is used to set the
access mode. The access mode must use at least one of the following three flags:
```
O_RDONLY Open file for read-only access.
O_WRONLY Open file for write-only access.
O_RDWR Open file for both read and write access.
O_APPEND Write data at the end of the file.
O_TRUNC If the file already exists, truncate the file to 0 length.
O_CREAT Create the file if it doesn't exist.
```

The flags used for the `open()` function have values that correspond to single bits.
This way, flags can be combined using OR logic without destroying any
information. The `fcntl_flags.c` program and its output explore some of the flag
values defined by `fcntl.h` and how they combine with each other.

### Output
![image](https://user-images.githubusercontent.com/33039708/143431565-7c33b820-d0ac-42ca-8b51-f6953314e233.png)

Using bit flags in combination with bitwise logic is an efficient and commonly
used technique. As long as each flag is a number that only has unique bits turned
on, the effect of doing a bitwise OR on these values is the same as adding them.
In `fcntl_flags.c`, 1 + 1024 + 64 = 1089.

## File Permissions
If the `O_CREAT` flag is used in access mode for the `open()` function, an additional
argument is needed to define the file permissions of the newly created file. This
argument uses bit flags defined in `sys/stat.h`, which can be combined with each
other using bitwise OR logic.

```
S_IRUSR Give the file read permission for the user (owner).
S_IWUSR Give the file write permission for the user (owner).
S_IXUSR Give the file execute permission for the user (owner).
S_IRGRP Give the file read permission for the group.
S_IWGRP Give the file write permission for the group.
S_IXGRP Give the file execute permission for the group.
S_IROTH Give the file read permission for other (anyone).
S_IWOTH Give the file write permission for other (anyone).
S_IXOTH Give the file execute permission for other (anyone).
```
## Relation with UNIX

The above `sys/stat.h` flags are somewhat simililar to Unix File Permissions.
the File Permissions for a program can be shown using 
`ls -l` command.

![image](https://user-images.githubusercontent.com/33039708/143432798-022b54c6-0141-4f38-b3c9-d9a092dbd7f2.png)

Read, write, and execute permissions can be turned on and off for three different
fields: user, group, and other. User permissions describe what the owner of the
file can do (read, write, and/or execute), group permissions describe what users
in that group can do, and other permissions describe what everyone else can do.
These fields are also displayed in the front of the `ls -l` output. First, the user
read/write/execute permissions are displayed, using `r` for read, `w` for write, `x` for
execute, and `-` for off. The next three characters display the group permissions,
and the last three characters are for the other permissions. In the output above,
the filedesc binar has all three user permissions turned on for User.
Each permission corresponds to a bit flag; read is 4 (100 in binary), write is 2
(010 in binary), and execute is 1 (001 in binary). Since each value only contains
unique bits, a bitwise OR operation achieves the same result as adding these
numbers together does. These values can be added together to define
permissions for user, group, and other using the `chmod` command.

