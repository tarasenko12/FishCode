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

#ifndef FISHCODE_ARGUMENTS_HPP
#define FISHCODE_ARGUMENTS_HPP

#include <filesystem>
#include "file.hpp"
#include "password.hpp"
#include "string.hpp"

namespace fc {
  struct Arguments {
    Arguments() = default;
    Arguments(
      const std::filesystem::path& pathToInputFile,
      const bool encryptedInputFile,
      const std::filesystem::path& pathToOutputFile,
      const string_t& passwordString
    );
    Arguments(const Arguments& otherArguments) = delete;
    Arguments(Arguments&& otherArguments) = default;
    
    Arguments& operator=(const Arguments& otherArguments) = delete;
    Arguments& operator=(Arguments&& otherArguments) = default;
    
    InputFile inputFile;
    OutputFile outputFile;
    Password password;
  };
}

#endif // FISHCODE_ARGUMENTS_HPP

