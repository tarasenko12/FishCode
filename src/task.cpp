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
#include <memory>
#include <wx/event.h>
#include "block.hpp"
#include "file.hpp"
#include "events.hpp"
#include "key.hpp"
#include "task.hpp"

// Task abortion is disabled by default.
std::atomic<bool> fc::abortTask(false);

void fc::encrypt(wxEvtHandler* sink, std::unique_ptr<fc::Task> task) try {
    // Obtain user data.
    auto& inputFile = task->getInputFile();
    auto& outputFile = task->getOutputFile();
    const auto& password = task->getPassword();

    // Calculate total number of full blocks in the input file.
    const auto total = inputFile.getSize() / Block::MAX_SIZE;

    // Calculate number of partial blocks in the input file.
    const auto partial = inputFile.getSize() % Block::MAX_SIZE;

    // Generate encryption key.
    auto key = Key::generate();

    // Encrypt the key.
    key.encrypt(password);

    // write decryption (encrypted) key to the output file.
    outputFile.writeKey(key);

    // Decrypt the key.
    key.decrypt(password);

    // Calculate 1% of blocks in the input file.
    const auto onePercent = total / 100;

    // Encrypt the input file by blocks.
    for (File::Size current = 0; current < total; current++) {
        // Check for task abortion.
        if (abortTask) {
            // Remove output file (user doesn't need it).
            outputFile.remove();

            // Terminate the thread.
            return;
        }

        // read one block from the file.
        auto block = inputFile.readBlock();

        // Encrypt the block.
        block.encrypt(key);

        // Store block to the output file.
        outputFile.writeBlock(block);

        // Calculate current percentage of task completition.
        const int percent = (current * 100) / total;

        // Check if there is a valuable progress.
        if (onePercent > 0) {
            if (current % onePercent == 0) {
                // Send a message about progress update.
                wxPostEvent(sink, events::UpdateProgress(events::ID_FRAME, percent));
            }
        }
    }

    // Check if there is a partial block.
    if (partial != 0 && !abortTask) {
        // read this block from the file.
        auto block = inputFile.readBlock(partial);

        // Encrypt the block.
        block.encrypt(key);

        // Store block to the output file.
        outputFile.writeBlock(block);
    }

    // Check for task abortion.
    if (!abortTask) {
        // Notify the main thread about task completition.
        wxPostEvent(sink, events::DoneEvent(events::ID_FRAME));
    }
    else {
        // Remove output file (user doesn't need it).
        outputFile.remove();
    }
}
catch (const std::exception& ex) {
    // Notify main thread about exception in the task thread.
    wxPostEvent(sink, events::TaskException(events::ID_FRAME, ex));
}

void fc::decrypt(wxEvtHandler* sink, std::unique_ptr<fc::Task> task) try {
    // Obtain user data.
    auto& inputFile = task->getInputFile();
    auto& outputFile = task->getOutputFile();
    const auto& password = task->getPassword();

    // Calculate total number of full blocks in the input file.
    const auto total = (inputFile.getSize() - Key::SIZE) / Block::MAX_SIZE;

    // Calculate number of partial blocks in the input file.
    const auto partial = (inputFile.getSize() - Key::SIZE) % Block::MAX_SIZE;

    // read decryption (encrypted) key from the input file.
    auto key = inputFile.readKey();

    // Decrypt the key.
    key.decrypt(password);

    // Calculate 1% of blocks in the input file.
    const auto onePercent = total / 100;

    // Decrypt the input file by blocks.
    for (File::Size current = 0; current < total; current++) {
        // Check for task abortion.
        if (abortTask) {
            // Remove output file (user doesn't need it).
            outputFile.remove();

            // Terminate the thread.
            return;
        }

        // read one block from the file.
        auto block = inputFile.readBlock();

        // Decrypt the block.
        block.decrypt(key);

        // Store block to the output file.
        outputFile.writeBlock(block);

        // Calculate current percentage of task completition.
        const int percent = (current * 100) / total;

        // Check if there is a valuable progress.
        if (onePercent > 0) {
            if (current % onePercent == 0) {
                // Send a message about progress update.
                wxPostEvent(sink, events::UpdateProgress(events::ID_FRAME, percent));
            }
        }
    }

    // Check if there is a partial block.
    if (partial != 0 && !abortTask) {
        // read this block from the file.
        auto block = inputFile.readBlock(partial);

        // Decrypt the block.
        block.decrypt(key);

        // Store block to the output file.
        outputFile.writeBlock(block);
    }

    // Check for task abortion.
    if (!abortTask) {
        // Notify the main thread about task completition.
        wxPostEvent(sink, events::DoneEvent(events::ID_FRAME));
    }
    else {
        // Remove output file (user doesn't need it).
        outputFile.remove();
    }
}
catch (const std::exception& ex) {
    // Notify main thread about exception in the task thread.
    wxPostEvent(sink, events::TaskException(events::ID_FRAME, ex));
}
