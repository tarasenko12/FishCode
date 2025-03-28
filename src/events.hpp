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
            ID_FRAME = 1,
            ID_CANCEL,
            ID_CHOOSE,
            ID_DECRYPT,
            ID_ENCRYPT,
            ID_SET
        };

        class TaskException : public wxEvent {
            std::string prompt;
        public:
            TaskException(int id, const std::exception& ex) noexcept;

            TaskException(const TaskException& event) noexcept = default;
            TaskException(TaskException&& event) noexcept = delete;

            TaskException& operator =(const TaskException& event) noexcept = default;
            TaskException& operator =(TaskException&& event) noexcept = delete;

            virtual ~TaskException() noexcept override = default;

            wxEvent* Clone() const override
            {
                return new TaskException(*this);
            }

            const char* what() const noexcept
            {
                // Return C-style explanation string.
                return prompt.c_str();
            }
        };

        wxDECLARE_EVENT(EVT_TASK_EXCEPTION, TaskException);

        class DoneEvent : public wxEvent {
        public:
            DoneEvent(int id);

            DoneEvent(const DoneEvent& event) = default;
            DoneEvent(DoneEvent&& event) noexcept = delete;

            DoneEvent& operator =(const DoneEvent& event) = default;
            DoneEvent& operator =(DoneEvent&& event) noexcept = delete;

            virtual ~DoneEvent() noexcept override = default;

            wxEvent* Clone() const override
            {
                return new DoneEvent(*this);
            }
        };

        wxDECLARE_EVENT(EVT_UPDATE_DONE, DoneEvent);

        class UpdateProgress : public wxEvent {
            int progress;
        public:
            UpdateProgress(int id, int progress);

            UpdateProgress(const UpdateProgress& event) = default;
            UpdateProgress(UpdateProgress&& event) noexcept = delete;

            UpdateProgress& operator =(const UpdateProgress& event) = default;
            UpdateProgress& operator =(UpdateProgress&& event) noexcept = delete;

            virtual ~UpdateProgress() noexcept override = default;

            wxEvent* Clone() const override
            {
                return new UpdateProgress(*this);
            }

            int GetProgress() const noexcept
            {
                return progress;
            }
        };

        wxDECLARE_EVENT(EVT_UPDATE_PROGRESS, UpdateProgress);

        class ReadyEvent : public wxEvent {
        public:
            ReadyEvent(int id);

            ReadyEvent(const ReadyEvent& event) = default;
            ReadyEvent(ReadyEvent&& event) noexcept = delete;

            ReadyEvent& operator =(const ReadyEvent& event) = default;
            ReadyEvent& operator =(ReadyEvent&& event) noexcept = delete;

            virtual ~ReadyEvent() noexcept override = default;

            wxEvent* Clone() const override
            {
                return new ReadyEvent(*this);
            }
        };

        wxDECLARE_EVENT(EVT_READY_EVENT, ReadyEvent);
    }
}

#endif // FISHCODE_EVENTS_HPP
