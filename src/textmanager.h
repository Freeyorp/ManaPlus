/*
 *  Support for non-overlapping floating text
 *  Copyright (C) 2008  Douglas Boffey <DougABoffey@netscape.net>
 *  Copyright (C) 2011-2012  The ManaPlus developers
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

#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H

#include <list>

class Text;

namespace gcn
{
    class Graphics;
}

class TextManager
{
    public:
        /**
         * Constructor
         */
        TextManager();

        /**
         * Add text to the manager
         */
        void addText(Text *const text);

        /**
         * Move the text around the screen
         */
        void moveText(Text *const text, const int x, const int y);

        /**
         * Remove the text from the manager
         */
        void removeText(const Text *const text);

        /**
         * Destroy the manager
         */
        ~TextManager();

        /**
         * Draw the text
         */
        void draw(gcn::Graphics *const graphics,
                  const int xOff, const int yOff);

    private:
        /**
         * Position the text so as to avoid conflict
         */
        void place(const Text *const textObj, const Text *const omit,
                   const int &x, int &y, const int h);

        typedef std::list<Text *> TextList; /**< The container type */
        TextList mTextList; /**< The container */
};

extern TextManager *textManager;

#endif // TEXTMANAGER_H
