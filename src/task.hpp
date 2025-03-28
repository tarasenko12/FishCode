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

#ifndef FISHCODE_TASK_HPP
#define FISHCODE_TASK_HPP

#include <atomic>
#include <filesystem>
#include <memory>
#include <utility>
#include <wx/event.h>
#include "file.hpp"
#include "password.hpp"

namespace fc
{
    class Task {
    private:
        File inputFile, outputFile;
        Password password;
    public:
        Task() = default;

        Task(const Task& task) = delete;
        Task(Task&& task) noexcept = default;

        virtual ~Task() noexcept = default;

        Task& operator =(const Task& task) = delete;
        Task& operator =(Task&& task) noexcept = default;

        File& getInputFile() noexcept
        {
            return inputFile;
        }

        File& getOutputFile() noexcept
        {
            return outputFile;
        }

        Password& getPassword() noexcept
        {
            return password;
        }

        void setInputFile(File&& file)
        {
            inputFile = std::move(file);
        }

        void setOutputFile(File&& file)
        {
            outputFile = std::move(file);
        }

        void setPassword(const Password& password)
        {
            this->password = password;
        }
    };

    extern std::atomic<bool> abortTask;

    void encrypt(wxEvtHandler* sink, std::unique_ptr<Task> task);
    void decrypt(wxEvtHandler* sink, std::unique_ptr<Task> task);
}

#endif // FISHCODE_TASK_HPP
