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

#ifndef FISHCODE_EVENTS_HPP
#define FISHCODE_EVENTS_HPP

#include <exception>
#include <string>
#include <wx/event.h>

namespace fc
{
    namespace events
    {
        enum {
            ID_CANCEL = 1,
            ID_CHOOSE,
            ID_DECRYPT,
            ID_ENCRYPT,
            ID_SET
        };

        constexpr auto ID_READY = ID_SET + 1;
        constexpr auto ID_FRAME = ID_READY + 1;

        class TaskException : public wxEvent {
            std::string prompt;
        public:
            TaskException(int id, const std::exception& ex) noexcept;

            TaskException(const TaskException& event) noexcept = default;
            TaskException(TaskException&& event) noexcept = delete;

            TaskException& operator =(const TaskException& event) noexcept = default;
            TaskException& operator =(TaskException&& event) noexcept = delete;

            virtual ~TaskException() noexcept override = default;

            inline wxEvent* Clone() const override
            {
                return new TaskException(*this);
            }

            inline const char* what() const noexcept
            {
                // Return C-style explanation string.
                return prompt.c_str();
            }
        };

        wxDECLARE_EVENT(EVT_TASK_EXCEPTION, TaskException);

        class UpdateDone : public wxEvent {
        public:
            UpdateDone(int id);

            UpdateDone(const UpdateDone& event) = default;
            UpdateDone(UpdateDone&& event) noexcept = delete;

            UpdateDone& operator=(const UpdateDone& event) = default;
            UpdateDone& operator=(UpdateDone&& event) noexcept = delete;

            virtual ~UpdateDone() noexcept override = default;

            inline wxEvent* Clone() const override
            {
                return new UpdateDone(*this);
            }
        };

        wxDECLARE_EVENT(EVT_UPDATE_DONE, UpdateDone);

        class UpdateProgress : public wxEvent {
            int progress;
        public:
            UpdateProgress(int id, int progress);

            UpdateProgress(const UpdateProgress& event) = default;
            UpdateProgress(UpdateProgress&& event) noexcept = delete;

            UpdateProgress& operator=(const UpdateProgress& event) = default;
            UpdateProgress& operator=(UpdateProgress&& event) noexcept = delete;

            virtual ~UpdateProgress() noexcept override = default;

            inline wxEvent* Clone() const override
            {
                return new UpdateProgress(*this);
            }

            inline int getProgress() const noexcept
            {
                return progress;
            }
        };

        wxDECLARE_EVENT(EVT_UPDATE_PROGRESS, UpdateProgress);
    }
}

#endif // FISHCODE_EVENTS_HPP
