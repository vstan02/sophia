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

#ifndef SOPHIA_SYNTAX_LEXER_HPP
#define SOPHIA_SYNTAX_LEXER_HPP

#include <string>
#include <cstddef>
#include <stdexcept>

#include "core/token.hpp"

namespace sophia::syntax {
  class lexer {
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

      class unexpected_character: public exception {
        public:
          unexpected_character(const core::token& token)
            : exception("Unexpected character.", token) {}
      };

      class unterminated_string: public exception {
        public:
          unterminated_string(const core::token& token)
            : exception("Unterminated string.", token) {}
      };

    public:
      lexer(
        std::string::const_iterator begin,
        std::string::const_iterator end
      ) : _line(1)
        , _current(begin)
        , _start(begin)
        , _end(end) {}

      core::token scan_next();

    private:
      std::size_t _line;
      std::string::const_iterator _current;
      std::string::const_iterator _start;
      std::string::const_iterator _end;

    private:
      void skip_whitespaces();

      core::token scan_kw_or_id();
      core::token scan_number();
      core::token scan_string();

      core::token scan_unknown() const {
        return scan_token(core::token_type::UNKNOWN);
      }

      core::token scan_token(core::token_type type) const {
        return { type, { _start, _current }, _line };
      }
  };
}

#endif // SOPHIA_SYNTAX_LEXER_HPP
