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
#include "block.hpp"
#include "key.hpp"
#include "types.hpp"

namespace fc
{
    enum class FileType {
        input,
        output
    };

    class File {
    public:
        File();

        File(const Path& path, FileType type, bool encrypted = false);

        File(const File& file) = delete;
        File(File&& file) noexcept = default;

        virtual ~File() noexcept = default;

        File& operator =(const File& file) = delete;
        File& operator =(File&& file) noexcept = default;

        inline FileSize getSize() const noexcept
        {
            return size;
        }

        Block readBlock(FileSize read_size = Block::MAX_SIZE) const;
        Key readKey() const;

        inline void remove()
        {
            // Remove this file using standard filesystem manipulations.
            std::filesystem::remove(path);
        }

        void writeBlock(const Block& block);
        void writeKey(const Key& key);
    protected:
        Path path;
        FileSize size;
        mutable std::fstream stream;
    };
}

#endif // FISHCODE_FILE_HPP
