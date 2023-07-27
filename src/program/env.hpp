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

#ifndef SOPHIA_PROGRAM_ENV_HPP
#define SOPHIA_PROGRAM_ENV_HPP

#include <variant>
#include <unordered_map>
#include <vector>
#include <functional>

#include "core/list.hpp"
#include "core/token.hpp"

#include "program/value.hpp"

namespace sophia::program {
  class program;

  class env {
    private:
      struct user_func {
        const core::list args;
        const core::list body;
      };

    public:
      env()
        : _functions()
        , _values() {}

      value search_value(const std::string&);

      void add_function(const std::string& id, const user_func& func);

      void add_value(const std::string& id, const value& value) {
        _values[id] = value;
      }

    private:
      std::vector<user_func> _functions;
      std::unordered_map<std::string, value> _values;
  };
}

#endif // SOPHIA_PROGRAM_ENV_HPP
