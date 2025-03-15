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

#ifndef FISHCODE_FRAME_HPP
#define FISHCODE_FRAME_HPP

#include <array>
#include <memory>
#include <thread>
#include <wx/event.h>
#include <wx/frame.h>
#include <wx/msgdlg.h>
#include <wx/string.h>
#include <wx/timer.h>
#include "button.hpp"
#include "events.hpp"
#include "field.hpp"
#include "label.hpp"
#include "progress.hpp"
#include "strings.hpp"

namespace fc
{
    class Frame : public wxFrame {
    public:
        Frame();

        Frame(const Frame& frame) = delete;
        Frame(Frame&& frame) noexcept = delete;

        Frame& operator =(const Frame& frame) = delete;
        Frame& operator =(Frame&& frame) noexcept = delete;

        virtual ~Frame() noexcept override = default;

        void onAbout(wxCommandEvent& event);
        void onCancel(wxCommandEvent& event);
        void onChoose(wxCommandEvent& event);
        void onClose(wxCloseEvent& event);
        void onDecrypt(wxCommandEvent& event);
        void onEncrypt(wxCommandEvent& event);
        void onHelp(wxCommandEvent& event);
        void onReadyTimer(wxTimerEvent& event);
        void onSet(wxCommandEvent& event);

        void onDoneUpdate(events::UpdateDone& event);
        void onTaskException(events::TaskException& event);
        void onProgressUpdate(events::UpdateProgress& event);
    protected:
        inline wxString getIFPathValue() const
        {
            return fields[0]->GetValue();
        }

        inline wxString getOFPathValue() const
        {
            return fields[1]->GetValue();
        }

        inline wxString getPasswordValue() const
        {
            return fields[2]->GetValue();
        }

        inline void setIFPathValue(const wxString& value)
        {
            fields[0]->ChangeValue(value);
        }

        inline void setOFPathValue(const wxString& value)
        {
            fields[1]->ChangeValue(value);
        }

        inline void disableCancelButton()
        {
            buttons[4]->Disable();
        }

        void disableButtons();
        void disableFields();

        inline void disableProgressBar()
        {
            progress_bar->Disable();
        }

        inline void enableCancelButton()
        {
            buttons[4]->Enable();
        }

        void enableButtons();
        void enableFields();

        inline void enableProgressBar()
        {
            progress_bar->Enable();
        }
    private:
        std::unique_ptr<std::thread> task_thread;
        std::array<Button*, 5> buttons;
        std::array<Field*, 3> fields;
        std::array<Label*, 3> labels;
        std::unique_ptr<wxTimer> ready_timer;
        ProgressBar* progress_bar;
    };
}

#endif // FISHCODE_FRAME_HPP
