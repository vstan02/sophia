/* Copyright (C) 2023 Stan Vlad <vstan02@protonmail.com>
 *
 * This file is part of Sophia.
 *
 * Sophia is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef SOPHIA_LIBCORE_HPP
#define SOPHIA_LIBCORE_HPP

#include "core/list.hpp"

#include "program/program.hpp"
#include "program/value.hpp"

namespace sophia {
  extern program::value std_def(
    program::program&,
    core::list::const_iterator,
    core::list::const_iterator
  );

  extern program::value std_defn(
    program::program&,
    core::list::const_iterator,
    core::list::const_iterator
  );

  extern program::value std_add(
    program::program&,
    core::list::const_iterator,
    core::list::const_iterator
  );

  extern program::value std_sub(
    program::program&,
    core::list::const_iterator,
    core::list::const_iterator
  );

  extern program::value std_mul(
    program::program&,
    core::list::const_iterator,
    core::list::const_iterator
  );

  extern program::value std_div(
    program::program&,
    core::list::const_iterator,
    core::list::const_iterator
  );

  extern program::value std_int(
    program::program&,
    core::list::const_iterator,
    core::list::const_iterator
  );

  extern program::value std_if(
    program::program&,
    core::list::const_iterator,
    core::list::const_iterator
  );

  extern program::value std_print(
    program::program&,
    core::list::const_iterator,
    core::list::const_iterator
  );

  extern program::value std_println(
    program::program&,
    core::list::const_iterator,
    core::list::const_iterator
  );
}

#endif // SOPHIA_LIBCORE_HPP
