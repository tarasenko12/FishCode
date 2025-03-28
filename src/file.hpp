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

#ifndef FISHCODE_FILE_HPP
#define FISHCODE_FILE_HPP

#include <filesystem>
#include <fstream>
#include <cstddef>
#include "block.hpp"
#include "key.hpp"

namespace fc
{
    class File {
    public:
        using Path = std::filesystem::path;
        using Stream = std::fstream;
        using Size = std::size_t;

        enum class Type {
            input,
            output
        };
    private:
        Path path;
        Size size;
        mutable Stream stream;
        Type type;
        bool encrypted;
    public:
        File() = default;

        File(const Path& path, Type type, bool encrypted = false);

        File(const File& file) = delete;
        File(File&& file) noexcept = default;

        virtual ~File() noexcept = default;

        File& operator =(const File& file) = delete;
        File& operator =(File&& file) noexcept = default;

        Size getSize() const noexcept
        {
            return size;
        }

        Block readBlock(Size blockSize = Block::MAX_SIZE) const;
        Key readKey() const;

        void writeBlock(const Block& block);
        void writeKey(const Key& key);

        void remove()
        {
            // Remove this file using filesystem path.
            std::filesystem::remove(path);
        }
    };

    void checkFileIO(const File::Path& ifPath, const File::Path& ofPath);
}

#endif // FISHCODE_FILE_HPP
