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

#include <cstddef>
#include <cstdint>
#include "error.hpp"
#include "password.hpp"
#include "string.hpp"

fc::Password::Password(const fc::string_t& passwordString) {
  // Get length of the string.
  const auto length = passwordString.length();

  // Check length of the password string.
  if (length < MIN_LENGTH || length > MAX_LENGTH) {
    // Invalid password.
    throw InvalidPasswordError();
  }

  // Check password characters.
  for (const auto symbol : passwordString) {
    if (symbol < 0x21 || symbol > 0x7E) {
      // Invalid symbol (and password too).
      throw InvalidPasswordError();
    }
  }

  // Convert each symbol to its binary representation and store it.
  for (std::size_t index = 0; index < length; index++) {
    bytes[index] = static_cast<std::uint8_t>(passwordString[index]);
  }

  // Check if password string has not maximal length.
  if (length < MAX_LENGTH) {
    // Append additional bytes from the beginning.
    for (
      std::size_t index = 0, offset = length;
      offset < SIZE;
      offset++, index++
     ) {
      bytes[offset] = bytes[index];
    }
  }
}

