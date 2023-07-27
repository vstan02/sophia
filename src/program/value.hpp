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

#ifndef SOPHIA_PROGRAM_VALUE_HPP
#define SOPHIA_PROGRAM_VALUE_HPP

#include <cstddef>
#include <variant>
#include <string>
#include <utility>

namespace sophia::program {
  enum class value_type {
    NIL,
    BOOL,
    NUMBER,
    STRING,
    FUNCTION
  };

  enum func_type {
    LANG,
    USER
  };

  struct function {
    using size_type = std::size_t;

    static const size_type args_limit = 1'000;

    func_type type;
    size_type index;
    size_type min_args;
    size_type max_args;

    function(
      func_type type,
      size_type index,
      size_type min_args,
      size_type max_args
    ) : type(type)
      , index(index)
      , min_args(min_args)
      , max_args(max_args) {}

    function(
      func_type type,
      size_type index,
      size_type args,
      bool many_args = false
    ) : type(type)
      , index(index)
      , min_args(args)
      , max_args(many_args ? args_limit : min_args) {}
  };

  struct value {
    value_type type;
    std::variant<
      bool,
      double,
      std::string,
      function
    > target;

    value(value_type type = value_type::NIL)
      : type(type)
      , target() {}

    value(bool target)
      : type(value_type::BOOL)
      , target(target) {}

    value(double target)
      : type(value_type::NUMBER)
      , target(target) {}

    value(const std::string& target)
      : type(value_type::STRING)
      , target(target) {}

    value(std::string&& target)
      : type(value_type::STRING)
      , target(std::move(target)) {}

    value(function target)
      : type(value_type::FUNCTION)
      , target(target) {}
  };
}

#endif // SOPHIA_PROGRAM_VALUE_HPP
