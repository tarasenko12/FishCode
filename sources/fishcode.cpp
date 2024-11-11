/*
** Copyright (C) 2024 Vitaliy Tarasenko.
**
** This file is part of FishCode.
**
** FishCode is free software: you can redistribute it and/or modify it under
** the terms of the GNU General Public License as published by the Free
** Software Foundation, either version 3 of the License, or (at your option)
** any later version.
**
** FishCode is distributed in the hope that it will be useful, but WITHOUT
** ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
** FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
** more details.
**
** You should have received a copy of the GNU General Public License along
** with FishCode. If not, see <https://www.gnu.org/licenses/>.
*/

#include <exception>
#include <filesystem>
#include <iostream>
#include <vector>
#include <cstddef>
#include "block.hpp"
#include "error.hpp"
#include "file.hpp"
#include "fishcode.hpp"
#include "key.hpp"
#include "password.hpp"
#include "string.hpp"

int fc::Main(const std::vector<fc::string_t>& argv) try {
  // Check command-line arguments.
  if (argv.size() == 2) {
    // One-word subcommand.
    // Check subcommand.
    if (argv[1] == L"--copyright") {
      // Print copyright information.
      std::cout <<
        "FishCode (fishcode) is a program for encrypting and decrypting files.\n"
        "Copyright (C) 2024 Vitaliy Tarasenko.\n"
        "This program comes with ABSOLUTELY NO WARRANTY.\n"
        "This is free software, and you are welcome to redistribute it\n"
        "under certain conditions.\n";
    } else if (argv[1] == L"--help") {
      // Print user manual.
      std::cout << USER_MANUAL << '\n';
    } else if (argv[1] == L"--version") {
      // Print program version.
      std::cout << "FishCode (fishcode) v1.0\n";
    } else {
      // Invalid subcommand.
      throw InvalidSubcommandError();
    }
  } else if (argv.size() == 5) {
    // Subcommand with parameters.
    // Check subcommand.
    if (argv[1] == L"--encrypt" || argv[1] == L"--decrypt") {
      // Create output file.
      OutputFile outputFile(argv[3]);

      // Create binary representation of the password.
      const Password password(argv[4]);      

      // Do the task.
      if (argv[1] == L"--encrypt") {
        // Encrypt the file.
        // Open the input file.
        InputFile inputFile(argv[2], false);

        // Generate encryption key.
        auto key = Key::Generate();

        // Encrypt the key with password.
        key.Encrypt(password);

        // Store encrypted key to the output file.
        outputFile.WriteKey(key);

        // Decrypt the key.
        key.Decrypt(password);

        // Get number of blocks in the input file.
        const auto inputFileBlocks = inputFile.GetBlocksNumber();

        // Encrypt the input file by blocks.
        for (std::size_t counter = 0; counter < inputFileBlocks; counter++) {
          // Read one block from the file.
          auto block = inputFile.ReadBlock();

          // Encrypt the block.
          block.Encrypt(key);

          // Store block to the output file.
          outputFile.WriteBlock(block);
        }

        // Check if the input file has partial block.
        if (inputFile.HasPartialBlock()) {
          // Read partial block.
          auto block = inputFile.ReadBlock(inputFile.GetPartialBlockSize());

          // Encrypt the block.
          block.Encrypt(key);

          // Store block to the output file.
          outputFile.WriteBlock(block);
        }
      } else {
        // Decrypt the file.
        // Open the input file.
        InputFile inputFile(argv[2], true);

        // Read key from the input file.
        auto key = inputFile.ReadKey();

        // Decrypt key using the password.
        key.Decrypt(password);

        // Get number of blocks in the input file (except key).
        const auto inputFileBlocks = inputFile.GetBlocksNumber() - 1;

        // Decrypt the input file by blocks.
        for (std::size_t counter = 0; counter < inputFileBlocks; counter++) {
          // Read one block from the file.
          auto block = inputFile.ReadBlock();

          // Decrypt the block.
          block.Decrypt(key);

          // Store block to the output file.
          outputFile.WriteBlock(block);
        }

        // Check if the input file has partial block.
        if (inputFile.HasPartialBlock()) {
          // Read partial block.
          auto block = inputFile.ReadBlock(inputFile.GetPartialBlockSize());

          // Decrypt the block.
          block.Decrypt(key);

          // Store block to the output file.
          outputFile.WriteBlock(block);
        }
      }

      // Print message for the user.
      std::cout << "Processed successfully.\n";
    } else {
      // Invalid subcommand.
      throw InvalidSubcommandError();
    }
  } else {
    // Invalid usage.
    throw InvalidUsageError();
  }

  // Return success code.
  return Results::SUCCESS;
} catch (const fc::Error& err) {
  // Print message for the user.
  std::cerr << err.What() << "\n\n";

  // Print user manual.
  std::cerr << USER_MANUAL << '\n';

  // Return error code.
  return err.GetErrorCode();
} catch (const std::exception& ex) {
  // Print message for the user.
  std::cerr
  <<
    "Error: system exception!\n"
    "Method \"what()\" has returned such string:\n"
  <<
    '\"'
  <<
    ex.what()
  <<
    "\"\n";

  // Return error code.
  return Results::SYSTEM_EXCEPTION;
}
