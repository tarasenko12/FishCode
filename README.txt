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
  The program works with 128-bit data blocks and a 128-bit key. File encryption
and decryption is carried out in 15 rounds. The file is encrypted in blocks
up to 128 bits (16 bytes). A unique key is generated for each round, this key
is derived from the main key.
  Each round of encryption has the following sequence of actions:
  1. bytes swap (if the file contains 2 or more bytes of data);
  2. round key generation;
  3. combining the key with each block of data (byte-by-byte) using a
  bitwise XOR operation.
  Each round of decryption is performed in the following sequence:
  1. round key generation;
  2. combining the key with each block of data (byte-by-byte) using a
  bitwise XOR operation;
  3. bytes swap (if the file contains 2 or more bytes of data).
  For encryption, the key is generated using a pseudo-random number generation
algorithm. When encrypting a file, the user enters a password that can
contain upper and lowercase Latin letters, special characters, numbers
from 0 to 9. The password cannot contain spaces and non-Latin letters and
symbols that are not part of the ASCII character set. The password is used to
encrypt and decrypt the key, because the key is written in the encrypted file
(at the beginning of the file). When decrypting the master file, the key is
decrypted using a password, which makes it impossible to accidentally guess
the master key and decrypt the file without entering the password.
********************************************************************************
System requirements:
________________________________________________________________________________
  The FishCode program is a cross-platform application, but primarily it is
oriented to work on three platforms: Windows, Linux and Mac OS. This program
is as minimalistic as possible and can successfully run on both powerful and
weak computers. The recommended hardware is the same as for modern versions
of Windows (10, 11), Mac OS (v11 and above), and Linux (Ubuntu 22.04 and
later, Fedora 38, etc.).
  Compiling the program requires a modern C++ compiler that supports at least
C++20. In addition to the compiler, you also need the following build
systems: CMake (version 3.20 or later) and Ninja (almost any version).
wxWidgets library (version 3.0 or later) is also required. On Linux, this
library (wxGTK) can be installed from the official repositories of your
distribution. For Windows (wxMSW) and Mac OS (wxOSX/Cocoa), it is recommended
to compile this library by yourself (https://www.wxwidgets.org/downloads/).
You can find the system requirements for the wxWidgets compilation on the
official website of this project:
(https://docs.wxwidgets.org/3.2/page_introduction.html).
********************************************************************************
Build instructions:
________________________________________________________________________________
  To build the program, you need to enter the following commands:
  $ cmake -B build -D CMAKE_BUILD_TYPE=Release -G Ninja
  $ cmake --build build
  After the compilation process is completed, the executable file will be in
the "build" directory.
********************************************************************************
  If for some reason you want to compile the program with the debugging
symbols, you can enter the following commands:
  $ cmake -B build -D CMAKE_BUILD_TYPE=Debug -G Ninja
  $ cmake --build build
********************************************************************************
  The compilation of the program on Windows or Mac OS is carried out in two
stages. At the first stage, you need to build the wxWidgets library. For more
detailed information on this matter, read the official documentation
for wxWidgets.
  Windows: https://docs.wxwidgets.org/3.2/plat_msw_install.html
  Mac OS: https://docs.wxwidgets.org/3.2/plat_osx_install.html
  After that, the second stage, at which the program itself is built using the
prepared on the previous step wxWidgets library. This step is carried out
similarly to build on Linux.
********************************************************************************
User documentation:
________________________________________________________________________________
  Fishcode interface consists of two main components: the main window and an
additional menu called "More...".
  The main window has three input fields ("Input file", "Output file",
"Password") and four buttons ("Choose...", "Set...", "Encrypt", "Decrypt").
  The "Input file" and "Output file" fields are for entering the path to the
corresponding files on the disk. The file path can be either absolute,
such as "C:\users\user\Downloads\file", or relative, such as "Downloads/file".
  The "Choose..." and "Set..." buttons are alternative ways to identify
the relevant files. These buttons bring up the corresponding dialog boxes.
  The "Encrypt" and "Decrypt" buttons perform the operations corresponding
to their name. The status of the operation is displayed in the progress bar
and at the bottom of the window, in the status field.
  Note: password cannot contain spaces and non-Latin letters and symbols that
are not part of the ASCII character set.
================================================================================

