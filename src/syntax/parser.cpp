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

#include <stdexcept>
#include <string>
#include <cstddef>

#include "core/token.hpp"
#include "core/list.hpp"

#include "syntax/parser.hpp"

namespace sophia::syntax {
  extern core::list parser::parse() {
    ++_deep;
    core::list list;

    _token = _target.scan_next();
    while (
      _token.type != core::token_type::END &&
      _token.type != core::token_type::RPAREN
    ) {
      process_token(list);
      _token = _target.scan_next();
    }

    if (_deep <= 1 && _token.type == core::token_type::RPAREN) {
      throw unexpected_paren(_token);
    }

    --_deep;
    return list;
  }

  extern void parser::process_token(core::list& list) {
    if (_token.type != core::token_type::LPAREN) {
      return list.push_back({ core::node_type::TOKEN, _token });
    }

    core::list result = parse();
    if (_token.type != core::token_type::RPAREN) {
      throw unclosed_paren(_token);
    }
    list.push_back({ core::node_type::LIST, result });
  }
}
