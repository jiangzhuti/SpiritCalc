#include <boost/spirit/home/x3.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

#include <string>
#include <iostream>

namespace x3 = boost::spirit::x3;
using x3::double_;
using x3::_attr;
using x3::space;
using x3::phrase_parse;
using x3::_val;

x3::rule<class expression, double> const expression("expression");
x3::rule<class term, double> const term("term");
x3::rule<class factor, double> const factor("factor");

auto assign_ = [](auto& ctx)
              {
                  _val(ctx) = _attr(ctx);
              };
auto add_ = [](auto& ctx)
           {
               _val(ctx) += _attr(ctx);
           };
auto sub_ = [](auto& ctx)
           {
               _val(ctx) -= _attr(ctx);
           };

auto mul_ = [](auto& ctx)
           {
               _val(ctx) *= _attr(ctx);
           };
auto div_ = [](auto& ctx)
           {
               _val(ctx) /= _attr(ctx);
           };

auto const expression_def =
    term[assign_]
    >> *(   ('+' >> term            [add_])
        |   ('-' >> term            [sub_])
        )
    ;

auto const term_def =
    factor[assign_]
    >> *(   ('*' >> factor          [mul_])
        |   ('/' >> factor          [div_])
        )
    ;

auto const factor_def =
    double_
    |   '(' >> expression >> ')'
    ;

BOOST_SPIRIT_DEFINE(
    expression
  , term
  , factor
);

int main()
{
    std::string line;
    while (true) {
        std::getline(std::cin, line);
        if (line == "q") {
            break;
        }
        auto it = line.begin();
        auto const end = line.end();
        double result = 0.0;
        bool ret = phrase_parse(it, end, expression, space, result);
        if (ret && it == end) {
            std::cout << result << std::endl;
        } else {
            std::cout <<std::string("failed to parse at: \"").append(std::string(it, end)).append("\"") << std::endl;;
        }
    }
    return 0;
}
