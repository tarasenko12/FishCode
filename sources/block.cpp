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

#include <vector>
#include <cstddef>
#include <cstdint>
#include "block.hpp"
#include "key.hpp"

fc::Block::Block() {
  // Allocate memory to store block with maximal size.
  bytes.reserve(SIZE);
}

void fc::Block::PushByte(const std::uint8_t byte) {
  // Store one byte to the vector.
  bytes.push_back(byte);
}

void fc::Block::Encrypt(const fc::Key& key) noexcept {
  // Step 1: swap bytes.
  for (
    std::size_t index = 1, counter = 0, pairs = bytes.size() / 2;
    counter < pairs;
    index += 2,
    counter++
  ) {
    // Copy 'index - 1 byte' to the temporary storage.
    const auto temp = bytes[index - 1];

    // Move 'index byte'.
    bytes[index - 1] = bytes[index];

    // Store 'index - 1 byte'.
    bytes[index] = temp;
  }

  // Step 2: xor key.
  for (std::size_t index = 0, size = bytes.size(); index < size; index++) {
    bytes[index] ^= key[index];
  }
}

void fc::Block::Decrypt(const fc::Key& key) noexcept {
  // Step 1: xor key.
  for (std::size_t index = 0, size = bytes.size(); index < size; index++) {
    bytes[index] ^= key[index];
  }

  // Step 2: swap bytes.
  for (
    std::size_t index = 1, counter = 0, pairs = bytes.size() / 2;
    counter < pairs;
    index += 2,
    counter++
  ) {
    // Copy 'index - 1 byte' to the temporary storage.
    const auto temp = bytes[index - 1];

    // Move 'index byte'.
    bytes[index - 1] = bytes[index];

    // Store 'index - 1 byte'.
    bytes[index] = temp;
  }
}