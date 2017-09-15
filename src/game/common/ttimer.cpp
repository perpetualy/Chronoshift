/**
 * @file
 *
 * @Author CCHyper, OmniBlade
 *
 * @brief Templated timers intended to tick on either the system timer or a frame.
 *
 * @copyright Redalert++ is free software: you can redistribute it and/or
 *            modify it under the terms of the GNU General Public License
 *            as published by the Free Software Foundation, either version
 *            2 of the License, or (at your option) any later version.
 *
 *            A full copy of the GNU General Public License can be found in
 *            LICENSE
 */
#include "ttimer.h"
#include "globals.h"
#include "ostimer.h"

int SystemTimerClass::operator()() const
{
    if (PlatformTimer != nullptr) {
        return PlatformTimer->Get_System_Tick_Count();
    }

    return 0;
}

int FrameTimerClass::operator()() const
{
    return g_frame;
}