# OS_Shell
This program is a simple shell that allows you to execute various commands, as well as handle some file operations such as comparing files, copying files, and encoding/decoding files with two different codecs.

The available commands are:

`cmp file1 file2 [offset]`: Compare two files and output the first byte offset where they differ. If offset is not provided, the files are compared until the end.

`copy file1 file2 [option]`: Copy file1 to file2. If option is`-v`, print a message indicating that the copy was successful. If option is `-f`, overwrite file2 without prompting.

`encode codec input_file`: Encode input_file using `codecA` or `codecB`, and output the `encoded` result.

`decode codec input_file`: Decode input_file using `codecA` or `codecB`, and output the `decoded` result.

`cd [directory]`: Change the current working directory. If directory is not provided, change to the home directory.

`--help`: Display this help message.

In addition, this shell also allows for basic input/output redirection and piping. To redirect output to a file, use `>` followed by the filename. To append output to a file, use `>>` followed by the filename. To pipe the output of one command into another command, use `|` followed by the next command.

Finally, the shell can be terminated by pressing `Ctrl+C`.
