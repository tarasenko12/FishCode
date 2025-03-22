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

module;

#include <array>
#include <atomic>
#include <memory>
#include <thread>
#include <utility>
#include <wx/wx.h>
#include "events/events.hpp"

export module ui;

import core;
import data;

std::atomic<bool> abortTask = false;

export namespace fc
{
    class Button : public wxButton {
    public:
        Button(wxWindow* parent, wxWindowID id, const wxString& label);

        Button(const Button& button) = delete;
        Button(Button&& button) noexcept = delete;

        Button& operator =(const Button& button) = delete;
        Button& operator =(Button&& button) noexcept = delete;

        virtual ~Button() noexcept override = default;
    };

    class Field : public wxTextCtrl {
    public:
        Field(wxWindow* parent);
        Field(
            wxWindow* parent,
            wxWindowID id,
            const wxString& value,
            const wxPoint& position,
            const wxSize& size,
            long style
        );

        Field(const Field& field) = delete;
        Field(Field&& field) noexcept = delete;

        Field& operator =(const Field& field) = delete;
        Field& operator =(Field&& field) noexcept = delete;

        virtual ~Field() noexcept override = default;
    };

    class PasswordField : public Field {
    public:
        PasswordField(wxWindow* parent);

        PasswordField(const PasswordField& field) = delete;
        PasswordField(PasswordField&& field) noexcept = delete;

        PasswordField& operator =(const PasswordField& field) = delete;
        PasswordField& operator =(PasswordField&& field) noexcept = delete;

        virtual ~PasswordField() noexcept override = default;
    };

    class Label : public wxStaticText {
    public:
        Label(wxWindow* parent, const wxString& text);

        Label(const Label& label) = delete;
        Label(Label&& label) noexcept = delete;

        Label& operator =(const Label& label) = delete;
        Label& operator =(Label&& label) noexcept = delete;

        virtual ~Label() noexcept override = default;
    };

    class ProgressBar : public wxGauge {
    public:
        ProgressBar(wxWindow* parent);

        ProgressBar(const ProgressBar& bar) = delete;
        ProgressBar(ProgressBar&& bar) noexcept = delete;

        ProgressBar& operator =(const ProgressBar& bar) = delete;
        ProgressBar& operator =(ProgressBar&& bar) noexcept = delete;

        virtual ~ProgressBar() noexcept override = default;
    };

    class TaskData {
        File inputFile, outputFile;
        Password password;
    public:
        TaskData() = default;

        TaskData(const TaskData& data) = delete;
        TaskData(TaskData&& data) noexcept = default;

        virtual ~TaskData() noexcept = default;

        TaskData& operator =(const TaskData& data) = delete;
        TaskData& operator =(TaskData&& data) noexcept = default;

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

        void setInputFile(File&& inputFile) noexcept
        {
            this->inputFile = std::move(inputFile);
        }

        void setOutputFile(File&& outputFile) noexcept
        {
            this->outputFile = std::move(outputFile);
        }

        void setPassword(Password&& password) noexcept
        {
            this->password = std::move(password);
        }
    };

    class Frame : public wxFrame {
        std::unique_ptr<std::thread> taskThread;
        std::array<Button*, 5> buttons;
        std::array<Field*, 3> fields;
        std::array<Label*, 3> labels;
        std::unique_ptr<wxTimer> readyTimer;
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
        void onEncrypt(wxCommandEvent& event);
        void onHelp(wxCommandEvent& event);
        void onReadyTimer(wxTimerEvent& event);
        void onSet(wxCommandEvent& event);

        void onDoneUpdate(events::UpdateDone& event);
        void onTaskException(events::TaskException& event);
        void onProgressUpdate(events::UpdateProgress& event);
    protected:
        wxString getIFPathValue() const
        {
            return fields[0]->GetValue();
        }

        wxString getOFPathValue() const
        {
            return fields[1]->GetValue();
        }

        wxString getPasswordValue() const
        {
            return fields[2]->GetValue();
        }

        void setIFPathValue(const wxString& value)
        {
            fields[0]->ChangeValue(value);
        }

        void setOFPathValue(const wxString& value)
        {
            fields[1]->ChangeValue(value);
        }

        void disableCancelButton()
        {
            buttons[4]->Disable();
        }

        void disableButtons();
        void disableFields();

        void disableProgressBar()
        {
            progressBar->Disable();
        }

        void enableCancelButton()
        {
            buttons[4]->Enable();
        }

        void enableButtons();
        void enableFields();

        void enableProgressBar()
        {
            progressBar->Enable();
        }
    };

    void checkFileIO(const File::Path& ifPath, const File::Path& ofPath);

    void encrypt(wxEvtHandler* sink, std::unique_ptr<TaskData> data);
    void decrypt(wxEvtHandler* sink, std::unique_ptr<TaskData> data);
}
