(set-logic QF_BV)
(declare-fun x () (_ BitVec 1))
(declare-fun y () (_ BitVec 1))
(declare-fun b1 () Bool)
(declare-fun b2 () Bool)
(declare-fun b3 () Bool)
(define-fun |Scoreboard#30#11654| () (_ BitVec 1) (ite b1 #b1 #b0))
(define-fun |$paramod/FF/WIDTH=1_n D#11655| () Bool b2)
(define-fun |$paramod/FF/WIDTH=1_n Q#11657| () Bool (= ((_ extract 0 0) y) #b1))
(define-fun |Scoreboard_h#11556| () Bool (and true (= (= ((_ extract 0 0) |Scoreboard#30#11654|) #b1) |$paramod/FF/WIDTH=1_n D#11655|) (= b1 |$paramod/FF/WIDTH=1_n Q#11657|) true))
(assert |Scoreboard_h#11556|)
(define-fun |$paramod/FF/WIDTH=1_n Q#12936| () Bool (= ((_ extract 0 0) x) #b1))
(define-fun |Scoreboard_h#12835| () Bool (and true (= true |$paramod/FF/WIDTH=1_n Q#12936|) true))
(assert |Scoreboard_h#12835|)
(define-fun |$paramod/FF/WIDTH=1#4#13790| () (_ BitVec 1) (ite b3 (ite b2 #b1 #b0) y))
(define-fun |$paramod/FF/WIDTH=1_t#13789| () Bool (= |$paramod/FF/WIDTH=1#4#13790| x))
(define-fun |Scoreboard_t#13771| () Bool (and true |$paramod/FF/WIDTH=1_t#13789| true))
(assert |Scoreboard_t#13771|)
(check-sat)
(exit)
