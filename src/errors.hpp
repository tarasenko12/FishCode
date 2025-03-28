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

#ifndef FISHCODE_ERRORS_HPP
#define FISHCODE_ERRORS_HPP

#include <exception>

namespace fc
{
    namespace errors
    {
        class InvalidFileIO : public std::exception {
        public:
            InvalidFileIO() noexcept = default;

            InvalidFileIO(const InvalidFileIO& ex) = default;
            InvalidFileIO(InvalidFileIO&& ex) noexcept = default;

            ~InvalidFileIO() noexcept = default;

            InvalidFileIO& operator =(const InvalidFileIO& ex) = default;
            InvalidFileIO& operator =(InvalidFileIO&& ex) noexcept = default;

            const char* what() const noexcept override;
        };

        class InvalidInputFile : public std::exception {
        public:
            InvalidInputFile() noexcept = default;
            InvalidInputFile(const InvalidInputFile& ex) = default;
            InvalidInputFile(InvalidInputFile&& ex) noexcept = default;

            ~InvalidInputFile() noexcept = default;

            InvalidInputFile& operator =(const InvalidInputFile& ex) = default;
            InvalidInputFile& operator =(InvalidInputFile&& ex) noexcept = default;

            const char* what() const noexcept override;
        };

        class InvalidOutputFile : public std::exception {
        public:
            InvalidOutputFile() noexcept = default;
            InvalidOutputFile(const InvalidOutputFile& ex) = default;
            InvalidOutputFile(InvalidOutputFile&& ex) noexcept = default;

            ~InvalidOutputFile() noexcept = default;

            InvalidOutputFile& operator =(const InvalidOutputFile& ex) = default;
            InvalidOutputFile& operator =(InvalidOutputFile&& ex) noexcept = default;

            const char* what() const noexcept override;
        };

        class InvalidPassword : public std::exception {
        public:
            InvalidPassword() noexcept = default;
            InvalidPassword(const InvalidPassword& ex) = default;
            InvalidPassword(InvalidPassword&& ex) noexcept = default;

            ~InvalidPassword() noexcept = default;

            InvalidPassword& operator =(const InvalidPassword& ex) = default;
            InvalidPassword& operator =(InvalidPassword&& ex) noexcept = default;

            const char* what() const noexcept override;
        };
    }
}

#endif // FISHCODE_ERRORS_HPP
