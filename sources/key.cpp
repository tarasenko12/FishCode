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

#include <array>
#include <random>
#include <cstddef>
#include <cstdint>
#include "key.hpp"

fc::Key::Key() noexcept : bytes{} {}

fc::Key fc::Key::Generate() {
  // Create a new empty key.
  Key newKey;

  // Create a new random device.
  std::random_device randomDevice;

  // Use 32-bit 'Mersenne Twister' algorithm.
  std::mt19937 generator(randomDevice());

  // Configure generator to produce numbers from 0 to UINT8_MAX.
  std::uniform_int_distribution<unsigned int> distribute(0, UINT8_MAX);

  // Generate key by bytes.
  for (auto& byte : newKey) {
    // Produce pseudo-random number and store it.
    byte = static_cast<std::uint8_t>(distribute(generator));
  }

  // Return the key.
  return newKey;
}

void fc::Key::Encrypt(const fc::Key& anotherKey) noexcept {
  // Step 1: swap bytes.
  for (std::size_t index = 1; index < SIZE; index += 2) {
    // Copy 'index - 1 byte' to the temporary storage.
    const auto temp = bytes[index - 1];

    // Move 'index byte'.
    bytes[index - 1] = bytes[index];

    // Store 'index - 1 byte'.
    bytes[index] = temp;
  }

  // Step 2: xor key.
  for (std::size_t index = 0; index < SIZE; index++) {
    bytes[index] ^= anotherKey.bytes[index];
  }
}

void fc::Key::Decrypt(const fc::Key& anotherKey) noexcept {
  // Step 1: xor key.
  for (std::size_t index = 0; index < SIZE; index++) {
    bytes[index] ^= anotherKey.bytes[index];
  }

  // Step 2: swap bytes.
  for (std::size_t index = 1; index < SIZE; index += 2) {
    // Copy 'index - 1 byte' to the temporary storage.
    const auto temp = bytes[index - 1];

    // Move 'index byte'.
    bytes[index - 1] = bytes[index];

    // Store 'index - 1 byte'.
    bytes[index] = temp;
  }
}

