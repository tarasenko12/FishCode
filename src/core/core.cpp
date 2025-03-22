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

#include <array>
#include <exception>
#include <filesystem>
#include <fstream>
#include <ios>
#include <string>
#include <vector>
#include <cstddef>

export module core;

export namespace fc
{
    class Key {
    public:
        using Byte = std::byte;
        using Array = std::array<Byte, 16>;
        using Iterator = Array::iterator;
        using ConstIterator = Array::const_iterator;

        static constexpr unsigned SIZE = 16;
        static constexpr unsigned BYTE_MAX = 0xff;
    private:
        Array bytes;
    public:
        Key() = default;

        Key(const Key& key) = default;
        Key(Key&& key) noexcept = default;

        virtual ~Key() noexcept = default;

        Key& operator =(const Key& key) = default;
        Key& operator =(Key&& key) noexcept = default;

        Byte& operator [](int index) noexcept
        {
            return bytes[index];
        }

        const Byte& operator [](int index) const noexcept
        {
            return bytes[index];
        }

        static Key generate();

        Iterator begin()
        {
            return bytes.begin();
        }

        Iterator end()
        {
            return bytes.end();
        }

        ConstIterator begin() const
        {
            return bytes.begin();
        }

        ConstIterator end() const
        {
            return bytes.end();
        }

        Key getRoundKey(int round) const;

        void encrypt(const Key& key);
        void decrypt(const Key& key);
    };

    class Password : public Key {
    public:
        using String = std::string;

        static constexpr unsigned MIN_LENGTH = 8;
        static constexpr unsigned MAX_LENGTH = SIZE;
    private:
        String string;
    public:
        Password() = default;

        Password(const String& string);

        Password(const Password& password) = default;
        Password(Password&& password) noexcept = default;

        virtual ~Password() noexcept override = default;

        Password& operator =(const Password& password) = default;
        Password& operator =(Password&& password) noexcept = default;
    };

    class Block {
    public:
        using Byte = Key::Byte;
        using Vector = std::vector<Byte>;
        using Iterator = Vector::iterator;
        using ConstIterator = Vector::const_iterator;

        static constexpr unsigned MIN_SIZE = 1;
        static constexpr unsigned MAX_SIZE = 16;
    private:
        Vector bytes;
    public:
        Block();

        Block(const Block& block) = default;
        Block(Block&& block) noexcept = default;

        virtual ~Block() noexcept = default;

        Block& operator =(const Block& block) = default;
        Block& operator =(Block&& block) noexcept = default;

        Iterator begin()
        {
            return bytes.begin();
        }

        Iterator end()
        {
            return bytes.end();
        }

        ConstIterator begin() const
        {
            return bytes.begin();
        }

        ConstIterator end() const
        {
            return bytes.end();
        }

        void push(Byte byte)
        {
            bytes.push_back(byte);
        }

        void pop()
        {
            bytes.pop_back();
        }

        void encrypt(const Key& key);
        void decrypt(const Key& key);
    };

    class File {
    public:
        using Path = std::filesystem::path;
        using Size = std::streamsize;
        using Stream = std::fstream;

        enum class Type {
            INPUT,
            OUTPUT
        };
    private:
        Path path;
        Size size;
        mutable Stream stream;
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

        void remove()
        {
            // Remove this file using standard filesystem manipulations.
            std::filesystem::remove(path);
        }

        void writeBlock(const Block& block);
        void writeKey(const Key& key);
    };

    namespace errors
    {
        class InvalidFileIO : public std::exception {
        public:
            InvalidFileIO() noexcept = default;

            InvalidFileIO(const InvalidFileIO& other) = default;
            InvalidFileIO(InvalidFileIO&& other) noexcept = default;

            virtual ~InvalidFileIO() noexcept = default;

            InvalidFileIO& operator =(const InvalidFileIO& other) = default;
            InvalidFileIO& operator =(InvalidFileIO&& other) noexcept = default;

            const char* what() const noexcept override;
        };

        class InvalidInputFile : public std::exception {
        public:
            InvalidInputFile() noexcept = default;

            InvalidInputFile(const InvalidInputFile& other) = default;
            InvalidInputFile(InvalidInputFile&& other) noexcept = default;

            virtual ~InvalidInputFile() noexcept = default;

            InvalidInputFile& operator =(const InvalidInputFile& other) = default;
            InvalidInputFile& operator =(InvalidInputFile&& other) noexcept = default;

            const char* what() const noexcept override;
        };

        class InvalidOutputFile : public std::exception {
        public:
            InvalidOutputFile() noexcept = default;

            InvalidOutputFile(const InvalidOutputFile& other) = default;
            InvalidOutputFile(InvalidOutputFile&& other) noexcept = default;

            virtual ~InvalidOutputFile() noexcept = default;

            InvalidOutputFile& operator =(const InvalidOutputFile& other) = default;
            InvalidOutputFile& operator =(InvalidOutputFile&& other) noexcept = default;

            const char* what() const noexcept override;
        };

        class InvalidPassword : public std::exception {
        public:
            InvalidPassword() noexcept = default;

            InvalidPassword(const InvalidPassword& other) = default;
            InvalidPassword(InvalidPassword&& other) noexcept = default;

            virtual ~InvalidPassword() noexcept = default;

            InvalidPassword& operator =(const InvalidPassword& other) = default;
            InvalidPassword& operator =(InvalidPassword&& other) noexcept = default;

            const char* what() const noexcept override;
        };
    }
}
