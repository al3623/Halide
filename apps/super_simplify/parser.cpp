#include "parser.h"

#include <fstream>
#include <stdio.h>

using std::ostringstream;
using std::string;
using std::vector;
using namespace Halide;
using namespace Halide::Internal;
bool is_whitespace(char c) {
    return c == ' ' || c == '\n' || c == '\t';
}

void consume_whitespace(char **cursor, char *end) {
    while (*cursor < end && is_whitespace(**cursor)) {
        (*cursor)++;
    }
}

bool consume(char **cursor, char *end, const char *expected) {
    char *tmp = *cursor;
    while (*tmp == *expected && tmp < end && *expected) {
        tmp++;
        expected++;
    }
    if ((*expected) == 0) {
        *cursor = tmp;
        return true;
    } else {
        return false;
    }
}

void expect(char **cursor, char *end, const char *pattern) {
    if (!consume(cursor, end, pattern)) {
        printf("Parsing failed. Expected %s, got %s\n",
               pattern, *cursor);
        abort();
    }
}

bool check(char **cursor, char *end, const char *pattern) {
    char *tmp_cursor = *cursor;
    return consume(&tmp_cursor, end, pattern);
}

string consume_token(char **cursor, char *end) {
    size_t sz = 0;
    while (*cursor + sz < end &&
           (std::isalnum((*cursor)[sz]) ||
            (*cursor)[sz] == '!' ||
            (*cursor)[sz] == '.' ||
            (*cursor)[sz] == '$' ||
            (*cursor)[sz] == '_'))
        sz++;
    string result{*cursor, sz};
    *cursor += sz;
    return result;
}

int64_t consume_int(char **cursor, char *end) {
    bool negative = consume(cursor, end, "-");
    int64_t n = 0;
    while (*cursor < end && **cursor >= '0' && **cursor <= '9') {
        n *= 10;
        n += (**cursor - '0');
        (*cursor)++;
    }
    return negative ? -n : n;
}

Expr consume_float(char **cursor, char *end) {
    bool negative = consume(cursor, end, "-");
    int64_t integer_part = consume_int(cursor, end);
    int64_t fractional_part = 0;
    int64_t denom = 1;
    if (consume(cursor, end, ".")) {
        while (*cursor < end && **cursor >= '0' && **cursor <= '9') {
            denom *= 10;
            fractional_part *= 10;
            fractional_part += (**cursor - '0');
            (*cursor)++;
        }
    }
    double d = integer_part + double(fractional_part) / denom;
    if (negative) {
        d = -d;
    }
    if (consume(cursor, end, "h")) {
        return make_const(Float(16), d);
    } else if (consume(cursor, end, "f")) {
        return make_const(Float(32), d);
    } else {
        return make_const(Float(64), d);
    }
}

Expr reparse_as_bool(const Expr &e) {
    const Call *op = e.as<Call>();
    if (e.type().is_bool()) {
        return e;
    } else if (const Variable *var = e.as<Variable>()) {
        return Variable::make(Bool(), var->name);
    } else if (op &&
               (op->is_intrinsic(Call::likely) ||
                op->is_intrinsic(Call::likely_if_innermost))) {
        return Call::make(Bool(), op->name, {reparse_as_bool(op->args[0])}, op->call_type);
    } else if (is_zero(e)) {
        return const_false();
    } else if (is_one(e)) {
        return const_true();
    } else {
        std::cerr << "Expected bool Expr: " << e << "\n";
        abort();
        return Expr();
    }
}

Expr parse_halide_expr(char **cursor, char *end, int precedence,
                       std::vector<std::pair<Expr, int>> &stack) {

    if (!stack.empty() && stack.back().second <= precedence) {
        Expr a = stack.back().first;
        stack.pop_back();
        return a;
    }

    struct TypePattern {
        const char *cast_prefix = nullptr;
        const char *constant_prefix = nullptr;
        Type type;
        string cast_prefix_storage, constant_prefix_storage;
        TypePattern(Type t) {
            ostringstream cast_prefix_stream, constant_prefix_stream;
            cast_prefix_stream << t << '(';
            cast_prefix_storage = cast_prefix_stream.str();
            cast_prefix = cast_prefix_storage.c_str();

            constant_prefix_stream << '(' << t << ')';
            constant_prefix_storage = constant_prefix_stream.str();
            constant_prefix = constant_prefix_storage.c_str();
            type = t;
        }
    };
    static TypePattern typenames[] = {{UInt(1)},
                                      {Int(8)},
                                      {UInt(8)},
                                      {Int(16)},
                                      {UInt(16)},
                                      {Int(32)},
                                      {UInt(32)},
                                      {Int(64)},
                                      {UInt(64)},
                                      {Float(64)},
                                      {Float(32)}};

    consume_whitespace(cursor, end);

    if (precedence == 10) {
        // type-cast
        for (auto t : typenames) {
            if (consume(cursor, end, t.cast_prefix)) {
                Expr a = cast(t.type, parse_halide_expr(cursor, end, 0, stack));
                expect(cursor, end, ")");
                return a;
            }
        }

        // Let binding. Always has parens
        if (consume(cursor, end, "(let ")) {
            string name = consume_token(cursor, end);
            consume_whitespace(cursor, end);
            expect(cursor, end, "=");
            consume_whitespace(cursor, end);

            Expr value = parse_halide_expr(cursor, end, 0, stack);

            consume_whitespace(cursor, end);
            expect(cursor, end, "in");
            consume_whitespace(cursor, end);

            Expr body = parse_halide_expr(cursor, end, 0, stack);

            Expr a = Let::make(name, value, body);
            expect(cursor, end, ")");
            return a;
        }
        if (consume(cursor, end, "min(")) {
            Expr a = parse_halide_expr(cursor, end, 0, stack);
            expect(cursor, end, ",");
            Expr b = parse_halide_expr(cursor, end, 0, stack);
            consume_whitespace(cursor, end);
            expect(cursor, end, ")");
            return min(a, b);
        }
        if (consume(cursor, end, "max(")) {
            Expr a = parse_halide_expr(cursor, end, 0, stack);
            expect(cursor, end, ",");
            Expr b = parse_halide_expr(cursor, end, 0, stack);
            consume_whitespace(cursor, end);
            expect(cursor, end, ")");
            return max(a, b);
        }
        if (consume(cursor, end, "select(")) {
            Expr a = parse_halide_expr(cursor, end, 0, stack);
            a = reparse_as_bool(a);
            expect(cursor, end, ",");
            Expr b = parse_halide_expr(cursor, end, 0, stack);
            expect(cursor, end, ",");
            Expr c = parse_halide_expr(cursor, end, 0, stack);
            consume_whitespace(cursor, end);
            expect(cursor, end, ")");
            if (b.type().is_bool() && !c.type().is_bool()) {
                c = reparse_as_bool(c);
            } else if (!b.type().is_bool() && c.type().is_bool()) {
                b = reparse_as_bool(b);
            }

            return select(a, b, c);
        }
        Call::IntrinsicOp binary_intrinsics[] = {Call::bitwise_and,
                                                 Call::bitwise_or,
                                                 Call::shift_left,
                                                 Call::shift_right};
        for (auto intrin : binary_intrinsics) {
            if (consume(cursor, end, Call::get_intrinsic_name(intrin))) {
                expect(cursor, end, "(");
                Expr a = parse_halide_expr(cursor, end, 0, stack);
                expect(cursor, end, ",");
                Expr b = parse_halide_expr(cursor, end, 0, stack);
                consume_whitespace(cursor, end);
                expect(cursor, end, ")");
                return Call::make(a.type(), intrin, {a, b}, Call::PureIntrinsic);
            }
        }

        if (consume(cursor, end, "fold(")) {
            // strip folds
            Expr e = parse_halide_expr(cursor, end, 0, stack);
            expect(cursor, end, ")");
            return e;
        }

        if (consume(cursor, end, "!")) {
            Expr e = parse_halide_expr(cursor, end, precedence, stack);
            e = reparse_as_bool(e);
            return !e;
        }

        // Parse entire rewrite rules as exprs
        if (consume(cursor, end, "rewrite(")) {
            Expr lhs = parse_halide_expr(cursor, end, 0, stack);
            expect(cursor, end, ",");
            Expr rhs = parse_halide_expr(cursor, end, 0, stack);
            if (lhs.type().is_bool()) {
                rhs = reparse_as_bool(rhs);
            }
            if (rhs.type().is_bool()) {
                lhs = reparse_as_bool(lhs);
            }
            Expr predicate = const_true();
            consume_whitespace(cursor, end);
            if (consume(cursor, end, ",")) {
                predicate = parse_halide_expr(cursor, end, 0, stack);
                predicate = reparse_as_bool(predicate);
            }
            expect(cursor, end, ")");
            return Call::make(Bool(), "rewrite", {lhs, rhs, predicate}, Call::Extern);
        }

        if (consume(cursor, end, "round_f32(")) {
            Expr a = parse_halide_expr(cursor, end, 0, stack);
            expect(cursor, end, ")");
            return round(a);
        }
        if (consume(cursor, end, "ceil_f32(")) {
            Expr a = parse_halide_expr(cursor, end, 0, stack);
            expect(cursor, end, ")");
            return ceil(a);
        }
        if (consume(cursor, end, "floor_f32(")) {
            Expr a = parse_halide_expr(cursor, end, 0, stack);
            expect(cursor, end, ")");
            return floor(a);
        }
        if (consume(cursor, end, "likely(")) {
            Expr a = parse_halide_expr(cursor, end, 0, stack);
            expect(cursor, end, ")");
            return likely(a);
        }
        if (consume(cursor, end, "likely_if_innermost(")) {
            Expr a = parse_halide_expr(cursor, end, 0, stack);
            expect(cursor, end, ")");
            return likely(a);
        }

        Type expected_type = Int(32);
        for (auto t : typenames) {
            // A type annotation for the token that follows
            if (consume(cursor, end, t.constant_prefix)) {
                expected_type = t.type;
            }
        }

        // An expression in parens
        if (consume(cursor, end, "(")) {
            Expr e = parse_halide_expr(cursor, end, 0, stack);
            expect(cursor, end, ")");
            return e;
        }

        // Constants
        if ((**cursor >= '0' && **cursor <= '9') || **cursor == '-') {
            Expr e = make_const(Int(32), consume_int(cursor, end));
            if (**cursor == '.') {
                e += consume_float(cursor, end);
            }
            return e;
        }
        if (consume(cursor, end, "true")) {
            return const_true();
        }
        if (consume(cursor, end, "false")) {
            return const_false();
        }

        // Variables, loads, and calls
        if ((**cursor >= 'a' && **cursor <= 'z') ||
            (**cursor >= 'A' && **cursor <= 'Z') ||
            **cursor == '$' ||
            **cursor == '_' ||
            **cursor == '.') {
            char **tmp = cursor;
            string name = consume_token(tmp, end);
            if (consume(tmp, end, "[")) {
                *cursor = *tmp;
                Expr index = parse_halide_expr(cursor, end, 0, stack);
                expect(cursor, end, "]");
                if (expected_type == Type{}) {
                    expected_type = Int(32);
                }
                return Load::make(expected_type, name, index, Buffer<>(), Parameter(), const_true(), ModulusRemainder());
            } else if (consume(tmp, end, "(")) {
                *cursor = *tmp;
                vector<Expr> args;
                while (1) {
                    consume_whitespace(cursor, end);
                    if (consume(cursor, end, ")")) break;
                    args.push_back(parse_halide_expr(cursor, end, 0, stack));
                    consume_whitespace(cursor, end);
                    consume(cursor, end, ",");
                }
                return Call::make(expected_type, name, args, Call::PureExtern);
            } else {
                if (expected_type == Type{}) {
                    expected_type = Int(32);
                }
                return Variable::make(expected_type, name);
            }
        }

        for (auto p : stack) {
            std::cerr << p.first << " " << p.second << "\n";
        }

        std::cerr << "Failed to parse starting at: " << *cursor << "\n";
        abort();
        return Expr();

    } else if (precedence == 9) {
        // Multiplicative things

        Expr a = parse_halide_expr(cursor, end, precedence + 1, stack);
        Expr result;
        while (1) {
            consume_whitespace(cursor, end);
            if (consume(cursor, end, "*")) {
                a *= parse_halide_expr(cursor, end, precedence + 1, stack);
            } else if (consume(cursor, end, "/")) {
                a /= parse_halide_expr(cursor, end, precedence + 1, stack);
            } else if (consume(cursor, end, "%")) {
                a = a % parse_halide_expr(cursor, end, precedence + 1, stack);
            } else {
                stack.emplace_back(a, precedence + 1);
                break;
            }
        }
    } else if (precedence == 8) {
        // Additive things

        Expr a = parse_halide_expr(cursor, end, precedence + 1, stack);
        Expr result;
        while (1) {
            consume_whitespace(cursor, end);
            if (consume(cursor, end, "+")) {
                a += parse_halide_expr(cursor, end, precedence + 1, stack);
            } else if (consume(cursor, end, "-")) {
                a -= parse_halide_expr(cursor, end, precedence + 1, stack);
            } else {
                stack.emplace_back(a, precedence + 1);
                break;
            }
        }
    } else if (precedence == 7) {
        // Comparisons

        Expr a = parse_halide_expr(cursor, end, precedence + 1, stack);
        Expr result;
        consume_whitespace(cursor, end);
        if (consume(cursor, end, "<=")) {
            return a <= parse_halide_expr(cursor, end, precedence, stack);
        } else if (consume(cursor, end, ">=")) {
            return a >= parse_halide_expr(cursor, end, precedence, stack);
        } else if (consume(cursor, end, "<")) {
            return a < parse_halide_expr(cursor, end, precedence, stack);
        } else if (consume(cursor, end, ">")) {
            return a > parse_halide_expr(cursor, end, precedence, stack);
        } else if (consume(cursor, end, "==")) {
            return a == parse_halide_expr(cursor, end, precedence, stack);
        } else if (consume(cursor, end, "!=")) {
            return a != parse_halide_expr(cursor, end, precedence, stack);
        } else {
            stack.emplace_back(a, precedence + 1);
        }
    } else if (precedence == 6) {
        // Logical and
        Expr a = parse_halide_expr(cursor, end, precedence + 1, stack);
        Expr result;
        if (consume(cursor, end, "&&")) {
            Expr b = parse_halide_expr(cursor, end, precedence, stack);
            a = reparse_as_bool(a);
            b = reparse_as_bool(b);
            return a && b;
        } else {
            stack.emplace_back(a, precedence + 1);
        }
    } else if (precedence == 5) {
        // Logical or
        Expr a = parse_halide_expr(cursor, end, precedence + 1, stack);
        Expr result;
        if (consume(cursor, end, "||")) {
            Expr b = parse_halide_expr(cursor, end, precedence, stack);
            a = reparse_as_bool(a);
            b = reparse_as_bool(b);
            return a || b;
        } else {
            stack.emplace_back(a, 6);
        }
    }

    // Try increasing precedence
    return parse_halide_expr(cursor, end, precedence + 1, stack);
}

Expr parse_halide_expr(char **cursor, char *end, Type expected_type) {
    std::vector<std::pair<Expr, int>> stack;
    Expr result = parse_halide_expr(cursor, end, 0, stack);
    if (expected_type.is_bool()) {
        result = reparse_as_bool(result);
    }
    _halide_user_assert(stack.empty());
    return result;
}

vector<Expr> parse_halide_exprs_from_file(const std::string &filename) {
    vector<Expr> exprs;
    std::ifstream input;
    input.open(filename);
    for (string line; std::getline(input, line);) {
        if (line.empty()) continue;
        // It's possible to comment out lines for debugging
        if (line[0] == '#') continue;  // for python-style comments
        if (line[0] == '/') continue;  // for //
        if (line[0] == '*') continue;  // for */

        // There are some extraneous newlines in some of the files. Balance parentheses...
        size_t open, close;
        while (1) {
            open = std::count(line.begin(), line.end(), '(');
            close = std::count(line.begin(), line.end(), ')');
            if (open <= close) break;
            string next;
            debug(0) << "Unbalanced parens in :\n\n"
                     << line << "\n\n";
            assert(std::getline(input, next));
            line += next;
        }
        char *start = &line[0];
        char *end = &line[line.size()];
        debug(1) << "Parsing: " << line << "\n";
        exprs.push_back(parse_halide_expr(&start, end, Type{}));
    }

    return exprs;
}
