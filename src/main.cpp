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

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "core/list.hpp"
#include "core/token.hpp"

#include "syntax/lexer.hpp"
#include "syntax/parser.hpp"

#include "program/program.hpp"

#include "libcore.hpp"

static std::string readfile(const std::string&);

extern int main(int argc, const char** argv) {
  using namespace sophia;
  try {
    if (argc < 2) {
      throw std::runtime_error("Invalid file path.");
    }

    std::string code(readfile(argv[1]));
    syntax::parser parser(code.cbegin(), code.cend());
    program::program program({
      { "def", std_def, 2, false },
      { "defn", std_defn, 3, true },
      { "+", std_add, 1, true },
      { "-", std_sub, 1, true },
      { "*", std_mul, 1, true },
      { "/", std_div, 1, true },
      { "int", std_int, 1, false },
      { "if", std_if, 3, false },
      { "print", std_print, 1, true },
      { "println", std_println, 1, true }
    });

    program.exec(parser.parse());
    program.exec(core::list {{
      core::node_type::TOKEN,
      core::token(core::token_type::ID, "main", 0)
    }});
    return EXIT_SUCCESS;
  } catch (const std::exception& error) {
    std::cerr << "[Error]: " << error.what() << '\n';
    return EXIT_FAILURE;
  }
}

static std::string readfile(const std::string& path) {
  std::ifstream file(path);
  if (!file.is_open()) {
    throw std::runtime_error("Can't open the file.");
  }

  std::string content;
  std::getline(file, content);
  while (!file.eof()) {
    std::string line;
    std::getline(file, line);
    content += '\n' + line;
  }

  file.close();
  return content;
}
