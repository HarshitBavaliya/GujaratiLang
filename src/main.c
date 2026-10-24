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
    TOKEN_WHILE,
    TOKEN_ELSE,
    TOKEN_ELSE_IF,
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_NOT,
    TOKEN_NULL,
    TOKEN_ERROR,
    TOKEN_FATAL_ERROR,
    TOKEN_WARNING,
    TOKEN_FUNCTION,
    TOKEN_RETURN,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_STRING,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_EQUAL,
    TOKEN_EQUAL_EQUAL,
    TOKEN_BANG_EQUAL,
    TOKEN_LESS,
    TOKEN_LESS_EQUAL,
    TOKEN_GREATER,
    TOKEN_GREATER_EQUAL,
    TOKEN_LEFT_PAREN,
    TOKEN_RIGHT_PAREN,
    TOKEN_COMMA,
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
    size_t source_offset;
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
    MESSAGE_EXPECTED_WHILE_OPEN,
    MESSAGE_EXPECTED_CONDITION_CLOSE,
    MESSAGE_CONDITION_TYPE,
    MESSAGE_EXPECTED_QUOTED_MESSAGE,
    MESSAGE_EXPECTED_DIAGNOSTIC_SEMICOLON,
    MESSAGE_WRITE_DIAGNOSTIC,
    MESSAGE_EXPECTED_STATEMENT,
    MESSAGE_EXPECTED_EXPRESSION_SEMICOLON,
    MESSAGE_WRITE_OUTPUT,
    MESSAGE_COMPARISON_NUMBERS_REQUIRED,
    MESSAGE_EXPECTED_ASSIGNMENT,
    MESSAGE_UNDEFINED_VARIABLE,
    MESSAGE_OUT_OF_MEMORY_FOR_VARIABLE,
    MESSAGE_LOGICAL_OPERANDS_REQUIRED,
    MESSAGE_EXPECTED_FUNCTION_NAME,
    MESSAGE_EXPECTED_FUNCTION_OPEN,
    MESSAGE_EXPECTED_PARAMETER,
    MESSAGE_EXPECTED_FUNCTION_CLOSE,
    MESSAGE_EXPECTED_FUNCTION_BODY,
    MESSAGE_DUPLICATE_FUNCTION,
    MESSAGE_UNDEFINED_FUNCTION,
    MESSAGE_WRONG_ARGUMENT_COUNT,
    MESSAGE_DUPLICATE_PARAMETER,
    MESSAGE_RETURN_OUTSIDE_FUNCTION,
    MESSAGE_OUT_OF_MEMORY_FOR_FUNCTION,
    MESSAGE_OUT_OF_MEMORY_FOR_ARGUMENTS,
    MESSAGE_EXPECTED_INPUT_PROMPT,
    MESSAGE_COULD_NOT_READ_INPUT,
    MESSAGE_OUT_OF_MEMORY_FOR_INPUT,
    MESSAGE_RESERVED_FUNCTION_NAME,
    MESSAGE_EXPECTED_SINGLE_COMMAND,
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
    char *owned_string;
} Value;

typedef struct {
    char **items;
    size_t count;
    size_t capacity;
} StringStorage;

typedef struct {
    size_t name_offset;
    size_t name_length;
    Value value;
} Variable;

typedef struct Environment {
    Variable *variables;
    size_t variable_count;
    size_t variable_capacity;
    struct Environment *parent;
} Environment;

typedef struct {
    size_t name_offset;
    size_t name_length;
    size_t declaration_offset;
    Token *parameters;
    size_t parameter_count;
    Token body_open;
} Function;

typedef struct {
    const char *source;
    size_t offset;
    size_t line;
    size_t column;
    const char *filename;
    Language language;
    Environment *environment;
    Environment *globals;
    Function *functions;
    size_t function_count;
    size_t function_capacity;
    StringStorage *string_storage;
    Token current;
    int failed;
    int in_function;
    int returned;
    Value return_value;
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
        "expected '(' after 'જ્યાં સુધી'",
        "expected ')' after condition",
        "condition must be a number or 'નકામો'",
        "expected a quoted message",
        "expected ';' after diagnostic",
        "could not write diagnostic",
        "expected a variable assignment, function, return, print, conditional, loop, or diagnostic statement",
        "expected ';' after expression",
        "could not write output",
        "comparisons require numbers",
        "expected '=' after variable name",
        "undefined variable",
        "out of memory while storing variable",
        "logical operators require a number or 'નકામો'",
        "expected a function name after 'કાર્ય'",
        "expected '(' after function name",
        "expected a parameter name",
        "expected ')' after function parameters",
        "expected a function body",
        "function is already declared",
        "undefined function",
        "incorrect number of function arguments",
        "parameter is already declared",
        "'પરત' can only be used inside a function",
        "out of memory while storing function",
        "out of memory while storing function arguments",
        "expected a string prompt for 'વાંચો'",
        "could not read a line from standard input",
        "out of memory while storing input",
        "built-in function name cannot be declared",
        "expected one complete statement or expression per REPL line",
        "expected 'આવો' at the start of the program",
        "expected 'આવજો' at the end of the program",
        "expected end of file after 'આવજો'",
        "could not open file",
        "could not read file",
        "out of memory while reading file",
        "file contains a NUL byte",
        "could not set console output to UTF-8",
        "usage: %s [--language en|gu] <source.gj> | [--language en|gu] --repl"
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
        "'જ્યાં સુધી' પછી '(' અપેક્ષિત છે",
        "શરત પછી ')' અપેક્ષિત છે",
        "શરત સંખ્યા અથવા 'નકામો' હોવી જોઈએ",
        "અવતરણ ચિહ્નોમાં સંદેશ અપેક્ષિત છે",
        "ડાયગ્નોસ્ટિક પછી ';' અપેક્ષિત છે",
        "ડાયગ્નોસ્ટિક લખી શકાયું નહીં",
        "ચલ સોંપણી, ફંક્શન, પરત, છાપો, શરત, લૂપ, અથવા ડાયગ્નોસ્ટિક સ્ટેટમેન્ટ અપેક્ષિત છે",
        "અભિવ્યક્તિ પછી ';' અપેક્ષિત છે",
        "આઉટપુટ લખી શકાયું નહીં",
        "તુલના માટે સંખ્યાઓ જરૂરી છે",
        "ચલના નામ પછી '=' અપેક્ષિત છે",
        "અવ્યાખ્યાયિત ચલ",
        "ચલ સંગ્રહવા માટે પૂરતી મેમરી મળી નહીં",
        "તાર્કિક ઓપરેટર માટે સંખ્યા અથવા 'નકામો' જરૂરી છે",
        "'કાર્ય' પછી ફંક્શનનું નામ અપેક્ષિત છે",
        "ફંક્શનના નામ પછી '(' અપેક્ષિત છે",
        "પરિમાણનું નામ અપેક્ષિત છે",
        "ફંક્શનના પરિમાણો પછી ')' અપેક્ષિત છે",
        "ફંક્શનનું શરીર અપેક્ષિત છે",
        "ફંક્શન પહેલેથી જાહેર કરેલું છે",
        "અવ્યાખ્યાયિત ફંક્શન",
        "ફંક્શન માટે દલીલોની સંખ્યા ખોટી છે",
        "પરિમાણ પહેલેથી જાહેર કરેલું છે",
        "'પરત' નો ઉપયોગ ફક્ત ફંક્શનની અંદર થઈ શકે છે",
        "ફંક્શન સંગ્રહવા માટે પૂરતી મેમરી મળી નહીં",
        "ફંક્શનની દલીલો સંગ્રહવા માટે પૂરતી મેમરી મળી નહીં",
        "'વાંચો' માટે લખાણરૂપ સંદેશ અપેક્ષિત છે",
        "માનક ઇનપુટમાંથી લીટી વાંચી શકાયી નહીં",
        "ઇનપુટ સંગ્રહવા માટે પૂરતી મેમરી મળી નહીં",
        "આ બિલ્ટ-ઇન ફંક્શનનું નામ જાહેર કરી શકાય નહીં",
        "REPL માં દરેક લીટી પર એક પૂરું સ્ટેટમેન્ટ અથવા અભિવ્યક્તિ અપેક્ષિત છે",
        "પ્રોગ્રામની શરૂઆતમાં 'આવો' અપેક્ષિત છે",
        "પ્રોગ્રામના અંતે 'આવજો' અપેક્ષિત છે",
        "'આવજો' પછી ફાઇલનો અંત અપેક્ષિત છે",
        "ફાઇલ ખોલી શકાયી નહીં",
        "ફાઇલ વાંચી શકાયી નહીં",
        "ફાઇલ વાંચતી વખતે પૂરતી મેમરી મળી નહીં",
        "ફાઇલમાં NUL બાઇટ છે",
        "કોન્સોલનું આઉટપુટ UTF-8 પર સેટ કરી શકાયું નહીં",
        "ઉપયોગ: %s [--language en|gu] <source.gj> | [--language en|gu] --repl"
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

static int is_identifier_start(char character)
{
    unsigned char byte = (unsigned char)character;
    return (byte >= 'a' && byte <= 'z') ||
           (byte >= 'A' && byte <= 'Z') ||
           byte == '_' || byte >= 0x80;
}

static int is_identifier_continue(char character)
{
    unsigned char byte = (unsigned char)character;
    return is_identifier_start(character) ||
           (byte >= '0' && byte <= '9');
}

static int keyword_matches(const Parser *parser, const char *keyword)
{
    size_t length = strlen(keyword);
    return strncmp(parser->source + parser->offset, keyword, length) == 0 &&
           !is_identifier_continue(parser->source[parser->offset + length]);
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
    token.source_offset = 0;
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
    static const char while_keyword[] = "જ્યાં સુધી";
    static const char else_if_keyword[] = "નહિતર જો";
    static const char else_keyword[] = "નહિતર";
    static const char and_keyword[] = "અને";
    static const char or_keyword[] = "અથવા";
    static const char not_keyword[] = "નહીં";
    static const char null_keyword[] = "નકામો";
    static const char fatal_error_keyword[] = "ઘાતક ભૂલ";
    static const char error_keyword[] = "ભૂલ";
    static const char warning_keyword[] = "ચેતવણી";
    static const char function_keyword[] = "કાર્ય";
    static const char return_keyword[] = "પરત";
    Token token;
    size_t start;
    char character;

    skip_whitespace_and_comments(parser);
    token = make_token(TOKEN_EOF, parser->line, parser->column);
    token.source_offset = parser->offset;
    character = peek(parser);
    if (character == '\0') {
        return token;
    }

    if (keyword_matches(parser, else_if_keyword)) {
        size_t index;
        for (index = 0; index < sizeof(else_if_keyword) - 1; index++) {
            advance_char(parser);
        }
        token.kind = TOKEN_ELSE_IF;
        return token;
    }
    if (keyword_matches(parser, fatal_error_keyword)) {
        size_t index;
        for (index = 0; index < sizeof(fatal_error_keyword) - 1; index++) {
            advance_char(parser);
        }
        token.kind = TOKEN_FATAL_ERROR;
        return token;
    }
    if (keyword_matches(parser, start_keyword)) {
        size_t index;
        for (index = 0; index < sizeof(start_keyword) - 1; index++) {
            advance_char(parser);
        }
        token.kind = TOKEN_START;
        return token;
    }
    if (keyword_matches(parser, end_keyword)) {
        size_t index;
        for (index = 0; index < sizeof(end_keyword) - 1; index++) {
            advance_char(parser);
        }
        token.kind = TOKEN_END;
        return token;
    }
    if (keyword_matches(parser, print_keyword)) {
        size_t index;
        for (index = 0; index < sizeof(print_keyword) - 1; index++) {
            advance_char(parser);
        }
        token.kind = TOKEN_PRINT;
        return token;
    }
    if (keyword_matches(parser, if_keyword)) {
        size_t index;
        for (index = 0; index < sizeof(if_keyword) - 1; index++) {
            advance_char(parser);
        }
        token.kind = TOKEN_IF;
        return token;
    }
    if (keyword_matches(parser, while_keyword)) {
        size_t index;
        for (index = 0; index < sizeof(while_keyword) - 1; index++) {
            advance_char(parser);
        }
        token.kind = TOKEN_WHILE;
        return token;
    }
    if (keyword_matches(parser, and_keyword)) {
        size_t index;
        for (index = 0; index < sizeof(and_keyword) - 1; index++) {
            advance_char(parser);
        }
        token.kind = TOKEN_AND;
        return token;
    }
    if (keyword_matches(parser, or_keyword)) {
        size_t index;
        for (index = 0; index < sizeof(or_keyword) - 1; index++) {
            advance_char(parser);
        }
        token.kind = TOKEN_OR;
        return token;
    }
    if (keyword_matches(parser, not_keyword)) {
        size_t index;
        for (index = 0; index < sizeof(not_keyword) - 1; index++) {
            advance_char(parser);
        }
        token.kind = TOKEN_NOT;
        return token;
    }
    if (keyword_matches(parser, else_keyword)) {
        size_t index;
        for (index = 0; index < sizeof(else_keyword) - 1; index++) {
            advance_char(parser);
        }
        token.kind = TOKEN_ELSE;
        return token;
    }
    if (keyword_matches(parser, null_keyword)) {
        size_t index;
        for (index = 0; index < sizeof(null_keyword) - 1; index++) {
            advance_char(parser);
        }
        token.kind = TOKEN_NULL;
        return token;
    }
    if (keyword_matches(parser, error_keyword)) {
        size_t index;
        for (index = 0; index < sizeof(error_keyword) - 1; index++) {
            advance_char(parser);
        }
        token.kind = TOKEN_ERROR;
        return token;
    }
    if (keyword_matches(parser, warning_keyword)) {
        size_t index;
        for (index = 0; index < sizeof(warning_keyword) - 1; index++) {
            advance_char(parser);
        }
        token.kind = TOKEN_WARNING;
        return token;
    }
    if (keyword_matches(parser, function_keyword)) {
        size_t index;
        for (index = 0; index < sizeof(function_keyword) - 1; index++) {
            advance_char(parser);
        }
        token.kind = TOKEN_FUNCTION;
        return token;
    }
    if (keyword_matches(parser, return_keyword)) {
        size_t index;
        for (index = 0; index < sizeof(return_keyword) - 1; index++) {
            advance_char(parser);
        }
        token.kind = TOKEN_RETURN;
        return token;
    }
    if (is_identifier_start(character)) {
        size_t identifier_start = parser->offset;
        while (is_identifier_continue(peek(parser))) {
            advance_char(parser);
        }
        token.kind = TOKEN_IDENTIFIER;
        token.string_offset = identifier_start;
        token.string_length = parser->offset - identifier_start;
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
            token.kind = TOKEN_EQUAL;
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
    case ',': token.kind = TOKEN_COMMA; break;
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
    value.owned_string = NULL;
    return value;
}

static Variable *find_variable(Parser *parser, Token name)
{
    Environment *environment;
    for (environment = parser->environment; environment != NULL;
         environment = environment->parent) {
        size_t index;
        for (index = 0; index < environment->variable_count; index++) {
            Variable *variable = &environment->variables[index];
            if (variable->name_length == name.string_length &&
                memcmp(parser->source + variable->name_offset,
                       parser->source + name.string_offset,
                       name.string_length) == 0) {
                return variable;
            }
        }
    }
    return NULL;
}

static int declare_variable(Parser *parser, Token name, Value value)
{
    Environment *environment = parser->environment;
    Variable *variables;
    size_t capacity;
    if (environment->variable_count == environment->variable_capacity) {
        if (environment->variable_capacity == 0) {
            capacity = 8;
        } else {
            if (environment->variable_capacity >
                (size_t)-1 / 2 / sizeof(*environment->variables)) {
                report_error(parser, name.line, name.column,
                             MESSAGE_OUT_OF_MEMORY_FOR_VARIABLE);
                return 0;
            }
            capacity = environment->variable_capacity * 2;
        }
        variables = (Variable *)realloc(environment->variables,
                                        capacity * sizeof(*variables));
        if (variables == NULL) {
            report_error(parser, name.line, name.column,
                         MESSAGE_OUT_OF_MEMORY_FOR_VARIABLE);
            return 0;
        }
        environment->variables = variables;
        environment->variable_capacity = capacity;
    }

    environment->variables[environment->variable_count].name_offset =
        name.string_offset;
    environment->variables[environment->variable_count].name_length =
        name.string_length;
    environment->variables[environment->variable_count].value = value;
    environment->variable_count++;
    return 1;
}

static int assign_variable(Parser *parser, Token name, Value value)
{
    Variable *variable = find_variable(parser, name);
    if (variable == NULL) {
        report_error(parser, name.line, name.column,
                     MESSAGE_UNDEFINED_VARIABLE);
        return 0;
    }
    variable->value = value;
    return 1;
}

static Value parse_expression(Parser *parser, int execute);
static Value parse_additive(Parser *parser, int execute);
static int value_is_truthy(Value value);
static int parse_block(Parser *parser, int execute);

static Value null_value(void)
{
    Value value = number_value(0.0);
    value.kind = VALUE_NULL;
    return value;
}

static Function *find_function(Parser *parser, Token name)
{
    size_t index;
    for (index = 0; index < parser->function_count; index++) {
        Function *function = &parser->functions[index];
        if (function->name_length == name.string_length &&
            memcmp(parser->source + function->name_offset,
                   parser->source + name.string_offset,
                   name.string_length) == 0) {
            return function;
        }
    }
    return NULL;
}

static int write_string(Parser *parser, FILE *output,
                        size_t offset, size_t length);

static int token_matches(Parser *parser, Token token, const char *text)
{
    size_t length = strlen(text);
    return token.string_length == length &&
           memcmp(parser->source + token.string_offset, text, length) == 0;
}

static int store_input_string(Parser *parser, Token name, char *input)
{
    StringStorage *storage = parser->string_storage;
    if (storage->count == storage->capacity) {
        size_t capacity = storage->capacity == 0 ? 4 : storage->capacity * 2;
        char **items;
        if (capacity < storage->capacity ||
            capacity > (size_t)-1 / sizeof(*storage->items)) {
            free(input);
            report_error(parser, name.line, name.column,
                         MESSAGE_OUT_OF_MEMORY_FOR_INPUT);
            return 0;
        }
        items = (char **)realloc(storage->items, capacity * sizeof(*items));
        if (items == NULL) {
            free(input);
            report_error(parser, name.line, name.column,
                         MESSAGE_OUT_OF_MEMORY_FOR_INPUT);
            return 0;
        }
        storage->items = items;
        storage->capacity = capacity;
    }
    storage->items[storage->count++] = input;
    return 1;
}

static int read_input_line(Parser *parser, Token name, Value prompt,
                           Value *result)
{
    size_t capacity = 64;
    size_t length = 0;
    int received_character = 0;
    char *input = (char *)malloc(capacity);
    int character;

    if (input == NULL) {
        report_error(parser, name.line, name.column,
                     MESSAGE_OUT_OF_MEMORY_FOR_INPUT);
        return 0;
    }
    if (prompt.owned_string != NULL) {
        if (fwrite(prompt.owned_string, 1, prompt.string_length, stdout) !=
                prompt.string_length ||
            fflush(stdout) == EOF) {
            free(input);
            report_error(parser, name.line, name.column, MESSAGE_WRITE_OUTPUT);
            return 0;
        }
    } else if (!write_string(parser, stdout, prompt.string_offset,
                             prompt.string_length) ||
               fflush(stdout) == EOF) {
        free(input);
        report_error(parser, name.line, name.column, MESSAGE_WRITE_OUTPUT);
        return 0;
    }

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        received_character = 1;
        if (character == '\0') {
            free(input);
            report_error(parser, name.line, name.column,
                         MESSAGE_COULD_NOT_READ_INPUT);
            return 0;
        }
        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_input;
            if (capacity > (size_t)-1 / 2) {
                free(input);
                report_error(parser, name.line, name.column,
                             MESSAGE_OUT_OF_MEMORY_FOR_INPUT);
                return 0;
            }
            new_capacity = capacity * 2;
            new_input = (char *)realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                report_error(parser, name.line, name.column,
                             MESSAGE_OUT_OF_MEMORY_FOR_INPUT);
                return 0;
            }
            input = new_input;
            capacity = new_capacity;
        }
        input[length++] = (char)character;
    }
    if (ferror(stdin) || (character == EOF && !received_character)) {
        free(input);
        report_error(parser, name.line, name.column,
                     MESSAGE_COULD_NOT_READ_INPUT);
        return 0;
    }
    if (length > 0 && input[length - 1] == '\r') {
        length--;
    }
    input[length] = '\0';
    if (!store_input_string(parser, name, input)) {
        return 0;
    }

    *result = number_value(0.0);
    result->kind = VALUE_STRING;
    result->string_length = length;
    result->owned_string = input;
    return 1;
}

static Value call_function(Parser *parser, Function function,
                           const Value *arguments)
{
    Environment local_environment;
    Parser callee = *parser;
    size_t index;
    Value result = null_value();

    memset(&local_environment, 0, sizeof(local_environment));
    local_environment.parent = parser->globals;
    callee.environment = &local_environment;
    callee.in_function = 1;
    callee.returned = 0;
    callee.return_value = null_value();
    callee.failed = 0;
    callee.offset = function.body_open.source_offset;
    callee.line = function.body_open.line;
    callee.column = function.body_open.column;
    callee.current = make_token(TOKEN_EOF, callee.line, callee.column);
    advance_token(&callee);

    for (index = 0; index < function.parameter_count; index++) {
        if (!declare_variable(&callee, function.parameters[index],
                              arguments[index])) {
            break;
        }
    }
    if (!callee.failed) {
        parse_block(&callee, 1);
    }
    if (callee.failed) {
        parser->failed = 1;
    } else if (callee.returned) {
        result = callee.return_value;
    }
    free(local_environment.variables);
    return result;
}

static Value parse_function_call(Parser *parser, Token name, int execute)
{
    Value *arguments = NULL;
    size_t argument_count = 0;
    size_t argument_capacity = 0;
    Value result = null_value();

    advance_token(parser);
    while (!parser->failed &&
           parser->current.kind != TOKEN_RIGHT_PAREN) {
        Value argument = parse_expression(parser, execute);
        if (parser->failed) {
            break;
        }
        if (execute) {
            if (argument_count == argument_capacity) {
                size_t capacity = argument_capacity == 0 ? 4 :
                                  argument_capacity * 2;
                Value *new_arguments;
                if (capacity < argument_capacity ||
                    capacity > (size_t)-1 / sizeof(*arguments)) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_OUT_OF_MEMORY_FOR_ARGUMENTS);
                    break;
                }
                new_arguments = (Value *)realloc(
                    arguments, capacity * sizeof(*arguments));
                if (new_arguments == NULL) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_OUT_OF_MEMORY_FOR_ARGUMENTS);
                    break;
                }
                arguments = new_arguments;
                argument_capacity = capacity;
            }
            arguments[argument_count] = argument;
        }
        argument_count++;
        if (parser->current.kind != TOKEN_COMMA) {
            break;
        }
        advance_token(parser);
        if (parser->current.kind == TOKEN_RIGHT_PAREN) {
            report_error(parser, parser->current.line, parser->current.column,
                         MESSAGE_EXPECTED_VALUE);
            break;
        }
    }
    if (!parser->failed && parser->current.kind != TOKEN_RIGHT_PAREN) {
        report_error(parser, parser->current.line, parser->current.column,
                     MESSAGE_EXPECTED_RIGHT_PAREN);
    }
    if (!parser->failed) {
        advance_token(parser);
        if (execute) {
            if (token_matches(parser, name, "વાંચો")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_INPUT_PROMPT);
                } else {
                    read_input_line(parser, name, arguments[0], &result);
                }
            } else {
                Function *function = find_function(parser, name);
                if (function == NULL) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_UNDEFINED_FUNCTION);
                } else if (function->parameter_count != argument_count) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    result = call_function(parser, *function, arguments);
                }
            }
        }
    }
    free(arguments);
    return result;
}

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
        value = null_value();
        advance_token(parser);
        return value;
    }
    if (token.kind == TOKEN_STRING) {
        value = number_value(0.0);
        value.kind = VALUE_STRING;
        value.string_offset = token.string_offset;
        value.string_length = token.string_length;
        value.owned_string = NULL;
        advance_token(parser);
        return value;
    }
    if (token.kind == TOKEN_IDENTIFIER) {
        Variable *variable = find_variable(parser, token);
        advance_token(parser);
        if (parser->current.kind == TOKEN_LEFT_PAREN) {
            return parse_function_call(parser, token, execute);
        }
        if (variable == NULL) {
            if (execute) {
                report_error(parser, token.line, token.column,
                             MESSAGE_UNDEFINED_VARIABLE);
            }
            return number_value(0.0);
        }
        return variable->value;
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

static Value parse_comparison(Parser *parser, int execute)
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

static int check_logical_operand(Parser *parser, Token operation, Value value,
                                 int execute)
{
    if (execute && value.kind == VALUE_STRING) {
        report_runtime_error(parser, operation,
                             MESSAGE_LOGICAL_OPERANDS_REQUIRED, 1);
        return 0;
    }
    return 1;
}

static Value parse_not(Parser *parser, int execute)
{
    if (parser->current.kind == TOKEN_NOT) {
        Token operation = parser->current;
        Value value;
        advance_token(parser);
        value = parse_not(parser, execute);
        if (parser->failed ||
            !check_logical_operand(parser, operation, value, execute)) {
            return number_value(0.0);
        }
        return number_value(value_is_truthy(value) ? 0.0 : 1.0);
    }
    return parse_comparison(parser, execute);
}

static Value parse_and(Parser *parser, int execute)
{
    Value value = parse_not(parser, execute);

    while (!parser->failed && parser->current.kind == TOKEN_AND) {
        Token operation = parser->current;
        int left_truthy;
        Value right;

        if (!check_logical_operand(parser, operation, value, execute)) {
            return number_value(0.0);
        }
        left_truthy = value_is_truthy(value);
        advance_token(parser);
        right = parse_not(parser, execute && left_truthy);
        if (parser->failed ||
            !check_logical_operand(parser, operation, right,
                                   execute && left_truthy)) {
            return number_value(0.0);
        }
        value = number_value(left_truthy && value_is_truthy(right) ?
                             1.0 : 0.0);
    }
    return value;
}

static Value parse_expression(Parser *parser, int execute)
{
    Value value = parse_and(parser, execute);

    while (!parser->failed && parser->current.kind == TOKEN_OR) {
        Token operation = parser->current;
        int left_truthy;
        Value right;

        if (!check_logical_operand(parser, operation, value, execute)) {
            return number_value(0.0);
        }
        left_truthy = value_is_truthy(value);
        advance_token(parser);
        right = parse_and(parser, execute && !left_truthy);
        if (parser->failed ||
            !check_logical_operand(parser, operation, right,
                                   execute && !left_truthy)) {
            return number_value(0.0);
        }
        value = number_value(left_truthy || value_is_truthy(right) ?
                             1.0 : 0.0);
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
        if (value.owned_string != NULL) {
            return fwrite(value.owned_string, 1, value.string_length, stdout) ==
                   value.string_length;
        }
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
        parse_statement(parser, execute && !parser->returned);
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

static int parse_while_loop(Parser *parser, int execute, Token keyword)
{
    Token condition_open = parser->current;

    for (;;) {
        Value condition;
        int body_execute;

        if (parser->current.kind != TOKEN_LEFT_PAREN) {
            report_error(parser, parser->current.line, parser->current.column,
                         MESSAGE_EXPECTED_WHILE_OPEN);
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
            report_runtime_error(parser, keyword, MESSAGE_CONDITION_TYPE,
                                 execute);
            if (parser->failed) {
                return 0;
            }
        }

        body_execute = execute && value_is_truthy(condition);
        advance_token(parser);
        if (!parse_block(parser, body_execute)) {
            return 0;
        }
        if (parser->returned) {
            return 1;
        }
        if (!body_execute) {
            return 1;
        }

        parser->offset = condition_open.source_offset;
        parser->line = condition_open.line;
        parser->column = condition_open.column;
        parser->current = make_token(TOKEN_EOF, parser->line, parser->column);
        advance_token(parser);
    }
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

static int parse_variable_assignment(Parser *parser, Token name, int execute)
{
    Value value;

    if (parser->current.kind != TOKEN_EQUAL) {
        report_error(parser, parser->current.line, parser->current.column,
                     MESSAGE_EXPECTED_ASSIGNMENT);
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
    if (execute) {
        if (find_variable(parser, name) != NULL) {
            if (!assign_variable(parser, name, value)) {
                return 0;
            }
        } else if (!declare_variable(parser, name, value)) {
            return 0;
        }
    }
    advance_token(parser);
    return !parser->failed;
}

static int register_function(Parser *parser, Token name, Token *parameters,
                             size_t parameter_count, Token body_open)
{
    Function *existing = find_function(parser, name);
    Function *functions;
    size_t capacity;

    if (existing != NULL) {
        free(parameters);
        if (existing->declaration_offset == name.source_offset) {
            return 1;
        }
        report_error(parser, name.line, name.column,
                     MESSAGE_DUPLICATE_FUNCTION);
        return 0;
    }
    if (parser->function_count == parser->function_capacity) {
        if (parser->function_capacity == 0) {
            capacity = 8;
        } else {
            if (parser->function_capacity >
                (size_t)-1 / 2 / sizeof(*parser->functions)) {
                free(parameters);
                report_error(parser, name.line, name.column,
                             MESSAGE_OUT_OF_MEMORY_FOR_FUNCTION);
                return 0;
            }
            capacity = parser->function_capacity * 2;
        }
        functions = (Function *)realloc(parser->functions,
                                        capacity * sizeof(*functions));
        if (functions == NULL) {
            free(parameters);
            report_error(parser, name.line, name.column,
                         MESSAGE_OUT_OF_MEMORY_FOR_FUNCTION);
            return 0;
        }
        parser->functions = functions;
        parser->function_capacity = capacity;
    }
    parser->functions[parser->function_count].name_offset =
        name.string_offset;
    parser->functions[parser->function_count].name_length =
        name.string_length;
    parser->functions[parser->function_count].declaration_offset =
        name.source_offset;
    parser->functions[parser->function_count].parameters = parameters;
    parser->functions[parser->function_count].parameter_count =
        parameter_count;
    parser->functions[parser->function_count].body_open = body_open;
    parser->function_count++;
    return 1;
}

static int parse_function_declaration(Parser *parser, int execute)
{
    Token name;
    Token *parameters = NULL;
    size_t parameter_count = 0;
    size_t parameter_capacity = 0;
    Token body_open;
    size_t brace_depth = 0;

    advance_token(parser);
    if (parser->current.kind != TOKEN_IDENTIFIER) {
        report_error(parser, parser->current.line, parser->current.column,
                     MESSAGE_EXPECTED_FUNCTION_NAME);
        return 0;
    }
    name = parser->current;
    if (token_matches(parser, name, "વાંચો")) {
        report_error(parser, name.line, name.column,
                     MESSAGE_RESERVED_FUNCTION_NAME);
        return 0;
    }
    advance_token(parser);
    if (parser->current.kind != TOKEN_LEFT_PAREN) {
        report_error(parser, parser->current.line, parser->current.column,
                     MESSAGE_EXPECTED_FUNCTION_OPEN);
        return 0;
    }
    advance_token(parser);
    while (!parser->failed &&
           parser->current.kind != TOKEN_RIGHT_PAREN) {
        size_t index;
        Token parameter;
        if (parser->current.kind != TOKEN_IDENTIFIER) {
            free(parameters);
            report_error(parser, parser->current.line, parser->current.column,
                         MESSAGE_EXPECTED_PARAMETER);
            return 0;
        }
        parameter = parser->current;
        for (index = 0; index < parameter_count; index++) {
            if (parameters[index].string_length == parameter.string_length &&
                memcmp(parser->source + parameters[index].string_offset,
                       parser->source + parameter.string_offset,
                       parameter.string_length) == 0) {
                free(parameters);
                report_error(parser, parameter.line, parameter.column,
                             MESSAGE_DUPLICATE_PARAMETER);
                return 0;
            }
        }
        if (parameter_count == parameter_capacity) {
            size_t capacity = parameter_capacity == 0 ? 4 :
                              parameter_capacity * 2;
            Token *new_parameters;
            if (capacity < parameter_capacity ||
                capacity > (size_t)-1 / sizeof(*parameters)) {
                free(parameters);
                report_error(parser, parameter.line, parameter.column,
                             MESSAGE_OUT_OF_MEMORY_FOR_FUNCTION);
                return 0;
            }
            new_parameters = (Token *)realloc(
                parameters, capacity * sizeof(*parameters));
            if (new_parameters == NULL) {
                free(parameters);
                report_error(parser, parameter.line, parameter.column,
                             MESSAGE_OUT_OF_MEMORY_FOR_FUNCTION);
                return 0;
            }
            parameters = new_parameters;
            parameter_capacity = capacity;
        }
        parameters[parameter_count++] = parameter;
        advance_token(parser);
        if (parser->current.kind != TOKEN_COMMA) {
            break;
        }
        advance_token(parser);
        if (parser->current.kind == TOKEN_RIGHT_PAREN) {
            free(parameters);
            report_error(parser, parser->current.line, parser->current.column,
                         MESSAGE_EXPECTED_PARAMETER);
            return 0;
        }
    }
    if (parser->failed) {
        free(parameters);
        return 0;
    }
    if (parser->current.kind != TOKEN_RIGHT_PAREN) {
        free(parameters);
        report_error(parser, parser->current.line, parser->current.column,
                     MESSAGE_EXPECTED_FUNCTION_CLOSE);
        return 0;
    }
    advance_token(parser);
    if (parser->current.kind != TOKEN_LEFT_BRACE) {
        free(parameters);
        report_error(parser, parser->current.line, parser->current.column,
                     MESSAGE_EXPECTED_FUNCTION_BODY);
        return 0;
    }
    body_open = parser->current;
    while (!parser->failed && parser->current.kind != TOKEN_EOF &&
           parser->current.kind != TOKEN_END) {
        if (parser->current.kind == TOKEN_LEFT_BRACE) {
            brace_depth++;
        } else if (parser->current.kind == TOKEN_RIGHT_BRACE) {
            brace_depth--;
            if (brace_depth == 0) {
                advance_token(parser);
                break;
            }
        }
        advance_token(parser);
    }
    if (parser->failed) {
        free(parameters);
        return 0;
    }
    if (brace_depth != 0) {
        free(parameters);
        report_error(parser, parser->current.line, parser->current.column,
                     MESSAGE_EXPECTED_BLOCK_CLOSE);
        return 0;
    }
    if (execute) {
        return register_function(parser, name, parameters, parameter_count,
                                 body_open);
    }
    free(parameters);
    return 1;
}

static int parse_return_statement(Parser *parser, Token statement,
                                  int execute)
{
    Value value = null_value();

    advance_token(parser);
    if (parser->current.kind != TOKEN_SEMICOLON) {
        value = parse_expression(parser, execute);
        if (parser->failed) {
            return 0;
        }
    }
    if (parser->current.kind != TOKEN_SEMICOLON) {
        report_error(parser, parser->current.line, parser->current.column,
                     MESSAGE_EXPECTED_EXPRESSION_SEMICOLON);
        return 0;
    }
    if (!parser->in_function) {
        report_error(parser, statement.line, statement.column,
                     MESSAGE_RETURN_OUTSIDE_FUNCTION);
        return 0;
    }
    if (execute) {
        parser->returned = 1;
        parser->return_value = value;
    }
    advance_token(parser);
    return !parser->failed;
}

static int parse_statement(Parser *parser, int execute)
{
    Token statement = parser->current;
    Value value;

    if (statement.kind == TOKEN_IF) {
        advance_token(parser);
        return parse_if_condition(parser, execute, statement);
    }
    if (statement.kind == TOKEN_WHILE) {
        advance_token(parser);
        return parse_while_loop(parser, execute, statement);
    }
    if (statement.kind == TOKEN_FUNCTION) {
        return parse_function_declaration(parser, execute);
    }
    if (statement.kind == TOKEN_RETURN) {
        return parse_return_statement(parser, statement, execute);
    }
    if (statement.kind == TOKEN_ERROR ||
        statement.kind == TOKEN_FATAL_ERROR ||
        statement.kind == TOKEN_WARNING) {
        return parse_diagnostic(parser, statement, execute);
    }
    if (statement.kind == TOKEN_IDENTIFIER) {
        advance_token(parser);
        if (parser->current.kind == TOKEN_LEFT_PAREN) {
            parse_function_call(parser, statement, execute);
            if (parser->failed) {
                return 0;
            }
            if (parser->current.kind != TOKEN_SEMICOLON) {
                report_error(parser, parser->current.line,
                             parser->current.column,
                             MESSAGE_EXPECTED_EXPRESSION_SEMICOLON);
                return 0;
            }
            advance_token(parser);
            return !parser->failed;
        }
        return parse_variable_assignment(parser, statement, execute);
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

static int parse_repl_command(Parser *parser, int execute)
{
    Token command = parser->current;
    Value value;
    int is_assignment = 0;

    if (parser->current.kind == TOKEN_IDENTIFIER) {
        Parser lookahead = *parser;
        advance_token(&lookahead);
        is_assignment = !lookahead.failed &&
                        lookahead.current.kind == TOKEN_EQUAL;
    }
    if (parser->current.kind == TOKEN_PRINT ||
        parser->current.kind == TOKEN_IF ||
        parser->current.kind == TOKEN_WHILE ||
        parser->current.kind == TOKEN_FUNCTION ||
        parser->current.kind == TOKEN_RETURN ||
        parser->current.kind == TOKEN_ERROR ||
        parser->current.kind == TOKEN_FATAL_ERROR ||
        parser->current.kind == TOKEN_WARNING ||
        is_assignment) {
        return parse_statement(parser, execute);
    }

    value = parse_expression(parser, execute);
    if (parser->failed) {
        return 0;
    }
    if (parser->current.kind == TOKEN_SEMICOLON) {
        advance_token(parser);
    }
    if (!parser->failed && parser->current.kind != TOKEN_EOF) {
        report_error(parser, parser->current.line, parser->current.column,
                     MESSAGE_EXPECTED_SINGLE_COMMAND);
        return 0;
    }
    if (execute && (!write_value(parser, value) || fputc('\n', stdout) == EOF)) {
        report_error(parser, command.line, command.column,
                     MESSAGE_WRITE_OUTPUT);
        return 0;
    }
    return !parser->failed;
}

static int read_repl_line(Parser *parser, char **line, size_t *length)
{
    size_t capacity = 64;
    size_t used = 0;
    int character;
    char *buffer = (char *)malloc(capacity);

    if (buffer == NULL) {
        report_error(parser, parser->line, parser->column,
                     MESSAGE_OUT_OF_MEMORY_FOR_INPUT);
        return -1;
    }
    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (character == '\0') {
            free(buffer);
            report_error(parser, parser->line, parser->column,
                         MESSAGE_COULD_NOT_READ_INPUT);
            return -1;
        }
        if (used + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;
            if (capacity > (size_t)-1 / 2) {
                free(buffer);
                report_error(parser, parser->line, parser->column,
                             MESSAGE_OUT_OF_MEMORY_FOR_INPUT);
                return -1;
            }
            new_capacity = capacity * 2;
            new_buffer = (char *)realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                report_error(parser, parser->line, parser->column,
                             MESSAGE_OUT_OF_MEMORY_FOR_INPUT);
                return -1;
            }
            buffer = new_buffer;
            capacity = new_capacity;
        }
        buffer[used++] = (char)character;
    }
    if (ferror(stdin)) {
        free(buffer);
        report_error(parser, parser->line, parser->column,
                     MESSAGE_COULD_NOT_READ_INPUT);
        return -1;
    }
    if (character == EOF && used == 0) {
        free(buffer);
        return 0;
    }
    if (used > 0 && buffer[used - 1] == '\r') {
        used--;
    }
    buffer[used] = '\0';
    *line = buffer;
    *length = used;
    return 1;
}

static int line_is_blank(const char *line, size_t length)
{
    size_t index;
    for (index = 0; index < length; index++) {
        if (line[index] != ' ' && line[index] != '\t' &&
            line[index] != '\r') {
            return 0;
        }
    }
    return 1;
}

static int append_repl_line(char **source, size_t *source_length,
                            size_t *source_capacity, const char *line,
                            size_t line_length)
{
    size_t required;
    if (*source_length > (size_t)-1 - 2 ||
        line_length > (size_t)-1 - *source_length - 2) {
        return 0;
    }
    required = *source_length + line_length + 2;
    if (required > *source_capacity) {
        size_t capacity = *source_capacity == 0 ? 256 : *source_capacity;
        char *new_source;
        while (capacity < required) {
            if (capacity > (size_t)-1 / 2) {
                capacity = required;
                break;
            }
            capacity *= 2;
        }
        new_source = (char *)realloc(*source, capacity);
        if (new_source == NULL) {
            return 0;
        }
        *source = new_source;
        *source_capacity = capacity;
    }
    memcpy(*source + *source_length, line, line_length);
    (*source)[*source_length + line_length] = '\n';
    *source_length += line_length + 1;
    (*source)[*source_length] = '\0';
    return 1;
}

static int run_repl(Language language)
{
    Parser parser;
    Environment globals;
    StringStorage string_storage;
    char *source = NULL;
    size_t source_length = 0;
    size_t source_capacity = 0;
    int read_status;
    int result = EXIT_SUCCESS;

    memset(&globals, 0, sizeof(globals));
    memset(&string_storage, 0, sizeof(string_storage));
    memset(&parser, 0, sizeof(parser));
    parser.source = "";
    parser.filename = "REPL";
    parser.language = language;
    parser.environment = &globals;
    parser.globals = &globals;
    parser.string_storage = &string_storage;
    parser.line = 1;
    parser.column = 1;

    for (;;) {
        char *line;
        size_t line_length;
        size_t command_offset;
        size_t command_line;
        Parser validation;

        if (fputs("GujaratiLang> ", stdout) == EOF || fflush(stdout) == EOF) {
            report_error(&parser, parser.line, parser.column,
                         MESSAGE_WRITE_OUTPUT);
            result = EXIT_FAILURE;
            break;
        }
        read_status = read_repl_line(&parser, &line, &line_length);
        if (read_status <= 0) {
            if (read_status < 0) {
                result = EXIT_FAILURE;
            }
            break;
        }
        if (line_is_blank(line, line_length)) {
            free(line);
            continue;
        }

        command_offset = source_length;
        command_line = parser.line;
        if (!append_repl_line(&source, &source_length, &source_capacity,
                              line, line_length)) {
            free(line);
            report_error(&parser, parser.line, parser.column,
                         MESSAGE_OUT_OF_MEMORY_FOR_INPUT);
            result = EXIT_FAILURE;
            break;
        }
        free(line);

        parser.source = source;
        parser.offset = command_offset;
        parser.line = command_line;
        parser.column = 1;
        parser.current = make_token(TOKEN_EOF, command_line, 1);
        parser.failed = 0;
        parser.in_function = 0;
        parser.returned = 0;
        advance_token(&parser);

        validation = parser;
        if (!validation.failed) {
            parse_repl_command(&validation, 0);
        }
        if (!validation.failed &&
            validation.current.kind != TOKEN_EOF) {
            report_error(&validation, validation.current.line,
                         validation.current.column,
                         MESSAGE_EXPECTED_SINGLE_COMMAND);
        }
        if (!validation.failed) {
            parser.offset = command_offset;
            parser.line = command_line;
            parser.column = 1;
            parser.current = make_token(TOKEN_EOF, command_line, 1);
            advance_token(&parser);
            parse_repl_command(&parser, 1);
            if (!parser.failed && parser.current.kind != TOKEN_EOF) {
                report_error(&parser, parser.current.line,
                             parser.current.column,
                             MESSAGE_EXPECTED_SINGLE_COMMAND);
            }
        }

        parser.source = source;
        parser.offset = source_length;
        parser.line = command_line + 1;
        parser.column = 1;
        parser.current = make_token(TOKEN_EOF, parser.line, parser.column);
        parser.failed = 0;
        parser.in_function = 0;
        parser.returned = 0;
    }

    free(globals.variables);
    while (parser.function_count > 0) {
        parser.function_count--;
        free(parser.functions[parser.function_count].parameters);
    }
    free(parser.functions);
    while (string_storage.count > 0) {
        free(string_storage.items[--string_storage.count]);
    }
    free(string_storage.items);
    free(source);
    return result;
}

static int interpret(const char *source, const char *filename, Language language)
{
    Parser parser;
    Environment globals;
    StringStorage string_storage;

    memset(&globals, 0, sizeof(globals));
    memset(&string_storage, 0, sizeof(string_storage));
    parser.source = source;
    parser.offset = 0;
    parser.line = 1;
    parser.column = 1;
    parser.filename = filename;
    parser.language = language;
    parser.environment = &globals;
    parser.globals = &globals;
    parser.functions = NULL;
    parser.function_count = 0;
    parser.function_capacity = 0;
    parser.string_storage = &string_storage;
    parser.failed = 0;
    parser.in_function = 0;
    parser.returned = 0;
    parser.return_value = null_value();
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
    free(globals.variables);
    while (parser.function_count > 0) {
        parser.function_count--;
        free(parser.functions[parser.function_count].parameters);
    }
    free(parser.functions);
    while (string_storage.count > 0) {
        free(string_storage.items[--string_storage.count]);
    }
    free(string_storage.items);
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
    const char *filename = NULL;
    Language language = LANGUAGE_ENGLISH;
    int result;
    int repl = 0;

    if (argc == 2) {
        if (strcmp(argv[1], "--repl") == 0) {
            repl = 1;
        } else {
            filename = argv[1];
        }
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
        if (strcmp(argv[3], "--repl") == 0) {
            repl = 1;
        } else {
            filename = argv[3];
        }
    } else {
        fprintf(stderr, localized_message(LANGUAGE_ENGLISH, MESSAGE_USAGE),
                argv[0]);
        return EXIT_FAILURE;
    }

#ifdef _WIN32
    {
        DWORD console_mode;
        HANDLE stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);
        HANDLE stdin_handle = GetStdHandle(STD_INPUT_HANDLE);
        if (stdout_handle != INVALID_HANDLE_VALUE &&
            GetConsoleMode(stdout_handle, &console_mode) &&
            !SetConsoleOutputCP(CP_UTF8)) {
            fprintf(stderr, "%s\n",
                    localized_message(language, MESSAGE_SET_CONSOLE_ENCODING));
            return EXIT_FAILURE;
        }
        if (stdin_handle != INVALID_HANDLE_VALUE &&
            GetConsoleMode(stdin_handle, &console_mode) &&
            !SetConsoleCP(CP_UTF8)) {
            fprintf(stderr, "%s\n",
                    localized_message(language, MESSAGE_SET_CONSOLE_ENCODING));
            return EXIT_FAILURE;
        }
    }
#endif

    if (repl) {
        return run_repl(language);
    }
    source = read_source_file(filename, language);
    if (source == NULL) {
        return EXIT_FAILURE;
    }
    result = interpret(source, filename, language);
    free(source);
    return result;
}
