# 🎵 MP3 Tag Reader and Editor in C

This project is a **C-based MP3 Tag Reader and Editor** that allows users to **view, extract, and modify ID3v1 and ID3v2 metadata** embedded within MP3 files. The tool provides a simple command-line interface to interact with song details such as title, artist, album, year, genre, and comments.

---

## 🔹 Overview

The program reads the **ID3 tags** from MP3 files and displays all available metadata fields. It can also **edit existing tags** by updating the corresponding fields directly within the MP3 file without affecting the audio content.

This project demonstrates practical applications of **file I/O**, **binary data manipulation**, and **string handling** in C, along with a **modular programming approach**.

---

## 🔹 Features

- **View Tags:** Displays song metadata such as title, artist, album, year, genre, and comments.
- **Edit Tags:** Modify existing fields such as title, artist, or album directly from the command line.
- **ID3v1 & ID3v2 Support:** Compatible with standard MP3 metadata formats.
- **Error Handling:** Displays meaningful error messages for invalid inputs or missing files.
- **User-Friendly CLI:** Simple commands for easy access and modification of tags.

---

## 🔹 Project Structure

| File | Description |
|------|--------------|
| `main.c` / `main.h` | Entry point and CLI logic for viewing and editing tags |
| `id3_reader.c` / `id3_reader.h` | Reads and displays ID3 tag information |
| `id3_writer.c` / `id3_writer.h` | Updates or modifies tag data within the MP3 file |
| `id3_utils.c` / `id3_utils.h` | Defines data structures and helper functions for tag handling |
| `error_handling.h` | Provides functions for displaying errors and usage help |

---

## 🔹 Technical Highlights

- Reads and writes **binary data** using C file operations (`fopen`, `fread`, `fwrite`, `fseek`).
- Implements **data structures** (`TagData`) to store metadata efficiently.
- Uses **modular programming** for better maintainability and clarity.
- Demonstrates **string and memory management** techniques in C.

---

## 🔹 Usage

### 🧩 View Tags
```bash
./a.out -v <filename.mp3>
```

### 🧩 Edit Tags
```bash
./a.out -e -t/-a/-A/-y/-g/-c "NewValue" <filename.mp3>
```

**Options:**
- `-t`: Edit title  
- `-a`: Edit artist  
- `-A`: Edit album  
- `-y`: Edit year  
- `-g`: Edit genre  
- `-c`: Edit comments  

### 🧩 Help
```bash
./a.out -h
```

---

## 🔹 Summary

This **MP3 Tag Reader and Editor** showcases how **C programming** can be used to handle multimedia file metadata. It combines binary data processing, structured programming, and file system manipulation to build a robust tool for managing music file information efficiently.
