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

#include <iostream>
#include <cstddef>
#include "block.hpp"
#include "commands.hpp"
#include "error.hpp"
#include "file.hpp"
#include "fishcode.hpp"
#include "key.hpp"
#include "manual.hpp"
#include "messages.hpp"
#include "password.hpp"
#include "string.hpp"

void fc::Main(const fc::string_t& subcommand) {
  // Check subcommand.
  if (subcommand == CMD_COPYRIGHT) {
    // Print copyright information.
    std::cout << MSG_COPYRIGHT << '\n';
  } else if (subcommand == CMD_HELP) {
    // Print user manual.
    std::cout << USER_MANUAL << '\n';
  } else if (subcommand == CMD_VERSION) {
    // Print program version.
    std::cout << MSG_VERSION << '\n';
  } else {
    // Invalid subcommand.
    throw InvalidSubcommandError();
  }
}

void fc::Main(const fc::string_t& subcommand, fc::Arguments& arguments) {
  // Check subcommand.
  if (subcommand == CMD_ENCRYPT) {
    // Encrypt the file.
    // Generate encryption key.
    auto key = Key::Generate();

    // Encrypt the key with password.
    key.Encrypt(arguments.password);

    // Store encrypted key to the output file.
    arguments.outputFile.WriteKey(key);

    // Decrypt the key.
    key.Decrypt(arguments.password);

    // Get number of blocks in the input file.
    const auto inputFileBlocks = arguments.inputFile.GetBlocksNumber();

    // Encrypt the input file by blocks.
    for (std::size_t counter = 0; counter < inputFileBlocks; counter++) {
      // Read one block from the file.
      auto block = arguments.inputFile.ReadBlock();

      // Encrypt the block.
      block.Encrypt(key);

      // Store block to the output file.
      arguments.outputFile.WriteBlock(block);
    }

    // Check if the input file has partial block.
    if (arguments.inputFile.HasPartialBlock()) {
      // Read partial block.
      auto block = arguments.inputFile.ReadBlock(
        arguments.inputFile.GetPartialBlockSize()
      );

      // Encrypt the block.
      block.Encrypt(key);

      // Store block to the output file.
      arguments.outputFile.WriteBlock(block);
    }
  } else {
    // Decrypt the file.
    // Read key from the input file.
    auto key = arguments.inputFile.ReadKey();

    // Decrypt key using the password.
    key.Decrypt(arguments.password);

    // Get number of blocks in the input file (except key).
    const auto inputFileBlocks = arguments.inputFile.GetBlocksNumber() - 1;

    // Decrypt the input file by blocks.
    for (std::size_t counter = 0; counter < inputFileBlocks; counter++) {
      // Read one block from the file.
      auto block = arguments.inputFile.ReadBlock();

      // Decrypt the block.
      block.Decrypt(key);

      // Store block to the output file.
      arguments.outputFile.WriteBlock(block);
    }

    // Check if the input file has partial block.
    if (arguments.inputFile.HasPartialBlock()) {
      // Read partial block.
      auto block = arguments.inputFile.ReadBlock(
        arguments.inputFile.GetPartialBlockSize()
      );

      // Decrypt the block.
      block.Decrypt(key);

      // Store block to the output file.
      arguments.outputFile.WriteBlock(block);
    }
  }

  // Print message for the user.
  std::cout << "Processed successfully.\n";
}

