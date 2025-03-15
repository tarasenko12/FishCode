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
#include <memory>
#include <utility>
#include <wx/event.h>
#include "file.hpp"
#include "password.hpp"
#include "types.hpp"

namespace fc
{
    class TaskData {
    public:
        TaskData() = default;

        TaskData(const TaskData& data) = delete;
        TaskData(TaskData&& data) noexcept = default;

        virtual ~TaskData() noexcept = default;

        TaskData& operator =(const TaskData& data) = delete;
        TaskData& operator =(TaskData&& data) noexcept = default;

        inline File& getInputFile() noexcept
        {
            return input_file;
        }

        inline File& getOutputFile() noexcept
        {
            return output_file;
        }

        inline Password& getPassword() noexcept
        {
            return password;
        }

        inline void setInputFile(File&& input_file) noexcept
        {
            this->input_file = std::move(input_file);
        }

        inline void setOutputFile(File&& output_file) noexcept
        {
            this->output_file = std::move(output_file);
        }

        inline void setPassword(Password&& password) noexcept
        {
            this->password = std::move(password);
        }
    protected:
        File input_file, output_file;
        Password password;
    };

    extern std::atomic<bool> abort_task;

    void checkFileIO(const Path& if_path, const Path& of_path);

    void encrypt(wxEvtHandler* sink, std::unique_ptr<TaskData> data);
    void decrypt(wxEvtHandler* sink, std::unique_ptr<TaskData> data);
}

#endif // FISHCODE_TASK_HPP
