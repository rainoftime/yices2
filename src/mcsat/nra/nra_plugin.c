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
 * Anything that includes "yices.h" requires these macros.
 * Otherwise the code doesn't build on Windows or Cygwin.
 */
#if defined(CYGWIN) || defined(MINGW)
#ifndef __YICES_DLLSPEC__
#define __YICES_DLLSPEC__ __declspec(dllexport)
#endif
#endif

#include <poly/polynomial.h>
#include <poly/polynomial_context.h>
#include <poly/variable_db.h>
#include <poly/feasibility_set.h>
#include <poly/variable_order.h>
#include <poly/variable_list.h>
#include <poly/upolynomial.h>

#include "mcsat/nra/nra_plugin.h"
#include "mcsat/nra/nra_plugin_internal.h"
#include "mcsat/nra/libpoly_utils.h"
#include "mcsat/tracing.h"
#include "mcsat/utils/scope_holder.h"
#include "mcsat/utils/int_mset.h"
#include "mcsat/watch_list_manager.h"
#include "mcsat/nra/poly_constraint.h"
#include "mcsat/nra/nra_plugin_explain.h"

#include "terms/terms.h"
#include "utils/int_array_sort2.h"
#include "terms/term_explorer.h"
#include "utils/refcount_strings.h"

#include "api/yices_api_lock_free.h"

static inline
bool nra_plugin_has_assignment(const nra_plugin_t* nra, variable_t x) {
  return trail_has_value(nra->ctx->trail, x) && trail_get_index(nra->ctx->trail, x) < nra->trail_i;
}

static
void nra_plugin_stats_init(nra_plugin_t* nra) {
  // Add statistics
  nra->stats.propagations = statistics_new_int(nra->ctx->stats, "mcsat::nra::propagations");
  nra->stats.conflicts = statistics_new_int(nra->ctx->stats, "mcsat::nra::conflicts");
  nra->stats.conflicts_int = statistics_new_int(nra->ctx->stats, "mcsat::nra::conflicts_int");
  nra->stats.conflicts_assumption = statistics_new_int(nra->ctx->stats, "mcsat::nra::conflicts_assumption");
  nra->stats.constraints_attached = statistics_new_int(nra->ctx->stats, "mcsat::nra::constraints_attached");
  nra->stats.evaluations = statistics_new_int(nra->ctx->stats, "mcsat::nra::evaluations");
  nra->stats.constraint_regular = statistics_new_int(nra->ctx->stats, "mcsat::nra::constraints_regular");
  nra->stats.constraint_root = statistics_new_int(nra->ctx->stats, "mcsat::nra::constraints_root");
}

static
void nra_plugin_heuristics_init(nra_plugin_t* nra) {
  // Initialize heuristic
}

static
void nra_plugin_construct(plugin_t* plugin, plugin_context_t* ctx) {
  nra_plugin_t* nra = (nra_plugin_t*) plugin;

  // OPTIONS NOT AVAILABLE IN CONSTRUCTOR, THEY ARE SETUP LATER

  nra->ctx = ctx;
  nra->last_decided_and_unprocessed = variable_null;
  nra->trail_i = 0;
  nra->conflict_variable = variable_null;

  watch_list_manager_construct(&nra->wlm, ctx->var_db);
  init_int_hmap(&nra->constraint_unit_info, 0);
  init_int_hmap(&nra->constraint_unit_var, 0);

  init_ivector(&nra->processed_variables, 0);
  nra->processed_variables_size = 0;

  scope_holder_construct(&nra->scope);

  init_int_hmap(&nra->lp_data.mcsat_to_lp_var_map, 0);
  init_int_hmap(&nra->lp_data.lp_to_mcsat_var_map, 0);

  init_int_hmap(&nra->evaluation_value_cache, 0);
  init_int_hmap(&nra->evaluation_timestamp_cache, 0);

  init_int_hmap(&nra->feasible_set_cache_top_var[0], 0);
  init_int_hmap(&nra->feasible_set_cache_top_var[1], 0);
  init_int_hmap(&nra->feasible_set_cache_timestamp[0], 0);
  init_int_hmap(&nra->feasible_set_cache_timestamp[1], 0);
  init_ptr_hmap(&nra->feasible_set_cache[0], 0);
  init_ptr_hmap(&nra->feasible_set_cache[1], 0);

  // Constraint db
  nra->constraint_db = poly_constraint_db_new(nra);

  // Feasible sets
  nra->feasible_set_db = feasible_set_db_new(ctx);

  // lipoly init
  nra->lp_data.lp_var_db = lp_variable_db_new();
  nra->lp_data.lp_var_order = lp_variable_order_new();
  nra->lp_data.lp_var_order_size = 0;
  nra->lp_data.lp_ctx = lp_polynomial_context_new(lp_Z, nra->lp_data.lp_var_db, nra->lp_data.lp_var_order);
  nra->lp_data.lp_assignment = lp_assignment_new(nra->lp_data.lp_var_db);

  // Tracing in libpoly
  if (false) {
    lp_trace_enable("coefficient");
    lp_trace_enable("coefficient::roots");
    lp_trace_enable("polynomial");
    lp_trace_enable("polynomial::check_input");
  }

  // Trace pscs
  if (false) {
    lp_trace_enable("polynomial::expensive");
  }

  // Atoms
  ctx->request_term_notification_by_kind(ctx, ARITH_EQ_ATOM);
  ctx->request_term_notification_by_kind(ctx, ARITH_GE_ATOM);
  ctx->request_term_notification_by_kind(ctx, ARITH_BINEQ_ATOM);
  ctx->request_term_notification_by_kind(ctx, ARITH_ROOT_ATOM);
  ctx->request_term_notification_by_kind(ctx, ARITH_MOD);
  ctx->request_term_notification_by_kind(ctx, ARITH_IDIV);
  ctx->request_term_notification_by_kind(ctx, ARITH_RDIV);
  ctx->request_term_notification_by_kind(ctx, ARITH_CEIL);
  ctx->request_term_notification_by_kind(ctx, ARITH_FLOOR);

  // Terms
  ctx->request_term_notification_by_kind(ctx, ARITH_CONSTANT);
  ctx->request_term_notification_by_kind(ctx, ARITH_POLY);
  ctx->request_term_notification_by_kind(ctx, POWER_PRODUCT);

  // Types (we add INT because it's there for ITEs over int constants)
  ctx->request_term_notification_by_type(ctx, REAL_TYPE);
  ctx->request_term_notification_by_type(ctx, INT_TYPE);
  ctx->request_decision_calls(ctx, REAL_TYPE);
  ctx->request_decision_calls(ctx, INT_TYPE);

  init_rba_buffer(&nra->buffer, ctx->terms->pprods);

  nra->conflict_variable = variable_null;
  nra->conflict_variable_int = variable_null;
  nra->conflict_variable_assumption = variable_null;

  nra->global_bound_term = NULL_TERM;

  nra_plugin_stats_init(nra);
  nra_plugin_heuristics_init(nra);
}

static
void nra_plugin_destruct(plugin_t* plugin) {
  nra_plugin_t* nra = (nra_plugin_t*) plugin;

  watch_list_manager_destruct(&nra->wlm);
  delete_int_hmap(&nra->constraint_unit_info);
  delete_int_hmap(&nra->constraint_unit_var);
  delete_ivector(&nra->processed_variables);
  scope_holder_destruct(&nra->scope);

  delete_int_hmap(&nra->lp_data.mcsat_to_lp_var_map);
  delete_int_hmap(&nra->lp_data.lp_to_mcsat_var_map);

  delete_int_hmap(&nra->evaluation_value_cache);
  delete_int_hmap(&nra->evaluation_timestamp_cache);

  delete_int_hmap(&nra->feasible_set_cache_top_var[0]);
  delete_int_hmap(&nra->feasible_set_cache_top_var[1]);
  delete_int_hmap(&nra->feasible_set_cache_timestamp[0]);
  delete_int_hmap(&nra->feasible_set_cache_timestamp[1]);

  // delete feasibility objects
  ptr_hmap_pair_t* it = ptr_hmap_first_record(&nra->feasible_set_cache[0]);
  for (; it != NULL; it = ptr_hmap_next_record(&nra->feasible_set_cache[0], it)) {
    lp_feasibility_set_delete(it->val);
  }
  delete_ptr_hmap(&nra->feasible_set_cache[0]);
  it = ptr_hmap_first_record(&nra->feasible_set_cache[1]);
  for (; it != NULL; it = ptr_hmap_next_record(&nra->feasible_set_cache[1], it)) {
    lp_feasibility_set_delete(it->val);
  }
  delete_ptr_hmap(&nra->feasible_set_cache[1]);

  poly_constraint_db_delete(nra->constraint_db);

  feasible_set_db_delete(nra->feasible_set_db);

  lp_polynomial_context_detach(nra->lp_data.lp_ctx);
  lp_variable_order_detach(nra->lp_data.lp_var_order);
  lp_variable_db_detach(nra->lp_data.lp_var_db);
  lp_assignment_delete(nra->lp_data.lp_assignment);

  delete_rba_buffer(&nra->buffer);
}

static
bool nra_plugin_trail_variable_compare(void *data, variable_t t1, variable_t t2) {
  const mcsat_trail_t* trail;
  bool t1_has_value, t2_has_value;
  uint32_t t1_index, t2_index;

  trail = data;

  // We compare variables based on the trail level, unassigned to the front,
  // then assigned ones by decreasing level

  // Literals with no value
  t1_has_value = trail_has_value(trail, t1);
  t2_has_value = trail_has_value(trail, t2);
  if (!t1_has_value && !t2_has_value) {
    // Both have no value, just order by variable
    return t1 < t2;
  }

  // At least one has a value
  if (!t1_has_value) {
    // t1 < t2, goes to front
    return true;
  }
  if (!t2_has_value) {
    // t2 < t1, goes to front
    return false;
  }

  // Both literals have a value, sort by decreasing level
  t1_index = trail_get_index(trail, t1);
  t2_index = trail_get_index(trail, t2);
  if (t1_index != t2_index) {
    // t1 > t2 goes to front
    return t1_index > t2_index;
  } else {
    return t1 < t2;
  }
}

static
lp_feasibility_set_t* nra_plugin_get_feasible_set(nra_plugin_t* nra, variable_t cstr_var, variable_t cstr_top_var, bool is_negated) {
  // TODO:
  // 1. cache
  // 2. negation
  // 3. only compute if current value doesn't satisfy

  // Check if it is a valid constraints
  const poly_constraint_t* cstr = poly_constraint_db_get(nra->constraint_db, cstr_var);

  // Constraint var list (we only cache if in use)
  if (!watch_list_manager_has_constraint(&nra->wlm, cstr_var)) {
    return poly_constraint_get_feasible_set(cstr, nra->lp_data.lp_assignment, is_negated);
  }
  variable_list_ref_t var_list_ref = watch_list_manager_get_list_of(&nra->wlm, cstr_var);
  const variable_t* var_list = watch_list_manager_get_list(&nra->wlm, var_list_ref);

  // Get the timestamp and level
  uint32_t cstr_timestamp = 0;
  const mcsat_trail_t* trail = nra->ctx->trail;
  const variable_t* var_i = var_list;
  while (*var_i != variable_null) {
    if (nra_plugin_has_assignment(nra, *var_i)) {
      assert(*var_i != cstr_top_var);
      uint32_t timestamp_i = trail_get_value_timestamp(trail, *var_i);
      assert(timestamp_i > 0);
      if (cstr_timestamp < timestamp_i) {
        cstr_timestamp = timestamp_i;
      }
    } else {
      assert(*var_i == cstr_top_var);
    }
    var_i ++;
  }

  // Cached top variable
  int_hmap_t* cache_top_var = &nra->feasible_set_cache_top_var[is_negated];\
  int_hmap_pair_t* find_top_var = int_hmap_get(cache_top_var, cstr_var);
  // Cached timestamp
  int_hmap_t* cache_timestamp = &nra->feasible_set_cache_timestamp[is_negated];
  int_hmap_pair_t* find_timestamp = int_hmap_get(cache_timestamp, cstr_var);
  // Cached feasible set
  ptr_hmap_t* cache = &nra->feasible_set_cache[is_negated];
  ptr_hmap_pair_t* find = ptr_hmap_get(cache, cstr_var);

  // Check if we can use the cached value
  if (find->val != NULL) {
    if (find_top_var->val == cstr_top_var && find_timestamp->val == cstr_timestamp) {
      return lp_feasibility_set_new_copy(find->val);
    }
  }

  // Compute
  lp_feasibility_set_t* feasible = poly_constraint_get_feasible_set(cstr, nra->lp_data.lp_assignment, is_negated);

  // Remember cache
  find_top_var->val = cstr_top_var;
  find_timestamp->val = cstr_timestamp;
  if (find->val != NULL) {
    lp_feasibility_set_delete(find->val);
  }
  find->val = feasible;

  // Done
  return lp_feasibility_set_new_copy(feasible);
}

static
const mcsat_value_t* nra_plugin_constraint_evaluate(nra_plugin_t* nra, variable_t cstr_var, uint32_t* cstr_level) {

  assert(!trail_has_value(nra->ctx->trail, cstr_var));

  if (ctx_trace_enabled(nra->ctx, "nra::evaluate")) {
    trail_print(nra->ctx->trail, ctx_trace_out(nra->ctx));
  }

  // Check if it is a valid constraints
  const poly_constraint_t* cstr = poly_constraint_db_get(nra->constraint_db, cstr_var);
  if (!poly_constraint_is_valid(cstr)) {
    return NULL;
  }

  // Constraint var list
  variable_list_ref_t var_list_ref = watch_list_manager_get_list_of(&nra->wlm, cstr_var);
  const variable_t* var_list = watch_list_manager_get_list(&nra->wlm, var_list_ref);

  // Get the timestamp and level
  uint32_t cstr_timestamp = 0;
  *cstr_level = nra->ctx->trail->decision_level_base;
  const mcsat_trail_t* trail = nra->ctx->trail;
  const variable_t* var_i = var_list;
  while (*var_i != variable_null) {
    if (nra_plugin_has_assignment(nra, *var_i)) {
      uint32_t timestamp_i = trail_get_value_timestamp(trail, *var_i);
      assert(timestamp_i > 0);
      if (cstr_timestamp < timestamp_i) {
        cstr_timestamp = timestamp_i;
      }
      uint32_t level_i = trail_get_level(trail, *var_i);
      if (level_i > *cstr_level) {
        *cstr_level = level_i;
      }
    } else {
      // Doesn't evaluate
      return NULL;
    }
    var_i ++;
  }

  bool cstr_value = false;

  // Check the cache
  int_hmap_pair_t* find_value = int_hmap_find(&nra->evaluation_value_cache, cstr_var);
  int_hmap_pair_t* find_timestamp = NULL;
  if (find_value != NULL) {
    find_timestamp = int_hmap_find(&nra->evaluation_timestamp_cache, cstr_var);
    assert(find_timestamp != NULL);
    if (find_timestamp->val == cstr_timestamp) {
      // Can use the cached value;
      cstr_value = find_value->val;
      return cstr_value ? &mcsat_value_true : &mcsat_value_false;
    }
  }

  // NOTE: with/without caching can change search. Some poly constraints
  // do not evaluate (see ok below, but we can evaluate them in the cache)

  // Compute the evaluation
  bool ok = poly_constraint_evaluate(cstr, nra, &cstr_value);
  (void) ok;
  assert(ok);
  (*nra->stats.evaluations) ++;

  // Set the cache
  if (find_value != NULL) {
    find_value->val = cstr_value;
    find_timestamp->val = cstr_timestamp;
  } else {
    int_hmap_add(&nra->evaluation_value_cache, cstr_var, cstr_value);
    int_hmap_add(&nra->evaluation_timestamp_cache, cstr_var, cstr_timestamp);
  }

  return cstr_value ? &mcsat_value_true : &mcsat_value_false;
}

static
void nra_plugin_process_fully_assigned_constraint(nra_plugin_t* nra, trail_token_t* prop, variable_t cstr_var) {

  uint32_t cstr_level = 0;
  const mcsat_value_t* cstr_value = NULL;

  assert(!trail_has_value(nra->ctx->trail, cstr_var));

  if (ctx_trace_enabled(nra->ctx, "nra::evaluate")) {
    trail_print(nra->ctx->trail, ctx_trace_out(nra->ctx));
  }

  // Compute the evaluation timestamp
  cstr_value = nra_plugin_constraint_evaluate(nra, cstr_var, &cstr_level);

  // Propagate
  if (cstr_value) {
    bool ok = prop->add_at_level(prop, cstr_var, cstr_value, cstr_level);
    (void)ok;
    assert(ok);
  }

  if (ctx_trace_enabled(nra->ctx, "nra::evaluate")) {
    trail_print(nra->ctx->trail, ctx_trace_out(nra->ctx));
  }
}

static
void nra_plugin_new_term_notify(plugin_t* plugin, term_t t, trail_token_t* prop) {

  uint32_t i;
  nra_plugin_t* nra = (nra_plugin_t*) plugin;
  term_table_t* terms = nra->ctx->terms;

  if (ctx_trace_enabled(nra->ctx, "mcsat::new_term")) {
    ctx_trace_printf(nra->ctx, "nra_plugin_new_term_notify: ");
    ctx_trace_term(nra->ctx, t);
  }

  assert(!is_neg_term(t));

  term_kind_t t_kind = term_kind(terms, t);

  // Only process power terms if they are real ones
  if (t_kind == POWER_PRODUCT && !is_arithmetic_term(terms, t)) {
    return;
  }

  // The variable
  variable_t t_var = variable_db_get_variable(nra->ctx->var_db, t);

  // Check for div and mod
  if (t_kind == ARITH_MOD) {
    // Just make sure that the div is registered
    composite_term_t* mod = arith_mod_term_desc(terms, t);
    term_t a = mod->arg[0];
    term_t b = mod->arg[1];
    term_t t_div = arith_idiv(terms, a, b);
    variable_db_get_variable(nra->ctx->var_db, t_div);
    return;
  }
  if (t_kind == ARITH_IDIV) {
    // Make sure that mod has a variable
    composite_term_t* div = arith_idiv_term_desc(terms, t);
    term_t q = t;
    term_t m = div->arg[0];
    term_t n = div->arg[1];
    term_t r = arith_mod(terms, m, n);
    variable_db_get_variable(nra->ctx->var_db, r);

    // Add a lemma (assuming non-zero):
    // (div m n)
    // (and (= m (+ (* n q) r)) (<= 0 r (- (abs n) 1))))))
    term_t guard = opposite_term(_o_yices_arith_eq0_atom(n));
    term_t c1 = _o_yices_eq(m, _o_yices_add(_o_yices_mul(n, q), r));
    term_t c2 = arith_geq_atom(terms, r);
    // r < (abs n) same as not (r - abs) >= 0
    term_t abs_n = _o_yices_ite(_o_yices_arith_geq0_atom(n), n, _o_yices_neg(n));
    term_t c3 = opposite_term(arith_geq_atom(terms, _o_yices_sub(r, abs_n)));

    prop->lemma(prop, _o_yices_implies(guard, c1));
    prop->lemma(prop, _o_yices_implies(guard, c2));
    prop->lemma(prop, _o_yices_implies(guard, c3));
    return;
  }
  if (t_kind == ARITH_RDIV) {
    composite_term_t* div = arith_rdiv_term_desc(terms, t);
    term_t q = t;
    term_t m = div->arg[0];
    term_t n = div->arg[1];

    // Add a lemma (assuming non-zero):
    // (n != 0) => m = n*q
    // (and (= m (+ (* n q) r)) (<= 0 r (- (abs n) 1))))))
    term_t guard = opposite_term(_o_yices_arith_eq0_atom(n));
    term_t c = _o_yices_eq(m, _o_yices_mul(n, q));
    prop->lemma(prop, _o_yices_implies(guard, c));
    return;
  }

  // Check for floor, ceil
  if (t_kind == ARITH_FLOOR) {
    term_t arg = arith_floor_arg(terms, t);

    // t <= arg < t+1: t is int so it should be fine
    term_t ineq1 = _o_yices_arith_geq_atom(arg, t);
    term_t t_1 = _o_yices_add(t, _o_yices_rational32(1, 1));
    term_t ineq2 = _o_yices_arith_gt_atom(t_1, arg);

    prop->lemma(prop, ineq1);
    prop->lemma(prop, ineq2);
    return;
  }

  // Check for floor, ceil
  if (t_kind == ARITH_CEIL) {
    term_t arg = arith_ceil_arg(terms, t);

    // t-1 < arg <= t: t is int so it should be fine
    term_t t_1 = _o_yices_sub(t, _o_yices_rational32(1, 1));
    term_t ineq1 = _o_yices_arith_gt_atom(arg, t_1);
    term_t ineq2 = _o_yices_arith_geq_atom(t, arg);

    prop->lemma(prop, ineq1);
    prop->lemma(prop, ineq2);
    return;
  }

  // The vector to collect variables
  int_mset_t t_variables;
  int_mset_construct(&t_variables, variable_null);
  nra_plugin_get_constraint_variables(nra, t, &t_variables);

  // Examples:
  // - x: t_variables = [x]
  // - 5: t_variables = [5]
  // - x+1: t_variables = [x+1, x]
  // - (x = 0): t_variables = [x]
  // We're a constraint if
  bool is_constraint = t_variables.element_list.size != 1 || t_variables.element_list.data[0] != t_var;

  // Setup the constraint
  if (is_constraint) {

    // Get the list of variables
    ivector_t* t_variables_list = int_mset_get_list(&t_variables);

    assert(t_variables_list->size > 0);

    // Register all the variables to libpoly (these are mcsat_variables)
    for (i = 0; i < t_variables_list->size; ++ i) {
      if (!nra_plugin_variable_has_lp_variable(nra, t_variables_list->data[i])) {
        nra_plugin_add_lp_variable(nra, t_variables_list->data[i]);
      }
    }

    // Bump variables
    for (i = 0; i < t_variables_list->size; ++ i) {
      variable_t x = t_variables_list->data[i];
      uint32_t deg = int_mset_contains(&t_variables, x);
      nra->ctx->bump_variable_n(nra->ctx, x, deg);
    }

    // Sort variables by trail index
    int_array_sort2(t_variables_list->data, t_variables_list->size, (void*) nra->ctx->trail, nra_plugin_trail_variable_compare);

    if (ctx_trace_enabled(nra->ctx, "mcsat::new_term")) {
      ctx_trace_printf(nra->ctx, "nra_plugin_new_term_notify: vars: \n");
      for (i = 0; i < t_variables_list->size; ++ i) {
        ctx_trace_term(nra->ctx, variable_db_get_term(nra->ctx->var_db, t_variables_list->data[i]));
      }
    }

    // Make the variable list
    variable_list_ref_t var_list = watch_list_manager_new_list(&nra->wlm, t_variables_list->data, t_variables_list->size, t_var);

    // Add first variable to watch list
    watch_list_manager_add_to_watch(&nra->wlm, var_list, t_variables_list->data[0]);

    // Add second variable to watch list
    if (t_variables_list->size > 1) {
      watch_list_manager_add_to_watch(&nra->wlm, var_list, t_variables_list->data[1]);
    }

    // Check the current status of the constraint
    variable_t top_var = t_variables_list->data[0];
    constraint_unit_info_t unit_status = CONSTRAINT_UNKNOWN;
    if (nra_plugin_has_assignment(nra, top_var)) {
      // All variables assigned,
      unit_status = CONSTRAINT_FULLY_ASSIGNED;
    } else {
      if (t_variables_list->size == 1) {
        // Single variable, unassigned => unit
        unit_status = CONSTRAINT_UNIT;
      } else if (nra_plugin_has_assignment(nra, t_variables_list->data[1])) {
        // Second one is assigned and processed, so we're unit
        unit_status = CONSTRAINT_UNIT;
      }
    }

    // Set the status of the constraint
    nra_plugin_set_unit_info(nra, t_var, unit_status == CONSTRAINT_UNIT ? top_var : variable_null, unit_status);

    // Add the constraint to the database
    poly_constraint_db_add(nra->constraint_db, t_var);

    // Propagate if fully assigned
    if (unit_status == CONSTRAINT_FULLY_ASSIGNED) {
      nra_plugin_process_fully_assigned_constraint(nra, prop, t_var);
    }

    // Stats
    (*nra->stats.constraints_attached) ++;
  } else {
    // Add the variable to libpoly if not a constant
    if (t_kind != ARITH_CONSTANT) {
      if (!nra_plugin_term_has_lp_variable(nra, t)) {
        nra_plugin_add_lp_variable_from_term(nra, t);
      }

      if (nra->ctx->options->nra_bound) {

        if (nra->global_bound_term == NULL_TERM) {
          term_table_t* terms = nra->ctx->terms;
          type_t reals = int_type(terms->types);
          nra->global_bound_term = new_uninterpreted_term(terms, reals);
          set_term_name(terms, nra->global_bound_term, clone_string("__mcsat_B"));
        }

        // Add bound lemma b - t >= 0 && t + b >= 0
        term_t ub_term = _o_yices_sub(nra->global_bound_term, t);
        term_t lb_term = _o_yices_add(nra->global_bound_term, t);
        term_t ub = _o_yices_arith_geq0_atom(ub_term);
        term_t lb = _o_yices_arith_geq0_atom(lb_term);
        prop->lemma(prop, ub);
        prop->lemma(prop, lb);

        // If we are at bound variable, set it as main decision
        if (t == nra->global_bound_term) {
          nra->ctx->request_top_decision(nra->ctx, t_var);
          if (nra->ctx->options->nra_bound_min >= 0) {
            rational_t q;
            q_init(&q);
            q_set32(&q, nra->ctx->options->nra_bound_min);
            term_t min = mk_arith_constant(nra->ctx->tm, &q);
            term_t min_bound = _o_yices_arith_geq_atom(nra->global_bound_term, min);
            prop->lemma(prop, min_bound);
            q_clear(&q);
          }
          if (nra->ctx->options->nra_bound_max >= 0) {
            rational_t q;
            q_init(&q);
            q_set32(&q, nra->ctx->options->nra_bound_max);
            term_t max = mk_arith_constant(nra->ctx->tm, &q);
            term_t max_bound = _o_yices_arith_leq_atom(nra->global_bound_term, max);
            prop->lemma(prop, max_bound);
            q_clear(&q);
          }
        }
      }

    } else {
      // Propagate constant value
      lp_rational_t rat_value;
      lp_rational_construct(&rat_value);
      q_get_mpq(rational_term_desc(terms, t), &rat_value);
      lp_value_t lp_value;
      lp_value_construct(&lp_value, LP_VALUE_RATIONAL, &rat_value);
      mcsat_value_t mcsat_value;
      mcsat_value_construct_lp_value(&mcsat_value, &lp_value);
      prop->add_at_level(prop, t_var, &mcsat_value, nra->ctx->trail->decision_level_base);
      mcsat_value_destruct(&mcsat_value);
      lp_value_destruct(&lp_value);
      lp_rational_destruct(&rat_value);
    }
  }

  // Remove the variables vector
  int_mset_destruct(&t_variables);
}

static
void nra_plugin_process_unit_constraint(nra_plugin_t* nra, trail_token_t* prop, variable_t constraint_var) {

  bool feasible;

  if (ctx_trace_enabled(nra->ctx, "nra::propagate")) {
    ctx_trace_printf(nra->ctx, "nra: processing unit constraint :\n");
    ctx_trace_term(nra->ctx, variable_db_get_term(nra->ctx->var_db, constraint_var));
  }

  // Process if constraint is assigned, or an evaluation constraint
  bool is_eval_constraint = !variable_db_is_boolean(nra->ctx->var_db, constraint_var);
  if (is_eval_constraint || trail_has_value(nra->ctx->trail, constraint_var)) {
    // Get the constraint value
    bool constraint_value = is_eval_constraint || trail_get_value(nra->ctx->trail, constraint_var)->b;

    // Get the constraint
    const poly_constraint_t* constraint = poly_constraint_db_get(nra->constraint_db, constraint_var);
    if (!poly_constraint_is_valid(constraint)) {
      return;
    }

    // Variable of the constraint
    int_hmap_pair_t* x_find = int_hmap_find(&nra->constraint_unit_var, constraint_var);
    variable_t x = x_find->val;

    lp_feasibility_set_t* constraint_feasible = nra_plugin_get_feasible_set(nra, constraint_var, x, !constraint_value);

    if (ctx_trace_enabled(nra->ctx, "nra::propagate")) {
      ctx_trace_printf(nra->ctx, "nra: constraint_feasible = ");
      lp_feasibility_set_print(constraint_feasible, ctx_trace_out(nra->ctx));
      ctx_trace_printf(nra->ctx, "\n");
    }

    // Update the infeasible intervals
    feasible = feasible_set_db_update(nra->feasible_set_db, x, constraint_feasible, &constraint_var, 1);

    if (ctx_trace_enabled(nra->ctx, "nra::propagate")) {
      ctx_trace_printf(nra->ctx, "nra: new feasible = ");
      lp_feasibility_set_print(feasible_set_db_get(nra->feasible_set_db, x), ctx_trace_out(nra->ctx));
      ctx_trace_printf(nra->ctx, "\n");
    }

    // If the intervals are empty, we have a conflict
    if (!feasible) {
      nra_plugin_report_conflict(nra, prop, x);
    } else {
      // If the variable is integer, check that is has an integer solution
      if (nra->conflict_variable_int == variable_null && variable_db_is_int(nra->ctx->var_db, x)) {
        // Check if there is an integer value
        lp_value_t v;
        lp_value_construct_none(&v);
        lp_feasibility_set_pick_value(feasible_set_db_get(nra->feasible_set_db, x), &v);
        if (!lp_value_is_integer(&v)) {
          nra->conflict_variable_int = x;
        }
        lp_value_destruct(&v);
      }
      // If the value is implied at zero level, propagate it
      if (!trail_has_value(nra->ctx->trail, x) && trail_is_at_base_level(nra->ctx->trail)) {
        const lp_feasibility_set_t* feasible = feasible_set_db_get(nra->feasible_set_db, x);
        if (lp_feasibility_set_is_point(feasible)) {
          lp_value_t x_value;
          lp_value_construct_none(&x_value);
          lp_feasibility_set_pick_value(feasible, &x_value);
          mcsat_value_t value;
          mcsat_value_construct_lp_value(&value, &x_value);
          prop->add_at_level(prop, x, &value, nra->ctx->trail->decision_level_base);
          mcsat_value_destruct(&value);
          lp_value_destruct(&x_value);
        }
      }
    }
  }
}

/**
 * The variable has been assigned, look for constraints that become unit.
 */
static
void nra_plugin_process_variable_assignment(nra_plugin_t* nra, trail_token_t* prop, variable_t var) {

  remove_iterator_t it;
  variable_list_ref_t var_list_ref;
  variable_t* var_list;
  variable_t* var_list_it;

  // The trail
  const mcsat_trail_t* trail = nra->ctx->trail;

  assert(trail_is_consistent(trail));

  // Mark the variable as processed
  ivector_push(&nra->processed_variables, var);
  nra->processed_variables_size ++;

  // Check if we have processed our last decision
  if (var == nra->last_decided_and_unprocessed) {
    nra->last_decided_and_unprocessed = variable_null;
  }

  if (ctx_trace_enabled(nra->ctx, "nra::propagate")) {
    ctx_trace_printf(nra->ctx, "nra: processing var assignment of :\n");
    ctx_trace_term(nra->ctx, variable_db_get_term(nra->ctx->var_db, var));
  }

  // If it's constant, just skip it
  if (!nra_plugin_variable_has_lp_variable(nra, var)) {
    return;
  }

  // Add to the lp model and context
  lp_variable_t lp_var = nra_plugin_get_lp_variable(nra, var);
  lp_assignment_set_value(nra->lp_data.lp_assignment, lp_var, &trail_get_value(trail, var)->lp_value);
  lp_variable_order_push(nra->lp_data.lp_var_order, lp_var);
  nra->lp_data.lp_var_order_size ++;

  if (ctx_trace_enabled(nra->ctx, "nra::propagate")) {
    ctx_trace_printf(nra->ctx, "nra: var order :");
    lp_variable_order_print(nra->lp_data.lp_var_order, nra->lp_data.lp_var_db, ctx_trace_out(nra->ctx));
    ctx_trace_printf(nra->ctx, "\n");
  }

  if (ctx_trace_enabled(nra->ctx, "nra::wlm")) {
    watch_list_manager_print(&nra->wlm, ctx_trace_out(nra->ctx));
  }

  // Get the watch-list
  remove_iterator_construct(&it, &nra->wlm, var);

  // Go through all constraints where this variable appears
  while (!remove_iterator_done(&it)) {

    // Get the variables of the constraint
    var_list_ref = remove_iterator_get_list_ref(&it);
    var_list = watch_list_manager_get_list(&nra->wlm, var_list_ref);

    // Constraint variable
    variable_t constraint_var = watch_list_manager_get_constraint(&nra->wlm, var_list_ref);

    if (ctx_trace_enabled(nra->ctx, "nra::propagate")) {
      ctx_trace_printf(nra->ctx, "nra: processing constraint :");
      ctx_trace_term(nra->ctx, variable_db_get_term(nra->ctx->var_db, constraint_var));

      ctx_trace_printf(nra->ctx, "nra: var_list :");
      var_list_it = var_list;
      while (*var_list_it != variable_null) {
        ctx_trace_term(nra->ctx, variable_db_get_term(nra->ctx->var_db, *var_list_it));
        var_list_it ++;
      }
    }

    // Put the variable to [1] so that [0] is the unit one
    if (var_list[0] == var && var_list[1] != variable_null) {
      var_list[0] = var_list[1];
      var_list[1] = var;
    }

    // Find a new watch (start from [2], increase in for loop again!)
    var_list_it = var_list + 1;
    if (*var_list_it != variable_null) {
      for (++ var_list_it; *var_list_it != variable_null; ++ var_list_it) {
        if (!nra_plugin_has_assignment(nra, *var_list_it)) {
          // Swap with var_list[1]
          var_list[1] = *var_list_it;
          *var_list_it = var;
          // Add to new watch
          watch_list_manager_add_to_watch(&nra->wlm, var_list_ref, var_list[1]);
          // Don't watch this one
          remove_iterator_next_and_remove(&it);
          break;
        }
      }
    }

    if (*var_list_it == variable_null) {
      if (ctx_trace_enabled(nra->ctx, "nra::propagate")) {
        ctx_trace_printf(nra->ctx, "no watch found\n");
      }
      if (!nra_plugin_has_assignment(nra, *var_list)) {
        // We're unit
        nra_plugin_set_unit_info(nra, constraint_var, *var_list, CONSTRAINT_UNIT);
        // Process the constraint
        if (trail_is_consistent(trail)) {
          nra_plugin_process_unit_constraint(nra, prop, constraint_var);
        }
      } else {
        // Fully assigned
        nra_plugin_set_unit_info(nra, constraint_var, variable_null, CONSTRAINT_FULLY_ASSIGNED);
        // Evaluate the constraint and propagate (if not assigned already)
        if (trail_is_consistent(trail) && !trail_has_value(trail, constraint_var)) {
          nra_plugin_process_fully_assigned_constraint(nra, prop, constraint_var);
        }
      }
      // Keep the watch
      remove_iterator_next_and_keep(&it);
    }
  }

  // Done, destruct the iterator
  remove_iterator_destruct(&it);
}


static
void nra_plugin_check_assignment(nra_plugin_t* nra) {

  const mcsat_trail_t* trail = nra->ctx->trail;

  // Go through the trail and check if all assigned are in lp_assignment
  uint32_t i;
  for (i = 0; i < trail->elements.size; ++ i) {
    variable_t x = trail->elements.data[i];
    if (x == nra->last_decided_and_unprocessed) {
      continue;
    }
    const mcsat_value_t* value = trail_get_value(trail, x);
    if (value->type == VALUE_LIBPOLY && nra_plugin_has_assignment(nra, x)) {
      lp_variable_t x_lp = nra_plugin_get_lp_variable(nra, x);
      const lp_value_t* value_lp = lp_assignment_get_value(nra->lp_data.lp_assignment, x_lp);
      int cmp = lp_value_cmp(&value->lp_value, value_lp);
      (void)cmp;
      assert(cmp == 0);
    }
  }

  // Go through lp_assignment and check if they are assigned in trail
  const lp_variable_list_t* order = lp_variable_order_get_list(nra->lp_data.lp_var_order);
  for (i = 0; i < order->list_size; ++ i) {
    lp_variable_t x_lp = order->list[i];
    variable_t x = nra_plugin_get_variable_from_lp_variable(nra, x_lp);
    const mcsat_value_t* value = trail_get_value(trail, x);
    const lp_value_t* value_lp = lp_assignment_get_value(nra->lp_data.lp_assignment, x_lp);
    int cmp = lp_value_cmp(&value->lp_value, value_lp);
    (void)cmp;
    assert(cmp == 0);
  }
}


/**
 * Propagates the trail with BCP. When done, either the trail is fully
 * propagated, or the trail is in an inconsistent state.
 */
static
void nra_plugin_propagate(plugin_t* plugin, trail_token_t* prop) {
  nra_plugin_t* nra = (nra_plugin_t*) plugin;

  variable_t var;

  if (ctx_trace_enabled(nra->ctx, "nra::check_assignment")) {
    nra_plugin_check_assignment(nra);
  }

  // Context
  const mcsat_trail_t* trail = nra->ctx->trail;
  variable_db_t* var_db = nra->ctx->var_db;

  if (ctx_trace_enabled(nra->ctx, "nra::propagate")) {
    ctx_trace_printf(nra->ctx, "trail:\n");
    trail_print(trail, nra->ctx->tracer->file);
  }

  // Propagate
  while(trail_is_consistent(trail) && nra->trail_i < trail_size(trail)) {
    // Current trail element
    var = trail_at(trail, nra->trail_i);
    nra->trail_i ++;
    if (variable_db_is_real(var_db, var) || variable_db_is_int(var_db, var)) {
      // Real variables, detect if the constraint is unit
      nra_plugin_process_variable_assignment(nra, prop, var);
    }
    if (nra_plugin_get_unit_info(nra, var) == CONSTRAINT_UNIT) {
      // Process any unit constraints
      nra_plugin_process_unit_constraint(nra, prop, var);
    }
  }

  if (trail_is_consistent(trail) && nra->conflict_variable_int != variable_null) {
    nra_plugin_report_int_conflict(nra, prop, nra->conflict_variable_int);
  }

  if (ctx_trace_enabled(nra->ctx, "nra::check_assignment")) {
    nra_plugin_check_assignment(nra);
  }
}

static
void nra_plugin_decide(plugin_t* plugin, variable_t x, trail_token_t* decide_token, bool must) {
  nra_plugin_t* nra = (nra_plugin_t*) plugin;

  assert(variable_db_is_real(nra->ctx->var_db, x) || variable_db_is_int(nra->ctx->var_db, x));

  // Get the feasibility set
  lp_feasibility_set_t* feasible = feasible_set_db_get(nra->feasible_set_db, x);

  if (ctx_trace_enabled(nra->ctx, "nra::decide")) {
    ctx_trace_printf(nra->ctx, "decide on ");
    variable_db_print_variable(nra->ctx->var_db, x, ctx_trace_out(nra->ctx));
    ctx_trace_printf(nra->ctx, "[%d] at level %d\n", x, nra->ctx->trail->decision_level);
    if (feasible) {
      ctx_trace_printf(nra->ctx, "feasible :");
      feasible_set_db_print_var(nra->feasible_set_db, x, ctx_trace_out(nra->ctx));
      ctx_trace_printf(nra->ctx, "\n");
    } else {
      ctx_trace_printf(nra->ctx, "feasible : ALL\n");
    }
  }

  // Pick a value from the set
  lp_value_t x_new_lpvalue;
  lp_rational_t x_value_default;
  lp_rational_construct_from_int(&x_value_default, 0, 1);
  lp_value_construct(&x_new_lpvalue, LP_VALUE_RATIONAL, &x_value_default);
  lp_rational_destruct(&x_value_default);

  // See if the cached value fits
  bool using_cached = false;
  const mcsat_value_t* x_cached_value = NULL;
  if (trail_has_cached_value(nra->ctx->trail, x)) {
    x_cached_value = trail_get_cached_value(nra->ctx->trail, x);
    if (feasible == NULL || lp_feasibility_set_contains(feasible, &x_cached_value->lp_value)) {
      using_cached = true;
    }
  }

  // If the set is 0, we can pick any value, including 0
  if (!using_cached && feasible != NULL) {
    // Otherwise pick from the set
    lp_feasibility_set_pick_value(feasible, &x_new_lpvalue);
  }

  // Decide if not too complex of a rational number
  bool decide = true;
  if (!must) {
    if (!lp_value_is_rational(&x_new_lpvalue)) {
      if (lp_upolynomial_degree(x_new_lpvalue.value.a.f) > 2) {
        decide = false;
      }
    }
  }

  if (decide) {

    if (ctx_trace_enabled(nra->ctx, "nra::decide")) {
      ctx_trace_printf(nra->ctx, "decided on ");
      variable_db_print_variable(nra->ctx->var_db, x, ctx_trace_out(nra->ctx));
      ctx_trace_printf(nra->ctx, "[%d]: ", x);
      if (using_cached) {
        mcsat_value_print(x_cached_value, ctx_trace_out(nra->ctx));
      } else {
        lp_value_print(&x_new_lpvalue, ctx_trace_out(nra->ctx));
      }
      ctx_trace_printf(nra->ctx, "\n");
    }

    // Make an mcsat value
    mcsat_value_t to_decide_value;
    if (!using_cached) {
      mcsat_value_construct_lp_value(&to_decide_value, &x_new_lpvalue);
      if (variable_db_is_int(nra->ctx->var_db, x)) {
        assert(lp_value_is_integer(&x_new_lpvalue));
      }
    }

    // Decide the to_decide_value
    const mcsat_value_t* to_decide_value_ptr = using_cached ? x_cached_value : &to_decide_value;
    decide_token->add(decide_token, x, to_decide_value_ptr);

    // Remember that we've decided this guy
    nra->last_decided_and_unprocessed = x;

    if (!using_cached) {
      mcsat_value_destruct(&to_decide_value);
    }
  }

  lp_value_destruct(&x_new_lpvalue);
}

/**
 * Check conflicts in core (set of variables).
 */
static
void nra_plugin_check_conflict(nra_plugin_t* nra, ivector_t* core) {
  uint32_t i;

  static uint32_t count = 0;
  count ++;

  fprintf(stderr, "CONFLICT %u\n", count);

  char filename[100];
  sprintf(filename, "conflict_%u.m", count);

  FILE* out = fopen(filename, "w");
  if (out == NULL) {
    fprintf(stderr, "Can't open %s.", filename);
    return;
  }

  // Variables in the conflict
  int_mset_t core_vars;
  int_mset_construct(&core_vars, variable_null);

  // The trail
  const mcsat_trail_t* trail = nra->ctx->trail;

  // Variable database
  const variable_db_t* var_db = nra->ctx->var_db;

  // Get the constraint variables
  for (i = 0; i < core->size; ++ i) {
    variable_t constraint_var = core->data[i];
    term_t constraint_term = variable_db_get_term(var_db, constraint_var);
    nra_plugin_get_constraint_variables(nra, constraint_term, &core_vars);
  }

  // Variables in the assignment
  ivector_t* core_vars_list = int_mset_get_list(&core_vars);

  lp_variable_t free_var = lp_variable_null;

  // Variable assignment
  for (i = 0; i < core_vars_list->size; ++ i) {
    variable_t x = core_vars_list->data[i];
    // Don't consider ones we didn't process yet
    if (x == nra->last_decided_and_unprocessed) {
      continue;
    }
    lp_variable_t x_lp = nra_plugin_get_lp_variable(nra, x);
    // Ignore unassigned too
    if (!trail_has_value(trail, x)) {
      assert(free_var == lp_variable_null);
      free_var = x_lp;
      continue;
    }
    const mcsat_value_t* x_value = trail_get_value(trail, x);
    switch (x_value->type) {
    case VALUE_NONE:
      assert(free_var == lp_variable_null);
      free_var = x_lp;
      continue;
      break;
    case VALUE_LIBPOLY: {
      fprintf(out, "x%zu = ", x_lp);
      const lp_value_t* x_value_lp = &x_value->lp_value;
#ifndef NDEBUG
      const lp_value_t* x_value_lp_in_assignment = lp_assignment_get_value(nra->lp_data.lp_assignment, x_lp);
      assert(lp_value_cmp(x_value_lp, x_value_lp_in_assignment) == 0);
#endif
      if (lp_value_is_rational(x_value_lp)) {
        lp_rational_t q;
        lp_rational_construct(&q);
        lp_value_get_rational(x_value_lp, &q);
        lp_rational_print(&q, out);
        lp_rational_destruct(&q);
      } else {
        lp_value_print(x_value_lp, out);
      }
      fprintf(out, "\n");
      break;
    }
    default:
      assert(false);
    }
  }

  fprintf(out, "check = ");
  if (free_var != lp_variable_null) {
    fprintf(out, "Resolve[Exists[{x%zu},", free_var);
  }

  // Constraints
  for (i = 0; i < core->size; ++ i) {
    fprintf(out, "\\\n\t");
    if (i) {
      fprintf(out, "&& ");
    }
    variable_t constraint_var = core->data[i];
    const poly_constraint_t* constraint = poly_constraint_db_get(nra->constraint_db, constraint_var);
    bool constraint_value = trail_get_boolean_value(trail, constraint_var);
    poly_constraint_print_mathematica(constraint, !constraint_value, out);
  }

  if (free_var != lp_variable_null) {
    fprintf(out, "]]\n");
  } else {
    fprintf(out, "\n");
  }

  fclose(out);
  int_mset_destruct(&core_vars);
}

static
void nra_plugin_get_real_conflict(nra_plugin_t* nra, const int_mset_t* pos, const int_mset_t* neg,
    variable_t x, ivector_t* conflict) {
  size_t i;

  if (ctx_trace_enabled(nra->ctx, "nra::conflict")) {
    ctx_trace_printf(nra->ctx, "nra_plugin_get_conflict(): ");
    ctx_trace_term(nra->ctx, variable_db_get_term(nra->ctx->var_db, x));
  }

  // The assertions on x that are in conflict (as constraint variables)
  ivector_t core, lemma_reasons;
  init_ivector(&core, 0);
  init_ivector(&lemma_reasons, 0);
  feasible_set_db_get_conflict_reasons(nra->feasible_set_db, nra, x, NULL, &core, &lemma_reasons);

  if (ctx_trace_enabled(nra->ctx, "nra::conflict")) {
    ctx_trace_printf(nra->ctx, "nra_plugin_get_conflict(): core:\n");
    for (i = 0; i < core.size; ++ i) {
      ctx_trace_printf(nra->ctx, "[%zu] (", i);
      if (trail_has_value(nra->ctx->trail, core.data[i])) {
        mcsat_value_print(trail_get_value(nra->ctx->trail, core.data[i]), ctx_trace_out(nra->ctx));
      }
      ctx_trace_printf(nra->ctx, "): ");
      ctx_trace_term(nra->ctx, variable_db_get_term(nra->ctx->var_db, core.data[i]));
    }
  }

  if (ctx_trace_enabled(nra->ctx, "nra::check_conflict")) {
    nra_plugin_check_conflict(nra, &core);
  }

  // Project
  nra_plugin_explain_conflict(nra, pos, neg, &core, &lemma_reasons, conflict);

  if (ctx_trace_enabled(nra->ctx, "nra::conflict")) {
    ctx_trace_printf(nra->ctx, "nra_plugin_get_conflict(): conflict:\n");
    for (i = 0; i < conflict->size; ++ i) {
      ctx_trace_printf(nra->ctx, "[%zu]: ", i);
      ctx_trace_term(nra->ctx, conflict->data[i]);
    }
  }

  // Remove temps
  delete_ivector(&core);
  delete_ivector(&lemma_reasons);

}

/**
 * Check consistency of given constraint. If inconsistent it returns the conflict.
 */
static
bool nra_plugin_speculate_constraint(nra_plugin_t* nra, int_mset_t* pos, int_mset_t* neg,
    variable_t x, term_t constraint, ivector_t* conflict) {

  term_t constraint_atom = unsigned_term(constraint);
  bool negated = constraint != constraint_atom;
  variable_t constraint_var = variable_db_get_variable(nra->ctx->var_db, constraint_atom);
  poly_constraint_db_add(nra->constraint_db, constraint_var);

  // Check if the constraint is in Boolean conflict
  if (trail_has_value(nra->ctx->trail, constraint_var)) {
    if (trail_get_boolean_value(nra->ctx->trail, constraint_var) == negated) {
      // Constraint value is false, so we just add the Boolean conflict
      ivector_push(conflict, constraint);
      ivector_push(conflict, opposite_term(constraint));
      return false;
    }
  }

  // Compute the feasible set
  lp_feasibility_set_t* constraint_feasible = nra_plugin_get_feasible_set(nra, constraint_var, x, negated);

  // Update the infeasible intervals
  bool feasible = feasible_set_db_update(nra->feasible_set_db, x, constraint_feasible, &constraint_var, 1);

  // Add to assumptions
  if (negated) {
    int_mset_add(neg, constraint_var);
  } else {
    int_mset_add(pos, constraint_var);
  }

  // If not feasible, get the conflict
  if (!feasible) {
    // Get the real conflict
    ivector_t constraint_conflict;
    init_ivector(&constraint_conflict, 0);
    nra_plugin_get_real_conflict(nra, pos, neg, x, &constraint_conflict);

    // Copy the conflict (except the assumption into the conflict)
    uint32_t i;
    for (i = 0; i < constraint_conflict.size; ++ i) {
      ivector_push(conflict, constraint_conflict.data[i]);
    }
    delete_ivector(&constraint_conflict);
  }

  // Remove from assumptions not feasible
  if (!feasible) {
    if (negated) {
      int_mset_remove_one(neg, constraint_var);
    } else {
      int_mset_remove_one(pos, constraint_var);
    }
  }

  return feasible;
}

static
void nra_plugin_get_int_conflict(nra_plugin_t* nra, int_mset_t* pos, int_mset_t* neg,
    variable_t x, ivector_t* conflict) {

  // We have an int conflict on x

  // That means that the feasible set is of the form
  //   I1    I2   I3 I4  I5
  //   ( )   ()   ( )()  ()
  //
  // Where each Ik doesn't allow an integer value.
  //
  // We do the splits manually and collect the explanation

  lp_value_t v;
  lp_value_construct_none(&v);

  term_t x_term = variable_db_get_term(nra->ctx->var_db, x);

  // We'll be making changes, remember state
  feasible_set_db_push(nra->feasible_set_db);

  // Set of constraints that we resolve using Boolean resolution
  int_mset_t to_resolve;
  int_mset_construct(&to_resolve, NULL_TERM);

  for (;;) {

    // Get the first value from the left
    const lp_feasibility_set_t* x_feasible = feasible_set_db_get(nra->feasible_set_db, x);
    if (ctx_trace_enabled(nra->ctx, "nia")) {
      ctx_trace_printf(nra->ctx, "x = ");
      variable_db_print_variable(nra->ctx->var_db, x, ctx_trace_out(nra->ctx));
      ctx_trace_printf(nra->ctx, "\nx_feasible = ");
      lp_feasibility_set_print(x_feasible, ctx_trace_out(nra->ctx));
      ctx_trace_printf(nra->ctx, "\n");
    }
    lp_feasibility_set_pick_first_value(x_feasible, &v);
    if (ctx_trace_enabled(nra->ctx, "nia")) {
      ctx_trace_printf(nra->ctx, "v = ");
      lp_value_print(&v, ctx_trace_out(nra->ctx));
      ctx_trace_printf(nra->ctx, "\n");
    }
    assert(!lp_value_is_integer(&v));

    // Get the floor
    lp_integer_t v_floor;
    lp_integer_construct(&v_floor);
    lp_value_floor(&v, &v_floor);

    // Yices versions of the floor
    rational_t v_floor_rat;
    rational_construct_from_lp_integer(&v_floor_rat, &v_floor);
    term_t v_floor_term = mk_arith_constant(nra->ctx->tm, &v_floor_rat);

    // Remove temp
    lp_integer_destruct(&v_floor);
    q_clear(&v_floor_rat);

    // The constraint
    term_t x_leq_floor = mk_arith_leq(nra->ctx->tm, x_term, v_floor_term);
    int_mset_add(&to_resolve, x_leq_floor);

    // Get the conflict
    feasible_set_db_push(nra->feasible_set_db);
    bool feasible = nra_plugin_speculate_constraint(nra, pos, neg, x, x_leq_floor, conflict);
    assert(!feasible);
    feasible_set_db_pop(nra->feasible_set_db);

    // Get the ceiling
    lp_integer_t v_ceil;
    lp_integer_construct(&v_ceil);
    lp_value_ceiling(&v, &v_ceil);

    // Yices versions of the ceiling
    rational_t v_ceil_rat;
    rational_construct_from_lp_integer(&v_ceil_rat, &v_ceil);
    term_t v_ceil_term = mk_arith_constant(nra->ctx->tm, &v_ceil_rat);

    // Remove temp
    lp_integer_destruct(&v_ceil);
    q_clear(&v_ceil_rat);

    // The constraint
    term_t x_geq_ceil = mk_arith_geq(nra->ctx->tm, x_term, v_ceil_term);
    int_mset_add(&to_resolve, x_geq_ceil);

    // Try it out
    feasible = nra_plugin_speculate_constraint(nra, pos, neg, x, x_geq_ceil, conflict);

    if (ctx_trace_enabled(nra->ctx, "nia")) {
      ctx_trace_printf(nra->ctx, "int_conflict: current conflict:\n");
      uint32_t i;
      for (i = 0; i < conflict->size; ++ i) {
        ctx_trace_printf(nra->ctx, "  ");
        ctx_trace_term(nra->ctx, conflict->data[i]);
      }
    }

    // If not feasible, we're done
    if (!feasible) {
      break;
    }
  }

  // Undo feasibility changes
  feasible_set_db_pop(nra->feasible_set_db);

  // Remove resolved literals
  uint32_t i = 0, to_keep;
  for (i = 0, to_keep = 0; i < conflict->size; ++ i) {
    if (!int_mset_contains(&to_resolve, conflict->data[i])) {
      conflict->data[to_keep ++] = conflict->data[i];
    }
  }
  ivector_shrink(conflict, to_keep);

  if (ctx_trace_enabled(nra->ctx, "nia")) {
    ctx_trace_printf(nra->ctx, "int_conflict: final conflict:\n");
    uint32_t i;
    for (i = 0; i < conflict->size; ++ i) {
      ctx_trace_printf(nra->ctx, "  ");
      ctx_trace_term(nra->ctx, conflict->data[i]);
    }
  }

  // Remove temps
  int_mset_destruct(&to_resolve);
  lp_value_destruct(&v);
}

static
void nra_plugin_get_assumption_conflict(nra_plugin_t* nra, int_mset_t* pos, int_mset_t* neg,
    variable_t x, ivector_t* conflict) {
  size_t i;

  if (ctx_trace_enabled(nra->ctx, "nra::conflict")) {
    ctx_trace_printf(nra->ctx, "nra_plugin_get_assumption_conflict(): ");
    ctx_trace_term(nra->ctx, variable_db_get_term(nra->ctx->var_db, x));
  }

  // Get the value of x (responsible for conflict)
  const mcsat_value_t* x_value = trail_get_value(nra->ctx->trail, x);

  // The assertions on x that are in conflict (as constraint variables)
  ivector_t core, lemma_reasons;
  init_ivector(&core, 0);
  init_ivector(&lemma_reasons, 0);
  feasible_set_db_get_conflict_reasons(nra->feasible_set_db, nra, x, x_value, &core, &lemma_reasons);

  if (ctx_trace_enabled(nra->ctx, "nra::conflict")) {
    ctx_trace_printf(nra->ctx, "nra_plugin_get_assumption_conflict(): core:\n");
    for (i = 0; i < core.size; ++ i) {
      ctx_trace_printf(nra->ctx, "[%zu] (", i);
      if (trail_has_value(nra->ctx->trail, core.data[i])) {
        mcsat_value_print(trail_get_value(nra->ctx->trail, core.data[i]), ctx_trace_out(nra->ctx));
      }
      ctx_trace_printf(nra->ctx, "): ");
      ctx_trace_term(nra->ctx, variable_db_get_term(nra->ctx->var_db, core.data[i]));
    }
  }

  // No projection needed, we just return the core
  assert(lemma_reasons.size == 0);
  for (i = 0; i < core.size; ++ i) {
    variable_t constraint_var = core.data[i];
    term_t constraint_term = variable_db_get_term(nra->ctx->var_db, constraint_var);
    assert(trail_has_value(nra->ctx->trail, constraint_var));
    bool constraint_value = trail_get_boolean_value(nra->ctx->trail, constraint_var);
    if (!constraint_value) {
      constraint_term = opposite_term(constraint_term);
    }
    ivector_push(conflict, constraint_term);
  }
  if (ctx_trace_enabled(nra->ctx, "nra::conflict")) {
    ctx_trace_printf(nra->ctx, "nra_plugin_get_assumption_conflict(): conflict:\n");
    for (i = 0; i < conflict->size; ++ i) {
      ctx_trace_printf(nra->ctx, "[%zu]: ", i);
      ctx_trace_term(nra->ctx, conflict->data[i]);
    }
  }

  // Remove temps
  delete_ivector(&core);
  delete_ivector(&lemma_reasons);
}


static
void nra_plugin_get_conflict(plugin_t* plugin, ivector_t* conflict) {
  nra_plugin_t* nra = (nra_plugin_t*) plugin;

  if (ctx_trace_enabled(nra->ctx, "nra::conflict")) {
    ctx_trace_printf(nra->ctx, "nra_plugin_get_conflict(): START\n");
  }

  int_mset_t pos, neg;
  int_mset_construct(&pos, variable_null);
  int_mset_construct(&neg, variable_null);

  if (nra->conflict_variable != variable_null) {
    nra_plugin_get_real_conflict(nra, &pos, &neg, nra->conflict_variable, conflict);
  } else if (nra->conflict_variable_int != variable_null) {
    nra_plugin_get_int_conflict(nra, &pos, &neg, nra->conflict_variable_int, conflict);
  } else if (nra->conflict_variable_assumption != variable_null) {
    nra_plugin_get_assumption_conflict(nra, &pos, &neg, nra->conflict_variable_assumption, conflict);
  }

  int_mset_destruct(&pos);
  int_mset_destruct(&neg);

  if (ctx_trace_enabled(nra->ctx, "nra::conflict")) {
    uint32_t i;
    ctx_trace_printf(nra->ctx, "nra_plugin_get_conflict(): END\n");
    for (i = 0; i < conflict->size; ++ i) {
      ctx_trace_term(nra->ctx, conflict->data[i]);
    }
  }
}

static
term_t nra_plugin_explain_propagation(plugin_t* plugin, variable_t var, ivector_t* reasons) {
  nra_plugin_t* nra = (nra_plugin_t*) plugin;

  // We only propagate evaluations, and we explain them using the literal itself
  term_t atom = variable_db_get_term(nra->ctx->var_db, var);
  if (ctx_trace_enabled(nra->ctx, "nra::conflict")) {
    ctx_trace_printf(nra->ctx, "nra_plugin_explain_propagation():\n");
    ctx_trace_term(nra->ctx, atom);
  }
  bool value = trail_get_boolean_value(nra->ctx->trail, var);
  if (ctx_trace_enabled(nra->ctx, "nra::conflict")) {
    ctx_trace_printf(nra->ctx, "assigned to %s\n", value ? "true" : "false");
  }

  if (value) {
    // atom => atom = true
    ivector_push(reasons, atom);
    return bool2term(true);
  } else {
    // neg atom => atom = false
    ivector_push(reasons, opposite_term(atom));
    return bool2term(false);
  }
}

static
bool nra_plugin_explain_evaluation(plugin_t* plugin, term_t t, int_mset_t* vars, mcsat_value_t* value) {
  nra_plugin_t* nra = (nra_plugin_t*) plugin;

  // Get all the variables and make sure they are all assigned.
  nra_plugin_get_constraint_variables(nra, t, vars);

  // Check if the variables are assigned
  ivector_t* var_list = int_mset_get_list(vars);
  size_t i = 0;
  for (i = 0; i < var_list->size; ++ i) {
    if (!trail_has_value(nra->ctx->trail, var_list->data[i])) {
      int_mset_clear(vars);
      return false;
    }
  }

  // All variables assigned
  return true;
}

static
void nra_plugin_push(plugin_t* plugin) {
  nra_plugin_t* nra = (nra_plugin_t*) plugin;
  scope_holder_push(&nra->scope,
      &nra->trail_i,
      &nra->processed_variables_size,
      &nra->lp_data.lp_var_order_size,
      NULL);

  feasible_set_db_push(nra->feasible_set_db);
}

static
void nra_plugin_pop(plugin_t* plugin) {

  nra_plugin_t* nra = (nra_plugin_t*) plugin;
  const mcsat_trail_t* trail = nra->ctx->trail;

  if (ctx_trace_enabled(nra->ctx, "nra::conflict")) {
    trail_print(trail, ctx_trace_out(nra->ctx));
  }

  // Pop the scoped variables
  scope_holder_pop(&nra->scope,
      &nra->trail_i,
      &nra->processed_variables_size,
      &nra->lp_data.lp_var_order_size,
      NULL);

  // Undo the processed variables
  while (nra->processed_variables.size > nra->processed_variables_size) {
    // The variable to undo
    variable_t x = ivector_last(&nra->processed_variables);
    ivector_pop(&nra->processed_variables);
    assert(variable_db_is_real(nra->ctx->var_db, x) || variable_db_is_int(nra->ctx->var_db, x));
    // Go through the watch and mark the constraints
    remove_iterator_t it;
    remove_iterator_construct(&it, &nra->wlm, x);
    while (!remove_iterator_done(&it)) {
      variable_t constraint_var = remove_iterator_get_constraint(&it);
      constraint_unit_info_t unit_info = nra_plugin_get_unit_info(nra, constraint_var);
      switch (unit_info) {
      case CONSTRAINT_UNKNOWN:
        // Nothing to do
        break;
      case CONSTRAINT_UNIT:
        // If it was unit it becomes not unit
        nra_plugin_set_unit_info(nra, constraint_var, variable_null, CONSTRAINT_UNKNOWN);
        break;
      case CONSTRAINT_FULLY_ASSIGNED:
        // It is unit now
        nra_plugin_set_unit_info(nra, constraint_var, x, CONSTRAINT_UNIT);
        break;
      }
      remove_iterator_next_and_keep(&it);
    }
    remove_iterator_destruct(&it);
  }

  // Pop the variable order and the lp model
  lp_variable_order_t* order = nra->lp_data.lp_var_order;
  lp_assignment_t* assignment = nra->lp_data.lp_assignment;
  while (lp_variable_order_size(order) > nra->lp_data.lp_var_order_size) {
    lp_variable_t lp_var = lp_variable_order_top(order);
    lp_variable_order_pop(order);
    lp_assignment_set_value(assignment, lp_var, 0);
    variable_t var = nra_plugin_get_variable_from_lp_variable(nra, lp_var);
    (void)var;
  }

  if (ctx_trace_enabled(nra->ctx, "nra::check_assignment")) {
    nra_plugin_check_assignment(nra);
  }

  // Pop the feasibility
  feasible_set_db_pop(nra->feasible_set_db);

  // Unset the conflict
  nra->conflict_variable = variable_null;
  nra->conflict_variable_int = variable_null;
  nra->conflict_variable_assumption = variable_null;

  // We undid last decision, so we're back to normal
  nra->last_decided_and_unprocessed = variable_null;
}

static
void nra_plugin_gc_mark(plugin_t* plugin, gc_info_t* gc_vars) {
  nra_plugin_t* nra = (nra_plugin_t*) plugin;
  // The NRA plugin doesn't really need to keep much. The only things we'd
  // like to keep are the lemmas that restrict top level feasibility sets.
  feasible_set_db_gc_mark(nra->feasible_set_db, gc_vars);
  // We also need to mark all the real variables that are in use
  poly_constraint_db_gc_mark(nra->constraint_db, gc_vars);
}

static
void nra_plugin_gc_sweep(plugin_t* plugin, const gc_info_t* gc_vars) {
  nra_plugin_t* nra = (nra_plugin_t*) plugin;

  // The feasibility sets keep everything, we just gc the constraints,
  // the watchlists and the unit information.

  // The constraint database
  poly_constraint_db_gc_sweep(nra->constraint_db, gc_vars);

  // The lp_data mappings:
  // - lpdata.lp_to_mcsat_var_map (values)
  // - lpdata.mcsat_to_lp_var_map (keys)
  gc_info_sweep_int_hmap_values(gc_vars, &nra->lp_data.lp_to_mcsat_var_map);
  gc_info_sweep_int_hmap_keys(gc_vars, &nra->lp_data.mcsat_to_lp_var_map);

  // Evaluation cache
  gc_info_sweep_int_hmap_keys(gc_vars, &nra->evaluation_value_cache);
  gc_info_sweep_int_hmap_keys(gc_vars, &nra->evaluation_timestamp_cache);

  // Feasible set cache
  gc_info_sweep_int_hmap_keys(gc_vars, &nra->feasible_set_cache_top_var[0]);
  gc_info_sweep_int_hmap_values(gc_vars, &nra->feasible_set_cache_top_var[0]);
  gc_info_sweep_int_hmap_keys(gc_vars, &nra->feasible_set_cache_top_var[1]);
  gc_info_sweep_int_hmap_values(gc_vars, &nra->feasible_set_cache_top_var[1]);
  gc_info_sweep_int_hmap_keys(gc_vars, &nra->feasible_set_cache_timestamp[0]);
  gc_info_sweep_int_hmap_keys(gc_vars, &nra->feasible_set_cache_timestamp[1]);
  gc_info_sweep_ptr_hmap_keys(gc_vars, &nra->feasible_set_cache[0], (ptr_hmap_ptr_delete) &lp_feasibility_set_delete);
  gc_info_sweep_ptr_hmap_keys(gc_vars, &nra->feasible_set_cache[0], (ptr_hmap_ptr_delete) &lp_feasibility_set_delete);

  // Unit information (constraint_unit_info, constraint_unit_var)
  gc_info_sweep_int_hmap_keys(gc_vars, &nra->constraint_unit_info);
  gc_info_sweep_int_hmap_keys(gc_vars, &nra->constraint_unit_var);

  // Watch list manager
  watch_list_manager_gc_sweep_lists(&nra->wlm, gc_vars);
}

static
void nra_plugin_event_notify(plugin_t* plugin, plugin_notify_kind_t kind) {
  nra_plugin_t* nra = (nra_plugin_t*) plugin;
  (void)nra;

  switch (kind) {
  case MCSAT_SOLVER_START:
    // Re-initialize the heuristics
    break;
  case MCSAT_SOLVER_RESTART:
    // Check if clause compaction needed
    break;
  case MCSAT_SOLVER_CONFLICT:
    // Decay the scores each conflict
    break;
  case MCSAT_SOLVER_POP:
    // Not much to do
    break;
  default:
    assert(false);
  }
}

static
void nra_plugin_new_lemma_notify(plugin_t* plugin, ivector_t* lemma, trail_token_t* prop) {
  nra_plugin_t* nra = (nra_plugin_t*) plugin;

  uint32_t i;

  // Check if unit in single variable
  bool unit = true;
  variable_t unit_var = variable_null;
  for (i = 0; unit && i < lemma->size; ++ i) {

    if (ctx_trace_enabled(nra->ctx, "nra::lemma")) {
      ctx_trace_printf(nra->ctx, "lemma[%u] = ", i); ctx_trace_term(nra->ctx, lemma->data[i]); ctx_trace_printf(nra->ctx, "\n");
    }

    term_t literal = lemma->data[i];
    term_t atom = unsigned_term(literal);
    variable_t atom_var = variable_db_get_variable_if_exists(nra->ctx->var_db, atom);
    assert(atom_var != variable_null);
    if (nra_plugin_get_unit_info(nra, atom_var) != CONSTRAINT_UNIT) {
      // Not unit
      unit = false;
    } else {
      // Unit, check if same variable
      variable_t atom_unit_var = nra_plugin_get_unit_var(nra, atom_var);
      if (unit_var == variable_null) {
        unit_var = atom_unit_var;
      } else if (unit_var != atom_unit_var) {
        unit = false;
      }
    }
  }

  if (unit && nra->ctx->trail->decision_level == 0) {

    // Get the feasible set
    lp_feasibility_set_t* lemma_feasible = lp_feasibility_set_new_empty();

    // Add all the literal sets
    for (i = 0; i < lemma->size; ++ i) {

      if (ctx_trace_enabled(nra->ctx, "nra::lemma")) {
        ctx_trace_printf(nra->ctx, "nra: lemma_feasible = ");
        lp_feasibility_set_print(lemma_feasible, ctx_trace_out(nra->ctx));
        ctx_trace_printf(nra->ctx, "\n");
      }

      term_t literal_term = lemma->data[i];
      term_t constraint_term = unsigned_term(literal_term);
      variable_t constraint_var = variable_db_get_variable_if_exists(nra->ctx->var_db, constraint_term);
      assert(constraint_var != variable_null);

      // Is it negated
      bool negated = constraint_term != literal_term;

      // Compute and add the feasible set
      lp_feasibility_set_t* constraint_feasible = nra_plugin_get_feasible_set(nra, constraint_var, unit_var, negated);

      if (ctx_trace_enabled(nra->ctx, "nra::lemma")) {
        ctx_trace_printf(nra->ctx, "nra: constraint_feasible = ");
        lp_feasibility_set_print(constraint_feasible, ctx_trace_out(nra->ctx));
        ctx_trace_printf(nra->ctx, "\n");
      }

      lp_feasibility_set_add(lemma_feasible, constraint_feasible);
      lp_feasibility_set_delete(constraint_feasible);
    }

    if (ctx_trace_enabled(nra->ctx, "nra::lemma")) {
      ctx_trace_printf(nra->ctx, "nra: lemma_feasible = ");
      lp_feasibility_set_print(lemma_feasible, ctx_trace_out(nra->ctx));
      ctx_trace_printf(nra->ctx, "\n");
    }

    // Since we need to communicate conflicts to bool theory, vacuous constraints
    // can happen, i.e. the following is not a valid assertion
    // assert(!lp_feasibility_set_is_full(lemma_feasible));
    // We can also learn infeasible lemmas, we just have to report a conflict
    if (!lp_feasibility_set_is_full(lemma_feasible)) {

      if (ctx_trace_enabled(nra->ctx, "nra::lemma")) {
        const lp_feasibility_set_t* current_feasible = feasible_set_db_get(nra->feasible_set_db, unit_var);
        if (current_feasible) {
          ctx_trace_printf(nra->ctx, "nra: current feasible = ");
          lp_feasibility_set_print(current_feasible, ctx_trace_out(nra->ctx));
          ctx_trace_printf(nra->ctx, "\n");
        }
      }

      // Collect the literals
      ivector_t lemma_reasons;
      init_ivector(&lemma_reasons, 0);
      for (i = 0; i < lemma->size; ++ i) {
        term_t literal_term = lemma->data[i];
        term_t constraint_term = unsigned_term(literal_term);
        variable_t constraint_var = variable_db_get_variable_if_exists(nra->ctx->var_db, constraint_term);
        assert(constraint_var != variable_null);
        ivector_push(&lemma_reasons, constraint_var);
      }

      // Update
      bool feasible = feasible_set_db_update(nra->feasible_set_db, unit_var, lemma_feasible, lemma_reasons.data, lemma_reasons.size);
      if (ctx_trace_enabled(nra->ctx, "nra::lemma")) {
        ctx_trace_printf(nra->ctx, "nra: new feasible = ");
        const lp_feasibility_set_t* current_feasible = feasible_set_db_get(nra->feasible_set_db, unit_var);
        lp_feasibility_set_print(current_feasible, ctx_trace_out(nra->ctx));
        ctx_trace_printf(nra->ctx, "\n");
      }

      // If infeasible report conflict
      if (!feasible) {
        nra_plugin_report_conflict(nra, prop, unit_var);
      } else if (variable_db_is_int(nra->ctx->var_db, unit_var)) {
        // Check if there is an integer value
        lp_value_t v;
        lp_value_construct_none(&v);
        lp_feasibility_set_pick_value(feasible_set_db_get(nra->feasible_set_db, unit_var), &v);
        if (!lp_value_is_integer(&v)) {
          nra->conflict_variable_int = unit_var;
          nra_plugin_report_conflict(nra, prop, unit_var);
        }
        lp_value_destruct(&v);
      }

      delete_ivector(&lemma_reasons);
    } else {
      lp_feasibility_set_delete(lemma_feasible);
    }
  }
}

static
void nra_plugin_set_exception_handler(plugin_t* plugin, jmp_buf* handler) {
  nra_plugin_t* nra = (nra_plugin_t*) plugin;
  nra->exception = handler;
}

static
const mcsat_value_t* ensure_lp_value(const mcsat_value_t* value, mcsat_value_t* alternative) {
  lp_value_t lp_value;
  lp_rational_t rat_value;
  switch (value->type) {
  case VALUE_LIBPOLY:
    return value;
  case VALUE_RATIONAL:
    lp_rational_construct(&rat_value);
    q_get_mpq((rational_t*)&value->q, &rat_value);
    lp_value_construct(&lp_value, LP_VALUE_RATIONAL, &rat_value);
    mcsat_value_construct_lp_value(alternative, &lp_value);
    lp_value_destruct(&lp_value);
    lp_rational_destruct(&rat_value);
    return alternative;
  default:
    assert(false);
  }
  return NULL;
}


static
void nra_plugin_decide_assignment(plugin_t* plugin, variable_t x, const mcsat_value_t* value, trail_token_t* decide) {
  nra_plugin_t* nra = (nra_plugin_t*) plugin;
  // If we get a rational, conver to lp_value_t
  mcsat_value_t tmp;
  const mcsat_value_t* lp_value = ensure_lp_value(value, &tmp);
  // Get the feasibility set
  lp_feasibility_set_t* feasible = feasible_set_db_get(nra->feasible_set_db, x);
  // Decide the variable anyhow
  decide->add(decide, x, lp_value);
  nra->last_decided_and_unprocessed = x;
  // Check if this was feasible
  if (feasible != NULL && !lp_feasibility_set_contains(feasible, &lp_value->lp_value)) {
    // Ouch, conflict
    nra_plugin_report_assumption_conflict(nra, decide, x);
  }
  // Remove temps
  if (lp_value != value) {
    lp_value_destruct(&tmp.lp_value);
  }
}


plugin_t* nra_plugin_allocator(void) {
  nra_plugin_t* plugin = safe_malloc(sizeof(nra_plugin_t));
  plugin_construct((plugin_t*) plugin);
  plugin->plugin_interface.construct           = nra_plugin_construct;
  plugin->plugin_interface.destruct            = nra_plugin_destruct;
  plugin->plugin_interface.new_term_notify     = nra_plugin_new_term_notify;
  plugin->plugin_interface.new_lemma_notify    = nra_plugin_new_lemma_notify;
  plugin->plugin_interface.event_notify        = nra_plugin_event_notify;
  plugin->plugin_interface.propagate           = nra_plugin_propagate;
  plugin->plugin_interface.decide              = nra_plugin_decide;
  plugin->plugin_interface.decide_assignment   = nra_plugin_decide_assignment;
  plugin->plugin_interface.get_conflict        = nra_plugin_get_conflict;
  plugin->plugin_interface.explain_propagation = nra_plugin_explain_propagation;
  plugin->plugin_interface.explain_evaluation  = nra_plugin_explain_evaluation;
  plugin->plugin_interface.push                = nra_plugin_push;
  plugin->plugin_interface.pop                 = nra_plugin_pop;
  plugin->plugin_interface.gc_mark             = nra_plugin_gc_mark;
  plugin->plugin_interface.gc_sweep            = nra_plugin_gc_sweep;
  plugin->plugin_interface.set_exception_handler = nra_plugin_set_exception_handler;

  return (plugin_t*) plugin;
}
