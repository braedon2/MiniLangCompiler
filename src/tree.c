#include "tree.h"
#include <stdlib.h>
#include <stdio.h>

EXP *makeEXP_identifier(char *identifier)
{
    EXP *exp = malloc(sizeof(EXP));
    exp->kind = k_expressionKindIdentifier;
    exp->val.identifier = identifier;
    return exp;
}

EXP *makeEXP_intLiteral(int intLiteral)
{
    EXP *exp = malloc(sizeof(EXP));
    exp->kind = k_expressionKindIntLiteral;
    exp->val.intLiteral = intLiteral;
    return exp;
}

EXP *makeEXP_strLiteral(char *strLiteral)
{
    EXP *exp = malloc(sizeof(EXP));
    exp->kind = k_expressionKindStrLiteral;
    exp->val.strLiteral = strLiteral;
    return exp;
}

EXP *makeEXP_floatLiteral(float floatLiteral)
{
    EXP *exp = malloc(sizeof(EXP));
    exp->kind = k_expressionKindFloatLiteral;
    exp->val.floatLiteral = floatLiteral;
    return exp;
}

EXP *makeEXP_boolLiteral(int boolLiteral)
{
    if (boolLiteral != 0 && boolLiteral != 1)
    {
        printf("bool literal must have value of 0 or 1");
        exit(1);
    }

    EXP *exp = malloc(sizeof(EXP));
    exp->kind = k_expressionKindBoolLiteral;
    exp->val.boolLiteral = boolLiteral;
    return exp;
}

EXP *makeEXP_addition(EXP *lfs, EXP *rhs)
{
    EXP *exp = malloc(sizeof(EXP));
    exp->kind = k_expressionKindAddition;
    exp->val.binary.lhs = lfs;
    exp->val.binary.rhs = rhs;
    return exp;
}

EXP *makeEXP_subtraction(EXP *lfs, EXP *rhs)
{
    EXP *exp = malloc(sizeof(EXP));
    exp->kind = k_expressionKindSubtraction;
    exp->val.binary.lhs = lfs;
    exp->val.binary.rhs = rhs;
    return exp;
}

EXP *makeEXP_multiplication(EXP *lfs, EXP *rhs)
{
    EXP *exp = malloc(sizeof(EXP));
    exp->kind = k_expressionKindMultiplication;
    exp->val.binary.lhs = lfs;
    exp->val.binary.rhs = rhs;
    return exp;
}

EXP *makeEXP_division(EXP *lfs, EXP *rhs)
{
    EXP *exp = malloc(sizeof(EXP));
    exp->kind = k_expressionKindDivision;
    exp->val.binary.lhs = lfs;
    exp->val.binary.rhs = rhs;
    return exp;
}

EXP *makeEXP_GTEQ(EXP *lfs, EXP *rhs)
{
    EXP *exp = malloc(sizeof(EXP));
    exp->kind = k_expressionKindGTEQ;
    exp->val.binary.lhs = lfs;
    exp->val.binary.rhs = rhs;
    return exp;
}

EXP *makeEXP_LTEQ(EXP *lfs, EXP *rhs)
{
    EXP *exp = malloc(sizeof(EXP));
    exp->kind = k_expressionKindLTEQ;
    exp->val.binary.lhs = lfs;
    exp->val.binary.rhs = rhs;
    return exp;
}

EXP *makeEXP_lessThan(EXP *lfs, EXP *rhs)
{
    EXP *exp = malloc(sizeof(EXP));
    exp->kind = k_expressionKindLessThan;
    exp->val.binary.lhs = lfs;
    exp->val.binary.rhs = rhs;
    return exp;
}

EXP *makeEXP_greaterThan(EXP *lfs, EXP *rhs)
{
    EXP *exp = malloc(sizeof(EXP));
    exp->kind = k_expressionKindGreaterThan;
    exp->val.binary.lhs = lfs;
    exp->val.binary.rhs = rhs;
    return exp;
}

EXP *makeEXP_equal(EXP *lfs, EXP *rhs)
{
    EXP *exp = malloc(sizeof(EXP));
    exp->kind = k_expressionKindEqual;
    exp->val.binary.lhs = lfs;
    exp->val.binary.rhs = rhs;
    return exp;
}

EXP *makeEXP_notEqual(EXP *lfs, EXP *rhs)
{
    EXP *exp = malloc(sizeof(EXP));
    exp->kind = k_expressionKindNotEqual;
    exp->val.binary.lhs = lfs;
    exp->val.binary.rhs = rhs;
    return exp;
}

EXP *makeEXP_and(EXP *lfs, EXP *rhs)
{
    EXP *exp = malloc(sizeof(EXP));
    exp->kind = k_expressionKindAnd;
    exp->val.binary.lhs = lfs;
    exp->val.binary.rhs = rhs;
    return exp;
}

EXP *makeEXP_or(EXP *lfs, EXP *rhs)
{
    EXP *exp = malloc(sizeof(EXP));
    exp->kind = k_expressionKindOr;
    exp->val.binary.lhs = lfs;
    exp->val.binary.rhs = rhs;
    return exp;
}

EXP *makeEXP_uMinus(EXP *exp)
{
    EXP *e = malloc(sizeof(EXP));
    e->kind = k_expressionKindUMinus;
    e->val.unary.exp = exp;
    return e;
}

EXP *makeEXP_uNot(EXP *exp)
{
    EXP *e = malloc(sizeof(EXP));
    e->kind = k_expressionKindUNot;
    e->val.unary.exp = exp;
    return e;
}

IFSTMT *makeIFSTMT_ifElse(EXP *condition, STMT *true_branch, STMT *false_branch)
{
    IFSTMT *ifstmt = malloc(sizeof(IFSTMT));
    ifstmt->kind = k_ifstmtKindIfElse;
    ifstmt->val.condition = condition;
    ifstmt->val.true_branch = true_branch;
    ifstmt->val.false_branch.stmt_list = false_branch;
    return ifstmt;
}

IFSTMT *makeIFSTMT_ifElseIf(EXP *condition, STMT *true_branch, IFSTMT *false_branch)
{
    IFSTMT *ifstmt = malloc(sizeof(IFSTMT));
    ifstmt->kind = k_ifstmtKindIfElseIf;
    ifstmt->val.condition = condition;
    ifstmt->val.true_branch = true_branch;
    ifstmt->val.false_branch.ifstmt = false_branch;
    return ifstmt;
}

STMT *makeSTMT_declaration(char *identifier, DeclarationType type, EXP *exp)
{
    STMT *stmt = malloc(sizeof(STMT));
    stmt->kind = k_stmtKindDeclaration;
    stmt->val.declaration.identifier = identifier;
    stmt->val.declaration.type = type;
    stmt->val.declaration.exp = exp;
    return stmt;
}

STMT *makeSTMT_read(char *readVar)
{
    STMT *stmt = malloc(sizeof(STMT));
    stmt->kind = k_stmtKindRead;
    stmt->val.readVar = readVar;
    return stmt;
}

STMT *makeSTMT_print(EXP *exp)
{
    STMT *stmt = malloc(sizeof(STMT));
    stmt->kind = k_stmtKindPrint;
    stmt->val.printExp = exp;
    return stmt;
}

STMT *makeSTMT_assign(char *identifier, EXP *exp)
{
    STMT *stmt = malloc(sizeof(STMT));
    stmt->kind = k_stmtKindAssign;
    stmt->val.assign.identifier;
    stmt->val.assign.exp = exp;
    return stmt;
}

STMT *makeSTMT_if(IFSTMT *ifstmt)
{
    STMT *stmt = malloc(sizeof(STMT));
    stmt->kind = k_stmtKindIf;
    stmt->val.ifstmt = ifstmt;
    return stmt;
}

STMT *makeSTMT_while(EXP *condition, STMT *body)
{
    STMT *stmt = malloc(sizeof(STMT));
    stmt->kind = k_stmtKindWhile;
    stmt->val.whilestmt.condition = condition;
    stmt->val.whilestmt.body = body;
    return stmt;
}