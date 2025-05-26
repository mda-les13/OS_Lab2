#include <mettle.hpp>
using namespace mettle;

#include <cstring>

template<typename Char>
std::basic_string<Char> make_string(const char *s) {
  std::size_t n = std::strlen(s);
  std::basic_string<Char> result(n, static_cast<Char>('\0'));
  for(std::size_t i = 0; i != n; i++)
    result[i] = static_cast<Char>(s[i]);
  return result;
}

suite<> test_string_output("string output", [](auto &_) {
  subsuite<>(_, "escape_string()", [](auto &_) {
    _.test("std::string", []() {
      using namespace std::literals::string_literals;
      expect(escape_string("text"s), equal_to("\"text\""));
    });

    _.test("std::string_view", []() {
      using namespace std::literals::string_view_literals;
      expect(escape_string("text"sv), equal_to("\"text\""));
    });

    _.test("char *", []() {
      expect(escape_string("text"), equal_to("\"text\""));
    });

    _.test("escaping", []() {
      expect(escape_string("\"text\""), equal_to("\"\\\"text\\\"\""));
      expect(escape_string("te\\xt"), equal_to("\"te\\\\xt\""));
      expect(escape_string("text\nmore"), equal_to("\"text\\nmore\""));
      expect(escape_string(std::string{'a', '\0', 'b'}), equal_to("\"a\\0b\""));
      expect(escape_string("\a\b\f\n\r\t\v\x1f"),
             equal_to("\"\\a\\b\\f\\n\\r\\t\\v\\x1f\""));
    });

    _.test("delimiter", []() {
      expect(escape_string("'text'", '\''), equal_to("'\\'text\\''"));
      expect(escape_string("te\\xt", '\''), equal_to("'te\\\\xt'"));
    });
  });

  subsuite<
    char, char8_t, wchar_t, char16_t, char32_t
  >(_, "convert_string()", type_only, [](auto &_) {
    using C = fixture_type_t<decltype(_)>;
    auto T = &make_string<C>;
    using S = std::basic_string<C>;
    using SV = std::basic_string_view<C>;

    _.test("std::basic_string", [T]() {
      expect(convert_string(T("text")), equal_to("text"));
      expect(convert_string(S{C('a'), C('\0'), C('b')}),
             equal_to(std::string{'a', '\0', 'b'}));
    });

    _.test("std::basic_string_view", [T]() {
      expect(convert_string(SV(T("text"))), equal_to("text"));
      expect(convert_string(SV(S{C('a'), C('\0'), C('b')})),
             equal_to(std::string{'a', '\0', 'b'}));
    });

    _.test("C string", [T]() {
      expect(convert_string(T("text").c_str()), equal_to("text"));
    });
  });

  subsuite<
    char, char8_t, wchar_t, char16_t, char32_t
  >(_, "represent_string()", type_only, [](auto &_) {
    using C = fixture_type_t<decltype(_)>;
    auto T = &make_string<C>;
    using SV = std::basic_string_view<C>;

    _.test("std::basic_string", [T]() {
      expect(represent_string(T("text")), equal_to("\"text\""));
    });

    _.test("std::basic_string_view", [T]() {
      expect(represent_string(SV(T("text"))), equal_to("\"text\""));
    });

    _.test("C string", [T]() {
      expect(represent_string(T("text").c_str()), equal_to("\"text\""));
    });
  });
});
