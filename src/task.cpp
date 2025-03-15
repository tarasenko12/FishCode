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
**
** This program uses wxWidgets, a free and open-source cross-platform C++
** library for creating GUIs. wxWidgets is licensed under the wxWindows
** Library License, which is compatible with the GNU GPL.
** See <https://www.wxwidgets.org/about/licence/>.
*/

#include <atomic>
#include <exception>
#include <ios>
#include <memory>
#include <wx/event.h>
#include "block.hpp"
#include "errors.hpp"
#include "events.hpp"
#include "key.hpp"
#include "task.hpp"
#include "types.hpp"

// Disable task abortion (default).
std::atomic<bool> fc::abort_task(false);

void fc::checkFileIO(const fc::Path& if_path, const fc::Path& of_path)
{
  // Check if pathes are not equivalent.
  if (std::filesystem::exists(if_path) && std::filesystem::exists(of_path)) {
    if (std::filesystem::equivalent(if_path, of_path)) {
      // Invalid file I/O.
      throw errors::InvalidFileIO();
    }
  }
}

void fc::encrypt(wxEvtHandler* sink, std::unique_ptr<fc::TaskData> data) try {
    // Obtain user data.
    auto& input_file = data->getInputFile();
    auto& output_file = data->getOutputFile();
    const auto& password = data->getPassword();

    // Calculate total number of full blocks in the input file.
    const auto total = input_file.getSize() / Block::MAX_SIZE;

    // Calculate number of partial blocks in the input file.
    const auto partial = input_file.getSize() % Block::MAX_SIZE;

    // Generate encryption key.
    auto key = Key::generate();

    // Encrypt the key.
    key.encrypt(password);

    // Write decryption (encrypted) key to the output file.
    output_file.writeKey(key);

    // Decrypt the key.
    key.decrypt(password);

    // Calculate 1% of blocks in the input file.
    const auto one_percent = total / 100;

    // Encrypt the input file by blocks.
    for (Index current = 0; current < total; current++) {
        // Check for task abortion.
        if (abort_task) {
            // Remove output file (user doesn't need it).
            output_file.remove();

            // Terminate the thread.
            return;
        }

        // Read one block from the file.
        auto block = input_file.readBlock();

        // Encrypt the block.
        block.encrypt(key);

        // Store block to the output file.
        output_file.writeBlock(block);

        // Calculate current percentage of task completition.
        const int percent = (current * 100) / total;

        // Check if there is a valuable progress.
        if (one_percent > 0) {
            if (current % one_percent == 0) {
                // Send a message about progress update.
                wxPostEvent(sink, events::UpdateProgress(fc::events::ID_FRAME, percent));
            }
        }
    }

    // Check if there is a partial block.
    if (partial != 0 && !abort_task) {
        // Read this block from the file.
        auto block = input_file.readBlock(partial);

        // Encrypt the block.
        block.encrypt(key);

        // Store block to the output file.
        output_file.writeBlock(block);
    }

    // Check for task abortion.
    if (!abort_task) {
        // Notify the main thread about task completition.
        wxPostEvent(sink, events::UpdateDone(fc::events::ID_FRAME));
    }
    else {
        // Remove output file (user doesn't need it).
        output_file.remove();
    }
}
catch (const std::exception& ex) {
    // Notify main thread about exception in the task thread.
    wxPostEvent(sink, events::TaskException(events::ID_FRAME, ex));
}

void fc::decrypt(wxEvtHandler* sink, std::unique_ptr<fc::TaskData> data) try {
    // Obtain user data.
    auto& input_file = data->getInputFile();
    auto& output_file = data->getOutputFile();
    const auto& password = data->getPassword();

    // Calculate total number of full blocks in the input file.
    const auto total = (input_file.getSize() - Key::SIZE) / Block::MAX_SIZE;

    // Calculate number of partial blocks in the input file.
    const auto partial = (input_file.getSize() - Key::SIZE) % Block::MAX_SIZE;

    // Read decryption (encrypted) key from the input file.
    auto key = input_file.readKey();

    // Decrypt the key.
    key.decrypt(password);

    // Calculate 1% of blocks in the input file.
    const auto one_percent = total / 100;

    // Decrypt the input file by blocks.
    for (Index current = 0; current < total; current++) {
        // Check for task abortion.
        if (abort_task) {
            // Remove output file (user doesn't need it).
            output_file.remove();

            // Terminate the thread.
            return;
        }

        // Read one block from the file.
        auto block = input_file.readBlock();

        // Decrypt the block.
        block.decrypt(key);

        // Store block to the output file.
        output_file.writeBlock(block);

        // Calculate current percentage of task completition.
        const int percent = (current * 100) / total;

        // Check if there is a valuable progress.
        if (one_percent > 0) {
            if (current % one_percent == 0) {
                // Send a message about progress update.
                wxPostEvent(sink, events::UpdateProgress(fc::events::ID_FRAME, percent));
            }
        }
    }

    // Check if there is a partial block.
    if (partial != 0 && !abort_task) {
        // Read this block from the file.
        auto block = input_file.readBlock(partial);

        // Decrypt the block.
        block.decrypt(key);

        // Store block to the output file.
        output_file.writeBlock(block);
    }

    // Check for task abortion.
    if (!abort_task) {
        // Notify the main thread about task completition.
        wxPostEvent(sink, events::UpdateDone(fc::events::ID_FRAME));
    }
    else {
        // Remove output file (user doesn't need it).
        output_file.remove();
    }
}
catch (const std::exception& ex) {
    // Notify main thread about exception in the task thread.
    wxPostEvent(sink, events::TaskException(events::ID_FRAME, ex));
}
