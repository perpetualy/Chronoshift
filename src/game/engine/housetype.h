/**
 * @file
 *
 * @author CCHyper
 * @author OmniBlade
 *
 * @brief Class holding information on house types.
 *
 * @copyright Redalert++ is free software: you can redistribute it and/or
 *            modify it under the terms of the GNU General Public License
 *            as published by the Free Software Foundation, either version
 *            2 of the License, or (at your option) any later version.
 *            A full copy of the GNU General Public License can be found in
 *            LICENSE
 */
#pragma once

#ifndef HOUSETYPE_H
#define HOUSETYPE_H

#include "always.h"
#include "abstract.h"
#include "fixed.h"
#include "heap.h"
#include "noinit.h"
#include "remap.h"

class CCINIClass;

class HouseTypeClass : public AbstractTypeClass
{
public:
    HouseTypeClass(HousesType type, const char *name, int uiname, const char *suffix, int lemon_factor,
        PlayerColorType color, char prefix);
    HouseTypeClass(HouseTypeClass const &that);
    HouseTypeClass(NoInitClass const &noinit) : AbstractTypeClass(noinit) {}
    virtual ~HouseTypeClass() {}

    virtual BOOL Read_INI(CCINIClass &ini);

    uint8_t *Remap_Table();
    void Code_Pointers() {}
    void Decode_Pointers() {}

    void *operator new(size_t size);
    void *operator new(size_t size, void *ptr) { return ptr; }
    void operator delete(void *ptr);
#ifndef COMPILER_WATCOM // Watcom doesn't like this, MSVC/GCC does.
    void operator delete(void *ptr, void *place) {}
#endif

    static void One_Time() {}
    static void Init_Heap();
    static HousesType From_Name(const char *name);
    static HouseTypeClass &As_Reference(HousesType type);

private:
    HousesType Type;
    char HouseName[256];
    int LemonFactor;
    PlayerColorType Color; // Color to use when displaying objects owned by this country.
    char Prefix;
    fixed Firepower; // Multiplier to firepower for all weapons [larger means more damage]
    fixed Groundspeed; // Multiplier to speed for all ground units [larger means faster]
    fixed Airspeed; // Multiplier to speed for all air units [larger means faster]
    fixed Armor; // Multiplier to armor damage for all units and buildings [larger means more damage]
    fixed ROF; // Multiplier to Rate Of Fire for all weapons [larger means slower ROF]
    fixed Cost; // Multiplier to cost for all units and buildings [larger means costlier]
    fixed BuildTime; // Multiplier to general object build time [larger means longer to build]
};

#ifndef RAPP_STANDALONE
#include "hooker.h"
extern TFixedIHeapClass<HouseTypeClass> &HouseTypes;
#else
extern TFixedIHeapClass<HouseTypeClass> HouseTypes;
#endif

#endif // HOUSETYPE_H
