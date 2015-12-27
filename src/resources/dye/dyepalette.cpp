/*
 *  The ManaPlus Client
 *  Copyright (C) 2007-2009  The Mana World Development Team
 *  Copyright (C) 2009-2010  The Mana Developers
 *  Copyright (C) 2011-2015  The ManaPlus Developers
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

#include "resources/dye/dyepalette.h"

#include "logger.h"

#ifndef DYECMD
#include "resources/db/palettedb.h"
#endif

#include <cmath>

#include <SDL_endian.h>

#include "debug.h"

DyePalette::DyePalette(const std::string &restrict description,
                       const uint8_t blockSize) :
    mColors()
{
    const size_t size = static_cast<size_t>(description.length());
    if (size == 0)
        return;

    if (description[0] == '#')
    {
        size_t pos = 1;
        for ( ; ; )
        {
            if (pos + blockSize > size)
                break;

            DyeColor color(0, 0, 0, 0);

            for (size_t i = 0, colorIdx = 0; i < blockSize && colorIdx < 4;
                 i += 2, colorIdx ++)
            {
                color.value[colorIdx] = static_cast<unsigned char>((
                    hexDecode(description[pos + i]) << 4)
                    + hexDecode(description[pos + i + 1]));
            }
            mColors.push_back(color);
            pos += blockSize;

            if (pos == size)
                return;
            if (description[pos] != ',')
                break;

            ++pos;
        }
    }
#ifndef DYECMD
    else if (description[0] == '@')
    {
        size_t pos = 1;
        for ( ; pos < size ; )
        {
            const size_t idx = description.find(',', pos);
            if (idx == std::string::npos)
                return;
            if (idx == pos)
                break;
            mColors.push_back(PaletteDB::getColor(
                description.substr(pos, idx - pos)));
            pos = idx + 1;
        }
    }
#endif
    logger->log("Error, invalid embedded palette: %s", description.c_str());
}

unsigned int DyePalette::hexDecode(const signed char c)
{
    if ('0' <= c && c <= '9')
        return c - '0';
    else if ('A' <= c && c <= 'F')
        return c - 'A' + 10;
    else if ('a' <= c && c <= 'f')
        return c - 'a' + 10;
    else
        return 0;
}

void DyePalette::getColor(const unsigned int intensity,
                          unsigned int (&restrict color)[3]) const restrict2
{
    if (intensity == 0)
    {
        color[0] = 0;
        color[1] = 0;
        color[2] = 0;
        return;
    }

    const int last = static_cast<int>(mColors.size());
    if (last == 0)
        return;

    const int intLast = intensity * last;
    const int i = intLast / 255;
    const int t = intLast % 255;

    int j = t != 0 ? i : i - 1;

    if (j >= last)
        j = 0;

    // Get the exact color if any, the next color otherwise.
    const DyeColor &colorJ = mColors[j];
    const int r2 = colorJ.value[0];
    const int g2 = colorJ.value[1];
    const int b2 = colorJ.value[2];

    if (t == 0)
    {
        // Exact color.
        color[0] = r2;
        color[1] = g2;
        color[2] = b2;
        return;
    }

    // Get the previous color. First color is implicitly black.
    if (i > 0 && i < last + 1)
    {
        const DyeColor &colorI = mColors[i - 1];
        const int t2 = 255 - t;
        // Perform a linear interpolation.
        color[0] = (t2 * colorI.value[0] + t * r2) / 255;
        color[1] = (t2 * colorI.value[1] + t * g2) / 255;
        color[2] = (t2 * colorI.value[2] + t * b2) / 255;
    }
    else
    {
        // Perform a linear interpolation.
        color[0] = (t * r2) / 255;
        color[1] = (t * g2) / 255;
        color[2] = (t * b2) / 255;
    }
}

void DyePalette::getColor(double intensity,
                          int (&restrict color)[3]) const restrict2
{
    // Nothing to do here
    if (mColors.empty())
        return;

    // Force range
    if (intensity > 1.0)
        intensity = 1.0;
    else if (intensity < 0.0)
        intensity = 0.0;

    // Scale up
    intensity *= static_cast<double>(mColors.size() - 1);

    // Color indices
    const int i = static_cast<int>(floor(intensity));
    const int j = static_cast<int>(ceil(intensity));
    const DyeColor &colorI = mColors[i];

    if (i == j)
    {
        // Exact color.
        color[0] = colorI.value[0];
        color[1] = colorI.value[1];
        color[2] = colorI.value[2];
        return;
    }

    intensity -= i;
    const double rest = 1 - intensity;
    const DyeColor &colorJ = mColors[j];

    // Perform the interpolation.
    color[0] = static_cast<int>(rest * colorI.value[0] +
        intensity * colorJ.value[0]);
    color[1] = static_cast<int>(rest * colorI.value[1] +
        intensity * colorJ.value[1]);
    color[2] = static_cast<int>(rest * colorI.value[2] +
        intensity * colorJ.value[2]);
}

void DyePalette::replaceSColor(uint32_t *restrict pixels,
                               const int bufSize) const restrict2
{
    std::vector<DyeColor>::const_iterator it_end = mColors.end();
    const size_t sz = mColors.size();
    if (!sz || !pixels)
        return;
    if (sz % 2)
        -- it_end;

#ifdef ENABLE_CILKPLUS
    cilk_for (int ptr = 0; ptr < bufSize; ptr ++)
    {
        uint8_t *const p = reinterpret_cast<uint8_t *>(&pixels[ptr]);
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
        const int alpha = pixels[ptr] & 0xff000000;
        const unsigned int data = pixels[ptr] & 0x00ffffff;
#else
        const int alpha = *p & 0xff;
        const unsigned int data = pixels[ptr] & 0xffffff00;
#endif
//        logger->log("c:%04d   %08x", c, *pixels);
//        logger->log("data:    %08x", data);
        if (!alpha)
        {
//            logger->log("skip:    %08x", *pixels);
        }
        else
        {
            std::vector<DyeColor>::const_iterator it = mColors.begin();
            while (it != it_end)
            {
                const DyeColor &col = *it;
                ++ it;
                const DyeColor &col2 = *it;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
                const unsigned int coldata = (col.value[2] << 16U)
                    | (col.value[1] << 8U) | (col.value[0]);
#else
                const unsigned int coldata = (col.value[2] << 8U)
                    | (col.value[1] << 16U) | (col.value[0] << 24U);
#endif
//            logger->log("coldata: %08x", coldata);
                if (data == coldata)
                {
//                logger->log("correct");
                    p[3] = col2.value[0];
                    p[2] = col2.value[1];
                    p[1] = col2.value[2];
                    break;
                }
                ++ it;
            }
        }
    }
#else  // ENABLE_CILKPLUS

    for (uint32_t *p_end = pixels + static_cast<size_t>(bufSize);
         pixels != p_end;
         ++ pixels)
    {
        uint8_t *const p = reinterpret_cast<uint8_t *>(pixels);
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
        const int alpha = *pixels & 0xff000000;
        const unsigned int data = (*pixels) & 0x00ffffff;
#else
        const int alpha = *p & 0xff;
        const unsigned int data = (*pixels) & 0xffffff00;
#endif
//        logger->log("c:%04d   %08x", c, *pixels);
//        logger->log("data:    %08x", data);
        if (!alpha)
        {
//            logger->log("skip:    %08x", *pixels);
            continue;
        }

        std::vector<DyeColor>::const_iterator it = mColors.begin();
        while (it != it_end)
        {
            const DyeColor &col = *it;
            ++ it;
            const DyeColor &col2 = *it;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
            const unsigned int coldata = (col.value[2] << 16U)
                | (col.value[1] << 8U) | (col.value[0]);
#else
            const unsigned int coldata = (col.value[2] << 8U)
                | (col.value[1] << 16U) | (col.value[0] << 24U);
#endif
//            logger->log("coldata: %08x", coldata);
            if (data == coldata)
            {
//                logger->log("correct");
                p[3] = col2.value[0];
                p[2] = col2.value[1];
                p[1] = col2.value[2];
                break;
            }

            ++ it;
        }
    }
#endif  // ENABLE_CILKPLUS
}

void DyePalette::replaceAColor(uint32_t *restrict pixels,
                               const int bufSize) const restrict2
{
    std::vector<DyeColor>::const_iterator it_end = mColors.end();
    const size_t sz = mColors.size();
    if (!sz || !pixels)
        return;
    if (sz % 2)
        -- it_end;

#ifdef ENABLE_CILKPLUS
    cilk_for (int ptr = 0; ptr < bufSize; ptr ++)
    {
        uint8_t *const p = reinterpret_cast<uint8_t *>(&pixels[ptr]);
        const unsigned int data = pixels[ptr];

        std::vector<DyeColor>::const_iterator it = mColors.begin();
        while (it != it_end)
        {
            const DyeColor &col = *it;
            ++ it;
            const DyeColor &col2 = *it;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
            const unsigned int coldata = (col.value[3] << 24U)
                | (col.value[2] << 16U)
                | (col.value[1] << 8U)
                | (col.value[0]);
#else
            const unsigned int coldata = (col.value[3])
                | (col.value[2] << 8U)
                | (col.value[1] << 16U) |
                (col.value[0] << 24U);
#endif

            if (data == coldata)
            {
                p[3] = col2.value[0];
                p[2] = col2.value[1];
                p[1] = col2.value[2];
                p[0] = col2.value[3];
                break;
            }

            ++ it;
        }
    }

#else  // ENABLE_CILKPLUS

    for (uint32_t *p_end = pixels + static_cast<size_t>(bufSize);
         pixels != p_end;
         ++pixels)
    {
        uint8_t *const p = reinterpret_cast<uint8_t *>(pixels);
        const unsigned int data = *pixels;

        std::vector<DyeColor>::const_iterator it = mColors.begin();
        while (it != it_end)
        {
            const DyeColor &col = *it;
            ++ it;
            const DyeColor &col2 = *it;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
            const unsigned int coldata = (col.value[3] << 24U)
                | (col.value[2] << 16U)
                | (col.value[1] << 8U)
                | (col.value[0]);
#else
            const unsigned int coldata = (col.value[3])
                | (col.value[2] << 8U)
                | (col.value[1] << 16U) |
                (col.value[0] << 24U);
#endif

            if (data == coldata)
            {
                p[3] = col2.value[0];
                p[2] = col2.value[1];
                p[1] = col2.value[2];
                p[0] = col2.value[3];
                break;
            }

            ++ it;
        }
    }
#endif  // ENABLE_CILKPLUS
}

void DyePalette::replaceSOGLColor(uint32_t *restrict pixels,
                                  const int bufSize) const restrict2
{
    std::vector<DyeColor>::const_iterator it_end = mColors.end();
    const size_t sz = mColors.size();
    if (!sz || !pixels)
        return;
    if (sz % 2)
        -- it_end;

#ifdef ENABLE_CILKPLUS
    cilk_for (int ptr = 0; ptr < bufSize; ptr ++)
    {
        uint8_t *const p = reinterpret_cast<uint8_t *>(&pixels[ptr]);
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
        const int alpha = *p & 0xff;
        const unsigned int data = (pixels[ptr]) & 0xffffff00;
#else
        const int alpha = pixels[ptr] & 0xff000000;
        const unsigned int data = (pixels[ptr]) & 0x00ffffff;
#endif
        if (alpha)
        {
            std::vector<DyeColor>::const_iterator it = mColors.begin();
            while (it != it_end)
            {
                const DyeColor &col = *it;
                ++ it;
                const DyeColor &col2 = *it;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
                const unsigned int coldata = (col.value[0] << 24)
                    | (col.value[1] << 16) | (col.value[2] << 8);
#else
                const unsigned int coldata = (col.value[0])
                    | (col.value[1] << 8) | (col.value[2] << 16);
#endif
                if (data == coldata)
                {
                    p[0] = col2.value[0];
                    p[1] = col2.value[1];
                    p[2] = col2.value[2];
                    break;
                }

                ++ it;
            }
        }
    }

#else  // ENABLE_CILKPLUS

    for (uint32_t *p_end = pixels + static_cast<size_t>(bufSize);
         pixels != p_end;
         ++pixels)
    {
        uint8_t *const p = reinterpret_cast<uint8_t *>(pixels);
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
        const int alpha = *p & 0xff;
        const unsigned int data = (*pixels) & 0xffffff00;
#else
        const int alpha = *pixels & 0xff000000;
        const unsigned int data = (*pixels) & 0x00ffffff;
#endif
        if (!alpha)
            continue;

        std::vector<DyeColor>::const_iterator it = mColors.begin();
        while (it != it_end)
        {
            const DyeColor &col = *it;
            ++ it;
            const DyeColor &col2 = *it;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
            const unsigned int coldata = (col.value[0] << 24)
                | (col.value[1] << 16) | (col.value[2] << 8);
#else
            const unsigned int coldata = (col.value[0])
                | (col.value[1] << 8) | (col.value[2] << 16);
#endif
            if (data == coldata)
            {
                p[0] = col2.value[0];
                p[1] = col2.value[1];
                p[2] = col2.value[2];
                break;
            }

            ++ it;
        }
    }
#endif  // ENABLE_CILKPLUS
}

void DyePalette::replaceAOGLColor(uint32_t *restrict pixels,
                                  const int bufSize) const restrict2
{
    std::vector<DyeColor>::const_iterator it_end = mColors.end();
    const size_t sz = mColors.size();
    if (!sz || !pixels)
        return;
    if (sz % 2)
        -- it_end;

#ifdef ENABLE_CILKPLUS
    cilk_for (int ptr = 0; ptr < bufSize; ptr ++)
    {
        uint8_t *const p = reinterpret_cast<uint8_t *>(&pixels[ptr]);
        const unsigned int data = pixels[ptr];

        std::vector<DyeColor>::const_iterator it = mColors.begin();
        while (it != it_end)
        {
            const DyeColor &col = *it;
            ++ it;
            const DyeColor &col2 = *it;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
            const unsigned int coldata = (col.value[0] << 24U)
                | (col.value[1] << 16U)
                | (col.value[2] << 8U)
                | col.value[3];
#else
            const unsigned int coldata = (col.value[0])
                | (col.value[1] << 8U)
                | (col.value[2] << 16U)
                | (col.value[3] << 24U);
#endif
            if (data == coldata)
            {
                p[0] = col2.value[0];
                p[1] = col2.value[1];
                p[2] = col2.value[2];
                p[3] = col2.value[3];
                break;
            }

            ++ it;
        }
    }

#else  // ENABLE_CILKPLUS

    for (uint32_t *p_end = pixels + static_cast<size_t>(bufSize);
         pixels != p_end;
         ++pixels)
    {
        uint8_t *const p = reinterpret_cast<uint8_t *>(pixels);
        const unsigned int data = *pixels;

        std::vector<DyeColor>::const_iterator it = mColors.begin();
        while (it != it_end)
        {
            const DyeColor &col = *it;
            ++ it;
            const DyeColor &col2 = *it;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
            const unsigned int coldata = (col.value[0] << 24U)
                | (col.value[1] << 16U)
                | (col.value[2] << 8U)
                | col.value[3];
#else
            const unsigned int coldata = (col.value[0])
                | (col.value[1] << 8U)
                | (col.value[2] << 16U)
                | (col.value[3] << 24U);
#endif
            if (data == coldata)
            {
                p[0] = col2.value[0];
                p[1] = col2.value[1];
                p[2] = col2.value[2];
                p[3] = col2.value[3];
                break;
            }

            ++ it;
        }
    }
#endif  // ENABLE_CILKPLUS
}
