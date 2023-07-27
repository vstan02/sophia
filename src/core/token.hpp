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

#ifndef SOPHIA_CORE_TOKEN_HPP
#define SOPHIA_CORE_TOKEN_HPP

#include <cstddef>
#include <string>
#include <utility>

namespace sophia::core {
  enum class token_type {
    LPAREN,
    RPAREN,
    ID,
    NUMBER,
    STRING,
    TRUE,
    FALSE,
    NIL,
    UNKNOWN,
    END
  };

  struct token {
    token_type type;
    std::string value;
    std::size_t line;

    token(token_type type = token_type::END)
      : type(type)
      , value()
      , line(1) {}

    token(token_type type, std::size_t line)
      : type(type)
      , value()
      , line(line) {}

    token(token_type type, const std::string& value, std::size_t line)
      : type(type)
      , value(value)
      , line(line) {}

    token(token_type type, std::string&& value, std::size_t line)
      : type(type)
      , value(std::move(value))
      , line(line) {}
  };
}

#endif // SOPHIA_CORE_TOKEN_HPP
