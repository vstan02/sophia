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

#include <string>
#include <cctype>
#include <algorithm>

#include "core/token.hpp"

#include "syntax/lexer.hpp"

namespace sophia::syntax {
  struct keyword {
    std::string target;
    core::token_type type;
  };

  static keyword kws[] = {
    { "true", core::token_type::TRUE },
    { "false", core::token_type::FALSE },
    { "nil", core::token_type::NIL }
  };

  static inline bool isname(char ch) {
    return std::isgraph(ch)
      && ch != '(' && ch != ')' && ch != '"';
  }

  extern core::token lexer::scan_next() {
    skip_whitespaces();
    if (_current == _end) {
      return scan_token(core::token_type::END);
    }

    _start = _current;
    char ch = *(_current++);

    if (std::isdigit(ch)) {
      return scan_number();
    }

    if (isname(ch)) {
      return scan_kw_or_id();
    }

    switch (ch) {
      case '"': return scan_string();
      case '(': return scan_token(core::token_type::LPAREN);
      case ')': return scan_token(core::token_type::RPAREN);
    }

    throw unexpected_character(scan_unknown());
  }

  extern void lexer::skip_whitespaces() {
    while (true) {
      switch (*_current) {
        case ' ':
        case '\t':
        case '\r':
          ++_current;
          break;
        case '\n':
          ++_line;
          ++_current;
          break;
        default:
          return;
      }
    }
  }

  extern core::token lexer::scan_kw_or_id() {
    while (isname(*_current)) ++_current;

    std::string value(_start, _current);
    const keyword* it = std::find_if(
      std::begin(kws), std::end(kws),
      [&](const keyword& kw) -> bool { return value == kw.target; }
    );

    return {
      it == std::end(kws) ? core::token_type::ID : it->type,
      std::move(value),
      _line
    };
  }

  extern core::token lexer::scan_number() {
    while (std::isdigit(*_current)) ++_current;
    if (*_current == '.') {
      ++_current;
      while (std::isdigit(*_current)) ++_current;
    }
    return scan_token(core::token_type::NUMBER);
  }

  extern core::token lexer::scan_string() {
    ++_current;
    while (_current != _end && *_current != '"') {
      ++_current;
    }

    if (_current == _end) {
      throw unterminated_string(scan_unknown());
    }

    ++_current;
    return {
      core::token_type::STRING,
      { _start + 1, _current - 1 },
      _line
    };
  }
}
