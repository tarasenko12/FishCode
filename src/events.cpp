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

#include <exception>
#include <wx/event.h>
#include "events.hpp"

wxDEFINE_EVENT(fc::events::EVT_TASK_EXCEPTION, fc::events::TaskException);

fc::events::TaskException::TaskException(int id, const std::exception& ex) noexcept
: wxEvent(id, fc::events::EVT_TASK_EXCEPTION), prompt(ex.what())
{

}

wxDEFINE_EVENT(fc::events::EVT_UPDATE_DONE, fc::events::DoneEvent);

fc::events::DoneEvent::DoneEvent(int id)
: wxEvent(id, fc::events::EVT_UPDATE_DONE)
{

}

wxDEFINE_EVENT(fc::events::EVT_UPDATE_PROGRESS, fc::events::UpdateProgress);

fc::events::UpdateProgress::UpdateProgress(int id, const int progress)
: wxEvent(id, fc::events::EVT_UPDATE_PROGRESS), progress(progress)
{

}

wxDEFINE_EVENT(fc::events::EVT_READY_EVENT, fc::events::ReadyEvent);

fc::events::ReadyEvent::ReadyEvent(int id)
: wxEvent(id, fc::events::EVT_READY_EVENT)
{

}
