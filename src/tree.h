// defines the abstract syntac tree

typedef struct EXP EXP;
struct EXP {
    ExpressionKind kind;
    union {
        char *identifier;
        int intLiteral;
        char *strLiteral;
        int boolLiteral;
        struct { EXP *lfs; EXP *rhs; } binary;
        struct { EXP *exp; } unary;
    } val;
};

typedef enum {
    k_expressionKindIdentifier,
    k_expressionKindIntLiteral,
    k_expressionKindAddition,
    k_expressionKindSubtraction,
    k_expressionKindMultiplication,
    k_expressionKindDivision,
    k_expressionKindUMinus,
    k_expressionKindUNot
} ExpressionKind;

typedef struct IFSTMT IFSTMT;
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
    k_ifstmtKindIfElse,
    k_ifstmtKindIfElseIf
} IfstmtKind;

typedef struct STMT STMT;
struct STMT {
    StmtKind kind;
    union {
        struct { char *identifier; DeclarationType type; EXP *exp; } declaration;
        char *readVar;
        EXP *printExp;
        struct { char *identifier; EXP *exp; } assign;
        IFSTMT *ifstmt;
        struct { EXP *condition; STMT_LIST *body; } whileStmt;
    };
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

typedef struct STMT_LIST STMT_LIST;
struct STMT_LIST {
    STMT *stmt;
    STMT_LIST *rest;
}