/*!
 * \file            tpgentypes.h
 * \brief           Interface to terminal program general types.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_CURSES_GENTYPES_H
#define PG_CURSES_GENTYPES_H

namespace pgcurses {

/*!
 * \brief           Point structure.
 * \ingroup         pgcurses
 */
struct Point {

    /*!  X coordinate  */
    int x;

    /*!  Y coordinate  */
    int y;

    /*!
     * \brief           Constructor.
     */
    Point() : x{0}, y{0} {}

    /*!
     * \brief           Constructor.
     * \param x         The X coordinate.
     * \param y         The Y coordinate.
     */
    Point(const int x, const int y) : x{x}, y{y} {}
};

/*!
 * \brief               Size structure.
 * \ingroup             pgcurses
 */
struct Size {

    /*!  The width  */
    int width;

    /*!  The height  */
    int height;

    /*!
     * \brief           Constructor.
     */
    Size() : width{0}, height{0} {}

    /*!
     * \brief           Constructor.
     * \param width     The width.
     * \param height    The height.
     */
    Size(const int width, const int height) : width{width}, height{height} {}
};

/*!
 * \brief               Rectangle structure.
 * \ingroup             pgcurses
 */
struct Rectangle {

    /*!  The size  */
    Size size;

    /*!  The origin  */
    Point origin;

    /*!
     * \brief           Constructor.
     */
    Rectangle() : size{Size{0, 0}}, origin{Point{0, 0}} {}

    /*!
     * \brief           Constructor.
     * \param sz        The size.
     */
    Rectangle(const Size sz) :
        size{sz}, origin{Point{0, 0}} {}

    /*!
     * \brief           Constructor.
     * \param sz        The size.
     * \param origin    The origin.
     */
    Rectangle(const Size sz, const Point origin) :
        size{sz}, origin{origin} {}
};

}               //  namespace pgcurses

#endif          //  PG_CURSES_GENTYPES_H

