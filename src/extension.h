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

#ifndef _INCLUDE_SOURCEMOD_EXTENSION_PROPER_H_
#define _INCLUDE_SOURCEMOD_EXTENSION_PROPER_H_

#include "smsdk_ext.h"
#include "functions.h"

class Hooks;
class ConsoleManager;
class Functions;

class JabronEZ : public SDKExtension
{
public:
    virtual bool SDK_OnLoad(char *error, size_t maxlength, bool late);
    virtual void SDK_OnUnload();

    virtual bool SDK_OnMetamodLoad(ISmmAPI *ismm, char *error, size_t maxlength, bool late);

    Hooks *GetHooks() { return _hooks; }
    Functions *GetFunctions() { return _functions; }

private:
    Hooks *_hooks { nullptr };
    ConsoleManager *_consoleManager { nullptr };
    Functions *_functions { nullptr };
};

extern JabronEZ g_JabronEZ;

extern Vector lastOrigin;
extern QAngle lastAngle;
extern Vector lastVelocity;
extern Vector lastAngularImpulse;

#endif