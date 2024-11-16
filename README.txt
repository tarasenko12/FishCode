********************************************************************************
Brief description:
________________________________________________________________________________
  FishCode is a program for encrypting and decrypting files.
********************************************************************************
Detailed description:
________________________________________________________________________________
  FishCode is a simple program that encrypts files (text and binary) using a
custom algorithm (described below). The program works with files as byte
arrays, so the file type has no effect on the result, and therefore can
encrypt videos, images and text files using the same algorithm.
  The program works with 128-bit data blocks and a 128-bit key. Encryption
happens as follows:
  1. bytes swap (if the file contains 2 or more bytes of data);
  2. combining the key with each block of data (byte-by-byte) using a
  bitwise XOR operation.
  Decryption is carried out in reverse order. For encryption, the key is
generated using a pseudo-random number generation algorithm. When
encrypting a file, the user enters a password that can contain upper and
lowercase Latin letters, special characters, numbers from 0 to 9. The
password cannot contain spaces and non-Latin letters and symbols that are not
part of the ASCII character set. The password is used to encrypt and decrypt
the key, because the key is written in the encrypted file (at the beginning
of the file). When decrypting the master file, the key is decrypted using a
password, which makes it impossible to accidentally guess the master key and
decrypt the file without entering the password.
********************************************************************************
System requirements:
________________________________________________________________________________
General Requirements:
  - C++ Standard: ensure the system supports C++20.
  - Build System: CMake (version 3.20 or later) and Ninja (almost any version).
  - Compiler: a modern C++ compiler that supports C++20 features.
################################################################################
Windows:
  - Operating System: Windows 10 or later.
  - Compiler:
    -- Microsoft Visual Studio 2019 (version 16.10) or later (ensure the "C++
       CMake tools for Windows" and "MSVC v14.29" toolchain are installed).
  - Additional Tools:
    -- PowerShell or Command Prompt for build management.
    -- Windows SDK matching the Visual Studio version for development.
################################################################################
Linux:
  - Operating System: any modern Linux distribution (e.g., Ubuntu 22.04 or
    later, Debian 12 or later, Fedora 38 or later).
  - Compiler:
    -- GCC (version 11 or later).
    -- Alternatively, Clang (version 13 or later).
  - Build Tools:
    -- Essential development libraries ("build-essential", "libstdc++-dev",
       etc.).
  - Package Manager: ensure a package manager like "apt", "dnf", or "pacman"
    is available for dependency installation.
################################################################################
macOS:
  - Operating System: macOS 11.3 (Big Sur) or later.
  - Compiler:
    -- Apple Clang (version 13.0.0 or later (bundled with Xcode 13.0 or later).
    -- Alternatively, GCC (version 11 or later) or Clang (version 13 or later)
       via Homebrew.
  - Build Tools:
    -- Install CMake via Homebrew or the official website.
    -- Use Ninja as the build tool.
********************************************************************************
Build instructions:
________________________________________________________________________________
  For a normal build of the program, you need to enter the following
commands:
  $ cmake -B build -D CMAKE_BUILD_TYPE=Release -G Ninja
  $ cmake --build build
  After the compilation process is complete, the executable file will be in
the "build" directory.
********************************************************************************
  If for some reason you want to compile the program with the debugging
symbols, you can enter the following commands:
  $ cmake -B build -D CMAKE_BUILD_TYPE=Debug -G Ninja
  $ cmake --build build
********************************************************************************
User documentation:
________________________________________________________________________________
Usage: fishcode [SUBCOMMAND] [ARGUMENTS]
################################################################################
Subcommands:
  --copyright - prints license and copyright information;
  --help - prints user manual;
  --version - prints information about the program version;
  --encrypt [ARGUMENTS] - encrypts the file;
  --decrypt [ARGUMENTS] - decrypts the file.
Arguments:
  1. {PATH TO INPUT FILE};
  2. {PATH TO OUTPUT FILE};
  3. {PASSWORD}.
Password:
  1. ASCII-only printable characters;
  2. at least 8 symbols, maximum 16 symbols;
  3. no spaces.
================================================================================

