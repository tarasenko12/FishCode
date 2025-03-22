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

module;

#include <filesystem>
#include <fstream>
#include <ios>
#include <cstddef>

module core;

fc::File::File(const fc::File::Path& path, fc::File::Type type, bool encrypted)
: path(path)
{
    if (type == Type::INPUT) {
        // Check if path is not empty.
        if (path.empty()) {
            // Invalid output file (no file).
            throw errors::InvalidInputFile();
        }

        // Check if it is path to a regular file.
        if (!std::filesystem::is_regular_file(path)) {
            // Invalid input file.
            throw errors::InvalidInputFile();
        }

        // Open a file.
        stream.open(path, std::ios::in | std::ios::binary | std::ios::ate);

        // Calculate size of the file.
        size = static_cast<Size>(stream.tellg());

        // Check file size.
        if (encrypted) {
            if (size < static_cast<Size>(Key::SIZE) + 1) {
                // Invalid input file.
                throw errors::InvalidInputFile();
            }
        }
        else {
            if (size < static_cast<Size>(Block::MIN_SIZE)) {
                // Invalid input file.
                throw errors::InvalidInputFile();
            }
        }

        // Rewind the stream.
        stream.seekg(std::ios::beg);
    }
    else {
        // Check if path is not empty.
        if (path.empty()) {
            // Invalid output file (no file).
            throw errors::InvalidOutputFile();
        }

        // Check if path points to the existing file.
        if (std::filesystem::exists(path)) {
            // Check if it is regular file.
            if (!std::filesystem::is_regular_file(path)) {
                // Invalid output file.
                throw errors::InvalidOutputFile();
            }
        }

        // Create a file.
        stream.open(path, std::ios::out | std::ios::binary);

        // It is empty file.
        size = 0;
    }
}

fc::Block fc::File::readBlock(fc::File::Size blockSize) const
{
    // Create storage for the block.
    Block block;

    // Read block by bytes from the file.
    for (unsigned index = 0; index < blockSize; index++) {
        // Read one byte from the file and store it to the block.
        block.push(static_cast<Block::Byte>(stream.get()));
    }

    // Return the block.
    return block;
}

fc::Key fc::File::readKey() const
{
    // Create storage for the key.
    Key key;

    // Read key by bytes from the file.
    for (auto& byte : key) {
        // Read one byte and store it.
        byte = static_cast<Key::Byte>(stream.get());
    }

    // Create a real key object and return it.
    return key;
}

void fc::File::writeBlock(const fc::Block& block)
{
    // Write block by bytes.
    for (auto byte : block) {
        // Store the byte.
        stream.put(static_cast<char>(byte));

        // Increase file size.
        size++;
    }
}

void fc::File::writeKey(const fc::Key& key) {
    // Write key by bytes.
    for (auto byte : key) {
        // Store the byte.
        stream.put(static_cast<char>(byte));

        // Increase file size.
        size++;
    }
}
