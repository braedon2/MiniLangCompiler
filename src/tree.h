// defines the abstract syntac tree

#ifndef TREE_H
#define TREE_H

typedef struct EXP EXP;
typedef struct IFSTMT IFSTMT;
typedef struct STMT STMT;

typedef enum {
    k_expressionKindIdentifier,
    k_expressionKindIntLiteral,
    k_expressionKindStrLiteral,
    k_expressionKindFloatLiteral,
    k_expressionKindBoolLiteral,
    k_expressionKindAddition,
    k_expressionKindSubtraction,
    k_expressionKindMultiplication,
    k_expressionKindGTEQ,
    k_expressionKindLTEQ,
    k_expressionKindLessThan,
    k_expressionKindGreaterThan,
    k_expressionKindEqual,
    k_expressionKindNotEqual,
    k_expressionKindAnd,
    k_expressionKindOr,
    k_expressionKindDivision,
    k_expressionKindUMinus,
    k_expressionKindUNot
} ExpressionKind;


struct EXP {
    ExpressionKind kind;
    union {
        char *identifier;
        int intLiteral;
        char *strLiteral;
        float floatLiteral;
        int boolLiteral;
        struct { EXP *lhs; EXP *rhs; } binary;
        struct { EXP *exp; } unary;
    } val;
};

typedef enum {
    k_ifstmtKindIfElse,
    k_ifstmtKindIfElseIf
} IfstmtKind;


struct IFSTMT {
    IfstmtKind kind;
    struct { 
        EXP *condition;
        STMT *true_branch;
        union {
            STMT *stmt_list;
            IFSTMT *ifstmt;
        } false_branch; 
    } val;
};

typedef enum {
    k_stmtKindDeclaration,
    k_stmtKindRead,
    k_stmtKindPrint,
    k_stmtKindAssign,
    k_stmtKindIf,
    k_stmtKindWhile
} StmtKind;

typedef enum {
    STR,
    FLOAT,
    BOOL,
    INT,
    INFERRED
} DeclarationType;

struct STMT {
    StmtKind kind;
    union {
        struct { char *identifier; DeclarationType type; EXP *exp; } declaration;
        char *readVar;
        EXP *printExp;
        struct { char *identifier; EXP *exp; } assign;
        IFSTMT *ifstmt;
        struct { EXP *condition; STMT *body; } whilestmt;
    } val;
    STMT *next;
};

/* constructors */

EXP *makeEXP_identifier(char *identifier);
EXP *makeEXP_intLiteral(int intLiteral);
EXP *makeEXP_strLiteral(char *strLiteral);
EXP *makeEXP_floatLiteral(float floatLiteral);
EXP *makeEXP_boolLiteral(int boolLiteral);
EXP *makeEXP_addition(EXP *lfs, EXP *rhs);
EXP *makeEXP_subtraction(EXP *lfs, EXP *rhs);
EXP *makeEXP_multiplication(EXP *lfs, EXP *rhs);
EXP *makeEXP_division(EXP *lfs, EXP *rhs);
EXP *makeEXP_GTEQ(EXP *lfs, EXP *rhs);
EXP *makeEXP_LTEQ(EXP *lfs, EXP *rhs);
EXP *makeEXP_lessThan(EXP *lfs, EXP *rhs);
EXP *makeEXP_greaterThan(EXP *lfs, EXP *rhs);
EXP *makeEXP_equal(EXP *lfs, EXP *rhs);
EXP *makeEXP_notEqual(EXP *lfs, EXP *rhs);
EXP *makeEXP_and(EXP *lfs, EXP *rhs);
EXP *makeEXP_or(EXP *lfs, EXP *rhs);
EXP *makeEXP_uMinus(EXP *exp);
EXP *makeEXP_uNot(EXP *exp);

IFSTMT *makeIFSTMT_ifElse(EXP *condition, STMT *true_branch, STMT *false_branch);
IFSTMT *makeIFSTMT_ifElseIf(EXP *condition, STMT *true_branch, IFSTMT *false_branch);

STMT *makeSTMT_declaration(char *identifier, DeclarationType type, EXP *exp);
STMT *makeSTMT_read(char *readVar);
STMT *makeSTMT_print(EXP *exp);
STMT *makeSTMT_assign(char *identifier, EXP *exp);
STMT *makeSTMT_if(IFSTMT *ifstmt);
STMT *makeSTMT_while(EXP *condition, STMT *body);

#endif