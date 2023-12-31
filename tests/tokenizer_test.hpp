#include "token/token.hpp"
#include "tokenizer/tokenizer.hpp"

#include <cstdint>
#include <string>
#include <vector>

#include "catch2/catch_test_macros.hpp"

TEST_CASE("Tokenizer skips BOM at the beginning", "[tokenizer]") {
  auto input = std::string();
  input.push_back(0xEF);
  input.push_back(0xBB);
  input.push_back(0xBF);

  REQUIRE(input.length() == 3);

  auto tokenizer = mirim::tokenizer::Tokenizer(input);
  auto tok = tokenizer.next();

  REQUIRE(tok.kind == mirim::token::Eof);
}

TEST_CASE("Tokenizer sees 0 byte as an illegal token", "[tokenizer]") {
  auto input = std::string();
  input.push_back(0);

  auto tokenizer = mirim::tokenizer::Tokenizer(input);
  auto tok = tokenizer.next();

  REQUIRE(tok.kind == mirim::token::Illegal);
}

TEST_CASE("Tokenizer sees + byte as plus token", "[tokenizer]") {
  auto input = std::string("+");

  auto tokenizer = mirim::tokenizer::Tokenizer(input);
  auto tok = tokenizer.next();

  REQUIRE(tok.kind == mirim::token::Plus);
}

TEST_CASE("Tokenizer tokenizes single char operators correctly",
          "[tokenizer]") {
  std::string input = "+-*/%=!&|^<>,.:#?([{)]}";

  auto tokenizer = mirim::tokenizer::Tokenizer(input);

  std::vector<mirim::token::Token> expected_tokens = {
      mirim::token::Token(mirim::token::Plus),
      mirim::token::Token(mirim::token::Minus),
      mirim::token::Token(mirim::token::Star),
      mirim::token::Token(mirim::token::Slash),

      mirim::token::Token(mirim::token::Percent),
      mirim::token::Token(mirim::token::Equal),
      mirim::token::Token(mirim::token::Bang),
      mirim::token::Token(mirim::token::Ampersand),

      mirim::token::Token(mirim::token::Pipe),
      mirim::token::Token(mirim::token::Caret),
      mirim::token::Token(mirim::token::AngleBracketLeft),
      mirim::token::Token(mirim::token::AngleBracketRight),

      mirim::token::Token(mirim::token::Comma),
      mirim::token::Token(mirim::token::Period),
      mirim::token::Token(mirim::token::Colon),
      mirim::token::Token(mirim::token::Pound),
      mirim::token::Token(mirim::token::QuestionMark),

      mirim::token::Token(mirim::token::LParen),
      mirim::token::Token(mirim::token::LBrack),
      mirim::token::Token(mirim::token::LBrace),

      mirim::token::Token(mirim::token::RParen),
      mirim::token::Token(mirim::token::RBrack),
      mirim::token::Token(mirim::token::RBrace),

      mirim::token::Token(mirim::token::Eof),
  };

  for (uint32_t i = 0; i <= input.length(); i++) {
    auto provided = tokenizer.next();
    auto expected = expected_tokens.at(i).kind;
    REQUIRE(provided.kind == expected);
  }
}

TEST_CASE("Tokenizer skips whitespace", "[tokenizer]") {
  std::string input = "    +   ";

  auto tokenizer = mirim::tokenizer::Tokenizer(input);

  std::vector<mirim::token::Token> expected_tokens = {
      mirim::token::Token(mirim::token::Plus),
      mirim::token::Token(mirim::token::Eof),
  };

  for (uint32_t i = 0; i < 2; i++) {
    auto provided = tokenizer.next();
    auto expected = expected_tokens.at(i).kind;
    REQUIRE(provided.kind == expected);
  }
}