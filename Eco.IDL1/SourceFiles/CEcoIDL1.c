/*
 * <character encoding>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </character encoding>
 *
 * <summary>
 *   CEcoIDL1_40BB8A88
 * </summary>
 *
 * <description>
 *   This source code describes the implementation of the interfaces for CEcoIDL1_40BB8A88
 * </description>
 *
 * <author>
 *   Copyright (c) 2026 Vladimir Bashev. All rights reserved.
 * </author>
 *
 */


#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "CEcoIDL1.h"
#include "IdEcoList1.h"
#include "IdEcoLR1.h"
#include "IdEcoIDL1C.h"
#include "IdEcoIDL1CPP.h"
#include "IdEcoIDL1Java.h"
#include "IdEcoIDL1Python.h"

typedef enum IDL_LEXICAL_TOKENS_e {
    TOKEN_NONE = 0,
    
    /* Базовые категории (Core Rules) */
    TOKEN_ALPHA = 1,
    TOKEN_DIGIT = 2,
    TOKEN_HEXDIG = 3,
    TOKEN_DQUOTE = 4,
    TOKEN_WSP = 5,
    TOKEN_CRLF = 6,
    
    /* Ключевые слова (Keywords) */
    TOKEN_KW_INTERFACE = 20,
    TOKEN_KW_UUID      = 21,
    TOKEN_KW_VERSION   = 22,
    TOKEN_KW_TYPEDEF   = 23,
    TOKEN_KW_STRUCT    = 24,
    TOKEN_KW_IN        = 25,
    TOKEN_KW_OUT       = 26,
    TOKEN_KW_VOID      = 27,
    TOKEN_KW_IMPORT    = 28,

    /* Сложные типы данных */
    TOKEN_IDENTIFIER   = 50,
    TOKEN_INTEGER      = 51,
    TOKEN_STRING       = 52,
    TOKEN_UUID_LITERAL = 53, /* 8-4-4-4-12 */

    /* Пунктуация */
    TOKEN_LBRACKET     = 70, /* [ */
    TOKEN_RBRACKET     = 71, /* ] */
    TOKEN_LBRACE       = 72, /* { */
    TOKEN_RBRACE       = 73, /* } */
    TOKEN_LPAREN       = 74, /* ( */
    TOKEN_RPAREN       = 75, /* ) */
    TOKEN_SEMI         = 76, /* ; */
    TOKEN_COMMA        = 77, /* , */
    TOKEN_COLON        = 78, /* : */
    TOKEN_STAR         = 79,
    TOKEN_POINT        = 80,

    /* Служебные */
    TOKEN_WS           = 100,
    TOKEN_COMMENT      = 101,
    TOKEN_EOF          = 0xFFFFFFFE,
    TOKEN_ERROR        = 0xFFFFFFFF
} IDL_LEXICAL_TOKENS_e;

/*
 *
 * <summary>
 *   SetDefaultLexer Function
 * </summary>
 *
 * <description>
 *   
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1_40BB8A88_SetDefaultLexer(CEcoIDL1_40BB8A88* pCMe) {
    int16_t result = -1;
    IEcoLexicalData1* pIData = 0;
    IEcoLexicalAnalyzer1Scanner* pScanner = 0;
    IEcoLexicalAnalyzer1Token* pToken = 0;

    /*
        ABNF IDL

        ; --- Базовые символы (Core) ---
        ALPHA          = %x41-5A / %x61-7A
        DIGIT          = %x30-39
        HEXDIG         = DIGIT / "A" / "B" / "C" / "D" / "E" / "F" / "a" / "b" / "c" / "d" / "e" / "f"
        DQUOTE         = %x22

        ; --- Идентификаторы и литералы ---
        IDENTIFIER     = (ALPHA / "_") *(ALPHA / DIGIT / "_")
        INTEGER        = 1*DIGIT
        HEX_INTEGER    = "0x" 1*HEXDIG
        UUID_REP       = 8HEXDIG "-" 4HEXDIG "-" 4HEXDIG "-" 4HEXDIG "-" 12HEXDIG
        STRING_LITERAL = DQUOTE *(%x20-21 / %x23-5B / %x5D-7E / "\" DQUOTE / "\\") DQUOTE

        ; --- Ключевые слова (Microsoft & OMG) ---
        KW_INTERFACE   = "interface"
        KW_UUID        = "uuid"
        KW_VERSION     = "version"
        KW_ENDPOINT    = "endpoint"
        KW_EXCEPTIONS  = "exceptions"
        KW_LOCAL       = "local"
        KW_PTR_DEFAULT = "pointer_default"
        KW_TYPEDEF     = "typedef"
        KW_STRUCT      = "struct"
        KW_CONST       = "const"
        KW_IN          = "in"
        KW_OUT         = "out"
        KW_RET_VOID    = "void"

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

        ; --- Игнорируемое ---
        WS             = 1*(%x20 / %x09 / %x0A / %x0D)
        COMMENT        = 
        LINE_COMMENT   = "//" *(%x20-7E) (%x0A / %x0D)
    */


    /* Создаем объект правил через основной интерфейс */
    result = pCMe->m_pILA->pVTbl->CreateRulesRE(pCMe->m_pILA, &pCMe->m_pILexicalRules);

    if (result == 0 && pCMe->m_pILexicalRules != 0) {
        pCMe->m_pILexicalRules->pVTbl->AddRuleRE(pCMe->m_pILexicalRules, 0, "\\[", TOKEN_LBRACKET);
        pCMe->m_pILexicalRules->pVTbl->AddRuleRE(pCMe->m_pILexicalRules, 0, "\\]", TOKEN_RBRACKET);
        pCMe->m_pILexicalRules->pVTbl->AddRuleRE(pCMe->m_pILexicalRules, 0, "\\{", TOKEN_LBRACE);
        pCMe->m_pILexicalRules->pVTbl->AddRuleRE(pCMe->m_pILexicalRules, 0, "\\}", TOKEN_RBRACE);
        pCMe->m_pILexicalRules->pVTbl->AddRuleRE(pCMe->m_pILexicalRules, 0, "\\(", TOKEN_LPAREN);
        pCMe->m_pILexicalRules->pVTbl->AddRuleRE(pCMe->m_pILexicalRules, 0, "\\)", TOKEN_RPAREN);
        pCMe->m_pILexicalRules->pVTbl->AddRuleRE(pCMe->m_pILexicalRules, 0, ";", TOKEN_SEMI);
        pCMe->m_pILexicalRules->pVTbl->AddRuleRE(pCMe->m_pILexicalRules, 0, ",", TOKEN_COMMA);
        pCMe->m_pILexicalRules->pVTbl->AddRuleRE(pCMe->m_pILexicalRules, 0, ":", TOKEN_COLON);
        pCMe->m_pILexicalRules->pVTbl->AddRuleRE(pCMe->m_pILexicalRules, 0, "\\.", TOKEN_POINT);
        pCMe->m_pILexicalRules->pVTbl->AddRuleRE(pCMe->m_pILexicalRules, 0, "\\*", TOKEN_STAR);
        pCMe->m_pILexicalRules->pVTbl->AddRuleRE(pCMe->m_pILexicalRules, 0, "interface", TOKEN_KW_INTERFACE);
        pCMe->m_pILexicalRules->pVTbl->AddRuleRE(pCMe->m_pILexicalRules, 0, "uuid", TOKEN_KW_UUID);
        pCMe->m_pILexicalRules->pVTbl->AddRuleRE(pCMe->m_pILexicalRules, 0, "import", TOKEN_KW_IMPORT);
        pCMe->m_pILexicalRules->pVTbl->AddRuleRE(pCMe->m_pILexicalRules, 0, "in", TOKEN_KW_IN);
        pCMe->m_pILexicalRules->pVTbl->AddRuleRE(pCMe->m_pILexicalRules, 0, "out", TOKEN_KW_OUT);
        pCMe->m_pILexicalRules->pVTbl->AddRuleRE(pCMe->m_pILexicalRules, 0, "void", TOKEN_KW_VOID);
        pCMe->m_pILexicalRules->pVTbl->AddRuleRE(pCMe->m_pILexicalRules, 0, "\"([A-Z]|[a-z]|[0-9]|_|\\[|\\]| |\\{|\\}|\\(|\\)|;|:|,|\\.|\\*)*\"", TOKEN_STRING);
        pCMe->m_pILexicalRules->pVTbl->AddRuleRE(pCMe->m_pILexicalRules, 0, "[0-9]+", TOKEN_INTEGER);
        pCMe->m_pILexicalRules->pVTbl->AddRuleRE(pCMe->m_pILexicalRules, 0, "([A-Z]|[a-z]|_)([A-Z]|[a-z]|[0-9]|_)*", TOKEN_IDENTIFIER);
        pCMe->m_pILexicalRules->pVTbl->AddRuleRE(pCMe->m_pILexicalRules, 0, "([0-9]|[a-f]|[A-F]){8}-([0-9]|[a-f]|[A-F]){4}-([0-9]|[a-f]|[A-F]){4}-([0-9]|[a-f]|[A-F]){4}-([0-9]|[a-f]|[A-F]){12}", TOKEN_UUID_LITERAL);
        pCMe->m_pILexicalRules->pVTbl->AddRuleRE(pCMe->m_pILexicalRules, 0, "( |\t|\r|\n)+", TOKEN_WS);
		pCMe->m_pILexicalRules->pVTbl->AddRuleRE(pCMe->m_pILexicalRules, 0, "/\\*.*\\*/", TOKEN_COMMENT);

        pCMe->m_pILexicalRules->pVTbl->SetPriority(pCMe->m_pILexicalRules, TOKEN_STRING, 5);
        pCMe->m_pILexicalRules->pVTbl->SetPriority(pCMe->m_pILexicalRules, TOKEN_UUID_LITERAL, 6);
        pCMe->m_pILexicalRules->pVTbl->SetPriority(pCMe->m_pILexicalRules, TOKEN_KW_INTERFACE, 10);
        pCMe->m_pILexicalRules->pVTbl->SetPriority(pCMe->m_pILexicalRules, TOKEN_KW_UUID, 10);
        pCMe->m_pILexicalRules->pVTbl->SetPriority(pCMe->m_pILexicalRules, TOKEN_KW_IMPORT, 10);
        pCMe->m_pILexicalRules->pVTbl->SetPriority(pCMe->m_pILexicalRules, TOKEN_KW_IN, 10);
        pCMe->m_pILexicalRules->pVTbl->SetPriority(pCMe->m_pILexicalRules, TOKEN_KW_OUT, 10);
        pCMe->m_pILexicalRules->pVTbl->SetPriority(pCMe->m_pILexicalRules, TOKEN_KW_VOID, 10);
        pCMe->m_pILexicalRules->pVTbl->SetPriority(pCMe->m_pILexicalRules, TOKEN_LBRACKET, 15);
        pCMe->m_pILexicalRules->pVTbl->SetPriority(pCMe->m_pILexicalRules, TOKEN_RBRACKET, 15);
        pCMe->m_pILexicalRules->pVTbl->SetPriority(pCMe->m_pILexicalRules, TOKEN_LBRACE, 15);
        pCMe->m_pILexicalRules->pVTbl->SetPriority(pCMe->m_pILexicalRules, TOKEN_RBRACE, 15);
        pCMe->m_pILexicalRules->pVTbl->SetPriority(pCMe->m_pILexicalRules, TOKEN_LPAREN, 15);
        pCMe->m_pILexicalRules->pVTbl->SetPriority(pCMe->m_pILexicalRules, TOKEN_RPAREN, 15);
        pCMe->m_pILexicalRules->pVTbl->SetPriority(pCMe->m_pILexicalRules, TOKEN_SEMI, 15);
        pCMe->m_pILexicalRules->pVTbl->SetPriority(pCMe->m_pILexicalRules, TOKEN_COMMA, 15);
        pCMe->m_pILexicalRules->pVTbl->SetPriority(pCMe->m_pILexicalRules, TOKEN_COLON, 15);
        pCMe->m_pILexicalRules->pVTbl->SetPriority(pCMe->m_pILexicalRules, TOKEN_STAR, 15);
        pCMe->m_pILexicalRules->pVTbl->SetPriority(pCMe->m_pILexicalRules, TOKEN_POINT, 15);
        pCMe->m_pILexicalRules->pVTbl->SetPriority(pCMe->m_pILexicalRules, TOKEN_INTEGER, 25);
        pCMe->m_pILexicalRules->pVTbl->SetPriority(pCMe->m_pILexicalRules, TOKEN_IDENTIFIER, 25); 
        pCMe->m_pILexicalRules->pVTbl->SetPriority(pCMe->m_pILexicalRules, TOKEN_WS, 100); 
        pCMe->m_pILexicalRules->pVTbl->SetPriority(pCMe->m_pILexicalRules, TOKEN_COMMENT, 100); 
        pCMe->m_pILexicalRules->pVTbl->SetChannel(pCMe->m_pILexicalRules, TOKEN_WS, 1);
        pCMe->m_pILexicalRules->pVTbl->SetChannel(pCMe->m_pILexicalRules, TOKEN_COMMENT, 1);

    }

    return result;
}

/*
 *
 * <summary>
 *   SetDefaultSyntax Function
 * </summary>
 *
 * <description>
 *   
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1_40BB8A88_SetDefaultSyntax(CEcoIDL1_40BB8A88* pCMe) {
    int16_t result = -1;
    /* Beginning */
    IEcoBNF1* pIBNF = 0;
    IEcoBNF1Rule* pIRule = 0;
    IEcoBNF1Rule* pIGroup = 0;
    IEcoBNF1Rule* pIOption = 0;
    IEcoBNF1Element* pIElement = 0;
    uint32_t indexSet = 0;

    /*
        ABNF IDL

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
    */

    /* Получение интерфейса по работе с грамматикой синтаксического разбора Lua */
    result = pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoBNF1, 0, &IID_IEcoBNF1, (void**) &pIBNF);
    /* Проверка */
    if (result != 0 || pIBNF == 0) {
        return result;
    }

    /* Beginning */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "c0-begin-state");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "translation-unit");

    /* (6.3.1) primary-expression:
                        identifier
                        constant
                        string-literal
                        ( expression )
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "primary-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "identifier");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "constant");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "string-literal");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "(");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ")");

    /* (6.3.2) postfix-expression:
                        primary-expression
                        postfix-expression [ expression ]
                        postfix-expression ( argument-expression-list opt )
                        postfix-expression . identifier
                        postfix-expression -> identifier
                        postfix-expression ++
                        postfix-expression --
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "postfix-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "primary-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "postfix-expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "[");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "]");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "postfix-expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "(");
    pIOption = pIRule->pVTbl->AddOptionalSequence(pIRule, &indexSet, ECO_BNF_1_EF_NONE, 0, 0);
    pIElement = pIOption->pVTbl->AddConcatenation(pIOption, indexSet, ECO_BNF_1_EF_NONE, "argument-expression-list");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ")");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "postfix-expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ".");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "identifier");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "postfix-expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "->");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "identifier");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "postfix-expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "++");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "postfix-expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "--");

    /* (6.3.2) argument-expression-list:
                        assignment-expression
                        argument-expression-list , assignment-expression
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "argument-expression-list");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "assignment-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "argument-expression-list");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ",");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "assignment-expression");

    /* (6.3.3) unary-expression:
                        postfix-expression
                        ++ unary-expression
                        -- unary-expression
                        unary-operator cast-expression
                        sizeof unary-expression
                        sizeof ( type-name )
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "unary-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "postfix-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "++");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "unary-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "--");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "unary-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "unary-operator");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "cast-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "sizeof");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "unary-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "sizeof");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "(");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "type-name");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ")");

    /* (6.3.3) unary-operator: one of
                        & * + - ~ !
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "unary-operator");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "&");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "*");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "+");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "-");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "~");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "!");

    /* (6.3.4) cast-expression:
                    unary-expression
                    ( type-name ) cast-expression
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "cast-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "unary-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "(");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "type-name");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ")");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "cast-expression");

    /* (6.3.5) multiplicative-expression:
                    cast-expression
                    multiplicative-expression * cast-expression
                    multiplicative-expression / cast-expression
                    multiplicative-expression % cast-expression
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "multiplicative-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "cast-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "multiplicative-expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "*");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "cast-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "multiplicative-expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "/");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "cast-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "multiplicative-expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "%");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "cast-expression");

    /* (6.3.6) additive-expression:
                    multiplicative-expression
                    additive-expression + multiplicative-expression
                    additive-expression - multiplicative-expression
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "additive-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "multiplicative-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "additive-expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "+");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "multiplicative-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "additive-expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "-");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "multiplicative-expression");

    /* (6.3.7) shift-expression:
                    additive-expression
                    shift-expression << additive-expression
                    shift-expression >> additive-expression
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "shift-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "additive-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "shift-expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "<<");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "additive-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "shift-expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ">>");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "additive-expression");

    /* (6.3.8) relational-expression:
                    shift-expression
                    relational-expression < shift-expression
                    relational-expression > shift-expression
                    relational-expression <= shift-expression
                    relational-expression >= shift-expression
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "relational-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "shift-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "relational-expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "<");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "shift-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "relational-expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ">");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "shift-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "relational-expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "<=");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "shift-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "relational-expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ">=");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "shift-expression");

    /* (6.3.9) equality-expression:
                    relational-expression
                    equality-expression == relational-expression
                    equality-expression != relational-expression
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "equality-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "relational-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "equality-expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "==");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "relational-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "equality-expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "!=");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "relational-expression");

    /* (6.3.10) AND-expression:
                    equality-expression
                    AND-expression & equality-expression
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "AND-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "equality-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "AND-expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "&");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "equality-expression");

    /* (6.3.11) exclusive-OR-expression:
                    AND-expression
                    exclusive-OR-expression ^ AND-expression
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "exclusive-OR-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "AND-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "exclusive-OR-expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "^");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "AND-expression");

    /* (6.3.12) inclusive-OR-expression:
                    exclusive-OR-expression
                    inclusive-OR-expression | exclusive-OR-expression
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "inclusive-OR-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "exclusive-OR-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "inclusive-OR-expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "|");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "exclusive-OR-expression");

    /* (6.3.13) logical-AND-expression:
                    inclusive-OR-expression
                    logical-AND-expression && inclusive-OR-expression
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "logical-AND-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "inclusive-OR-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "logical-AND-expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "&&");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "inclusive-OR-expression");

    /* (6.3.14) logical-OR-expression:
                    logical-AND-expression
                    logical-OR-expression || logical-AND-expression
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "logical-OR-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "logical-AND-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "logical-OR-expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "||");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "logical-AND-expression");

    /* (6.3.15) conditional-expression:
                    logical-OR-expression
                    logical-OR-expression ? expression : conditional-expression
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "conditional-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "logical-OR-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "logical-OR-expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "?");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ":");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "conditional-expression");

    /* (6.3.16) assignment-expression:
                    conditional-expression
                    unary-expression assignment-operator assignment-expression
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "assignment-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "conditional-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "unary-expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "assignment-operator");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "assignment-expression");

    /* (6.3.16) assignment-operator: one of
                    = *= /= %= += -= <<= >>= &= ^= |=
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "assignment-operator");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "=");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "*=");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "/=");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "%=");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "+=");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "-=");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "<<=");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, ">>=");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "&=");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "^=");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "|=");

    /* (6.3.17) expression:
                    assignment-expression
                    expression , assignment-expression
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "assignment-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ",");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "assignment-expression");

    /* (6.4) constant-expression:
                    conditional-expression
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "constant-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "conditional-expression");

    /* B.2.2 Declarations */

    /* (6.5) declaration:
                declaration-specifiers init-declarator-list opt ;
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "declaration");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "declaration-specifier");  //declaration-specifiers
    pIOption = pIRule->pVTbl->AddOptionalSequence(pIRule, &indexSet, ECO_BNF_1_EF_NONE, 0, 0);
    pIElement = pIOption->pVTbl->AddConcatenation(pIOption, indexSet, ECO_BNF_1_EF_NONE, "init-declarator-list");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ";");

    /* Rule for mapping declaration-specifier */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "declaration-specifier");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "declaration-specifiers");

    /* (6.5) declaration:
                declaration-specifiers:
                storage-class-specifier declaration-specifiers opt
                type-specifier declaration-specifiers opt
                type-qualifier declaration-specifiers opt
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "declaration-specifiers");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "storage-class-specifier");
    pIOption = pIRule->pVTbl->AddOptionalSequence(pIRule, &indexSet, ECO_BNF_1_EF_NONE, 0, 0);
    pIElement = pIOption->pVTbl->AddConcatenation(pIOption, indexSet, ECO_BNF_1_EF_NONE, "declaration-specifiers");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "type-specifier");
    pIOption = pIRule->pVTbl->AddOptionalSequence(pIRule, &indexSet, ECO_BNF_1_EF_NONE, 0, 0);
    pIElement = pIOption->pVTbl->AddConcatenation(pIOption, indexSet, ECO_BNF_1_EF_NONE, "declaration-specifiers");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "type-qualifier");
    pIOption = pIRule->pVTbl->AddOptionalSequence(pIRule, &indexSet, ECO_BNF_1_EF_NONE, 0, 0);
    pIElement = pIOption->pVTbl->AddConcatenation(pIOption, indexSet, ECO_BNF_1_EF_NONE, "declaration-specifiers");

    /* (6.5) init-declarator-list:
                init-declarator
                init-declarator-list , init-declarator
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "init-declarator-list");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "init-declarator");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "init-declarator-list");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ",");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "init-declarator");

    /* (6.5) init-declarator:
                declarator
                declarator = initializer
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "init-declarator");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "declarator");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "declarator");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "=");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "initializer");

    /* (6.5.1) storage-class-specifier:
                typedef
                extern
                static
                auto
                register
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "storage-class-specifier");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "typedef");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "extern");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "static");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "auto");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "register");

    /* (6.5.2) type-specifier:
                void
                char
                short
                int
                long
                float
                double
                signed
                unsigned
                struct-or-union-specifier
                enum-specifier
                typedef-name
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "type-specifier");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "void");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "char");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "short");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "int");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "long");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "float");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "double");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "signed");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "unsigned");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "struct-or-union-specifier");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "enum-specifier");
    //pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "typedef-name");

    /* (6.5.2.1) struct-or-union-specifier:
                struct-or-union identifieropt { struct-declaration-list }
                struct-or-union identifier
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "struct-or-union-specifier");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "struct-or-union");
    pIOption = pIRule->pVTbl->AddOptionalSequence(pIRule, &indexSet, ECO_BNF_1_EF_NONE, 0, 0);
    pIElement = pIOption->pVTbl->AddConcatenation(pIOption, indexSet, ECO_BNF_1_EF_NONE, "identifier");
    pIOption = pIRule->pVTbl->AddOptionalSequence(pIRule, &indexSet, ECO_BNF_1_EF_NONE, 0, 0);
    pIElement = pIOption->pVTbl->AddConcatenation(pIOption, indexSet, ECO_BNF_1_EF_NONE, ":");
    pIElement = pIOption->pVTbl->AddConcatenation(pIOption, indexSet, ECO_BNF_1_EF_NONE, "identifier");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "{");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "struct-declaration-list");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "}");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "struct-or-union");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "identifier");

    /* (6.5.2.1) struct-or-union:
                    struct
                    union
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "struct-or-union");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "interface");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "union");

    /* (6.5.2.1) struct-declaration-list:
                    struct-declaration
                    struct-declaration-list struct-declaration
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "struct-declaration-list");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "struct-declaration");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "struct-declaration-list");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "struct-declaration");

    /* Rule for mapping specifier-qualifier */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "specifier-qualifier");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "specifier-qualifier-list");

    /* (6.5.2.1) struct-declaration:
                    specifier-qualifier-list struct-declarator-list ;
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "struct-declaration");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "specifier-qualifier");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "struct-declarator-list");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ";");

    /* (6.5.2.1) specifier-qualifier-list:
                    type-specifier specifier-qualifier-list opt
                    type-qualifier specifier-qualifier-list opt
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "specifier-qualifier-list");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "type-specifier");
    pIOption = pIRule->pVTbl->AddOptionalSequence(pIRule, &indexSet, ECO_BNF_1_EF_NONE,  0, 0);
    pIElement = pIOption->pVTbl->AddConcatenation(pIOption, indexSet, ECO_BNF_1_EF_NONE, "specifier-qualifier-list");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "type-qualifier");
    pIOption = pIRule->pVTbl->AddOptionalSequence(pIRule, &indexSet, ECO_BNF_1_EF_NONE, 0, 0);
    pIElement = pIOption->pVTbl->AddConcatenation(pIOption, indexSet, ECO_BNF_1_EF_NONE, "specifier-qualifier-list");

    /* (6.5.2.1) struct-declarator-list:
                    struct-declarator
                    struct-declarator-list , struct-declarator
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "struct-declarator-list");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "struct-declarator");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "struct-declarator-list");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ",");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "struct-declarator");

    /* (6.5.2.1) struct-declarator:
                    declarator
                    declarator opt : constant-expression
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "struct-declarator");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "declarator");
    pIOption = pIRule->pVTbl->AddOptionalSequence(pIRule, &indexSet, ECO_BNF_1_EF_ALTERNATION, 0, 0);
    pIElement = pIOption->pVTbl->AddAlternative(pIOption, &indexSet, ECO_BNF_1_EF_NONE, "declarator");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ":");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "constant-expression");

    /* (6.5.2.2) enum-specifier:
                    enum identifier opt { enumerator-list }
                    enum identifier
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "enum-specifier");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "enum");
    pIOption = pIRule->pVTbl->AddOptionalSequence(pIRule, &indexSet, ECO_BNF_1_EF_NONE, 0, 0);
    pIElement = pIOption->pVTbl->AddConcatenation(pIOption, indexSet, ECO_BNF_1_EF_NONE, "identifier");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "{");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "enumerator-list");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "}");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "enum");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "identifier");

    /* (6.5.2.2) enumerator-list:
                    enumerator
                    enumerator-list , enumerator
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "enumerator-list");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "enumerator");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "enumerator-list");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ",");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "enumerator");

    /* (6.5.2.2) enumerator:
                    enumeration-constant
                    enumeration-constant = constant-expression
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "enumerator");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "enumeration-constant");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "enumeration-constant");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "=");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "constant-expression");

    /* Add rule from lexical grammar */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "enumeration-constant");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "identifier");

    /* (6.5.3) type-qualifier:
                    const
                    volatile
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "type-qualifier");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "const");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "volatile");

    /* (6.5.4) declarator:
                    pointer opt direct-declarator
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "declarator");
    indexSet = 0;
    pIOption = pIRule->pVTbl->AddOptionalSequence(pIRule, &indexSet, ECO_BNF_1_EF_ALTERNATION, 0, 0);
    pIElement = pIOption->pVTbl->AddAlternative(pIOption, &indexSet, ECO_BNF_1_EF_NONE, "pointer");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "direct-declarator");

    /* (6.5.4) direct-declarator:
                    identifier
                    ( declarator )
                    direct-declarator [ constant-expression opt ]
                    direct-declarator ( parameter-type-list )
                    direct-declarator ( identifier-list opt )
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "direct-declarator");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "identifier");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "(");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "declarator");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ")");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "direct-declarator");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "[");
    pIOption = pIRule->pVTbl->AddOptionalSequence(pIRule, &indexSet, ECO_BNF_1_EF_NONE, 0, 0);
    pIElement = pIOption->pVTbl->AddConcatenation(pIOption, indexSet, ECO_BNF_1_EF_NONE, "constant-expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "]");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "direct-declarator");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "(");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "parameter-type-list");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ")");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "direct-declarator");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "(");
    pIOption = pIRule->pVTbl->AddOptionalSequence(pIRule, &indexSet, ECO_BNF_1_EF_NONE, 0, 0);
    pIElement = pIOption->pVTbl->AddConcatenation(pIOption, indexSet, ECO_BNF_1_EF_NONE, "identifier-list");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ")");

    /* (6.5.4) pointer:
                    * type-qualifier-listopt
                    * type-qualifier-listopt pointer
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "pointer");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "*");
    pIOption = pIRule->pVTbl->AddOptionalSequence(pIRule, &indexSet, ECO_BNF_1_EF_NONE, 0, 0);
    pIElement = pIOption->pVTbl->AddConcatenation(pIOption, indexSet, ECO_BNF_1_EF_NONE, "type-qualifier-list");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "*");
    pIOption = pIRule->pVTbl->AddOptionalSequence(pIRule, &indexSet, ECO_BNF_1_EF_NONE,  0, 0);
    pIElement = pIOption->pVTbl->AddConcatenation(pIOption, indexSet, ECO_BNF_1_EF_NONE, "type-qualifier-list");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "pointer");

    /* (6.5.4) type-qualifier-list:
                    type-qualifier
                    type-qualifier-list type-qualifier
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "type-qualifier-list");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "type-qualifier");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "type-qualifier-list");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "type-qualifier");

    /* (6.5.4) parameter-type-list:
                    parameter-list
                    parameter-list , ...
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "parameter-type-list");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "parameter-list");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "parameter-list");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ",");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "...");

    /* (6.5.4) parameter-list:
                    parameter-declaration
                    parameter-list , parameter-declaration
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "parameter-list");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "parameter-declaration");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "parameter-list");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ",");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "parameter-declaration");

    /* (6.5.4) parameter-declaration:
                    declaration-specifiers declarator
                    declaration-specifiers abstract-declarator opt
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "parameter-declaration");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "declaration-specifier");  // declaration-specifiers
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "declarator");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "declaration-specifier");  // declaration-specifiers
    pIOption = pIRule->pVTbl->AddOptionalSequence(pIRule, &indexSet, ECO_BNF_1_EF_NONE, 0, 0);
    pIElement = pIOption->pVTbl->AddConcatenation(pIOption, indexSet, ECO_BNF_1_EF_NONE, "abstract-declarator");

    /* (6.5.4) identifier-list:
                    identifier
                    identifier-list , identifier
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "identifier-list");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "identifier");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "identifier-list");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ",");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "identifier");

    /* (6.5.5) type-name:
                    specifier-qualifier-list abstract-declarator opt
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "type-name");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "specifier-qualifier");
    pIOption = pIRule->pVTbl->AddOptionalSequence(pIRule, &indexSet, ECO_BNF_1_EF_NONE, 0, 0);
    pIElement = pIOption->pVTbl->AddConcatenation(pIOption, indexSet, ECO_BNF_1_EF_NONE, "abstract-declarator");

    /* (6.5.5) abstract-declarator:
                    pointer
                    pointeropt direct-abstract-declarator
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "abstract-declarator");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "pointer");
    pIOption = pIRule->pVTbl->AddOptionalSequence(pIRule, &indexSet, ECO_BNF_1_EF_ALTERNATION, 0, 0);
    pIElement = pIOption->pVTbl->AddAlternative(pIOption, &indexSet, ECO_BNF_1_EF_NONE, "pointer");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "direct-abstract-declarator");

    /* (6.5.5) direct-abstract-declarator:
                    ( abstract-declarator )
                    direct-abstract-declaratoropt [ constant-expression opt ]
                    direct-abstract-declaratoropt ( parameter-type-list opt )
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "direct-abstract-declarator");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "(");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "abstract-declarator");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ")");
    pIOption = pIRule->pVTbl->AddOptionalSequence(pIRule, &indexSet, ECO_BNF_1_EF_ALTERNATION, 0, 0);
    pIElement = pIOption->pVTbl->AddAlternative(pIOption, &indexSet, ECO_BNF_1_EF_NONE, "direct-abstract-declarator");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "[");
    pIOption = pIRule->pVTbl->AddOptionalSequence(pIRule, &indexSet, ECO_BNF_1_EF_NONE, 0, 0);
    pIElement = pIOption->pVTbl->AddConcatenation(pIOption, indexSet, ECO_BNF_1_EF_NONE, "constant-expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "]");
    pIOption = pIRule->pVTbl->AddOptionalSequence(pIRule, &indexSet, ECO_BNF_1_EF_ALTERNATION, 0, 0);
    pIElement = pIOption->pVTbl->AddAlternative(pIOption, &indexSet, ECO_BNF_1_EF_NONE, "direct-abstract-declarator");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "(");
    pIOption = pIRule->pVTbl->AddOptionalSequence(pIRule, &indexSet, ECO_BNF_1_EF_NONE, 0, 0);
    pIElement = pIOption->pVTbl->AddConcatenation(pIOption, indexSet, ECO_BNF_1_EF_NONE, "parameter-type-list");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ")");

    /* (6.5.6) typedef-name:
                    identifier
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "typedef-name");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "identifier");

    /* (6.5.7) initializer:
                    assignment-expression
                    { initializer-list }
                    { initializer-list , }
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "initializer");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "assignment-expression");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "{");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "initializer-list");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "}");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "{");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "initializer-list");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ",");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "}");

    /* (6.5.7) initializer-list:
                    initializer
                    initializer-list , initializer
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "initializer-list");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "initializer");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "initializer-list");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ",");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "initializer");

    /* B.2.3 Statements */

    /* (6.6) statement:
                    labeled-statement
                    compound-statement
                    expression-statement
                    selection-statement
                    iteration-statement
                    jump-statement
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "statement");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "labeled-statement");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "compound-statement");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "expression-statement");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "selection-statement");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "iteration-statement");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "jump-statement");

    /* (6.6.1) labeled-statement:
                    identifier : statement
                    case constant-expression : statement
                    default : statement
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "labeled-statement");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "identifier");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ":");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "statement");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "case");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "constant-expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ":");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "statement");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "default");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ":");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "statement");

    /* (6.6.2) compound-statement:
                { declaration-list opt statement-list opt}
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "compound-statement");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "{");
    pIOption = pIRule->pVTbl->AddOptionalSequence(pIRule, &indexSet, ECO_BNF_1_EF_NONE, 0, 0);
    pIElement = pIOption->pVTbl->AddConcatenation(pIOption, indexSet, ECO_BNF_1_EF_NONE, "declaration-list");
    pIOption = pIRule->pVTbl->AddOptionalSequence(pIRule, &indexSet, ECO_BNF_1_EF_NONE, 0, 0);
    pIElement = pIOption->pVTbl->AddConcatenation(pIOption, indexSet, ECO_BNF_1_EF_NONE, "statement-list");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "}");

    /* (6.6.2) declaration-list:
                    declaration
                    declaration-list declaration
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "declaration-list");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "declaration");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "declaration-list");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "declaration");

    /* (6.6.2) statement-list:
                    statement
                    statement-list statement
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "statement-list");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "statement");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "statement-list");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "statement");

    /* (6.6.3) expression-statement:
                    expressionopt ;
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "expression-statement");
    indexSet = 0;
    pIOption = pIRule->pVTbl->AddOptionalSequence(pIRule, &indexSet, ECO_BNF_1_EF_ALTERNATION, 0, 0);
    pIElement = pIOption->pVTbl->AddAlternative(pIOption, &indexSet, ECO_BNF_1_EF_NONE, "expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ";");

    /* (6.6.4) selection-statement:
                    if ( expression ) statement
                    if ( expression ) statement else statement
                    switch ( expression ) statement
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "selection-statement");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "if");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "(");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ")");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "statement");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "if");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "(");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ")");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "statement");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "else");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "statement");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "switch");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "(");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ")");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "statement");

    /* (6.6.5) iteration-statement:
                    while ( expression ) statement
                    do statement while ( expression ) ;
                    for ( expression opt ; expression opt ; expression opt ) statement
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "iteration-statement");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "while");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "(");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ")");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "statement");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "do");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "statement");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "while");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "(");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ")");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ";");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "for");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "(");
    pIOption = pIRule->pVTbl->AddOptionalSequence(pIRule, &indexSet, ECO_BNF_1_EF_NONE, 0, 0);
    pIElement = pIOption->pVTbl->AddConcatenation(pIOption, indexSet, ECO_BNF_1_EF_NONE, "expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ";");
    pIOption = pIRule->pVTbl->AddOptionalSequence(pIRule, &indexSet, ECO_BNF_1_EF_NONE, 0, 0);
    pIElement = pIOption->pVTbl->AddConcatenation(pIOption, indexSet, ECO_BNF_1_EF_NONE, "expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ";");
    pIOption = pIRule->pVTbl->AddOptionalSequence(pIRule, &indexSet, ECO_BNF_1_EF_NONE, 0, 0);
    pIElement = pIOption->pVTbl->AddConcatenation(pIOption, indexSet, ECO_BNF_1_EF_NONE, "expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ")");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "statement");


    /* (6.6.6) jump-statement:
                        goto identifier ;
                        continue ;
                        break ;
                        return expressionopt ;
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "jump-statement");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "goto");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "identifier");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ";");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "continue");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ";");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "break");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ";");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "return");
    pIOption = pIRule->pVTbl->AddOptionalSequence(pIRule, &indexSet, ECO_BNF_1_EF_NONE, 0, 0);
    pIElement = pIOption->pVTbl->AddConcatenation(pIOption, indexSet, ECO_BNF_1_EF_NONE, "expression");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, ";");

    /* B.2.4 External definitions */

    /* (6.7) translation-unit:
                        external-declaration
                        translation-unit external-declaration
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "translation-unit");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "external-declaration");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "translation-unit");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "external-declaration");

    /* (6.7) external-declaration:
                        function-definition
                        declaration
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "external-declaration");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "function-definition");
    pIElement = pIRule->pVTbl->AddAlternative(pIRule, &indexSet, ECO_BNF_1_EF_NONE, "declaration");

    /* (6.7.1) function-definition:
                        declaration-specifiers opt declarator declaration-list opt compound-statement
     */
    pIRule = pIBNF->pVTbl->AddRule(pIBNF, "function-definition");
    indexSet = 0;
    pIOption = pIRule->pVTbl->AddOptionalSequence(pIRule, &indexSet, ECO_BNF_1_EF_ALTERNATION, 0, 0);
    pIElement = pIOption->pVTbl->AddAlternative(pIOption, &indexSet, ECO_BNF_1_EF_NONE, "declaration-specifier"); //declaration-specifiers
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "declarator");
    pIOption = pIRule->pVTbl->AddOptionalSequence(pIRule, &indexSet, ECO_BNF_1_EF_NONE, 0, 0);
    pIElement = pIOption->pVTbl->AddConcatenation(pIOption, indexSet, ECO_BNF_1_EF_NONE, "declaration-list");
    pIElement = pIRule->pVTbl->AddConcatenation(pIRule, indexSet, ECO_BNF_1_EF_NONE, "compound-statement");
    pCMe->m_pISyntaxRules = pIBNF;
    return result;
}

/*
 *
 * <summary>
 *   QueryInterface Function
 * </summary>
 *
 * <description>
 *   QueryInterface function for the IEcoIDL1 interface
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1_40BB8A88_QueryInterface(/* in */ IEcoIDL1Ptr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoIDL1_40BB8A88* pCMe = (CEcoIDL1_40BB8A88*)me;

    /* Pointer Validation */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Validate and retrieve requested interface */
    if ( IsEqualUGUID(riid, &IID_IEcoIDL1) ) {
        *ppv = &pCMe->m_pVTblIIDL;
        pCMe->m_pVTblIIDL->AddRef((IEcoIDL1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIIDL;
        pCMe->m_pVTblIIDL->AddRef((IEcoIDL1*)pCMe);
    }
    else {
        *ppv = 0;
        return ERR_ECO_NOINTERFACE;
    }
    return ERR_ECO_SUCCESES;
}

/*
 *
 * <summary>
 *   AddRef Function
 * </summary>
 *
 * <description>
 *   AddRef function for the IEcoIDL1 interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoIDL1_40BB8A88_AddRef(/* in */ IEcoIDL1Ptr_t me) {
    CEcoIDL1_40BB8A88* pCMe = (CEcoIDL1_40BB8A88*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    return atomicincrement_int32_t(&pCMe->m_cRef);
}

/*
 *
 * <summary>
 *   Release Function
 * </summary>
 *
 * <description>
 *   Release function for the IEcoIDL1 interface
 * </description>
 *
 */
static uint32_t ECOCALLMETHOD CEcoIDL1_40BB8A88_Release(/* in */ IEcoIDL1Ptr_t me) {
    CEcoIDL1_40BB8A88* pCMe = (CEcoIDL1_40BB8A88*)me;

    /* Pointer Validation */
    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    /* Decrementing the component's reference count */
    atomicdecrement_int32_t(&pCMe->m_cRef);
    /* If the count is zero, free the instance data */
    if ( pCMe->m_cRef == 0 ) {
        pCMe->Delete(pCMe);

        return 0;
    }
    return pCMe->m_cRef;
}


/*
 *
 * <summary>
 *   Initialize Function
 * </summary>
 *
 * <description>
 *   Function
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1_40BB8A88_Initialize(/* in */ IEcoIDL1Ptr_t me) {
    CEcoIDL1_40BB8A88* pCMe = (CEcoIDL1_40BB8A88*)me;
    IEcoList1* pIRuleList = 0;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    if (pCMe->m_pILexicalRules == 0) {
         CEcoIDL1_40BB8A88_SetDefaultLexer(pCMe);
    }

   // pIRuleList = pCMe->m_pISyntaxRules->pVTbl->get_RuleList(pCMe->m_pISyntaxRules);
    if (pCMe->m_pISyntaxRules == 0) {
        //if ( pIRuleList->pVTbl->Count(pIRuleList) == 0) {
            CEcoIDL1_40BB8A88_SetDefaultSyntax(pCMe);
        //}
    }

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <summary>
 *   Terminate Function
 * </summary>
 *
 * <description>
 *   Function
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1_40BB8A88_Terminate(/* in */ IEcoIDL1Ptr_t me) {
    CEcoIDL1_40BB8A88* pCMe = (CEcoIDL1_40BB8A88*)me;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <summary>
 *   GetLexicalRules Function
 * </summary>
 *
 * <description>
 *   Function
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1_40BB8A88_GetLexicalRules(/* in */ IEcoIDL1Ptr_t me, /* out */ voidptr_t* ppRules) {
    CEcoIDL1_40BB8A88* pCMe = (CEcoIDL1_40BB8A88*)me;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <summary>
 *   GetSyntaxRules Function
 * </summary>
 *
 * <description>
 *   Function
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1_40BB8A88_GetSyntaxRules(/* in */ IEcoIDL1Ptr_t me, /* out */ voidptr_t* ppRules) {
    CEcoIDL1_40BB8A88* pCMe = (CEcoIDL1_40BB8A88*)me;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <summary>
 *   ParseFile Function
 * </summary>
 *
 * <description>
 *   Function
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1_40BB8A88_ParseFile(/* in */ IEcoIDL1Ptr_t me, /* in */ char_t* filePath, /* out */ IEcoAST1Ptr_t* ppAST) {
    CEcoIDL1_40BB8A88* pCMe = (CEcoIDL1_40BB8A88*)me;
    IEcoSyntaxAnalyzer1Parser* pIParser = 0;
    IEcoLexicalAnalyzer1Token* pIToken = 0;
    IEcoParser1Action* pIAction = 0;
    IEcoLexicalData1* pIData = 0;
    IEcoLexicalAnalyzer1Scanner* pScanner = 0;
    char_t* pszSourceFileExt = 0;
    IEcoAST1* pIAST;
    int16_t result = 0;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    /* КОМПИЛЯЦИЯ: Превращаем RE в оптимизированные таблицы (DFA) */
    /* Здесь создается IEcoLexicalData1 с AlphabetMap и TransitionMatrix */
    result = pCMe->m_pILexicalRules->pVTbl->Compile(pCMe->m_pILexicalRules, &pIData);
	if (result != 0) {
		return -1;
	}

    /* Извлекаем расширение файла из имени */
    pszSourceFileExt = pCMe->m_pIStr->pVTbl->SearchLastCharacter(pCMe->m_pIStr, filePath, '.');
    if (pszSourceFileExt != 0) {
        pCMe->m_Name = pCMe->m_pIStr->pVTbl->Substring(pCMe->m_pIStr, filePath, 0, pszSourceFileExt - filePath);
    } else {
        pCMe->m_Name = pCMe->m_pIStr->pVTbl->Clone(pCMe->m_pIStr, filePath);
    }

    /* Парсер */
    pIParser = pCMe->m_pISA->pVTbl->get_Parser(pCMe->m_pISA, pCMe->m_pISyntaxRules, 0);
    if (pIParser == 0) {
        printf("ERROR: failed create parser\n");
    }

    if (result == 0 && pIData != 0) {
        result = pCMe->m_pILA->pVTbl->new_FileScanner(pCMe->m_pILA, (IEcoUnknownPtr_t)pIData, filePath, &pScanner);
        if (result != 0) {
            printf("ERROR: failed when scanning a file with code %d\n", result);
            return result;
        } else {
            printf("SUCCESS scanned a file\n");
        }

        pIToken = pScanner->pVTbl->Scan(pScanner);
        while (pIToken && !pIToken->pVTbl->IsEOF(pIToken)) {
            uint32_t type = pIToken->pVTbl->get_Type(pIToken);
            char_t* lexeme = pIToken->pVTbl->get_Lexeme(pIToken);
            uint32_t line = pIToken->pVTbl->get_Line(pIToken);
            uint32_t col = pIToken->pVTbl->get_Column(pIToken);
            uint32_t channel = pIToken->pVTbl->get_Channel(pIToken);

            printf("Token: type=%u, lexeme='%s', line=%u, col=%u, channel=%u\n", type, lexeme ? lexeme : "", line, col, channel);

            /* Синтаксический анализ */
            //while ( (pIAction = pIParser->pVTbl->Parse(pIParser, pIToken)) != 0 ) {
            //    if (pIAction->pVTbl->get_Type(pIAction) != ECO_ACTION_PROCESSING_TYPE_REDUCE) {
            //        pIAction->pVTbl->Release(pIAction);
            //    }
            //}
            pIToken->pVTbl->Release(pIToken);
            pIToken = 0;
            pIToken = pScanner->pVTbl->Scan(pScanner);
        }
        if (pIToken) {
            pIToken->pVTbl->Release(pIToken);
            pIToken = 0;
        }
    }
    if (pIParser != 0) {
        pIAST = pIParser->pVTbl->get_AST(pIParser);
        *ppAST = pIAST;
    }

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <summary>
 *   RegisterEmitter Function
 * </summary>
 *
 * <description>
 *   Function
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1_40BB8A88_RegisterEmitter(/* in */ IEcoIDL1Ptr_t me, /* in */ const UGUID* rcid, /* in */ char_t* langId) {
    CEcoIDL1_40BB8A88* pCMe = (CEcoIDL1_40BB8A88*)me;
    uint32_t i;

    /* Pointer Validation */
    if (me == 0 || rcid == 0 || langId == 0) {
		return ERR_ECO_POINTER;
	}
    if (pCMe->m_cEmitters >= 16) {
		return -1; /* Достигнут лимит */
	}

	/* Проверка, нет ли уже такого языка */
    for (i = 0; i < pCMe->m_cEmitters; i++) {
        if (pCMe->m_pIStr->pVTbl->Compare(pCMe->m_pIStr, pCMe->m_Emitters[i].langId, langId) == 0) {
            pCMe->m_Emitters[i].cid = *rcid;
            return ERR_ECO_SUCCESES;
        }
    }

	/* Добавление нового */
    pCMe->m_Emitters[pCMe->m_cEmitters].cid = *rcid;
    for (i = 0; i < 31 && langId[i] != 0; i++) {
        pCMe->m_Emitters[pCMe->m_cEmitters].langId[i] = langId[i];
    }
    pCMe->m_Emitters[pCMe->m_cEmitters].langId[i] = 0;
    
    pCMe->m_cEmitters++;

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <summary>
 *   GetEmitter Function
 * </summary>
 *
 * <description>
 *   Function
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1_40BB8A88_GetEmitter(/* in */ IEcoIDL1Ptr_t me, /* in */ char_t* langId, /* out */ IEcoIDL1Emitter** ppIEmitter) {
    CEcoIDL1_40BB8A88* pCMe = (CEcoIDL1_40BB8A88*)me;
	uint32_t i;

    /* Pointer Validation */
    if (me == 0 || langId == 0 || ppIEmitter == 0) {
		return ERR_ECO_POINTER;
	}
    *ppIEmitter = 0;

	for (i = 0; i < pCMe->m_cEmitters; i++) {
        if (pCMe->m_pIStr->pVTbl->Compare(pCMe->m_pIStr, pCMe->m_Emitters[i].langId, langId) == 0) {
            return pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &pCMe->m_Emitters[i].cid, 0, &IID_IEcoIDL1Emitter, (void**)ppIEmitter);
        }
    }

    return -1;
}

/*
 *
 * <summary>
 *   Generate Function
 * </summary>
 *
 * <description>
 *   Function
 * </description>
 *
 */
static int16_t ECOCALLMETHOD CEcoIDL1_40BB8A88_Generate(/* in */ IEcoIDL1Ptr_t me, /* in */ IEcoAST1Ptr_t pAST, /* in */ IEcoIDL1ProjectLayoutPtr_t pLayout, /* in */ char_t* langId, /* in */ void* commonArgs) {
    CEcoIDL1_40BB8A88* pCMe = (CEcoIDL1_40BB8A88*)me;
    IEcoIDL1Emitter* pIEmitter = 0;
    char_t* pszIfaceName = 0;
    uint32_t i;
    bool_t generateAll = 0;
    bool_t foundLanguage = 0;
    uint32_t successCount = 0;
    uint32_t failCount = 0;
    int16_t result = 0;

    /* Pointer Validation */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

	if (langId == 0 || pCMe->m_pIStr->pVTbl->Compare(pCMe->m_pIStr, langId, "ALL") == 0) {
        generateAll = 1;
    }

    for (i = 0; i < pCMe->m_cEmitters; i++) {
        if (generateAll || pCMe->m_pIStr->pVTbl->Compare(pCMe->m_pIStr, langId, pCMe->m_Emitters[i].langId) == 0) {
            foundLanguage = 1;
			result = pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &pCMe->m_Emitters[i].cid, 0, &IID_IEcoIDL1Emitter, (void**)&pIEmitter);
            if (result == 0 && pIEmitter != 0) { 
                pszIfaceName = pCMe->m_pIStr->pVTbl->Append(pCMe->m_pIStr, pszIfaceName, pCMe->m_Name);
                pIEmitter->pVTbl->Emit(pIEmitter, pAST, pszIfaceName);
                pCMe->m_pIStr->pVTbl->Free(pCMe->m_pIStr, pszIfaceName);
                pszIfaceName = 0;
                pIEmitter->pVTbl->Release(pIEmitter);
				successCount++;
            } else {
				failCount++;
            }
        }
    }

	if (!foundLanguage) {
        return -2;
    }
    if (successCount == 0) {
        return -3;
    }
    if (failCount > 0) {
        return -4; 
    }

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <summary>
 *   Init Function
 * </summary>
 *
 * <description>
 *   Instance initialization function
 * </description>
 *
 */
static int16_t ECOCALLMETHOD initCEcoIDL1_40BB8A88(/*in*/ CEcoIDL1_40BB8A88Ptr_t me, /* in */ IEcoUnknownPtr_t pIUnkSystem) {
    CEcoIDL1_40BB8A88* pCMe = (CEcoIDL1_40BB8A88*)me;

    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    int16_t result = ERR_ECO_POINTER;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;	

    /* Pointer Validation */
    if (me == 0 ) {
        return result;
    }

    /* Storing the pointer to the system interface */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;

    /* Getting the interface for working with the interface bus */
    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void **)&pCMe->m_pIBus);

    /* Getting the component ID for working with memory */
    result = pCMe->m_pIBus->pVTbl->QueryInterface(pCMe->m_pIBus, &IID_IEcoInterfaceBus1MemExt, (void**)&pIMemExt);
    if (result == 0 && pIMemExt != 0) {
        rcid = (UGUID*)pIMemExt->pVTbl->get_Manager(pIMemExt);
        pIMemExt->pVTbl->Release(pIMemExt);
    }

    /* Getting the memory allocator interface */
    result = pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, rcid, 0, &IID_IEcoMemoryAllocator1, (void**) &pCMe->m_pIMem);
    /* Check */
    if (result != 0 || pCMe->m_pIMem == 0) {
        result = ERR_ECO_GET_MEMORY_ALLOCATOR;
    }

    result = pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoString1, 0, &IID_IEcoString1, (void**) &pCMe->m_pIStr);
    /* Check */
    if (result != 0 || pCMe->m_pIStr == 0) {
        //result = ERR_ECO_GET_MEMORY_ALLOCATOR;
    }

    result = pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoBLA1, 0, &IID_IEcoLexicalAnalyzer1, (void**) &pCMe->m_pILA);
    if (result != 0 || pCMe->m_pILA == 0) {
        //result = ERR_ECO_BLA;
    }
    result = pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoBSA1, 0, &IID_IEcoSyntaxAnalyzer1, (void**) &pCMe->m_pISA);
    if (result != 0 || pCMe->m_pILA == 0) {
        //result = ERR_ECO_SA;
    }

    /* Регистрация алгоритма для анализа */
    pCMe->m_pISA->pVTbl->RegisterAlgorithm(pCMe->m_pISA, &CID_EcoLR1, "LR1");
    /* Устанавливаем алгоритм по умолчанию */
    pCMe->m_pISA->pVTbl->set_DefaultAlgorithm(pCMe->m_pISA, "LR1");

    result = pCMe->m_pIBus->pVTbl->QueryComponent(pCMe->m_pIBus, &CID_EcoAST1, 0, &IID_IEcoAST1, (void**) &pCMe->m_pIAST);
    if (result != 0 || pCMe->m_pIAST == 0) {
        //result = ERR_ECO_AST;
    }

	pCMe->m_cEmitters = 0;

    return result;
}

/*
 *
 * <summary>
 *   Create Function
 * </summary>
 *
 * <description>
 *   Instance creation function
 * </description>
 *
 */
static int16_t ECOCALLMETHOD createCEcoIDL1_40BB8A88(/* in */ CEcoIDL1_40BB8A88Ptr_t pCMe, /* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter) {
    int16_t result = ERR_ECO_POINTER;

    /* Pointer Validation */
    if (pCMe == 0) {
        return result; /* ERR_ECO_POINTER */
    }

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <summary>
 *   Delete Function
 * </summary>
 *
 * <description>
 *   Instance freeing function
 * </description>
 *
 */
static void ECOCALLMETHOD deleteCEcoIDL1_40BB8A88(/* in */ CEcoIDL1_40BB8A88Ptr_t pCMe) {
    IEcoMemoryAllocator1* pIMem = 0;

    if (pCMe != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Freeing */
        if ( pCMe->m_Name != 0 ) {
            pIMem->pVTbl->Free(pIMem, pCMe->m_Name);
        }
		if ( pCMe->m_pIAST != 0 ) {
            pCMe->m_pIAST->pVTbl->Release(pCMe->m_pIAST);
        }
        if ( pCMe->m_pISyntaxRules != 0 ) {
            pCMe->m_pISyntaxRules->pVTbl->Release(pCMe->m_pISyntaxRules);
        }
        if ( pCMe->m_pISA != 0 ) {
            pCMe->m_pISA->pVTbl->Release(pCMe->m_pISA);
        }
		if ( pCMe->m_pILexicalRules != 0 ) {
            pCMe->m_pILexicalRules->pVTbl->Release(pCMe->m_pILexicalRules);
        }
        if ( pCMe->m_pILA != 0 ) {
            pCMe->m_pILA->pVTbl->Release(pCMe->m_pILA);
        }
		if ( pCMe->m_pIStr != 0 ) {
            pCMe->m_pIStr->pVTbl->Release(pCMe->m_pIStr);
        }
        if ( pCMe->m_pIBus != 0 ) {
            pCMe->m_pIBus->pVTbl->Release(pCMe->m_pIBus);
        }
        if ( pCMe->m_pISys != 0 ) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}

/* IEcoIDL1 Virtual Table */
IEcoIDL1VTbl g_x948C13ED820E45389E1EBBDD9308A42CVTbl_40BB8A88 = {
    CEcoIDL1_40BB8A88_QueryInterface,
    CEcoIDL1_40BB8A88_AddRef,
    CEcoIDL1_40BB8A88_Release,
    CEcoIDL1_40BB8A88_Initialize,
    CEcoIDL1_40BB8A88_Terminate,
    CEcoIDL1_40BB8A88_GetLexicalRules,
    CEcoIDL1_40BB8A88_GetSyntaxRules,
    CEcoIDL1_40BB8A88_ParseFile,
    CEcoIDL1_40BB8A88_RegisterEmitter,
    CEcoIDL1_40BB8A88_GetEmitter,
    CEcoIDL1_40BB8A88_Generate
};

/* Object Instance */
CEcoIDL1_40BB8A88 g_xCEcoIDL1_40BB8A88 = {
    &g_x948C13ED820E45389E1EBBDD9308A42CVTbl_40BB8A88,
   
    initCEcoIDL1_40BB8A88,
    createCEcoIDL1_40BB8A88,
    deleteCEcoIDL1_40BB8A88,
    1, /* m_cRef */
    0, /* m_pIMem */
    0, /* m_pISys */
    0, /* m_pIBus */
    0, /* m_pIStr */
    0, /* m_pILA */
    0, /* m_pILexicalRules */
    0, /* m_pISA */
    0, /* m_pISynatxRules */
    0, /* m_pIAST */
    0  /* m_Name */
};
