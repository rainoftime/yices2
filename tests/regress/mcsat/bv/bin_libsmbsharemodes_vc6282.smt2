(set-logic QF_BV)
(declare-fun _substvar_34_ () (_ BitVec 64))
(declare-fun _substvar_36_ () (_ BitVec 8))
(declare-fun _substvar_39_ () (_ BitVec 32))
(declare-fun _substvar_74_ () Bool)
(declare-fun _substvar_30_ () (_ BitVec 32))
(declare-fun _substvar_22_ () (_ BitVec 64))
(declare-fun _substvar_68_ () Bool)
(assert _substvar_68_)
(assert (= _substvar_30_ ((_ sign_extend 24) _substvar_36_)))
(assert (= _substvar_39_ (bvadd _substvar_30_ ((_ extract 31 0) (_ bv24 64)))))
(assert (= _substvar_34_ ((_ sign_extend 32) _substvar_39_)))
(assert (= _substvar_74_ (bvult (_ bv0 64) _substvar_34_)))
(assert (= false (bvult _substvar_22_ _substvar_34_)))
(check-sat)
(exit)
