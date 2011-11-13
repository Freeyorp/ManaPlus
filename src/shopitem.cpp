/*
 *  The ManaPlus Client
 *  Copyright (C) 2004-2009  The Mana World Development Team
 *  Copyright (C) 2009-2010  The Mana Developers
 *  Copyright (C) 2011  The ManaPlus Developers
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

#include "shopitem.h"

#include "client.h"
#include "units.h"

#include "utils/stringutils.h"

#include "resources/iteminfo.h"

#include "debug.h"

ShopItem::ShopItem(int inventoryIndex, int id, unsigned char color,
                   int quantity, int price) :
    Item(id, 0, 0, color),
    mPrice(price),
    mShowQuantity(true)
{
    if (serverVersion > 0)
    {
        mDisplayName = getInfo().getName(color) + " ("
            + Units::formatCurrency(mPrice).c_str() + ") ";
    }
    else
    {
        mDisplayName = getInfo().getName() + " ("
            + Units::formatCurrency(mPrice).c_str() + ") ";
    }
    if (quantity > 0)
        mDisplayName += "[" + toString(quantity) + "]";

    setInvIndex(inventoryIndex);
    addDuplicate(inventoryIndex, quantity);
}

ShopItem::ShopItem (int id, unsigned char color, int price) :
    Item (id, 0, 0, color),
    mPrice(price),
    mShowQuantity(false)
{
    if (serverVersion > 0)
    {
        mDisplayName = getInfo().getName(color) +
            " (" + Units::formatCurrency(mPrice).c_str() + ")";
    }
    else
    {
        mDisplayName = getInfo().getName() +
            " (" + Units::formatCurrency(mPrice).c_str() + ")";
    }
    setInvIndex(-1);
    addDuplicate(-1, 0);
}

ShopItem::~ShopItem()
{
    /** Clear all remaining duplicates on Object destruction. */
    while (!mDuplicates.empty())
    {
        delete mDuplicates.top();
        mDuplicates.pop();
    }
}

void ShopItem::update()
{
    if (mShowQuantity)
    {
        if (serverVersion > 0)
        {
            mDisplayName = getInfo().getName(mColor) + " ("
                + Units::formatCurrency(mPrice).c_str() + ") ";
        }
        else
        {
            mDisplayName = getInfo().getName() + " ("
                + Units::formatCurrency(mPrice).c_str() + ") ";
        }
        if (mQuantity > 0)
            mDisplayName += "[" + toString(mQuantity) + "]";
    }
}

void ShopItem::addDuplicate(int inventoryIndex, int quantity)
{
    DuplicateItem* di = new DuplicateItem;
    di->inventoryIndex = inventoryIndex;
    di->quantity = quantity;
    mDuplicates.push(di);
    mQuantity += quantity;
}

void ShopItem::addDuplicate()
{
    DuplicateItem* di = new DuplicateItem;
    di->inventoryIndex = -1;
    di->quantity = 0;
    mDuplicates.push(di);
}

int ShopItem::sellCurrentDuplicate(int quantity)
{
    DuplicateItem* dupl = mDuplicates.top();
    if (!dupl)
        return 0;

    int sellCount = quantity <= dupl->quantity ? quantity : dupl->quantity;
    dupl->quantity -= sellCount;
    mQuantity -= sellCount;
    if (dupl->quantity == 0)
    {
        delete dupl;
        dupl = nullptr;
        mDuplicates.pop();
    }
    return sellCount;
}
