#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
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
    VALUE_LIST
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
    MESSAGE_USAGE
} MessageId;

typedef struct Value Value;

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
};

typedef struct {
    char **items;
    size_t count;
    size_t capacity;
    List **lists;
    size_t list_count;
    size_t list_capacity;
} StringStorage;

typedef struct {
    char *name;
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
        {"import", TOKEN_IMPORT}
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

static int declare_variable(Parser *parser, Token name, Value value)
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
           token_matches(parser, name, "sima");
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

static void format_value_to_buffer(Parser *parser, Value value,
                                   StringBuffer *sb, List **ancestors,
                                   size_t depth)
{
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
        size_t index;
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
            if (!resolve_list_index(parser, value, index_value, bracket,
                                    &index)) {
                return number_value(0.0);
            }
            value = value.list->items[index];
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

static int parse_for_loop(Parser *parser, int execute)
{
    Token variable;
    Token in_keyword;
    Token body_open;
    Value first;
    Value last = null_value();
    List *list = NULL;
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
        if (first.kind != VALUE_LIST) {
            report_error(parser, in_keyword.line, in_keyword.column,
                         MESSAGE_EXPECTED_LIST_FOR_LOOP);
            return 0;
        }
        list = first.list;
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
    if (!parse_block(parser, 0)) {
        return 0;
    }
    if (!execute) {
        return 1;
    }

    if (is_range) {
        double current = first.number;
        while (!parser->failed && current < last.number) {
            Value loop_value = number_value(current);
            Variable *existing;
            parser->returned = 0;
            existing = find_variable(parser, variable);
            if (existing != NULL) {
                existing->value = loop_value;
            } else if (!declare_variable(parser, variable, loop_value)) {
                return 0;
            }
            parser->offset = body_open.source_offset;
            parser->line = body_open.line;
            parser->column = body_open.column;
            parser->current = make_token(TOKEN_EOF, parser->line,
                                         parser->column);
            advance_token(parser);
            if (!parse_block(parser, 1) || parser->returned) {
                break;
            }
            current += 1.0;
        }
    } else {
        for (index = 0; index < list->count && !parser->failed; index++) {
            Variable *existing;
            parser->returned = 0;
            existing = find_variable(parser, variable);
            if (existing != NULL) {
                existing->value = list->items[index];
            } else if (!declare_variable(parser, variable,
                                         list->items[index])) {
                return 0;
            }
            parser->offset = body_open.source_offset;
            parser->line = body_open.line;
            parser->column = body_open.column;
            parser->current = make_token(TOKEN_EOF, parser->line,
                                         parser->column);
            advance_token(parser);
            if (!parse_block(parser, 1) || parser->returned) {
                break;
            }
        }
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
    size_t list_index = 0;
    int indexed_assignment = 0;

    while (parser->current.kind == TOKEN_LEFT_BRACKET) {
        Token bracket = parser->current;
        Value index_value;
        advance_token(parser);
        index_value = parse_expression(parser, execute);
        if (parser->failed) {
            return 0;
        }
        if (parser->current.kind != TOKEN_RIGHT_BRACKET) {
            report_error(parser, parser->current.line, parser->current.column,
                         MESSAGE_EXPECTED_LIST_INDEX);
            return 0;
        }
        if (execute) {
            if (!indexed_assignment) {
                Variable *variable = find_variable(parser, name);
                if (variable == NULL) {
                    report_error(parser, name.line, name.column,
                                 MESSAGE_UNDEFINED_VARIABLE);
                    return 0;
                }
                indexed_value = variable->value;
            }
            if (!resolve_list_index(parser, indexed_value, index_value, bracket,
                                    &list_index)) {
                return 0;
            }
            target_list = indexed_value.list;
            indexed_value = target_list->items[list_index];
        }
        indexed_assignment = 1;
        advance_token(parser);
    }

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
        if (indexed_assignment) {
            target_list->items[list_index] = value;
        } else if (find_variable(parser, name) != NULL) {
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
