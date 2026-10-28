#define _CRT_SECURE_NO_WARNINGS
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdint.h>
#include <ctype.h>

#define GUJARATI_PI 3.14159265358979323846
#define GUJARATI_E  2.71828182845904523536

#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#else
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#endif

typedef enum {
    TOKEN_EOF,
    TOKEN_START,
    TOKEN_END,
    TOKEN_PRINT,
    TOKEN_IF,
    TOKEN_WHILE,
    TOKEN_FOR,
    TOKEN_IN,
    TOKEN_RANGE,
    TOKEN_IMPORT,
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
    TOKEN_LEFT_BRACKET,
    TOKEN_RIGHT_BRACKET,
    TOKEN_LEFT_BRACE,
    TOKEN_RIGHT_BRACE,
    TOKEN_SEMICOLON,
    TOKEN_COLON,
    TOKEN_QUESTION,
    TOKEN_PERCENT,
    TOKEN_PLUS_EQUAL,
    TOKEN_MINUS_EQUAL,
    TOKEN_STAR_EQUAL,
    TOKEN_SLASH_EQUAL,
    TOKEN_PERCENT_EQUAL,
    TOKEN_CONST,
    TOKEN_BREAK,
    TOKEN_CONTINUE,
    TOKEN_TRY,
    TOKEN_CATCH,
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
    VALUE_STRING,
    VALUE_LIST,
    VALUE_DICT
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
    MESSAGE_EXPECTED_LIST_CLOSE,
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
    MESSAGE_EXPECTED_LENGTH_STRING,
    MESSAGE_COULD_NOT_READ_INPUT,
    MESSAGE_OUT_OF_MEMORY_FOR_INPUT,
    MESSAGE_OUT_OF_MEMORY_FOR_STRING,
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
    MESSAGE_EXPECTED_LIST_INDEX,
    MESSAGE_INDEXED_VALUE_NOT_LIST,
    MESSAGE_LIST_INDEX_MUST_BE_INTEGER,
    MESSAGE_LIST_INDEX_OUT_OF_RANGE,
    MESSAGE_OUT_OF_MEMORY_FOR_LIST,
    MESSAGE_EXPECTED_FOR_OPEN,
    MESSAGE_EXPECTED_FOR_VARIABLE,
    MESSAGE_EXPECTED_IN,
    MESSAGE_EXPECTED_RANGE_END,
    MESSAGE_RANGE_NUMBERS_REQUIRED,
    MESSAGE_EXPECTED_LIST_FOR_LOOP,
    MESSAGE_EXPECTED_IMPORT_PATH,
    MESSAGE_EXPECTED_IMPORT_SEMICOLON,
    MESSAGE_CIRCULAR_IMPORT,
    MESSAGE_EXPECTED_SANKHYA_STRING,
    MESSAGE_COULD_NOT_PARSE_NUMBER,
    MESSAGE_EXPECTED_LIST_FOR_UMERO,
    MESSAGE_EXPECTED_STRING_FOR_KAPO,
    MESSAGE_EXPECTED_KAPO_INTEGER,
    MESSAGE_EXPECTED_STRING_FOR_SHODHO,
    MESSAGE_EXPECTED_SHODHO_INTEGER,
    MESSAGE_EXPECTED_LIST_FOR_KADHO,
    MESSAGE_KADHO_EMPTY_LIST,
    MESSAGE_EXPECTED_STRING_FOR_CASE,
    MESSAGE_EXPECTED_NUMERIC_MATH_ARGUMENT,
    MESSAGE_EXPECTED_LIST_FOR_ULTAVO,
    MESSAGE_EXPECTED_STRING_FOR_BHAG,
    MESSAGE_EXPECTED_LIST_AND_STRING_FOR_JODO,
    MESSAGE_EXPECTED_STRING_FOR_SAF,
    MESSAGE_NEGATIVE_SQUARE_ROOT,
    MESSAGE_EXPECTED_LIST_FOR_GOTHVO,
    MESSAGE_EXPECTED_STRING_FOR_BADLO,
    MESSAGE_EXPECTED_STRING_FOR_PREFIX_SUFFIX,
    MESSAGE_EXPECTED_LIST_FOR_SAMAVE_CHHE,
    MESSAGE_EXPECTED_STRING_FOR_PUNRAVARTAN,
    MESSAGE_EXPECTED_PUNRAVARTAN_INTEGER,
    MESSAGE_EXPECTED_LIST_FOR_TUKDO,
    MESSAGE_EXPECTED_TUKDO_INTEGER,
    MESSAGE_EXPECTED_LIST_FOR_STHAN,
    MESSAGE_EXPECTED_STHAN_INTEGER,
    MESSAGE_EXPECTED_LIST_FOR_MUKO,
    MESSAGE_EXPECTED_MUKO_INTEGER,
    MESSAGE_MUKO_INDEX_OUT_OF_RANGE,
    MESSAGE_EXPECTED_STRING_FOR_PADDING,
    MESSAGE_EXPECTED_PADDING_WIDTH_INTEGER,
    MESSAGE_EXPECTED_PAD_STRING,
    MESSAGE_SIMA_MIN_GREATER_THAN_MAX,
    MESSAGE_YADACHHIK_MIN_GREATER_THAN_MAX,
    MESSAGE_EXPECTED_INTEGER_YADACHHIK,
    MESSAGE_EXPECTED_LIST_FOR_VISTARO,
    MESSAGE_LAGHUGANAK_DOMAIN_ERROR,
    MESSAGE_LAGHUGANAK_BASE_ERROR,
    MESSAGE_EXPECTED_STRING_FOR_AKSHAR_KOD,
    MESSAGE_EXPECTED_AKSHAR_KOD_INTEGER,
    MESSAGE_AKSHAR_KOD_INDEX_OUT_OF_RANGE,
    MESSAGE_INVALID_UNICODE_CODEPOINT,
    MESSAGE_EXPECTED_YADI_BHARO_COUNT_INTEGER,
    MESSAGE_EXPECTED_LIST_FOR_SARVALO_YADI,
    MESSAGE_EXPECTED_NUMERIC_LIST_ELEMENTS,
    MESSAGE_EXPECTED_LIST_FOR_YADI_NYUNATAM,
    MESSAGE_EMPTY_LIST_FOR_YADI_NYUNATAM,
    MESSAGE_EXPECTED_NUMERIC_LIST_FOR_YADI_NYUNATAM,
    MESSAGE_EXPECTED_LIST_FOR_YADI_MAHATAM,
    MESSAGE_EMPTY_LIST_FOR_YADI_MAHATAM,
    MESSAGE_EXPECTED_NUMERIC_LIST_FOR_YADI_MAHATAM,
    MESSAGE_EXPECTED_LIST_OR_STRING_FOR_GANATARI,
    MESSAGE_EXPECTED_STRING_SECOND_FOR_GANATARI,
    MESSAGE_EXPECTED_STRING_FOR_DABE_KAPO,
    MESSAGE_EXPECTED_STRING_FOR_JAMNE_KAPO,
    MESSAGE_EXPECTED_STRING_FOR_VIBHAAJAN_PANKTI,
    MESSAGE_EXPECTED_STRING_FOR_AKSHARO,
    MESSAGE_EXPECTED_STRING_FOR_PARYAVARAN,
    MESSAGE_EXPECTED_EXIT_CODE_INTEGER,
    MESSAGE_EXPECTED_STRING_ASSERTION_MESSAGE,
    MESSAGE_ASSERTION_FAILED,
    MESSAGE_EXPECTED_STRING_FOR_SAMAVE_LAKHAN,
    MESSAGE_EXPECTED_STRING_FOR_FILE_PATH,
    MESSAGE_EXPECTED_STRING_FOR_FILE_CONTENT,
    MESSAGE_EXPECTED_COLON_AFTER_DICT_KEY,
    MESSAGE_EXPECTED_DICT_KEY_STRING,
    MESSAGE_EXPECTED_EVEN_DICT_ARGS,
    MESSAGE_EXPECTED_DICT_FOR_OPERATION,
    MESSAGE_BREAK_OUTSIDE_LOOP,
    MESSAGE_CONTINUE_OUTSIDE_LOOP,
    MESSAGE_EXPECTED_CATCH_AFTER_TRY,
    MESSAGE_EXPECTED_STRING_FOR_PHENKO,
    MESSAGE_EXPECTED_STRING_FOR_TARIKH,
    MESSAGE_EXPECTED_TIMESTAMP_NUMBER,
    MESSAGE_EXPECTED_SLEEP_MILLISECONDS,
    MESSAGE_EXPECTED_COLON_IN_TERNARY,
    MESSAGE_CANNOT_REASSIGN_CONSTANT,
    MESSAGE_VARIABLE_ALREADY_DECLARED,
    MESSAGE_EXPECTED_JSON_STRING,
    MESSAGE_INVALID_JSON,
    MESSAGE_EXPECTED_RADIX_INTEGER,
    MESSAGE_EXPECTED_RADIX_STRING,
    MESSAGE_EXPECTED_FUNCTION_FOR_MAP,
    MESSAGE_EXPECTED_FUNCTION_FOR_FILTER,
    MESSAGE_EXPECTED_FUNCTION_FOR_REDUCE,
    MESSAGE_EXPECTED_FUNCTION_FOR_FIND,
    MESSAGE_EXPECTED_LIST_FOR_FLATTEN,
    MESSAGE_EXPECTED_LISTS_FOR_ZIP,
    MESSAGE_EXPECTED_BASE64_STRING,
    MESSAGE_INVALID_BASE64,
    MESSAGE_EXPECTED_STRING_FOR_PATTERN,
    MESSAGE_EXPECTED_STRING_FOR_DISTANCE,
    MESSAGE_EXPECTED_MATRIX_LISTS,
    MESSAGE_USAGE
} MessageId;

typedef struct Value Value;
typedef struct Dict Dict;

typedef struct {
    Value *items;
    size_t count;
    size_t capacity;
} List;

struct Value {
    ValueKind kind;
    double number;
    size_t string_offset;
    size_t string_length;
    char *owned_string;
    const char *string_source;
    List *list;
    Dict *dict;
};

typedef struct {
    char *key;
    size_t key_length;
    Value value;
} DictEntry;

struct Dict {
    DictEntry *entries;
    size_t count;
    size_t capacity;
};

typedef struct {
    char **items;
    size_t count;
    size_t capacity;
    List **lists;
    size_t list_count;
    size_t list_capacity;
    Dict **dicts;
    size_t dict_count;
    size_t dict_capacity;
} StringStorage;

typedef struct {
    char *name;
    size_t name_length;
    Value value;
    int is_constant;
} Variable;

typedef struct Environment {
    Variable *variables;
    size_t variable_count;
    size_t variable_capacity;
    struct Environment *parent;
} Environment;

typedef struct {
    char *name;
    size_t name_length;
    size_t declaration_offset;
    const char *source;
    const char *filename;
    Token *parameters;
    size_t parameter_count;
    Token body_open;
} Function;

typedef struct {
    Function *items;
    size_t count;
    size_t capacity;
} FunctionTable;

typedef struct {
    char *path;
    char *source;
    int loading;
} Module;

typedef struct {
    Module *items;
    size_t count;
    size_t capacity;
} ModuleStorage;

typedef struct {
    const char *source;
    size_t offset;
    size_t line;
    size_t column;
    const char *filename;
    Language language;
    Environment *environment;
    Environment *globals;
    FunctionTable *function_table;
    StringStorage *string_storage;
    ModuleStorage *modules;
    Token current;
    int failed;
    int in_function;
    int returned;
    Value return_value;
    int loop_depth;
    int loop_broken;
    int loop_continued;
    int in_try;
    int error_caught;
    char *last_error_message;
} Parser;

static int import_module(Parser *parser, Token keyword, Value path_value);
static int interpret_program(Parser *parser);
static int append_list_item(Parser *parser, List *list, Value value,
                            Token token);
static int insert_list_item(Parser *parser, List *list, size_t index,
                            Value value, Token token);

static void write_source_context(Parser *parser, size_t line, size_t column)
{
    const char *line_start = parser->source;
    const char *line_end;
    size_t current_line = 1;
    size_t visible_column = 1;
    const char *cursor;

    if (line == 0 || column == 0) {
        return;
    }
    while (current_line < line && *line_start != '\0') {
        if (*line_start++ == '\n') {
            current_line++;
        }
    }
    if (current_line != line) {
        return;
    }
    line_end = line_start;
    while (*line_end != '\0' && *line_end != '\n') {
        line_end++;
    }
    if (line_end > line_start && line_end[-1] == '\r') {
        line_end--;
    }
    fputs("  ", stderr);
    fwrite(line_start, 1, (size_t)(line_end - line_start), stderr);
    fputc('\n', stderr);
    fputs("  ", stderr);
    cursor = line_start;
    while (cursor < line_end && visible_column < column) {
        unsigned char byte = (unsigned char)*cursor;
        if (byte == '\t') {
            fputc('\t', stderr);
        } else if ((byte & 0xC0) != 0x80) {
            fputc(' ', stderr);
        }
        cursor++;
        while (cursor < line_end &&
               ((unsigned char)*cursor & 0xC0) == 0x80) {
            cursor++;
        }
        visible_column++;
    }
    fputs("^\n", stderr);
}

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
        "expected ']' after list items",
        "expected '(' after 'જો'",
        "expected '(' after 'જ્યાં સુધી'",
        "expected ')' after condition",
        "condition must be a number or 'નકામો'",
        "expected a quoted message",
        "expected ';' after diagnostic",
        "could not write diagnostic",
        "expected an assignment, function, return, print, conditional, loop, import, or diagnostic statement",
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
        "expected a string or list argument for 'લંબાઈ'",
        "could not read a line from standard input",
        "out of memory while storing input",
        "out of memory while creating string",
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
        "expected a list index",
        "cannot index a non-list value",
        "list index must be a non-negative whole number",
        "list index is out of range",
        "out of memory while storing list",
        "expected '(' after 'દરેક' or 'darek'",
        "expected a loop variable after '('",
        "expected 'માં' or 'ma' after loop variable",
        "expected an end value after '..'",
        "range bounds must be whole numbers",
        "expected a list argument for loop",
        "expected a quoted module path after 'import'",
        "expected ';' after module import",
        "circular module import detected",
        "expected a string argument for 'સંખ્યા' or 'sankhya'",
        "could not parse string as a number",
        "expected a list first argument for 'ઉમેરો' or 'umero'",
        "expected a string first argument for 'કાપો' or 'kapo'",
        "slice indices for 'કાપો' or 'kapo' must be non-negative whole numbers",
        "expected string arguments for 'શોધો' or 'shodho'",
        "start index for 'શોધો' or 'shodho' must be a non-negative whole number",
        "expected a list first argument for 'કાઢો' or 'kadho'",
        "cannot remove item from an empty list",
        "expected a string argument for case conversion",
        "expected number arguments for math function",
        "expected a list argument for 'ઉલટાવો' or 'ultavo'",
        "expected string arguments for 'ભાગ' or 'bhag'",
        "expected list and string separator arguments for 'જોડો' or 'jodo'",
        "expected a string argument for 'સાફ' or 'saf'",
        "cannot calculate square root of a negative number",
        "expected a list argument for 'ગોઠવો' or 'gothvo'",
        "expected string arguments for 'બદલો' or 'badlo'",
        "expected string arguments for prefix/suffix check",
        "expected a list first argument for 'સમાવે_છે' or 'samave_chhe'",
        "expected a string first argument for 'પુનરાવર્તન' or 'punravartan'",
        "repetition count for 'પુનરાવર્તન' or 'punravartan' must be a non-negative whole number",
        "expected a list first argument for 'ટુકડો' or 'tukdo'",
        "slice indices for 'ટુકડો' or 'tukdo' must be non-negative whole numbers",
        "expected a list first argument for 'સ્થાન' or 'sthan'",
        "start index for 'સ્થાન' or 'sthan' must be a non-negative whole number",
        "expected a list first argument for 'મૂકો' or 'muko'",
        "insert index for 'મૂકો' or 'muko' must be a non-negative whole number",
        "insert index for 'મૂકો' or 'muko' is out of range",
        "expected a string first argument for padding",
        "width for padding must be a non-negative whole number",
        "pad character for padding must be a string",
        "minimum bound cannot be greater than maximum bound for 'સીમા' or 'sima'",
        "minimum bound cannot be greater than maximum bound for 'યાદચ્છિક' or 'yadachhik'",
        "range bounds for 'યાદચ્છિક' or 'yadachhik' must be whole numbers",
        "expected list arguments for 'વિસ્તારો' or 'vistaro'",
        "logarithm argument must be greater than zero",
        "logarithm base must be greater than zero and not equal to one",
        "expected a string first argument for 'અક્ષર_કોડ' or 'akshar_kod'",
        "index for 'અક્ષર_કોડ' or 'akshar_kod' must be a non-negative whole number",
        "index for 'અક્ષર_કોડ' or 'akshar_kod' is out of range",
        "invalid Unicode code point for 'કોડ_થી_અક્ષર' or 'kod_thi_akshar'",
        "count for 'યાદી_ભરો' or 'yadi_bharo' must be a non-negative whole number",
        "expected a list argument for 'સરવાળો_યાદી' or 'sarvalo_yadi'",
        "all list items must be numbers for 'સરવાળો_યાદી' or 'sarvalo_yadi'",
        "expected a list argument for 'યાદી_ન્યૂનતમ' or 'yadi_nyunatam'",
        "cannot find minimum of an empty list",
        "all list items must be numbers for 'યાદી_ન્યૂનતમ' or 'yadi_nyunatam'",
        "expected a list argument for 'યાદી_મહત્તમ' or 'yadi_mahatam'",
        "cannot find maximum of an empty list",
        "all list items must be numbers for 'યાદી_મહત્તમ' or 'yadi_mahatam'",
        "expected a list or string first argument for 'ગણતરી' or 'ganatari'",
        "expected a string second argument when counting in a string",
        "expected a string argument for 'ડાબે_કાપો' or 'dabe_kapo'",
        "expected a string argument for 'જમણે_કાપો' or 'jamne_kapo'",
        "expected a string argument for 'વિભાજન_પંક્તિ' or 'vibhaajan_pankti'",
        "expected a string argument for 'અક્ષરો' or 'aksharo'",
        "expected a string argument for 'પર્યાવરણ' or 'paryavaran'",
        "exit code for 'બહાર' or 'bahar' must be a whole number between 0 and 255",
        "assertion failure message must be a string",
        "assertion failed",
        "expected string arguments for 'સમાવે_લખાણ' or 'samave_lakhan'",
        "expected a string file path",
        "expected string content for file operation",
        "expected ':' after dictionary key",
        "dictionary key must be a string",
        "expected an even number of key-value arguments for 'શબ્દકોશ' or 'kosh'",
        "expected a dictionary argument",
        "'અટકો' or 'atko' can only be used inside a loop",
        "'ચાલુ_રાખો' or 'chalu_rakho' can only be used inside a loop",
        "expected 'પકડો' or 'pakdo' block after 'પ્રયત્ન' or 'prayatna'",
        "expected a string argument for 'ફેંકો' or 'phenko'",
        "format for 'તારીખ' or 'tarikh' must be a string",
        "timestamp must be a number",
        "sleep duration must be a non-negative number of milliseconds",
        "expected ':' in ternary operator",
        "cannot reassign constant variable",
        "variable with this name is already declared",
        "expected a JSON string",
        "invalid JSON format",
        "expected an integer for radix conversion",
        "expected a string for radix conversion",
        "expected a function name for 'નકશો_યાદી' or 'naksho_yadi'",
        "expected a function name for 'ગાળો_યાદી' or 'gaalo_yadi'",
        "expected a function name for 'સમેટો_યાદી' or 'sameto_yadi'",
        "expected a function name for 'શોધો_યાદી' or 'shodho_yadi'",
        "expected a list for flattening",
        "expected two lists for 'ઝીપ_યાદી' or 'zip_yadi'",
        "expected a string for base64 operation",
        "invalid base64 content",
        "expected string pattern and text",
        "expected string arguments for distance calculation",
        "expected 2D numeric matrices of compatible dimensions",
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
        "યાદીના ઘટકો પછી ']' અપેક્ષિત છે",
        "'જો' પછી '(' અપેક્ષિત છે",
        "'જ્યાં સુધી' પછી '(' અપેક્ષિત છે",
        "શરત પછી ')' અપેક્ષિત છે",
        "શરત સંખ્યા અથવા 'નકામો' હોવી જોઈએ",
        "અવતરણ ચિહ્નોમાં સંદેશ અપેક્ષિત છે",
        "ડાયગ્નોસ્ટિક પછી ';' અપેક્ષિત છે",
        "ડાયગ્નોસ્ટિક લખી શકાયું નહીં",
        "ચલ સોંપણી, ફંક્શન, પરત, છાપો, શરત, લૂપ, આયાત, અથવા ડાયગ્નોસ્ટિક સ્ટેટમેન્ટ અપેક્ષિત છે",
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
        "'લંબાઈ' માટે સ્ટ્રિંગ અથવા યાદીરૂપ દલીલ અપેક્ષિત છે",
        "માનક ઇનપુટમાંથી લીટી વાંચી શકાયી નહીં",
        "ઇનપુટ સંગ્રહવા માટે પૂરતી મેમરી મળી નહીં",
        "સ્ટ્રિંગ બનાવવા માટે પૂરતી મેમરી મળી નહીં",
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
        "યાદીનો અનુક્રમ અપેક્ષિત છે",
        "યાદી સિવાયના મૂલ્યને અનુક્રમિત કરી શકાતું નથી",
        "યાદીનો અનુક્રમ શૂન્ય અથવા ધન પૂર્ણાંક હોવો જોઈએ",
        "યાદીનો અનુક્રમ મર્યાદાની બહાર છે",
        "યાદી સંગ્રહવા માટે પૂરતી મેમરી મળી નહીં",
        "'દરેક' પછી '(' અપેક્ષિત છે",
        "'(' પછી લૂપનું ચલ અપેક્ષિત છે",
        "લૂપના ચલ પછી 'માં' અપેક્ષિત છે",
        "'..' પછી અંતિમ સંખ્યા અપેક્ષિત છે",
        "શ્રેણીની સીમાઓ પૂર્ણાંક હોવી જોઈએ",
        "લૂપ માટે યાદી અપેક્ષિત છે",
        "'આયાત' પછી અવતરણ ચિહ્નોમાં મોડ્યુલનો માર્ગ અપેક્ષિત છે",
        "મોડ્યુલ આયાત પછી ';' અપેક્ષિત છે",
        "ચક્રીય મોડ્યુલ આયાત મળી",
        "'સંખ્યા' માટે લખાણ દલીલ અપેક્ષિત છે",
        "લખાણને સંખ્યામાં રૂપાંતરિત કરી શકાયું નહીં",
        "'ઉમેરો' માટે પ્રથમ દલીલ યાદી હોવી જોઈએ",
        "'કાપો' માટે પ્રથમ દલીલ લખાણ હોવી જોઈએ",
        "'કાપો' માટે અનુક્રમ શૂન્ય અથવા ધન પૂર્ણાંક હોવા જોઈએ",
        "'શોધો' માટે લખાણરૂપ દલીલો અપેક્ષિત છે",
        "'શોધો' માટે શરૂઆતનો અનુક્રમ શૂન્ય અથવા ધન પૂર્ણાંક હોવો જોઈએ",
        "'કાઢો' માટે પ્રથમ દલીલ યાદી હોવી જોઈએ",
        "ખાલી યાદીમાંથી ઘટક કાઢી શકાતો નથી",
        "કેસ રૂપાંતરણ માટે લખાણ દલીલ અપેક્ષિત છે",
        "ગણિત ફંક્શન માટે સંખ્યા દલીલો જરૂરી છે",
        "'ઉલટાવો' માટે યાદી દલીલ અપેક્ષિત છે",
        "'ભાગ' માટે લખાણરૂપ દલીલો અપેક્ષિત છે",
        "'જોડો' માટે યાદી અને વિભાજક લખાણ જરૂરી છે",
        "'સાફ' માટે લખાણ દલીલ અપેક્ષિત છે",
        "ઋણ સંખ્યાનું વર્ગમૂળ કાઢી શકાતું નથી",
        "'ગોઠવો' માટે યાદી દલીલ અપેક્ષિત છે",
        "'બદલો' માટે લખાણરૂપ દલીલો અપેક્ષિત છે",
        "શરૂઆત/અંત ચકાસણી માટે લખાણરૂપ દલીલો અપેક્ષિત છે",
        "'સમાવે_છે' માટે પ્રથમ દલીલ યાદી હોવી જોઈએ",
        "'પુનરાવર્તન' માટે પ્રથમ દલીલ લખાણ હોવી જોઈએ",
        "'પુનરાવર્તન' માટે ગણતરી શૂન્ય અથવા ધન પૂર્ણાંક હોવી જોઈએ",
        "'ટુકડો' માટે પ્રથમ દલીલ યાદી હોવી જોઈએ",
        "'ટુકડો' માટે અનુક્રમ શૂન્ય અથવા ધન પૂર્ણાંક હોવા જોઈએ",
        "'સ્થાન' માટે પ્રથમ દલીલ યાદી હોવી જોઈએ",
        "'સ્થાન' માટે શરૂઆતનો અનુક્રમ શૂન્ય અથવા ધન પૂર્ણાંક હોવો જોઈએ",
        "'મૂકો' માટે પ્રથમ દલીલ યાદી હોવી જોઈએ",
        "'મૂકો' માટે ઉમેરવાનો અનુક્રમ શૂન્ય અથવા ધન પૂર્ણાંક હોવો જોઈએ",
        "'મૂકો' માટે અનુક્રમ યાદીની મર્યાદા બહાર છે",
        "પેડિંગ માટે પ્રથમ દલીલ લખાણ હોવી જોઈએ",
        "પેડિંગ માટે પહોળાઈ શૂન્ય અથવા ધન પૂર્ણાંક હોવી જોઈએ",
        "પેડિંગ માટે પેડ કેરેક્ટર લખાણ હોવું જોઈએ",
        "'સીમા' માટે ન્યૂનતમ સીમા મહત્તમ સીમા કરતાં મોટી ન હોઈ શકે",
        "'યાદચ્છિક' માટે ન્યૂનતમ સીમા મહત્તમ સીમા કરતાં મોટી ન હોઈ શકે",
        "'યાદચ્છિક' માટે સીમાઓ પૂર્ણાંક સંખ્યા હોવી જોઈએ",
        "'વિસ્તારો' માટે બંને દલીલો યાદી હોવી જોઈએ",
        "લઘુગણક માટે કિંમત શૂન્ય કરતાં મોટી હોવી જોઈએ",
        "લઘુગણક આધાર શૂન્ય કરતાં મોટો અને એક સિવાયનો હોવો જોઈએ",
        "'અક્ષર_કોડ' માટે પ્રથમ દલીલ લખાણ હોવી જોઈએ",
        "'અક્ષર_કોડ' માટે અનુક્રમ શૂન્ય અથવા ધન પૂર્ણાંક હોવો જોઈએ",
        "'અક્ષર_કોડ' માટે અનુક્રમ લખાણની મર્યાદા બહાર છે",
        "'કોડ_થી_અક્ષર' માટે અમાન્ય યુનિકોડ કોડ પોઈન્ટ",
        "'યાદી_ભરો' માટે ગણતરી શૂન્ય અથવા ધન પૂર્ણાંક હોવી જોઈએ",
        "'સરવાળો_યાદી' માટે યાદી દલીલ અપેક્ષિત છે",
        "'સરવાળો_યાદી' માટે યાદીના તમામ ઘટકો સંખ્યા હોવા જોઈએ",
        "'યાદી_ન્યૂનતમ' માટે યાદી દલીલ અપેક્ષિત છે",
        "ખાલી યાદીમાંથી ન્યૂનતમ શોધી શકાતું નથી",
        "'યાદી_ન્યૂનતમ' માટે તમામ ઘટકો સંખ્યા હોવા જોઈએ",
        "'યાદી_મહત્તમ' માટે યાદી દલીલ અપેક્ષિત છે",
        "ખાલી યાદીમાંથી મહત્તમ શોધી શકાતું નથી",
        "'યાદી_મહત્તમ' માટે તમામ ઘટકો સંખ્યા હોવા જોઈએ",
        "'ગણતરી' માટે પ્રથમ દલીલ યાદી અથવા લખાણ હોવી જોઈએ",
        "લખાણમાં ગણતરી કરતી વખતે બીજી દલીલ લખાણ હોવી જોઈએ",
        "'ડાબે_કાપો' માટે લખાણ દલીલ અપેક્ષિત છે",
        "'જમણે_કાપો' માટે લખાણ દલીલ અપેક્ષિત છે",
        "'વિભાજન_પંક્તિ' માટે લખાણ દલીલ અપેક્ષિત છે",
        "'અક્ષરો' માટે લખાણ દલીલ અપેક્ષિત છે",
        "'પર્યાવરણ' માટે લખાણ દલીલ અપેક્ષિત છે",
        "'બહાર' માટે એક્ઝિટ કોડ ૦ અને ૨૫૫ વચ્ચેનો પૂર્ણ આંક હોવો જોઈએ",
        "ચકાસણી નિષ્ફળતા સંદેશ લખાણ હોવો જોઈએ",
        "ચકાસણી નિષ્ફળ ગઈ",
        "'સમાવે_લખાણ' માટે લખાણ દલીલો અપેક્ષિત છે",
        "ફાઇલ પાથ માટે લખાણ હોવું જરૂરી છે",
        "ફાઇલ સામગ્રી માટે લખાણ હોવું જરૂરી છે",
        "શબ્દકોશ ચાવી પછી ':' અપેક્ષિત છે",
        "શબ્દકોશની ચાવી લખાણ હોવી જોઈએ",
        "'શબ્દકોશ' માટે બેકી સંખ્યામાં ચાવી-મૂલ્ય દલીલો અપેક્ષિત છે",
        "શબ્દકોશ દલીલ અપેક્ષિત છે",
        "'અટકો' નો ઉપયોગ ફક્ત લૂપની અંદર થઈ શકે છે",
        "'ચાલુ_રાખો' નો ઉપયોગ ફક્ત લૂપની અંદર થઈ શકે છે",
        "'પ્રયત્ન' બ્લોક પછી 'પકડો' બ્લોક અપેક્ષિત છે",
        "'ફેંકો' માટે લખાણ દલીલ અપેક્ષિત છે",
        "'તારીખ' માટે ફોર્મેટ લખાણ હોવું જોઈએ",
        "સમયમુદ્રા સંખ્યા હોવી જોઈએ",
        "વિરામ સમય મિલિસેકન્ડ્સમાં અનૃણ સંખ્યા હોવી જોઈએ",
        "ત્રિપદી શરતમાં ':' અપેક્ષિત છે",
        "અચળ ચલને ફરીથી બદલી શકાતો નથી",
        "આ નામવાળો ચલ પહેલેથી ઘોષિત થયેલ છે",
        "જેસન લખાણ અપેક્ષિત છે",
        "અમાન્ય જેસન રચના",
        "સંખ્યા રૂપાંતરણ માટે પૂર્ણાંક અપેક્ષિત છે",
        "રૂપાંતરણ માટે લખાણ અપેક્ષિત છે",
        "'નકશો_યાદી' માટે કાર્ય અપેક્ષિત છે",
        "'ગાળો_યાદી' માટે કાર્ય અપેક્ષિત છે",
        "'સમેટો_યાદી' માટે કાર્ય અપેક્ષિત છે",
        "'શોધો_યાદી' માટે કાર્ય અપેક્ષિત છે",
        "ચપટી યાદી માટે યાદી અપેક્ષિત છે",
        "'ઝીપ_યાદી' માટે બે યાદીઓ અપેક્ષિત છે",
        "બેઝ૬૪ માટે લખાણ અપેક્ષિત છે",
        "અમાન્ય બેઝ૬૪ સામગ્રી",
        "પેટર્ન શોધ માટે લખાણ અપેક્ષિત છે",
        "અંતર ગણતરી માટે લખાણ દલીલો અપેક્ષિત છે",
        "સુસંગત પરિમાણવાળા મેટ્રિક્સ અપેક્ષિત છે",
        "ઉપયોગ: %s [--language en|gu] <source.gj> | [--language en|gu] --repl"
    };

    if (language == LANGUAGE_GUJARATI) {
        return gujarati_messages[message];
    }
    return english_messages[message];
}

static char *copy_string(const char *text);

static void report_error(Parser *parser, size_t line, size_t column,
                         MessageId message)
{
    if (parser->in_try) {
        if (!parser->error_caught) {
            const char *msg_str = localized_message(parser->language, message);
            free(parser->last_error_message);
            parser->last_error_message = copy_string(msg_str);
            parser->error_caught = 1;
        }
        return;
    }
    if (!parser->failed) {
        const char *label = parser->language == LANGUAGE_GUJARATI ?
                            "ભૂલ" : "error";
        fprintf(stderr, "%s:%zu:%zu: %s: %s\n",
                parser->filename, line, column, label,
                localized_message(parser->language, message));
        write_source_context(parser, line, column);
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
    static const struct {
        const char *text;
        TokenKind kind;
    } keywords[] = {
        {"નહિતર જો", TOKEN_ELSE_IF},
        {"ઘાતક ભૂલ", TOKEN_FATAL_ERROR},
        {"નહિતર", TOKEN_ELSE},
        {"અથવા", TOKEN_OR},
        {"ચેતવણી", TOKEN_WARNING},
        {"કાર્ય", TOKEN_FUNCTION},
        {"આવજો", TOKEN_END},
        {"જ્યાં સુધી", TOKEN_WHILE},
        {"છાપો", TOKEN_PRINT},
        {"આવો", TOKEN_START},
        {"નહીં", TOKEN_NOT},
        {"નકામો", TOKEN_NULL},
        {"ભૂલ", TOKEN_ERROR},
        {"પરત", TOKEN_RETURN},
        {"જો", TOKEN_IF},
        {"અને", TOKEN_AND},
        {"nahitar_jo", TOKEN_ELSE_IF},
        {"ghatak_bhul", TOKEN_FATAL_ERROR},
        {"jya_sudhi", TOKEN_WHILE},
        {"chetavani", TOKEN_WARNING},
        {"aavjo", TOKEN_END},
        {"દરેક", TOKEN_FOR},
        {"માં", TOKEN_IN},
        {"chhapo", TOKEN_PRINT},
        {"nahitar", TOKEN_ELSE},
        {"athva", TOKEN_OR},
        {"nakamo", TOKEN_NULL},
        {"kary", TOKEN_FUNCTION},
        {"parat", TOKEN_RETURN},
        {"aavo", TOKEN_START},
        {"ane", TOKEN_AND},
        {"nahi", TOKEN_NOT},
        {"bhul", TOKEN_ERROR},
        {"jo", TOKEN_IF},
        {"darek", TOKEN_FOR},
        {"ma", TOKEN_IN},
        {"આયાત", TOKEN_IMPORT},
        {"aayat", TOKEN_IMPORT},
        {"import", TOKEN_IMPORT},
        {"ચાલુ_રાખો", TOKEN_CONTINUE},
        {"chalu_rakho", TOKEN_CONTINUE},
        {"આગળ", TOKEN_CONTINUE},
        {"aagal", TOKEN_CONTINUE},
        {"અટકો", TOKEN_BREAK},
        {"atko", TOKEN_BREAK},
        {"પ્રયત્ન", TOKEN_TRY},
        {"prayatna", TOKEN_TRY},
        {"પકડો", TOKEN_CATCH},
        {"pakdo", TOKEN_CATCH},
        {"અચળ", TOKEN_CONST},
        {"achala", TOKEN_CONST},
        {"const", TOKEN_CONST}
    };
    Token token;
    size_t start;
    size_t keyword_index;
    char character;

    skip_whitespace_and_comments(parser);
    token = make_token(TOKEN_EOF, parser->line, parser->column);
    token.source_offset = parser->offset;
    character = peek(parser);
    if (character == '\0') {
        return token;
    }

    for (keyword_index = 0;
         keyword_index < sizeof(keywords) / sizeof(keywords[0]);
         keyword_index++) {
        size_t length;
        if (!keyword_matches(parser, keywords[keyword_index].text)) {
            continue;
        }
        length = strlen(keywords[keyword_index].text);
        while (length > 0) {
            advance_char(parser);
            length--;
        }
        token.kind = keywords[keyword_index].kind;
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
        if (end > parser->source + start && end[-1] == '.' && *end == '.') {
            end--;
        }
        while (parser->source + parser->offset < end) {
            advance_char(parser);
        }
        token.kind = TOKEN_NUMBER;
        return token;
    }

    advance_char(parser);
    switch (character) {
    case '+':
        if (peek(parser) == '=') {
            advance_char(parser);
            token.kind = TOKEN_PLUS_EQUAL;
        } else {
            token.kind = TOKEN_PLUS;
        }
        break;
    case '-':
        if (peek(parser) == '=') {
            advance_char(parser);
            token.kind = TOKEN_MINUS_EQUAL;
        } else {
            token.kind = TOKEN_MINUS;
        }
        break;
    case '*':
        if (peek(parser) == '=') {
            advance_char(parser);
            token.kind = TOKEN_STAR_EQUAL;
        } else {
            token.kind = TOKEN_STAR;
        }
        break;
    case '/':
        if (peek(parser) == '=') {
            advance_char(parser);
            token.kind = TOKEN_SLASH_EQUAL;
        } else {
            token.kind = TOKEN_SLASH;
        }
        break;
    case '%':
        if (peek(parser) == '=') {
            advance_char(parser);
            token.kind = TOKEN_PERCENT_EQUAL;
        } else {
            token.kind = TOKEN_PERCENT;
        }
        break;
    case '?':
        token.kind = TOKEN_QUESTION;
        break;
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
    case '.':
        if (peek(parser) == '.') {
            advance_char(parser);
            token.kind = TOKEN_RANGE;
        } else {
            report_error(parser, token.line, token.column,
                         MESSAGE_UNEXPECTED_CHARACTER);
            token.kind = TOKEN_INVALID;
        }
        break;
    case '[': token.kind = TOKEN_LEFT_BRACKET; break;
    case ']': token.kind = TOKEN_RIGHT_BRACKET; break;
    case '{': token.kind = TOKEN_LEFT_BRACE; break;
    case '}': token.kind = TOKEN_RIGHT_BRACE; break;
    case ';': token.kind = TOKEN_SEMICOLON; break;
    case ':': token.kind = TOKEN_COLON; break;
    case '&':
        if (peek(parser) == '&') {
            advance_char(parser);
            token.kind = TOKEN_AND;
        } else {
            report_error(parser, token.line, token.column,
                         MESSAGE_UNEXPECTED_CHARACTER);
            token.kind = TOKEN_INVALID;
        }
        break;
    case '|':
        if (peek(parser) == '|') {
            advance_char(parser);
            token.kind = TOKEN_OR;
        } else {
            report_error(parser, token.line, token.column,
                         MESSAGE_UNEXPECTED_CHARACTER);
            token.kind = TOKEN_INVALID;
        }
        break;
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

static unsigned long long prng_state = 0;
static int prng_initialized = 0;

static void set_prng_seed(unsigned long long seed)
{
    if (seed == 0) {
        seed = 0x853c49e6748fea9bULL;
    }
    prng_state = seed;
    prng_initialized = 1;
}

static void ensure_prng_initialized(void)
{
    if (!prng_initialized) {
        unsigned long long t = (unsigned long long)time(NULL);
        set_prng_seed((t ^ 0x5a17e29b9ULL) + 0xda942042e4dd58b5ULL);
    }
}

static double next_random_double(void)
{
    ensure_prng_initialized();
    prng_state ^= prng_state << 13;
    prng_state ^= prng_state >> 7;
    prng_state ^= prng_state << 17;
    return (double)(prng_state >> 11) * (1.0 / 9007199254740992.0);
}

static Value number_value(double number)
{
    Value value;
    value.kind = VALUE_NUMBER;
    value.number = number;
    value.string_offset = 0;
    value.string_length = 0;
    value.owned_string = NULL;
    value.string_source = NULL;
    value.list = NULL;
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
                memcmp(variable->name,
                       parser->source + name.string_offset,
                       name.string_length) == 0) {
                return variable;
            }
        }
    }
    return NULL;
}

static int declare_variable_ex(Parser *parser, Token name, Value value, int is_constant)
{
    Environment *environment = parser->environment;
    Variable *variables;
    char *variable_name;
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

    variable_name = (char *)malloc(name.string_length + 1);
    if (variable_name == NULL) {
        report_error(parser, name.line, name.column,
                     MESSAGE_OUT_OF_MEMORY_FOR_VARIABLE);
        return 0;
    }
    memcpy(variable_name, parser->source + name.string_offset,
           name.string_length);
    variable_name[name.string_length] = '\0';
    environment->variables[environment->variable_count].name = variable_name;
    environment->variables[environment->variable_count].name_length =
        name.string_length;
    environment->variables[environment->variable_count].value = value;
    environment->variables[environment->variable_count].is_constant = is_constant;
    environment->variable_count++;
    return 1;
}

static int declare_variable(Parser *parser, Token name, Value value)
{
    return declare_variable_ex(parser, name, value, 0);
}

static int assign_variable(Parser *parser, Token name, Value value)
{
    Variable *variable = find_variable(parser, name);
    if (variable == NULL) {
        report_error(parser, name.line, name.column,
                     MESSAGE_UNDEFINED_VARIABLE);
        return 0;
    }
    if (variable->is_constant) {
        report_error(parser, name.line, name.column,
                     MESSAGE_CANNOT_REASSIGN_CONSTANT);
        return 0;
    }
    variable->value = value;
    return 1;
}

static Value parse_expression(Parser *parser, int execute);
static Value parse_additive(Parser *parser, int execute);
static int value_is_truthy(Value value);
static int parse_block(Parser *parser, int execute);
static List *create_list(Parser *parser, Token token);
static int append_list_item(Parser *parser, List *list, Value value,
                            Token token);
static int resolve_list_index(Parser *parser, Value list_value,
                              Value index_value, Token token, size_t *index);

static Value null_value(void)
{
    Value value = number_value(0.0);
    value.kind = VALUE_NULL;
    return value;
}

static Function *find_function(Parser *parser, Token name)
{
    size_t index;
    for (index = 0; index < parser->function_table->count; index++) {
        Function *function = &parser->function_table->items[index];
        if (function->name_length == name.string_length &&
            memcmp(function->name,
                   parser->source + name.string_offset,
                   name.string_length) == 0) {
            return function;
        }
    }
    return NULL;
}

static Function *find_function_by_name(Parser *parser, const char *name, size_t length)
{
    size_t index;
    for (index = 0; index < parser->function_table->count; index++) {
        Function *function = &parser->function_table->items[index];
        if (function->name_length == length &&
            memcmp(function->name, name, length) == 0) {
            return function;
        }
    }
    return NULL;
}

static int write_string(Parser *parser, FILE *output, const char *source,
                        size_t offset, size_t length);

static int token_matches(Parser *parser, Token token, const char *text)
{
    size_t length = strlen(text);
    return token.string_length == length &&
           memcmp(parser->source + token.string_offset, text, length) == 0;
}

static int is_builtin_function_name(Parser *parser, Token name)
{
    return token_matches(parser, name, "વાંચો") ||
           token_matches(parser, name, "vancho") ||
           token_matches(parser, name, "લંબાઈ") ||
           token_matches(parser, name, "lambai") ||
           token_matches(parser, name, "સંખ્યા") ||
           token_matches(parser, name, "sankhya") ||
           token_matches(parser, name, "લખાણ") ||
           token_matches(parser, name, "lakhan") ||
           token_matches(parser, name, "પ્રકાર") ||
           token_matches(parser, name, "prakar") ||
           token_matches(parser, name, "ઉમેરો") ||
           token_matches(parser, name, "umero") ||
           token_matches(parser, name, "કાપો") ||
           token_matches(parser, name, "kapo") ||
           token_matches(parser, name, "શોધો") ||
           token_matches(parser, name, "shodho") ||
           token_matches(parser, name, "કાઢો") ||
           token_matches(parser, name, "kadho") ||
           token_matches(parser, name, "પહેલી_એબીસીડી") ||
           token_matches(parser, name, "peli_abcd") ||
           token_matches(parser, name, "બીજી_એબીસીડી") ||
           token_matches(parser, name, "biji_abcd") ||
           token_matches(parser, name, "મહત્તમ") ||
           token_matches(parser, name, "mahatam") ||
           token_matches(parser, name, "ન્યૂનતમ") ||
           token_matches(parser, name, "nyunatam") ||
           token_matches(parser, name, "ધન_મૂલ્ય") ||
           token_matches(parser, name, "dhan_mulya") ||
           token_matches(parser, name, "ઉલટાવો") ||
           token_matches(parser, name, "ultavo") ||
           token_matches(parser, name, "ભાગ") ||
           token_matches(parser, name, "bhag") ||
           token_matches(parser, name, "જોડો") ||
           token_matches(parser, name, "jodo") ||
           token_matches(parser, name, "સાફ") ||
           token_matches(parser, name, "saf") ||
           token_matches(parser, name, "ઘાત") ||
           token_matches(parser, name, "ghat") ||
           token_matches(parser, name, "મૂળ") ||
           token_matches(parser, name, "mul") ||
           token_matches(parser, name, "ગોઠવો") ||
           token_matches(parser, name, "gothvo") ||
           token_matches(parser, name, "બદલો") ||
           token_matches(parser, name, "badlo") ||
           token_matches(parser, name, "શરૂઆત_સાથે") ||
           token_matches(parser, name, "sharuat_sathe") ||
           token_matches(parser, name, "અંત_સાથે") ||
           token_matches(parser, name, "ant_sathe") ||
           token_matches(parser, name, "સમાવે_છે") ||
           token_matches(parser, name, "samave_chhe") ||
           token_matches(parser, name, "ગોળ") ||
           token_matches(parser, name, "gol") ||
           token_matches(parser, name, "નીચે") ||
           token_matches(parser, name, "niche") ||
           token_matches(parser, name, "ઉપર") ||
           token_matches(parser, name, "upar") ||
           token_matches(parser, name, "પુનરાવર્તન") ||
           token_matches(parser, name, "punravartan") ||
           token_matches(parser, name, "ટુકડો") ||
           token_matches(parser, name, "tukdo") ||
           token_matches(parser, name, "સ્થાન") ||
           token_matches(parser, name, "sthan") ||
           token_matches(parser, name, "મૂકો") ||
           token_matches(parser, name, "muko") ||
           token_matches(parser, name, "ડાબે_ભરો") ||
           token_matches(parser, name, "dabe_bharo") ||
           token_matches(parser, name, "જમણે_ભરો") ||
           token_matches(parser, name, "jamne_bharo") ||
           token_matches(parser, name, "સીમા") ||
           token_matches(parser, name, "sima") ||
           token_matches(parser, name, "યાદચ્છિક") ||
           token_matches(parser, name, "yadachhik") ||
           token_matches(parser, name, "બીજ") ||
           token_matches(parser, name, "beej") ||
           token_matches(parser, name, "વિસ્તારો") ||
           token_matches(parser, name, "vistaro") ||
           token_matches(parser, name, "પાઈ") ||
           token_matches(parser, name, "pi") ||
           token_matches(parser, name, "ઈ") ||
           token_matches(parser, name, "e") ||
           token_matches(parser, name, "ચિહ્ન") ||
           token_matches(parser, name, "chihna") ||
           token_matches(parser, name, "લઘુગણક") ||
           token_matches(parser, name, "laghuganak") ||
           token_matches(parser, name, "અક્ષર_કોડ") ||
           token_matches(parser, name, "akshar_kod") ||
           token_matches(parser, name, "કોડ_થી_અક્ષર") ||
           token_matches(parser, name, "kod_thi_akshar") ||
           token_matches(parser, name, "યાદી_ભરો") ||
           token_matches(parser, name, "yadi_bharo") ||
           token_matches(parser, name, "સરવાળો_યાદી") ||
           token_matches(parser, name, "sarvalo_yadi") ||
           token_matches(parser, name, "યાદી_ન્યૂનતમ") ||
           token_matches(parser, name, "yadi_nyunatam") ||
           token_matches(parser, name, "યાદી_મહત્તમ") ||
           token_matches(parser, name, "yadi_mahatam") ||
           token_matches(parser, name, "ગણતરી") ||
           token_matches(parser, name, "ganatari") ||
           token_matches(parser, name, "ગણતરી_વસ્તુ") ||
           token_matches(parser, name, "ganatari_vastu") ||
           token_matches(parser, name, "ડાબે_કાપો") ||
           token_matches(parser, name, "dabe_kapo") ||
           token_matches(parser, name, "ડાબે_સાફ") ||
           token_matches(parser, name, "dabe_saf") ||
           token_matches(parser, name, "જમણે_કાપો") ||
           token_matches(parser, name, "jamne_kapo") ||
           token_matches(parser, name, "જમણે_સાફ") ||
           token_matches(parser, name, "jamne_saf") ||
           token_matches(parser, name, "વિભાજન_પંક્તિ") ||
           token_matches(parser, name, "vibhaajan_pankti") ||
           token_matches(parser, name, "પંક્તિઓ") ||
           token_matches(parser, name, "panktiyo") ||
           token_matches(parser, name, "પંક્તિ_ભાગ") ||
           token_matches(parser, name, "pankti_bhag") ||
           token_matches(parser, name, "અક્ષરો") ||
           token_matches(parser, name, "aksharo") ||
           token_matches(parser, name, "પર્યાવરણ") ||
           token_matches(parser, name, "paryavaran") ||
           token_matches(parser, name, "બહાર") ||
           token_matches(parser, name, "bahar") ||
           token_matches(parser, name, "ચકાસો") ||
           token_matches(parser, name, "chakaso") ||
           token_matches(parser, name, "સમાવે_લખાણ") ||
           token_matches(parser, name, "samave_lakhan") ||
           token_matches(parser, name, "ફાઇલ_વાંચો") ||
           token_matches(parser, name, "file_vancho") ||
           token_matches(parser, name, "ફાઇલ_લખો") ||
           token_matches(parser, name, "file_lakho") ||
           token_matches(parser, name, "ફાઇલ_ઉમેરો") ||
           token_matches(parser, name, "file_umero") ||
           token_matches(parser, name, "ફાઇલ_છે") ||
           token_matches(parser, name, "file_chhe") ||
           token_matches(parser, name, "ફાઇલ_કાઢો") ||
           token_matches(parser, name, "file_kadho") ||
           token_matches(parser, name, "ફાઇલ_હટાવો") ||
           token_matches(parser, name, "file_hatao") ||
           token_matches(parser, name, "ફાઇલ_કદ") ||
           token_matches(parser, name, "file_kad") ||
           token_matches(parser, name, "શબ્દકોશ") ||
           token_matches(parser, name, "shabdakosh") ||
           token_matches(parser, name, "કોશ") ||
           token_matches(parser, name, "kosh") ||
           token_matches(parser, name, "ચાવીઓ") ||
           token_matches(parser, name, "chavio") ||
           token_matches(parser, name, "ચાવી") ||
           token_matches(parser, name, "chavi") ||
           token_matches(parser, name, "મૂલ્યો") ||
           token_matches(parser, name, "mulyo") ||
           token_matches(parser, name, "દૂર_કરો") ||
           token_matches(parser, name, "dur_karo") ||
           token_matches(parser, name, "કોશ_દૂર") ||
           token_matches(parser, name, "kosh_dur") ||
           token_matches(parser, name, "સમય") ||
           token_matches(parser, name, "samay") ||
           token_matches(parser, name, "તારીખ") ||
           token_matches(parser, name, "tarikh") ||
           token_matches(parser, name, "વર્ષ") ||
           token_matches(parser, name, "varsh") ||
           token_matches(parser, name, "મહિનો") ||
           token_matches(parser, name, "mahino") ||
           token_matches(parser, name, "દિવસ") ||
           token_matches(parser, name, "divas") ||
           token_matches(parser, name, "કલાક") ||
           token_matches(parser, name, "kalak") ||
           token_matches(parser, name, "મિનિટ") ||
           token_matches(parser, name, "minute") ||
           token_matches(parser, name, "સેકન્ડ") ||
           token_matches(parser, name, "second") ||
           token_matches(parser, name, "શાંત") ||
           token_matches(parser, name, "shant") ||
           token_matches(parser, name, "રાહ_જુઓ") ||
           token_matches(parser, name, "raah_juo") ||
           token_matches(parser, name, "ફેંકો") ||
           token_matches(parser, name, "phenko") ||
           token_matches(parser, name, "જેસન_વાંચો") ||
           token_matches(parser, name, "json_vancho") ||
           token_matches(parser, name, "જેસન_લખો") ||
           token_matches(parser, name, "json_lakho") ||
           token_matches(parser, name, "દલીલો") ||
           token_matches(parser, name, "daleelo") ||
           token_matches(parser, name, "દલીલ_યાદી") ||
           token_matches(parser, name, "arg_yadi") ||
           token_matches(parser, name, "દ્વિ_સંખ્યા") ||
           token_matches(parser, name, "dvi_sankhya") ||
           token_matches(parser, name, "દ્વિ_થી_સંખ્યા") ||
           token_matches(parser, name, "dvi_thi_sankhya") ||
           token_matches(parser, name, "હેક્સ_લખાણ") ||
           token_matches(parser, name, "hex_lakhan") ||
           token_matches(parser, name, "હેક્સ_થી_સંખ્યા") ||
           token_matches(parser, name, "hex_thi_sankhya") ||
           token_matches(parser, name, "ફોલ્ડર_છે") ||
           token_matches(parser, name, "folder_chhe") ||
           token_matches(parser, name, "ફોલ્ડર_બનાવો") ||
           token_matches(parser, name, "folder_banao") ||
           token_matches(parser, name, "ફોલ્ડર_સૂચિ") ||
           token_matches(parser, name, "folder_suchi") ||
           token_matches(parser, name, "કમાન્ડ_ચલાવો") ||
           token_matches(parser, name, "command_chalao") ||
           token_matches(parser, name, "સિસ્ટમ") ||
           token_matches(parser, name, "system_kary") ||
           token_matches(parser, name, "નકશો_યાદી") ||
           token_matches(parser, name, "naksho_yadi") ||
           token_matches(parser, name, "ગાળો_યાદી") ||
           token_matches(parser, name, "gaalo_yadi") ||
           token_matches(parser, name, "સમેટો_યાદી") ||
           token_matches(parser, name, "sameto_yadi") ||
           token_matches(parser, name, "શોધો_યાદી") ||
           token_matches(parser, name, "shodho_yadi") ||
           token_matches(parser, name, "શોધો_સૂચક_યાદી") ||
           token_matches(parser, name, "shodho_suchak_yadi") ||
           token_matches(parser, name, "ચપટી_યાદી") ||
           token_matches(parser, name, "chapti_yadi") ||
           token_matches(parser, name, "ઝીપ_યાદી") ||
           token_matches(parser, name, "zip_yadi") ||
           token_matches(parser, name, "પેટર્ન_શોધો") ||
           token_matches(parser, name, "pattern_shodho") ||
           token_matches(parser, name, "લખાણ_બદલો_દરેક") ||
           token_matches(parser, name, "lakhan_badlo_darek") ||
           token_matches(parser, name, "બેઝ૬૪_કોડ") ||
           token_matches(parser, name, "base64_kod") ||
           token_matches(parser, name, "બેઝ૬૪_ડીકોડ") ||
           token_matches(parser, name, "base64_decode") ||
           token_matches(parser, name, "શીર્ષક_લખાણ") ||
           token_matches(parser, name, "shirshak_lakhan") ||
           token_matches(parser, name, "પ્રથમ_મોટી") ||
           token_matches(parser, name, "pratham_moti") ||
           token_matches(parser, name, "સ્વરૂપ") ||
           token_matches(parser, name, "swaroop") ||
           token_matches(parser, name, "લખાણ_અંતર") ||
           token_matches(parser, name, "lakhan_antar") ||
           token_matches(parser, name, "શા૨૫૬_હેશ") ||
           token_matches(parser, name, "sha256_hash") ||
           token_matches(parser, name, "સાઇન") ||
           token_matches(parser, name, "sine") ||
           token_matches(parser, name, "કોસાઇન") ||
           token_matches(parser, name, "cosine") ||
           token_matches(parser, name, "ટેન્જન્ટ") ||
           token_matches(parser, name, "tangent") ||
           token_matches(parser, name, "આર્કસાઇન") ||
           token_matches(parser, name, "arcsin") ||
           token_matches(parser, name, "આર્કકોસ") ||
           token_matches(parser, name, "arccos") ||
           token_matches(parser, name, "આર્કટેન") ||
           token_matches(parser, name, "arctan") ||
           token_matches(parser, name, "ગુરુ_તમ") ||
           token_matches(parser, name, "guru_tam") ||
           token_matches(parser, name, "લઘુ_તમ") ||
           token_matches(parser, name, "laghu_tam") ||
           token_matches(parser, name, "અંશ_થી_રેડિયન") ||
           token_matches(parser, name, "ansha_thi_radian") ||
           token_matches(parser, name, "રેડિયન_થી_અંશ") ||
           token_matches(parser, name, "radian_thi_ansha") ||
           token_matches(parser, name, "મેટ્રિક્સ_સરવાળો") ||
           token_matches(parser, name, "matrix_sarvalo") ||
           token_matches(parser, name, "મેટ્રિક્સ_ગુણાકાર") ||
           token_matches(parser, name, "matrix_gunakar") ||
           token_matches(parser, name, "ભાષા_આવૃત્તિ") ||
           token_matches(parser, name, "bhasha_avrutti") ||
           token_matches(parser, name, "પ્લેટફોર્મ_નામ") ||
           token_matches(parser, name, "platform_nam") ||
           token_matches(parser, name, "પર્યાવરણ") ||
           token_matches(parser, name, "paryavaran") ||
           token_matches(parser, name, "પર્યાવરણ_લખો") ||
           token_matches(parser, name, "paryavaran_lakho") ||
           token_matches(parser, name, "પાથ_જોડો") ||
           token_matches(parser, name, "path_jodo") ||
           token_matches(parser, name, "પાથ_વિસ્તરણ") ||
           token_matches(parser, name, "path_vistaran") ||
           token_matches(parser, name, "પાથ_મુખ્ય") ||
           token_matches(parser, name, "path_mukhya") ||
           token_matches(parser, name, "પાથ_ફોલ્ડર") ||
           token_matches(parser, name, "path_folder") ||
           token_matches(parser, name, "યુયુઆઈડી_બનાવો") ||
           token_matches(parser, name, "uuid_banao") ||
           token_matches(parser, name, "યુઆરએલ_કોડ") ||
           token_matches(parser, name, "url_kod") ||
           token_matches(parser, name, "યુઆરએલ_ડીકોડ") ||
           token_matches(parser, name, "url_decode") ||
           token_matches(parser, name, "યાદી_સરવાળો") ||
           token_matches(parser, name, "yadi_sarvalo") ||
           token_matches(parser, name, "યાદી_સરેરાશ") ||
           token_matches(parser, name, "yadi_sareras") ||
           token_matches(parser, name, "યાદી_મધ્યસ્થ") ||
           token_matches(parser, name, "yadi_madhyastha") ||
           token_matches(parser, name, "લેખન_પૂર્ણ_ડાબી") ||
           token_matches(parser, name, "lakhan_purn_dabi") ||
           token_matches(parser, name, "લેખન_પૂર્ણ_જમણી") ||
           token_matches(parser, name, "lakhan_purn_jamni") ||
           token_matches(parser, name, "બીટ_અને") ||
           token_matches(parser, name, "bit_ane") ||
           token_matches(parser, name, "બીટ_અથવા") ||
           token_matches(parser, name, "bit_athva") ||
           token_matches(parser, name, "બીટ_એક્સઓર") ||
           token_matches(parser, name, "bit_xor") ||
           token_matches(parser, name, "બીટ_નહિ") ||
           token_matches(parser, name, "bit_nahi") ||
           token_matches(parser, name, "બીટ_શિફ્ટ_ડાબી") ||
           token_matches(parser, name, "bit_shifte_dabi") ||
           token_matches(parser, name, "બીટ_શિફ્ટ_જમણી") ||
           token_matches(parser, name, "bit_shifte_jamni") ||
           token_matches(parser, name, "યાદી_અનન્ય") ||
           token_matches(parser, name, "yadi_ananya") ||
           token_matches(parser, name, "યાદી_મેળ") ||
           token_matches(parser, name, "yadi_mel") ||
           token_matches(parser, name, "યાદી_છેદ") ||
           token_matches(parser, name, "yadi_chhed") ||
           token_matches(parser, name, "યાદી_તફાવત") ||
           token_matches(parser, name, "yadi_tavat") ||
           token_matches(parser, name, "અક્ષર_કોડ") ||
           token_matches(parser, name, "akshar_kod") ||
           token_matches(parser, name, "કોડ_થી_અક્ષર") ||
           token_matches(parser, name, "kod_thi_akshar") ||
           token_matches(parser, name, "લૉગ_કુદરતી") ||
           token_matches(parser, name, "log_kudrati") ||
           token_matches(parser, name, "લૉગ_૧૦") ||
           token_matches(parser, name, "log_10") ||
           token_matches(parser, name, "ઘાત_મૂળ") ||
           token_matches(parser, name, "ghat_mul") ||
           token_matches(parser, name, "ઈ_ઘાત") ||
           token_matches(parser, name, "e_ghat") ||
           token_matches(parser, name, "યાદી_ઊલટે_ક્રમ") ||
           token_matches(parser, name, "yadi_ulte_kram") ||
           token_matches(parser, name, "યાદી_ટુકડા") ||
           token_matches(parser, name, "yadi_tukda") ||
           token_matches(parser, name, "યાદી_ખીચડી") ||
           token_matches(parser, name, "yadi_khichdi") ||
           token_matches(parser, name, "ચાવી_છે") ||
           token_matches(parser, name, "chavi_chhe") ||
           token_matches(parser, name, "કોશ_જોડો") ||
           token_matches(parser, name, "kosh_jodo") ||
           token_matches(parser, name, "માઇક્રો_સમય") ||
           token_matches(parser, name, "micro_samay") ||
           token_matches(parser, name, "લેખન_આવૃત્તિ") ||
           token_matches(parser, name, "lakhan_aavrutti") ||
           token_matches(parser, name, "લેખન_ગણતરી") ||
           token_matches(parser, name, "lakhan_ganatari") ||
           token_matches(parser, name, "લેખન_ટુકડા_યાદી") ||
           token_matches(parser, name, "lakhan_tukda_yadi") ||
           token_matches(parser, name, "ફાઇલ_લાઇન_વાંચો") ||
           token_matches(parser, name, "file_line_vancho") ||
           token_matches(parser, name, "હેક્સ_થી_લેખન") ||
           token_matches(parser, name, "hex_thi_lakhan") ||
           token_matches(parser, name, "સીએસવી_વાંચો") ||
           token_matches(parser, name, "csv_vancho") ||
           token_matches(parser, name, "સંખ્યા_છે") ||
           token_matches(parser, name, "sankhya_chhe") ||
           token_matches(parser, name, "લેખન_છે") ||
           token_matches(parser, name, "lakhan_chhe") ||
           token_matches(parser, name, "યાદી_છે") ||
           token_matches(parser, name, "yadi_chhe") ||
           token_matches(parser, name, "કોશ_છે") ||
           token_matches(parser, name, "kosh_chhe") ||
           token_matches(parser, name, "નકામો_છે") ||
           token_matches(parser, name, "nakamo_chhe");
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

static int store_owned_string(Parser *parser, Token operation, char *string)
{
    StringStorage *storage = parser->string_storage;
    if (storage->count == storage->capacity) {
        size_t capacity = storage->capacity == 0 ? 4 : storage->capacity * 2;
        char **items;
        if (capacity < storage->capacity ||
            capacity > (size_t)-1 / sizeof(*storage->items)) {
            free(string);
            report_error(parser, operation.line, operation.column,
                         MESSAGE_OUT_OF_MEMORY_FOR_STRING);
            return 0;
        }
        items = (char **)realloc(storage->items, capacity * sizeof(*items));
        if (items == NULL) {
            free(string);
            report_error(parser, operation.line, operation.column,
                         MESSAGE_OUT_OF_MEMORY_FOR_STRING);
            return 0;
        }
        storage->items = items;
        storage->capacity = capacity;
    }
    storage->items[storage->count++] = string;
    return 1;
}

static size_t decoded_string_length(Parser *parser, Value value)
{
    size_t index;
    size_t length = 0;
    const char *source = value.string_source == NULL ?
                         parser->source : value.string_source;
    if (value.owned_string != NULL) {
        return value.string_length;
    }
    for (index = 0; index < value.string_length; index++) {
        if (source[value.string_offset + index] == '\\') {
            index++;
        }
        length++;
    }
    return length;
}

static size_t copy_value_string(Parser *parser, Value value, char *output)
{
    size_t index;
    size_t length = 0;
    const char *source = value.string_source == NULL ?
                         parser->source : value.string_source;
    if (value.owned_string != NULL) {
        memcpy(output, value.owned_string, value.string_length);
        return value.string_length;
    }
    for (index = 0; index < value.string_length; index++) {
        char character = source[value.string_offset + index];
        if (character == '\\' && index + 1 < value.string_length) {
            index++;
            switch (source[value.string_offset + index]) {
            case '"': character = '"'; break;
            case '\\': character = '\\'; break;
            case 'n': character = '\n'; break;
            case 'r': character = '\r'; break;
            case 't': character = '\t'; break;
            default: break;
            }
        }
        output[length++] = character;
    }
    return length;
}

static char *value_to_c_string(Parser *parser, Value value)
{
    size_t len = decoded_string_length(parser, value);
    char *buf = (char *)malloc(len + 1);
    if (buf == NULL) {
        return NULL;
    }
    copy_value_string(parser, value, buf);
    buf[len] = '\0';
    return buf;
}

static Dict *create_dict(Parser *parser, Token token)
{
    StringStorage *storage = parser->string_storage;
    Dict *dict;

    if (storage->dict_count == storage->dict_capacity) {
        size_t capacity = storage->dict_capacity == 0 ? 4 :
                          storage->dict_capacity * 2;
        Dict **dicts;
        if (capacity < storage->dict_capacity ||
            capacity > (size_t)-1 / sizeof(*storage->dicts)) {
            report_error(parser, token.line, token.column,
                         MESSAGE_OUT_OF_MEMORY);
            return NULL;
        }
        dicts = (Dict **)realloc(storage->dicts,
                                 capacity * sizeof(*dicts));
        if (dicts == NULL) {
            report_error(parser, token.line, token.column,
                         MESSAGE_OUT_OF_MEMORY);
            return NULL;
        }
        storage->dicts = dicts;
        storage->dict_capacity = capacity;
    }
    dict = (Dict *)calloc(1, sizeof(*dict));
    if (dict == NULL) {
        report_error(parser, token.line, token.column,
                     MESSAGE_OUT_OF_MEMORY);
        return NULL;
    }
    storage->dicts[storage->dict_count++] = dict;
    return dict;
}

static Value *dict_get(Dict *dict, const char *key, size_t key_len)
{
    if (dict == NULL) return NULL;
    for (size_t i = 0; i < dict->count; i++) {
        if (dict->entries[i].key_length == key_len &&
            memcmp(dict->entries[i].key, key, key_len) == 0) {
            return &dict->entries[i].value;
        }
    }
    return NULL;
}

static int dict_set(Parser *parser, Dict *dict, const char *key, size_t key_len,
                    Value val, Token token)
{
    if (dict == NULL) return 0;
    Value *existing = dict_get(dict, key, key_len);
    if (existing != NULL) {
        *existing = val;
        return 1;
    }
    if (dict->count == dict->capacity) {
        size_t new_cap = dict->capacity == 0 ? 4 : dict->capacity * 2;
        DictEntry *new_entries = (DictEntry *)realloc(dict->entries,
                                                      new_cap * sizeof(DictEntry));
        if (new_entries == NULL) {
            report_error(parser, token.line, token.column, MESSAGE_OUT_OF_MEMORY);
            return 0;
        }
        dict->entries = new_entries;
        dict->capacity = new_cap;
    }
    char *k_copy = (char *)malloc(key_len + 1);
    if (k_copy == NULL) {
        report_error(parser, token.line, token.column, MESSAGE_OUT_OF_MEMORY);
        return 0;
    }
    memcpy(k_copy, key, key_len);
    k_copy[key_len] = '\0';
    dict->entries[dict->count].key = k_copy;
    dict->entries[dict->count].key_length = key_len;
    dict->entries[dict->count].value = val;
    dict->count++;
    return 1;
}

static int dict_delete(Dict *dict, const char *key, size_t key_len)
{
    if (dict == NULL) return 0;
    for (size_t i = 0; i < dict->count; i++) {
        if (dict->entries[i].key_length == key_len &&
            memcmp(dict->entries[i].key, key, key_len) == 0) {
            free(dict->entries[i].key);
            for (size_t j = i; j + 1 < dict->count; j++) {
                dict->entries[j] = dict->entries[j + 1];
            }
            dict->count--;
            return 1;
        }
    }
    return 0;
}

static int next_string_byte(Parser *parser, Value value, size_t *index)
{
    int character;
    const char *source = value.string_source == NULL ?
                         parser->source : value.string_source;
    if (value.owned_string != NULL) {
        return (unsigned char)value.owned_string[(*index)++];
    }
    character = (unsigned char)source[value.string_offset + *index];
    (*index)++;
    if (character == '\\' && *index < value.string_length) {
        switch (source[value.string_offset + *index]) {
        case '"': character = '"'; break;
        case '\\': character = '\\'; break;
        case 'n': character = '\n'; break;
        case 'r': character = '\r'; break;
        case 't': character = '\t'; break;
        default: break;
        }
        (*index)++;
    }
    return character;
}

static int string_values_equal(Parser *parser, Value left, Value right)
{
    size_t left_index = 0;
    size_t right_index = 0;
    size_t left_length = decoded_string_length(parser, left);
    size_t right_length = decoded_string_length(parser, right);

    if (left_length != right_length) {
        return 0;
    }
    while (left_index < left_length) {
        if (next_string_byte(parser, left, &left_index) !=
            next_string_byte(parser, right, &right_index)) {
            return 0;
        }
    }
    return 1;
}

static size_t string_codepoint_length(Parser *parser, Value value)
{
    size_t index = 0;
    size_t count = 0;
    while (index < value.string_length) {
        int character = next_string_byte(parser, value, &index);
        if (((unsigned char)character & 0xC0) != 0x80) {
            count++;
        }
    }
    return count;
}

static size_t utf8_total_codepoints(const char *str, size_t str_len)
{
    size_t count = 0;
    size_t i;
    for (i = 0; i < str_len; i++) {
        if (((unsigned char)str[i] & 0xC0) != 0x80) {
            count++;
        }
    }
    return count;
}

static unsigned int utf8_decode_codepoint(const char *bytes, size_t len)
{
    if (len == 0) return 0;
    unsigned char b0 = (unsigned char)bytes[0];
    if (b0 < 0x80) {
        return b0;
    } else if ((b0 & 0xE0) == 0xC0 && len >= 2) {
        return ((b0 & 0x1F) << 6) | ((unsigned char)bytes[1] & 0x3F);
    } else if ((b0 & 0xF0) == 0xE0 && len >= 3) {
        return ((b0 & 0x0F) << 12) | (((unsigned char)bytes[1] & 0x3F) << 6) | ((unsigned char)bytes[2] & 0x3F);
    } else if ((b0 & 0xF8) == 0xF0 && len >= 4) {
        return ((b0 & 0x07) << 18) | (((unsigned char)bytes[1] & 0x3F) << 12) | (((unsigned char)bytes[2] & 0x3F) << 6) | ((unsigned char)bytes[3] & 0x3F);
    }
    return b0;
}

static size_t utf8_encode_codepoint(unsigned int cp, char *out_bytes)
{
    if (cp <= 0x7F) {
        out_bytes[0] = (char)cp;
        return 1;
    } else if (cp <= 0x7FF) {
        out_bytes[0] = (char)(0xC0 | ((cp >> 6) & 0x1F));
        out_bytes[1] = (char)(0x80 | (cp & 0x3F));
        return 2;
    } else if (cp <= 0xFFFF) {
        out_bytes[0] = (char)(0xE0 | ((cp >> 12) & 0x0F));
        out_bytes[1] = (char)(0x80 | ((cp >> 6) & 0x3F));
        out_bytes[2] = (char)(0x80 | (cp & 0x3F));
        return 3;
    } else {
        out_bytes[0] = (char)(0xF0 | ((cp >> 18) & 0x07));
        out_bytes[1] = (char)(0x80 | ((cp >> 12) & 0x3F));
        out_bytes[2] = (char)(0x80 | ((cp >> 6) & 0x3F));
        out_bytes[3] = (char)(0x80 | (cp & 0x3F));
        return 4;
    }
}
static size_t utf8_codepoint_to_byte_offset(const char *str, size_t str_len, size_t target_cp)
{
    size_t cp = 0;
    size_t i = 0;
    while (i < str_len && cp < target_cp) {
        i++;
        while (i < str_len && ((unsigned char)str[i] & 0xC0) == 0x80) {
            i++;
        }
        cp++;
    }
    return i;
}

static int concatenate_strings(Parser *parser, Token operation,
                               Value left, Value right, Value *result)
{
    size_t left_length = decoded_string_length(parser, left);
    size_t right_length = decoded_string_length(parser, right);
    size_t total_length;
    char *string;

    if (left_length == (size_t)-1 ||
        right_length > (size_t)-1 - left_length - 1) {
        report_error(parser, operation.line, operation.column,
                     MESSAGE_OUT_OF_MEMORY_FOR_STRING);
        return 0;
    }
    total_length = left_length + right_length;
    string = (char *)malloc(total_length + 1);
    if (string == NULL) {
        report_error(parser, operation.line, operation.column,
                     MESSAGE_OUT_OF_MEMORY_FOR_STRING);
        return 0;
    }
    left_length = copy_value_string(parser, left, string);
    right_length = copy_value_string(parser, right, string + left_length);
    string[left_length + right_length] = '\0';
    if (!store_owned_string(parser, operation, string)) {
        return 0;
    }

    *result = number_value(0.0);
    result->kind = VALUE_STRING;
    result->string_length = left_length + right_length;
    result->owned_string = string;
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
    } else if (!write_string(parser, stdout,
                             prompt.string_source == NULL ?
                                 parser->source : prompt.string_source,
                             prompt.string_offset,
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
    callee.source = function.source;
    callee.filename = function.filename;
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
    while (local_environment.variable_count > 0) {
        free(local_environment.variables[
            --local_environment.variable_count].name);
    }
    free(local_environment.variables);
    return result;
}

typedef struct {
    char *data;
    size_t length;
    size_t capacity;
    int failed;
} StringBuffer;

static void sb_init(StringBuffer *sb)
{
    sb->capacity = 64;
    sb->length = 0;
    sb->failed = 0;
    sb->data = (char *)malloc(sb->capacity);
    if (sb->data == NULL) {
        sb->failed = 1;
    } else {
        sb->data[0] = '\0';
    }
}

static void sb_append(StringBuffer *sb, const char *str, size_t len)
{
    if (sb->failed || len == 0) {
        return;
    }
    if (sb->length + len + 1 > sb->capacity) {
        size_t new_cap = sb->capacity * 2;
        char *new_data;
        if (new_cap < sb->length + len + 1) {
            new_cap = sb->length + len + 16;
        }
        new_data = (char *)realloc(sb->data, new_cap);
        if (new_data == NULL) {
            sb->failed = 1;
            return;
        }
        sb->data = new_data;
        sb->capacity = new_cap;
    }
    memcpy(sb->data + sb->length, str, len);
    sb->length += len;
    sb->data[sb->length] = '\0';
}

static void sb_free(StringBuffer *sb)
{
    if (sb != NULL && sb->data != NULL) {
        free(sb->data);
        sb->data = NULL;
    }
    if (sb != NULL) {
        sb->length = 0;
        sb->capacity = 0;
    }
}

static void format_value_to_buffer(Parser *parser, Value value,
                                   StringBuffer *sb, List **ancestors,
                                   size_t depth)
{
    size_t index;
    if (sb->failed) {
        return;
    }
    if (value.kind == VALUE_STRING) {
        if (value.owned_string != NULL) {
            sb_append(sb, value.owned_string, value.string_length);
        } else {
            size_t len = decoded_string_length(parser, value);
            char *temp = (char *)malloc(len + 1);
            if (temp == NULL) {
                sb->failed = 1;
                return;
            }
            copy_value_string(parser, value, temp);
            sb_append(sb, temp, len);
            free(temp);
        }
        return;
    }
    if (value.kind == VALUE_LIST) {
        if (depth >= 256) {
            sb_append(sb, "[...]", 5);
            return;
        }
        for (index = 0; index < depth; index++) {
            if (ancestors[index] == value.list) {
                sb_append(sb, "<cycle>", 7);
                return;
            }
        }
        ancestors[depth] = value.list;
        sb_append(sb, "[", 1);
        for (index = 0; index < value.list->count; index++) {
            if (index > 0) {
                sb_append(sb, ", ", 2);
            }
            format_value_to_buffer(parser, value.list->items[index], sb,
                                   ancestors, depth + 1);
        }
        sb_append(sb, "]", 1);
        return;
    }
    if (value.kind == VALUE_DICT) {
        if (depth >= 256) {
            sb_append(sb, "{...}", 5);
            return;
        }
        sb_append(sb, "{", 1);
        for (index = 0; index < value.dict->count; index++) {
            if (index > 0) {
                sb_append(sb, ", ", 2);
            }
            sb_append(sb, value.dict->entries[index].key,
                      value.dict->entries[index].key_length);
            sb_append(sb, ": ", 2);
            format_value_to_buffer(parser, value.dict->entries[index].value,
                                   sb, ancestors, depth + 1);
        }
        sb_append(sb, "}", 1);
        return;
    }
    if (value.kind == VALUE_NULL) {
        sb_append(sb, "\xE0\xAA\xA8\xE0\xAA\x95\xE0\xAA\xBE\xE0\xAA\xAE\xE0\xAB\x8B", 15);
        return;
    }
    {
        char num_buf[64];
        snprintf(num_buf, sizeof(num_buf), "%.15g", value.number);
        sb_append(sb, num_buf, strlen(num_buf));
    }
}

static int format_value_as_string(Parser *parser, Token name, Value value,
                                  Value *result)
{
    List *ancestors[256];
    StringBuffer sb;
    sb_init(&sb);
    if (sb.failed) {
        report_error(parser, name.line, name.column,
                     MESSAGE_OUT_OF_MEMORY_FOR_STRING);
        return 0;
    }
    format_value_to_buffer(parser, value, &sb, ancestors, 0);
    if (sb.failed) {
        free(sb.data);
        report_error(parser, name.line, name.column,
                     MESSAGE_OUT_OF_MEMORY_FOR_STRING);
        return 0;
    }
    if (!store_owned_string(parser, name, sb.data)) {
        return 0;
    }
    *result = number_value(0.0);
    result->kind = VALUE_STRING;
    result->string_length = sb.length;
    result->owned_string = sb.data;
    return 1;
}

static int values_are_equal(Parser *parser, Value a, Value b)
{
    if (a.kind != b.kind) {
        return 0;
    }
    if (a.kind == VALUE_NUMBER) {
        return a.number == b.number;
    }
    if (a.kind == VALUE_STRING) {
        return string_values_equal(parser, a, b);
    }
    if (a.kind == VALUE_NULL) {
        return 1;
    }
    if (a.kind == VALUE_LIST) {
        return a.list == b.list;
    }
    if (a.kind == VALUE_DICT) {
        return a.dict == b.dict;
    }
    return 0;
}

static int compare_sort_values(Parser *parser, Value a, Value b)
{
    if (a.kind != b.kind) {
        return a.kind < b.kind ? -1 : 1;
    }
    if (a.kind == VALUE_NUMBER) {
        if (a.number < b.number) return -1;
        if (a.number > b.number) return 1;
        return 0;
    }
    if (a.kind == VALUE_STRING) {
        size_t a_len = decoded_string_length(parser, a);
        size_t b_len = decoded_string_length(parser, b);
        size_t min_len = a_len < b_len ? a_len : b_len;
        size_t a_idx = 0;
        size_t b_idx = 0;
        size_t i;
        for (i = 0; i < min_len; i++) {
            unsigned char cb_a = (unsigned char)next_string_byte(parser, a, &a_idx);
            unsigned char cb_b = (unsigned char)next_string_byte(parser, b, &b_idx);
            if (cb_a < cb_b) return -1;
            if (cb_a > cb_b) return 1;
        }
        if (a_len < b_len) return -1;
        if (a_len > b_len) return 1;
        return 0;
    }
    return 0;
}

static Value pad_string_value(Parser *parser, Token name, Value str_val,
                              Value width_val, Value *opt_pad_val, int is_left)
{
    Value result = str_val;
    size_t target_width = (size_t)width_val.number;
    size_t str_cp = string_codepoint_length(parser, str_val);
    size_t pad_cp;
    size_t needed_cp;
    size_t str_bytes;
    size_t pad_bytes;
    size_t full_repeats;
    size_t rem_cp;
    size_t rem_bytes;
    size_t pad_total_bytes;
    size_t total_bytes;
    char *str_buf;
    char *pad_buf;
    char *out_buf;
    size_t r;

    if (str_cp >= target_width) {
        return str_val;
    }

    if (opt_pad_val != NULL) {
        pad_cp = string_codepoint_length(parser, *opt_pad_val);
        if (pad_cp == 0) {
            return str_val;
        }
        pad_bytes = decoded_string_length(parser, *opt_pad_val);
        pad_buf = (char *)malloc(pad_bytes + 1);
        if (pad_buf == NULL) {
            report_error(parser, name.line, name.column, MESSAGE_OUT_OF_MEMORY);
            return result;
        }
        copy_value_string(parser, *opt_pad_val, pad_buf);
        pad_buf[pad_bytes] = '\0';
    } else {
        pad_cp = 1;
        pad_bytes = 1;
        pad_buf = (char *)malloc(2);
        if (pad_buf == NULL) {
            report_error(parser, name.line, name.column, MESSAGE_OUT_OF_MEMORY);
            return result;
        }
        pad_buf[0] = ' ';
        pad_buf[1] = '\0';
    }

    needed_cp = target_width - str_cp;
    str_bytes = decoded_string_length(parser, str_val);
    str_buf = (char *)malloc(str_bytes + 1);
    if (str_buf == NULL) {
        free(pad_buf);
        report_error(parser, name.line, name.column, MESSAGE_OUT_OF_MEMORY);
        return result;
    }
    copy_value_string(parser, str_val, str_buf);
    str_buf[str_bytes] = '\0';

    full_repeats = needed_cp / pad_cp;
    rem_cp = needed_cp % pad_cp;
    rem_bytes = utf8_codepoint_to_byte_offset(pad_buf, pad_bytes, rem_cp);

    if (full_repeats > 0 && pad_bytes > (size_t)-1 / full_repeats) {
        free(str_buf);
        free(pad_buf);
        report_error(parser, name.line, name.column, MESSAGE_OUT_OF_MEMORY);
        return result;
    }
    pad_total_bytes = full_repeats * pad_bytes + rem_bytes;
    if (str_bytes > (size_t)-1 - pad_total_bytes) {
        free(str_buf);
        free(pad_buf);
        report_error(parser, name.line, name.column, MESSAGE_OUT_OF_MEMORY);
        return result;
    }
    total_bytes = str_bytes + pad_total_bytes;

    out_buf = (char *)malloc(total_bytes + 1);
    if (out_buf == NULL) {
        free(str_buf);
        free(pad_buf);
        report_error(parser, name.line, name.column, MESSAGE_OUT_OF_MEMORY);
        return result;
    }

    if (is_left) {
        char *ptr = out_buf;
        for (r = 0; r < full_repeats; r++) {
            memcpy(ptr, pad_buf, pad_bytes);
            ptr += pad_bytes;
        }
        if (rem_bytes > 0) {
            memcpy(ptr, pad_buf, rem_bytes);
            ptr += rem_bytes;
        }
        memcpy(ptr, str_buf, str_bytes);
    } else {
        char *ptr = out_buf;
        memcpy(ptr, str_buf, str_bytes);
        ptr += str_bytes;
        for (r = 0; r < full_repeats; r++) {
            memcpy(ptr, pad_buf, pad_bytes);
            ptr += pad_bytes;
        }
        if (rem_bytes > 0) {
            memcpy(ptr, pad_buf, rem_bytes);
            ptr += rem_bytes;
        }
    }
    out_buf[total_bytes] = '\0';
    free(str_buf);
    free(pad_buf);

    if (store_owned_string(parser, name, out_buf)) {
        result = number_value(0.0);
        result.kind = VALUE_STRING;
        result.string_length = total_bytes;
        result.owned_string = out_buf;
    }
    return result;
}

static int g_script_argc = 0;
static char **g_script_argv = NULL;

static Value make_owned_string_value(Parser *parser, Token name, char *data, size_t length)
{
    Value result = number_value(0.0);
    if (!store_owned_string(parser, name, data)) {
        return null_value();
    }
    result.kind = VALUE_STRING;
    result.string_length = length;
    result.owned_string = data;
    return result;
}

/* --- SHA-256 Implementation --- */
typedef struct {
    uint8_t data[64];
    uint32_t datalen;
    unsigned long long bitlen;
    uint32_t state[8];
} SHA256Context;

#define SHA256_ROTR(a,b) (((a) >> (b)) | ((a) << (32-(b))))
#define SHA256_CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define SHA256_MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define SHA256_EP0(x) (SHA256_ROTR(x,2) ^ SHA256_ROTR(x,13) ^ SHA256_ROTR(x,22))
#define SHA256_EP1(x) (SHA256_ROTR(x,6) ^ SHA256_ROTR(x,11) ^ SHA256_ROTR(x,25))
#define SHA256_SIG0(x) (SHA256_ROTR(x,7) ^ SHA256_ROTR(x,18) ^ ((x) >> 3))
#define SHA256_SIG1(x) (SHA256_ROTR(x,17) ^ SHA256_ROTR(x,19) ^ ((x) >> 10))

static const uint32_t sha256_k[64] = {
    0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
    0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
    0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
    0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
    0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
    0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
    0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
    0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
};

static void sha256_transform(SHA256Context *ctx, const uint8_t data[])
{
    uint32_t a, b, c, d, e, f, g, h, i, j, t1, t2, m[64];
    for (i = 0, j = 0; i < 16; ++i, j += 4)
        m[i] = ((uint32_t)data[j] << 24) | ((uint32_t)data[j + 1] << 16) | ((uint32_t)data[j + 2] << 8) | ((uint32_t)data[j + 3]);
    for (; i < 64; ++i)
        m[i] = SHA256_SIG1(m[i - 2]) + m[i - 7] + SHA256_SIG0(m[i - 15]) + m[i - 16];
    a = ctx->state[0]; b = ctx->state[1]; c = ctx->state[2]; d = ctx->state[3];
    e = ctx->state[4]; f = ctx->state[5]; g = ctx->state[6]; h = ctx->state[7];
    for (i = 0; i < 64; ++i) {
        t1 = h + SHA256_EP1(e) + SHA256_CH(e, f, g) + sha256_k[i] + m[i];
        t2 = SHA256_EP0(a) + SHA256_MAJ(a, b, c);
        h = g; g = f; f = e; e = d + t1;
        d = c; c = b; b = a; a = t1 + t2;
    }
    ctx->state[0] += a; ctx->state[1] += b; ctx->state[2] += c; ctx->state[3] += d;
    ctx->state[4] += e; ctx->state[5] += f; ctx->state[6] += g; ctx->state[7] += h;
}

static void sha256_init(SHA256Context *ctx)
{
    ctx->datalen = 0;
    ctx->bitlen = 0;
    ctx->state[0] = 0x6a09e667;
    ctx->state[1] = 0xbb67ae85;
    ctx->state[2] = 0x3c6ef372;
    ctx->state[3] = 0xa54ff53a;
    ctx->state[4] = 0x510e527f;
    ctx->state[5] = 0x9b05688c;
    ctx->state[6] = 0x1f83d9ab;
    ctx->state[7] = 0x5be0cd19;
}

static void sha256_update(SHA256Context *ctx, const uint8_t data[], size_t len)
{
    size_t i;
    for (i = 0; i < len; ++i) {
        ctx->data[ctx->datalen] = data[i];
        ctx->datalen++;
        if (ctx->datalen == 64) {
            sha256_transform(ctx, ctx->data);
            ctx->bitlen += 512;
            ctx->datalen = 0;
        }
    }
}

static void sha256_final(SHA256Context *ctx, uint8_t hash[])
{
    uint32_t i = ctx->datalen;
    if (ctx->datalen < 56) {
        ctx->data[i++] = 0x80;
        while (i < 56) ctx->data[i++] = 0x00;
    } else {
        ctx->data[i++] = 0x80;
        while (i < 64) ctx->data[i++] = 0x00;
        sha256_transform(ctx, ctx->data);
        memset(ctx->data, 0, 56);
    }
    ctx->bitlen += (unsigned long long)ctx->datalen * 8;
    ctx->data[63] = (uint8_t)(ctx->bitlen);
    ctx->data[62] = (uint8_t)(ctx->bitlen >> 8);
    ctx->data[61] = (uint8_t)(ctx->bitlen >> 16);
    ctx->data[60] = (uint8_t)(ctx->bitlen >> 24);
    ctx->data[59] = (uint8_t)(ctx->bitlen >> 32);
    ctx->data[58] = (uint8_t)(ctx->bitlen >> 40);
    ctx->data[57] = (uint8_t)(ctx->bitlen >> 48);
    ctx->data[56] = (uint8_t)(ctx->bitlen >> 56);
    sha256_transform(ctx, ctx->data);
    for (i = 0; i < 4; ++i) {
        hash[i]      = (uint8_t)((ctx->state[0] >> (24 - i * 8)) & 0x000000ff);
        hash[i + 4]  = (uint8_t)((ctx->state[1] >> (24 - i * 8)) & 0x000000ff);
        hash[i + 8]  = (uint8_t)((ctx->state[2] >> (24 - i * 8)) & 0x000000ff);
        hash[i + 12] = (uint8_t)((ctx->state[3] >> (24 - i * 8)) & 0x000000ff);
        hash[i + 16] = (uint8_t)((ctx->state[4] >> (24 - i * 8)) & 0x000000ff);
        hash[i + 20] = (uint8_t)((ctx->state[5] >> (24 - i * 8)) & 0x000000ff);
        hash[i + 24] = (uint8_t)((ctx->state[6] >> (24 - i * 8)) & 0x000000ff);
        hash[i + 28] = (uint8_t)((ctx->state[7] >> (24 - i * 8)) & 0x000000ff);
    }
}

static char *sha256_hash_string(const char *input, size_t len)
{
    SHA256Context ctx;
    uint8_t hash[32];
    static const char hex_chars[] = "0123456789abcdef";
    char *output_hex = (char *)malloc(65);
    size_t i;
    if (!output_hex) return NULL;
    sha256_init(&ctx);
    sha256_update(&ctx, (const uint8_t *)input, len);
    sha256_final(&ctx, hash);
    for (i = 0; i < 32; ++i) {
        output_hex[i * 2]     = hex_chars[(hash[i] >> 4) & 0x0f];
        output_hex[i * 2 + 1] = hex_chars[hash[i] & 0x0f];
    }
    output_hex[64] = '\0';
    return output_hex;
}

/* --- Base64 Implementation --- */
static const char b64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static char *base64_encode_str(const unsigned char *data, size_t input_length, size_t *output_length)
{
    size_t out_len = 4 * ((input_length + 2) / 3);
    char *encoded_data = (char *)malloc(out_len + 1);
    size_t i, j;
    if (encoded_data == NULL) return NULL;
    for (i = 0, j = 0; i < input_length;) {
        uint32_t octet_a = i < input_length ? data[i++] : 0;
        uint32_t octet_b = i < input_length ? data[i++] : 0;
        uint32_t octet_c = i < input_length ? data[i++] : 0;
        uint32_t triple = (octet_a << 16) + (octet_b << 8) + octet_c;
        encoded_data[j++] = b64_table[(triple >> 18) & 0x3F];
        encoded_data[j++] = b64_table[(triple >> 12) & 0x3F];
        encoded_data[j++] = (i > input_length + 1) ? '=' : b64_table[(triple >> 6) & 0x3F];
        encoded_data[j++] = (i > input_length) ? '=' : b64_table[triple & 0x3F];
    }
    encoded_data[out_len] = '\0';
    if (output_length) *output_length = out_len;
    return encoded_data;
}

static int b64_char_val(char c)
{
    if (c >= 'A' && c <= 'Z') return c - 'A';
    if (c >= 'a' && c <= 'z') return c - 'a' + 26;
    if (c >= '0' && c <= '9') return c - '0' + 52;
    if (c == '+') return 62;
    if (c == '/') return 63;
    return -1;
}

static char *base64_decode_str(const char *data, size_t input_length, size_t *output_length)
{
    size_t i, j = 0;
    size_t pad = 0;
    size_t valid_len = 0;
    for (i = 0; i < input_length; i++) {
        if (data[i] == '=') pad++;
        else if (b64_char_val(data[i]) >= 0) valid_len++;
    }
    size_t total_chars = valid_len + pad;
    if (total_chars == 0 || (total_chars % 4) != 0) return NULL;
    size_t out_len = (total_chars / 4) * 3 - pad;
    char *decoded_data = (char *)malloc(out_len + 1);
    if (!decoded_data) return NULL;
    for (i = 0; i < input_length;) {
        int v[4] = {-1, -1, -1, -1};
        int count = 0;
        while (i < input_length && count < 4) {
            char c = data[i++];
            if (c == '=') { v[count++] = 0; }
            else {
                int val = b64_char_val(c);
                if (val >= 0) v[count++] = val;
            }
        }
        if (count == 4) {
            uint32_t triple = (v[0] << 18) + (v[1] << 12) + (v[2] << 6) + v[3];
            if (j < out_len) decoded_data[j++] = (char)((triple >> 16) & 0xFF);
            if (j < out_len) decoded_data[j++] = (char)((triple >> 8) & 0xFF);
            if (j < out_len) decoded_data[j++] = (char)(triple & 0xFF);
        }
    }
    decoded_data[out_len] = '\0';
    if (output_length) *output_length = out_len;
    return decoded_data;
}

/* --- Levenshtein Distance --- */
static size_t calc_levenshtein(const char *s1, size_t len1, const char *s2, size_t len2)
{
    size_t *d;
    size_t i, j;
    if (len1 == 0) return len2;
    if (len2 == 0) return len1;
    d = (size_t *)malloc((len2 + 1) * sizeof(size_t));
    if (!d) return 0;
    for (j = 0; j <= len2; j++) d[j] = j;
    for (i = 1; i <= len1; i++) {
        size_t prev = d[0];
        d[0] = i;
        for (j = 1; j <= len2; j++) {
            size_t temp = d[j];
            size_t cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
            size_t min = d[j] + 1;
            if (d[j - 1] + 1 < min) min = d[j - 1] + 1;
            if (prev + cost < min) min = prev + cost;
            d[j] = min;
            prev = temp;
        }
    }
    size_t result = d[len2];
    free(d);
    return result;
}

/* --- Wildcard Pattern Matcher --- */
static int wildcard_match(const char *pat, const char *str)
{
    while (*pat) {
        if (*pat == '*') {
            while (*(pat + 1) == '*') pat++;
            if (*(pat + 1) == '\0') return 1;
            while (*str) {
                if (wildcard_match(pat + 1, str)) return 1;
                str++;
            }
            return wildcard_match(pat + 1, str);
        } else if (*pat == '?' || *pat == *str) {
            if (*str == '\0') return 0;
            pat++;
            str++;
        } else {
            return 0;
        }
    }
    return *str == '\0';
}

/* --- Global Substring Replacement --- */
static char *string_replace_all(const char *src, const char *target, const char *replacement)
{
    size_t src_len = strlen(src);
    size_t tgt_len = strlen(target);
    size_t rep_len = strlen(replacement);
    StringBuffer sb;
    sb_init(&sb);
    if (tgt_len == 0) {
        sb_append(&sb, src, src_len);
        return sb.data;
    }
    const char *p = src;
    while (*p) {
        const char *found = strstr(p, target);
        if (!found) {
            sb_append(&sb, p, strlen(p));
            break;
        }
        sb_append(&sb, p, (size_t)(found - p));
        sb_append(&sb, replacement, rep_len);
        p = found + tgt_len;
    }
    return sb.data;
}

/* --- Title Case & Capitalize First --- */
static char *string_to_title_case(const char *src, size_t len)
{
    char *out = (char *)malloc(len + 1);
    if (!out) return NULL;
    int capitalize_next = 1;
    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)src[i];
        if (c == ' ' || c == '\t' || c == '\n' || c == '_' || c == '-') {
            out[i] = (char)c;
            capitalize_next = 1;
        } else if (capitalize_next && c >= 'a' && c <= 'z') {
            out[i] = (char)(c - 'a' + 'A');
            capitalize_next = 0;
        } else if (!capitalize_next && c >= 'A' && c <= 'Z') {
            out[i] = (char)(c - 'A' + 'a');
        } else {
            out[i] = (char)c;
            capitalize_next = 0;
        }
    }
    out[len] = '\0';
    return out;
}

static char *string_capitalize_first(const char *src, size_t len)
{
    char *out = (char *)malloc(len + 1);
    if (!out) return NULL;
    memcpy(out, src, len);
    out[len] = '\0';
    if (len > 0 && out[0] >= 'a' && out[0] <= 'z') {
        out[0] = (char)(out[0] - 'a' + 'A');
    }
    return out;
}

/* --- Radix Conversions --- */
static char *int_to_bin_string(long long num)
{
    char buf[66];
    int pos = 0;
    unsigned long long n;
    int is_neg = 0;
    if (num == 0) return copy_string("0");
    if (num < 0) { is_neg = 1; n = (unsigned long long)(-num); }
    else n = (unsigned long long)num;
    while (n > 0) {
        buf[pos++] = (n & 1) ? '1' : '0';
        n >>= 1;
    }
    if (is_neg) buf[pos++] = '-';
    buf[pos] = '\0';
    for (int l = 0, r = pos - 1; l < r; l++, r--) {
        char tmp = buf[l]; buf[l] = buf[r]; buf[r] = tmp;
    }
    return copy_string(buf);
}

static char *int_to_hex_string(long long num)
{
    char buf[32];
    if (num < 0) {
        snprintf(buf, sizeof(buf), "-%llx", (unsigned long long)(-num));
    } else {
        snprintf(buf, sizeof(buf), "%llx", (unsigned long long)num);
    }
    return copy_string(buf);
}

/* --- Directory / Folder Helpers --- */
#ifdef _WIN32
static int platform_folder_exists(const char *path)
{
    DWORD attrs = GetFileAttributesA(path);
    return (attrs != INVALID_FILE_ATTRIBUTES && (attrs & FILE_ATTRIBUTE_DIRECTORY)) ? 1 : 0;
}

static int platform_folder_create(const char *path)
{
    if (CreateDirectoryA(path, NULL)) return 1;
    return GetLastError() == ERROR_ALREADY_EXISTS ? 1 : 0;
}

static List *platform_folder_list(Parser *parser, Token name, const char *path)
{
    char search_path[MAX_PATH];
    WIN32_FIND_DATAA fd;
    HANDLE hFind;
    List *list = create_list(parser, name);
    if (!list) return NULL;
    snprintf(search_path, sizeof(search_path), "%s\\*", path);
    hFind = FindFirstFileA(search_path, &fd);
    if (hFind == INVALID_HANDLE_VALUE) return list;
    do {
        if (strcmp(fd.cFileName, ".") != 0 && strcmp(fd.cFileName, "..") != 0) {
            char *fname = copy_string(fd.cFileName);
            if (fname) {
                Value val = make_owned_string_value(parser, name, fname, strlen(fname));
                append_list_item(parser, list, val, name);
            }
        }
    } while (FindNextFileA(hFind, &fd));
    FindClose(hFind);
    return list;
}
#else
static int platform_folder_exists(const char *path)
{
    struct stat st;
    if (stat(path, &st) == 0 && S_ISDIR(st.st_mode)) return 1;
    return 0;
}

static int platform_folder_create(const char *path)
{
    if (mkdir(path, 0777) == 0) return 1;
    return errno == EEXIST ? 1 : 0;
}

static List *platform_folder_list(Parser *parser, Token name, const char *path)
{
    DIR *dir;
    struct dirent *ent;
    List *list = create_list(parser, name);
    if (!list) return NULL;
    dir = opendir(path);
    if (!dir) return list;
    while ((ent = readdir(dir)) != NULL) {
        if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
            char *fname = copy_string(ent->d_name);
            if (fname) {
                Value val = make_owned_string_value(parser, name, fname, strlen(fname));
                append_list_item(parser, list, val, name);
            }
        }
    }
    closedir(dir);
    return list;
}
#endif

/* --- Matrix Math --- */
static Value matrix_add(Parser *parser, Token name, Value m1, Value m2)
{
    if (m1.kind != VALUE_LIST || m2.kind != VALUE_LIST) {
        report_error(parser, name.line, name.column, MESSAGE_EXPECTED_MATRIX_LISTS);
        return null_value();
    }
    size_t rows = m1.list->count;
    if (rows != m2.list->count || rows == 0) {
        report_error(parser, name.line, name.column, MESSAGE_EXPECTED_MATRIX_LISTS);
        return null_value();
    }
    List *res = create_list(parser, name);
    for (size_t r = 0; r < rows; r++) {
        Value row1 = m1.list->items[r];
        Value row2 = m2.list->items[r];
        if (row1.kind != VALUE_LIST || row2.kind != VALUE_LIST || row1.list->count != row2.list->count) {
            report_error(parser, name.line, name.column, MESSAGE_EXPECTED_MATRIX_LISTS);
            return null_value();
        }
        List *res_row = create_list(parser, name);
        for (size_t c = 0; c < row1.list->count; c++) {
            Value v1 = row1.list->items[c];
            Value v2 = row2.list->items[c];
            if (v1.kind != VALUE_NUMBER || v2.kind != VALUE_NUMBER) {
                report_error(parser, name.line, name.column, MESSAGE_EXPECTED_MATRIX_LISTS);
                return null_value();
            }
            append_list_item(parser, res_row, number_value(v1.number + v2.number), name);
        }
        Value rv = number_value(0.0);
        rv.kind = VALUE_LIST;
        rv.list = res_row;
        append_list_item(parser, res, rv, name);
    }
    Value v = number_value(0.0);
    v.kind = VALUE_LIST;
    v.list = res;
    return v;
}

static Value matrix_multiply(Parser *parser, Token name, Value m1, Value m2)
{
    if (m1.kind != VALUE_LIST || m2.kind != VALUE_LIST) {
        report_error(parser, name.line, name.column, MESSAGE_EXPECTED_MATRIX_LISTS);
        return null_value();
    }
    size_t r1 = m1.list->count;
    size_t r2 = m2.list->count;
    if (r1 == 0 || r2 == 0) {
        report_error(parser, name.line, name.column, MESSAGE_EXPECTED_MATRIX_LISTS);
        return null_value();
    }
    if (m1.list->items[0].kind != VALUE_LIST || m2.list->items[0].kind != VALUE_LIST) {
        report_error(parser, name.line, name.column, MESSAGE_EXPECTED_MATRIX_LISTS);
        return null_value();
    }
    size_t c1 = m1.list->items[0].list->count;
    size_t c2 = m2.list->items[0].list->count;
    if (c1 != r2 || c1 == 0 || c2 == 0) {
        report_error(parser, name.line, name.column, MESSAGE_EXPECTED_MATRIX_LISTS);
        return null_value();
    }
    List *res = create_list(parser, name);
    for (size_t i = 0; i < r1; i++) {
        List *row = create_list(parser, name);
        for (size_t j = 0; j < c2; j++) {
            double sum = 0.0;
            for (size_t k = 0; k < c1; k++) {
                Value a = m1.list->items[i].list->items[k];
                Value b = m2.list->items[k].list->items[j];
                if (a.kind != VALUE_NUMBER || b.kind != VALUE_NUMBER) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_MATRIX_LISTS);
                    return null_value();
                }
                sum += a.number * b.number;
            }
            append_list_item(parser, row, number_value(sum), name);
        }
        Value rv = number_value(0.0);
        rv.kind = VALUE_LIST;
        rv.list = row;
        append_list_item(parser, res, rv, name);
    }
    Value v = number_value(0.0);
    v.kind = VALUE_LIST;
    v.list = res;
    return v;
}

/* --- String Formatting Template --- */
static char *format_template(Parser *parser, const char *fmt, size_t fmt_len, const Value *args, size_t arg_count, size_t *out_len)
{
    StringBuffer sb;
    sb_init(&sb);
    size_t auto_idx = 1;
    size_t i = 0;
    while (i < fmt_len) {
        if (fmt[i] == '{') {
            if (i + 1 < fmt_len && fmt[i + 1] == '{') {
                sb_append(&sb, "{", 1);
                i += 2;
                continue;
            }
            size_t close = i + 1;
            while (close < fmt_len && fmt[close] != '}') close++;
            if (close < fmt_len) {
                size_t target_idx = 0;
                if (close == i + 1) {
                    target_idx = auto_idx++;
                } else {
                    target_idx = (size_t)strtoul(fmt + i + 1, NULL, 10) + 1;
                }
                if (target_idx < arg_count) {
                    List *ancestors[256];
                    format_value_to_buffer(parser, args[target_idx], &sb, ancestors, 0);
                }
                i = close + 1;
                continue;
            }
        }
        sb_append(&sb, &fmt[i], 1);
        i++;
    }
    *out_len = sb.length;
    return sb.data;
}

/* --- JSON Formatting & Parsing --- */
static void json_format_value(Parser *parser, Value value, StringBuffer *sb, List **ancestors, size_t depth)
{
    if (sb->failed) return;
    if (value.kind == VALUE_NULL) {
        sb_append(sb, "null", 4);
    } else if (value.kind == VALUE_NUMBER) {
        char buf[64];
        snprintf(buf, sizeof(buf), "%.15g", value.number);
        sb_append(sb, buf, strlen(buf));
    } else if (value.kind == VALUE_STRING) {
        sb_append(sb, "\"", 1);
        char *str = value_to_c_string(parser, value);
        if (str) {
            for (size_t i = 0; str[i] != '\0'; i++) {
                unsigned char c = (unsigned char)str[i];
                if (c == '"') sb_append(sb, "\\\"", 2);
                else if (c == '\\') sb_append(sb, "\\\\", 2);
                else if (c == '\n') sb_append(sb, "\\n", 2);
                else if (c == '\r') sb_append(sb, "\\r", 2);
                else if (c == '\t') sb_append(sb, "\\t", 2);
                else sb_append(sb, (const char *)&c, 1);
            }
            free(str);
        }
        sb_append(sb, "\"", 1);
    } else if (value.kind == VALUE_LIST) {
        if (depth >= 128) { sb_append(sb, "[]", 2); return; }
        for (size_t i = 0; i < depth; i++) {
            if (ancestors[i] == value.list) { sb_append(sb, "[]", 2); return; }
        }
        ancestors[depth] = value.list;
        sb_append(sb, "[", 1);
        for (size_t i = 0; i < value.list->count; i++) {
            if (i > 0) sb_append(sb, ", ", 2);
            json_format_value(parser, value.list->items[i], sb, ancestors, depth + 1);
        }
        sb_append(sb, "]", 1);
    } else if (value.kind == VALUE_DICT) {
        if (depth >= 128) { sb_append(sb, "{}", 2); return; }
        sb_append(sb, "{", 1);
        for (size_t i = 0; i < value.dict->count; i++) {
            if (i > 0) sb_append(sb, ", ", 2);
            sb_append(sb, "\"", 1);
            sb_append(sb, value.dict->entries[i].key, value.dict->entries[i].key_length);
            sb_append(sb, "\": ", 3);
            json_format_value(parser, value.dict->entries[i].value, sb, ancestors, depth + 1);
        }
        sb_append(sb, "}", 1);
    }
}

static void skip_json_whitespace(const char **p)
{
    while (**p == ' ' || **p == '\t' || **p == '\n' || **p == '\r') {
        (*p)++;
    }
}

static Value parse_json_value(Parser *parser, Token token, const char **p, int *err)
{
    skip_json_whitespace(p);
    if (**p == '\0') {
        *err = 1;
        return null_value();
    }
    if (**p == 'n' && strncmp(*p, "null", 4) == 0) {
        *p += 4;
        return null_value();
    }
    if (**p == 't' && strncmp(*p, "true", 4) == 0) {
        *p += 4;
        return number_value(1.0);
    }
    if (**p == 'f' && strncmp(*p, "false", 5) == 0) {
        *p += 5;
        return number_value(0.0);
    }
    if (**p == '"') {
        (*p)++;
        StringBuffer sb;
        sb_init(&sb);
        while (**p != '\0' && **p != '"') {
            if (**p == '\\') {
                (*p)++;
                if (**p == '"') sb_append(&sb, "\"", 1);
                else if (**p == '\\') sb_append(&sb, "\\", 1);
                else if (**p == '/') sb_append(&sb, "/", 1);
                else if (**p == 'b') sb_append(&sb, "\b", 1);
                else if (**p == 'f') sb_append(&sb, "\f", 1);
                else if (**p == 'n') sb_append(&sb, "\n", 1);
                else if (**p == 'r') sb_append(&sb, "\r", 1);
                else if (**p == 't') sb_append(&sb, "\t", 1);
                else if (**p != '\0') sb_append(&sb, *p, 1);
                if (**p != '\0') (*p)++;
            } else {
                sb_append(&sb, *p, 1);
                (*p)++;
            }
        }
        if (**p == '"') (*p)++;
        else { *err = 1; sb_free(&sb); return null_value(); }
        return make_owned_string_value(parser, token, sb.data, sb.length);
    }
    if (**p == '[') {
        (*p)++;
        List *list = create_list(parser, token);
        skip_json_whitespace(p);
        if (**p == ']') {
            (*p)++;
            Value v = number_value(0.0);
            v.kind = VALUE_LIST;
            v.list = list;
            return v;
        }
        while (**p != '\0') {
            Value item = parse_json_value(parser, token, p, err);
            if (*err) return null_value();
            append_list_item(parser, list, item, token);
            skip_json_whitespace(p);
            if (**p == ',') {
                (*p)++;
                skip_json_whitespace(p);
            } else if (**p == ']') {
                (*p)++;
                break;
            } else {
                *err = 1;
                return null_value();
            }
        }
        Value v = number_value(0.0);
        v.kind = VALUE_LIST;
        v.list = list;
        return v;
    }
    if (**p == '{') {
        (*p)++;
        Dict *dict = create_dict(parser, token);
        skip_json_whitespace(p);
        if (**p == '}') {
            (*p)++;
            Value v = number_value(0.0);
            v.kind = VALUE_DICT;
            v.dict = dict;
            return v;
        }
        while (**p != '\0') {
            skip_json_whitespace(p);
            if (**p != '"') { *err = 1; return null_value(); }
            (*p)++;
            StringBuffer key_sb;
            sb_init(&key_sb);
            while (**p != '\0' && **p != '"') {
                if (**p == '\\') {
                    (*p)++;
                    if (**p == '"') sb_append(&key_sb, "\"", 1);
                    else if (**p == '\\') sb_append(&key_sb, "\\", 1);
                    else if (**p != '\0') sb_append(&key_sb, *p, 1);
                    if (**p != '\0') (*p)++;
                } else {
                    sb_append(&key_sb, *p, 1);
                    (*p)++;
                }
            }
            if (**p == '"') (*p)++;
            else { *err = 1; sb_free(&key_sb); return null_value(); }
            skip_json_whitespace(p);
            if (**p != ':') { *err = 1; sb_free(&key_sb); return null_value(); }
            (*p)++;
            skip_json_whitespace(p);
            Value val = parse_json_value(parser, token, p, err);
            if (*err) { sb_free(&key_sb); return null_value(); }
            dict_set(parser, dict, key_sb.data, key_sb.length, val, token);
            sb_free(&key_sb);
            skip_json_whitespace(p);
            if (**p == ',') {
                (*p)++;
                skip_json_whitespace(p);
            } else if (**p == '}') {
                (*p)++;
                break;
            } else {
                *err = 1;
                return null_value();
            }
        }
        Value v = number_value(0.0);
        v.kind = VALUE_DICT;
        v.dict = dict;
        return v;
    }
    if (**p == '-' || (**p >= '0' && **p <= '9')) {
        char *endptr;
        double d = strtod(*p, &endptr);
        if (endptr == *p) { *err = 1; return null_value(); }
        *p = endptr;
        return number_value(d);
    }
    *err = 1;
    return null_value();
}

static Function *resolve_callee_function(Parser *parser, Value func_val)
{
    if (func_val.kind != VALUE_STRING) return NULL;
    char *fn_name = value_to_c_string(parser, func_val);
    if (!fn_name) return NULL;
    Function *fn = find_function_by_name(parser, fn_name, strlen(fn_name));
    free(fn_name);
    return fn;
}

static char *generate_uuid_v4(void)
{
    char *uuid = (char *)malloc(37);
    if (!uuid) return NULL;
    unsigned char b[16];
    for (int i = 0; i < 16; i++) {
        b[i] = (unsigned char)(rand() & 0xFF);
    }
    b[6] = (b[6] & 0x0F) | 0x40;
    b[8] = (b[8] & 0x3F) | 0x80;
    sprintf(uuid, "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
            b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7],
            b[8], b[9], b[10], b[11], b[12], b[13], b[14], b[15]);
    return uuid;
}

static char *url_encode(const char *src, size_t len)
{
    StringBuffer sb;
    sb_init(&sb);
    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)src[i];
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            sb_append(&sb, (const char *)&c, 1);
        } else {
            char hex[4];
            sprintf(hex, "%%%02X", c);
            sb_append(&sb, hex, 3);
        }
    }
    return sb.data;
}

static char *url_decode(const char *src, size_t len)
{
    StringBuffer sb;
    sb_init(&sb);
    size_t i = 0;
    while (i < len) {
        if (src[i] == '+') {
            sb_append(&sb, " ", 1);
            i++;
        } else if (src[i] == '%' && i + 2 < len && isxdigit((unsigned char)src[i + 1]) && isxdigit((unsigned char)src[i + 2])) {
            char hex[3] = { src[i + 1], src[i + 2], '\0' };
            unsigned int c = 0;
            sscanf(hex, "%x", &c);
            unsigned char ch = (unsigned char)c;
            sb_append(&sb, (const char *)&ch, 1);
            i += 3;
        } else {
            sb_append(&sb, &src[i], 1);
            i++;
        }
    }
    return sb.data;
}

static int compare_doubles_asc(const void *a, const void *b)
{
    double da = *(const double *)a;
    double db = *(const double *)b;
    if (da < db) return -1;
    if (da > db) return 1;
    return 0;
}

static char *path_join(const char *a, size_t a_len, const char *b, size_t b_len)
{
    while (a_len > 0 && (a[a_len - 1] == '/' || a[a_len - 1] == '\\')) a_len--;
    while (b_len > 0 && (*b == '/' || *b == '\\')) { b++; b_len--; }
    char *res = (char *)malloc(a_len + b_len + 2);
    if (!res) return NULL;
    memcpy(res, a, a_len);
    res[a_len] = '/';
    memcpy(res + a_len + 1, b, b_len);
    res[a_len + 1 + b_len] = '\0';
    return res;
}

static const char *path_extension(const char *path, size_t len)
{
    for (size_t i = len; i > 0; i--) {
        char c = path[i - 1];
        if (c == '/' || c == '\\') break;
        if (c == '.') return &path[i - 1];
    }
    return "";
}

static const char *path_basename(const char *path, size_t len)
{
    for (size_t i = len; i > 0; i--) {
        char c = path[i - 1];
        if (c == '/' || c == '\\') return &path[i];
    }
    return path;
}

static char *path_dirname(const char *path, size_t len)
{
    for (size_t i = len; i > 0; i--) {
        char c = path[i - 1];
        if (c == '/' || c == '\\') {
            size_t dlen = i - 1;
            if (dlen == 0) dlen = 1;
            char *d = (char *)malloc(dlen + 1);
            if (!d) return NULL;
            memcpy(d, path, dlen);
            d[dlen] = '\0';
            return d;
        }
    }
    return copy_string(".");
}

static char *string_repeat(const char *src, size_t src_len, size_t count, size_t *out_len)
{
    if (count == 0 || src_len == 0) {
        char *r = copy_string("");
        if (out_len) *out_len = 0;
        return r;
    }
    size_t total = src_len * count;
    char *res = (char *)malloc(total + 1);
    if (!res) return NULL;
    for (size_t i = 0; i < count; i++) {
        memcpy(res + i * src_len, src, src_len);
    }
    res[total] = '\0';
    if (out_len) *out_len = total;
    return res;
}

static size_t string_count_substring(const char *src, size_t src_len, const char *sub, size_t sub_len)
{
    if (sub_len == 0 || src_len < sub_len) return 0;
    size_t count = 0;
    const char *p = src;
    const char *end = src + src_len - sub_len + 1;
    while (p < end) {
        if (memcmp(p, sub, sub_len) == 0) {
            count++;
            p += sub_len;
        } else {
            p++;
        }
    }
    return count;
}

static char *pad_string(const char *src, size_t src_len, size_t target_len, char pad_char, int is_left, size_t *out_len)
{
    if (src_len >= target_len) {
        char *res = (char *)malloc(src_len + 1);
        if (!res) return NULL;
        memcpy(res, src, src_len);
        res[src_len] = '\0';
        if (out_len) *out_len = src_len;
        return res;
    }
    char *res = (char *)malloc(target_len + 1);
    if (!res) return NULL;
    size_t pad_amount = target_len - src_len;
    if (is_left) {
        memset(res, pad_char, pad_amount);
        memcpy(res + pad_amount, src, src_len);
    } else {
        memcpy(res, src, src_len);
        memset(res + src_len, pad_char, pad_amount);
    }
    res[target_len] = '\0';
    if (out_len) *out_len = target_len;
    return res;
}

static char *hex_to_string(const char *hex, size_t len, size_t *out_len)
{
    if (len % 2 != 0) return NULL;
    size_t result_len = len / 2;
    char *out = (char *)malloc(result_len + 1);
    if (!out) return NULL;
    for (size_t i = 0; i < result_len; i++) {
        char buf[3] = { hex[i * 2], hex[i * 2 + 1], '\0' };
        if (!isxdigit((unsigned char)buf[0]) || !isxdigit((unsigned char)buf[1])) {
            free(out);
            return NULL;
        }
        unsigned int byte_val = 0;
        sscanf(buf, "%x", &byte_val);
        out[i] = (char)byte_val;
    }
    out[result_len] = '\0';
    if (out_len) *out_len = result_len;
    return out;
}

static Value read_file_lines(Parser *parser, Token name, const char *path)
{
    FILE *f = fopen(path, "rb");
    if (!f) return null_value();
    List *list = create_list(parser, name);
    StringBuffer line;
    sb_init(&line);
    int c;
    while ((c = fgetc(f)) != EOF) {
        if (c == '\r') {
            int next = fgetc(f);
            if (next != '\n' && next != EOF) ungetc(next, f);
            Value lv = make_owned_string_value(parser, name, line.data ? line.data : copy_string(""), line.length);
            append_list_item(parser, list, lv, name);
            sb_init(&line);
        } else if (c == '\n') {
            Value lv = make_owned_string_value(parser, name, line.data ? line.data : copy_string(""), line.length);
            append_list_item(parser, list, lv, name);
            sb_init(&line);
        } else {
            char ch = (char)c;
            sb_append(&line, &ch, 1);
        }
    }
    if (line.length > 0) {
        Value lv = make_owned_string_value(parser, name, line.data ? line.data : copy_string(""), line.length);
        append_list_item(parser, list, lv, name);
    } else {
        sb_free(&line);
    }
    fclose(f);
    Value res = number_value(0.0);
    res.kind = VALUE_LIST;
    res.list = list;
    return res;
}

static Value parse_csv_string(Parser *parser, Token name, const char *csv, size_t len)
{
    List *rows = create_list(parser, name);
    size_t i = 0;
    while (i < len) {
        if (csv[i] == '\r' || csv[i] == '\n') {
            i++;
            continue;
        }
        List *row = create_list(parser, name);
        while (i < len && csv[i] != '\r' && csv[i] != '\n') {
            StringBuffer field;
            sb_init(&field);
            if (csv[i] == '"') {
                i++;
                while (i < len) {
                    if (csv[i] == '"') {
                        if (i + 1 < len && csv[i + 1] == '"') {
                            sb_append(&field, "\"", 1);
                            i += 2;
                        } else {
                            i++;
                            break;
                        }
                    } else {
                        sb_append(&field, &csv[i], 1);
                        i++;
                    }
                }
                while (i < len && csv[i] != ',' && csv[i] != '\r' && csv[i] != '\n') {
                    i++;
                }
            } else {
                while (i < len && csv[i] != ',' && csv[i] != '\r' && csv[i] != '\n') {
                    sb_append(&field, &csv[i], 1);
                    i++;
                }
            }
            Value col_val = make_owned_string_value(parser, name, field.data ? field.data : copy_string(""), field.length);
            append_list_item(parser, row, col_val, name);
            if (i < len && csv[i] == ',') {
                i++;
                if (i == len || csv[i] == '\r' || csv[i] == '\n') {
                    Value empty_val = make_owned_string_value(parser, name, copy_string(""), 0);
                    append_list_item(parser, row, empty_val, name);
                }
            }
        }
        Value row_val = number_value(0.0);
        row_val.kind = VALUE_LIST;
        row_val.list = row;
        append_list_item(parser, rows, row_val, name);
        if (i < len && csv[i] == '\r') i++;
        if (i < len && csv[i] == '\n') i++;
    }
    Value result = number_value(0.0);
    result.kind = VALUE_LIST;
    result.list = rows;
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
            if (token_matches(parser, name, "વાંચો") ||
                token_matches(parser, name, "vancho")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_INPUT_PROMPT);
                } else {
                    read_input_line(parser, name, arguments[0], &result);
                }
            } else if (token_matches(parser, name, "લંબાઈ") ||
                       token_matches(parser, name, "lambai")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind == VALUE_STRING) {
                    result = number_value((double)string_codepoint_length(
                        parser, arguments[0]));
                } else if (arguments[0].kind == VALUE_LIST) {
                    result = number_value((double)arguments[0].list->count);
                } else if (arguments[0].kind == VALUE_DICT) {
                    result = number_value((double)arguments[0].dict->count);
                } else {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_LENGTH_STRING);
                }
            } else if (token_matches(parser, name, "સંખ્યા") ||
                       token_matches(parser, name, "sankhya")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_SANKHYA_STRING);
                } else {
                    size_t length = decoded_string_length(parser, arguments[0]);
                    char *buffer = (char *)malloc(length + 1);
                    if (buffer == NULL) {
                        report_error(parser, name.line, name.column,
                                     MESSAGE_OUT_OF_MEMORY);
                    } else {
                        char *ptr;
                        char *endptr;
                        double num;
                        copy_value_string(parser, arguments[0], buffer);
                        buffer[length] = '\0';
                        ptr = buffer;
                        while (*ptr == ' ' || *ptr == '\t' ||
                               *ptr == '\r' || *ptr == '\n') {
                            ptr++;
                        }
                        if (*ptr == '\0') {
                            free(buffer);
                            report_error(parser, name.line, name.column,
                                         MESSAGE_COULD_NOT_PARSE_NUMBER);
                        } else {
                            errno = 0;
                            num = strtod(ptr, &endptr);
                            while (*endptr == ' ' || *endptr == '\t' ||
                                   *endptr == '\r' || *endptr == '\n') {
                                endptr++;
                            }
                            if (endptr == ptr || *endptr != '\0' || errno == ERANGE) {
                                free(buffer);
                                report_error(parser, name.line, name.column,
                                             MESSAGE_COULD_NOT_PARSE_NUMBER);
                            } else {
                                free(buffer);
                                result = number_value(num);
                            }
                        }
                    }
                }
            } else if (token_matches(parser, name, "લખાણ") ||
                       token_matches(parser, name, "lakhan")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    format_value_as_string(parser, name, arguments[0], &result);
                }
            } else if (token_matches(parser, name, "પ્રકાર") ||
                       token_matches(parser, name, "prakar")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    const char *type_name = "null";
                    if (arguments[0].kind == VALUE_NUMBER) {
                        type_name = "number";
                    } else if (arguments[0].kind == VALUE_STRING) {
                        type_name = "string";
                    } else if (arguments[0].kind == VALUE_LIST) {
                        type_name = "list";
                    } else if (arguments[0].kind == VALUE_DICT) {
                        type_name = "dict";
                    }
                    size_t len = strlen(type_name);
                    char *str = (char *)malloc(len + 1);
                    if (str == NULL) {
                        report_error(parser, name.line, name.column,
                                     MESSAGE_OUT_OF_MEMORY);
                    } else {
                        memcpy(str, type_name, len + 1);
                        if (store_owned_string(parser, name, str)) {
                            result = number_value(0.0);
                            result.kind = VALUE_STRING;
                            result.string_length = len;
                            result.owned_string = str;
                        }
                    }
                }
            } else if (token_matches(parser, name, "સમાવે_લખાણ") ||
                       token_matches(parser, name, "samave_lakhan")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING ||
                           arguments[1].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_STRING_FOR_SAMAVE_LAKHAN);
                } else {
                    size_t h_len = decoded_string_length(parser, arguments[0]);
                    size_t n_len = decoded_string_length(parser, arguments[1]);
                    if (n_len == 0) {
                        result = number_value(1.0);
                    } else if (h_len < n_len) {
                        result = number_value(0.0);
                    } else {
                        char *h_buf = (char *)malloc(h_len + 1);
                        char *n_buf = (char *)malloc(n_len + 1);
                        if (h_buf == NULL || n_buf == NULL) {
                            free(h_buf);
                            free(n_buf);
                            report_error(parser, name.line, name.column,
                                         MESSAGE_OUT_OF_MEMORY);
                        } else {
                            copy_value_string(parser, arguments[0], h_buf);
                            h_buf[h_len] = '\0';
                            copy_value_string(parser, arguments[1], n_buf);
                            n_buf[n_len] = '\0';
                            int found = 0;
                            size_t limit = h_len - n_len;
                            for (size_t i = 0; i <= limit; i++) {
                                if (memcmp(h_buf + i, n_buf, n_len) == 0) {
                                    found = 1;
                                    break;
                                }
                            }
                            free(h_buf);
                            free(n_buf);
                            result = number_value(found ? 1.0 : 0.0);
                        }
                    }
                }
            } else if (token_matches(parser, name, "ફાઇલ_વાંચો") ||
                       token_matches(parser, name, "file_vancho")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_STRING_FOR_FILE_PATH);
                } else if (execute) {
                    char *path_buf = value_to_c_string(parser, arguments[0]);
                    if (path_buf == NULL) {
                        report_error(parser, name.line, name.column,
                                     MESSAGE_OUT_OF_MEMORY);
                    } else {
                        FILE *f = fopen(path_buf, "rb");
                        free(path_buf);
                        if (f == NULL) {
                            result = null_value();
                        } else {
                            if (fseek(f, 0, SEEK_END) != 0) {
                                fclose(f);
                                result = null_value();
                            } else {
                                long fsize = ftell(f);
                                if (fsize < 0 || fseek(f, 0, SEEK_SET) != 0) {
                                    fclose(f);
                                    result = null_value();
                                } else if (fsize == 0) {
                                    fclose(f);
                                    char *empty_str = (char *)malloc(1);
                                    if (empty_str == NULL) {
                                        report_error(parser, name.line, name.column,
                                                     MESSAGE_OUT_OF_MEMORY);
                                    } else {
                                        empty_str[0] = '\0';
                                        if (!store_owned_string(parser, name, empty_str)) {
                                            result = number_value(0.0);
                                        } else {
                                            result.kind = VALUE_STRING;
                                            result.string_offset = 0;
                                            result.string_length = 0;
                                            result.owned_string = empty_str;
                                        }
                                    }
                                } else {
                                    char *content_buf = (char *)malloc((size_t)fsize + 1);
                                    if (content_buf == NULL) {
                                        fclose(f);
                                        report_error(parser, name.line, name.column,
                                                     MESSAGE_OUT_OF_MEMORY);
                                    } else {
                                        size_t read_bytes = fread(content_buf, 1, (size_t)fsize, f);
                                        fclose(f);
                                        content_buf[read_bytes] = '\0';
                                        if (!store_owned_string(parser, name, content_buf)) {
                                            result = number_value(0.0);
                                        } else {
                                            result.kind = VALUE_STRING;
                                            result.string_offset = 0;
                                            result.string_length = read_bytes;
                                            result.owned_string = content_buf;
                                        }
                                    }
                                }
                            }
                        }
                    }
                } else {
                    result = null_value();
                }
            } else if (token_matches(parser, name, "ફાઇલ_લખો") ||
                       token_matches(parser, name, "file_lakho")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_STRING_FOR_FILE_PATH);
                } else if (arguments[1].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_STRING_FOR_FILE_CONTENT);
                } else if (execute) {
                    char *path_buf = value_to_c_string(parser, arguments[0]);
                    size_t c_len = decoded_string_length(parser, arguments[1]);
                    char *c_buf = (char *)malloc(c_len + 1);
                    if (path_buf == NULL || c_buf == NULL) {
                        free(path_buf);
                        free(c_buf);
                        report_error(parser, name.line, name.column,
                                     MESSAGE_OUT_OF_MEMORY);
                    } else {
                        copy_value_string(parser, arguments[1], c_buf);
                        c_buf[c_len] = '\0';
                        FILE *f = fopen(path_buf, "wb");
                        free(path_buf);
                        if (f == NULL) {
                            free(c_buf);
                            result = number_value(0.0);
                        } else {
                            size_t written = 0;
                            if (c_len > 0) {
                                written = fwrite(c_buf, 1, c_len, f);
                            }
                            fclose(f);
                            free(c_buf);
                            result = number_value(written == c_len ? 1.0 : 0.0);
                        }
                    }
                } else {
                    result = number_value(0.0);
                }
            } else if (token_matches(parser, name, "ફાઇલ_ઉમેરો") ||
                       token_matches(parser, name, "file_umero")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_STRING_FOR_FILE_PATH);
                } else if (arguments[1].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_STRING_FOR_FILE_CONTENT);
                } else if (execute) {
                    char *path_buf = value_to_c_string(parser, arguments[0]);
                    size_t c_len = decoded_string_length(parser, arguments[1]);
                    char *c_buf = (char *)malloc(c_len + 1);
                    if (path_buf == NULL || c_buf == NULL) {
                        free(path_buf);
                        free(c_buf);
                        report_error(parser, name.line, name.column,
                                     MESSAGE_OUT_OF_MEMORY);
                    } else {
                        copy_value_string(parser, arguments[1], c_buf);
                        c_buf[c_len] = '\0';
                        FILE *f = fopen(path_buf, "ab");
                        free(path_buf);
                        if (f == NULL) {
                            free(c_buf);
                            result = number_value(0.0);
                        } else {
                            size_t written = 0;
                            if (c_len > 0) {
                                written = fwrite(c_buf, 1, c_len, f);
                            }
                            fclose(f);
                            free(c_buf);
                            result = number_value(written == c_len ? 1.0 : 0.0);
                        }
                    }
                } else {
                    result = number_value(0.0);
                }
            } else if (token_matches(parser, name, "ફાઇલ_છે") ||
                       token_matches(parser, name, "file_chhe")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_STRING_FOR_FILE_PATH);
                } else if (execute) {
                    char *path_buf = value_to_c_string(parser, arguments[0]);
                    if (path_buf == NULL) {
                        report_error(parser, name.line, name.column,
                                     MESSAGE_OUT_OF_MEMORY);
                    } else {
                        FILE *f = fopen(path_buf, "rb");
                        free(path_buf);
                        if (f != NULL) {
                            fclose(f);
                            result = number_value(1.0);
                        } else {
                            result = number_value(0.0);
                        }
                    }
                } else {
                    result = number_value(0.0);
                }
            } else if (token_matches(parser, name, "ફાઇલ_કાઢો") ||
                       token_matches(parser, name, "file_kadho") ||
                       token_matches(parser, name, "ફાઇલ_હટાવો") ||
                       token_matches(parser, name, "file_hatao")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_STRING_FOR_FILE_PATH);
                } else if (execute) {
                    char *path_buf = value_to_c_string(parser, arguments[0]);
                    if (path_buf == NULL) {
                        report_error(parser, name.line, name.column,
                                     MESSAGE_OUT_OF_MEMORY);
                    } else {
                        int rc = remove(path_buf);
                        free(path_buf);
                        result = number_value(rc == 0 ? 1.0 : 0.0);
                    }
                } else {
                    result = number_value(0.0);
                }
            } else if (token_matches(parser, name, "ફાઇલ_કદ") ||
                       token_matches(parser, name, "file_kad")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_STRING_FOR_FILE_PATH);
                } else if (execute) {
                    char *path_buf = value_to_c_string(parser, arguments[0]);
                    if (path_buf == NULL) {
                        report_error(parser, name.line, name.column,
                                     MESSAGE_OUT_OF_MEMORY);
                    } else {
                        FILE *f = fopen(path_buf, "rb");
                        free(path_buf);
                        if (f == NULL) {
                            result = null_value();
                        } else {
                            if (fseek(f, 0, SEEK_END) != 0) {
                                fclose(f);
                                result = null_value();
                            } else {
                                long fsize = ftell(f);
                                fclose(f);
                                if (fsize < 0) {
                                    result = null_value();
                                } else {
                                    result = number_value((double)fsize);
                                }
                            }
                        }
                    }
                } else {
                    result = null_value();
                }
            } else if (token_matches(parser, name, "શબ્દકોશ") || token_matches(parser, name, "shabdakosh") ||
                       token_matches(parser, name, "કોશ") || token_matches(parser, name, "kosh")) {
                if (argument_count % 2 != 0) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_EVEN_DICT_ARGS);
                } else if (execute) {
                    Dict *dict = create_dict(parser, name);
                    if (dict != NULL) {
                        for (size_t i = 0; i < argument_count; i += 2) {
                            if (arguments[i].kind != VALUE_STRING) {
                                report_error(parser, name.line, name.column, MESSAGE_EXPECTED_DICT_KEY_STRING);
                                break;
                            }
                            char *k = value_to_c_string(parser, arguments[i]);
                            if (k == NULL) {
                                report_error(parser, name.line, name.column, MESSAGE_OUT_OF_MEMORY);
                                break;
                            }
                            dict_set(parser, dict, k, strlen(k), arguments[i + 1], name);
                            free(k);
                        }
                        result = number_value(0.0);
                        result.kind = VALUE_DICT;
                        result.dict = dict;
                    }
                } else {
                    result = number_value(0.0);
                }
            } else if (token_matches(parser, name, "ચાવીઓ") || token_matches(parser, name, "chavio") ||
                       token_matches(parser, name, "ચાવી") || token_matches(parser, name, "chavi")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_DICT) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_DICT_FOR_OPERATION);
                } else if (execute) {
                    List *list = create_list(parser, name);
                    if (list != NULL) {
                        for (size_t i = 0; i < arguments[0].dict->count; i++) {
                            char *k = arguments[0].dict->entries[i].key;
                            size_t k_len = arguments[0].dict->entries[i].key_length;
                            char *k_copy = (char *)malloc(k_len + 1);
                            if (k_copy != NULL) {
                                memcpy(k_copy, k, k_len + 1);
                                if (store_owned_string(parser, name, k_copy)) {
                                    Value k_val = number_value(0.0);
                                    k_val.kind = VALUE_STRING;
                                    k_val.string_offset = 0;
                                    k_val.string_length = k_len;
                                    k_val.owned_string = k_copy;
                                    append_list_item(parser, list, k_val, name);
                                }
                            }
                        }
                        result = number_value(0.0);
                        result.kind = VALUE_LIST;
                        result.list = list;
                    }
                } else {
                    result = number_value(0.0);
                }
            } else if (token_matches(parser, name, "મૂલ્યો") || token_matches(parser, name, "mulyo")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_DICT) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_DICT_FOR_OPERATION);
                } else if (execute) {
                    List *list = create_list(parser, name);
                    if (list != NULL) {
                        for (size_t i = 0; i < arguments[0].dict->count; i++) {
                            append_list_item(parser, list, arguments[0].dict->entries[i].value, name);
                        }
                        result = number_value(0.0);
                        result.kind = VALUE_LIST;
                        result.list = list;
                    }
                } else {
                    result = number_value(0.0);
                }
            } else if (token_matches(parser, name, "દૂર_કરો") || token_matches(parser, name, "dur_karo") ||
                       token_matches(parser, name, "કોશ_દૂર") || token_matches(parser, name, "kosh_dur")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_DICT) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_DICT_FOR_OPERATION);
                } else if (arguments[1].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_DICT_KEY_STRING);
                } else if (execute) {
                    char *k = value_to_c_string(parser, arguments[1]);
                    int rc = 0;
                    if (k != NULL) {
                        rc = dict_delete(arguments[0].dict, k, strlen(k));
                        free(k);
                    }
                    result = number_value(rc ? 1.0 : 0.0);
                } else {
                    result = number_value(0.0);
                }
            } else if (token_matches(parser, name, "સમય") ||
                       token_matches(parser, name, "samay")) {
                if (argument_count != 0) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (execute) {
                    time_t now = time(NULL);
                    result = number_value((double)now);
                } else {
                    result = number_value(0.0);
                }
            } else if (token_matches(parser, name, "તારીખ") ||
                       token_matches(parser, name, "tarikh")) {
                if (argument_count > 2) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (argument_count >= 1 && arguments[0].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_STRING_FOR_TARIKH);
                } else if (argument_count == 2 && arguments[1].kind != VALUE_NUMBER) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_TIMESTAMP_NUMBER);
                } else if (execute) {
                    time_t ts = time(NULL);
                    if (argument_count == 2) {
                        ts = (time_t)arguments[1].number;
                    }
                    struct tm *tm_info = localtime(&ts);
                    char buf[128];
                    const char *fmt = "%Y-%m-%d %H:%M:%S";
                    char *custom_fmt = NULL;
                    if (argument_count >= 1) {
                        custom_fmt = value_to_c_string(parser, arguments[0]);
                        if (custom_fmt != NULL) {
                            fmt = custom_fmt;
                        }
                    }
                    size_t formatted_len = strftime(buf, sizeof(buf), fmt, tm_info);
                    free(custom_fmt);
                    char *out_str = (char *)malloc(formatted_len + 1);
                    if (out_str == NULL) {
                        report_error(parser, name.line, name.column, MESSAGE_OUT_OF_MEMORY);
                    } else {
                        memcpy(out_str, buf, formatted_len + 1);
                        if (!store_owned_string(parser, name, out_str)) {
                            result = number_value(0.0);
                        } else {
                            result.kind = VALUE_STRING;
                            result.string_offset = 0;
                            result.string_length = formatted_len;
                            result.owned_string = out_str;
                        }
                    }
                } else {
                    result = number_value(0.0);
                }
            } else if (token_matches(parser, name, "વર્ષ") || token_matches(parser, name, "varsh") ||
                       token_matches(parser, name, "મહિનો") || token_matches(parser, name, "mahino") ||
                       token_matches(parser, name, "દિવસ") || token_matches(parser, name, "divas") ||
                       token_matches(parser, name, "કલાક") || token_matches(parser, name, "kalak") ||
                       token_matches(parser, name, "મિનિટ") || token_matches(parser, name, "minute") ||
                       token_matches(parser, name, "સેકન્ડ") || token_matches(parser, name, "second")) {
                if (argument_count > 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (argument_count == 1 && arguments[0].kind != VALUE_NUMBER) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_TIMESTAMP_NUMBER);
                } else if (execute) {
                    time_t ts = time(NULL);
                    if (argument_count == 1) {
                        ts = (time_t)arguments[0].number;
                    }
                    struct tm *tm_info = localtime(&ts);
                    double val = 0.0;
                    if (token_matches(parser, name, "વર્ષ") || token_matches(parser, name, "varsh")) {
                        val = (double)(tm_info->tm_year + 1900);
                    } else if (token_matches(parser, name, "મહિનો") || token_matches(parser, name, "mahino")) {
                        val = (double)(tm_info->tm_mon + 1);
                    } else if (token_matches(parser, name, "દિવસ") || token_matches(parser, name, "divas")) {
                        val = (double)tm_info->tm_mday;
                    } else if (token_matches(parser, name, "કલાક") || token_matches(parser, name, "kalak")) {
                        val = (double)tm_info->tm_hour;
                    } else if (token_matches(parser, name, "મિનિટ") || token_matches(parser, name, "minute")) {
                        val = (double)tm_info->tm_min;
                    } else {
                        val = (double)tm_info->tm_sec;
                    }
                    result = number_value(val);
                } else {
                    result = number_value(0.0);
                }
            } else if (token_matches(parser, name, "શાંત") || token_matches(parser, name, "shant") ||
                       token_matches(parser, name, "રાહ_જુઓ") || token_matches(parser, name, "raah_juo")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_NUMBER || arguments[0].number < 0.0) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_SLEEP_MILLISECONDS);
                } else if (execute) {
                    double ms = arguments[0].number;
#ifdef _WIN32
                    Sleep((DWORD)ms);
#else
                    usleep((useconds_t)(ms * 1000));
#endif
                    result = number_value(1.0);
                } else {
                    result = number_value(0.0);
                }
            } else if (token_matches(parser, name, "ફેંકો") || token_matches(parser, name, "phenko")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_STRING_FOR_PHENKO);
                } else if (execute) {
                    char *msg = value_to_c_string(parser, arguments[0]);
                    if (msg == NULL) {
                        report_error(parser, name.line, name.column, MESSAGE_OUT_OF_MEMORY);
                    } else {
                        if (parser->in_try) {
                            if (!parser->error_caught) {
                                free(parser->last_error_message);
                                parser->last_error_message = msg;
                                parser->error_caught = 1;
                            } else {
                                free(msg);
                            }
                        } else {
                            const char *label = parser->language == LANGUAGE_GUJARATI ? "ભૂલ" : "error";
                            fprintf(stderr, "%s:%zu:%zu: %s: %s\n",
                                    parser->filename, name.line, name.column, label, msg);
                            write_source_context(parser, name.line, name.column);
                            parser->failed = 1;
                            free(msg);
                        }
                    }
                }
                result = number_value(0.0);
            } else if (token_matches(parser, name, "ચકાસો") ||
                       token_matches(parser, name, "chakaso")) {
                if (argument_count != 1 && argument_count != 2) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (argument_count == 2 && arguments[1].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_STRING_ASSERTION_MESSAGE);
                } else if (execute && !value_is_truthy(arguments[0])) {
                    if (argument_count == 2) {
                        size_t msg_len = decoded_string_length(parser, arguments[1]);
                        char *msg_buf = (char *)malloc(msg_len + 1);
                        if (msg_buf == NULL) {
                            report_error(parser, name.line, name.column,
                                         MESSAGE_OUT_OF_MEMORY);
                        } else {
                            copy_value_string(parser, arguments[1], msg_buf);
                            msg_buf[msg_len] = '\0';
                            if (!parser->failed) {
                                const char *label = parser->language == LANGUAGE_GUJARATI ?
                                                    "ભૂલ" : "error";
                                fprintf(stderr, "%s:%zu:%zu: %s: %s\n",
                                        parser->filename, name.line, name.column, label, msg_buf);
                                write_source_context(parser, name.line, name.column);
                                parser->failed = 1;
                            }
                            free(msg_buf);
                        }
                    } else {
                        report_error(parser, name.line, name.column,
                                     MESSAGE_ASSERTION_FAILED);
                    }
                    result = number_value(0.0);
                } else {
                    result = number_value(1.0);
                }
            } else if (token_matches(parser, name, "બહાર") ||
                       token_matches(parser, name, "bahar")) {
                if (argument_count > 1) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (argument_count == 1 &&
                           (arguments[0].kind != VALUE_NUMBER ||
                            arguments[0].number < 0.0 ||
                            arguments[0].number > 255.0 ||
                            arguments[0].number != (double)(int)arguments[0].number)) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_EXIT_CODE_INTEGER);
                } else {
                    int exit_code = 0;
                    if (argument_count == 1) {
                        exit_code = (int)arguments[0].number;
                    }
                    if (execute) {
                        exit(exit_code);
                    }
                    result = number_value(0.0);
                }
            } else if (token_matches(parser, name, "પર્યાવરણ") ||
                       token_matches(parser, name, "paryavaran")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_STRING_FOR_PARYAVARAN);
                } else {
                    size_t name_len = decoded_string_length(parser, arguments[0]);
                    char *name_buf = (char *)malloc(name_len + 1);
                    if (name_buf == NULL) {
                        report_error(parser, name.line, name.column,
                                     MESSAGE_OUT_OF_MEMORY);
                    } else {
                        copy_value_string(parser, arguments[0], name_buf);
                        name_buf[name_len] = '\0';
                        const char *env_val = getenv(name_buf);
                        free(name_buf);
                        if (env_val == NULL) {
                            result = null_value();
                        } else {
                            size_t val_len = strlen(env_val);
                            char *out_val = (char *)malloc(val_len + 1);
                            if (out_val == NULL) {
                                report_error(parser, name.line, name.column,
                                             MESSAGE_OUT_OF_MEMORY);
                            } else {
                                memcpy(out_val, env_val, val_len + 1);
                                if (!store_owned_string(parser, name, out_val)) {
                                    result = number_value(0.0);
                                } else {
                                    result.kind = VALUE_STRING;
                                    result.string_offset = 0;
                                    result.string_length = val_len;
                                    result.owned_string = out_val;
                                }
                            }
                        }
                    }
                }
            } else if (token_matches(parser, name, "અક્ષરો") ||
                       token_matches(parser, name, "aksharo")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_STRING_FOR_AKSHARO);
                } else {
                    List *list = create_list(parser, name);
                    if (list != NULL) {
                        size_t src_len = decoded_string_length(parser, arguments[0]);
                        char *src_buf = (char *)malloc(src_len + 1);
                        if (src_buf == NULL) {
                            report_error(parser, name.line, name.column,
                                         MESSAGE_OUT_OF_MEMORY);
                        } else {
                            copy_value_string(parser, arguments[0], src_buf);
                            src_buf[src_len] = '\0';
                            size_t total_cp = utf8_total_codepoints(src_buf, src_len);
                            size_t cp;
                            int ok = 1;
                            for (cp = 0; cp < total_cp; cp++) {
                                size_t b_start = utf8_codepoint_to_byte_offset(src_buf, src_len, cp);
                                size_t b_end = utf8_codepoint_to_byte_offset(src_buf, src_len, cp + 1);
                                size_t piece_len = b_end - b_start;
                                char *piece = (char *)malloc(piece_len + 1);
                                if (piece == NULL) {
                                    report_error(parser, name.line, name.column,
                                                 MESSAGE_OUT_OF_MEMORY);
                                    ok = 0;
                                    break;
                                }
                                memcpy(piece, src_buf + b_start, piece_len);
                                piece[piece_len] = '\0';
                                if (!store_owned_string(parser, name, piece)) {
                                    ok = 0;
                                    break;
                                }
                                Value piece_val = number_value(0.0);
                                piece_val.kind = VALUE_STRING;
                                piece_val.string_length = piece_len;
                                piece_val.owned_string = piece;
                                if (!append_list_item(parser, list, piece_val, name)) {
                                    ok = 0;
                                    break;
                                }
                            }
                            free(src_buf);
                            if (ok) {
                                result = number_value(0.0);
                                result.kind = VALUE_LIST;
                                result.list = list;
                            }
                        }
                    }
                }
            } else if (token_matches(parser, name, "વિભાજન_પંક્તિ") ||
                       token_matches(parser, name, "vibhaajan_pankti") ||
                       token_matches(parser, name, "પંક્તિઓ") ||
                       token_matches(parser, name, "panktiyo") ||
                       token_matches(parser, name, "પંક્તિ_ભાગ") ||
                       token_matches(parser, name, "pankti_bhag")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_STRING_FOR_VIBHAAJAN_PANKTI);
                } else {
                    List *list = create_list(parser, name);
                    if (list != NULL) {
                        size_t length = decoded_string_length(parser, arguments[0]);
                        char *buffer = (char *)malloc(length + 1);
                        if (buffer == NULL) {
                            report_error(parser, name.line, name.column,
                                         MESSAGE_OUT_OF_MEMORY);
                        } else {
                            copy_value_string(parser, arguments[0], buffer);
                            buffer[length] = '\0';
                            int ok = 1;
                            if (length > 0) {
                                size_t line_start = 0;
                                size_t i = 0;
                                while (i < length) {
                                    if (buffer[i] == '\r' || buffer[i] == '\n') {
                                        size_t line_len = i - line_start;
                                        char *line = (char *)malloc(line_len + 1);
                                        if (line == NULL) {
                                            report_error(parser, name.line, name.column,
                                                         MESSAGE_OUT_OF_MEMORY);
                                            ok = 0;
                                            break;
                                        }
                                        memcpy(line, buffer + line_start, line_len);
                                        line[line_len] = '\0';
                                        if (!store_owned_string(parser, name, line)) {
                                            ok = 0;
                                            break;
                                        }
                                        Value item = number_value(0.0);
                                        item.kind = VALUE_STRING;
                                        item.string_length = line_len;
                                        item.owned_string = line;
                                        if (!append_list_item(parser, list, item, name)) {
                                            ok = 0;
                                            break;
                                        }
                                        if (buffer[i] == '\r' && i + 1 < length && buffer[i + 1] == '\n') {
                                            i += 2;
                                        } else {
                                            i += 1;
                                        }
                                        line_start = i;
                                    } else {
                                        i++;
                                    }
                                }
                                if (ok && line_start < length) {
                                    size_t line_len = length - line_start;
                                    char *line = (char *)malloc(line_len + 1);
                                    if (line == NULL) {
                                        report_error(parser, name.line, name.column,
                                                     MESSAGE_OUT_OF_MEMORY);
                                        ok = 0;
                                    } else {
                                        memcpy(line, buffer + line_start, line_len);
                                        line[line_len] = '\0';
                                        if (!store_owned_string(parser, name, line)) {
                                            ok = 0;
                                        } else {
                                            Value item = number_value(0.0);
                                            item.kind = VALUE_STRING;
                                            item.string_length = line_len;
                                            item.owned_string = line;
                                            if (!append_list_item(parser, list, item, name)) {
                                                ok = 0;
                                            }
                                        }
                                    }
                                }
                            }
                            free(buffer);
                            if (ok) {
                                result = number_value(0.0);
                                result.kind = VALUE_LIST;
                                result.list = list;
                            }
                        }
                    }
                }
            } else if (token_matches(parser, name, "જમણે_કાપો") ||
                       token_matches(parser, name, "jamne_kapo") ||
                       token_matches(parser, name, "જમણે_સાફ") ||
                       token_matches(parser, name, "jamne_saf")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_STRING_FOR_JAMNE_KAPO);
                } else {
                    size_t length = decoded_string_length(parser, arguments[0]);
                    char *buffer = (char *)malloc(length + 1);
                    if (buffer == NULL) {
                        report_error(parser, name.line, name.column,
                                     MESSAGE_OUT_OF_MEMORY);
                    } else {
                        size_t end = length;
                        char *trimmed;

                        copy_value_string(parser, arguments[0], buffer);
                        buffer[length] = '\0';

                        while (end > 0 &&
                               (buffer[end - 1] == ' ' || buffer[end - 1] == '\t' ||
                                buffer[end - 1] == '\r' || buffer[end - 1] == '\n')) {
                            end--;
                        }
                        trimmed = (char *)malloc(end + 1);
                        if (trimmed == NULL) {
                            free(buffer);
                            report_error(parser, name.line, name.column,
                                         MESSAGE_OUT_OF_MEMORY);
                        } else {
                            memcpy(trimmed, buffer, end);
                            trimmed[end] = '\0';
                            free(buffer);
                            if (!store_input_string(parser, name, trimmed)) {
                                result = number_value(0.0);
                            } else {
                                result.kind = VALUE_STRING;
                                result.string_offset = 0;
                                result.string_length = end;
                                result.owned_string = trimmed;
                            }
                        }
                    }
                }
            } else if (token_matches(parser, name, "ડાબે_કાપો") ||
                       token_matches(parser, name, "dabe_kapo") ||
                       token_matches(parser, name, "ડાબે_સાફ") ||
                       token_matches(parser, name, "dabe_saf")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_STRING_FOR_DABE_KAPO);
                } else {
                    size_t length = decoded_string_length(parser, arguments[0]);
                    char *buffer = (char *)malloc(length + 1);
                    if (buffer == NULL) {
                        report_error(parser, name.line, name.column,
                                     MESSAGE_OUT_OF_MEMORY);
                    } else {
                        size_t start = 0;
                        size_t trimmed_len;
                        char *trimmed;

                        copy_value_string(parser, arguments[0], buffer);
                        buffer[length] = '\0';

                        while (start < length &&
                               (buffer[start] == ' ' || buffer[start] == '\t' ||
                                buffer[start] == '\r' || buffer[start] == '\n')) {
                            start++;
                        }
                        trimmed_len = length - start;
                        trimmed = (char *)malloc(trimmed_len + 1);
                        if (trimmed == NULL) {
                            free(buffer);
                            report_error(parser, name.line, name.column,
                                         MESSAGE_OUT_OF_MEMORY);
                        } else {
                            memcpy(trimmed, buffer + start, trimmed_len);
                            trimmed[trimmed_len] = '\0';
                            free(buffer);
                            if (!store_input_string(parser, name, trimmed)) {
                                result = number_value(0.0);
                            } else {
                                result.kind = VALUE_STRING;
                                result.string_offset = 0;
                                result.string_length = trimmed_len;
                                result.owned_string = trimmed;
                            }
                        }
                    }
                }
            } else if (token_matches(parser, name, "ગણતરી") ||
                       token_matches(parser, name, "ganatari") ||
                       token_matches(parser, name, "ગણતરી_વસ્તુ") ||
                       token_matches(parser, name, "ganatari_vastu")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_LIST &&
                           arguments[0].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_LIST_OR_STRING_FOR_GANATARI);
                } else if (arguments[0].kind == VALUE_STRING &&
                           arguments[1].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_STRING_SECOND_FOR_GANATARI);
                } else if (arguments[0].kind == VALUE_LIST) {
                    List *list = arguments[0].list;
                    double count = 0.0;
                    size_t i;
                    for (i = 0; i < list->count; i++) {
                        if (values_are_equal(parser, list->items[i], arguments[1])) {
                            count += 1.0;
                        }
                    }
                    result = number_value(count);
                } else {
                    size_t h_len = decoded_string_length(parser, arguments[0]);
                    size_t n_len = decoded_string_length(parser, arguments[1]);
                    if (n_len == 0) {
                        result = number_value(0.0);
                    } else {
                        char *h_buf = (char *)malloc(h_len + 1);
                        char *n_buf = (char *)malloc(n_len + 1);
                        if (h_buf == NULL || n_buf == NULL) {
                            free(h_buf);
                            free(n_buf);
                            report_error(parser, name.line, name.column,
                                         MESSAGE_OUT_OF_MEMORY);
                        } else {
                            size_t pos = 0;
                            double count = 0.0;
                            copy_value_string(parser, arguments[0], h_buf);
                            h_buf[h_len] = '\0';
                            copy_value_string(parser, arguments[1], n_buf);
                            n_buf[n_len] = '\0';
                            if (h_len >= n_len) {
                                size_t max_pos = h_len - n_len;
                                while (pos <= max_pos) {
                                    if (memcmp(h_buf + pos, n_buf, n_len) == 0) {
                                        count += 1.0;
                                        pos += n_len;
                                    } else {
                                        pos++;
                                    }
                                }
                            }
                            free(h_buf);
                            free(n_buf);
                            result = number_value(count);
                        }
                    }
                }
            } else if (token_matches(parser, name, "યાદી_મહત્તમ") ||
                       token_matches(parser, name, "yadi_mahatam")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_LIST) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_LIST_FOR_YADI_MAHATAM);
                } else if (arguments[0].list->count == 0) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EMPTY_LIST_FOR_YADI_MAHATAM);
                } else {
                    List *list = arguments[0].list;
                    double max_val = 0.0;
                    int ok = 1;
                    for (size_t i = 0; i < list->count; i++) {
                        if (list->items[i].kind != VALUE_NUMBER) {
                            report_error(parser, name.line, name.column,
                                         MESSAGE_EXPECTED_NUMERIC_LIST_FOR_YADI_MAHATAM);
                            ok = 0;
                            break;
                        }
                        if (i == 0 || list->items[i].number > max_val) {
                            max_val = list->items[i].number;
                        }
                    }
                    if (ok) {
                        result = number_value(max_val);
                    }
                }
            } else if (token_matches(parser, name, "યાદી_ન્યૂનતમ") ||
                       token_matches(parser, name, "yadi_nyunatam")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_LIST) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_LIST_FOR_YADI_NYUNATAM);
                } else if (arguments[0].list->count == 0) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EMPTY_LIST_FOR_YADI_NYUNATAM);
                } else {
                    List *list = arguments[0].list;
                    double min_val = 0.0;
                    int ok = 1;
                    for (size_t i = 0; i < list->count; i++) {
                        if (list->items[i].kind != VALUE_NUMBER) {
                            report_error(parser, name.line, name.column,
                                         MESSAGE_EXPECTED_NUMERIC_LIST_FOR_YADI_NYUNATAM);
                            ok = 0;
                            break;
                        }
                        if (i == 0 || list->items[i].number < min_val) {
                            min_val = list->items[i].number;
                        }
                    }
                    if (ok) {
                        result = number_value(min_val);
                    }
                }
            } else if (token_matches(parser, name, "સરવાળો_યાદી") ||
                       token_matches(parser, name, "sarvalo_yadi")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_LIST) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_LIST_FOR_SARVALO_YADI);
                } else {
                    List *list = arguments[0].list;
                    double sum = 0.0;
                    int ok = 1;
                    for (size_t i = 0; i < list->count; i++) {
                        if (list->items[i].kind != VALUE_NUMBER) {
                            report_error(parser, name.line, name.column,
                                         MESSAGE_EXPECTED_NUMERIC_LIST_ELEMENTS);
                            ok = 0;
                            break;
                        }
                        sum += list->items[i].number;
                    }
                    if (ok) {
                        result = number_value(sum);
                    }
                }
            } else if (token_matches(parser, name, "યાદી_ભરો") ||
                       token_matches(parser, name, "yadi_bharo")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_NUMBER ||
                           arguments[0].number < 0.0 ||
                           arguments[0].number >= (double)(size_t)-1 ||
                           arguments[0].number != (double)(size_t)arguments[0].number) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_YADI_BHARO_COUNT_INTEGER);
                } else {
                    size_t count = (size_t)arguments[0].number;
                    List *list = create_list(parser, name);
                    if (list != NULL) {
                        int ok = 1;
                        for (size_t i = 0; i < count; i++) {
                            if (!append_list_item(parser, list, arguments[1], name)) {
                                ok = 0;
                                break;
                            }
                        }
                        if (ok) {
                            result.kind = VALUE_LIST;
                            result.list = list;
                        }
                    }
                }
            } else if (token_matches(parser, name, "કોડ_થી_અક્ષર") ||
                       token_matches(parser, name, "kod_thi_akshar")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_NUMBER) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_NUMERIC_MATH_ARGUMENT);
                } else {
                    double num = arguments[0].number;
                    if (num < 0.0 || num > 0x10FFFF || num != floor(num) || (num >= 0xD800 && num <= 0xDFFF)) {
                        report_error(parser, name.line, name.column,
                                     MESSAGE_INVALID_UNICODE_CODEPOINT);
                    } else {
                        char *str = (char *)malloc(5);
                        if (str == NULL) {
                            report_error(parser, name.line, name.column, MESSAGE_OUT_OF_MEMORY);
                        } else {
                            size_t byte_len = utf8_encode_codepoint((unsigned int)num, str);
                            str[byte_len] = '\0';
                            if (!store_owned_string(parser, name, str)) {
                                free(str);
                            } else {
                                result.kind = VALUE_STRING;
                                result.string_length = byte_len;
                                result.owned_string = str;
                            }
                        }
                    }
                }
            } else if (token_matches(parser, name, "અક્ષર_કોડ") ||
                       token_matches(parser, name, "akshar_kod")) {
                if (argument_count != 1 && argument_count != 2) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_STRING_FOR_AKSHAR_KOD);
                } else if (argument_count == 2 && (arguments[1].kind != VALUE_NUMBER ||
                           arguments[1].number < 0.0 ||
                           arguments[1].number >= (double)(size_t)-1 ||
                           arguments[1].number != (double)(size_t)arguments[1].number)) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_AKSHAR_KOD_INTEGER);
                } else {
                    size_t length = decoded_string_length(parser, arguments[0]);
                    char *buffer = (char *)malloc(length + 1);
                    if (buffer == NULL) {
                        report_error(parser, name.line, name.column, MESSAGE_OUT_OF_MEMORY);
                    } else {
                        copy_value_string(parser, arguments[0], buffer);
                        buffer[length] = '\0';
                        size_t total_cp = utf8_total_codepoints(buffer, length);
                        size_t target_idx = 0;
                        if (argument_count == 2) {
                            target_idx = (size_t)arguments[1].number;
                        }
                        if (target_idx >= total_cp) {
                            free(buffer);
                            report_error(parser, name.line, name.column,
                                         MESSAGE_AKSHAR_KOD_INDEX_OUT_OF_RANGE);
                        } else {
                            size_t b_start = utf8_codepoint_to_byte_offset(buffer, length, target_idx);
                            size_t b_end = utf8_codepoint_to_byte_offset(buffer, length, target_idx + 1);
                            unsigned int cp = utf8_decode_codepoint(buffer + b_start, b_end - b_start);
                            free(buffer);
                            result = number_value((double)cp);
                        }
                    }
                }
            } else if (token_matches(parser, name, "લઘુગણક") ||
                       token_matches(parser, name, "laghuganak")) {
                if (argument_count != 1 && argument_count != 2) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_NUMBER ||
                           (argument_count == 2 && arguments[1].kind != VALUE_NUMBER)) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_NUMERIC_MATH_ARGUMENT);
                } else if (arguments[0].number <= 0.0) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_LAGHUGANAK_DOMAIN_ERROR);
                } else if (argument_count == 2 && (arguments[1].number <= 0.0 || arguments[1].number == 1.0)) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_LAGHUGANAK_BASE_ERROR);
                } else {
                    double n = arguments[0].number;
                    if (argument_count == 1) {
                        result = number_value(log(n));
                    } else {
                        double base = arguments[1].number;
                        result = number_value(log(n) / log(base));
                    }
                }
            } else if (token_matches(parser, name, "ચિહ્ન") ||
                       token_matches(parser, name, "chihna")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_NUMBER) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_NUMERIC_MATH_ARGUMENT);
                } else {
                    double n = arguments[0].number;
                    if (n > 0.0) {
                        result = number_value(1.0);
                    } else if (n < 0.0) {
                        result = number_value(-1.0);
                    } else {
                        result = number_value(0.0);
                    }
                }
            } else if (token_matches(parser, name, "ઈ") ||
                       token_matches(parser, name, "e")) {
                if (argument_count != 0) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    result = number_value(GUJARATI_E);
                }
            } else if (token_matches(parser, name, "પાઈ") ||
                       token_matches(parser, name, "pi")) {
                if (argument_count != 0) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    result = number_value(GUJARATI_PI);
                }
            } else if (token_matches(parser, name, "વિસ્તારો") ||
                       token_matches(parser, name, "vistaro")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_LIST ||
                           arguments[1].kind != VALUE_LIST) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_LIST_FOR_VISTARO);
                } else {
                    List *dst = arguments[0].list;
                    List *src = arguments[1].list;
                    size_t count = src->count;
                    int success = 1;
                    for (size_t i = 0; i < count; i++) {
                        if (!append_list_item(parser, dst, src->items[i], name)) {
                            success = 0;
                            break;
                        }
                    }
                    if (success) {
                        result = arguments[0];
                    }
                }
            } else if (token_matches(parser, name, "ઉમેરો") ||
                       token_matches(parser, name, "umero")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_LIST) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_LIST_FOR_UMERO);
                } else {
                    if (append_list_item(parser, arguments[0].list, arguments[1], name)) {
                        result = arguments[0];
                    }
                }
            } else if (token_matches(parser, name, "કાપો") ||
                       token_matches(parser, name, "kapo")) {
                if (argument_count != 2 && argument_count != 3) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_STRING_FOR_KAPO);
                } else if (arguments[1].kind != VALUE_NUMBER ||
                           arguments[1].number < 0.0 ||
                           arguments[1].number >= (double)(size_t)-1 ||
                           arguments[1].number != (double)(size_t)arguments[1].number ||
                           (argument_count == 3 &&
                            (arguments[2].kind != VALUE_NUMBER ||
                             arguments[2].number < 0.0 ||
                             arguments[2].number >= (double)(size_t)-1 ||
                             arguments[2].number != (double)(size_t)arguments[2].number))) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_KAPO_INTEGER);
                } else {
                    size_t length = decoded_string_length(parser, arguments[0]);
                    char *buffer = (char *)malloc(length + 1);
                    if (buffer == NULL) {
                        report_error(parser, name.line, name.column,
                                     MESSAGE_OUT_OF_MEMORY);
                    } else {
                        size_t total_cp;
                        size_t start_cp;
                        size_t end_cp;
                        size_t start_byte;
                        size_t end_byte;
                        size_t slice_bytes;
                        char *slice;

                        copy_value_string(parser, arguments[0], buffer);
                        buffer[length] = '\0';
                        total_cp = utf8_total_codepoints(buffer, length);
                        start_cp = (size_t)arguments[1].number;
                        if (start_cp >= total_cp) {
                            free(buffer);
                            slice = (char *)malloc(1);
                            if (slice == NULL) {
                                report_error(parser, name.line, name.column,
                                             MESSAGE_OUT_OF_MEMORY);
                            } else {
                                slice[0] = '\0';
                                if (store_owned_string(parser, name, slice)) {
                                    result = number_value(0.0);
                                    result.kind = VALUE_STRING;
                                    result.string_length = 0;
                                    result.owned_string = slice;
                                }
                            }
                        } else {
                            if (argument_count == 2) {
                                end_cp = total_cp;
                            } else {
                                size_t req_len = (size_t)arguments[2].number;
                                end_cp = (start_cp + req_len > total_cp) ?
                                         total_cp : start_cp + req_len;
                            }
                            start_byte = utf8_codepoint_to_byte_offset(buffer, length, start_cp);
                            end_byte = utf8_codepoint_to_byte_offset(buffer, length, end_cp);
                            slice_bytes = end_byte - start_byte;
                            slice = (char *)malloc(slice_bytes + 1);
                            if (slice == NULL) {
                                free(buffer);
                                report_error(parser, name.line, name.column,
                                             MESSAGE_OUT_OF_MEMORY);
                            } else {
                                memcpy(slice, buffer + start_byte, slice_bytes);
                                slice[slice_bytes] = '\0';
                                free(buffer);
                                if (store_owned_string(parser, name, slice)) {
                                    result = number_value(0.0);
                                    result.kind = VALUE_STRING;
                                    result.string_length = slice_bytes;
                                    result.owned_string = slice;
                                }
                            }
                        }
                    }
                }
            } else if (token_matches(parser, name, "શોધો") ||
                       token_matches(parser, name, "shodho")) {
                if (argument_count != 2 && argument_count != 3) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING ||
                           arguments[1].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_STRING_FOR_SHODHO);
                } else if (argument_count == 3 &&
                           (arguments[2].kind != VALUE_NUMBER ||
                            arguments[2].number < 0.0 ||
                            arguments[2].number >= (double)(size_t)-1 ||
                            arguments[2].number != (double)(size_t)arguments[2].number)) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_SHODHO_INTEGER);
                } else {
                    size_t h_len = decoded_string_length(parser, arguments[0]);
                    size_t n_len = decoded_string_length(parser, arguments[1]);
                    char *h_buf = (char *)malloc(h_len + 1);
                    char *n_buf = (char *)malloc(n_len + 1);
                    if (h_buf == NULL || n_buf == NULL) {
                        free(h_buf);
                        free(n_buf);
                        report_error(parser, name.line, name.column,
                                     MESSAGE_OUT_OF_MEMORY);
                    } else {
                        size_t start_cp;
                        size_t total_h_cp;
                        copy_value_string(parser, arguments[0], h_buf);
                        h_buf[h_len] = '\0';
                        copy_value_string(parser, arguments[1], n_buf);
                        n_buf[n_len] = '\0';
                        start_cp = (argument_count == 3) ? (size_t)arguments[2].number : 0;
                        total_h_cp = utf8_total_codepoints(h_buf, h_len);
                        if (start_cp > total_h_cp) {
                            free(h_buf);
                            free(n_buf);
                            result = number_value(-1.0);
                        } else if (n_len == 0) {
                            free(h_buf);
                            free(n_buf);
                            result = number_value((double)start_cp);
                        } else {
                            size_t start_byte = utf8_codepoint_to_byte_offset(h_buf, h_len, start_cp);
                            double found = -1.0;
                            if (start_byte + n_len <= h_len) {
                                size_t max_pos = h_len - n_len;
                                size_t pos = start_byte;
                                while (pos <= max_pos) {
                                    if (memcmp(h_buf + pos, n_buf, n_len) == 0) {
                                        size_t cp_idx = 0;
                                        size_t k;
                                        for (k = 0; k < pos; k++) {
                                            if (((unsigned char)h_buf[k] & 0xC0) != 0x80) {
                                                cp_idx++;
                                            }
                                        }
                                        found = (double)cp_idx;
                                        break;
                                    }
                                    pos++;
                                    while (pos <= max_pos && ((unsigned char)h_buf[pos] & 0xC0) == 0x80) {
                                        pos++;
                                    }
                                }
                            }
                            free(h_buf);
                            free(n_buf);
                            result = number_value(found);
                        }
                    }
                }
            } else if (token_matches(parser, name, "કાઢો") ||
                       token_matches(parser, name, "kadho")) {
                if (argument_count != 1 && argument_count != 2) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_LIST) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_LIST_FOR_KADHO);
                } else if (arguments[0].list->count == 0) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_KADHO_EMPTY_LIST);
                } else {
                    size_t target_idx = 0;
                    int valid = 1;
                    if (argument_count == 1) {
                        target_idx = arguments[0].list->count - 1;
                    } else {
                        if (arguments[1].kind != VALUE_NUMBER ||
                            arguments[1].number < 0.0 ||
                            arguments[1].number >= (double)(size_t)-1 ||
                            arguments[1].number != (double)(size_t)arguments[1].number) {
                            report_error(parser, name.line, name.column,
                                         MESSAGE_LIST_INDEX_MUST_BE_INTEGER);
                            valid = 0;
                        } else if ((size_t)arguments[1].number >= arguments[0].list->count) {
                            report_error(parser, name.line, name.column,
                                         MESSAGE_LIST_INDEX_OUT_OF_RANGE);
                            valid = 0;
                        } else {
                            target_idx = (size_t)arguments[1].number;
                        }
                    }
                    if (valid) {
                        size_t i;
                        result = arguments[0].list->items[target_idx];
                        for (i = target_idx; i + 1 < arguments[0].list->count; i++) {
                            arguments[0].list->items[i] = arguments[0].list->items[i + 1];
                        }
                        arguments[0].list->count--;
                    }
                }
            } else if (token_matches(parser, name, "પહેલી_એબીસીડી") ||
                       token_matches(parser, name, "peli_abcd")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_STRING_FOR_CASE);
                } else {
                    size_t length = decoded_string_length(parser, arguments[0]);
                    char *buffer = (char *)malloc(length + 1);
                    if (buffer == NULL) {
                        report_error(parser, name.line, name.column,
                                     MESSAGE_OUT_OF_MEMORY);
                    } else {
                        size_t i;
                        copy_value_string(parser, arguments[0], buffer);
                        buffer[length] = '\0';
                        for (i = 0; i < length; i++) {
                            if (buffer[i] >= 'a' && buffer[i] <= 'z') {
                                buffer[i] = (char)(buffer[i] - ('a' - 'A'));
                            }
                        }
                        if (store_owned_string(parser, name, buffer)) {
                            result = number_value(0.0);
                            result.kind = VALUE_STRING;
                            result.string_length = length;
                            result.owned_string = buffer;
                        }
                    }
                }
            } else if (token_matches(parser, name, "બીજી_એબીસીડી") ||
                       token_matches(parser, name, "biji_abcd")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_STRING_FOR_CASE);
                } else {
                    size_t length = decoded_string_length(parser, arguments[0]);
                    char *buffer = (char *)malloc(length + 1);
                    if (buffer == NULL) {
                        report_error(parser, name.line, name.column,
                                     MESSAGE_OUT_OF_MEMORY);
                    } else {
                        size_t i;
                        copy_value_string(parser, arguments[0], buffer);
                        buffer[length] = '\0';
                        for (i = 0; i < length; i++) {
                            if (buffer[i] >= 'A' && buffer[i] <= 'Z') {
                                buffer[i] = (char)(buffer[i] + ('a' - 'A'));
                            }
                        }
                        if (store_owned_string(parser, name, buffer)) {
                            result = number_value(0.0);
                            result.kind = VALUE_STRING;
                            result.string_length = length;
                            result.owned_string = buffer;
                        }
                    }
                }
            } else if (token_matches(parser, name, "મહત્તમ") ||
                       token_matches(parser, name, "mahatam")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_NUMBER ||
                           arguments[1].kind != VALUE_NUMBER) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_NUMERIC_MATH_ARGUMENT);
                } else {
                    double a = arguments[0].number;
                    double b = arguments[1].number;
                    result = number_value(a >= b ? a : b);
                }
            } else if (token_matches(parser, name, "ન્યૂનતમ") ||
                       token_matches(parser, name, "nyunatam")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_NUMBER ||
                           arguments[1].kind != VALUE_NUMBER) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_NUMERIC_MATH_ARGUMENT);
                } else {
                    double a = arguments[0].number;
                    double b = arguments[1].number;
                    result = number_value(a <= b ? a : b);
                }
            } else if (token_matches(parser, name, "ધન_મૂલ્ય") ||
                       token_matches(parser, name, "dhan_mulya")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_NUMBER) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_NUMERIC_MATH_ARGUMENT);
                } else {
                    double val = arguments[0].number;
                    result = number_value(val < 0.0 ? -val : val);
                }
            } else if (token_matches(parser, name, "સીમા") ||
                       token_matches(parser, name, "sima")) {
                if (argument_count != 3) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_NUMBER ||
                           arguments[1].kind != VALUE_NUMBER ||
                           arguments[2].kind != VALUE_NUMBER) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_NUMERIC_MATH_ARGUMENT);
                } else if (arguments[1].number > arguments[2].number) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_SIMA_MIN_GREATER_THAN_MAX);
                } else {
                    double val = arguments[0].number;
                    double min_b = arguments[1].number;
                    double max_b = arguments[2].number;
                    if (val < min_b) {
                        result = number_value(min_b);
                    } else if (val > max_b) {
                        result = number_value(max_b);
                    } else {
                        result = number_value(val);
                    }
                }
            } else if (token_matches(parser, name, "બીજ") ||
                       token_matches(parser, name, "beej")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_NUMBER) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_NUMERIC_MATH_ARGUMENT);
                } else {
                    double s = arguments[0].number;
                    set_prng_seed((unsigned long long)(s < 0.0 ? -s : s));
                    result = null_value();
                }
            } else if (token_matches(parser, name, "યાદચ્છિક") ||
                       token_matches(parser, name, "yadachhik")) {
                if (argument_count != 0 && argument_count != 2) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (argument_count == 0) {
                    result = number_value(next_random_double());
                } else {
                    if (arguments[0].kind != VALUE_NUMBER ||
                        arguments[1].kind != VALUE_NUMBER) {
                        report_error(parser, name.line, name.column,
                                     MESSAGE_EXPECTED_NUMERIC_MATH_ARGUMENT);
                    } else if (arguments[0].number != floor(arguments[0].number) ||
                               arguments[1].number != floor(arguments[1].number)) {
                        report_error(parser, name.line, name.column,
                                     MESSAGE_EXPECTED_INTEGER_YADACHHIK);
                    } else if (arguments[0].number > arguments[1].number) {
                        report_error(parser, name.line, name.column,
                                     MESSAGE_YADACHHIK_MIN_GREATER_THAN_MAX);
                    } else {
                        long long min_val = (long long)arguments[0].number;
                        long long max_val = (long long)arguments[1].number;
                        unsigned long long range = (unsigned long long)(max_val - min_val) + 1ULL;
                        double r = next_random_double();
                        long long offset = (long long)(r * (double)range);
                        if (offset >= (long long)range) {
                            offset = (long long)range - 1;
                        }
                        result = number_value((double)(min_val + offset));
                    }
                }
            } else if (token_matches(parser, name, "ઉલટાવો") ||
                       token_matches(parser, name, "ultavo")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_LIST) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_LIST_FOR_ULTAVO);
                } else {
                    if (arguments[0].list->count > 1) {
                        size_t left = 0;
                        size_t right = arguments[0].list->count - 1;
                        while (left < right) {
                            Value temp = arguments[0].list->items[left];
                            arguments[0].list->items[left] = arguments[0].list->items[right];
                            arguments[0].list->items[right] = temp;
                            left++;
                            right--;
                        }
                    }
                    result = arguments[0];
                }
            } else if (token_matches(parser, name, "ભાગ") ||
                       token_matches(parser, name, "bhag")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING ||
                           arguments[1].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_STRING_FOR_BHAG);
                } else {
                    List *list = create_list(parser, name);
                    if (list != NULL) {
                        size_t src_len = decoded_string_length(parser, arguments[0]);
                        size_t delim_len = decoded_string_length(parser, arguments[1]);
                        char *src_buf = (char *)malloc(src_len + 1);
                        char *delim_buf = (char *)malloc(delim_len + 1);
                        if (src_buf == NULL || delim_buf == NULL) {
                            free(src_buf);
                            free(delim_buf);
                            report_error(parser, name.line, name.column,
                                         MESSAGE_OUT_OF_MEMORY);
                        } else {
                            copy_value_string(parser, arguments[0], src_buf);
                            src_buf[src_len] = '\0';
                            copy_value_string(parser, arguments[1], delim_buf);
                            delim_buf[delim_len] = '\0';

                            if (delim_len == 0) {
                                size_t total_cp = utf8_total_codepoints(src_buf, src_len);
                                size_t cp;
                                int ok = 1;
                                for (cp = 0; cp < total_cp; cp++) {
                                    size_t b_start = utf8_codepoint_to_byte_offset(src_buf, src_len, cp);
                                    size_t b_end = utf8_codepoint_to_byte_offset(src_buf, src_len, cp + 1);
                                    size_t piece_len = b_end - b_start;
                                    char *piece = (char *)malloc(piece_len + 1);
                                    if (piece == NULL) {
                                        report_error(parser, name.line, name.column,
                                                     MESSAGE_OUT_OF_MEMORY);
                                        ok = 0;
                                        break;
                                    }
                                    memcpy(piece, src_buf + b_start, piece_len);
                                    piece[piece_len] = '\0';
                                    if (!store_owned_string(parser, name, piece)) {
                                        ok = 0;
                                        break;
                                    }
                                    Value piece_val = number_value(0.0);
                                    piece_val.kind = VALUE_STRING;
                                    piece_val.string_length = piece_len;
                                    piece_val.owned_string = piece;
                                    if (!append_list_item(parser, list, piece_val, name)) {
                                        ok = 0;
                                        break;
                                    }
                                }
                                free(src_buf);
                                free(delim_buf);
                                if (ok) {
                                    result = number_value(0.0);
                                    result.kind = VALUE_LIST;
                                    result.list = list;
                                }
                            } else {
                                size_t cur = 0;
                                int ok = 1;
                                while (cur <= src_len) {
                                    size_t match_pos = (size_t)-1;
                                    size_t scan;
                                    for (scan = cur; scan + delim_len <= src_len; scan++) {
                                        if (memcmp(src_buf + scan, delim_buf, delim_len) == 0) {
                                            match_pos = scan;
                                            break;
                                        }
                                    }
                                    if (match_pos != (size_t)-1) {
                                        size_t part_len = match_pos - cur;
                                        char *part = (char *)malloc(part_len + 1);
                                        if (part == NULL) {
                                            report_error(parser, name.line, name.column,
                                                         MESSAGE_OUT_OF_MEMORY);
                                            ok = 0;
                                            break;
                                        }
                                        memcpy(part, src_buf + cur, part_len);
                                        part[part_len] = '\0';
                                        if (!store_owned_string(parser, name, part)) {
                                            ok = 0;
                                            break;
                                        }
                                        Value item = number_value(0.0);
                                        item.kind = VALUE_STRING;
                                        item.string_length = part_len;
                                        item.owned_string = part;
                                        if (!append_list_item(parser, list, item, name)) {
                                            ok = 0;
                                            break;
                                        }
                                        cur = match_pos + delim_len;
                                    } else {
                                        size_t part_len = src_len - cur;
                                        char *part = (char *)malloc(part_len + 1);
                                        if (part == NULL) {
                                            report_error(parser, name.line, name.column,
                                                         MESSAGE_OUT_OF_MEMORY);
                                            ok = 0;
                                            break;
                                        }
                                        memcpy(part, src_buf + cur, part_len);
                                        part[part_len] = '\0';
                                        if (!store_owned_string(parser, name, part)) {
                                            ok = 0;
                                            break;
                                        }
                                        Value item = number_value(0.0);
                                        item.kind = VALUE_STRING;
                                        item.string_length = part_len;
                                        item.owned_string = part;
                                        if (!append_list_item(parser, list, item, name)) {
                                            ok = 0;
                                            break;
                                        }
                                        break;
                                    }
                                }
                                free(src_buf);
                                free(delim_buf);
                                if (ok) {
                                    result = number_value(0.0);
                                    result.kind = VALUE_LIST;
                                    result.list = list;
                                }
                            }
                        }
                    }
                }
            } else if (token_matches(parser, name, "જોડો") ||
                       token_matches(parser, name, "jodo")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_LIST ||
                           arguments[1].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_LIST_AND_STRING_FOR_JODO);
                } else {
                    size_t sep_len = decoded_string_length(parser, arguments[1]);
                    char *sep_buf = (char *)malloc(sep_len + 1);
                    if (sep_buf == NULL) {
                        report_error(parser, name.line, name.column,
                                     MESSAGE_OUT_OF_MEMORY);
                    } else {
                        List *ancestors[256];
                        StringBuffer sb;
                        size_t i;
                        copy_value_string(parser, arguments[1], sep_buf);
                        sep_buf[sep_len] = '\0';
                        sb_init(&sb);
                        if (sb.failed) {
                            free(sep_buf);
                            report_error(parser, name.line, name.column,
                                         MESSAGE_OUT_OF_MEMORY_FOR_STRING);
                        } else {
                            for (i = 0; i < arguments[0].list->count; i++) {
                                if (i > 0 && sep_len > 0) {
                                    sb_append(&sb, sep_buf, sep_len);
                                }
                                format_value_to_buffer(parser,
                                                       arguments[0].list->items[i],
                                                       &sb, ancestors, 0);
                            }
                            free(sep_buf);
                            if (sb.failed) {
                                free(sb.data);
                                report_error(parser, name.line, name.column,
                                             MESSAGE_OUT_OF_MEMORY_FOR_STRING);
                            } else {
                                if (store_owned_string(parser, name, sb.data)) {
                                    result = number_value(0.0);
                                    result.kind = VALUE_STRING;
                                    result.string_length = sb.length;
                                    result.owned_string = sb.data;
                                }
                            }
                        }
                    }
                }
            } else if (token_matches(parser, name, "સાફ") ||
                       token_matches(parser, name, "saf")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_STRING_FOR_SAF);
                } else {
                    size_t length = decoded_string_length(parser, arguments[0]);
                    char *buffer = (char *)malloc(length + 1);
                    if (buffer == NULL) {
                        report_error(parser, name.line, name.column,
                                     MESSAGE_OUT_OF_MEMORY);
                    } else {
                        size_t start = 0;
                        size_t end;
                        size_t trimmed_len;
                        char *trimmed;

                        copy_value_string(parser, arguments[0], buffer);
                        buffer[length] = '\0';

                        while (start < length &&
                               (buffer[start] == ' ' || buffer[start] == '\t' ||
                                buffer[start] == '\r' || buffer[start] == '\n')) {
                            start++;
                        }
                        if (start == length) {
                            free(buffer);
                            trimmed = (char *)malloc(1);
                            if (trimmed == NULL) {
                                report_error(parser, name.line, name.column,
                                             MESSAGE_OUT_OF_MEMORY);
                            } else {
                                trimmed[0] = '\0';
                                if (store_owned_string(parser, name, trimmed)) {
                                    result = number_value(0.0);
                                    result.kind = VALUE_STRING;
                                    result.string_length = 0;
                                    result.owned_string = trimmed;
                                }
                            }
                        } else {
                            end = length;
                            while (end > start &&
                                   (buffer[end - 1] == ' ' || buffer[end - 1] == '\t' ||
                                    buffer[end - 1] == '\r' || buffer[end - 1] == '\n')) {
                                end--;
                            }
                            trimmed_len = end - start;
                            trimmed = (char *)malloc(trimmed_len + 1);
                            if (trimmed == NULL) {
                                free(buffer);
                                report_error(parser, name.line, name.column,
                                             MESSAGE_OUT_OF_MEMORY);
                            } else {
                                memcpy(trimmed, buffer + start, trimmed_len);
                                trimmed[trimmed_len] = '\0';
                                free(buffer);
                                if (store_owned_string(parser, name, trimmed)) {
                                    result = number_value(0.0);
                                    result.kind = VALUE_STRING;
                                    result.string_length = trimmed_len;
                                    result.owned_string = trimmed;
                                }
                            }
                        }
                    }
                }
            } else if (token_matches(parser, name, "ઘાત") ||
                       token_matches(parser, name, "ghat")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_NUMBER ||
                           arguments[1].kind != VALUE_NUMBER) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_NUMERIC_MATH_ARGUMENT);
                } else if (arguments[0].number == 0.0 && arguments[1].number < 0.0) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_DIVISION_BY_ZERO);
                } else {
                    result = number_value(pow(arguments[0].number, arguments[1].number));
                }
            } else if (token_matches(parser, name, "મૂળ") ||
                       token_matches(parser, name, "mul")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_NUMBER) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_NUMERIC_MATH_ARGUMENT);
                } else if (arguments[0].number < 0.0) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_NEGATIVE_SQUARE_ROOT);
                } else {
                    result = number_value(sqrt(arguments[0].number));
                }
            } else if (token_matches(parser, name, "ગોઠવો") ||
                       token_matches(parser, name, "gothvo")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_LIST) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_LIST_FOR_GOTHVO);
                } else {
                    List *list = arguments[0].list;
                    if (list->count > 1) {
                        size_t i;
                        for (i = 1; i < list->count; i++) {
                            Value key = list->items[i];
                            size_t j = i;
                            while (j > 0 && compare_sort_values(parser, list->items[j - 1], key) > 0) {
                                list->items[j] = list->items[j - 1];
                                j--;
                            }
                            list->items[j] = key;
                        }
                    }
                    result = arguments[0];
                }
            } else if (token_matches(parser, name, "બદલો") ||
                       token_matches(parser, name, "badlo")) {
                if (argument_count != 3) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING ||
                           arguments[1].kind != VALUE_STRING ||
                           arguments[2].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_STRING_FOR_BADLO);
                } else {
                    size_t src_len = decoded_string_length(parser, arguments[0]);
                    size_t target_len = decoded_string_length(parser, arguments[1]);
                    size_t repl_len = decoded_string_length(parser, arguments[2]);
                    char *src_buf = (char *)malloc(src_len + 1);
                    char *target_buf = (char *)malloc(target_len + 1);
                    char *repl_buf = (char *)malloc(repl_len + 1);
                    if (src_buf == NULL || target_buf == NULL || repl_buf == NULL) {
                        free(src_buf);
                        free(target_buf);
                        free(repl_buf);
                        report_error(parser, name.line, name.column,
                                     MESSAGE_OUT_OF_MEMORY);
                    } else {
                        copy_value_string(parser, arguments[0], src_buf);
                        src_buf[src_len] = '\0';
                        copy_value_string(parser, arguments[1], target_buf);
                        target_buf[target_len] = '\0';
                        copy_value_string(parser, arguments[2], repl_buf);
                        repl_buf[repl_len] = '\0';

                        if (target_len == 0) {
                            free(target_buf);
                            free(repl_buf);
                            if (store_owned_string(parser, name, src_buf)) {
                                result = number_value(0.0);
                                result.kind = VALUE_STRING;
                                result.string_length = src_len;
                                result.owned_string = src_buf;
                            }
                        } else {
                            StringBuffer sb;
                            size_t cur = 0;
                            sb_init(&sb);
                            if (sb.failed) {
                                free(src_buf);
                                free(target_buf);
                                free(repl_buf);
                                report_error(parser, name.line, name.column,
                                             MESSAGE_OUT_OF_MEMORY_FOR_STRING);
                            } else {
                                while (cur < src_len) {
                                    if (cur + target_len <= src_len &&
                                        memcmp(src_buf + cur, target_buf, target_len) == 0) {
                                        if (repl_len > 0) {
                                            sb_append(&sb, repl_buf, repl_len);
                                        }
                                        cur += target_len;
                                    } else {
                                        sb_append(&sb, src_buf + cur, 1);
                                        cur++;
                                    }
                                }
                                free(src_buf);
                                free(target_buf);
                                free(repl_buf);
                                if (sb.failed) {
                                    free(sb.data);
                                    report_error(parser, name.line, name.column,
                                                 MESSAGE_OUT_OF_MEMORY_FOR_STRING);
                                } else {
                                    if (store_owned_string(parser, name, sb.data)) {
                                        result = number_value(0.0);
                                        result.kind = VALUE_STRING;
                                        result.string_length = sb.length;
                                        result.owned_string = sb.data;
                                    }
                                }
                            }
                        }
                    }
                }
            } else if (token_matches(parser, name, "શરૂઆત_સાથે") ||
                       token_matches(parser, name, "sharuat_sathe")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING ||
                           arguments[1].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_STRING_FOR_PREFIX_SUFFIX);
                } else {
                    size_t str_len = decoded_string_length(parser, arguments[0]);
                    size_t pre_len = decoded_string_length(parser, arguments[1]);
                    if (pre_len > str_len) {
                        result = number_value(0.0);
                    } else if (pre_len == 0) {
                        result = number_value(1.0);
                    } else {
                        char *str_buf = (char *)malloc(str_len + 1);
                        char *pre_buf = (char *)malloc(pre_len + 1);
                        if (str_buf == NULL || pre_buf == NULL) {
                            free(str_buf);
                            free(pre_buf);
                            report_error(parser, name.line, name.column,
                                         MESSAGE_OUT_OF_MEMORY);
                        } else {
                            copy_value_string(parser, arguments[0], str_buf);
                            copy_value_string(parser, arguments[1], pre_buf);
                            result = number_value(memcmp(str_buf, pre_buf, pre_len) == 0 ? 1.0 : 0.0);
                            free(str_buf);
                            free(pre_buf);
                        }
                    }
                }
            } else if (token_matches(parser, name, "અંત_સાથે") ||
                       token_matches(parser, name, "ant_sathe")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING ||
                           arguments[1].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_STRING_FOR_PREFIX_SUFFIX);
                } else {
                    size_t str_len = decoded_string_length(parser, arguments[0]);
                    size_t suf_len = decoded_string_length(parser, arguments[1]);
                    if (suf_len > str_len) {
                        result = number_value(0.0);
                    } else if (suf_len == 0) {
                        result = number_value(1.0);
                    } else {
                        char *str_buf = (char *)malloc(str_len + 1);
                        char *suf_buf = (char *)malloc(suf_len + 1);
                        if (str_buf == NULL || suf_buf == NULL) {
                            free(str_buf);
                            free(suf_buf);
                            report_error(parser, name.line, name.column,
                                         MESSAGE_OUT_OF_MEMORY);
                        } else {
                            copy_value_string(parser, arguments[0], str_buf);
                            copy_value_string(parser, arguments[1], suf_buf);
                            result = number_value(memcmp(str_buf + (str_len - suf_len), suf_buf, suf_len) == 0 ? 1.0 : 0.0);
                            free(str_buf);
                            free(suf_buf);
                        }
                    }
                }
            } else if (token_matches(parser, name, "સમાવે_છે") ||
                       token_matches(parser, name, "samave_chhe")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind == VALUE_DICT) {
                    if (arguments[1].kind != VALUE_STRING) {
                        result = number_value(0.0);
                    } else {
                        char *k = value_to_c_string(parser, arguments[1]);
                        int found = 0;
                        if (k != NULL) {
                            found = dict_get(arguments[0].dict, k, strlen(k)) != NULL;
                            free(k);
                        }
                        result = number_value(found ? 1.0 : 0.0);
                    }
                } else if (arguments[0].kind != VALUE_LIST) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_LIST_FOR_SAMAVE_CHHE);
                } else {
                    List *list = arguments[0].list;
                    size_t i;
                    int found = 0;
                    for (i = 0; i < list->count; i++) {
                        if (values_are_equal(parser, list->items[i], arguments[1])) {
                            found = 1;
                            break;
                        }
                    }
                    result = number_value(found ? 1.0 : 0.0);
                }
            } else if (token_matches(parser, name, "ગોળ") ||
                       token_matches(parser, name, "gol")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_NUMBER) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_NUMERIC_MATH_ARGUMENT);
                } else {
                    result = number_value(round(arguments[0].number));
                }
            } else if (token_matches(parser, name, "નીચે") ||
                       token_matches(parser, name, "niche")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_NUMBER) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_NUMERIC_MATH_ARGUMENT);
                } else {
                    result = number_value(floor(arguments[0].number));
                }
            } else if (token_matches(parser, name, "ઉપર") ||
                       token_matches(parser, name, "upar")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_NUMBER) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_NUMERIC_MATH_ARGUMENT);
                } else {
                    result = number_value(ceil(arguments[0].number));
                }
            } else if (token_matches(parser, name, "પુનરાવર્તન") ||
                       token_matches(parser, name, "punravartan")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_STRING_FOR_PUNRAVARTAN);
                } else if (arguments[1].kind != VALUE_NUMBER ||
                           arguments[1].number < 0.0 ||
                           arguments[1].number >= (double)(size_t)-1 ||
                           arguments[1].number != (double)(size_t)arguments[1].number) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_PUNRAVARTAN_INTEGER);
                } else {
                    size_t count = (size_t)arguments[1].number;
                    if (count == 0) {
                        char *empty_s = (char *)malloc(1);
                        if (empty_s == NULL) {
                            report_error(parser, name.line, name.column,
                                         MESSAGE_OUT_OF_MEMORY);
                        } else {
                            empty_s[0] = '\0';
                            if (store_owned_string(parser, name, empty_s)) {
                                result = number_value(0.0);
                                result.kind = VALUE_STRING;
                                result.string_length = 0;
                                result.owned_string = empty_s;
                            }
                        }
                    } else {
                        size_t str_len = decoded_string_length(parser, arguments[0]);
                        if (str_len > 0 && count > (size_t)-1 / str_len) {
                            report_error(parser, name.line, name.column,
                                         MESSAGE_OUT_OF_MEMORY);
                        } else {
                            size_t total_len = str_len * count;
                            char *temp = (char *)malloc(str_len + 1);
                            char *buffer = (char *)malloc(total_len + 1);
                            if (temp == NULL || buffer == NULL) {
                                free(temp);
                                free(buffer);
                                report_error(parser, name.line, name.column,
                                             MESSAGE_OUT_OF_MEMORY);
                            } else {
                                size_t i;
                                copy_value_string(parser, arguments[0], temp);
                                temp[str_len] = '\0';
                                for (i = 0; i < count; i++) {
                                    memcpy(buffer + i * str_len, temp, str_len);
                                }
                                buffer[total_len] = '\0';
                                free(temp);
                                if (store_owned_string(parser, name, buffer)) {
                                    result = number_value(0.0);
                                    result.kind = VALUE_STRING;
                                    result.string_length = total_len;
                                    result.owned_string = buffer;
                                }
                            }
                        }
                    }
                }
            } else if (token_matches(parser, name, "ટુકડો") ||
                       token_matches(parser, name, "tukdo")) {
                if (argument_count != 2 && argument_count != 3) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_LIST) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_LIST_FOR_TUKDO);
                } else if (arguments[1].kind != VALUE_NUMBER ||
                           arguments[1].number < 0.0 ||
                           arguments[1].number >= (double)(size_t)-1 ||
                           arguments[1].number != (double)(size_t)arguments[1].number ||
                           (argument_count == 3 &&
                            (arguments[2].kind != VALUE_NUMBER ||
                             arguments[2].number < 0.0 ||
                             arguments[2].number >= (double)(size_t)-1 ||
                             arguments[2].number != (double)(size_t)arguments[2].number))) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_TUKDO_INTEGER);
                } else {
                    List *new_list = create_list(parser, name);
                    if (new_list != NULL) {
                        size_t total_items = arguments[0].list->count;
                        size_t start_idx = (size_t)arguments[1].number;
                        int ok = 1;
                        if (start_idx < total_items) {
                            size_t end_idx;
                            size_t i;
                            if (argument_count == 2) {
                                end_idx = total_items;
                            } else {
                                size_t req_len = (size_t)arguments[2].number;
                                end_idx = (start_idx + req_len > total_items) ?
                                          total_items : start_idx + req_len;
                            }
                            for (i = start_idx; i < end_idx; i++) {
                                if (!append_list_item(parser, new_list,
                                                     arguments[0].list->items[i],
                                                     name)) {
                                    ok = 0;
                                    break;
                                }
                            }
                        }
                        if (ok) {
                            result = number_value(0.0);
                            result.kind = VALUE_LIST;
                            result.list = new_list;
                        }
                    }
                }
            } else if (token_matches(parser, name, "સ્થાન") ||
                       token_matches(parser, name, "sthan")) {
                if (argument_count != 2 && argument_count != 3) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_LIST) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_LIST_FOR_STHAN);
                } else if (argument_count == 3 &&
                           (arguments[2].kind != VALUE_NUMBER ||
                            arguments[2].number < 0.0 ||
                            arguments[2].number >= (double)(size_t)-1 ||
                            arguments[2].number != (double)(size_t)arguments[2].number)) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_STHAN_INTEGER);
                } else {
                    List *list = arguments[0].list;
                    size_t start = 0;
                    size_t i;
                    double index = -1.0;
                    if (argument_count == 3) {
                        start = (size_t)arguments[2].number;
                    }
                    for (i = start; i < list->count; i++) {
                        if (values_are_equal(parser, list->items[i], arguments[1])) {
                            index = (double)i;
                            break;
                        }
                    }
                    result = number_value(index);
                }
            } else if (token_matches(parser, name, "મૂકો") ||
                       token_matches(parser, name, "muko")) {
                if (argument_count != 3) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_LIST) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_LIST_FOR_MUKO);
                } else if (arguments[1].kind != VALUE_NUMBER ||
                           arguments[1].number < 0.0 ||
                           arguments[1].number >= (double)(size_t)-1 ||
                           arguments[1].number != (double)(size_t)arguments[1].number) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_MUKO_INTEGER);
                } else if ((size_t)arguments[1].number > arguments[0].list->count) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_MUKO_INDEX_OUT_OF_RANGE);
                } else {
                    if (insert_list_item(parser, arguments[0].list,
                                         (size_t)arguments[1].number,
                                         arguments[2], name)) {
                        result = arguments[0];
                    }
                }
            } else if (token_matches(parser, name, "ડાબે_ભરો") ||
                       token_matches(parser, name, "dabe_bharo") ||
                       token_matches(parser, name, "જમણે_ભરો") ||
                       token_matches(parser, name, "jamne_bharo")) {
                int is_left = (token_matches(parser, name, "ડાબે_ભરો") ||
                               token_matches(parser, name, "dabe_bharo"));
                if (argument_count != 2 && argument_count != 3) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_STRING_FOR_PADDING);
                } else if (arguments[1].kind != VALUE_NUMBER ||
                           arguments[1].number < 0.0 ||
                           arguments[1].number >= (double)(size_t)-1 ||
                           arguments[1].number != (double)(size_t)arguments[1].number) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_PADDING_WIDTH_INTEGER);
                } else if (argument_count == 3 && arguments[2].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_EXPECTED_PAD_STRING);
                } else {
                    Value *opt_pad = (argument_count == 3) ? &arguments[2] : NULL;
                    result = pad_string_value(parser, name, arguments[0],
                                              arguments[1], opt_pad, is_left);
                }
            } else if (token_matches(parser, name, "જેસન_વાંચો") || token_matches(parser, name, "json_vancho")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_JSON_STRING);
                } else {
                    char *json_text = value_to_c_string(parser, arguments[0]);
                    if (json_text) {
                        const char *p = json_text;
                        int err = 0;
                        Value v = parse_json_value(parser, name, &p, &err);
                        skip_json_whitespace(&p);
                        if (err || *p != '\0') {
                            report_error(parser, name.line, name.column, MESSAGE_INVALID_JSON);
                        } else {
                            result = v;
                        }
                        free(json_text);
                    }
                }
            } else if (token_matches(parser, name, "જેસન_લખો") || token_matches(parser, name, "json_lakho")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    StringBuffer sb;
                    sb_init(&sb);
                    List *ancestors[256];
                    json_format_value(parser, arguments[0], &sb, ancestors, 0);
                    if (!sb.failed && sb.data) {
                        result = make_owned_string_value(parser, name, sb.data, sb.length);
                    }
                }
            } else if (token_matches(parser, name, "દલીલો") || token_matches(parser, name, "daleelo") ||
                       token_matches(parser, name, "દલીલ_યાદી") || token_matches(parser, name, "arg_yadi")) {
                if (argument_count != 0) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    List *list = create_list(parser, name);
                    for (int i = 0; i < g_script_argc; i++) {
                        char *arg_copy = copy_string(g_script_argv[i]);
                        if (arg_copy) {
                            Value item = make_owned_string_value(parser, name, arg_copy, strlen(arg_copy));
                            append_list_item(parser, list, item, name);
                        }
                    }
                    result.kind = VALUE_LIST;
                    result.list = list;
                }
            } else if (token_matches(parser, name, "દ્વિ_સંખ્યા") || token_matches(parser, name, "dvi_sankhya")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_NUMBER) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_RADIX_INTEGER);
                } else {
                    char *bin_str = int_to_bin_string((long long)arguments[0].number);
                    if (bin_str) {
                        result = make_owned_string_value(parser, name, bin_str, strlen(bin_str));
                    }
                }
            } else if (token_matches(parser, name, "દ્વિ_થી_સંખ્યા") || token_matches(parser, name, "dvi_thi_sankhya")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_RADIX_STRING);
                } else {
                    char *str = value_to_c_string(parser, arguments[0]);
                    if (str) {
                        long long val = (long long)strtoull(str, NULL, 2);
                        result = number_value((double)val);
                        free(str);
                    }
                }
            } else if (token_matches(parser, name, "હેક્સ_લખાણ") || token_matches(parser, name, "hex_lakhan")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_NUMBER) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_RADIX_INTEGER);
                } else {
                    char *hex_str = int_to_hex_string((long long)arguments[0].number);
                    if (hex_str) {
                        result = make_owned_string_value(parser, name, hex_str, strlen(hex_str));
                    }
                }
            } else if (token_matches(parser, name, "હેક્સ_થી_સંખ્યા") || token_matches(parser, name, "hex_thi_sankhya")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_RADIX_STRING);
                } else {
                    char *str = value_to_c_string(parser, arguments[0]);
                    if (str) {
                        long long val = (long long)strtoull(str, NULL, 16);
                        result = number_value((double)val);
                        free(str);
                    }
                }
            } else if (token_matches(parser, name, "ફોલ્ડર_છે") || token_matches(parser, name, "folder_chhe")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_STRING_FOR_FILE_PATH);
                } else {
                    char *path = value_to_c_string(parser, arguments[0]);
                    if (path) {
                        result = number_value(platform_folder_exists(path) ? 1.0 : 0.0);
                        free(path);
                    }
                }
            } else if (token_matches(parser, name, "ફોલ્ડર_બનાવો") || token_matches(parser, name, "folder_banao")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_STRING_FOR_FILE_PATH);
                } else {
                    char *path = value_to_c_string(parser, arguments[0]);
                    if (path) {
                        result = number_value(platform_folder_create(path) ? 1.0 : 0.0);
                        free(path);
                    }
                }
            } else if (token_matches(parser, name, "ફોલ્ડર_સૂચિ") || token_matches(parser, name, "folder_suchi")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_STRING_FOR_FILE_PATH);
                } else {
                    char *path = value_to_c_string(parser, arguments[0]);
                    if (path) {
                        List *list = platform_folder_list(parser, name, path);
                        if (list) {
                            result.kind = VALUE_LIST;
                            result.list = list;
                        }
                        free(path);
                    }
                }
            } else if (token_matches(parser, name, "કમાન્ડ_ચલાવો") || token_matches(parser, name, "command_chalao") ||
                       token_matches(parser, name, "સિસ્ટમ") || token_matches(parser, name, "system_kary")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_LENGTH_STRING);
                } else {
                    char *cmd = value_to_c_string(parser, arguments[0]);
                    if (cmd) {
                        int code = system(cmd);
                        result = number_value((double)code);
                        free(cmd);
                    }
                }
            } else if (token_matches(parser, name, "નકશો_યાદી") || token_matches(parser, name, "naksho_yadi")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_LIST) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_LIST_FOR_LOOP);
                } else {
                    Function *fn = resolve_callee_function(parser, arguments[1]);
                    if (!fn) {
                        report_error(parser, name.line, name.column, MESSAGE_EXPECTED_FUNCTION_FOR_MAP);
                    } else {
                        List *new_list = create_list(parser, name);
                        for (size_t i = 0; i < arguments[0].list->count; i++) {
                            Value arg = arguments[0].list->items[i];
                            Value mapped = call_function(parser, *fn, &arg);
                            append_list_item(parser, new_list, mapped, name);
                        }
                        result.kind = VALUE_LIST;
                        result.list = new_list;
                    }
                }
            } else if (token_matches(parser, name, "ગાળો_યાદી") || token_matches(parser, name, "gaalo_yadi")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_LIST) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_LIST_FOR_LOOP);
                } else {
                    Function *fn = resolve_callee_function(parser, arguments[1]);
                    if (!fn) {
                        report_error(parser, name.line, name.column, MESSAGE_EXPECTED_FUNCTION_FOR_FILTER);
                    } else {
                        List *new_list = create_list(parser, name);
                        for (size_t i = 0; i < arguments[0].list->count; i++) {
                            Value arg = arguments[0].list->items[i];
                            Value cond = call_function(parser, *fn, &arg);
                            if (value_is_truthy(cond)) {
                                append_list_item(parser, new_list, arg, name);
                            }
                        }
                        result.kind = VALUE_LIST;
                        result.list = new_list;
                    }
                }
            } else if (token_matches(parser, name, "સમેટો_યાદી") || token_matches(parser, name, "sameto_yadi")) {
                if (argument_count != 3) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_LIST) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_LIST_FOR_LOOP);
                } else {
                    Function *fn = resolve_callee_function(parser, arguments[1]);
                    if (!fn) {
                        report_error(parser, name.line, name.column, MESSAGE_EXPECTED_FUNCTION_FOR_REDUCE);
                    } else {
                        Value acc = arguments[2];
                        for (size_t i = 0; i < arguments[0].list->count; i++) {
                            Value args[2];
                            args[0] = acc;
                            args[1] = arguments[0].list->items[i];
                            acc = call_function(parser, *fn, args);
                        }
                        result = acc;
                    }
                }
            } else if (token_matches(parser, name, "શોધો_યાદી") || token_matches(parser, name, "shodho_yadi")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_LIST) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_LIST_FOR_LOOP);
                } else {
                    Function *fn = resolve_callee_function(parser, arguments[1]);
                    if (!fn) {
                        report_error(parser, name.line, name.column, MESSAGE_EXPECTED_FUNCTION_FOR_FIND);
                    } else {
                        result = null_value();
                        for (size_t i = 0; i < arguments[0].list->count; i++) {
                            Value arg = arguments[0].list->items[i];
                            Value cond = call_function(parser, *fn, &arg);
                            if (value_is_truthy(cond)) {
                                result = arg;
                                break;
                            }
                        }
                    }
                }
            } else if (token_matches(parser, name, "શોધો_સૂચક_યાદી") || token_matches(parser, name, "shodho_suchak_yadi")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_LIST) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_LIST_FOR_LOOP);
                } else {
                    Function *fn = resolve_callee_function(parser, arguments[1]);
                    if (!fn) {
                        report_error(parser, name.line, name.column, MESSAGE_EXPECTED_FUNCTION_FOR_FIND);
                    } else {
                        result = number_value(-1.0);
                        for (size_t i = 0; i < arguments[0].list->count; i++) {
                            Value arg = arguments[0].list->items[i];
                            Value cond = call_function(parser, *fn, &arg);
                            if (value_is_truthy(cond)) {
                                result = number_value((double)i);
                                break;
                            }
                        }
                    }
                }
            } else if (token_matches(parser, name, "ચપટી_યાદી") || token_matches(parser, name, "chapti_yadi")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_LIST) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_LIST_FOR_FLATTEN);
                } else {
                    List *flat = create_list(parser, name);
                    for (size_t i = 0; i < arguments[0].list->count; i++) {
                        Value item = arguments[0].list->items[i];
                        if (item.kind == VALUE_LIST) {
                            for (size_t j = 0; j < item.list->count; j++) {
                                append_list_item(parser, flat, item.list->items[j], name);
                            }
                        } else {
                            append_list_item(parser, flat, item, name);
                        }
                    }
                    result.kind = VALUE_LIST;
                    result.list = flat;
                }
            } else if (token_matches(parser, name, "ઝીપ_યાદી") || token_matches(parser, name, "zip_yadi")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_LIST || arguments[1].kind != VALUE_LIST) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_LISTS_FOR_ZIP);
                } else {
                    size_t len1 = arguments[0].list->count;
                    size_t len2 = arguments[1].list->count;
                    size_t min_len = len1 < len2 ? len1 : len2;
                    List *zipped = create_list(parser, name);
                    for (size_t i = 0; i < min_len; i++) {
                        List *pair = create_list(parser, name);
                        append_list_item(parser, pair, arguments[0].list->items[i], name);
                        append_list_item(parser, pair, arguments[1].list->items[i], name);
                        Value pair_val = number_value(0.0);
                        pair_val.kind = VALUE_LIST;
                        pair_val.list = pair;
                        append_list_item(parser, zipped, pair_val, name);
                    }
                    result.kind = VALUE_LIST;
                    result.list = zipped;
                }
            } else if (token_matches(parser, name, "પેટર્ન_શોધો") || token_matches(parser, name, "pattern_shodho")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING || arguments[1].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_STRING_FOR_PATTERN);
                } else {
                    char *str = value_to_c_string(parser, arguments[0]);
                    char *pat = value_to_c_string(parser, arguments[1]);
                    if (str && pat) {
                        result = number_value(wildcard_match(pat, str) ? 1.0 : 0.0);
                    }
                    free(str);
                    free(pat);
                }
            } else if (token_matches(parser, name, "લખાણ_બદલો_દરેક") || token_matches(parser, name, "lakhan_badlo_darek")) {
                if (argument_count != 3) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING || arguments[1].kind != VALUE_STRING || arguments[2].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_STRING_FOR_BADLO);
                } else {
                    char *src = value_to_c_string(parser, arguments[0]);
                    char *tgt = value_to_c_string(parser, arguments[1]);
                    char *rep = value_to_c_string(parser, arguments[2]);
                    if (src && tgt && rep) {
                        char *replaced = string_replace_all(src, tgt, rep);
                        if (replaced) {
                            result = make_owned_string_value(parser, name, replaced, strlen(replaced));
                        }
                    }
                    free(src);
                    free(tgt);
                    free(rep);
                }
            } else if (token_matches(parser, name, "બેઝ૬૪_કોડ") || token_matches(parser, name, "base64_kod")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_BASE64_STRING);
                } else {
                    char *str = value_to_c_string(parser, arguments[0]);
                    if (str) {
                        size_t out_len = 0;
                        char *encoded = base64_encode_str((const unsigned char *)str, strlen(str), &out_len);
                        if (encoded) {
                            result = make_owned_string_value(parser, name, encoded, out_len);
                        }
                        free(str);
                    }
                }
            } else if (token_matches(parser, name, "બેઝ૬૪_ડીકોડ") || token_matches(parser, name, "base64_decode")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_BASE64_STRING);
                } else {
                    char *str = value_to_c_string(parser, arguments[0]);
                    if (str) {
                        size_t out_len = 0;
                        char *decoded = base64_decode_str(str, strlen(str), &out_len);
                        if (decoded) {
                            result = make_owned_string_value(parser, name, decoded, out_len);
                        } else {
                            report_error(parser, name.line, name.column, MESSAGE_INVALID_BASE64);
                        }
                        free(str);
                    }
                }
            } else if (token_matches(parser, name, "શીર્ષક_લખાણ") || token_matches(parser, name, "shirshak_lakhan")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_STRING_FOR_CASE);
                } else {
                    char *str = value_to_c_string(parser, arguments[0]);
                    if (str) {
                        char *tc = string_to_title_case(str, strlen(str));
                        if (tc) {
                            result = make_owned_string_value(parser, name, tc, strlen(tc));
                        }
                        free(str);
                    }
                }
            } else if (token_matches(parser, name, "પ્રથમ_મોટી") || token_matches(parser, name, "pratham_moti")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_STRING_FOR_CASE);
                } else {
                    char *str = value_to_c_string(parser, arguments[0]);
                    if (str) {
                        char *cf = string_capitalize_first(str, strlen(str));
                        if (cf) {
                            result = make_owned_string_value(parser, name, cf, strlen(cf));
                        }
                        free(str);
                    }
                }
            } else if (token_matches(parser, name, "સ્વરૂપ") || token_matches(parser, name, "swaroop")) {
                if (argument_count < 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_STRING_FOR_CASE);
                } else {
                    char *fmt = value_to_c_string(parser, arguments[0]);
                    if (fmt) {
                        size_t out_len = 0;
                        char *formatted = format_template(parser, fmt, strlen(fmt), arguments, argument_count, &out_len);
                        if (formatted) {
                            result = make_owned_string_value(parser, name, formatted, out_len);
                        }
                        free(fmt);
                    }
                }
            } else if (token_matches(parser, name, "લખાણ_અંતર") || token_matches(parser, name, "lakhan_antar")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING || arguments[1].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_STRING_FOR_DISTANCE);
                } else {
                    char *s1 = value_to_c_string(parser, arguments[0]);
                    char *s2 = value_to_c_string(parser, arguments[1]);
                    if (s1 && s2) {
                        size_t dist = calc_levenshtein(s1, strlen(s1), s2, strlen(s2));
                        result = number_value((double)dist);
                    }
                    free(s1);
                    free(s2);
                }
            } else if (token_matches(parser, name, "શા૨૫૬_હેશ") || token_matches(parser, name, "sha256_hash")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_STRING) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_LENGTH_STRING);
                } else {
                    char *str = value_to_c_string(parser, arguments[0]);
                    if (str) {
                        char *hex = sha256_hash_string(str, strlen(str));
                        if (hex) {
                            result = make_owned_string_value(parser, name, hex, 64);
                        }
                        free(str);
                    }
                }
            } else if (token_matches(parser, name, "સાઇન") || token_matches(parser, name, "sine")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_NUMBER) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_NUMERIC_MATH_ARGUMENT);
                } else {
                    result = number_value(sin(arguments[0].number));
                }
            } else if (token_matches(parser, name, "કોસાઇન") || token_matches(parser, name, "cosine")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_NUMBER) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_NUMERIC_MATH_ARGUMENT);
                } else {
                    result = number_value(cos(arguments[0].number));
                }
            } else if (token_matches(parser, name, "ટેન્જન્ટ") || token_matches(parser, name, "tangent")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_NUMBER) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_NUMERIC_MATH_ARGUMENT);
                } else {
                    result = number_value(tan(arguments[0].number));
                }
            } else if (token_matches(parser, name, "આર્કસાઇન") || token_matches(parser, name, "arcsin")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_NUMBER) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_NUMERIC_MATH_ARGUMENT);
                } else {
                    result = number_value(asin(arguments[0].number));
                }
            } else if (token_matches(parser, name, "આર્કકોસ") || token_matches(parser, name, "arccos")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_NUMBER) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_NUMERIC_MATH_ARGUMENT);
                } else {
                    result = number_value(acos(arguments[0].number));
                }
            } else if (token_matches(parser, name, "આર્કટેન") || token_matches(parser, name, "arctan")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_NUMBER) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_NUMERIC_MATH_ARGUMENT);
                } else {
                    result = number_value(atan(arguments[0].number));
                }
            } else if (token_matches(parser, name, "ગુરુ_તમ") || token_matches(parser, name, "guru_tam")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_NUMBER || arguments[1].kind != VALUE_NUMBER) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_NUMERIC_MATH_ARGUMENT);
                } else {
                    long long x = llabs((long long)arguments[0].number);
                    long long y = llabs((long long)arguments[1].number);
                    while (y != 0) {
                        long long t = y;
                        y = x % y;
                        x = t;
                    }
                    result = number_value((double)x);
                }
            } else if (token_matches(parser, name, "લઘુ_તમ") || token_matches(parser, name, "laghu_tam")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_NUMBER || arguments[1].kind != VALUE_NUMBER) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_NUMERIC_MATH_ARGUMENT);
                } else {
                    long long x = llabs((long long)arguments[0].number);
                    long long y = llabs((long long)arguments[1].number);
                    if (x == 0 || y == 0) {
                        result = number_value(0.0);
                    } else {
                        long long a = x, b = y;
                        while (b != 0) {
                            long long t = b;
                            b = a % b;
                            a = t;
                        }
                        result = number_value((double)((x / a) * y));
                    }
                }
            } else if (token_matches(parser, name, "અંશ_થી_રેડિયન") || token_matches(parser, name, "ansha_thi_radian")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_NUMBER) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_NUMERIC_MATH_ARGUMENT);
                } else {
                    result = number_value(arguments[0].number * (GUJARATI_PI / 180.0));
                }
            } else if (token_matches(parser, name, "રેડિયન_થી_અંશ") || token_matches(parser, name, "radian_thi_ansha")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_NUMBER) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_NUMERIC_MATH_ARGUMENT);
                } else {
                    result = number_value(arguments[0].number * (180.0 / GUJARATI_PI));
                }
            } else if (token_matches(parser, name, "મેટ્રિક્સ_સરવાળો") || token_matches(parser, name, "matrix_sarvalo")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    result = matrix_add(parser, name, arguments[0], arguments[1]);
                }
            } else if (token_matches(parser, name, "મેટ્રિક્સ_ગુણાકાર") || token_matches(parser, name, "matrix_gunakar")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    result = matrix_multiply(parser, name, arguments[0], arguments[1]);
                }
            } else if (token_matches(parser, name, "ભાષા_આવૃત્તિ") || token_matches(parser, name, "bhasha_avrutti")) {
                if (argument_count != 0) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    char *ver = copy_string("1.0.0");
                    if (ver) {
                        result = make_owned_string_value(parser, name, ver, strlen(ver));
                    }
                }
            } else if (token_matches(parser, name, "પ્લેટફોર્મ_નામ") || token_matches(parser, name, "platform_nam")) {
                if (argument_count != 0) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
#if defined(_WIN32)
                    char *pname = copy_string("windows");
#elif defined(__APPLE__)
                    char *pname = copy_string("macos");
#else
                    char *pname = copy_string("linux");
#endif
                    if (pname) {
                        result = make_owned_string_value(parser, name, pname, strlen(pname));
                    }
                }
            } else if (token_matches(parser, name, "પર્યાવરણ") || token_matches(parser, name, "paryavaran")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    char *ename = value_to_c_string(parser, arguments[0]);
                    if (ename) {
                        char *eval = getenv(ename);
                        free(ename);
                        if (eval) {
                            char *copy = copy_string(eval);
                            if (copy) result = make_owned_string_value(parser, name, copy, strlen(copy));
                        } else {
                            result = null_value();
                        }
                    }
                }
            } else if (token_matches(parser, name, "પર્યાવરણ_લખો") || token_matches(parser, name, "paryavaran_lakho")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    char *ename = value_to_c_string(parser, arguments[0]);
                    char *eval = value_to_c_string(parser, arguments[1]);
                    if (ename && eval) {
#if defined(_WIN32)
                        _putenv_s(ename, eval);
#else
                        setenv(ename, eval, 1);
#endif
                        result = number_value(1.0);
                    }
                    if (ename) free(ename);
                    if (eval) free(eval);
                }
            } else if (token_matches(parser, name, "પાથ_જોડો") || token_matches(parser, name, "path_jodo")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    char *a = value_to_c_string(parser, arguments[0]);
                    char *b = value_to_c_string(parser, arguments[1]);
                    if (a && b) {
                        char *res = path_join(a, strlen(a), b, strlen(b));
                        if (res) result = make_owned_string_value(parser, name, res, strlen(res));
                    }
                    if (a) free(a);
                    if (b) free(b);
                }
            } else if (token_matches(parser, name, "પાથ_વિસ્તરણ") || token_matches(parser, name, "path_vistaran")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    char *p = value_to_c_string(parser, arguments[0]);
                    if (p) {
                        const char *ext = path_extension(p, strlen(p));
                        char *copy = copy_string(ext);
                        free(p);
                        if (copy) result = make_owned_string_value(parser, name, copy, strlen(copy));
                    }
                }
            } else if (token_matches(parser, name, "પાથ_મુખ્ય") || token_matches(parser, name, "path_mukhya")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    char *p = value_to_c_string(parser, arguments[0]);
                    if (p) {
                        const char *base = path_basename(p, strlen(p));
                        char *copy = copy_string(base);
                        free(p);
                        if (copy) result = make_owned_string_value(parser, name, copy, strlen(copy));
                    }
                }
            } else if (token_matches(parser, name, "પાથ_ફોલ્ડર") || token_matches(parser, name, "path_folder")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    char *p = value_to_c_string(parser, arguments[0]);
                    if (p) {
                        char *dir = path_dirname(p, strlen(p));
                        free(p);
                        if (dir) result = make_owned_string_value(parser, name, dir, strlen(dir));
                    }
                }
            } else if (token_matches(parser, name, "યુયુઆઈડી_બનાવો") || token_matches(parser, name, "uuid_banao")) {
                if (argument_count != 0) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    char *u = generate_uuid_v4();
                    if (u) result = make_owned_string_value(parser, name, u, strlen(u));
                }
            } else if (token_matches(parser, name, "યુઆરએલ_કોડ") || token_matches(parser, name, "url_kod")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    char *s = value_to_c_string(parser, arguments[0]);
                    if (s) {
                        char *enc = url_encode(s, strlen(s));
                        free(s);
                        if (enc) result = make_owned_string_value(parser, name, enc, strlen(enc));
                    }
                }
            } else if (token_matches(parser, name, "યુઆરએલ_ડીકોડ") || token_matches(parser, name, "url_decode")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    char *s = value_to_c_string(parser, arguments[0]);
                    if (s) {
                        char *dec = url_decode(s, strlen(s));
                        free(s);
                        if (dec) result = make_owned_string_value(parser, name, dec, strlen(dec));
                    }
                }
            } else if (token_matches(parser, name, "યાદી_સરવાળો") || token_matches(parser, name, "yadi_sarvalo")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_LIST) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_LIST_FOR_LOOP);
                } else {
                    List *l = arguments[0].list;
                    double sum = 0.0;
                    if (l) {
                        for (size_t i = 0; i < l->count; i++) {
                            if (l->items[i].kind == VALUE_NUMBER) sum += l->items[i].number;
                        }
                    }
                    result = number_value(sum);
                }
            } else if (token_matches(parser, name, "યાદી_સરેરાશ") || token_matches(parser, name, "yadi_sareras")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_LIST) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_LIST_FOR_LOOP);
                } else {
                    List *l = arguments[0].list;
                    double sum = 0.0;
                    size_t cnt = 0;
                    if (l) {
                        for (size_t i = 0; i < l->count; i++) {
                            if (l->items[i].kind == VALUE_NUMBER) {
                                sum += l->items[i].number;
                                cnt++;
                            }
                        }
                    }
                    result = number_value(cnt > 0 ? (sum / (double)cnt) : 0.0);
                }
            } else if (token_matches(parser, name, "યાદી_મધ્યસ્થ") || token_matches(parser, name, "yadi_madhyastha")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_LIST) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_LIST_FOR_LOOP);
                } else {
                    List *l = arguments[0].list;
                    if (!l || l->count == 0) {
                        result = number_value(0.0);
                    } else {
                        double *arr = (double *)malloc(l->count * sizeof(double));
                        if (arr) {
                            size_t cnt = 0;
                            for (size_t i = 0; i < l->count; i++) {
                                if (l->items[i].kind == VALUE_NUMBER) arr[cnt++] = l->items[i].number;
                            }
                            if (cnt == 0) {
                                result = number_value(0.0);
                            } else {
                                qsort(arr, cnt, sizeof(double), compare_doubles_asc);
                                if (cnt % 2 == 1) {
                                    result = number_value(arr[cnt / 2]);
                                } else {
                                    result = number_value((arr[cnt / 2 - 1] + arr[cnt / 2]) / 2.0);
                                }
                            }
                            free(arr);
                        }
                    }
                }
            } else if (token_matches(parser, name, "લેખન_પૂર્ણ_ડાબી") || token_matches(parser, name, "lakhan_purn_dabi")) {
                if (argument_count != 3) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    char *s = value_to_c_string(parser, arguments[0]);
                    char *p = value_to_c_string(parser, arguments[2]);
                    char pch = (p && p[0] != '\0') ? p[0] : ' ';
                    size_t out_len = 0;
                    if (s) {
                        char *res = pad_string(s, strlen(s), (size_t)arguments[1].number, pch, 1, &out_len);
                        if (res) result = make_owned_string_value(parser, name, res, out_len);
                        free(s);
                    }
                    if (p) free(p);
                }
            } else if (token_matches(parser, name, "લેખન_પૂર્ણ_જમણી") || token_matches(parser, name, "lakhan_purn_jamni")) {
                if (argument_count != 3) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    char *s = value_to_c_string(parser, arguments[0]);
                    char *p = value_to_c_string(parser, arguments[2]);
                    char pch = (p && p[0] != '\0') ? p[0] : ' ';
                    size_t out_len = 0;
                    if (s) {
                        char *res = pad_string(s, strlen(s), (size_t)arguments[1].number, pch, 0, &out_len);
                        if (res) result = make_owned_string_value(parser, name, res, out_len);
                        free(s);
                    }
                    if (p) free(p);
                }
            } else if (token_matches(parser, name, "બીટ_અને") || token_matches(parser, name, "bit_ane")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    int64_t a = (int64_t)arguments[0].number;
                    int64_t b = (int64_t)arguments[1].number;
                    result = number_value((double)(a & b));
                }
            } else if (token_matches(parser, name, "બીટ_અથવા") || token_matches(parser, name, "bit_athva")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    int64_t a = (int64_t)arguments[0].number;
                    int64_t b = (int64_t)arguments[1].number;
                    result = number_value((double)(a | b));
                }
            } else if (token_matches(parser, name, "બીટ_એક્સઓર") || token_matches(parser, name, "bit_xor")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    int64_t a = (int64_t)arguments[0].number;
                    int64_t b = (int64_t)arguments[1].number;
                    result = number_value((double)(a ^ b));
                }
            } else if (token_matches(parser, name, "બીટ_નહિ") || token_matches(parser, name, "bit_nahi")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    int64_t a = (int64_t)arguments[0].number;
                    result = number_value((double)(~a));
                }
            } else if (token_matches(parser, name, "બીટ_શિફ્ટ_ડાબી") || token_matches(parser, name, "bit_shifte_dabi")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    int64_t a = (int64_t)arguments[0].number;
                    int64_t b = (int64_t)arguments[1].number;
                    result = number_value((double)(a << b));
                }
            } else if (token_matches(parser, name, "બીટ_શિફ્ટ_જમણી") || token_matches(parser, name, "bit_shifte_jamni")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    int64_t a = (int64_t)arguments[0].number;
                    int64_t b = (int64_t)arguments[1].number;
                    result = number_value((double)(a >> b));
                }
            } else if (token_matches(parser, name, "યાદી_અનન્ય") || token_matches(parser, name, "yadi_ananya")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_LIST) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_LIST_FOR_LOOP);
                } else {
                    List *src_list = arguments[0].list;
                    List *dst_list = create_list(parser, name);
                    if (src_list && dst_list) {
                        for (size_t i = 0; i < src_list->count; i++) {
                            int exists = 0;
                            for (size_t j = 0; j < dst_list->count; j++) {
                                if (values_are_equal(parser, src_list->items[i], dst_list->items[j])) {
                                    exists = 1;
                                    break;
                                }
                            }
                            if (!exists) append_list_item(parser, dst_list, src_list->items[i], name);
                        }
                    }
                    result = number_value(0.0);
                    result.kind = VALUE_LIST;
                    result.list = dst_list;
                }
            } else if (token_matches(parser, name, "યાદી_મેળ") || token_matches(parser, name, "yadi_mel")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_LIST || arguments[1].kind != VALUE_LIST) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_LIST_FOR_LOOP);
                } else {
                    List *l1 = arguments[0].list;
                    List *l2 = arguments[1].list;
                    List *dst = create_list(parser, name);
                    if (l1 && dst) {
                        for (size_t i = 0; i < l1->count; i++) {
                            int exists = 0;
                            for (size_t j = 0; j < dst->count; j++) {
                                if (values_are_equal(parser, l1->items[i], dst->items[j])) { exists = 1; break; }
                            }
                            if (!exists) append_list_item(parser, dst, l1->items[i], name);
                        }
                    }
                    if (l2 && dst) {
                        for (size_t i = 0; i < l2->count; i++) {
                            int exists = 0;
                            for (size_t j = 0; j < dst->count; j++) {
                                if (values_are_equal(parser, l2->items[i], dst->items[j])) { exists = 1; break; }
                            }
                            if (!exists) append_list_item(parser, dst, l2->items[i], name);
                        }
                    }
                    result = number_value(0.0);
                    result.kind = VALUE_LIST;
                    result.list = dst;
                }
            } else if (token_matches(parser, name, "યાદી_છેદ") || token_matches(parser, name, "yadi_chhed")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_LIST || arguments[1].kind != VALUE_LIST) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_LIST_FOR_LOOP);
                } else {
                    List *l1 = arguments[0].list;
                    List *l2 = arguments[1].list;
                    List *dst = create_list(parser, name);
                    if (l1 && l2 && dst) {
                        for (size_t i = 0; i < l1->count; i++) {
                            int in_l2 = 0;
                            for (size_t j = 0; j < l2->count; j++) {
                                if (values_are_equal(parser, l1->items[i], l2->items[j])) { in_l2 = 1; break; }
                            }
                            if (in_l2) {
                                int in_dst = 0;
                                for (size_t k = 0; k < dst->count; k++) {
                                    if (values_are_equal(parser, l1->items[i], dst->items[k])) { in_dst = 1; break; }
                                }
                                if (!in_dst) append_list_item(parser, dst, l1->items[i], name);
                            }
                        }
                    }
                    result = number_value(0.0);
                    result.kind = VALUE_LIST;
                    result.list = dst;
                }
            } else if (token_matches(parser, name, "યાદી_તફાવત") || token_matches(parser, name, "yadi_tavat")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_LIST || arguments[1].kind != VALUE_LIST) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_LIST_FOR_LOOP);
                } else {
                    List *l1 = arguments[0].list;
                    List *l2 = arguments[1].list;
                    List *dst = create_list(parser, name);
                    if (l1 && dst) {
                        for (size_t i = 0; i < l1->count; i++) {
                            int in_l2 = 0;
                            if (l2) {
                                for (size_t j = 0; j < l2->count; j++) {
                                    if (values_are_equal(parser, l1->items[i], l2->items[j])) { in_l2 = 1; break; }
                                }
                            }
                            if (!in_l2) {
                                int in_dst = 0;
                                for (size_t k = 0; k < dst->count; k++) {
                                    if (values_are_equal(parser, l1->items[i], dst->items[k])) { in_dst = 1; break; }
                                }
                                if (!in_dst) append_list_item(parser, dst, l1->items[i], name);
                            }
                        }
                    }
                    result = number_value(0.0);
                    result.kind = VALUE_LIST;
                    result.list = dst;
                }
            } else if (token_matches(parser, name, "અક્ષર_કોડ") || token_matches(parser, name, "akshar_kod")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    char *s = value_to_c_string(parser, arguments[0]);
                    if (s) {
                        size_t idx = (size_t)arguments[1].number;
                        size_t slen = strlen(s);
                        if (idx < slen) {
                            result = number_value((double)(unsigned char)s[idx]);
                        } else {
                            result = number_value(-1.0);
                        }
                        free(s);
                    }
                }
            } else if (token_matches(parser, name, "કોડ_થી_અક્ષર") || token_matches(parser, name, "kod_thi_akshar")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    char buf[2] = { (char)(int)arguments[0].number, '\0' };
                    char *copy = copy_string(buf);
                    if (copy) result = make_owned_string_value(parser, name, copy, 1);
                }
            } else if (token_matches(parser, name, "લૉગ_કુદરતી") || token_matches(parser, name, "log_kudrati")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    result = number_value(log(arguments[0].number));
                }
            } else if (token_matches(parser, name, "લૉગ_૧૦") || token_matches(parser, name, "log_10")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    result = number_value(log10(arguments[0].number));
                }
            } else if (token_matches(parser, name, "ઘાત_મૂળ") || token_matches(parser, name, "ghat_mul")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    result = number_value(pow(arguments[0].number, arguments[1].number));
                }
            } else if (token_matches(parser, name, "ઈ_ઘાત") || token_matches(parser, name, "e_ghat")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    result = number_value(exp(arguments[0].number));
                }
            } else if (token_matches(parser, name, "યાદી_ઊલટે_ક્રમ") || token_matches(parser, name, "yadi_ulte_kram")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_LIST) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_LIST_FOR_LOOP);
                } else {
                    List *src = arguments[0].list;
                    List *dst = create_list(parser, name);
                    if (src && dst) {
                        for (size_t i = src->count; i > 0; i--) {
                            append_list_item(parser, dst, src->items[i - 1], name);
                        }
                    }
                    result = number_value(0.0);
                    result.kind = VALUE_LIST;
                    result.list = dst;
                }
            } else if (token_matches(parser, name, "યાદી_ટુકડા") || token_matches(parser, name, "yadi_tukda")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_LIST) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_LIST_FOR_LOOP);
                } else {
                    List *src = arguments[0].list;
                    size_t chunk_size = (size_t)arguments[1].number;
                    if (chunk_size == 0) chunk_size = 1;
                    List *chunks = create_list(parser, name);
                    if (src && chunks) {
                        for (size_t i = 0; i < src->count; i += chunk_size) {
                            List *chunk = create_list(parser, name);
                            for (size_t j = i; j < i + chunk_size && j < src->count; j++) {
                                append_list_item(parser, chunk, src->items[j], name);
                            }
                            Value cv = number_value(0.0);
                            cv.kind = VALUE_LIST;
                            cv.list = chunk;
                            append_list_item(parser, chunks, cv, name);
                        }
                    }
                    result = number_value(0.0);
                    result.kind = VALUE_LIST;
                    result.list = chunks;
                }
            } else if (token_matches(parser, name, "યાદી_ખીચડી") || token_matches(parser, name, "yadi_khichdi")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_LIST) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_LIST_FOR_LOOP);
                } else {
                    List *src = arguments[0].list;
                    List *dst = create_list(parser, name);
                    if (src && dst) {
                        for (size_t i = 0; i < src->count; i++) {
                            append_list_item(parser, dst, src->items[i], name);
                        }
                        if (dst->count > 1) {
                            for (size_t i = dst->count - 1; i > 0; i--) {
                                size_t j = (size_t)rand() % (i + 1);
                                Value tmp = dst->items[i];
                                dst->items[i] = dst->items[j];
                                dst->items[j] = tmp;
                            }
                        }
                    }
                    result = number_value(0.0);
                    result.kind = VALUE_LIST;
                    result.list = dst;
                }
            } else if (token_matches(parser, name, "ચાવી_છે") || token_matches(parser, name, "chavi_chhe")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_DICT) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_DICT_FOR_OPERATION);
                } else {
                    char *k = value_to_c_string(parser, arguments[1]);
                    if (k) {
                        Value *found = dict_get(arguments[0].dict, k, strlen(k));
                        free(k);
                        result = number_value(found != NULL ? 1.0 : 0.0);
                    }
                }
            } else if (token_matches(parser, name, "કોશ_જોડો") || token_matches(parser, name, "kosh_jodo")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else if (arguments[0].kind != VALUE_DICT || arguments[1].kind != VALUE_DICT) {
                    report_error(parser, name.line, name.column, MESSAGE_EXPECTED_DICT_FOR_OPERATION);
                } else {
                    Dict *d1 = arguments[0].dict;
                    Dict *d2 = arguments[1].dict;
                    Dict *dst = create_dict(parser, name);
                    if (d1 && dst) {
                        for (size_t i = 0; i < d1->count; i++) {
                            dict_set(parser, dst, d1->entries[i].key, d1->entries[i].key_length, d1->entries[i].value, name);
                        }
                    }
                    if (d2 && dst) {
                        for (size_t i = 0; i < d2->count; i++) {
                            dict_set(parser, dst, d2->entries[i].key, d2->entries[i].key_length, d2->entries[i].value, name);
                        }
                    }
                    result = number_value(0.0);
                    result.kind = VALUE_DICT;
                    result.dict = dst;
                }
            } else if (token_matches(parser, name, "માઇક્રો_સમય") || token_matches(parser, name, "micro_samay")) {
                if (argument_count != 0) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
#if defined(_WIN32)
                    FILETIME ft;
                    GetSystemTimeAsFileTime(&ft);
                    ULARGE_INTEGER uli;
                    uli.LowPart = ft.dwLowDateTime;
                    uli.HighPart = ft.dwHighDateTime;
                    double usec = (double)(uli.QuadPart - 116444736000000000ULL) / 10.0;
                    result = number_value(usec);
#else
                    struct timeval tv;
                    gettimeofday(&tv, NULL);
                    double usec = (double)tv.tv_sec * 1000000.0 + (double)tv.tv_usec;
                    result = number_value(usec);
#endif
                }
            } else if (token_matches(parser, name, "લેખન_આવૃત્તિ") || token_matches(parser, name, "lakhan_aavrutti")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    char *s = value_to_c_string(parser, arguments[0]);
                    if (s) {
                        size_t out_len = 0;
                        size_t count = arguments[1].number > 0 ? (size_t)arguments[1].number : 0;
                        char *rep = string_repeat(s, strlen(s), count, &out_len);
                        free(s);
                        if (rep) result = make_owned_string_value(parser, name, rep, out_len);
                    }
                }
            } else if (token_matches(parser, name, "લેખન_ગણતરી") || token_matches(parser, name, "lakhan_ganatari")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    char *s = value_to_c_string(parser, arguments[0]);
                    char *sub = value_to_c_string(parser, arguments[1]);
                    if (s && sub) {
                        size_t cnt = string_count_substring(s, strlen(s), sub, strlen(sub));
                        result = number_value((double)cnt);
                    }
                    if (s) free(s);
                    if (sub) free(sub);
                }
            } else if (token_matches(parser, name, "લેખન_ટુકડા_યાદી") || token_matches(parser, name, "lakhan_tukda_yadi")) {
                if (argument_count != 2) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    char *s = value_to_c_string(parser, arguments[0]);
                    char *delims = value_to_c_string(parser, arguments[1]);
                    List *dst = create_list(parser, name);
                    if (s && delims && dst) {
                        StringBuffer piece;
                        sb_init(&piece);
                        size_t slen = strlen(s);
                        for (size_t i = 0; i < slen; i++) {
                            char c = s[i];
                            if (strchr(delims, c) != NULL) {
                                Value pv = make_owned_string_value(parser, name, piece.data ? piece.data : copy_string(""), piece.length);
                                append_list_item(parser, dst, pv, name);
                                sb_init(&piece);
                            } else {
                                sb_append(&piece, &c, 1);
                            }
                        }
                        Value pv = make_owned_string_value(parser, name, piece.data ? piece.data : copy_string(""), piece.length);
                        append_list_item(parser, dst, pv, name);
                    }
                    if (s) free(s);
                    if (delims) free(delims);
                    result = number_value(0.0);
                    result.kind = VALUE_LIST;
                    result.list = dst;
                }
            } else if (token_matches(parser, name, "ફાઇલ_લાઇન_વાંચો") || token_matches(parser, name, "file_line_vancho")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    char *p = value_to_c_string(parser, arguments[0]);
                    if (p) {
                        result = read_file_lines(parser, name, p);
                        free(p);
                    }
                }
            } else if (token_matches(parser, name, "હેક્સ_થી_લેખન") || token_matches(parser, name, "hex_thi_lakhan")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    char *hex = value_to_c_string(parser, arguments[0]);
                    if (hex) {
                        size_t out_len = 0;
                        char *txt = hex_to_string(hex, strlen(hex), &out_len);
                        free(hex);
                        if (txt) {
                            result = make_owned_string_value(parser, name, txt, out_len);
                        } else {
                            result = null_value();
                        }
                    }
                }
            } else if (token_matches(parser, name, "સીએસવી_વાંચો") || token_matches(parser, name, "csv_vancho")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    char *csv = value_to_c_string(parser, arguments[0]);
                    if (csv) {
                        result = parse_csv_string(parser, name, csv, strlen(csv));
                        free(csv);
                    }
                }
            } else if (token_matches(parser, name, "સંખ્યા_છે") || token_matches(parser, name, "sankhya_chhe")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    result = number_value(arguments[0].kind == VALUE_NUMBER ? 1.0 : 0.0);
                }
            } else if (token_matches(parser, name, "લેખન_છે") || token_matches(parser, name, "lakhan_chhe")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    result = number_value(arguments[0].kind == VALUE_STRING ? 1.0 : 0.0);
                }
            } else if (token_matches(parser, name, "યાદી_છે") || token_matches(parser, name, "yadi_chhe")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    result = number_value(arguments[0].kind == VALUE_LIST ? 1.0 : 0.0);
                }
            } else if (token_matches(parser, name, "કોશ_છે") || token_matches(parser, name, "kosh_chhe")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    result = number_value(arguments[0].kind == VALUE_DICT ? 1.0 : 0.0);
                }
            } else if (token_matches(parser, name, "નકામો_છે") || token_matches(parser, name, "nakamo_chhe")) {
                if (argument_count != 1) {
                    report_error(parser, name.line, name.column, MESSAGE_WRONG_ARGUMENT_COUNT);
                } else {
                    result = number_value(arguments[0].kind == VALUE_NULL ? 1.0 : 0.0);
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

static Value parse_primary_atom(Parser *parser, int execute)
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
        value.string_source = parser->source;
        advance_token(parser);
        return value;
    }
    if (token.kind == TOKEN_LEFT_BRACKET) {
        List *list = execute ? create_list(parser, token) : NULL;
        advance_token(parser);
        while (!parser->failed &&
               parser->current.kind != TOKEN_RIGHT_BRACKET) {
            Value item = parse_expression(parser, execute);
            if (parser->failed) {
                return number_value(0.0);
            }
            if (execute && !append_list_item(parser, list, item, token)) {
                return number_value(0.0);
            }
            if (parser->current.kind != TOKEN_COMMA) {
                break;
            }
            advance_token(parser);
            if (parser->current.kind == TOKEN_RIGHT_BRACKET) {
                report_error(parser, parser->current.line,
                             parser->current.column, MESSAGE_EXPECTED_VALUE);
                return number_value(0.0);
            }
        }
        if (!parser->failed &&
            parser->current.kind != TOKEN_RIGHT_BRACKET) {
            report_error(parser, parser->current.line, parser->current.column,
                         MESSAGE_EXPECTED_LIST_CLOSE);
            return number_value(0.0);
        }
        if (!parser->failed) {
            advance_token(parser);
        }
        value = number_value(0.0);
        if (execute) {
            value.kind = VALUE_LIST;
            value.list = list;
        }
        return value;
    }
    if (token.kind == TOKEN_LEFT_BRACE) {
        Dict *dict = create_dict(parser, token);
        advance_token(parser);
        if (parser->current.kind != TOKEN_RIGHT_BRACE) {
            for (;;) {
                Value key_val = parse_expression(parser, execute);
                if (parser->failed) return number_value(0.0);
                if (parser->current.kind != TOKEN_COLON) {
                    report_error(parser, parser->current.line, parser->current.column,
                                 MESSAGE_EXPECTED_COLON_AFTER_DICT_KEY);
                    return number_value(0.0);
                }
                advance_token(parser);
                Value val = parse_expression(parser, execute);
                if (parser->failed) return number_value(0.0);
                if (execute) {
                    if (key_val.kind != VALUE_STRING) {
                        report_error(parser, token.line, token.column,
                                     MESSAGE_EXPECTED_DICT_KEY_STRING);
                        return number_value(0.0);
                    }
                    char *k_str = value_to_c_string(parser, key_val);
                    if (k_str == NULL) {
                        report_error(parser, token.line, token.column, MESSAGE_OUT_OF_MEMORY);
                        return number_value(0.0);
                    }
                    dict_set(parser, dict, k_str, strlen(k_str), val, token);
                    free(k_str);
                }
                if (parser->current.kind == TOKEN_COMMA) {
                    advance_token(parser);
                    if (parser->current.kind == TOKEN_RIGHT_BRACE) {
                        break;
                    }
                } else {
                    break;
                }
            }
        }
        if (!parser->failed && parser->current.kind != TOKEN_RIGHT_BRACE) {
            report_error(parser, parser->current.line, parser->current.column,
                         MESSAGE_EXPECTED_BLOCK_CLOSE);
            return number_value(0.0);
        }
        if (!parser->failed) {
            advance_token(parser);
        }
        value = number_value(0.0);
        if (execute) {
            value.kind = VALUE_DICT;
            value.dict = dict;
        }
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

static Value parse_primary(Parser *parser, int execute)
{
    Value value = parse_primary_atom(parser, execute);

    while (!parser->failed &&
           parser->current.kind == TOKEN_LEFT_BRACKET) {
        Token bracket = parser->current;
        Value index_value;
        size_t index;
        advance_token(parser);
        if (parser->current.kind == TOKEN_RIGHT_BRACKET) {
            report_error(parser, parser->current.line, parser->current.column,
                         MESSAGE_EXPECTED_LIST_INDEX);
            return number_value(0.0);
        }
        index_value = parse_expression(parser, execute);
        if (parser->failed) {
            return number_value(0.0);
        }
        if (parser->current.kind != TOKEN_RIGHT_BRACKET) {
            report_error(parser, parser->current.line, parser->current.column,
                         MESSAGE_EXPECTED_RIGHT_PAREN);
            return number_value(0.0);
        }
        advance_token(parser);
        if (execute) {
            if (value.kind == VALUE_DICT) {
                if (index_value.kind != VALUE_STRING) {
                    report_error(parser, bracket.line, bracket.column,
                                 MESSAGE_EXPECTED_DICT_KEY_STRING);
                    return number_value(0.0);
                }
                char *k_str = value_to_c_string(parser, index_value);
                if (k_str == NULL) {
                    report_error(parser, bracket.line, bracket.column,
                                 MESSAGE_OUT_OF_MEMORY);
                    return number_value(0.0);
                }
                Value *found = dict_get(value.dict, k_str, strlen(k_str));
                free(k_str);
                value = found ? *found : null_value();
            } else if (!resolve_list_index(parser, value, index_value, bracket,
                                           &index)) {
                return number_value(0.0);
            } else {
                value = value.list->items[index];
            }
        } else {
            value = number_value(0.0);
        }
    }
    return value;
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
            parser->current.kind == TOKEN_SLASH ||
            parser->current.kind == TOKEN_PERCENT)) {
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
        } else if (operation.kind == TOKEN_SLASH) {
            if (right.number == 0.0) {
                report_runtime_error(parser, operation, MESSAGE_DIVISION_BY_ZERO,
                                     execute);
                value = number_value(0.0);
            } else {
                value.number /= right.number;
            }
        } else if (operation.kind == TOKEN_PERCENT) {
            if (right.number == 0.0) {
                report_runtime_error(parser, operation, MESSAGE_DIVISION_BY_ZERO,
                                     execute);
                value = number_value(0.0);
            } else {
                value.number = fmod(value.number, right.number);
            }
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
        if (operation.kind == TOKEN_PLUS &&
            value.kind == VALUE_STRING && right.kind == VALUE_STRING) {
            if (execute &&
                !concatenate_strings(parser, operation, value, right, &value)) {
                return number_value(0.0);
            }
            if (!execute) {
                value = number_value(0.0);
                value.kind = VALUE_STRING;
            }
        } else if (value.kind != VALUE_NUMBER || right.kind != VALUE_NUMBER) {
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
        if (value.kind == VALUE_STRING && right.kind == VALUE_STRING &&
            (operation.kind == TOKEN_EQUAL_EQUAL ||
             operation.kind == TOKEN_BANG_EQUAL)) {
            comparison = string_values_equal(parser, value, right);
            if (operation.kind == TOKEN_BANG_EQUAL) {
                comparison = !comparison;
            }
        } else if (value.kind != VALUE_NUMBER || right.kind != VALUE_NUMBER) {
            report_runtime_error(parser, operation,
                                 MESSAGE_COMPARISON_NUMBERS_REQUIRED, execute);
            value = number_value(0.0);
            continue;
        } else {
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

static Value parse_logical_or(Parser *parser, int execute)
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

static Value parse_expression(Parser *parser, int execute)
{
    Value condition = parse_logical_or(parser, execute);
    if (!parser->failed && parser->current.kind == TOKEN_QUESTION) {
        advance_token(parser);
        int cond_truthy = value_is_truthy(condition);
        Value then_value = parse_expression(parser, execute && cond_truthy);
        if (parser->failed) {
            return number_value(0.0);
        }
        if (parser->current.kind != TOKEN_COLON) {
            report_error(parser, parser->current.line, parser->current.column,
                         MESSAGE_EXPECTED_COLON_IN_TERNARY);
            return number_value(0.0);
        }
        advance_token(parser);
        Value else_value = parse_expression(parser, execute && !cond_truthy);
        if (parser->failed) {
            return number_value(0.0);
        }
        return execute ? (cond_truthy ? then_value : else_value) : number_value(0.0);
    }
    return condition;
}

static int write_string(Parser *parser, FILE *output, const char *source,
                        size_t offset, size_t length)
{
    size_t index;
    size_t end = offset + length;
    (void)parser;
    for (index = offset; index < end; index++) {
        char character = source[index];
        if (character == '\\' && index + 1 < end) {
            index++;
            switch (source[index]) {
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

static int write_value_recursive(Parser *parser, Value value,
                                 List **ancestors, size_t depth)
{
    size_t index;
    if (value.kind == VALUE_STRING) {
        if (value.owned_string != NULL) {
            return fwrite(value.owned_string, 1, value.string_length, stdout) ==
                   value.string_length;
        }
        return write_string(parser, stdout,
                            value.string_source == NULL ?
                                parser->source : value.string_source,
                            value.string_offset,
                            value.string_length);
    }
    if (value.kind == VALUE_LIST) {
        if (depth >= 256) {
            return 0;
        }
        for (index = 0; index < depth; index++) {
            if (ancestors[index] == value.list) {
                return fputs("<cycle>", stdout) >= 0;
            }
        }
        ancestors[depth] = value.list;
        if (fputc('[', stdout) == EOF) {
            return 0;
        }
        for (index = 0; index < value.list->count; index++) {
            if ((index > 0 && fputs(", ", stdout) == EOF) ||
                !write_value_recursive(parser, value.list->items[index],
                                       ancestors, depth + 1)) {
                return 0;
            }
        }
        return fputc(']', stdout) != EOF;
    }
    if (value.kind == VALUE_DICT) {
        if (depth >= 256) {
            return 0;
        }
        if (fputc('{', stdout) == EOF) {
            return 0;
        }
        for (index = 0; index < value.dict->count; index++) {
            if ((index > 0 && fputs(", ", stdout) == EOF) ||
                fwrite(value.dict->entries[index].key, 1,
                       value.dict->entries[index].key_length, stdout) !=
                value.dict->entries[index].key_length ||
                fputs(": ", stdout) == EOF ||
                !write_value_recursive(parser, value.dict->entries[index].value,
                                       ancestors, depth + 1)) {
                return 0;
            }
        }
        return fputc('}', stdout) != EOF;
    }
    if (value.kind == VALUE_NULL) {
        return fputs("નકામો", stdout) >= 0;
    }
    return printf("%.15g", value.number) >= 0;
}

static int write_value(Parser *parser, Value value)
{
    List *ancestors[256];
    return write_value_recursive(parser, value, ancestors, 0);
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

static List *create_list(Parser *parser, Token token)
{
    StringStorage *storage = parser->string_storage;
    List *list;

    if (storage->list_count == storage->list_capacity) {
        size_t capacity = storage->list_capacity == 0 ? 4 :
                          storage->list_capacity * 2;
        List **lists;
        if (capacity < storage->list_capacity ||
            capacity > (size_t)-1 / sizeof(*storage->lists)) {
            report_error(parser, token.line, token.column,
                         MESSAGE_OUT_OF_MEMORY_FOR_LIST);
            return NULL;
        }
        lists = (List **)realloc(storage->lists,
                                 capacity * sizeof(*lists));
        if (lists == NULL) {
            report_error(parser, token.line, token.column,
                         MESSAGE_OUT_OF_MEMORY_FOR_LIST);
            return NULL;
        }
        storage->lists = lists;
        storage->list_capacity = capacity;
    }
    list = (List *)calloc(1, sizeof(*list));
    if (list == NULL) {
        report_error(parser, token.line, token.column,
                     MESSAGE_OUT_OF_MEMORY_FOR_LIST);
        return NULL;
    }
    storage->lists[storage->list_count++] = list;
    return list;
}

static int append_list_item(Parser *parser, List *list, Value value,
                            Token token)
{
    if (list->count == list->capacity) {
        size_t capacity = list->capacity == 0 ? 4 : list->capacity * 2;
        Value *items;
        if (capacity < list->capacity ||
            capacity > (size_t)-1 / sizeof(*list->items)) {
            report_error(parser, token.line, token.column,
                         MESSAGE_OUT_OF_MEMORY_FOR_LIST);
            return 0;
        }
        items = (Value *)realloc(list->items, capacity * sizeof(*items));
        if (items == NULL) {
            report_error(parser, token.line, token.column,
                         MESSAGE_OUT_OF_MEMORY_FOR_LIST);
            return 0;
        }
        list->items = items;
        list->capacity = capacity;
    }
    list->items[list->count++] = value;
    return 1;
}

static int insert_list_item(Parser *parser, List *list, size_t index,
                            Value value, Token token)
{
    if (list->count == list->capacity) {
        size_t capacity = list->capacity == 0 ? 4 : list->capacity * 2;
        Value *items;
        if (capacity < list->capacity ||
            capacity > (size_t)-1 / sizeof(*list->items)) {
            report_error(parser, token.line, token.column,
                         MESSAGE_OUT_OF_MEMORY_FOR_LIST);
            return 0;
        }
        items = (Value *)realloc(list->items, capacity * sizeof(*items));
        if (items == NULL) {
            report_error(parser, token.line, token.column,
                         MESSAGE_OUT_OF_MEMORY_FOR_LIST);
            return 0;
        }
        list->items = items;
        list->capacity = capacity;
    }
    if (index < list->count) {
        memmove(&list->items[index + 1], &list->items[index],
                (list->count - index) * sizeof(Value));
    }
    list->items[index] = value;
    list->count++;
    return 1;
}

static int resolve_list_index(Parser *parser, Value list_value,
                              Value index_value, Token token, size_t *index)
{
    if (list_value.kind != VALUE_LIST) {
        report_error(parser, token.line, token.column,
                     MESSAGE_INDEXED_VALUE_NOT_LIST);
        return 0;
    }
    if (index_value.kind != VALUE_NUMBER ||
        index_value.number < 0.0 ||
        index_value.number >= (double)(size_t)-1 ||
        index_value.number != (double)(size_t)index_value.number) {
        report_error(parser, token.line, token.column,
                     MESSAGE_LIST_INDEX_MUST_BE_INTEGER);
        return 0;
    }
    *index = (size_t)index_value.number;
    if (*index >= list_value.list->count) {
        report_error(parser, token.line, token.column,
                     MESSAGE_LIST_INDEX_OUT_OF_RANGE);
        return 0;
    }
    return 1;
}

static int parse_try_catch(Parser *parser, int execute)
{
    advance_token(parser);
    int prev_in_try = parser->in_try;
    parser->in_try++;
    int try_had_error = 0;

    if (!parse_block(parser, execute)) {
        if (parser->error_caught) {
            try_had_error = 1;
            parser->error_caught = 0;
            parser->failed = 0;
        } else {
            parser->in_try = prev_in_try;
            return 0;
        }
    } else if (parser->error_caught) {
        try_had_error = 1;
        parser->error_caught = 0;
    }
    parser->in_try = prev_in_try;

    if (parser->current.kind != TOKEN_CATCH) {
        report_error(parser, parser->current.line, parser->current.column,
                     MESSAGE_EXPECTED_CATCH_AFTER_TRY);
        return 0;
    }
    advance_token(parser);
    Token error_var;
    memset(&error_var, 0, sizeof(error_var));
    int has_var = 0;
    if (parser->current.kind == TOKEN_LEFT_PAREN) {
        advance_token(parser);
        if (parser->current.kind != TOKEN_IDENTIFIER) {
            report_error(parser, parser->current.line, parser->current.column,
                         MESSAGE_EXPECTED_PARAMETER);
            return 0;
        }
        error_var = parser->current;
        has_var = 1;
        advance_token(parser);
        if (parser->current.kind != TOKEN_RIGHT_PAREN) {
            report_error(parser, parser->current.line, parser->current.column,
                         MESSAGE_EXPECTED_RIGHT_PAREN);
            return 0;
        }
        advance_token(parser);
    }

    int catch_execute = execute && try_had_error;
    if (catch_execute && has_var) {
        const char *err_text = parser->last_error_message ? parser->last_error_message : "";
        size_t err_len = strlen(err_text);
        char *err_copy = (char *)malloc(err_len + 1);
        if (err_copy != NULL) {
            memcpy(err_copy, err_text, err_len + 1);
            if (store_owned_string(parser, error_var, err_copy)) {
                Value err_val = number_value(0.0);
                err_val.kind = VALUE_STRING;
                err_val.string_offset = 0;
                err_val.string_length = err_len;
                err_val.owned_string = err_copy;
                Variable *existing = find_variable(parser, error_var);
                if (existing != NULL) {
                    existing->value = err_val;
                } else {
                    declare_variable(parser, error_var, err_val);
                }
            }
        }
    }
    return parse_block(parser, catch_execute);
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
    while (!parser->failed &&
           parser->current.kind != TOKEN_RIGHT_BRACE &&
           parser->current.kind != TOKEN_EOF &&
           parser->current.kind != TOKEN_END) {
        parse_statement(parser, execute && !parser->returned &&
                                !parser->loop_broken && !parser->loop_continued &&
                                !parser->error_caught);
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
    parser->loop_depth++;

    for (;;) {
        Value condition;
        int body_execute;

        if (parser->current.kind != TOKEN_LEFT_PAREN) {
            report_error(parser, parser->current.line, parser->current.column,
                         MESSAGE_EXPECTED_WHILE_OPEN);
            parser->loop_depth--;
            return 0;
        }
        advance_token(parser);
        condition = parse_expression(parser, execute);
        if (parser->failed) {
            parser->loop_depth--;
            return 0;
        }
        if (parser->current.kind != TOKEN_RIGHT_PAREN) {
            report_error(parser, parser->current.line, parser->current.column,
                         MESSAGE_EXPECTED_CONDITION_CLOSE);
            parser->loop_depth--;
            return 0;
        }
        if (condition.kind == VALUE_STRING) {
            report_runtime_error(parser, keyword, MESSAGE_CONDITION_TYPE,
                                 execute);
            if (parser->failed) {
                parser->loop_depth--;
                return 0;
            }
        }

        body_execute = execute && value_is_truthy(condition);
        advance_token(parser);
        if (!parse_block(parser, body_execute)) {
            parser->loop_depth--;
            return 0;
        }
        if (parser->returned || parser->error_caught) {
            parser->loop_depth--;
            return 1;
        }
        if (parser->loop_broken) {
            parser->loop_broken = 0;
            parser->loop_depth--;
            return 1;
        }
        if (parser->loop_continued) {
            parser->loop_continued = 0;
        }
        if (!body_execute) {
            parser->loop_depth--;
            return 1;
        }

        parser->offset = condition_open.source_offset;
        parser->line = condition_open.line;
        parser->column = condition_open.column;
        parser->current = make_token(TOKEN_EOF, parser->line, parser->column);
        advance_token(parser);
    }
}

static int parse_for_loop(Parser *parser, int execute)
{
    Token variable;
    Token in_keyword;
    Token body_open;
    Value first;
    Value last = null_value();
    List *list = NULL;
    Dict *dict = NULL;
    size_t index;
    int is_range = 0;

    advance_token(parser);
    if (parser->current.kind != TOKEN_LEFT_PAREN) {
        report_error(parser, parser->current.line, parser->current.column,
                     MESSAGE_EXPECTED_FOR_OPEN);
        return 0;
    }
    advance_token(parser);
    if (parser->current.kind != TOKEN_IDENTIFIER) {
        report_error(parser, parser->current.line, parser->current.column,
                     MESSAGE_EXPECTED_FOR_VARIABLE);
        return 0;
    }
    variable = parser->current;
    advance_token(parser);
    if (parser->current.kind != TOKEN_IN) {
        report_error(parser, parser->current.line, parser->current.column,
                     MESSAGE_EXPECTED_IN);
        return 0;
    }
    in_keyword = parser->current;
    advance_token(parser);
    first = parse_expression(parser, execute);
    if (parser->failed) {
        return 0;
    }
    if (parser->current.kind == TOKEN_RANGE) {
        is_range = 1;
        if (execute && first.kind != VALUE_NUMBER) {
            report_error(parser, in_keyword.line, in_keyword.column,
                         MESSAGE_RANGE_NUMBERS_REQUIRED);
            return 0;
        }
        advance_token(parser);
        if (parser->current.kind == TOKEN_RIGHT_PAREN) {
            report_error(parser, parser->current.line, parser->current.column,
                         MESSAGE_EXPECTED_RANGE_END);
            return 0;
        }
        last = parse_expression(parser, execute);
        if (parser->failed) {
            return 0;
        }
        if (execute &&
            (last.kind != VALUE_NUMBER ||
             first.number < -9007199254740991.0 ||
             first.number > 9007199254740991.0 ||
             last.number < -9007199254740991.0 ||
             last.number > 9007199254740991.0 ||
             first.number != (double)(long long)first.number ||
             last.number != (double)(long long)last.number)) {
            report_error(parser, in_keyword.line, in_keyword.column,
                         MESSAGE_RANGE_NUMBERS_REQUIRED);
            return 0;
        }
    } else if (execute) {
        if (first.kind == VALUE_DICT) {
            dict = first.dict;
        } else if (first.kind != VALUE_LIST) {
            report_error(parser, in_keyword.line, in_keyword.column,
                         MESSAGE_EXPECTED_LIST_FOR_LOOP);
            return 0;
        } else {
            list = first.list;
        }
    }
    if (parser->current.kind != TOKEN_RIGHT_PAREN) {
        report_error(parser, parser->current.line, parser->current.column,
                     MESSAGE_EXPECTED_CONDITION_CLOSE);
        return 0;
    }
    advance_token(parser);
    if (parser->current.kind != TOKEN_LEFT_BRACE) {
        report_error(parser, parser->current.line, parser->current.column,
                     MESSAGE_EXPECTED_BLOCK_OPEN);
        return 0;
    }
    body_open = parser->current;
    parser->loop_depth++;
    if (!parse_block(parser, 0)) {
        parser->loop_depth--;
        return 0;
    }
    if (!execute) {
        parser->loop_depth--;
        return 1;
    }

    if (is_range) {
        double current = first.number;
        while (!parser->failed && !parser->error_caught && current < last.number) {
            Value loop_value = number_value(current);
            Variable *existing;
            parser->returned = 0;
            existing = find_variable(parser, variable);
            if (existing != NULL) {
                existing->value = loop_value;
            } else if (!declare_variable(parser, variable, loop_value)) {
                parser->loop_depth--;
                return 0;
            }
            parser->offset = body_open.source_offset;
            parser->line = body_open.line;
            parser->column = body_open.column;
            parser->current = make_token(TOKEN_EOF, parser->line,
                                         parser->column);
            advance_token(parser);
            if (!parse_block(parser, 1) || parser->returned || parser->error_caught) {
                break;
            }
            if (parser->loop_broken) {
                parser->loop_broken = 0;
                break;
            }
            if (parser->loop_continued) {
                parser->loop_continued = 0;
            }
            current += 1.0;
        }
    } else if (dict != NULL) {
        for (index = 0; index < dict->count && !parser->failed && !parser->error_caught; index++) {
            Variable *existing;
            parser->returned = 0;
            Value key_val = number_value(0.0);
            char *k_copy = (char *)malloc(dict->entries[index].key_length + 1);
            if (k_copy == NULL) {
                parser->loop_depth--;
                report_error(parser, variable.line, variable.column, MESSAGE_OUT_OF_MEMORY);
                return 0;
            }
            memcpy(k_copy, dict->entries[index].key, dict->entries[index].key_length + 1);
            if (!store_owned_string(parser, variable, k_copy)) {
                parser->loop_depth--;
                return 0;
            }
            key_val.kind = VALUE_STRING;
            key_val.string_offset = 0;
            key_val.string_length = dict->entries[index].key_length;
            key_val.owned_string = k_copy;

            existing = find_variable(parser, variable);
            if (existing != NULL) {
                existing->value = key_val;
            } else if (!declare_variable(parser, variable, key_val)) {
                parser->loop_depth--;
                return 0;
            }
            parser->offset = body_open.source_offset;
            parser->line = body_open.line;
            parser->column = body_open.column;
            parser->current = make_token(TOKEN_EOF, parser->line,
                                         parser->column);
            advance_token(parser);
            if (!parse_block(parser, 1) || parser->returned || parser->error_caught) {
                break;
            }
            if (parser->loop_broken) {
                parser->loop_broken = 0;
                break;
            }
            if (parser->loop_continued) {
                parser->loop_continued = 0;
            }
        }
    } else {
        for (index = 0; index < list->count && !parser->failed && !parser->error_caught; index++) {
            Variable *existing;
            parser->returned = 0;
            existing = find_variable(parser, variable);
            if (existing != NULL) {
                existing->value = list->items[index];
            } else if (!declare_variable(parser, variable,
                                         list->items[index])) {
                parser->loop_depth--;
                return 0;
            }
            parser->offset = body_open.source_offset;
            parser->line = body_open.line;
            parser->column = body_open.column;
            parser->current = make_token(TOKEN_EOF, parser->line,
                                         parser->column);
            advance_token(parser);
            if (!parse_block(parser, 1) || parser->returned || parser->error_caught) {
                break;
            }
            if (parser->loop_broken) {
                parser->loop_broken = 0;
                break;
            }
            if (parser->loop_continued) {
                parser->loop_continued = 0;
            }
        }
    }
    parser->loop_depth--;
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
        !write_string(parser, stderr, parser->source, message.string_offset,
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

static int parse_import(Parser *parser, Token keyword, int execute)
{
    Value path = number_value(0.0);

    advance_token(parser);
    if (parser->current.kind != TOKEN_STRING) {
        report_error(parser, parser->current.line, parser->current.column,
                     MESSAGE_EXPECTED_IMPORT_PATH);
        return 0;
    }
    path.kind = VALUE_STRING;
    path.string_offset = parser->current.string_offset;
    path.string_length = parser->current.string_length;
    path.string_source = parser->source;
    advance_token(parser);
    if (parser->current.kind != TOKEN_SEMICOLON) {
        report_error(parser, parser->current.line, parser->current.column,
                     MESSAGE_EXPECTED_IMPORT_SEMICOLON);
        return 0;
    }
    advance_token(parser);
    if (execute && !import_module(parser, keyword, path)) {
        return 0;
    }
    return !parser->failed;
}

static int parse_variable_assignment(Parser *parser, Token name, int execute)
{
    Value value;
    Value indexed_value = number_value(0.0);
    List *target_list = NULL;
    Dict *target_dict = NULL;
    char *target_key = NULL;
    size_t list_index = 0;
    int indexed_assignment = 0;

    while (parser->current.kind == TOKEN_LEFT_BRACKET) {
        Token bracket = parser->current;
        Value index_value;
        advance_token(parser);
        index_value = parse_expression(parser, execute);
        if (parser->failed) {
            free(target_key);
            return 0;
        }
        if (parser->current.kind != TOKEN_RIGHT_BRACKET) {
            report_error(parser, parser->current.line, parser->current.column,
                         MESSAGE_EXPECTED_LIST_INDEX);
            free(target_key);
            return 0;
        }
        if (execute) {
            if (!indexed_assignment) {
                Variable *variable = find_variable(parser, name);
                if (variable == NULL) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_UNDEFINED_VARIABLE);
                    free(target_key);
                    return 0;
                }
                indexed_value = variable->value;
            }
            if (indexed_value.kind == VALUE_DICT) {
                if (index_value.kind != VALUE_STRING) {
                    report_error(parser, bracket.line, bracket.column,
                                 MESSAGE_EXPECTED_DICT_KEY_STRING);
                    free(target_key);
                    return 0;
                }
                target_dict = indexed_value.dict;
                target_list = NULL;
                free(target_key);
                target_key = value_to_c_string(parser, index_value);
                Value *existing = dict_get(target_dict, target_key, strlen(target_key));
                indexed_value = existing ? *existing : null_value();
            } else if (indexed_value.kind == VALUE_LIST) {
                target_dict = NULL;
                free(target_key);
                target_key = NULL;
                if (!resolve_list_index(parser, indexed_value, index_value, bracket,
                                        &list_index)) {
                    return 0;
                }
                target_list = indexed_value.list;
                indexed_value = target_list->items[list_index];
            } else {
                report_error(parser, bracket.line, bracket.column,
                             MESSAGE_INDEXED_VALUE_NOT_LIST);
                free(target_key);
                return 0;
            }
        }
        indexed_assignment = 1;
        advance_token(parser);
    }

    Token assign_op = parser->current;
    if (assign_op.kind != TOKEN_EQUAL &&
        assign_op.kind != TOKEN_PLUS_EQUAL &&
        assign_op.kind != TOKEN_MINUS_EQUAL &&
        assign_op.kind != TOKEN_STAR_EQUAL &&
        assign_op.kind != TOKEN_SLASH_EQUAL &&
        assign_op.kind != TOKEN_PERCENT_EQUAL) {
        report_error(parser, parser->current.line, parser->current.column,
                     MESSAGE_EXPECTED_ASSIGNMENT);
        free(target_key);
        return 0;
    }
    Value cur_val = number_value(0.0);
    if (execute && assign_op.kind != TOKEN_EQUAL) {
        if (indexed_assignment) {
            cur_val = indexed_value;
        } else {
            Variable *var = find_variable(parser, name);
            if (var == NULL) {
                report_error(parser, name.line, name.column, MESSAGE_UNDEFINED_VARIABLE);
                free(target_key);
                return 0;
            }
            cur_val = var->value;
        }
    }
    advance_token(parser);
    value = parse_expression(parser, execute);
    if (parser->failed) {
        free(target_key);
        return 0;
    }
    if (parser->current.kind != TOKEN_SEMICOLON) {
        report_error(parser, parser->current.line, parser->current.column,
                     MESSAGE_EXPECTED_EXPRESSION_SEMICOLON);
        free(target_key);
        return 0;
    }
    if (execute) {
        if (assign_op.kind == TOKEN_PLUS_EQUAL) {
            if (cur_val.kind == VALUE_STRING && value.kind == VALUE_STRING) {
                char *s1 = value_to_c_string(parser, cur_val);
                char *s2 = value_to_c_string(parser, value);
                if (s1 && s2) {
                    size_t l1 = strlen(s1);
                    size_t l2 = strlen(s2);
                    char *cat = (char *)malloc(l1 + l2 + 1);
                    if (cat) {
                        memcpy(cat, s1, l1);
                        memcpy(cat + l1, s2, l2);
                        cat[l1 + l2] = '\0';
                        value = make_owned_string_value(parser, assign_op, cat, l1 + l2);
                    }
                }
                free(s1);
                free(s2);
            } else if (cur_val.kind == VALUE_NUMBER && value.kind == VALUE_NUMBER) {
                value = number_value(cur_val.number + value.number);
            } else {
                report_runtime_error(parser, assign_op, MESSAGE_ARITHMETIC_NUMBERS_REQUIRED, execute);
                free(target_key);
                return 0;
            }
        } else if (assign_op.kind == TOKEN_MINUS_EQUAL) {
            if (cur_val.kind == VALUE_NUMBER && value.kind == VALUE_NUMBER) {
                value = number_value(cur_val.number - value.number);
            } else {
                report_runtime_error(parser, assign_op, MESSAGE_ARITHMETIC_NUMBERS_REQUIRED, execute);
                free(target_key);
                return 0;
            }
        } else if (assign_op.kind == TOKEN_STAR_EQUAL) {
            if (cur_val.kind == VALUE_NUMBER && value.kind == VALUE_NUMBER) {
                value = number_value(cur_val.number * value.number);
            } else {
                report_runtime_error(parser, assign_op, MESSAGE_ARITHMETIC_NUMBERS_REQUIRED, execute);
                free(target_key);
                return 0;
            }
        } else if (assign_op.kind == TOKEN_SLASH_EQUAL) {
            if (cur_val.kind == VALUE_NUMBER && value.kind == VALUE_NUMBER) {
                if (value.number == 0.0) {
                    report_runtime_error(parser, assign_op, MESSAGE_DIVISION_BY_ZERO, execute);
                    free(target_key);
                    return 0;
                }
                value = number_value(cur_val.number / value.number);
            } else {
                report_runtime_error(parser, assign_op, MESSAGE_ARITHMETIC_NUMBERS_REQUIRED, execute);
                free(target_key);
                return 0;
            }
        } else if (assign_op.kind == TOKEN_PERCENT_EQUAL) {
            if (cur_val.kind == VALUE_NUMBER && value.kind == VALUE_NUMBER) {
                if (value.number == 0.0) {
                    report_runtime_error(parser, assign_op, MESSAGE_DIVISION_BY_ZERO, execute);
                    free(target_key);
                    return 0;
                }
                value = number_value(fmod(cur_val.number, value.number));
            } else {
                report_runtime_error(parser, assign_op, MESSAGE_ARITHMETIC_NUMBERS_REQUIRED, execute);
                free(target_key);
                return 0;
            }
        }

        if (indexed_assignment) {
            if (target_dict != NULL && target_key != NULL) {
                dict_set(parser, target_dict, target_key, strlen(target_key), value, name);
            } else if (target_list != NULL) {
                target_list->items[list_index] = value;
            }
        } else if (find_variable(parser, name) != NULL) {
            if (!assign_variable(parser, name, value)) {
                free(target_key);
                return 0;
            }
        } else if (!declare_variable(parser, name, value)) {
            free(target_key);
            return 0;
        }
    }
    free(target_key);
    advance_token(parser);
    return !parser->failed;
}

static int parse_const_declaration(Parser *parser, int execute)
{
    Token const_token = parser->current;
    Token name;
    Value value = null_value();
    advance_token(parser);
    if (parser->current.kind != TOKEN_IDENTIFIER) {
        report_error(parser, parser->current.line, parser->current.column,
                     MESSAGE_EXPECTED_PARAMETER);
        return 0;
    }
    name = parser->current;
    advance_token(parser);
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
    advance_token(parser);
    if (execute) {
        size_t i;
        Environment *env = parser->environment;
        for (i = 0; i < env->variable_count; i++) {
            if (env->variables[i].name_length == name.string_length &&
                memcmp(env->variables[i].name, parser->source + name.string_offset, name.string_length) == 0) {
                report_error(parser, const_token.line, const_token.column,
                             MESSAGE_VARIABLE_ALREADY_DECLARED);
                return 0;
            }
        }
        if (!declare_variable_ex(parser, name, value, 1)) {
            return 0;
        }
    }
    return 1;
}

static int register_function(Parser *parser, Token name, Token *parameters,
                             size_t parameter_count, Token body_open)
{
    Function *existing = find_function(parser, name);
    FunctionTable *table = parser->function_table;
    Function *functions;
    char *function_name;
    size_t capacity;

    if (existing != NULL) {
        free(parameters);
        if (existing->source == parser->source &&
            existing->declaration_offset == name.source_offset) {
            return 1;
        }
        report_error(parser, name.line, name.column,
                     MESSAGE_DUPLICATE_FUNCTION);
        return 0;
    }
    if (name.string_length == (size_t)-1) {
        free(parameters);
        report_error(parser, name.line, name.column,
                     MESSAGE_OUT_OF_MEMORY_FOR_FUNCTION);
        return 0;
    }
    function_name = (char *)malloc(name.string_length + 1);
    if (function_name == NULL) {
        free(parameters);
        report_error(parser, name.line, name.column,
                     MESSAGE_OUT_OF_MEMORY_FOR_FUNCTION);
        return 0;
    }
    memcpy(function_name, parser->source + name.string_offset,
           name.string_length);
    function_name[name.string_length] = '\0';
    if (table->count == table->capacity) {
        if (table->capacity == 0) {
            capacity = 8;
        } else {
            if (table->capacity > (size_t)-1 / 2 / sizeof(*table->items)) {
                free(parameters);
                free(function_name);
                report_error(parser, name.line, name.column,
                             MESSAGE_OUT_OF_MEMORY_FOR_FUNCTION);
                return 0;
            }
            capacity = table->capacity * 2;
        }
        functions = (Function *)realloc(table->items,
                                        capacity * sizeof(*functions));
        if (functions == NULL) {
            free(parameters);
            free(function_name);
            report_error(parser, name.line, name.column,
                         MESSAGE_OUT_OF_MEMORY_FOR_FUNCTION);
            return 0;
        }
        table->items = functions;
        table->capacity = capacity;
    }
    table->items[table->count].name = function_name;
    table->items[table->count].name_length =
        name.string_length;
    table->items[table->count].declaration_offset =
        name.source_offset;
    table->items[table->count].source = parser->source;
    table->items[table->count].filename = parser->filename;
    table->items[table->count].parameters = parameters;
    table->items[table->count].parameter_count =
        parameter_count;
    table->items[table->count].body_open = body_open;
    table->count++;
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
    if (is_builtin_function_name(parser, name)) {
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

    if (statement.kind == TOKEN_TRY) {
        return parse_try_catch(parser, execute);
    }
    if (statement.kind == TOKEN_CONST) {
        return parse_const_declaration(parser, execute);
    }
    if (statement.kind == TOKEN_BREAK) {
        advance_token(parser);
        if (parser->current.kind != TOKEN_SEMICOLON) {
            report_error(parser, parser->current.line, parser->current.column,
                         MESSAGE_EXPECTED_EXPRESSION_SEMICOLON);
            return 0;
        }
        if (parser->loop_depth == 0) {
            report_error(parser, statement.line, statement.column,
                         MESSAGE_BREAK_OUTSIDE_LOOP);
            return 0;
        }
        if (execute) {
            parser->loop_broken = 1;
        }
        advance_token(parser);
        return !parser->failed;
    }
    if (statement.kind == TOKEN_CONTINUE) {
        advance_token(parser);
        if (parser->current.kind != TOKEN_SEMICOLON) {
            report_error(parser, parser->current.line, parser->current.column,
                         MESSAGE_EXPECTED_EXPRESSION_SEMICOLON);
            return 0;
        }
        if (parser->loop_depth == 0) {
            report_error(parser, statement.line, statement.column,
                         MESSAGE_CONTINUE_OUTSIDE_LOOP);
            return 0;
        }
        if (execute) {
            parser->loop_continued = 1;
        }
        advance_token(parser);
        return !parser->failed;
    }
    if (statement.kind == TOKEN_IF) {
        advance_token(parser);
        return parse_if_condition(parser, execute, statement);
    }
    if (statement.kind == TOKEN_WHILE) {
        advance_token(parser);
        return parse_while_loop(parser, execute, statement);
    }
    if (statement.kind == TOKEN_FOR) {
        return parse_for_loop(parser, execute);
    }
    if (statement.kind == TOKEN_FUNCTION) {
        return parse_function_declaration(parser, execute);
    }
    if (statement.kind == TOKEN_IMPORT) {
        return parse_import(parser, statement, execute);
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
        parser->current.kind == TOKEN_FOR ||
        parser->current.kind == TOKEN_FUNCTION ||
        parser->current.kind == TOKEN_IMPORT ||
        parser->current.kind == TOKEN_RETURN ||
        parser->current.kind == TOKEN_TRY ||
        parser->current.kind == TOKEN_BREAK ||
        parser->current.kind == TOKEN_CONTINUE ||
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

static void rebase_value_source(Value *value, const char *old_source,
                                const char *new_source)
{
    if (value->kind == VALUE_STRING && value->owned_string == NULL &&
        value->string_source == old_source) {
        value->string_source = new_source;
    }
}

static void rebase_repl_sources(Environment *globals,
                                FunctionTable *function_table,
                                StringStorage *string_storage,
                                const char *old_source,
                                const char *new_source)
{
    size_t index;
    for (index = 0; index < globals->variable_count; index++) {
        rebase_value_source(&globals->variables[index].value, old_source,
                            new_source);
    }
    for (index = 0; index < string_storage->list_count; index++) {
        List *list = string_storage->lists[index];
        size_t item_index;
        for (item_index = 0; item_index < list->count; item_index++) {
            rebase_value_source(&list->items[item_index], old_source,
                                new_source);
        }
    }
    for (index = 0; index < function_table->count; index++) {
        if (function_table->items[index].source == old_source) {
            function_table->items[index].source = new_source;
        }
    }
}

static int run_repl(Language language)
{
    Parser parser;
    Environment globals;
    StringStorage string_storage;
    FunctionTable function_table;
    ModuleStorage modules;
    char *source = NULL;
    size_t source_length = 0;
    size_t source_capacity = 0;
    int read_status;
    int result = EXIT_SUCCESS;

    memset(&globals, 0, sizeof(globals));
    memset(&string_storage, 0, sizeof(string_storage));
    memset(&function_table, 0, sizeof(function_table));
    memset(&modules, 0, sizeof(modules));
    memset(&parser, 0, sizeof(parser));
    parser.source = "";
    parser.filename = "REPL";
    parser.language = language;
    parser.environment = &globals;
    parser.globals = &globals;
    parser.function_table = &function_table;
    parser.string_storage = &string_storage;
    parser.modules = &modules;
    parser.line = 1;
    parser.column = 1;

    for (;;) {
        char *line;
        size_t line_length;
        size_t command_offset;
        size_t command_line;
        const char *old_source;
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
        old_source = source;
        if (!append_repl_line(&source, &source_length, &source_capacity,
                              line, line_length)) {
            free(line);
            report_error(&parser, parser.line, parser.column,
                         MESSAGE_OUT_OF_MEMORY_FOR_INPUT);
            result = EXIT_FAILURE;
            break;
        }
        if (old_source != source) {
            rebase_repl_sources(&globals, &function_table, &string_storage,
                                old_source, source);
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

    while (globals.variable_count > 0) {
        free(globals.variables[--globals.variable_count].name);
    }
    free(globals.variables);
    while (function_table.count > 0) {
        Function *function = &function_table.items[--function_table.count];
        free(function->name);
        free(function->parameters);
    }
    free(function_table.items);
    while (string_storage.count > 0) {
        free(string_storage.items[--string_storage.count]);
    }
    free(string_storage.items);
    while (string_storage.list_count > 0) {
        List *list = string_storage.lists[--string_storage.list_count];
        free(list->items);
        free(list);
    }
    free(string_storage.lists);
    while (string_storage.dict_count > 0) {
        Dict *dict = string_storage.dicts[--string_storage.dict_count];
        if (dict != NULL) {
            for (size_t e = 0; e < dict->count; e++) {
                free(dict->entries[e].key);
            }
            free(dict->entries);
            free(dict);
        }
    }
    free(string_storage.dicts);
    free(parser.last_error_message);
    while (modules.count > 0) {
        Module *module = &modules.items[--modules.count];
        free(module->path);
        free(module->source);
    }
    free(modules.items);
    free(source);
    return result;
}

static int interpret_program(Parser *parser)
{
    advance_token(parser);

    if (!parser->failed && parser->current.kind != TOKEN_START) {
        report_error(parser, parser->current.line, parser->current.column,
                     MESSAGE_EXPECTED_PROGRAM_START);
    }
    if (!parser->failed) {
        advance_token(parser);
    }

    while (!parser->failed && parser->current.kind != TOKEN_END &&
           parser->current.kind != TOKEN_EOF) {
        parse_statement(parser, 1);
    }

    if (!parser->failed && parser->current.kind == TOKEN_EOF) {
        report_error(parser, parser->current.line, parser->current.column,
                     MESSAGE_EXPECTED_PROGRAM_END);
    }
    if (!parser->failed) {
        advance_token(parser);
        if (!parser->failed && parser->current.kind != TOKEN_EOF) {
            report_error(parser, parser->current.line, parser->current.column,
                         MESSAGE_EXPECTED_END_OF_FILE);
        }
    }
    return !parser->failed;
}

static int interpret(const char *source, const char *filename, Language language)
{
    Parser parser;
    Environment globals;
    StringStorage string_storage;
    FunctionTable function_table;
    ModuleStorage modules;

    memset(&globals, 0, sizeof(globals));
    memset(&string_storage, 0, sizeof(string_storage));
    memset(&function_table, 0, sizeof(function_table));
    memset(&modules, 0, sizeof(modules));
    memset(&parser, 0, sizeof(parser));
    parser.source = source;
    parser.offset = 0;
    parser.line = 1;
    parser.column = 1;
    parser.filename = filename;
    parser.language = language;
    parser.environment = &globals;
    parser.globals = &globals;
    parser.function_table = &function_table;
    parser.string_storage = &string_storage;
    parser.modules = &modules;
    parser.failed = 0;
    parser.in_function = 0;
    parser.returned = 0;
    parser.return_value = null_value();
    parser.current = make_token(TOKEN_EOF, 1, 1);
    interpret_program(&parser);
    while (globals.variable_count > 0) {
        free(globals.variables[--globals.variable_count].name);
    }
    free(globals.variables);
    while (function_table.count > 0) {
        Function *function = &function_table.items[--function_table.count];
        free(function->name);
        free(function->parameters);
    }
    free(function_table.items);
    while (string_storage.count > 0) {
        free(string_storage.items[--string_storage.count]);
    }
    free(string_storage.items);
    while (string_storage.list_count > 0) {
        List *list = string_storage.lists[--string_storage.list_count];
        free(list->items);
        free(list);
    }
    free(string_storage.lists);
    while (string_storage.dict_count > 0) {
        Dict *dict = string_storage.dicts[--string_storage.dict_count];
        if (dict != NULL) {
            for (size_t e = 0; e < dict->count; e++) {
                free(dict->entries[e].key);
            }
            free(dict->entries);
            free(dict);
        }
    }
    free(string_storage.dicts);
    free(parser.last_error_message);
    while (modules.count > 0) {
        Module *module = &modules.items[--modules.count];
        free(module->path);
        free(module->source);
    }
    free(modules.items);
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

static char *copy_string(const char *text)
{
    size_t length = strlen(text);
    char *copy;
    if (length == (size_t)-1) {
        return NULL;
    }
    copy = (char *)malloc(length + 1);
    if (copy != NULL) {
        memcpy(copy, text, length + 1);
    }
    return copy;
}

static char *resolve_import_path(Parser *parser, const char *import_path)
{
    size_t imported_length = strlen(import_path);
    size_t filename_length = strlen(parser->filename);
    size_t directory_length = 0;
    size_t index;
    size_t joined_length;
    char *joined;
    char *absolute;

#ifdef _WIN32
    int absolute_input = (imported_length > 0 &&
                          (import_path[0] == '/' || import_path[0] == '\\')) ||
                         (imported_length > 1 && import_path[1] == ':');
#else
    int absolute_input = imported_length > 0 && import_path[0] == '/';
#endif
    if (!absolute_input) {
        for (index = 0; index < filename_length; index++) {
            if (parser->filename[index] == '/' ||
                parser->filename[index] == '\\') {
                directory_length = index + 1;
            }
        }
    }
    if (imported_length > (size_t)-1 - directory_length - 2) {
        return NULL;
    }
    joined_length = directory_length + imported_length + 2;
    joined = (char *)malloc(joined_length);
    if (joined == NULL) {
        return NULL;
    }
    if (absolute_input) {
        memcpy(joined, import_path, imported_length + 1);
    } else if (directory_length > 0) {
        memcpy(joined, parser->filename, directory_length);
        memcpy(joined + directory_length, import_path, imported_length + 1);
    } else {
        memcpy(joined, import_path, imported_length + 1);
    }

#ifdef _WIN32
    {
        char full_path[32768];
        DWORD length = GetFullPathNameA(joined, (DWORD)sizeof(full_path),
                                        full_path, NULL);
        free(joined);
        if (length == 0 || length >= sizeof(full_path)) {
            return NULL;
        }
        absolute = copy_string(full_path);
    }
#else
    {
        char current_directory[32768];
        char combined[65536];
        const char *candidate = joined;
        size_t combined_length;
        int written;
        char *normalized;
        size_t previous_lengths[32768];
        size_t segment_count = 0;
        size_t output_length = 1;
        size_t cursor = 0;
        char *output;

        if (joined[0] != '/') {
            if (getcwd(current_directory, sizeof(current_directory)) == NULL) {
                free(joined);
                return NULL;
            }
            written = snprintf(combined, sizeof(combined), "%s/%s",
                               current_directory, joined);
            if (written < 0 || (size_t)written >= sizeof(combined)) {
                free(joined);
                return NULL;
            }
            candidate = combined;
        }
        combined_length = strlen(candidate);
        normalized = (char *)malloc(combined_length + 2);
        output = normalized;
        if (normalized == NULL) {
            free(joined);
            return NULL;
        }
        output[0] = '/';
        while (cursor < combined_length) {
            size_t start;
            size_t length;
            while (candidate[cursor] == '/') {
                cursor++;
            }
            start = cursor;
            while (cursor < combined_length && candidate[cursor] != '/') {
                cursor++;
            }
            length = cursor - start;
            if (length == 0 ||
                (length == 1 && candidate[start] == '.')) {
                continue;
            }
            if (length == 2 && candidate[start] == '.' &&
                candidate[start + 1] == '.') {
                if (segment_count > 0) {
                    output_length = previous_lengths[--segment_count];
                }
                continue;
            }
            if (segment_count >= sizeof(previous_lengths) /
                                sizeof(previous_lengths[0])) {
                free(normalized);
                free(joined);
                return NULL;
            }
            previous_lengths[segment_count] = output_length;
            if (output_length > 1) {
                output[output_length++] = '/';
            }
            memcpy(output + output_length, candidate + start, length);
            output_length += length;
            segment_count++;
        }
        output[output_length] = '\0';
        free(joined);
        absolute = normalized;
    }
#endif
    return absolute;
}

static int import_module(Parser *parser, Token keyword, Value path_value)
{
    size_t path_length = decoded_string_length(parser, path_value);
    char *path_text;
    char *resolved_path;
    size_t index;
    char *source;
    Module *modules;
    size_t capacity;
    size_t module_index;

    if (path_length == 0) {
        report_error(parser, keyword.line, keyword.column,
                     MESSAGE_EXPECTED_IMPORT_PATH);
        return 0;
    }
    if (path_length == (size_t)-1) {
        report_error(parser, keyword.line, keyword.column, MESSAGE_OUT_OF_MEMORY);
        return 0;
    }
    path_text = (char *)malloc(path_length + 1);
    if (path_text == NULL) {
        report_error(parser, keyword.line, keyword.column, MESSAGE_OUT_OF_MEMORY);
        return 0;
    }
    path_length = copy_value_string(parser, path_value, path_text);
    path_text[path_length] = '\0';
    resolved_path = resolve_import_path(parser, path_text);
    free(path_text);
    if (resolved_path == NULL) {
        report_error(parser, keyword.line, keyword.column,
                     MESSAGE_OUT_OF_MEMORY);
        return 0;
    }
    for (index = 0; index < parser->modules->count; index++) {
        Module *module = &parser->modules->items[index];
        if (strcmp(module->path, resolved_path) == 0) {
            free(resolved_path);
            if (module->loading) {
                report_error(parser, keyword.line, keyword.column,
                             MESSAGE_CIRCULAR_IMPORT);
                return 0;
            }
            return 1;
        }
    }
    source = read_source_file(resolved_path, parser->language);
    if (source == NULL) {
        free(resolved_path);
        parser->failed = 1;
        return 0;
    }
    if (parser->modules->count == parser->modules->capacity) {
        capacity = parser->modules->capacity == 0 ? 4 :
                   parser->modules->capacity * 2;
        if (capacity < parser->modules->capacity ||
            capacity > (size_t)-1 / sizeof(*parser->modules->items)) {
            free(source);
            free(resolved_path);
            report_error(parser, keyword.line, keyword.column,
                         MESSAGE_OUT_OF_MEMORY);
            return 0;
        }
        modules = (Module *)realloc(parser->modules->items,
                                    capacity * sizeof(*modules));
        if (modules == NULL) {
            free(source);
            free(resolved_path);
            report_error(parser, keyword.line, keyword.column,
                         MESSAGE_OUT_OF_MEMORY);
            return 0;
        }
        parser->modules->items = modules;
        parser->modules->capacity = capacity;
    }
    module_index = parser->modules->count++;
    parser->modules->items[module_index].path = resolved_path;
    parser->modules->items[module_index].source = source;
    parser->modules->items[module_index].loading = 1;

    {
        Parser imported;
        memset(&imported, 0, sizeof(imported));
        imported.source = source;
        imported.filename = resolved_path;
        imported.language = parser->language;
        imported.environment = parser->globals;
        imported.globals = parser->globals;
        imported.function_table = parser->function_table;
        imported.string_storage = parser->string_storage;
        imported.modules = parser->modules;
        imported.line = 1;
        imported.column = 1;
        imported.current = make_token(TOKEN_EOF, 1, 1);
        if (!interpret_program(&imported)) {
            parser->failed = 1;
        }
        free(imported.last_error_message);
    }
    parser->modules->items[module_index].loading = 0;
    return !parser->failed;
}

int main(int argc, char **argv)
{
    char *source;
    const char *filename = NULL;
    Language language = LANGUAGE_ENGLISH;
    int result;
    int repl = 0;

    if (argc >= 2) {
        if (strcmp(argv[1], "--repl") == 0) {
            repl = 1;
        } else if (strcmp(argv[1], "--language") == 0) {
            if (argc >= 3) {
                if (strcmp(argv[2], "en") == 0) {
                    language = LANGUAGE_ENGLISH;
                } else if (strcmp(argv[2], "gu") == 0) {
                    language = LANGUAGE_GUJARATI;
                } else {
                    fprintf(stderr, localized_message(LANGUAGE_ENGLISH, MESSAGE_USAGE),
                            argv[0]);
                    return EXIT_FAILURE;
                }
            }
            if (argc >= 4) {
                if (strcmp(argv[3], "--repl") == 0) {
                    repl = 1;
                } else {
                    filename = argv[3];
                    g_script_argc = argc - 4;
                    g_script_argv = argc > 4 ? &argv[4] : NULL;
                }
            } else {
                fprintf(stderr, localized_message(LANGUAGE_ENGLISH, MESSAGE_USAGE),
                        argv[0]);
                return EXIT_FAILURE;
            }
        } else {
            filename = argv[1];
            g_script_argc = argc - 2;
            g_script_argv = argc > 2 ? &argv[2] : NULL;
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
