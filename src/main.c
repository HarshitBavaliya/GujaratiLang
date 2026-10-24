#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#endif

typedef enum {
    TOKEN_EOF,
    TOKEN_START,
    TOKEN_END,
    TOKEN_PRINT,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_ELSE_IF,
    TOKEN_NULL,
    TOKEN_ERROR,
    TOKEN_FATAL_ERROR,
    TOKEN_WARNING,
    TOKEN_NUMBER,
    TOKEN_STRING,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_EQUAL_EQUAL,
    TOKEN_BANG_EQUAL,
    TOKEN_LESS,
    TOKEN_LESS_EQUAL,
    TOKEN_GREATER,
    TOKEN_GREATER_EQUAL,
    TOKEN_LEFT_PAREN,
    TOKEN_RIGHT_PAREN,
    TOKEN_LEFT_BRACE,
    TOKEN_RIGHT_BRACE,
    TOKEN_SEMICOLON,
    TOKEN_INVALID
} TokenKind;

typedef struct {
    TokenKind kind;
    double number;
    size_t string_offset;
    size_t string_length;
    size_t line;
    size_t column;
} Token;

typedef enum {
    VALUE_NUMBER,
    VALUE_NULL,
    VALUE_STRING
} ValueKind;

typedef enum {
    LANGUAGE_ENGLISH,
    LANGUAGE_GUJARATI
} Language;

typedef enum {
    MESSAGE_UNSUPPORTED_STRING_ESCAPE,
    MESSAGE_UNTERMINATED_STRING,
    MESSAGE_INVALID_NUMBER,
    MESSAGE_UNEXPECTED_CHARACTER,
    MESSAGE_EXPECTED_RIGHT_PAREN,
    MESSAGE_EXPECTED_VALUE,
    MESSAGE_UNARY_NUMBER_REQUIRED,
    MESSAGE_ARITHMETIC_NUMBERS_REQUIRED,
    MESSAGE_DIVISION_BY_ZERO,
    MESSAGE_EXPECTED_BLOCK_OPEN,
    MESSAGE_EXPECTED_BLOCK_CLOSE,
    MESSAGE_EXPECTED_IF_OPEN,
    MESSAGE_EXPECTED_CONDITION_CLOSE,
    MESSAGE_CONDITION_TYPE,
    MESSAGE_EXPECTED_QUOTED_MESSAGE,
    MESSAGE_EXPECTED_DIAGNOSTIC_SEMICOLON,
    MESSAGE_WRITE_DIAGNOSTIC,
    MESSAGE_EXPECTED_STATEMENT,
    MESSAGE_EXPECTED_EXPRESSION_SEMICOLON,
    MESSAGE_WRITE_OUTPUT,
    MESSAGE_COMPARISON_NUMBERS_REQUIRED,
    MESSAGE_EXPECTED_PROGRAM_START,
    MESSAGE_EXPECTED_PROGRAM_END,
    MESSAGE_EXPECTED_END_OF_FILE,
    MESSAGE_COULD_NOT_OPEN_FILE,
    MESSAGE_COULD_NOT_READ_FILE,
    MESSAGE_OUT_OF_MEMORY,
    MESSAGE_FILE_CONTAINS_NUL,
    MESSAGE_SET_CONSOLE_ENCODING,
    MESSAGE_USAGE
} MessageId;

typedef struct {
    ValueKind kind;
    double number;
    size_t string_offset;
    size_t string_length;
} Value;

typedef struct {
    const char *source;
    size_t offset;
    size_t line;
    size_t column;
    const char *filename;
    Language language;
    Token current;
    int failed;
} Parser;

static const char *localized_message(Language language, MessageId message)
{
    static const char *const english_messages[] = {
        "unsupported string escape",
        "unterminated string",
        "invalid or out-of-range number",
        "unexpected character",
        "expected ')'",
        "expected a number, string, 'નકામો', or '('",
        "unary arithmetic requires a number",
        "arithmetic requires numbers",
        "division by zero",
        "expected '{' before block",
        "expected '}' after block",
        "expected '(' after 'જો'",
        "expected ')' after condition",
        "condition must be a number or 'નકામો'",
        "expected a quoted message",
        "expected ';' after diagnostic",
        "could not write diagnostic",
        "expected 'છાપો', 'જો', or a diagnostic statement",
        "expected ';' after expression",
        "could not write output",
        "comparisons require numbers",
        "expected 'આવો' at the start of the program",
        "expected 'આવજો' at the end of the program",
        "expected end of file after 'આવજો'",
        "could not open file",
        "could not read file",
        "out of memory while reading file",
        "file contains a NUL byte",
        "could not set console output to UTF-8",
        "usage: %s [--language en|gu] <source.gj>"
    };
    static const char *const gujarati_messages[] = {
        "સ્ટ્રિંગમાં આ એસ્કેપ માન્ય નથી",
        "સ્ટ્રિંગ બંધ કરેલી નથી",
        "અમાન્ય અથવા મર્યાદાથી બહારની સંખ્યા",
        "અનપેક્ષિત અક્ષર",
        "અપેક્ષિત ')'",
        "અપેક્ષિત સંખ્યા, સ્ટ્રિંગ, 'નકામો', અથવા '('",
        "યુનરી ગણિત માટે સંખ્યા જરૂરી છે",
        "ગણિત માટે સંખ્યાઓ જરૂરી છે",
        "શૂન્ય વડે ભાગી શકાતો નથી",
        "બ્લોક પહેલાં '{' અપેક્ષિત છે",
        "બ્લોક પછી '}' અપેક્ષિત છે",
        "'જો' પછી '(' અપેક્ષિત છે",
        "શરત પછી ')' અપેક્ષિત છે",
        "શરત સંખ્યા અથવા 'નકામો' હોવી જોઈએ",
        "અવતરણ ચિહ્નોમાં સંદેશ અપેક્ષિત છે",
        "ડાયગ્નોસ્ટિક પછી ';' અપેક્ષિત છે",
        "ડાયગ્નોસ્ટિક લખી શકાયું નહીં",
        "'છાપો', 'જો', અથવા ડાયગ્નોસ્ટિક સ્ટેટમેન્ટ અપેક્ષિત છે",
        "અભિવ્યક્તિ પછી ';' અપેક્ષિત છે",
        "આઉટપુટ લખી શકાયું નહીં",
        "તુલના માટે સંખ્યાઓ જરૂરી છે",
        "પ્રોગ્રામની શરૂઆતમાં 'આવો' અપેક્ષિત છે",
        "પ્રોગ્રામના અંતે 'આવજો' અપેક્ષિત છે",
        "'આવજો' પછી ફાઇલનો અંત અપેક્ષિત છે",
        "ફાઇલ ખોલી શકાયી નહીં",
        "ફાઇલ વાંચી શકાયી નહીં",
        "ફાઇલ વાંચતી વખતે પૂરતી મેમરી મળી નહીં",
        "ફાઇલમાં NUL બાઇટ છે",
        "કોન્સોલનું આઉટપુટ UTF-8 પર સેટ કરી શકાયું નહીં",
        "ઉપયોગ: %s [--language en|gu] <source.gj>"
    };

    if (language == LANGUAGE_GUJARATI) {
        return gujarati_messages[message];
    }
    return english_messages[message];
}

static void report_error(Parser *parser, size_t line, size_t column,
                         MessageId message)
{
    if (!parser->failed) {
        const char *label = parser->language == LANGUAGE_GUJARATI ?
                            "ભૂલ" : "error";
        fprintf(stderr, "%s:%zu:%zu: %s: %s\n",
                parser->filename, line, column, label,
                localized_message(parser->language, message));
    }
    parser->failed = 1;
}

static void report_runtime_error(Parser *parser, Token token,
                                 MessageId message, int execute)
{
    if (execute) {
        report_error(parser, token.line, token.column, message);
    }
}

static char peek(const Parser *parser)
{
    return parser->source[parser->offset];
}

static char peek_next(const Parser *parser)
{
    if (peek(parser) == '\0') {
        return '\0';
    }
    return parser->source[parser->offset + 1];
}

static char advance_char(Parser *parser)
{
    char character = parser->source[parser->offset];
    if (character != '\0') {
        parser->offset++;
        if (character == '\n') {
            parser->line++;
            parser->column = 1;
        } else if (((unsigned char)character & 0xC0) != 0x80) {
            parser->column++;
        }
    }
    return character;
}

static void skip_whitespace_and_comments(Parser *parser)
{
    for (;;) {
        char character = peek(parser);
        if (character == ' ' || character == '\t' ||
            character == '\r' || character == '\n') {
            advance_char(parser);
        } else if (character == '/' && peek_next(parser) == '/') {
            while (peek(parser) != '\0' && peek(parser) != '\n') {
                advance_char(parser);
            }
        } else {
            return;
        }
    }
}

static Token make_token(TokenKind kind, size_t line, size_t column)
{
    Token token;
    token.kind = kind;
    token.number = 0.0;
    token.string_offset = 0;
    token.string_length = 0;
    token.line = line;
    token.column = column;
    return token;
}

static Token scan_token(Parser *parser)
{
    static const char start_keyword[] = "આવો";
    static const char end_keyword[] = "આવજો";
    static const char print_keyword[] = "છાપો";
    static const char if_keyword[] = "જો";
    static const char else_if_keyword[] = "અથવા જો";
    static const char else_keyword[] = "અથવા";
    static const char null_keyword[] = "નકામો";
    static const char fatal_error_keyword[] = "ઘાતક ભૂલ";
    static const char error_keyword[] = "ભૂલ";
    static const char warning_keyword[] = "ચેતવણી";
    Token token;
    size_t start;
    char character;

    skip_whitespace_and_comments(parser);
    token = make_token(TOKEN_EOF, parser->line, parser->column);
    character = peek(parser);
    if (character == '\0') {
        return token;
    }

    if (strncmp(parser->source + parser->offset, else_if_keyword,
                sizeof(else_if_keyword) - 1) == 0) {
        size_t index;
        for (index = 0; index < sizeof(else_if_keyword) - 1; index++) {
            advance_char(parser);
        }
        token.kind = TOKEN_ELSE_IF;
        return token;
    }
    if (strncmp(parser->source + parser->offset, fatal_error_keyword,
                sizeof(fatal_error_keyword) - 1) == 0) {
        size_t index;
        for (index = 0; index < sizeof(fatal_error_keyword) - 1; index++) {
            advance_char(parser);
        }
        token.kind = TOKEN_FATAL_ERROR;
        return token;
    }
    if (strncmp(parser->source + parser->offset, start_keyword,
                sizeof(start_keyword) - 1) == 0) {
        size_t index;
        for (index = 0; index < sizeof(start_keyword) - 1; index++) {
            advance_char(parser);
        }
        token.kind = TOKEN_START;
        return token;
    }
    if (strncmp(parser->source + parser->offset, end_keyword,
                sizeof(end_keyword) - 1) == 0) {
        size_t index;
        for (index = 0; index < sizeof(end_keyword) - 1; index++) {
            advance_char(parser);
        }
        token.kind = TOKEN_END;
        return token;
    }
    if (strncmp(parser->source + parser->offset, print_keyword,
                sizeof(print_keyword) - 1) == 0) {
        size_t index;
        for (index = 0; index < sizeof(print_keyword) - 1; index++) {
            advance_char(parser);
        }
        token.kind = TOKEN_PRINT;
        return token;
    }
    if (strncmp(parser->source + parser->offset, if_keyword,
                sizeof(if_keyword) - 1) == 0) {
        size_t index;
        for (index = 0; index < sizeof(if_keyword) - 1; index++) {
            advance_char(parser);
        }
        token.kind = TOKEN_IF;
        return token;
    }
    if (strncmp(parser->source + parser->offset, else_keyword,
                sizeof(else_keyword) - 1) == 0) {
        size_t index;
        for (index = 0; index < sizeof(else_keyword) - 1; index++) {
            advance_char(parser);
        }
        token.kind = TOKEN_ELSE;
        return token;
    }
    if (strncmp(parser->source + parser->offset, null_keyword,
                sizeof(null_keyword) - 1) == 0) {
        size_t index;
        for (index = 0; index < sizeof(null_keyword) - 1; index++) {
            advance_char(parser);
        }
        token.kind = TOKEN_NULL;
        return token;
    }
    if (strncmp(parser->source + parser->offset, error_keyword,
                sizeof(error_keyword) - 1) == 0) {
        size_t index;
        for (index = 0; index < sizeof(error_keyword) - 1; index++) {
            advance_char(parser);
        }
        token.kind = TOKEN_ERROR;
        return token;
    }
    if (strncmp(parser->source + parser->offset, warning_keyword,
                sizeof(warning_keyword) - 1) == 0) {
        size_t index;
        for (index = 0; index < sizeof(warning_keyword) - 1; index++) {
            advance_char(parser);
        }
        token.kind = TOKEN_WARNING;
        return token;
    }
    if (character == '"') {
        size_t string_start;
        advance_char(parser);
        string_start = parser->offset;
        while (peek(parser) != '\0' && peek(parser) != '"') {
            if (peek(parser) == '\\') {
                advance_char(parser);
                if (peek(parser) == '\0') {
                    break;
                }
                if (peek(parser) != '"' && peek(parser) != '\\' &&
                    peek(parser) != 'n' && peek(parser) != 'r' &&
                    peek(parser) != 't') {
                    report_error(parser, parser->line, parser->column,
                                 MESSAGE_UNSUPPORTED_STRING_ESCAPE);
                    token.kind = TOKEN_INVALID;
                    return token;
                }
            }
            advance_char(parser);
        }
        if (peek(parser) != '"') {
            report_error(parser, token.line, token.column,
                         MESSAGE_UNTERMINATED_STRING);
            token.kind = TOKEN_INVALID;
            return token;
        }
        token.kind = TOKEN_STRING;
        token.string_offset = string_start;
        token.string_length = parser->offset - string_start;
        advance_char(parser);
        return token;
    }

    if ((character >= '0' && character <= '9') ||
        (character == '.' && peek_next(parser) >= '0' &&
         peek_next(parser) <= '9')) {
        char *end;
        start = parser->offset;
        errno = 0;
        token.number = strtod(parser->source + start, &end);
        if (end == parser->source + start || errno == ERANGE) {
            report_error(parser, token.line, token.column,
                         MESSAGE_INVALID_NUMBER);
            token.kind = TOKEN_INVALID;
            return token;
        }
        while (parser->source + parser->offset < end) {
            advance_char(parser);
        }
        token.kind = TOKEN_NUMBER;
        return token;
    }

    advance_char(parser);
    switch (character) {
    case '+': token.kind = TOKEN_PLUS; break;
    case '-': token.kind = TOKEN_MINUS; break;
    case '*': token.kind = TOKEN_STAR; break;
    case '/': token.kind = TOKEN_SLASH; break;
    case '=':
        if (peek(parser) == '=') {
            advance_char(parser);
            token.kind = TOKEN_EQUAL_EQUAL;
        } else {
            report_error(parser, token.line, token.column,
                         MESSAGE_UNEXPECTED_CHARACTER);
            token.kind = TOKEN_INVALID;
        }
        break;
    case '!':
        if (peek(parser) == '=') {
            advance_char(parser);
            token.kind = TOKEN_BANG_EQUAL;
        } else {
            report_error(parser, token.line, token.column,
                         MESSAGE_UNEXPECTED_CHARACTER);
            token.kind = TOKEN_INVALID;
        }
        break;
    case '<':
        if (peek(parser) == '=') {
            advance_char(parser);
            token.kind = TOKEN_LESS_EQUAL;
        } else {
            token.kind = TOKEN_LESS;
        }
        break;
    case '>':
        if (peek(parser) == '=') {
            advance_char(parser);
            token.kind = TOKEN_GREATER_EQUAL;
        } else {
            token.kind = TOKEN_GREATER;
        }
        break;
    case '(': token.kind = TOKEN_LEFT_PAREN; break;
    case ')': token.kind = TOKEN_RIGHT_PAREN; break;
    case '{': token.kind = TOKEN_LEFT_BRACE; break;
    case '}': token.kind = TOKEN_RIGHT_BRACE; break;
    case ';': token.kind = TOKEN_SEMICOLON; break;
    default:
        report_error(parser, token.line, token.column,
                     MESSAGE_UNEXPECTED_CHARACTER);
        token.kind = TOKEN_INVALID;
        break;
    }
    return token;
}

static void advance_token(Parser *parser)
{
    if (!parser->failed) {
        parser->current = scan_token(parser);
    }
}

static Value number_value(double number)
{
    Value value;
    value.kind = VALUE_NUMBER;
    value.number = number;
    value.string_offset = 0;
    value.string_length = 0;
    return value;
}

static Value parse_expression(Parser *parser, int execute);
static Value parse_additive(Parser *parser, int execute);

static Value parse_primary(Parser *parser, int execute)
{
    Token token = parser->current;
    Value value;

    if (token.kind == TOKEN_NUMBER) {
        value = number_value(token.number);
        advance_token(parser);
        return value;
    }
    if (token.kind == TOKEN_NULL) {
        value = number_value(0.0);
        value.kind = VALUE_NULL;
        advance_token(parser);
        return value;
    }
    if (token.kind == TOKEN_STRING) {
        value = number_value(0.0);
        value.kind = VALUE_STRING;
        value.string_offset = token.string_offset;
        value.string_length = token.string_length;
        advance_token(parser);
        return value;
    }
    if (token.kind == TOKEN_LEFT_PAREN) {
        advance_token(parser);
        value = parse_expression(parser, execute);
        if (!parser->failed && parser->current.kind != TOKEN_RIGHT_PAREN) {
            report_error(parser, parser->current.line, parser->current.column,
                         MESSAGE_EXPECTED_RIGHT_PAREN);
            return number_value(0.0);
        }
        if (!parser->failed) {
            advance_token(parser);
        }
        return value;
    }

    report_error(parser, token.line, token.column,
                 MESSAGE_EXPECTED_VALUE);
    return number_value(0.0);
}

static Value parse_unary(Parser *parser, int execute)
{
    Token operation = parser->current;
    Value value;
    if (operation.kind == TOKEN_MINUS || operation.kind == TOKEN_PLUS) {
        advance_token(parser);
        value = parse_unary(parser, execute);
        if (!parser->failed && value.kind != VALUE_NUMBER) {
            report_runtime_error(parser, operation,
                                 MESSAGE_UNARY_NUMBER_REQUIRED, execute);
            return number_value(0.0);
        }
        if (operation.kind == TOKEN_MINUS) {
            value.number = -value.number;
        }
        return value;
    }
    return parse_primary(parser, execute);
}

static Value parse_term(Parser *parser, int execute)
{
    Value value = parse_unary(parser, execute);

    while (!parser->failed &&
           (parser->current.kind == TOKEN_STAR ||
            parser->current.kind == TOKEN_SLASH)) {
        Token operation = parser->current;
        Value right;
        advance_token(parser);
        right = parse_unary(parser, execute);
        if (parser->failed) {
            return number_value(0.0);
        }
        if (value.kind != VALUE_NUMBER || right.kind != VALUE_NUMBER) {
            report_runtime_error(parser, operation,
                                 MESSAGE_ARITHMETIC_NUMBERS_REQUIRED, execute);
            value = number_value(0.0);
        } else if (operation.kind == TOKEN_STAR) {
            value.number *= right.number;
        } else if (right.number == 0.0) {
            report_runtime_error(parser, operation, MESSAGE_DIVISION_BY_ZERO,
                                 execute);
            value = number_value(0.0);
        } else {
            value.number /= right.number;
        }
    }
    return value;
}

static Value parse_additive(Parser *parser, int execute)
{
    Value value = parse_term(parser, execute);

    while (!parser->failed &&
           (parser->current.kind == TOKEN_PLUS ||
            parser->current.kind == TOKEN_MINUS)) {
        Token operation = parser->current;
        Value right;
        advance_token(parser);
        right = parse_term(parser, execute);
        if (parser->failed) {
            return number_value(0.0);
        }
        if (value.kind != VALUE_NUMBER || right.kind != VALUE_NUMBER) {
            report_runtime_error(parser, operation,
                                 MESSAGE_ARITHMETIC_NUMBERS_REQUIRED, execute);
            value = number_value(0.0);
        } else if (operation.kind == TOKEN_PLUS) {
            value.number += right.number;
        } else {
            value.number -= right.number;
        }
    }
    return value;
}

static Value parse_expression(Parser *parser, int execute)
{
    Value value = parse_additive(parser, execute);

    while (!parser->failed &&
           (parser->current.kind == TOKEN_EQUAL_EQUAL ||
            parser->current.kind == TOKEN_BANG_EQUAL ||
            parser->current.kind == TOKEN_LESS ||
            parser->current.kind == TOKEN_LESS_EQUAL ||
            parser->current.kind == TOKEN_GREATER ||
            parser->current.kind == TOKEN_GREATER_EQUAL)) {
        Token operation = parser->current;
        Value right;
        int comparison;

        advance_token(parser);
        right = parse_additive(parser, execute);
        if (parser->failed) {
            return number_value(0.0);
        }
        if (value.kind != VALUE_NUMBER || right.kind != VALUE_NUMBER) {
            report_runtime_error(parser, operation,
                                 MESSAGE_COMPARISON_NUMBERS_REQUIRED, execute);
            value = number_value(0.0);
            continue;
        }

        switch (operation.kind) {
        case TOKEN_EQUAL_EQUAL:
            comparison = value.number == right.number;
            break;
        case TOKEN_BANG_EQUAL:
            comparison = value.number != right.number;
            break;
        case TOKEN_LESS:
            comparison = value.number < right.number;
            break;
        case TOKEN_LESS_EQUAL:
            comparison = value.number <= right.number;
            break;
        case TOKEN_GREATER:
            comparison = value.number > right.number;
            break;
        case TOKEN_GREATER_EQUAL:
            comparison = value.number >= right.number;
            break;
        default:
            comparison = 0;
            break;
        }
        value = number_value(comparison ? 1.0 : 0.0);
    }
    return value;
}

static int write_string(Parser *parser, FILE *output,
                        size_t offset, size_t length)
{
    size_t index;
    size_t end = offset + length;
    for (index = offset; index < end; index++) {
        char character = parser->source[index];
        if (character == '\\' && index + 1 < end) {
            index++;
            switch (parser->source[index]) {
            case '"': character = '"'; break;
            case '\\': character = '\\'; break;
            case 'n': character = '\n'; break;
            case 'r': character = '\r'; break;
            case 't': character = '\t'; break;
            default: return 0;
            }
        }
        if (fputc((unsigned char)character, output) == EOF) {
            return 0;
        }
    }
    return 1;
}

static int write_value(Parser *parser, Value value)
{
    if (value.kind == VALUE_STRING) {
        return write_string(parser, stdout, value.string_offset,
                            value.string_length);
    }
    if (value.kind == VALUE_NULL) {
        return fputs("નકામો", stdout) >= 0;
    }
    return printf("%.15g", value.number) >= 0;
}

static int value_is_truthy(Value value)
{
    if (value.kind == VALUE_NULL) {
        return 0;
    }
    if (value.kind == VALUE_NUMBER) {
        return value.number != 0.0;
    }
    return 0;
}

static int parse_statement(Parser *parser, int execute);

static int parse_block(Parser *parser, int execute)
{
    if (parser->current.kind != TOKEN_LEFT_BRACE) {
        report_error(parser, parser->current.line, parser->current.column,
                     MESSAGE_EXPECTED_BLOCK_OPEN);
        return 0;
    }
    advance_token(parser);
    while (!parser->failed && parser->current.kind != TOKEN_RIGHT_BRACE &&
           parser->current.kind != TOKEN_EOF &&
           parser->current.kind != TOKEN_END) {
        parse_statement(parser, execute);
    }
    if (!parser->failed && parser->current.kind != TOKEN_RIGHT_BRACE) {
        report_error(parser, parser->current.line, parser->current.column,
                     MESSAGE_EXPECTED_BLOCK_CLOSE);
        return 0;
    }
    if (!parser->failed) {
        advance_token(parser);
    }
    return !parser->failed;
}

static int parse_if_condition(Parser *parser, int execute, Token keyword)
{
    Value condition;
    int branch_taken;
    int branch_execute;

    if (parser->current.kind != TOKEN_LEFT_PAREN) {
        report_error(parser, parser->current.line, parser->current.column,
                     MESSAGE_EXPECTED_IF_OPEN);
        return 0;
    }
    advance_token(parser);
    condition = parse_expression(parser, execute);
    if (parser->failed) {
        return 0;
    }
    if (parser->current.kind != TOKEN_RIGHT_PAREN) {
        report_error(parser, parser->current.line, parser->current.column,
                     MESSAGE_EXPECTED_CONDITION_CLOSE);
        return 0;
    }
    if (condition.kind == VALUE_STRING) {
        report_runtime_error(parser, keyword,
                             MESSAGE_CONDITION_TYPE, execute);
    }
    branch_taken = value_is_truthy(condition);
    advance_token(parser);
    branch_execute = execute && branch_taken;
    if (!parse_block(parser, branch_execute)) {
        return 0;
    }

    if (parser->current.kind == TOKEN_ELSE_IF ||
        parser->current.kind == TOKEN_ELSE) {
        Token otherwise = parser->current;
        advance_token(parser);
        if (parser->current.kind == TOKEN_IF) {
            Token else_if = parser->current;
            advance_token(parser);
            return parse_if_condition(parser, execute && !branch_taken,
                                      else_if);
        }
        if (otherwise.kind == TOKEN_ELSE_IF) {
            return parse_if_condition(parser, execute && !branch_taken,
                                      otherwise);
        }
        return parse_block(parser, execute && !branch_taken);
    }
    return !parser->failed;
}

static int parse_diagnostic(Parser *parser, Token keyword, int execute)
{
    Token message;
    const char *label = keyword.kind == TOKEN_WARNING ? "warning" :
                        keyword.kind == TOKEN_FATAL_ERROR ? "fatal error" :
                        "error";
    if (parser->language == LANGUAGE_GUJARATI) {
        label = keyword.kind == TOKEN_WARNING ? "ચેતવણી" :
                keyword.kind == TOKEN_FATAL_ERROR ? "ઘાતક ભૂલ" : "ભૂલ";
    }
    advance_token(parser);
    if (parser->current.kind != TOKEN_STRING) {
        report_error(parser, parser->current.line, parser->current.column,
                     MESSAGE_EXPECTED_QUOTED_MESSAGE);
        return 0;
    }
    message = parser->current;
    advance_token(parser);
    if (parser->current.kind != TOKEN_SEMICOLON) {
        report_error(parser, parser->current.line, parser->current.column,
                     MESSAGE_EXPECTED_DIAGNOSTIC_SEMICOLON);
        return 0;
    }
    advance_token(parser);
    if (!execute || parser->failed) {
        return !parser->failed;
    }
    if (fprintf(stderr, "%s:%zu:%zu: %s: ", parser->filename,
                keyword.line, keyword.column, label) < 0 ||
        !write_string(parser, stderr, message.string_offset,
                      message.string_length) ||
        fputc('\n', stderr) == EOF) {
        report_error(parser, keyword.line, keyword.column,
                     MESSAGE_WRITE_DIAGNOSTIC);
        return 0;
    }
    if (keyword.kind != TOKEN_WARNING) {
        parser->failed = 1;
        return 0;
    }
    return 1;
}

static int parse_statement(Parser *parser, int execute)
{
    Token statement = parser->current;
    Value value;

    if (statement.kind == TOKEN_IF) {
        advance_token(parser);
        return parse_if_condition(parser, execute, statement);
    }
    if (statement.kind == TOKEN_ERROR ||
        statement.kind == TOKEN_FATAL_ERROR ||
        statement.kind == TOKEN_WARNING) {
        return parse_diagnostic(parser, statement, execute);
    }
    if (statement.kind != TOKEN_PRINT) {
        report_error(parser, statement.line, statement.column,
                     MESSAGE_EXPECTED_STATEMENT);
        return 0;
    }
    advance_token(parser);
    value = parse_expression(parser, execute);
    if (parser->failed) {
        return 0;
    }
    if (parser->current.kind != TOKEN_SEMICOLON) {
        report_error(parser, parser->current.line, parser->current.column,
                     MESSAGE_EXPECTED_EXPRESSION_SEMICOLON);
        return 0;
    }
    if (execute && (!write_value(parser, value) || fputc('\n', stdout) == EOF)) {
        report_error(parser, statement.line, statement.column,
                     MESSAGE_WRITE_OUTPUT);
        return 0;
    }
    advance_token(parser);
    return !parser->failed;
}

static int interpret(const char *source, const char *filename, Language language)
{
    Parser parser;

    parser.source = source;
    parser.offset = 0;
    parser.line = 1;
    parser.column = 1;
    parser.filename = filename;
    parser.language = language;
    parser.failed = 0;
    parser.current = make_token(TOKEN_EOF, 1, 1);
    advance_token(&parser);

    if (!parser.failed && parser.current.kind != TOKEN_START) {
        report_error(&parser, parser.current.line, parser.current.column,
                     MESSAGE_EXPECTED_PROGRAM_START);
    }
    if (!parser.failed) {
        advance_token(&parser);
    }

    while (!parser.failed && parser.current.kind != TOKEN_END &&
           parser.current.kind != TOKEN_EOF) {
        parse_statement(&parser, 1);
    }

    if (!parser.failed && parser.current.kind == TOKEN_EOF) {
        report_error(&parser, parser.current.line, parser.current.column,
                     MESSAGE_EXPECTED_PROGRAM_END);
    }
    if (!parser.failed) {
        advance_token(&parser);
        if (!parser.failed && parser.current.kind != TOKEN_EOF) {
            report_error(&parser, parser.current.line, parser.current.column,
                         MESSAGE_EXPECTED_END_OF_FILE);
        }
    }
    return parser.failed ? EXIT_FAILURE : EXIT_SUCCESS;
}

static char *read_source_file(const char *filename, Language language)
{
    FILE *file = fopen(filename, "rb");
    long file_size;
    char *source;
    size_t bytes_read;

    if (file == NULL) {
        fprintf(stderr, "%s: %s\n", filename,
                localized_message(language, MESSAGE_COULD_NOT_OPEN_FILE));
        return NULL;
    }
    if (fseek(file, 0, SEEK_END) != 0 ||
        (file_size = ftell(file)) < 0 ||
        fseek(file, 0, SEEK_SET) != 0) {
        fprintf(stderr, "%s: %s\n", filename,
                localized_message(language, MESSAGE_COULD_NOT_READ_FILE));
        fclose(file);
        return NULL;
    }

    source = (char *)malloc((size_t)file_size + 1);
    if (source == NULL) {
        fprintf(stderr, "%s: %s\n", filename,
                localized_message(language, MESSAGE_OUT_OF_MEMORY));
        fclose(file);
        return NULL;
    }
    bytes_read = fread(source, 1, (size_t)file_size, file);
    if (bytes_read != (size_t)file_size || ferror(file)) {
        fprintf(stderr, "%s: %s\n", filename,
                localized_message(language, MESSAGE_COULD_NOT_READ_FILE));
        free(source);
        fclose(file);
        return NULL;
    }
    if (memchr(source, '\0', bytes_read) != NULL) {
        fprintf(stderr, "%s: %s\n", filename,
                localized_message(language, MESSAGE_FILE_CONTAINS_NUL));
        free(source);
        fclose(file);
        return NULL;
    }
    source[bytes_read] = '\0';
    fclose(file);
    return source;
}

int main(int argc, char **argv)
{
    char *source;
    const char *filename;
    Language language = LANGUAGE_ENGLISH;
    int result;

    if (argc == 2) {
        filename = argv[1];
    } else if (argc == 4 && strcmp(argv[1], "--language") == 0) {
        if (strcmp(argv[2], "en") == 0) {
            language = LANGUAGE_ENGLISH;
        } else if (strcmp(argv[2], "gu") == 0) {
            language = LANGUAGE_GUJARATI;
        } else {
            fprintf(stderr, localized_message(LANGUAGE_ENGLISH, MESSAGE_USAGE),
                    argv[0]);
            return EXIT_FAILURE;
        }
        filename = argv[3];
    } else {
        fprintf(stderr, localized_message(LANGUAGE_ENGLISH, MESSAGE_USAGE),
                argv[0]);
        return EXIT_FAILURE;
    }

#ifdef _WIN32
    {
        DWORD console_mode;
        HANDLE stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);
        if (stdout_handle != INVALID_HANDLE_VALUE &&
            GetConsoleMode(stdout_handle, &console_mode) &&
            !SetConsoleOutputCP(CP_UTF8)) {
            fprintf(stderr, "%s\n",
                    localized_message(language, MESSAGE_SET_CONSOLE_ENCODING));
            return EXIT_FAILURE;
        }
    }
#endif

    source = read_source_file(filename, language);
    if (source == NULL) {
        return EXIT_FAILURE;
    }
    result = interpret(source, filename, language);
    free(source);
    return result;
}
