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

#ifndef SOPHIA_SYNTAX_PARSER_HPP
#define SOPHIA_SYNTAX_PARSER_HPP

#include <string>
#include <cstddef>
#include <stdexcept>

#include "core/token.hpp"
#include "core/list.hpp"

#include "syntax/lexer.hpp"

namespace sophia::syntax {
  class parser {
    public:
      class exception: public std::runtime_error {
        public:
          exception(const char* message, const core::token& token)
            : std::runtime_error(message)
            , _token(token) {}

          core::token where() const noexcept { return _token; }

        private:
          core::token _token;
      };

      class unclosed_paren: public exception {
        public:
          unclosed_paren(const core::token& token)
            : exception("Expected ')' after a list.", token) {}
      };

      class unexpected_paren: public exception {
        public:
          unexpected_paren(const core::token& token)
            : exception("Unexpected ')'.", token) {}
      };

    public:
      parser(const lexer& lexer)
        : _target(lexer)
        , _token()
        , _deep(0) {}

      parser(
        std::string::const_iterator begin,
        std::string::const_iterator end
      ) : _target(begin, end)
        , _token()
        , _deep(0) {}

      core::list parse();

    private:
      lexer _target;
      core::token _token;
      std::size_t _deep;

    private:
      void process_token(core::list&);
  };
}

#endif // SOPHIA_SYNTAX_PARSER_HPP
