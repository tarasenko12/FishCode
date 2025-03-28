/*
** Copyright (C) 2025 Vitaliy Tarasenko.
**
** This file is part of FishCode.
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
*/

#ifndef FISHCODE_STRINGS_HPP
#define FISHCODE_STRINGS_HPP

namespace fc
{
    namespace strings
    {
        constexpr auto CAPTION0 = "User documentation";
        constexpr auto CAPTION1 = "Choose an input file";
        constexpr auto CAPTION2 = "Set an output file";
        constexpr auto CAPTION3 = "Fatal error!";
        constexpr auto CAPTION4 = "Error!";
        constexpr auto COPYRIGHT = "Copyright (C) 2025 Vitaliy Tarasenko.";
        constexpr auto DESCRYPTION =
            "FishCode (fishcode) is a program for encrypting and decrypting files.\n\nFishCode is free software: "
            "you can redistribute it and/or modify it under the terms of the GNU General Public License as published "
            "by the Free Software Foundation, either version 3 of the License, or (at your option) any later "
            "version.\n\nFishCode is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; "
            "without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the "
            "GNU General Public License for more details.";
        constexpr auto DEVELOPER = "Vitaliy Tarasenko";
        constexpr auto DOCUMENTATION =
            "\tFishCode interface consists of two main components: the main window and an additional menu called "
            "\"More...\".\n\n\tThe main window has three input fields (\"Input file\", \"Output file\","
            " \"Password\") and five buttons (\"Choose...\", \"Set...\", \"Encrypt\", \"Decrypt\","
            " \"Cancel\").\n\n\t\"Input file\" and \"Output file\" fields are for entering path to the "
            "corresponding files on the disk.\n\n\tThe file path can be either absolute, such as "
            "\"/home/user/Documents/file\", or relative, such as \"Documents/file\".\n\n\t\"Choose...\" and "
            "\"Set...\" buttons are alternative ways to identify the relevant files. These buttons bring up the "
            "corresponding dialog boxes.\n\n\t\"Encrypt\" and \"Decrypt\" buttons perform the operations "
            "corresponding to their name. Status of the operation is displayed in the progress bar and at the bottom "
            "of the window, in the status field.\n\n\tThe \"Cancel\" button can abort encryption or decryption task."
            "\n\n\tNote: password cannot contain spaces, non-Latin letters and symbols that are not part of the "
            "ASCII character set.";
        constexpr auto LABEL0 = "Input file:";
        constexpr auto LABEL1 = "Output file:";
        constexpr auto LABEL2 = "Choose...";
        constexpr auto LABEL3 = "Set...";
        constexpr auto LABEL4 = "Password:";
        constexpr auto LABEL5 = "Encrypt";
        constexpr auto LABEL6 = "Decrypt";
        constexpr auto LABEL7 = "Cancel";
        constexpr auto NAME0 = "FishCode";
        constexpr auto NAME1 = "More...";
        constexpr auto NAME2 = "About";
        constexpr auto NAME3 = "Help";
        constexpr auto PATTERN0 = "HOME";
        constexpr auto PROMPT0 = "Get more information about the program.";
        constexpr auto PROMPT1 = "Get user documentation.";
        constexpr auto STATUS0 = "Ready";
        constexpr auto STATUS1 = "All done";
        constexpr auto STATUS2 = "Abort";
        constexpr auto STATUS3 = "Encrypting...";
        constexpr auto STATUS4 = "Decrypting...";
        constexpr auto VERSION = "v0.2";
    }
}

#endif // FISHCODE_STRINGS_HPP
