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

#include <iostream>
#include <stdexcept>
#include <string>
#include <iterator>
#include <variant>

#include "core/list.hpp"
#include "core/token.hpp"

#include "program/value.hpp"

#include "libcore.hpp"

namespace sophia {
  extern program::value std_def(
    program::program& program,
    core::list::const_iterator begin,
    [[maybe_unused]] core::list::const_iterator end
  ) {
    if (begin->type != core::node_type::TOKEN) {
      throw std::runtime_error("Invalid value ID.");
    }

    program::value result = program.node_exec(*std::next(begin));
    program.add_value(std::get<core::token>(begin->value).value, result);
    return result;
  }

  extern program::value std_defn(
    program::program& program,
    core::list::const_iterator begin,
    [[maybe_unused]] core::list::const_iterator end
  ) {
    if (begin->type != core::node_type::TOKEN) {
      throw std::runtime_error("Invalid function ID.");
    }

    if ((++begin)->type != core::node_type::LIST) {
      throw std::runtime_error("A list of parameters was expected.");
    }

    program.add_function(
      std::get<core::token>(std::prev(begin)->value).value,
      {
        std::get<core::list>(begin->value),
        core::list(std::next(begin), end)
      }
    );
    return program::value();
  }

  extern program::value std_add(
    program::program& program,
    core::list::const_iterator begin,
    core::list::const_iterator end
  ) {
    program::value result = program.node_exec(*begin);
    if (
      result.type != program::value_type::NUMBER &&
      result.type != program::value_type::STRING
    ) {
      throw std::runtime_error("Invalid argument types.");
    }

    for (++begin; begin != end; ++begin) {
      program::value current = program.node_exec(*begin);
      if (result.type != current.type) {
        throw std::runtime_error("Invalid argument types.");
      }
      switch (result.type) {
        case program::value_type::NUMBER:
          result = program::value(
            std::get<double>(result.target) +
            std::get<double>(current.target)
          );
          break;
        case program::value_type::STRING:
          result = program::value(
            std::get<std::string>(result.target) +
            std::get<std::string>(current.target)
          );
          break;
        default:
          throw std::runtime_error("Invalid argument types.");
      }
    }

    return result;
  }

  extern program::value std_sub(
    program::program& program,
    core::list::const_iterator begin,
    core::list::const_iterator end
  ) {
    program::value result = program.node_exec(*begin);
    if (result.type != program::value_type::NUMBER) {
      throw std::runtime_error("Invalid argument types.");
    }

    for (++begin; begin != end; ++begin) {
      program::value current = program.node_exec(*begin);
      if (result.type != current.type) {
        throw std::runtime_error("Invalid argument types.");
      }
      result = program::value(
        std::get<double>(result.target) -
        std::get<double>(current.target)
      );
    }

    return result;
  }

  extern program::value std_mul(
    program::program& program,
    core::list::const_iterator begin,
    core::list::const_iterator end
  ) {
    program::value result = program.node_exec(*begin);
    if (result.type != program::value_type::NUMBER) {
      throw std::runtime_error("Invalid argument types.");
    }

    for (++begin; begin != end; ++begin) {
      program::value current = program.node_exec(*begin);
      if (result.type != current.type) {
        throw std::runtime_error("Invalid argument types.");
      }
      result = program::value(
        std::get<double>(result.target) *
        std::get<double>(current.target)
      );
    }

    return result;
  }

  extern program::value std_div(
    program::program& program,
    core::list::const_iterator begin,
    core::list::const_iterator end
  ) {
    program::value result = program.node_exec(*begin);
    if (result.type != program::value_type::NUMBER) {
      throw std::runtime_error("Invalid argument types.");
    }

    for (++begin; begin != end; ++begin) {
      program::value current = program.node_exec(*begin);
      if (result.type != current.type) {
        throw std::runtime_error("Invalid argument types.");
      }
      result = program::value(
        std::get<double>(result.target) /
        std::get<double>(current.target)
      );
    }

    return result;
  }

  extern program::value std_if(
    program::program& program,
    core::list::const_iterator begin,
    core::list::const_iterator end
  ) {
    program::value cond = program.node_exec(*begin);

    if (
      cond.type == program::value_type::NIL ||
      (cond.type == program::value_type::NUMBER && !std::get<double>(cond.target)) ||
      (cond.type == program::value_type::STRING && "" == std::get<std::string>(cond.target)) ||
      (cond.type == program::value_type::BOOL && !std::get<bool>(cond.target))
    ) {
      return program.node_exec(*std::prev(end));
    }

    return program::value(program.node_exec(*std::next(begin)));
  }

  extern program::value std_int(
    program::program& program,
    core::list::const_iterator begin,
    [[maybe_unused]] core::list::const_iterator end
  ) {
    program::value first = program.node_exec(*begin);

    if (first.type != program::value_type::NUMBER) {
      throw std::runtime_error("Invalid argument types.");
    }

    auto val = (long long) std::get<double>(first.target);
    return program::value((double) val);
  }

  extern program::value std_println(
    program::program& program,
    core::list::const_iterator begin,
    core::list::const_iterator end
  ) {
    program::value result = std_print(program, begin, end);
    std::cout << '\n';
    return result;
  }

  extern program::value std_print(
    program::program& program,
    core::list::const_iterator begin,
    core::list::const_iterator end
  ) {
    for (auto it = begin; it != end; ++it) {
      program::value val = program.node_exec(*it);
      switch (val.type) {
        case program::value_type::NUMBER:
          std::cout << std::get<double>(val.target) << ' ';
          break;
        case program::value_type::BOOL:
          std::cout << std::boolalpha << std::get<bool>(val.target) << ' ';
          break;
        case program::value_type::NIL:
          std::cout << "null ";
          break;
        case program::value_type::STRING:
          std::cout << std::get<std::string>(val.target) << ' ';
          break;
        case program::value_type::FUNCTION:
          std::cout << "[Function] ";
          break;
      }
    }
    return program::value();
  }
}
