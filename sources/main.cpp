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
#include "arguments.hpp"
#include "commands.hpp"
#include "error.hpp"
#include "fishcode.hpp"
#include "manual.hpp"
#include "messages.hpp"
#include "results.hpp"
#include "string.hpp"

#if defined(_WIN32) || defined(_WIN64)
// UTF-16.
int wmain(const int argc, const wchar_t* argv[])
#else
// UTF-8.
int main(const int argc, const char* argv[])
#endif // UTF-16 or UTF-8 command-line arguments.
try {
  // Check usage mode.
  if (argc == 2) {
    // Call program-own main function with one-word subcommand.
    fc::Main(argv[1]);
  } else if (argc == 5) {
    // Parse command-line arguments.
    // Store subcommand.
    const fc::string_t subcommand = argv[1];
    
    // Create storage for the arguments.
    fc::Arguments arguments;
    
    // Check input file type.
    if (subcommand == fc::CMD_ENCRYPT) {
      // Plaintext.
      arguments = fc::Arguments(argv[2], false, argv[3], argv[4]);
    } else if (subcommand == fc::CMD_DECRYPT) {
      // Encrypted input file.
      arguments = fc::Arguments(argv[2], true, argv[3], argv[4]);
    } else {
      // Invalid subcommand.
      throw fc::InvalidSubcommandError();
    }
    
    // Call program-own main function with arguments.
    fc::Main(subcommand, arguments);
  } else {
    // Invalid usage.
    throw fc::InvalidUsageError();
  }
  
  // Return success code.
  return fc::Results::SUCCESS;
} catch (const std::exception& ex) {
  // Print message for the user.
  std::cerr << fc::MSG_SYSTEM_EXCEPTION << '\"' << ex.what() << "\"\n";

  // Return error code.
  return fc::Results::SYSTEM_EXCEPTION;
} catch (const fc::Error& err) {
  // Print message for the user.
  std::cerr << err.What() << "\n\n";

  // Print user manual.
  std::cerr << fc::USER_MANUAL << '\n';

  // Return error code.
  return err.GetErrorCode();
}

