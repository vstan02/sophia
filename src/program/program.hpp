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

#ifndef SOPHIA_PROGRAM_PROGRAM_HPP
#define SOPHIA_PROGRAM_PROGRAM_HPP

#include <variant>
#include <unordered_map>
#include <vector>
#include <functional>

#include "core/list.hpp"
#include "core/token.hpp"

#include "program/value.hpp"

namespace sophia::program {
  class program {
    private:
      struct lang_func {
        std::string id;
        std::function<value(
          program&,
          core::list::const_iterator,
          core::list::const_iterator
        )> target;
        function::size_type min_args;
        function::size_type max_args;

        lang_func(
          const std::string& id,
          const std::function<value(
            program&,
            core::list::const_iterator,
            core::list::const_iterator
          )>& target,
          function::size_type min_args,
          function::size_type max_args
        ) : id(id)
          , target(target)
          , min_args(min_args)
          , max_args(max_args) {}

        lang_func(
          const std::string& id,
          const std::function<value(
            program&,
            core::list::const_iterator,
            core::list::const_iterator
          )>& target,
          function::size_type min_args,
          bool many_args = false
        ) : id(id)
          , target(target)
          , min_args(min_args)
          , max_args(many_args ? function::args_limit : min_args) {}
      };

      struct user_func {
        const core::list args;
        const core::list body;
      };

    public:
      program(const std::vector<lang_func>& funcs);

      value exec(const core::token& token);
      value exec(const core::list& list);

      void add_function(const std::string& id, const user_func& func);

      void add_value(const std::string& id, const value& value) {
        _values[id] = value;
      }

      value node_exec(const core::node& node) {
        return node.type == core::node_type::TOKEN
          ? exec(std::get<core::token>(node.value))
          : exec(std::get<core::list>(node.value));
      }

    private:
      std::vector<user_func> _user_funcs;
      std::vector<
        std::function<value(
          program&,
          core::list::const_iterator,
          core::list::const_iterator
        )>
      > _lang_funcs;
      std::unordered_map<std::string, value> _values;

    private:
      value search_value(const std::string&);
  };
}

#endif // SOPHIA_PROGRAM_PROGRAM_HPP
