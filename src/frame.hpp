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
#include "button.hpp"
#include "events.hpp"
#include "field.hpp"
#include "file.hpp"
#include "label.hpp"
#include "password.hpp"
#include "progress.hpp"
#include "strings.hpp"
#include "task.hpp"

namespace fc
{
    class Frame : public wxFrame {
    private:
        std::unique_ptr<std::thread> taskThread;
        std::unique_ptr<std::thread> timerThread;
        std::array<Button*, 5> buttons;
        std::array<Field*, 3> fields;
        std::array<Label*, 3> labels;
        ProgressBar* progressBar;
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
        void onDone(events::DoneEvent& event);
        void onEncrypt(wxCommandEvent& event);
        void onHelp(wxCommandEvent& event);
        void onProgressUpdate(events::UpdateProgress& event);
        void onReady(events::ReadyEvent& event);
        void onTaskException(events::TaskException& event);
        void onSet(wxCommandEvent& event);
    protected:
        File::Path getIFPath() const
        {
            return File::Path(fields[0]->GetValue().utf8_string());
        }

        File::Path getOFPath() const
        {
            return File::Path(fields[1]->GetValue().utf8_string());
        }

        Password::String getPasswordString() const
        {
            return Password::String(fields[2]->GetValue().utf8_string());
        }

        void setIFPath(const File::Path& path)
        {
            fields[0]->ChangeValue(path.string());
        }

        void setOFPath(const File::Path& path)
        {
            fields[1]->ChangeValue(path.string());
        }

        void disableProgressBar()
        {
            progressBar->Disable();
        }

        void enableProgressBar()
        {
            progressBar->Enable();
        }

        void disableCancelButton();
        void disableButtons();
        void disableFields();
        void enableCancelButton();
        void enableButtons();
        void enableFields();
    };
}

#endif // FISHCODE_FRAME_HPP
