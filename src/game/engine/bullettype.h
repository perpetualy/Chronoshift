/**
 * @file
 *
 * @author OmniBlade
 * @author CCHyper
 *
 * @brief Class containing information about projectile behaviour.
 *
 * @copyright Chronoshift is free software: you can redistribute it and/or
 *            modify it under the terms of the GNU General Public License
 *            as published by the Free Software Foundation, either version
 *            2 of the License, or (at your option) any later version.
 *            A full copy of the GNU General Public License can be found in
 *            LICENSE
 */
#pragma once

#ifndef BULLETTYPE_H
#define BULLETTYPE_H

#include "always.h"
#include "heap.h"
#include "objecttype.h"

class GameINIClass;

// If you add an entry here, add matching entries to bullettype.cpp globals and Init_Heap.
enum BulletType
{
    BULLET_INVISIBLE,
    BULLET_CANNON,
    BULLET_ACK,
    BULLET_TORPEDO,
    BULLET_FROG,
    BULLET_HEATSEEKER,
    BULLET_LASERGUIDED,
    BULLET_LOBBED,
    BULLET_BOMBLET,
    BULLET_BALLISTIC,
    BULLET_PARACHUTE ,
    BULLET_FIREBALL,
    BULLET_LEAPDOG,
    BULLET_CATAPULT,
    BULLET_AAMISSILE,
    BULLET_GPSSATELLITE,
    BULLET_NUKEUP,
    BULLET_NUKEDOWN,
    BULLET_COUNT,

    BULLET_NONE = -1,
    BULLET_FIRST = BULLET_INVISIBLE,
};

DEFINE_ENUMERATION_OPERATORS(BulletType);

class BulletTypeClass : public ObjectTypeClass
{
public:
    BulletTypeClass(BulletType bullet, const char *name);
    BulletTypeClass(const BulletTypeClass &that);
    BulletTypeClass(const NoInitClass &noinit) : ObjectTypeClass(noinit) {}
    ~BulletTypeClass() {}

    void *operator new(size_t size);
    void *operator new(size_t size, void *ptr) { return ptr; }
    void operator delete(void *ptr);
#ifndef COMPILER_WATCOM // Watcom doesn't like this, MSVC/GCC does.
    void operator delete(void *ptr, void *place) {}
#endif

    virtual BOOL Create_And_Place(cell_t cellnum, HousesType house = HOUSES_NONE) const override { return false; };
    virtual ObjectClass *Create_One_Of(HouseClass *house) const override { return nullptr; }
    virtual BOOL Read_INI(GameINIClass &ini);

    void Code_Pointers() {}
    void Decode_Pointers() {}

    BOOL Get_High() const { return m_High; }
    BOOL Draw_Shadow() const { return m_Shadow; }
    BOOL Get_Arcing() const { return m_Arcing; }
    BOOL Is_Dropping() const { return m_Dropping; }
    BOOL Invisible() const { return m_Inviso; }
    BOOL Get_Proximity() const { return m_Proximity; }
    BOOL Animates() const { return m_Animates; }
    BOOL Ranged() const { return m_Ranged; }
    BOOL Rotates() const { return !m_NoRotate; }
    BOOL Is_Inaccurate() const { return m_Inaccurate; }
    BOOL Is_Translucent() const { return m_Translucent; }
    BOOL Is_Anti_Air() const { return m_AntiAir; }
    BOOL Is_Anti_Ground() const { return m_AntiGround; }
    BOOL Is_Anti_Sub_Warfare() const { return m_AntiSubWarfare; }
    BOOL Degenerates() const { return m_Degenerates; }
    BOOL Is_UnderWater() const { return m_UnderWater; }
    BOOL Get_Parachuted() const { return m_Parachuted; }
    BOOL Get_Gigundo() const { return m_Gigundo; }
    uint8_t Rate_Of_Turn() const { return m_ROT; }
    int Arming_Delay() const { return m_Arm; }
    int Get_Frames() const { return m_Frames; }

    BulletType What_Type() const { return m_Type; }

    static void Init_Heap();
    static void One_Time();
    static BulletType From_Name(const char *name);
    static const char *Name_From(BulletType bullet);
    static BulletTypeClass &As_Reference(BulletType bullet);
    static BulletTypeClass *As_Pointer(BulletType bullet);

private:
#ifndef CHRONOSHIFT_NO_BITFIELDS
    BOOL m_High : 1; // 1
    BOOL m_Shadow : 1; // 2
    BOOL m_Arcing : 1; // 4
    BOOL m_Dropping : 1; // 8
    BOOL m_Inviso : 1; // 16
    BOOL m_Proximity : 1; // 32
    BOOL m_Animates : 1; // 64
    BOOL m_Ranged : 1; // 128
    BOOL m_NoRotate : 1; // 1
    BOOL m_Inaccurate : 1; // 2
    BOOL m_Translucent : 1; // 4
    BOOL m_AntiAir : 1; // 8
    BOOL m_AntiGround : 1; // 16
    BOOL m_AntiSubWarfare : 1; // 32
    BOOL m_Degenerates : 1; // 64
    BOOL m_UnderWater : 1; // 128
    BOOL m_Parachuted : 1; // 1
    BOOL m_Gigundo : 1; // 2
#else
    bool m_High; // Can it fly over walls?
    bool m_Shadow; // If High, does this bullet need to have a shadow drawn?
    bool m_Arcing; // Does it have a ballistic trajectory?
    bool m_Dropping; // Does it fall from a starting height?
    bool m_Inviso; // Is the projectile invisible as it travels?
    bool m_Proximity; // Does it blow up when near its target?
    bool m_Animates; // Does it animate [this means smoke puffs]?
    bool m_Ranged; // Can it run out of fuel?
    bool m_NoRotate; // Does the projectile have rotation specific imagery?
    bool m_Inaccurate; // Is it inherently inaccurate?
    bool m_Translucent; // Are translucent colors used in artwork?
    bool m_AntiAir; // Can this weapon fire upon flying aircraft?
    bool m_AntiGround; // Can this weapon fire upon ground objects?
    bool m_AntiSubWarfare; // Is this an Anti-Submarine-Warfare projectile?
    bool m_Degenerates; // Does the bullet strength weaken as it travels?
    bool m_UnderWater; // Does the projectile travel under water?
    bool m_Parachuted; // Equipped with a parachute for dropping from plane (def = false)?
    bool m_Gigundo; // Is the projectile larger than normal?
#endif
    BulletType m_Type;
    uint8_t m_ROT; // Rate Of Turn [non zero implies homing].
    int m_Arm; // Arming delay.
    int m_Frames; // Number of image frames for animation purposes.
};

#ifdef GAME_DLL
extern TFixedIHeapClass<BulletTypeClass> &g_BulletTypes;
#else
extern TFixedIHeapClass<BulletTypeClass> g_BulletTypes;
#endif

#endif // BULLETTYPE_H
