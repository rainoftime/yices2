(set-logic QF_BV)
(declare-fun x () (_ BitVec 13))
(declare-fun y () (_ BitVec 8))
(declare-fun z () (_ BitVec 13))
(assert
  (let ((e9 (bvnot x)))
  (let ((e14 (bvshl e9 e9)))
  (let ((e18 (distinct e14 z)))
  (let ((e36 (bvule z ((_ zero_extend 5) y))))
  (let ((e43 (=> true e18)))
  (let ((e44 e43))
  (let ((e48 e44))
  (let ((e55 (xor false e48)))
  (let ((e56 e36))
  (let ((e57 (xor false e56)))
  (let ((e62 (= e57 e55)))
  (let ((e64 (xor e62 false)))
  (let ((e65 e64))
  (let ((e66 e65)) e66)))))))))))))))
(check-sat)
