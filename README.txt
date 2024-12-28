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
and decryption is carried out in 10 rounds. The file is encrypted in blocks
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
## TODO ##
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
## TODO ##
================================================================================

