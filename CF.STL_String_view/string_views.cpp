//
//  string_views.cpp
//  CF.STL_String_view
//
//  Created by Alan Sampson on 4/3/21.
//  MARK: - Reference.
//  @see: https://en.cppreference.com/w/cpp/header/string_view
//  @see: https://en.cppreference.com/w/cpp/string/basic_string_view
//

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <compare>
#include <memory>
#include <type_traits>
#include <string_view>
#include <iterator>
#include <string>
#include <array>
#include <unordered_set>
#include <cwchar>
#include <stdexcept>
#include <typeinfo>
#include <cstddef>

using namespace std::literals::string_literals;
using namespace std::literals::string_view_literals;

//  MARK: - Definitions

 //  MARK: - Local Constants.
//  ....+....!....+....!....+....!....+....!....+....!....+....!....+....!....+....!
//  MARK: namespace konst
namespace konst {

auto delimiter(char const dc = '-', size_t sl = 80) -> std::string const {
  auto const dlm = std::string(sl, dc);
  return dlm;
}

static
auto const dlm = delimiter();

static
auto const dot = delimiter('.');

} /* namespace konst */

#if (__cplusplus > 201707L)
#endif  /* (__cplusplus > 201707L) */

//  MARK: - Function Prototype.
auto C_string_view(int argc, const char * argv[]) -> decltype(argc);
#if (__cplusplus > 201707L)
auto C_string_view_deduction_guides(int argc, const char * argv[]) -> decltype(argc);
#endif  /* (__cplusplus > 201707L) */

//  MARK: - Implementation.
//  ....+....!....+....!....+....!....+....!....+....!....+....!....+....!....+....!
/*
 *  MARK: main()
 */
int main(int argc, const char * argv[]) {
  // insert code here...
  std::cout << "CF.STL_String_view\n";
  std::cout << "C++ Version: "s << __cplusplus << std::endl;

  std::cout << '\n' << konst::dlm << std::endl;
  C_string_view(argc, argv);
#if (__cplusplus > 201707L)
  C_string_view_deduction_guides(argc, argv);
#endif  /* (__cplusplus > 201707L) */

  return 0;
}

//  MARK: - C_string_view
//  ....+....!....+....!....+....!....+....!....+....!....+....!....+....!....+....!
//  ================================================================================
//  ....+....!....+....!....+....!....+....!....+....!....+....!....+....!....+....!
/*
 *  MARK: C_string_view()
 */
auto C_string_view(int argc, const char * argv[]) -> decltype(argc) {
  std::cout << "In "s << __func__ << std::endl;

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::string_view"s << '\n';
  {
#define UTF16_
#if defined(UTF16_)
    std::string_view constexpr unicode[] {
      "\u2580\u2584\u2500", "\u2584\u2580\u2500",
      "\u2580\u2500\u2584", "\u2584\u2500\u2580",
    };
#elif defined(UTF8_)
    std::string_view constexpr unicode[] {
      "\xE2\x96\x80\xE2\x96\x84\xE2\x94\x80", "\xE2\x96\x84\xE2\x96\x80\xE2\x94\x80",
      "\xE2\x96\x80\xE2\x94\x80\xE2\x96\x84", "\xE2\x96\x84\xE2\x94\x80\xE2\x96\x80",
    };
#else
    std::string_view constexpr unicode[] {
      "▀▄─", "▄▀─", "▀─▄", "▄─▀",
    };
#endif

    for (int y_ {}, p_ {}; y_ != 6; ++y_, p_ = ((p_ + 1) % 4)) {
      for (int x_ {}; x_ != 16; ++x_) {
        std::cout << unicode[p_];
      }
      std::cout << '\n';
    }

    std::cout << '\n';
  }

  /// Member functions
  /// Constructors and assignment
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::string_view - constructor"s << '\n';
  {
    std::wstring_view constexpr wcstr_v = L"xyzzy";

    char array[3] = { 'B', 'a', 'r', };
    std::string_view array_v(array, std::size(array));

    std::string cppstr = "Foo";
    std::string_view cppstr_v(cppstr);

    [[maybe_unused]]
    std::array ar = { 'P', 'u', 'b', };
#if (__cplusplus > 201707L)
    std::string_view ar_v(ar.begin(), ar.end()); // C++20
#endif  /* (__cplusplus > 201707L) */

    std::cout << cppstr_v << ' '
              << array_v << ' '
#if (__cplusplus > 201707L)
              << ar_v << ' '
#endif  /* (__cplusplus > 201707L) */
              << wcstr_v.size() << '\n';

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::string_view - operator="s << '\n';
  {
    std::string_view vue = "Hello, world";
    vue = vue.substr(7);
    std::cout << vue << '\n';

    std::cout << '\n';
  }

  /// Iterators
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::string_view - begin, end, cbegin, cend"s << '\n';
  {
    std::string_view str_view("abcd");

    auto begin = str_view.begin();
    auto cbegin = str_view.cbegin();

    std::cout << *begin << '\n';
    std::cout << *cbegin << '\n';

    std::cout << std::boolalpha << (begin == cbegin) << '\n';
    std::cout << std::boolalpha << (*begin == *cbegin) << '\n';

    auto end = str_view.end();
    auto cend = str_view.cend();

    std::cout << *std::prev(end) << '\n';
    std::cout << *std::prev(cend) << '\n';

    std::cout << std::boolalpha << (end == cend) << '\n';

    std::cout << std::noboolalpha;

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::string_view - rbegin, rend, crbegin, crend"s << '\n';
  {
    std::ostream_iterator<char> out_it(std::cout);
    std::string_view str_view("abcdef");

    std::copy(str_view.rbegin(), std::next(str_view.rbegin(), 3), out_it);
    *out_it = '\n';

    std::copy(str_view.crbegin(), std::next(str_view.crbegin(), 3), out_it);
    *out_it = '\n';

    std::copy(str_view.rbegin(), str_view.rend(), out_it);
    *out_it = '\n';

    std::copy(str_view.crbegin(), str_view.crend(), out_it);
    *out_it = '\n';

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::string_view - operator[]"s << '\n';
  {
    std::string str = "Exemplar"s;
    std::string_view view = str;
    std::cout << view << '\n' << view[2] << '\n';
//    view[2] = 'y'; // Error: cannot modify through a string view
    str[2] = 'y';
    std::cout << view[2] << '\n' << str << '\n';

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::string_view - at"s << '\n';
  {
    std::string_view str_view("abcdef");

    try {
      for (std::size_t i_ = 0; true; ++i_) {
        std::cout << i_ << ": "s << str_view.at(i_) << '\n';
      }
    }
    catch (std::out_of_range const & ex) {
      std::cout << "Whooops. Index is out of range.\n"s;
      std::cout << ex.what() << '\n';
    }

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::string_view - front"s << '\n';
  {
    for (std::string_view str { "ABCDEF" }; !str.empty(); str.remove_prefix(1)) {
      std::cout << str.front() << ' ' << str << '\n';
    }

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::string_view - back"s << '\n';
  {
    for (std::string_view str { "ABCDEF" }; !str.empty(); str.remove_suffix(1)) {
      std::cout << str.back() << ' ' << str << '\n';
    }

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::string_view - data"s << '\n';
  {
    std::wstring_view wcstr_v = L"xyzzy";
    std::cout << std::wcslen(wcstr_v.data()) << '\n';
    // OK: the underlying character array is null-terminated
    wchar_t const * wd = wcstr_v.data();
    auto wdl = std::wcslen(wd);
    std::cout << std::hex << std::setfill('0');
    for (auto w_(0ul); w_ < wdl; ++w_) {
      auto ww = wd[w_];
      std::cout << sizeof(ww) << ' ' << std::setw(sizeof(ww) * 2) << ww << ' ';
    }
    std::cout << '\n' << std::setfill(' ') << std::dec;

    char array[3] = { 'B', 'a', 'r', };
    std::string_view array_v(array, sizeof array);
    // std::cout << std::strlen(array_v.data()) << '\n';
    // error: the underlying character array is not null-terminated

    std::string str(array_v.data(), array_v.size()); // OK
    std::cout << std::strlen(str.data()) << '\n';
    // OK: the underlying character array of a std::string is always null-terminated

    std::cout << '\n';
  }

  /// Capacity
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::string_view - size, length"s << '\n';
  {
    auto check_string = [](std::string_view ref) {
      // Print a string surrounded by single quotes, its length
      // and whether it is considered empty.
      std::cout << std::boolalpha
                << "'"s << ref << "' has "s << ref.size()
                << " character(s); emptiness: "s << ref.empty()
                << std::noboolalpha << '\n';
    };

    // An empty string
    check_string("");

    // Almost always not empty: argv[0]
    if (argc > 0) {
      check_string(argv[0]);
    }

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::string_view - max_size"s << '\n';
  {
    std::cout << std::dec;
    std::cout << std::setw(22)
              << std::numeric_limits<std::int64_t>::max()
              << " <- numeric_limits<int64_t>::max()\n"s
              << std::setw(22)
              << std::string_view{}.max_size()
              << " <- std::string_view::max_size()\n"s
              << std::setw(22)
              << std::basic_string_view<char>{}.max_size()
              << " <- std::basic_string_view<char>::max_size()\n"s
              << std::setw(22)
              << std::basic_string_view<char16_t>{}.max_size()
              << " <- std::basic_string_view<char16_t>::max_size()\n"s
              << std::setw(22)
              << std::wstring_view{}.max_size()
              << " <- std::wstring_view::max_size()\n"s
              << std::setw(22)
              << std::basic_string_view<char32_t>{}.max_size()
              << " <- std::basic_string_view<char32_t>::max_size()\n"s
              ;

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::string_view - empty"s << '\n';
  {
    auto check_string = [](std::string_view ref) {
      // Print a string surrounded by single quotes, its length
      // and whether it is considered empty.
      std::cout << std::boolalpha
                << "'"s << ref << "' has "s << ref.size()
                << " character(s); emptiness: "s << ref.empty()
                << std::noboolalpha << '\n';
    };

    // An empty string
    check_string("");

    // Almost always not empty: argv[0]
    if (argc > 0) {
      check_string(argv[0]);
    }

    std::cout << '\n';
  }

  /// Modifiers
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::string_view - remove_prefix"s << '\n';
  {
    std::string str = "   trim me"s;
    std::string_view view = str;
    view.remove_prefix(std::min(view.find_first_not_of(" "), view.size()));
    std::cout << "String: '"s << str << "'\n"s
              << "View  : '"s << view << "'\n"s;

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::string_view - remove_suffix"s << '\n';
  {
    char arr[] = {'a', 'b', 'c', 'd', '\0', '\0', '\0'};
    std::string_view view(arr, sizeof arr);
    auto trim_pos = view.find('\0');
    if (trim_pos != view.npos) {
      view.remove_suffix(view.size() - trim_pos);
    }
    std::cout << "Array: '"s << arr << "', size="s << sizeof arr << '\n'
              << "View : '"s << view << "', size="s << view.size() << '\n';

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::string_view - swap"s << '\n';
  {
#if defined(UTF16_)
    auto s1 { std::string_view { "\u23fa\u23fa\u23fa\u23fa\u23fa" } };
    auto s2 { std::string_view { "\u23f9\u23f9\u23f9\u23f9\u23f9" } };
#elif defined(UTF8_)
    auto s1 { std::string_view {
      "\xe2\x8f\xba" "\xe2\x8f\xba" "\xe2\x8f\xba" "\xe2\x8f\xba" "\xe2\x8f\xba" } };
    auto s2 { std::string_view {
      "\xE2\x8F\xB9" "\xE2\x8F\xB9" "\xE2\x8F\xB9" "\xE2\x8F\xB9" "\xE2\x8F\xB9" } };
#else
    auto s1 { std::string_view { "⏺⏺⏺⏺⏺" } };
    auto s2 { std::string_view { "⏹⏹⏹⏹⏹" } };
#endif

    std::cout << "Before : "s << s1 << ' ' << s2 << "\n"s;
    s1.swap(s2);
    std::cout << "After  : "s << s1 << ' ' << s2 << "\n"s;

    std::cout << '\n';
  }

  /// Operations
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::string_view - copy"s << '\n';
  {
    std::basic_string_view<char> constexpr source { "ABCDEF" };
    std::array<char, 8> dest;
    std::size_t count{}, pos{};

    dest.fill('\0');
    source.copy(dest.data(), count = 4); // pos = 0
    std::cout << dest.data() << '\n'; // ABCD

    dest.fill('\0');
    source.copy(dest.data(), count = 4, pos = 1);
    std::cout << dest.data() << '\n'; // BCDE

    dest.fill('\0');
    source.copy(dest.data(), count = 42, pos = 2); // ok, count -> 4
    std::cout << dest.data() << '\n'; // CDEF

    try {
      source.copy(dest.data(), count = 1, pos = 666); // throws: pos > size()
    }
    catch (std::out_of_range const & ex) {
      std::cout << ex.what() << '\n';
    }

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::string_view - substr"s << '\n';
  {
//    using namespace std::literals::string_view_literals;

    std::size_t count {}, pos {};
    auto constexpr data { "ABCDEF"sv };

    std::cout << data.substr() << '\n'; // ABCDEF
    std::cout << data.substr(pos = 1) << '\n'; // BCDEF
    std::cout << data.substr(pos = 2, count = 3) << '\n'; // CDE

    std::cout << data.substr(pos = 4, count = 42) << '\n'; // EF
    // count -> 2 == size() - pos == 6 - 4

    try {
      data.substr(pos = 666, count = 1); // throws: pos > size()
    }
    catch (std::out_of_range const & ex) {
      std::cout << ex.what() << '\n';
    }

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::string_view - compare"s << '\n';
  {
    auto comp1 = "ditto"sv.compare("ditto"sv);
    auto comp2 = "ditto"sv.compare("doodoo");
    auto comp3 = "ddditto"sv.compare(2, 3, "dit"sv);
    auto comp4 = "ddditto"sv.compare(2, 3, "diddle", 1, 5);

    std::cout << std::setw(4) << comp1
              << std::setw(4) << comp2
              << std::setw(4) << comp3
              << std::setw(4) << comp4
              << '\n';

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::string_view - starts_with"s << '\n';
  {
//    using namespace std::literals::string_view_literals;

    std::cout
        << std::boolalpha

        // bool starts_with(basic_string_view x) const noexcept;
        << "https://cppreference.com"sv.starts_with("http"sv) << ' ' // true
        << "https://cppreference.com"sv.starts_with("ftp"sv) << ' '  // false

        // bool starts_with(CharT x) const noexcept;
        << "C++20"sv.starts_with('C') << ' ' // true
        << "C++20"sv.starts_with('J') << ' ' // false

        // bool starts_with(const CharT* x) const;
        << std::string_view("string_view").starts_with("string") << ' ' // true
        << std::string_view("string_view").starts_with("String") << ' ' // false

        << std::noboolalpha
        << '\n';

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::string_view - ends_with"s << '\n';
  {
    using namespace std::literals;

    std::cout
        << std::boolalpha

        // (1) bool ends_with( basic_string_view sv ) const noexcept;
        << std::string_view("https://cppreference.com").ends_with(".com"sv) << ' ' // true
        << std::string_view("https://cppreference.com").ends_with(".org"sv) << ' ' // false

        // (2) bool ends_with( CharT c ) const noexcept;
        << std::string_view("C++20").ends_with('0') << ' ' // true
        << std::string_view("C++20").ends_with('3') << ' ' // false

        // (3) bool ends_with( const CharT* s ) const;
        << std::string_view("string_view").ends_with("view") << ' ' // true
        << std::string_view("string_view").ends_with("View") << ' ' // false

        << std::noboolalpha
        << '\n';

    std::cout << '\n';
  }

#if (__cplusplus >= 202300L)
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::string_view - contains"s << '\n';
  {
//    using namespace std::literals::string_view_literals;

    std::cout
        << std::boolalpha

        // bool contains(basic_string_view x) const noexcept;
        << "https://cppreference.com"sv.contains("cpp"sv)  << ' ' // true
        << "https://cppreference.com"sv.contains("java"sv) << ' ' // false

        // bool contains(CharT x) const noexcept;
        << "C++23"sv.contains('+') << ' ' // true
        << "C++23"sv.contains('-') << ' ' // false

        // bool contains(const CharT* x) const;
        << std::string_view("basic_string_view").contains("string") << ' ' // true
        << std::string_view("basic_string_view").contains("String") << ' ' // false
        << '\n';

    std::cout << '\n';
  }
#endif  /* (__cplusplus > 202300L) */

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::string_view - find"s << '\n';
  {
//    using namespace std::literals::string_view_literals;

    auto constexpr str{" long long int;"sv};

    static_assert(
        1 == str.find("long"sv)            && "<- find(v , pos = 0)" &&
        6 == str.find("long"sv, 2)         && "<- find(v , pos = 2)" &&
        0 == str.find(' ')                 && "<- find(ch, pos = 0)" &&
        2 == str.find('o', 1)              && "<- find(ch, pos = 1)" &&
        2 == str.find("on")                && "<- find(s , pos = 0)" &&
        6 == str.find("long double", 5, 4) && "<- find(s , pos = 5, count = 4)"
    );

    std::cout << std::setw(4) << str.find("long"sv, 0)
              << std::setw(4) << str.find("long"sv, 2)
              << std::setw(4) << str.find(' ', 0)
              << std::setw(4) << str.find('o', 1)
              << std::setw(4) << str.find("on", 0)
              << std::setw(4) << str.find("long double", 5, 4)
              << '\n';

    static_assert(str.npos == str.find("float"));

    std::cout << std::boolalpha
              << (str.npos == str.find("float"))
              << std::noboolalpha
              << '\n';

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::string_view - rfind"s << '\n';
  {
//    using namespace std::literals::string_view_literals;

    auto constexpr Npos = std::string_view::npos;
     
        static_assert(true
            && (6 == "AB AB AB"sv.rfind("AB"))
            && (6 == "AB AB AB"sv.rfind("ABCD", Npos, 2))
            && (3 == "AB AB AB"sv.rfind("AB", 5))
            && (2 == "B AB AB "sv.rfind("AB", 2))
            && (Npos == "B AB AB "sv.rfind("AB", 1))
            && (5 == "B AB AB "sv.rfind('A'))
            && (4 == "AB AB AB"sv.rfind('B', 4))
            && (Npos == "AB AB AB"sv.rfind('C'))
        );

    std::cout << std::boolalpha
              << (6 == "AB AB AB"sv.rfind("AB")) << ' '
              << (6 == "AB AB AB"sv.rfind("ABCD", Npos, 2)) << ' '
              << (3 == "AB AB AB"sv.rfind("AB", 5)) << ' '
              << (2 == "B AB AB "sv.rfind("AB", 2)) << ' '
              << (Npos == "B AB AB "sv.rfind("AB", 1)) << ' '
              << (5 == "B AB AB "sv.rfind('A')) << ' '
              << (4 == "AB AB AB"sv.rfind('B', 4)) << ' '
              << (Npos == "AB AB AB"sv.rfind('C')) << ' '
              << std::noboolalpha
              << '\n';

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::string_view - find_first_of"s << '\n';
  {
//    using namespace std::literals::string_view_literals;

    auto constexpr Npos = std::string_view::npos;

    auto is_white_space = [](char const ch) noexcept {
      return " \t\n\f\r\v"sv.find_first_of(ch) != Npos;
    };

    static_assert(
        1 == "alignas"sv.find_first_of("klmn"sv) &&
          //   └─────────────────────────┘
        Npos == "alignof"sv.find_first_of("wxyz"sv) &&
          //
        3 == "concept"sv.find_first_of("bcde"sv, /* pos= */ 1) &&
          //     └───────────────────────┘
        Npos == "consteval"sv.find_first_of("oxyz"sv, /* pos= */ 2) &&
          //
        6 == "constexpr"sv.find_first_of('x') &&
          //        └─────────────────────┘
        Npos == "constinit"sv.find_first_of('x') &&
          //
        6 == "const_cast"sv.find_first_of('c', /* pos= */ 4) &&
          //        └──────────────────────┘
        Npos == "continue"sv.find_first_of('c', /* pos= */ 42) &&
          //
        5 == "co_await"sv.find_first_of("cba", /* pos= */ 4) &&
          //       └───────────────────────┘
        7 == "decltype"sv.find_first_of("def", /* pos= */ 2, /* count= */ 2) &&
          //         └────────────────────┘
        Npos == "decltype"sv.find_first_of("def", /* pos= */ 2, /* count= */ 1) &&
          //
        is_white_space(' ') && is_white_space('\r') && !is_white_space('\a')
    );
    std::cout << "All tests passed.\n"sv;

    std::cout
      << std::boolalpha
      << ("alignas"sv.find_first_of("klmn"sv)) << ' '
            //   └─────────────────────────┘
      << (Npos == "alignof"sv.find_first_of("wxyz"sv)) << ' '
            //
      << ("concept"sv.find_first_of("bcde"sv, /* pos= */ 1)) << ' '
            //     └───────────────────────┘
      << (Npos == "consteval"sv.find_first_of("oxyz"sv, /* pos= */ 2)) << ' '
            //
      << ("constexpr"sv.find_first_of('x')) << ' '
            //        └─────────────────────┘
      << (Npos == "constinit"sv.find_first_of('x')) << ' '
            //
      << ("const_cast"sv.find_first_of('c', /* pos= */ 4)) << ' '
            //        └──────────────────────┘
      << (Npos == "continue"sv.find_first_of('c', /* pos= */ 42)) << ' '
            //
      << ("co_await"sv.find_first_of("cba", /* pos= */ 4)) << ' '
            //       └───────────────────────┘
      << ("decltype"sv.find_first_of("def", /* pos= */ 2, /* count= */ 2)) << ' '
            //         └────────────────────┘
      << (Npos == "decltype"sv.find_first_of("def", /* pos= */ 2, /* count= */ 1)) << ' '
            //
      << (is_white_space(' ') && is_white_space('\r') && !is_white_space('\a'))
      << std::noboolalpha
      << '\n';

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::string_view - find_last_of"s << '\n';
  {
    using namespace std::literals::string_view_literals;

    auto constexpr Npos = std::string_view::npos;

    static_assert(
      5 == "delete"sv.find_last_of("cdef"sv) &&
        //       └────────────────────┘
      Npos == "double"sv.find_last_of("fghi"sv) &&
        //
      0 == "else"sv.find_last_of("bcde"sv, 2 /* pos [0..2]: "els" */) &&
        //  └────────────────────────┘
      Npos == "explicit"sv.find_last_of("abcd"sv, 4 /* pos [0..4]: "expli" */) &&
        //
      3 == "extern"sv.find_last_of('e') &&
        //     └────────────────────┘
      Npos == "false"sv.find_last_of('x') &&
        //
      0 == "inline"sv.find_last_of('i', 2 /* pos [0..2]: "inl" */) &&
        //  └───────────────────────┘
      Npos == "mutable"sv.find_last_of('a', 2 /* pos [0..2]: "mut" */) &&
        //
      3 == "namespace"sv.find_last_of("cdef", 3 /* pos [0..3]: "name" */, 3 /* "cde" */) &&
        //     └─────────────────────────┘
      Npos == "namespace"sv.find_last_of("cdef", 3 /* pos [0..3]: "name" */, 2 /* "cd" */)
    );

    std::cout << "All tests passed.\n"sv;

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::string_view - find_first_not_of"s << '\n';
  {
    static_assert(2 == "BCDEF"sv.find_first_not_of("ABC"));
                    //    ^
    static_assert(4 == "BCDEF"sv.find_first_not_of("ABC", 4));
                    //      ^
    static_assert(1 == "BCDEF"sv.find_first_not_of('B'));
                    //   ^
    static_assert(3 == "BCDEF"sv.find_first_not_of('D', 2));
                    //     ^

    std::cout << "All tests passed.\n"sv;

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::string_view - find_last_not_of"s << '\n';
  {
    static_assert(1 == "BCDEF"sv.find_last_not_of("DEF"));
                    //   ^
    static_assert(2 == "BCDEFG"sv.find_last_not_of("EFG", 3));
                    //    ^
    static_assert(2 == "ABBA"sv.find_last_not_of('A'));
                    //    ^
    static_assert(1 == "ABBA"sv.find_last_not_of('A', 1));
                    //   ^

    std::cout << "All tests passed.\n"sv;

    std::cout << '\n';
  }

  /// Constants
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::string_view - npos"s << '\n';
  {
    auto constexpr
    contains = [](std::string_view const what, std::string_view const where)
    noexcept -> bool {
      return std::string_view::npos != where.find(what);
    };

//    using namespace std::literals::string_view_literals;

    static_assert(contains("water", "in a bottle of water"));
    static_assert(!contains("wine", "in a bottle of champagne"));
    static_assert(""sv.npos == "haystack"sv.find("needle"));

    std::cout << "All tests passed.\n"sv;

    std::cout << "std::string_view::npos: "sv << std::string_view::npos << '\n';

    std::cout << '\n';
  }

  /// Non-member functions
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::string_view - operator==, etc."s << '\n';
  {
    auto comp1 = "ditto"sv == "ditto"sv;
    auto comp2 = "ditto"sv != "doodoo";
    auto comp3 = "ddditto"sv > "dit"sv;
    auto comp4 = "ddditto"sv <= "diddle";

    std::cout << std::boolalpha
              << comp1 << ' '
              << comp2 << ' '
              << comp3 << ' '
              << comp4 << ' '
              << std::noboolalpha
              << '\n';

    std::cout << '\n';
  }

  /// Input/output
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::string_view - operator<<"s << '\n';
  {
    std::cout << "std::string_view"sv << '\n';

    std::cout << '\n';
  }

  /// Literals
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::literals::string_view_literals::operator""sv"sv << '\n';
  {
//    using namespace std::literals::string_view_literals;

    std::string_view s1 = "abc\0\0def";
    std::string_view s2 = "abc\0\0def"sv;
    std::cout << "s1: " << s1.size() << " \"" << s1 << "\"\n";
    std::cout << "s2: " << s2.size() << " \"" << s2 << "\"\n";

    std::cout
        << sizeof(decltype( "char A"sv      )::value_type) << ' '
        << sizeof(decltype( L"wchar_t ∀"sv  )::value_type) << ' '
        << sizeof(decltype( u8"char8_t ∆"sv )::value_type) << ' '
        << sizeof(decltype( u"char16_t ∇"sv )::value_type) << ' '
        << sizeof(decltype( U"char32_t ∃"sv )::value_type) << ' '
        << sizeof(decltype( LR"(raw ⊞)"sv   )::value_type) << ' '
        << '\n';

    std::cout << '\n';
  }

  /// Helper classes
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::string_view - hash"sv << '\n';
  {
    std::cout << std::hex;
    std::cout << "\"A\"   #: " << std::hash<std::string_view>{}("A"sv) << '\n';
    std::cout << "L\"B\"  #: " << std::hash<std::wstring_view>{}(L"B"sv) << '\n';
    std::cout << "u8\"C\" #: " << std::hash<std::u8string_view>{}(u8"C"sv) << '\n';
    std::cout << "u\"D\"  #: " << std::hash<std::u16string_view>{}(u"D"sv) << '\n';
    std::cout << "U\"E\"  #: " << std::hash<std::u32string_view>{}(U"E"sv) << '\n';
    std::cout << std::dec;

    // std::hash for string_view family makes it possible to keep these view-types
    // in unordered_* associative containers, such as unordered_set. But ensure
    // the lifespan of referenced strings is no less than lifespan of the container,
    // i.e. no dangling references occurred.

    //  std::string_view
    std::unordered_set stars_sv{"Rigel"sv, "Capella"sv, "Vega"sv, "Arcturus"sv};
    //  std::string
    std::unordered_set stars_s{"Rigel"s, "Capella"s, "Vega"s, "Arcturus"s};
    //  char const *
    std::unordered_set stars_c{"Rigel", "Capella", "Vega", "Arcturus"};

    auto star = [](auto & star) {
      std::cout << star << ' ';
    };

    //  std::string_view
    std::cout << typeid(stars_sv).name() << '\n';
    std::for_each(stars_sv.cbegin(), stars_sv.cend(), star);
    std::cout << '\n' << '\n';

    //  std::string
    std::cout << typeid(stars_s).name() << '\n';
    std::for_each(stars_s.cbegin(), stars_s.cend(), star);
    std::cout << '\n' << '\n';

    //  char const *
    std::cout << typeid(stars_c).name() << '\n';
    std::for_each(stars_c.cbegin(), stars_c.cend(), star);
    std::cout << '\n' << '\n';

    std::cout << '\n';
  }

  std::cout << std::endl; //  make sure cout is flushed.

  return 0;
}

#if (__cplusplus > 201707L)
//  MARK: - C_string_view_deduction_guides
//  ....+....!....+....!....+....!....+....!....+....!....+....!....+....!....+....!
//  ================================================================================
//  ....+....!....+....!....+....!....+....!....+....!....+....!....+....!....+....!
/*
 *  MARK: C_string_view_deduction_guides()
 */
auto C_string_view_deduction_guides(int argc, const char * argv[]) -> decltype(argc) {
  std::cout << "In "s << __func__ << std::endl;

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::string_view - deduction guides"s << '\n';
  {
    std::array a1 { 'n', 'u', 'c', 'l', 'e', 'o', 'n', 's', ':', '\n', };
    std::basic_string_view s1(a1.cbegin(), a1.cend()); // deduction: CharT -> char
    static_assert(std::is_same_v<decltype(s1)::value_type, char>);
    std::cout << s1;

    std::array a2 { L'p', L'r', L'o', L't', L'o', L'n', L's', L'\n', };
    std::basic_string_view s2(a2.cbegin(), a2.cend()); // deduction: CharT -> wchar_t
    static_assert(std::is_same_v<decltype(s2)::value_type, wchar_t>);
    std::wcout << s2;

    std::array<long, 9> a3 { 'n', 'e', 'u', 't', 'r', 'o', 'n', 's', '\n', };
    std::basic_string_view s3(a3.cbegin(), a3.cend()); // deduction: CharT -> long
    static_assert(std::is_same_v<decltype(s3)::value_type, long>);
    for (const auto el : s3) { std::cout << static_cast<char>(el); }

    std::cout << '\n';
  }

  std::cout << std::endl; //  make sure cout is flushed.

  return 0;
}
#endif  /* (__cplusplus > 201707L) */
