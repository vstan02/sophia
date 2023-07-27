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

#ifndef SOPHIA_CORE_LIST_HPP
#define SOPHIA_CORE_LIST_HPP

#include <list>
#include <variant>

#include "core/token.hpp"

namespace sophia::core {
  enum class node_type {
    TOKEN,
    LIST
  };

  struct node {
    node_type type;
    std::variant<
      token,
      std::list<node>
    > value;
  };

  using list = std::list<node>;
}

#endif // SOPHIA_CORE_LIST_HPP
