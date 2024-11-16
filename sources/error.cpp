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

#include "error.hpp"
#include "fishcode.hpp"

const char* fc::InvalidPasswordError::What() const noexcept {
  // Return corresponding error message.
  return "Error: invalid password!";
}

int fc::InvalidPasswordError::GetErrorCode() const noexcept {
  // Return corresponding error code.
  return Results::INVALID_PASSWORD;
}

const char* fc::InvalidInputFileError::What() const noexcept {
  // Return corresponding error message.
  return "Error: invalid input file!";
}

int fc::InvalidInputFileError::GetErrorCode() const noexcept {
  // Return corresponding error code.
  return Results::INVALID_INPUT_FILE;
}

const char* fc::InvalidOutputFileError::What() const noexcept {
  // Return corresponding error message.
  return "Error: invalid output file!";
}

int fc::InvalidOutputFileError::GetErrorCode() const noexcept {
  // Return corresponding error code.
  return Results::INVALID_OUTPUT_FILE;
}

const char* fc::InvalidUsageError::What() const noexcept {
  // Return corresponding error message.
  return "Error: invalid usage!";
}

int fc::InvalidUsageError::GetErrorCode() const noexcept {
  // Return corresponding error code.
  return Results::INVALID_USAGE;
}

const char* fc::InvalidSubcommandError::What() const noexcept {
  // Return corresponding error message.
  return "Error: invalid subcommand!";
}

int fc::InvalidSubcommandError::GetErrorCode() const noexcept {
  // Return corresponding error code.
  return Results::INVALID_SUBCOMMAND;
}

