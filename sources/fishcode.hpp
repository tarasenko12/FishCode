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

#ifndef FISHCODE_HPP
#define FISHCODE_HPP

#include <vector>
#include "string.hpp"

namespace fc {
  // Program exit codes.
  enum Results : int {
    SUCCESS,
    INVALID_PASSWORD,
    INVALID_INPUT_FILE,
    INVALID_OUTPUT_FILE,
    INVALID_USAGE,
    INVALID_SUBCOMMAND,
    SYSTEM_EXCEPTION
  };

  // User manual.
  constexpr const auto USER_MANUAL =
    "Usage: fishcode [SUBCOMMAND] [ARGUMENTS]\n\n"
    "Subcommands:\n"
    "\t--copyright - prints license and copyright information;\n"
    "\t--help - prints this message;\n"
    "\t--version - prints information about the program version;\n"
    "\t--encrypt [ARGUMENTS] - encrypts the file;\n"
    "\t--decrypt [ARGUMENTS] - decrypts the file.\n\n"
    "Arguments:\n"
    "\t1. {PATH TO INPUT FILE};\n"
    "\t2. {PATH TO OUTPUT FILE};\n"
    "\t3. {PASSWORD}.\n\n"
    "Password:\n"
    "\t1. ASCII-only printable characters;\n"
    "\t2. at least 8 symbols, maximum 16 symbols;\n"
    "\t3. no spaces.";
  
#if defined(_WIN32) || defined(_WIN64)
  constexpr const auto CMD_COPYRIGHT = L"--copyright";
  constexpr const auto CMD_HELP = L"--help";
  constexpr const auto CMD_VERSION = L"--version";
  constexpr const auto CMD_ENCRYPT = L"--encrypt";
  constexpr const auto CMD_DECRYPT = L"--decrypt";
#else
  constexpr const auto CMD_COPYRIGHT = "--copyright";
  constexpr const auto CMD_HELP = "--help";
  constexpr const auto CMD_VERSION = "--version";
  constexpr const auto CMD_ENCRYPT = "--encrypt";
  constexpr const auto CMD_DECRYPT = "--decrypt";
#endif // UTF-16 or UTF-8 commands.

  // Program-own main function.
  int Main(const std::vector<fc::string_t>& argv);
}

#endif // FISHCODE_HPP
