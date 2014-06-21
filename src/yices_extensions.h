/*
 * Extensions of yices.h
 * Implemented in yices_api.c
 */

#ifndef __YICES_EXTENSIONS_H
#define __YICES_EXTENSIONS_H

#include <stdio.h>

#include "terms.h"
#include "bvlogic_buffers.h"
#include "context.h"


/*
 * TYPE VARIABLES/MACROS
 */

/*
 * Create a type variable of the given id
 */
extern type_t yices_type_variable(uint32_t id);

/*
 * Create a type constructor:
 * - name = its name
 * - n = arity
 * return -1 if there's an error or the macro id otherwise
 *
 * Error codes:
 * if n == 0
 *   code = POS_INT_REQUIRED
 *   badval = n
, * if n > TYPE_MACRO_MAX_ARITY
 *   code = TOO_MANY_MACRO_PARAMS
 *   badval = n
 */
extern int32_t yices_type_constructor(const char *name, uint32_t n);

/*
 * Create a type macro:
 * - name = its name
 * - n = arity
 * - vars = array of n distinct type variables
 * - body = type
 *
 * return -1 if there's an error or the macro id otherwise
 *
 * Error codes:
 * if n == 0
 *   code = POS_INT_REQUIRED
 *   badval = n
 * if n > TYPE_MACRO_MAX_ARITY
 *   code = TOO_MANY_MACRO_PARAMS
 *   badval = n
 * if body or one of vars[i] is not a valid type
 *   code = INVALID_TYPE
 *   type1 = body or vars[i]
 * if vars[i] is not a type variable
 *   code = TYPE_VAR_REQUIRED
 *   type1 = vars[i]
 * if the same variable occurs twice or more in vars
 *   code = DUPLICATE_TYPE_VAR
 *   type1 = the duplicate variable
 */
extern int32_t yices_type_macro(const char *name, uint32_t n, type_t *vars, type_t body);


/*
 * Instance of a macro or constructor
 * - cid = constructor or macro id
 * - n = number of arguments
 * - tau[0 ... n-1] = argument types
 *
 * return NULL_TYPE if there's an error
 *
 * Error reports:
 * if cid is not a valid macro or constructor id
 *   code = INVALID_MACRO
 *   badval = cid
 * if n is not the same as the macro/constructor arity
 *   code = WRONG_NUMBER_OF_ARGUMENTS
 *   badval = n
 * if one of tau[i] is not a valid type
 *   code = INVALID_TYPE
 *   type1 = tau[i]
 */
extern type_t yices_instance_type(int32_t cid, uint32_t n, type_t tau[]);

/*
 * Get the macro id for a given name
 * - return -1 if there's no macro or constructor with that name
 */
extern int32_t yices_get_macro_by_name(const char *name);

/*
 * Remove the mapping of name --> macro id
 * - no change if no such mapping exists
 */
extern void yices_remove_type_macro_name(const char *name);

/*
 * Remove a macro with the given id
 * - id must be a valid macro index (non-negative)
 */
extern void yices_delete_type_macro(int32_t id);


/*
 * BUFFER ALLOCATION/FREE
 */

/*
 * All buffer allocation functions can be used only after yices_init() has been called.
 */

/*
 * Allocate and initialize a bvarith_buffer
 * - the buffer is initialized to 0b0...0 (with n bits)
 * - n must be positive and no more than YICES_MAX_BVSIZE
 */
extern bvarith_buffer_t *yices_new_bvarith_buffer(uint32_t n);

/*
 * Free an allocated bvarith_buffer
 */
extern void yices_free_bvarith_buffer(bvarith_buffer_t *b);

/*
 * Allocate and initialize a bvarith64_buffer
 * - the buffer is initialized to 0b0000..0 (with n bits)
 * - n must be between 1 and 64
 */
extern bvarith64_buffer_t *yices_new_bvarith64_buffer(uint32_t n);

/*
 * Free an allocated bvarith64_buffer
 */
extern void yices_free_bvarith64_buffer(bvarith64_buffer_t *b);

/*
 * Allocate and initialize a bvlogic buffer
 * - the buffer is empty (bitsize = 0)
 */
extern bvlogic_buffer_t *yices_new_bvlogic_buffer(void);

/*
 * Free buffer b allocated by the previous function
 */
extern void yices_free_bvlogic_buffer(bvlogic_buffer_t *b);



/*
 * CONVERSION TO TERMS
 */

/*
 * Convert b to a term then reset b.
 * - b must not be empty.
 * - build a bitvector constant if possible
 * - if b is of the form (select 0 t) ... (select k t) and t has bitsize (k+1)
 *   then return t
 * - otherwise build a bitarray term
 */
extern term_t bvlogic_buffer_get_term(bvlogic_buffer_t *b);

/*
 * Normalize b then convert it to a term and reset b
 *
 * if b is reduced to a single variable x, return the term attached to x
 * if b is reduced to a power product, return that
 * if b is constant, build a BV_CONSTANT term
 * if b can be converted to a BV_ARRAY term do it
 * otherwise construct a BV_POLY
 */
extern term_t bvarith_buffer_get_term(bvarith_buffer_t *b);


/*
 * Normalize b then convert it to a term and reset b
 *
 * if b is reduced to a single variable x, return the term attached to x
 * if b is reduced to a power product, return that
 * if b is constant, build a BV64_CONSTANT term
 * if b can be converted to a BV_ARRAY term do it
 * otherwise construct a BV64_POLY
 */
extern term_t bvarith64_buffer_get_term(bvarith64_buffer_t *b);


/*
 * Convert a bitvector constant to a term
 * - n = bitsize (must be more than 64 and at most YICES_MAX_BVSIZE)
 * - v = value as an array of k words (k = ceil(n/32)).
 */
extern term_t yices_bvconst_term(uint32_t n, uint32_t *v);


/*
 * Convert a 64bit constant to a term
 * - n = bitsize (must be positive and no more than 64)
 * - c = constant value (must be normalized modulo 2^n)
 */
extern term_t yices_bvconst64_term(uint32_t n, uint64_t c);


/*
 * Convert rational q to a term
 */
extern term_t yices_rational_term(rational_t *q);



/*
 * SUPPORT FOR TYPE-CHECKING
 */

/*
 * Check whether t is a valid boolean term
 * - if not set the internal error report
 *
 * If t is not a valid term:
 *   code = INVALID_TERM
 *   term1 = t
 *   index = -1
 * If t is not Boolean
 *   code = TYPE_MISMATCH
 *   term1 = t
 *   type = bool
 */
extern bool yices_check_boolean_term(term_t t);

/*
 * Check whether t has a type that match tau (i.e., t's type is a subtype of tau)
 * If not set the error report:
 *   code = TYPE_MISMATCH
 *   term1 = t
 *   type1 = tau
 */
extern bool yices_check_term_type(term_t t, type_t tau);

/*
 * Check whether n <= YICES_MAX_BVSIZE and if not set the error report:
 *   code = MAX_BVSIZE_EXCEEDED
 *   badval = n
 */
extern bool yices_check_bvsize(uint32_t n);

/*
 * Check whether t is a valid bit-vector term
 * - if not set the internal error report.
 *
 * If t is not a valid term:
 *   code = INVALID_TERM
 *   term1 = t
 *   index = -1
 * If t is not an arithmetic term;
 *   code = BITVECTOR_REQUIRED
 *   term1 = t
 */
extern bool yices_check_bv_term(term_t t);

/*
 * Check whether buffer b is non-empty (i.e., can be converted to a term).
 * - return false if b is empty and set the error report (code = EMPTY_BITVECTOR).
 * - return true if b is non-empty.
 */
extern bool yices_check_bvlogic_buffer(bvlogic_buffer_t *b);

/*
 * Checks for degree overflow in bitvector multiplication:
 * - four variants depending on the type of buffer used
 *   and on whether the argument is a term or a buffer
 *
 * In all cases, the function set the error report and
 * return false if there's an overflow:
 *   code = DEGREE_OVEFLOW
 *   badval = degree of the product
 *
 * All return true if there's no overflow.
 */
extern bool yices_check_bvmul64_term(bvarith64_buffer_t *b, term_t t);
extern bool yices_check_bvmul64_buffer(bvarith64_buffer_t *b1, bvarith64_buffer_t *b2);

extern bool yices_check_bvmul_term(bvarith_buffer_t *b, term_t t);
extern bool yices_check_bvmul_buffer(bvarith_buffer_t *b1, bvarith_buffer_t *b2);


/*
 * Check whether s is a valid shift amount for buffer b:
 * - return true if 0 <= s <= b->bitsize
 * - otherwise set the error report and return false.
 */
extern bool yices_check_bitshift(bvlogic_buffer_t *b, int32_t s);


/*
 * Check whether [i, j] is a valid segment for a bitvector of size n
 * - return true if 0 <= i <= j < n
 * - otherwise set the error report and return false.
 */
extern bool yices_check_bvextract(uint32_t n, int32_t i, int32_t j);


/*
 * Check whether repeat_concat(b, n) is valid
 * - return true if 0 <= n and (n * b->bitsize) <= MAX_BVSIZE
 * - return false and set error report otherwise.
 */
extern bool yices_check_bvrepeat(bvlogic_buffer_t *b, int32_t n);


/*
 * Check whether sign_extend(b, n) or zero_extend(b, n) is valid
 * - return true if 0 <= m, b->bitsize != 0 and n + b->bitsize <= MAX_BVSIZE
 * - return false and set error report otherwise.
 */
extern bool yices_check_bvextend(bvlogic_buffer_t *b, int32_t n);

/*
 * CONTEXT INITIALIZATION
 */

/*
 * Return a new context for the given arch, mode, iflag, and qflag.
 * This doesn't use the configuration object, unlike the official
 * yices_new_context declared in yices.h.
 * - arch = architecture to use
 * - mode = which optional features are supported
 * - iflag = true to active the integer solver
 * - qflag = true to support quantifiers
 *
 * The following simplification options are enabled:
 * - variable elimination
 * - eq_abstraction
 * - diseq/or flattening
 * - arithvar and bvarithvar elimination
 */
extern context_t *yices_create_context(context_arch_t arch, context_mode_t mode,
                                       bool iflag, bool qflag);


/*
 * Set default search parameters for ctx (based on architecture and theories)
 * - this is based on benchmarking on the SMT-LIB 1.2 benchmarks (cf. yices_smtcomp.c)
 */
extern void yices_set_default_params(context_t *ctx, param_t *params);



/*
 * TRACE/STATISTICS AND SUPPORT FOR DEBUGGING
 */
extern void yices_print_presearch_stats(FILE *f, context_t *ctx);
extern void yices_show_statistics(FILE *f, context_t *ctx);
extern void yices_dump_context(FILE *f, context_t *ctx);

#endif /* __YICES_EXTENSIONS_H */