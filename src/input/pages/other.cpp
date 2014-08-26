/*
 *  The ManaPlus Client
 *  Copyright (C) 2007  Joshua Langley <joshlangley@optusnet.com.au>
 *  Copyright (C) 2009  The Mana World Development Team
 *  Copyright (C) 2009-2010  The Mana Developers
 *  Copyright (C) 2011-2014  The ManaPlus Developers
 *
 *  This file is part of The ManaPlus Client.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "gui/setupactiondata.h"

#include "input/inputaction.h"
#include "input/inputactiondata.h"

#include "utils/gettext.h"
#include "utils/stringutils.h"

#include "debug.h"

SetupActionData setupActionDataOther[] =
{
    {
        // TRANSLATORS: input action name
        N_("Ignore input 1"),
        InputAction::IGNORE_INPUT_1,
        "",
    },
    {
        // TRANSLATORS: input action name
        N_("Ignore input 2"),
        InputAction::IGNORE_INPUT_2,
        "",
    },
    {
        // TRANSLATORS: input action name
        N_("Direct Up"),
        InputAction::DIRECT_UP,
        "",
    },
    {
        // TRANSLATORS: input action name
        N_("Direct Down"),
        InputAction::DIRECT_DOWN,
        "",
    },
    {
        // TRANSLATORS: input action name
        N_("Direct Left"),
        InputAction::DIRECT_LEFT,
        "",
    },
    {
        // TRANSLATORS: input action name
        N_("Direct Right"),
        InputAction::DIRECT_RIGHT,
        "",
    },
    {
        // TRANSLATORS: input action name
        N_("Crazy moves"),
        InputAction::CRAZY_MOVES,
        "",
    },
    {
        // TRANSLATORS: input action name
        N_("Change Crazy Move mode"),
        InputAction::CHANGE_CRAZY_MOVES_TYPE,
        "",
    },
    {
        // TRANSLATORS: input action name
        N_("Quick Drop N Items from 0 slot"),
        InputAction::QUICK_DROP,
        "",
    },
    {
        // TRANSLATORS: input action name
        N_("Quick Drop N Items"),
        InputAction::QUICK_DROPN,
        "",
    },
    {
        // TRANSLATORS: input action name
        N_("Switch Quick Drop Counter"),
        InputAction::SWITCH_QUICK_DROP,
        "",
    },
    {
        // TRANSLATORS: input action name
        N_("Quick heal target or self"),
        InputAction::MAGIC_INMA1,
        "",
    },
    {
        // TRANSLATORS: input action name
        N_("Use #itenplz spell"),
        InputAction::MAGIC_ITENPLZ,
        "",
    },
    {
        // TRANSLATORS: input action name
        N_("Use magic attack"),
        InputAction::MAGIC_ATTACK,
        "",
    },
    {
        // TRANSLATORS: input action name
        N_("Switch magic attack"),
        InputAction::SWITCH_MAGIC_ATTACK,
        "",
    },
    {
        // TRANSLATORS: input action name
        N_("Switch pvp attack"),
        InputAction::SWITCH_PVP_ATTACK,
        "",
    },
    {
        // TRANSLATORS: input action name
        N_("Change move type"),
        InputAction::INVERT_DIRECTION,
        "",
    },
    {
        // TRANSLATORS: input action name
        N_("Change Attack Weapon Type"),
        InputAction::CHANGE_ATTACK_WEAPON_TYPE,
        "",
    },
    {
        // TRANSLATORS: input action name
        N_("Change Attack Type"),
        InputAction::CHANGE_ATTACK_TYPE,
        "",
    },
    {
        // TRANSLATORS: input action name
        N_("Change Follow mode"),
        InputAction::CHANGE_FOLLOW_MODE,
        "",
    },
    {
        // TRANSLATORS: input action name
        N_("Change Imitation mode"),
        InputAction::CHANGE_IMITATION_MODE,
        "",
    },
    {
        // TRANSLATORS: input action name
        N_("Disable / Enable Game modifier keys"),
        InputAction::DISABLE_GAME_MODIFIERS,
        "",
    },
    {
        // TRANSLATORS: input action name
        N_("On / Off audio"),
        InputAction::CHANGE_AUDIO,
        "",
    },
    {
        // TRANSLATORS: input action name
        N_("Enable / Disable away mode"),
        InputAction::AWAY,
        "",
    },
    {
        // TRANSLATORS: input action name
        N_("Emulate right click from keyboard"),
        InputAction::RIGHT_CLICK,
        "",
    },
    {
        // TRANSLATORS: input action name
        N_("Toggle camera mode"),
        InputAction::CAMERA,
        "",
    },
    {
        // TRANSLATORS: input action name
        N_("Toggle ipc mode"),
        InputAction::IPC_TOGGLE,
        "",
    },
    {
        // TRANSLATORS: input action name
        N_("Show information about position in chat"),
        InputAction::WHERE,
        "",
    },
    {
        // TRANSLATORS: input action name
        N_("Show online players number in chat"),
        InputAction::WHO,
        "",
    },
    {
        // TRANSLATORS: input action name
        N_("Show onscreen keyboard"),
        InputAction::SHOW_KEYBOARD,
        "",
    },
    {
        // TRANSLATORS: input action name
        N_("Clean cached graphics"),
        InputAction::CLEAN_GRAPHICS,
        "",
    },
    {
        // TRANSLATORS: input action name
        N_("Clean cached fonts"),
        InputAction::CLEAN_FONTS,
        "",
    },
    {
        // TRANSLATORS: input action name
        N_("Print visible players in chat"),
        InputAction::PRESENT,
        "",
    },
    {
        // TRANSLATORS: input action name
        N_("Print all visible beings in chat"),
        InputAction::PRINT_ALL,
        "",
    },
    {
        // TRANSLATORS: input action name
        N_("Load shop items list from disk"),
        InputAction::PRICE_LOAD,
        "",
    },
    {
        // TRANSLATORS: input action name
        N_("Save shop items list to disk"),
        InputAction::PRICE_SAVE,
        "",
    },
    {
        "",
        InputAction::NO_VALUE,
        ""
    }
};
