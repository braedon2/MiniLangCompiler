// defines the abstract syntac tree

typedef struct STMT_LIST STMT_LIST;
typedef struct EXP EXP;
typedef struct IFSTMT IFSTMT;
typedef struct STMT STMT;

struct STMT_LIST {
    STMT *stmt;
    STMT_LIST *rest;
};

typedef enum {
    k_expressionKindIdentifier,
    k_expressionKindIntLiteral,
    k_expressionKindStrLiteral,
    k_expressionKindBoolLiteral,
    k_expressionKindAddition,
    k_expressionKindSubtraction,
    k_expressionKindMultiplication,
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
        STMT_LIST *true_branch;
        union {
            STMT_LIST *stmt_list;
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
        struct { EXP *condition; STMT_LIST *body; } whilestmt;
    } val;
};

/* constructors */

EXP *makeEXP_identifier(char *identifier);
EXP *makeEXP_intLiteral(int intLiteral);
EXP *makeEXP_strLiteral(char *strLiteral);
EXP *makeEXP_boolLiteral(int boolLiteral);
EXP *makeEXP_addition(EXP *lfs, EXP *rhs);
EXP *makeEXP_subtraction(EXP *lfs, EXP *rhs);
EXP *makeEXP_multiplication(EXP *lfs, EXP *rhs);
EXP *makeEXP_division(EXP *lfs, EXP *rhs);
EXP *makeEXP_uMinus(EXP *exp);
EXP *makeEXP_uNot(EXP *exp);

IFSTMT *makeIFSTMT_ifElse(EXP *condition, STMT_LIST *true_branch, STMT_LIST *false_branch);
IFSTMT *makeIFSTMT_ifElseIf(EXP *condition, STMT_LIST *true_branch, IFSTMT *false_branch);

STMT *makeSTMT_declaration(char *identifier, DeclarationType type, EXP *exp);
STMT *makeSTMT_read(char *readVar);
STMT *makeSTMT_print(EXP *exp);
STMT *makeSTMT_assign(char *identifier, EXP *exp);
STMT *makeSTMT_if(IFSTMT *ifstmt);
STMT *makeSTMT_while(EXP *condition, STMT_LIST *body);