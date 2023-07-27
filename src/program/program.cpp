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

#include <cstddef>
#include <cstdlib>
#include <functional>
#include <stdexcept>
#include <vector>

#include "core/list.hpp"
#include "core/token.hpp"

#include "program/value.hpp"
#include "program/program.hpp"

namespace sophia::program {
  extern program::program(const std::vector<lang_func>& funcs)
    : _user_funcs()
    , _lang_funcs()
    , _values() {
    for (const auto& el: funcs) {
      _values[el.id] = {
        function(func_type::LANG, _lang_funcs.size(), el.min_args, el.max_args)
      };
      _lang_funcs.push_back(el.target);
    }
  }

  extern void program::add_function(const std::string& id, const user_func& func) {
    _values[id] = {
      function(func_type::USER, _user_funcs.size(), func.args.size())
    };
    _user_funcs.push_back(func);
  }

  extern value program::exec(const core::list& list) {
    if (list.empty()) {
      return value();
    }

    auto begin = list.cbegin();
    auto end = list.cend();

    value result = node_exec(*begin);
    if (result.type == value_type::FUNCTION) {
      auto func = std::get<function>(result.target);
      if (func.min_args >= list.size() || func.max_args + 1 < list.size()) {
        throw std::runtime_error("Invalid number of arguments.");
      }

      if (func.type == func_type::LANG) {
        return _lang_funcs[func.index](*this, std::next(begin), end);
      }

      return exec(_user_funcs[func.index].body);
    }

    if (list.size() == 1) {
      return result;
    }

    for (auto it = std::next(begin); it != std::prev(end); ++it) {
      node_exec(*it);
    }
    return node_exec(*std::prev(end));
  }

  extern value program::exec(const core::token& token) {
    switch (token.type) {
      case core::token_type::TRUE:
        return value(true);
      case core::token_type::FALSE:
        return value(false);
      case core::token_type::STRING:
        return value(token.value);
      case core::token_type::NUMBER:
        return value(std::strtod(token.value.data(), nullptr));
      case core::token_type::ID:
        return search_value(token.value);
      default:
        return value();
    }
  }

  extern value program::search_value(const std::string& id) {
    auto it = _values.find(id);
    if (it != _values.end()) {
      return it->second;
    }
    throw std::runtime_error("Value not found.");
  }
}
