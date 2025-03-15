/*
** Copyright (C) 2025 Vitaliy Tarasenko.
**
** This file is part of FishCode (fishcode).
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

#include <random>
#include "key.hpp"
#include "types.hpp"

fc::Key::Key(const fc::Key::Array& bytes)
: bytes(bytes)
{

}

fc::Key fc::Key::generate()
{
    // Create a new random device.
    std::random_device rnd_device;

    // Use 32-bit 'Mersenne Twister' algorithm.
    std::mt19937 generator(rnd_device());

    // Configure generator to produce numbers from 0 to 0xFF.
    std::uniform_int_distribution<unsigned> distribute(0, BYTE_MAX);

    // Create a storage for the generated key bytes.
    Array generated_bytes;

    // Generate key by bytes.
    for (Index counter = 0; counter < SIZE; counter++) {
        // Produce pseudo-random number and store it.
        generated_bytes[counter] = static_cast<Byte>(distribute(generator));
    }

    // Return generated key.
    return Key(generated_bytes);
}

fc::Key fc::Key::getRoundKey(Round round) const
{
    // Create a storage for the new key bytes.
    Array new_bytes;

    // Calculate a 'magic' number.
    const auto magicNumber = static_cast<Byte>(0x4d ^ round);

    // Combine key bytes and the 'magic' number.
    for (Index index = 0; index < SIZE; index++) {
        new_bytes[index] = bytes[index] ^ magicNumber;
    }

    // Return new round key.
    return Key(new_bytes);
}

void fc::Key::encrypt(const fc::Key& key)
{
    // Encrypt key within 15 rounds.
    for (int round = 0; round < 15; round++) {
        // Step 1: swap bytes.
        for (Index index = 1, counter = 0, pairs = SIZE / 2; counter < pairs; index += 2, counter++) {
            // Copy 'index - 1 byte' to the temporary storage.
            const auto temp = bytes[index - 1];

            // Move 'index byte'.
            bytes[index - 1] = bytes[index];

            // Store 'index - 1 byte'.
            bytes[index] = temp;
        }

        // Step 2: get round key.
        const auto round_key = key.getRoundKey(round);

        // Step 3: xor key.
        for (Index index = 0; index < SIZE; index++) {
            bytes[index] ^= round_key[index];
        }
    }
}

void fc::Key::decrypt(const fc::Key& key)
{
    // Decrypt key within 15 rounds.
    for (int round = 14; round >= 0; round--) {
        // Step 1: get round key.
        const auto round_key = key.getRoundKey(round);

        // Step 2: xor key.
        for (Index index = 0; index < SIZE; index++) {
            bytes[index] ^= round_key[index];
        }

        // Step 3: swap bytes.
        for (Index index = 1, counter = 0, pairs = SIZE / 2; counter < pairs; index += 2, counter++) {
            // Copy 'index - 1 byte' to the temporary storage.
            const auto temp = bytes[index - 1];

            // Move 'index byte'.
            bytes[index - 1] = bytes[index];

            // Store 'index - 1 byte'.
            bytes[index] = temp;
        }
    }
}
