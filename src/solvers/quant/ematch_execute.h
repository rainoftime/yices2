/*
 * This file is part of the Yices SMT Solver.
 * Copyright (C) 2017 SRI International.
 *
 * Yices is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Yices is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Yices.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * INSTRUCTION/CODE EXECUTER FOR E-MATCHING
 */

#ifndef __EMATCH_EXECUTE_H
#define __EMATCH_EXECUTE_H

#include "solvers/quant/ematch_compile.h"
#include "solvers/quant/ematch_instr_stack.h"



/*
 * E-match code executer
 */
typedef struct ematch_exec_s {
  ivector_t reg;                // register array
  ematch_stack_t bstack;        // instruction stack

  ematch_compile_t *comp;       // ematch compiler
  ematch_instr_table_t *itbl;   // ematch instruction table
  term_table_t *terms;          // term table

  egraph_t *egraph;             // link to egraph
  intern_tbl_t *intern;         // link to internalization table
} ematch_exec_t;


/*
 * Initialize code executer
 */
extern void init_ematch_exec(ematch_exec_t *exec, ematch_compile_t *comp);

/*
 * Reset code executer
 */
extern void reset_ematch_exec(ematch_exec_t *exec);

/*
 * Delete code executer
 */
extern void delete_ematch_exec(ematch_exec_t *exec);

/*
 * Execute a code sequence corresponding to idx in instruction table
 */
extern void ematch_exec_instr(ematch_exec_t *exec, int32_t idx);

/*
 * Execute the code sequence for a pattern
 */
extern void ematch_exec_pattern(ematch_exec_t *exec, pattern_t *pat);


#endif /* __EMATCH_EXECUTE_H */
