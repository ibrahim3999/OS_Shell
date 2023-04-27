# OS_Shell
This program is a simple shell that allows you to execute various commands, as well as handle some file operations such as comparing files, copying files, and encoding/decoding files with two different codecs.

## Installation
Clone the repository to your local machine
Open a terminal and navigate to the project directory
then run make.

## Usage

The shell supports the following commands:

* `cd [directory]`: Change the current working directory to [directory]. If [directory] is not specified, the home directory is used.
* `cmp [file1] [file2]`: Compare the contents of [file1] and [file2].
* `copy [source_file]` [destination_file] [options]: Copy [source_file] to [destination_file]. The following options are available:
  `-v`: Verbose mode. Print the progress of the copy operation.
  `-f`: Force mode. Overwrite the destination file if it already exists.
* `encode codecA [string]`: Encode [string] using codecA.
* `encode codecB [string]`: Encode [string] using codecB.
* `decode codecA [string]`: Decode [string] using codecA.
* `decode codecB [string]`: Decode [string] using codecB.
The shell also supports I/O redirection and pipes. The following symbols can be used:

* `>`: Redirect output to a file. Example: ls > file.txt
* `>>`: Append output to a file. Example: ls >> file.txt
* `|`: Pipe output to another command. Example: ls | grep foo
* `ls`,`grep`,`wc` ...
* To exit the shell, use the exit command or press Ctrl+C.

