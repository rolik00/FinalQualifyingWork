```abnf
; --- Базовые символы (Core) ---
ALPHA          = %x41-5A / %x61-7A
DIGIT          = %x30-39
HEXDIG         = DIGIT / "A" / "B" / "C" / "D" / "E" / "F" / "a" / "b" / "c" / "d" / "e" / "f"
DQUOTE         = %x22
WSP            = %x20 / %x09
CRLF           = %x0A / %x0D

; --- Идентификаторы и литералы ---
IDENTIFIER     = (ALPHA / "_") *(ALPHA / DIGIT / "_")
INTEGER        = 1*DIGIT
HEX_INTEGER    = "0x" 1*HEXDIG
UUID_REP       = 8HEXDIG "-" 4HEXDIG "-" 4HEXDIG "-" 4HEXDIG "-" 12HEXDIG
STRING_LITERAL = DQUOTE *(%x20-21 / %x23-5B / %x5D-7E / "\" DQUOTE / "\\") DQUOTE

; --- Ключевые слова (Keywords) ---
KW_INTERFACE   = "interface"
KW_LIBRARY     = "library"
KW_COCLASS     = "coclass"
KW_IMPORT      = "import"
KW_UUID        = "uuid"
KW_VERSION     = "version"
KW_PTR_DEFAULT = "pointer_default"
KW_TYPEDEF     = "typedef"
KW_STRUCT      = "struct"
KW_ENUM        = "enum"
KW_CONST       = "const"
KW_IN          = "in"
KW_OUT         = "out"
KW_RETVAL      = "retval"
KW_OBJECT      = "object"
KW_LOCAL       = "local"
KW_VOID        = "void"

; --- Операторы и пунктуация ---
LBRACKET       = "["
RBRACKET       = "]"
LBRACE         = "{"
RBRACE         = "}"
LPAREN         = "("
RPAREN         = ")"
SEMI           = ";"
COMMA          = ","
COLON          = ":"
ASTERISK       = "*"
EQUALS         = "="

; --- Комментарии (Критично для вашего генератора) ---
; Чтобы комментарии сохранялись, они должны быть частью дерева (AST)
COMMENT        = LINE_COMMENT / BLOCK_COMMENT
LINE_COMMENT   = "//" *(%x20-7E / %x09) (CRLF)
BLOCK_COMMENT  = "/*" *(%x00-FF) "*/"
WS             = 1*(WSP / CRLF)

; =========================================================
; --- Синтаксис (Syntax) ---
; =========================================================

idl_file       = *(definition / WS)

definition     = import_stmt / interface_def / library_def / typedef_def / struct_def / enum_def / COMMENT

; --- Импорт ---
import_stmt    = KW_IMPORT STRING_LITERAL SEMI

; --- Атрибуты (то, что в квадратных скобках) ---
attributes     = LBRACKET attribute_list RBRACKET
attribute_list = attribute *(COMMA [WS] attribute)
attribute      = (KW_UUID LPAREN UUID_REP RPAREN) / 
                 (KW_VERSION LPAREN (INTEGER / "float") RPAREN) /
                 (KW_PTR_DEFAULT LPAREN IDENTIFIER RPAREN) /
                 KW_IN / KW_OUT / KW_RETVAL / KW_OBJECT / KW_LOCAL / IDENTIFIER

; --- Интерфейс ---
interface_def  = [attributes] [WS] KW_INTERFACE IDENTIFIER [inheritance] [WS] LBRACE interface_body RBRACE [SEMI]
inheritance    = [WS] COLON [WS] IDENTIFIER
interface_body = *(method_def / COMMENT / WS)

; --- Метод (Функция) ---
; Учитываем комментарии ДО и ПОСЛЕ метода
method_def     = [attributes] [WS] type_spec [WS] IDENTIFIER [WS] LPAREN param_list RPAREN [WS] SEMI [WS] [COMMENT]

; --- Параметры ---
param_list     = [parameter *( [WS] COMMA [WS] parameter )]
parameter      = [COMMENT] [WS] [attributes] [WS] type_spec [WS] [IDENTIFIER] [WS] [COMMENT]

; --- Типы данных ---
type_spec      = [KW_STRUCT / KW_ENUM] [WS] IDENTIFIER *( [WS] ASTERISK )

; --- Структуры и Перечисления ---
struct_def     = KW_STRUCT IDENTIFIER LBRACE *(struct_member / WS / COMMENT) RBRACE SEMI
struct_member  = [COMMENT] [WS] type_spec [WS] IDENTIFIER [WS] SEMI [WS] [COMMENT]

enum_def       = KW_ENUM IDENTIFIER LBRACE enum_list RBRACE SEMI
enum_list      = enum_member *( [WS] COMMA [WS] enum_member )
enum_member    = [COMMENT] [WS] IDENTIFIER [ [WS] EQUALS [WS] (INTEGER / HEX_INTEGER) ] [WS] [COMMENT]

typedef_def    = KW_TYPEDEF [attributes] [WS] type_spec [WS] IDENTIFIER SEMI
library_def    = [attributes] [WS] KW_LIBRARY IDENTIFIER [WS] LBRACE *(definition / WS) RBRACE [SEMI]
```