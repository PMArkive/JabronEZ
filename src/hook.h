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

#ifndef JABRONEZ_HOOK_H
#define JABRONEZ_HOOK_H

#include "smsdk_ext.h"
class CDetour;

class Hook {
public:
    Hook(const char *functionName, void *callbackFunction, void **trampolineFunction);\
    ~Hook();

    bool Install(char *error, size_t maxlength);
    void Uninstall();
    bool IsInstalled() const;

private:
    char _functionName[256];
    void *_callbackFunction;
    void **_trampolineFunction;
    CDetour *_detour;
    bool _isInstalled;
};

#endif