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

fc::Key fc::Key::generate()
{
    // Create a new random device.
    std::random_device randomDevice;

    // Use 32-bit 'Mersenne Twister' algorithm.
    std::mt19937 generator(randomDevice());

    // Configure generator to produce numbers from 0 to 0xff.
    std::uniform_int_distribution<unsigned int> distribute(0, BYTE_MAX);

    // Create a storage for the key.
    Key key;

    // Generate key by bytes.
    for (unsigned counter = 0; counter < SIZE; counter++) {
        // Produce pseudo-random number and store it.
        key[counter] = static_cast<Byte>(distribute(generator));
    }

    // Return generated key.
    return key;
}

fc::Key fc::Key::getRoundKey(int round) const
{
    // Create a storage for the round key.
    Key key;

    // Calculate a 'magic' number.
    const auto magicNumber = static_cast<Byte>(0x4d) ^ static_cast<Byte>(round);

    // Combine key bytes and the 'magic' number.
    for (unsigned index = 0; index < SIZE; index++) {
        key[index] = bytes[index] ^ magicNumber;
    }

    // Return new round key.
    return key;
}

void fc::Key::encrypt(const fc::Key& key)
{
    // Encrypt key within 15 rounds.
    for (int round = 0; round < 15; round++) {
        // Step 1: swap bytes.
        for (unsigned index = 1, counter = 0, pairs = SIZE / 2; counter < pairs; index += 2, counter++) {
            // Copy 'index - 1 byte' to the temporary storage.
            const auto temp = bytes[index - 1];

            // Move 'index byte'.
            bytes[index - 1] = bytes[index];

            // Store 'index - 1 byte'.
            bytes[index] = temp;
        }

        // Step 2: get round key.
        const auto roundKey = key.getRoundKey(round);

        // Step 3: xor key.
        for (unsigned index = 0; index < SIZE; index++) {
            bytes[index] ^= roundKey.bytes[index];
        }
    }
}

void fc::Key::decrypt(const fc::Key& key)
{
    // Decrypt key within 15 rounds.
    for (int round = 14; round >= 0; round--) {
        // Step 1: get round key.
        const auto roundKey = key.getRoundKey(round);

        // Step 2: xor key.
        for (unsigned index = 0; index < SIZE; index++) {
            bytes[index] ^= roundKey.bytes[index];
        }

        // Step 3: swap bytes.
        for (unsigned index = 1, counter = 0, pairs = SIZE / 2; counter < pairs; index += 2, counter++) {
            // Copy 'index - 1 byte' to the temporary storage.
            const auto temp = bytes[index - 1];

            // Move 'index byte'.
            bytes[index - 1] = bytes[index];

            // Store 'index - 1 byte'.
            bytes[index] = temp;
        }
    }
}
