(set-info :source |fuzzsmt|)
(set-info :smt-lib-version 2.0)
(set-info :category "random")
(set-info :status unknown)
(set-logic QF_IDL)
(declare-fun v0 () Int)
(declare-fun v1 () Int)
(assert (let ((e2 0))
(let ((e3 1))
(let ((e4 (= v1 v0)))
(let ((e5 (> v1 v1)))
(let ((e6 (>= (- v1 v0) e3)))
(let ((e7 (<= (- v1 v0) (- e2))))
(let ((e8 (= v0 v1)))
(let ((e9 (> (- v1 v0) (- e3))))
(let ((e10 (>= v0 v0)))
(let ((e11 (= (- v0 v0) e3)))
(let ((e12 (> (- v1 v1) e2)))
(let ((e13 (< v1 v1)))
(let ((e14 (<= (- v0 v1) (- e2))))
(let ((e15 (= e10 e14)))
(let ((e16 (not e15)))
(let ((e17 (or e12 e16)))
(let ((e18 (ite e8 e11 e6)))
(let ((e19 (= e5 e4)))
(let ((e20 (=> e18 e17)))
(let ((e21 (not e13)))
(let ((e22 (not e20)))
(let ((e23 (not e7)))
(let ((e24 (xor e23 e22)))
(let ((e25 (=> e21 e9)))
(let ((e26 (and e24 e19)))
(let ((e27 (and e26 e25)))
e27
)))))))))))))))))))))))))))

(check-sat)