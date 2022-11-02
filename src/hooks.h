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

#ifndef JABRONEZ_HOOKS_H
#define JABRONEZ_HOOKS_H

#include "smsdk_ext.h"
#include <sh_vector.h>
#include "type_definitions.h"

class Hook;

class Hooks {
public:
    Hooks(ISourcePawnEngine *sourcePawnEngine, IGameConfig *gameConfig);
    ~Hooks();

    bool Init(char *error, size_t maxlength);

    bool InstallHooks(char *error, size_t maxlength);
    void UninstallHooks();

    void NewHook(const char *functionName, void *callbackFunction, void **trampolineFunction);

    static CBaseEntity* ProjectileCreateCallingConvention CSmokeGrenadeProjectileCreateHookCallback(
            const Vector& origin,
            const QAngle& angle,
            const Vector& velocity,
            const Vector& angularImpulse,
            void *player,
            int grenadeType);

    void NotifyCreatingSmokeGrenadeProjectile(bool isCreatingFromExtension) { _isCreatingSmokeGrenadeProjectileFromExtension = isCreatingFromExtension; }

private:
    SourceHook::CVector<Hook*> _hooks;
    bool _isCreatingSmokeGrenadeProjectileFromExtension { false };
    ProjectileCreatePrototype _originalCSmokeGrenadeProjectileCreate { nullptr };
};

#endif
