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
#include <vector>
#include <cstddef>
#include "fishcode.hpp"
#include "string.hpp"

#if defined(_WIN32) || defined(_WIN64)
// UTF-16.
int wmain(const int argc, const wchar_t* argv[])
#else
// UTF-8.
int main(const int argc, const char* argv[])
#endif // UTF-16 or UTF-8 command-line arguments.
try {
  // Create an empty vector for command-line arguments.
  std::vector<fc::string_t> cpp_argv;

  // Allocate memory to store command-line arguments.
  cpp_argv.reserve(argc);

  // Copy command-line arguments to the vector.
  for (int index = 0; index < argc; index++) {
    cpp_argv.push_back(argv[index]);
  }

  // Call program-own main function.
  // Use fc::Main() return value as exit code.
  return fc::Main(cpp_argv);
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
  return fc::Results::SYSTEM_EXCEPTION;
}

