(set-logic QF_BV)
(set-info :source |
 Patrice Godefroid, SAGE (systematic dynamic test generation)
 For more information: http://research.microsoft.com/en-us/um/people/pg/public_psfiles/ndss2008.pdf
|)
(set-info :smt-lib-version 2.0)
(set-info :category "industrial")
(set-info :status unknown)
(declare-fun T1_0 () (_ BitVec 8))
(declare-fun T4_0 () (_ BitVec 32))
(declare-fun T1_1 () (_ BitVec 8))
(declare-fun T1_2 () (_ BitVec 8))
(declare-fun T1_3 () (_ BitVec 8))
(assert (let ((?v_2 ((_ extract 7 0) (bvashr T4_0 ((_ zero_extend 24) (_ bv8 8))))) (?v_1 ((_ extract 7 0) (bvashr T4_0 ((_ zero_extend 24) (_ bv16 8))))) (?v_0 ((_ extract 7 0) (bvashr T4_0 ((_ zero_extend 24) (_ bv24 8)))))) (and true (= T4_0 (bvor (bvshl (bvor (bvshl (bvor (bvshl ((_ zero_extend 24) T1_3) (_ bv8 32)) ((_ zero_extend 24) T1_2)) (_ bv8 32)) ((_ zero_extend 24) T1_1)) (_ bv8 32)) ((_ zero_extend 24) T1_0))) (= T1_0 (_ bv0 8)) (bvule ?v_0 (_ bv90 8)) (bvule (_ bv65 8) ?v_0) (bvult ?v_0 (_ bv97 8)) (bvult (_ bv57 8) ?v_0) (bvule (_ bv48 8) ?v_0) (bvule ?v_1 (_ bv90 8)) (bvule (_ bv65 8) ?v_1) (bvult ?v_1 (_ bv97 8)) (bvult (_ bv57 8) ?v_1) (bvule (_ bv48 8) ?v_1) (bvule ?v_2 (_ bv90 8)) (bvule (_ bv65 8) ?v_2) (bvult ?v_2 (_ bv97 8)) (bvult (_ bv57 8) ?v_2) (bvule (_ bv48 8) ?v_2) (= (_ bv1179011410 32) T4_0) (= T4_0 (_ bv1179011410 32)) (bvule T1_0 (_ bv90 8)) (bvule (_ bv65 8) T1_0) (bvult T1_0 (_ bv97 8)) (bvult (_ bv57 8) T1_0) (bvule (_ bv48 8) T1_0))))
(check-sat)
(exit)
