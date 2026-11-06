
# MP3 Tag Reader and Editor using C

## Project Overview
The MP3 Tag Reader and Editor is a C programming project developed to read and edit ID3v2 metadata in MP3 files.

## Features

### View Operation
- Reads MP3 metadata.
- Displays Title, Artist, Album, Year, Genre and Comment.
- Reads ID3v2 frame information.
- Performs Big Endian to Little Endian conversion.

### Edit Operation
- Modifies selected MP3 tag information.
- Supports editing Title, Artist, Album, Year, Genre and Comment.
- Uses temporary file handling.
- Preserves the remaining MP3 data while editing.

## Technologies Used
- C Programming
- File Handling
- Structures and Pointers
- String Handling
- Command Line Arguments
- Binary File Operations

## Compilation

gcc *.c

## Execution
To view MP3 tags
./mp3_reader -v sample.mp3

To edit the song title:
./mp3_reader -e -t "New Title" sample.mp3

## Project Files
- mp3_main.c – Main function
- mp3_view.c – MP3 tag viewing operation
- mp3_edit.c – MP3 tag editing operation
- functions.c – Helper functions
- mp3_header.h – Structure and function declarations


