(set-logic QF_BV)
(declare-fun _substvar_584_ () (_ BitVec 32))
(declare-fun _substvar_562_ () (_ BitVec 32))
(declare-fun _substvar_468_ () (_ BitVec 16))
(assert (= _substvar_584_ ((_ sign_extend 16) _substvar_468_)))
(assert (= _substvar_562_ (bvadd (_ bv0 32) _substvar_584_)))
(assert (= false (bvslt _substvar_562_ ((_ extract 31 0) (_ bv338 64)))))
(check-sat)
(exit)