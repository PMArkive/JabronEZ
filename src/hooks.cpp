/**
 * =============================================================================
 * Copyright (C) 2022 JabronEZ Team.  All rights reserved.
 * =============================================================================
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "hooks.h"
#include "hook.h"
#include <CDetour/detours.h>
#include "extension.h"

Hooks::Hooks(ISourcePawnEngine *sourcePawnEngine, IGameConfig *gameConfig)
{
    _hooks.clear();

    CDetourManager::Init(sourcePawnEngine, gameConfig);
}

Hooks::~Hooks()
{
    size_t hookCount = _hooks.size();
    for (size_t hookIndex = 0; hookIndex < hookCount; hookIndex++)
    {
        Hook *hook = _hooks.at(hookIndex);
        delete hook;
    }

    _hooks.clear();
}

bool Hooks::Init(char *error, size_t maxlength)
{
    NewHook(
            "CSmokeGrenadeProjectileCreate",
            (void*)&Hooks::CSmokeGrenadeProjectileCreateHookCallback,
            (void**)&_originalCSmokeGrenadeProjectileCreate);

    if (!InstallHooks(error, maxlength))
    {
        return false;
    }

    return true;
}

bool Hooks::InstallHooks(char *error, size_t maxlength)
{
    size_t hookCount = _hooks.size();
    for (size_t hookIndex = 0; hookIndex < hookCount; hookIndex++)
    {
        Hook *hook = _hooks.at(hookIndex);
        if (!hook->Install(error, maxlength))
        {
            return false;
        }
    }

    return true;
}

void Hooks::UninstallHooks()
{
    size_t hookCount = _hooks.size();
    for (size_t hookIndex = 0; hookIndex < hookCount; hookIndex++)
    {
        Hook *hook = _hooks.at(hookIndex);
        hook->Uninstall();
    }
}

void Hooks::NewHook(
    const char *functionName,
    void *callbackFunction,
    void **trampolineFunction)
{
    Hook *hook = new Hook(functionName, callbackFunction, trampolineFunction);
    _hooks.push_back(hook);
}

CBaseEntity* __cdecl Hooks::CSmokeGrenadeProjectileCreateHookCallback(
        const Vector& origin,
        const QAngle& angle,
        const Vector& velocity,
        const Vector& angularImpulse,
        void *player,
        int grenadeType)
{
    if (g_JabronEZ.GetHooks()->_isCreatingSmokeGrenadeProjectileFromExtension)
    {
        return g_JabronEZ.GetHooks()->_originalCSmokeGrenadeProjectileCreate(
                origin,
                angle,
                velocity,
                angularImpulse,
                player,
                grenadeType);
    }

    lastOrigin = origin;
    lastAngle = angle;
    lastVelocity = velocity;
    lastAngularImpulse = angularImpulse;

    META_CONPRINTF(
            "Smoke thrown: [%f %f %f] [%f %f %f] [%f %f %f] [%f %f %f] %p %d\n",
            origin.x,
            origin.y,
            origin.z,
            angle.x,
            angle.y,
            angle.z,
            velocity.x,
            velocity.y,
            velocity.z,
            angularImpulse.x,
            angularImpulse.y,
            angularImpulse.z,
            player,
            grenadeType);

    return g_JabronEZ.GetHooks()->_originalCSmokeGrenadeProjectileCreate(
            origin,
            angle,
            velocity,
            angularImpulse,
            player,
            grenadeType);
}
