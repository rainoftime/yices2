(set-info :source |fuzzsmt|)
(set-info :smt-lib-version 2.0)
(set-info :category "random")
(set-info :status unknown)
(set-logic QF_AUFBV)
(declare-fun v0 () (_ BitVec 3))
(declare-fun v1 () (_ BitVec 11))
(declare-fun v2 () (_ BitVec 6))
(declare-fun v3 () (_ BitVec 12))
(declare-fun v4 () (_ BitVec 4))
(declare-fun a5 () (Array  (_ BitVec 14)  (_ BitVec 6)))
(declare-fun a6 () (Array  (_ BitVec 11)  (_ BitVec 15)))
(declare-fun a7 () (Array  (_ BitVec 10)  (_ BitVec 12)))
(assert (let ((e8(_ bv25663 15)))
(let ((e9 ((_ zero_extend 8) v2)))
(let ((e10 (ite (= (_ bv1 1) ((_ extract 5 5) v1)) v1 v1)))
(let ((e11 (bvnor v3 v3)))
(let ((e12 (ite (= (_ bv1 1) ((_ extract 6 6) v1)) v3 v3)))
(let ((e13 (bvlshr ((_ sign_extend 3) e10) e9)))
(let ((e14 (bvxor ((_ sign_extend 8) v4) v3)))
(let ((e15 (ite (bvult ((_ zero_extend 3) e11) e8) (_ bv1 1) (_ bv0 1))))
(let ((e16 (ite (bvugt ((_ sign_extend 5) e15) v2) (_ bv1 1) (_ bv0 1))))
(let ((e17 (bvnor e11 e14)))
(let ((e18 (bvnand v0 ((_ zero_extend 2) e15))))
(let ((e19 (store a5 ((_ sign_extend 2) e11) v2)))
(let ((e20 (store a6 ((_ zero_extend 7) v4) ((_ sign_extend 12) v0))))
(let ((e21 (store a5 ((_ extract 14 1) e8) ((_ extract 7 2) e12))))
(let ((e22 (select a5 e13)))
(let ((e23 (store a5 e9 ((_ extract 10 5) e8))))
(let ((e24 (store e20 ((_ zero_extend 10) e16) ((_ zero_extend 1) e13))))
(let ((e25 (ite (bvule ((_ zero_extend 1) e10) e17) (_ bv1 1) (_ bv0 1))))
(let ((e26 ((_ repeat 1) v2)))
(let ((e27 (bvneg v1)))
(let ((e28 (bvnot e22)))
(let ((e29 (ite (bvsge ((_ sign_extend 1) e9) e8) (_ bv1 1) (_ bv0 1))))
(let ((e30 (ite (bvule e17 ((_ zero_extend 6) e26)) (_ bv1 1) (_ bv0 1))))
(let ((e31 (bvneg v0)))
(let ((e32 (ite (distinct ((_ sign_extend 2) v4) e22) (_ bv1 1) (_ bv0 1))))
(let ((e33 (ite (bvsgt ((_ zero_extend 11) e16) e17) (_ bv1 1) (_ bv0 1))))
(let ((e34 ((_ extract 7 1) e12)))
(let ((e35 (ite (= (_ bv1 1) ((_ extract 7 7) v3)) ((_ zero_extend 5) e34) e17)))
(let ((e36 (bvnand ((_ sign_extend 2) e15) e18)))
(let ((e37 (bvashr e13 ((_ sign_extend 7) e34))))
(let ((e38 ((_ zero_extend 1) e15)))
(let ((e39 (bvneg e17)))
(let ((e40 (bvsdiv ((_ sign_extend 10) e25) e27)))
(let ((e41 ((_ repeat 1) e11)))
(let ((e42 (ite (= v3 ((_ zero_extend 11) e29)) (_ bv1 1) (_ bv0 1))))
(let ((e43 (ite (bvugt ((_ sign_extend 11) e29) e17) (_ bv1 1) (_ bv0 1))))
(let ((e44 (bvnor e14 ((_ sign_extend 6) v2))))
(let ((e45 (= ((_ sign_extend 11) e36) e9)))
(let ((e46 (bvslt e44 e44)))
(let ((e47 (bvsle ((_ zero_extend 11) e15) e41)))
(let ((e48 (bvsge e34 ((_ zero_extend 4) e31))))
(let ((e49 (bvuge e13 ((_ zero_extend 2) e35))))
(let ((e50 (bvslt e32 e16)))
(let ((e51 (bvuge e39 ((_ zero_extend 11) e16))))
(let ((e52 (= e11 ((_ sign_extend 11) e25))))
(let ((e53 (bvuge e17 ((_ sign_extend 11) e32))))
(let ((e54 (bvsle e32 e42)))
(let ((e55 (bvuge e36 e18)))
(let ((e56 (bvslt e12 e12)))
(let ((e57 (bvule e34 ((_ sign_extend 1) e22))))
(let ((e58 (bvslt v2 ((_ zero_extend 5) e32))))
(let ((e59 (= e14 e35)))
(let ((e60 (bvsle ((_ zero_extend 11) e25) e39)))
(let ((e61 (bvslt ((_ zero_extend 10) e30) e40)))
(let ((e62 (bvult e32 e29)))
(let ((e63 (bvsle e27 e40)))
(let ((e64 (bvslt e37 ((_ sign_extend 2) e11))))
(let ((e65 (bvuge v3 ((_ sign_extend 1) e40))))
(let ((e66 (bvuge ((_ zero_extend 5) e43) e26)))
(let ((e67 (bvult e32 e42)))
(let ((e68 (distinct ((_ zero_extend 2) e12) e9)))
(let ((e69 (bvult e34 ((_ zero_extend 4) v0))))
(let ((e70 (bvule ((_ sign_extend 2) e42) e36)))
(let ((e71 (bvugt v3 ((_ sign_extend 11) e16))))
(let ((e72 (bvslt e37 ((_ sign_extend 2) e39))))
(let ((e73 (bvugt e8 ((_ sign_extend 12) e31))))
(let ((e74 (bvsle e32 e30)))
(let ((e75 (bvsgt e28 e26)))
(let ((e76 (bvult e39 ((_ zero_extend 8) v4))))
(let ((e77 (bvsle ((_ sign_extend 5) e38) e34)))
(let ((e78 (bvugt e44 v3)))
(let ((e79 (bvsge e8 ((_ zero_extend 3) e41))))
(let ((e80 (bvsge ((_ zero_extend 3) e18) e26)))
(let ((e81 (= e26 e22)))
(let ((e82 (bvult e37 ((_ zero_extend 13) e29))))
(let ((e83 (bvugt ((_ zero_extend 5) e33) v2)))
(let ((e84 (bvslt ((_ sign_extend 1) e9) e8)))
(let ((e85 (bvult e10 e10)))
(let ((e86 (bvsge e11 ((_ zero_extend 11) e32))))
(let ((e87 (bvsle e34 ((_ zero_extend 6) e30))))
(let ((e88 (bvslt e22 ((_ sign_extend 5) e25))))
(let ((e89 (bvslt e37 ((_ sign_extend 8) e22))))
(let ((e90 (= e37 ((_ zero_extend 11) e18))))
(let ((e91 (= e44 e11)))
(let ((e92 (bvuge e12 ((_ sign_extend 6) e22))))
(let ((e93 (distinct e14 v3)))
(let ((e94 (bvslt ((_ zero_extend 10) e38) e41)))
(let ((e95 (bvugt e39 ((_ sign_extend 1) e40))))
(let ((e96 (bvugt e27 ((_ sign_extend 5) v2))))
(let ((e97 (bvule ((_ sign_extend 11) e16) e17)))
(let ((e98 (bvugt e12 ((_ sign_extend 6) v2))))
(let ((e99 (bvsgt ((_ sign_extend 11) e32) e17)))
(let ((e100 (bvsle e26 ((_ sign_extend 5) e25))))
(let ((e101 (bvslt ((_ zero_extend 6) e16) e34)))
(let ((e102 (bvsge ((_ zero_extend 9) v0) e11)))
(let ((e103 (bvsle e41 ((_ sign_extend 5) e34))))
(let ((e104 (bvule ((_ sign_extend 6) e29) e34)))
(let ((e105 (bvsgt e39 e17)))
(let ((e106 (bvuge ((_ sign_extend 2) e16) e18)))
(let ((e107 (bvsle e28 ((_ sign_extend 5) e29))))
(let ((e108 (= ((_ zero_extend 6) e22) e35)))
(let ((e109 (bvsle ((_ sign_extend 2) v3) e9)))
(let ((e110 (bvsgt ((_ zero_extend 8) e36) e27)))
(let ((e111 (bvsge e22 ((_ zero_extend 5) e29))))
(let ((e112 (bvsgt e44 e39)))
(let ((e113 (bvsgt ((_ zero_extend 10) e33) e27)))
(let ((e114 (bvsle ((_ sign_extend 2) e14) e9)))
(let ((e115 (distinct ((_ sign_extend 11) e32) v3)))
(let ((e116 (bvult ((_ zero_extend 10) e25) e40)))
(let ((e117 (bvuge e13 ((_ zero_extend 10) v4))))
(let ((e118 (bvugt ((_ zero_extend 9) v0) e35)))
(let ((e119 (bvslt e44 ((_ sign_extend 6) e28))))
(let ((e120 (bvsgt ((_ zero_extend 5) e16) v2)))
(let ((e121 (= e17 ((_ sign_extend 1) e10))))
(let ((e122 (bvsgt ((_ sign_extend 1) e22) e34)))
(let ((e123 (bvsgt e11 ((_ zero_extend 11) e16))))
(let ((e124 (bvsge ((_ zero_extend 8) v0) v1)))
(let ((e125 (= e58 e61)))
(let ((e126 (ite e120 e109 e121)))
(let ((e127 (not e47)))
(let ((e128 (xor e63 e45)))
(let ((e129 (xor e84 e54)))
(let ((e130 (or e115 e62)))
(let ((e131 (=> e123 e70)))
(let ((e132 (=> e86 e112)))
(let ((e133 (= e65 e126)))
(let ((e134 (= e83 e124)))
(let ((e135 (or e90 e104)))
(let ((e136 (or e110 e57)))
(let ((e137 (not e55)))
(let ((e138 (=> e130 e50)))
(let ((e139 (xor e99 e85)))
(let ((e140 (ite e69 e49 e53)))
(let ((e141 (= e132 e139)))
(let ((e142 (and e82 e114)))
(let ((e143 (not e59)))
(let ((e144 (=> e134 e100)))
(let ((e145 (not e75)))
(let ((e146 (= e94 e128)))
(let ((e147 (xor e103 e146)))
(let ((e148 (and e106 e93)))
(let ((e149 (ite e148 e129 e127)))
(let ((e150 (=> e143 e64)))
(let ((e151 (=> e79 e76)))
(let ((e152 (not e133)))
(let ((e153 (not e77)))
(let ((e154 (=> e135 e107)))
(let ((e155 (and e67 e68)))
(let ((e156 (or e122 e140)))
(let ((e157 (or e60 e51)))
(let ((e158 (=> e154 e118)))
(let ((e159 (not e98)))
(let ((e160 (=> e147 e97)))
(let ((e161 (not e156)))
(let ((e162 (=> e152 e108)))
(let ((e163 (xor e102 e157)))
(let ((e164 (= e78 e153)))
(let ((e165 (=> e56 e158)))
(let ((e166 (ite e144 e144 e138)))
(let ((e167 (xor e160 e116)))
(let ((e168 (ite e88 e131 e74)))
(let ((e169 (xor e137 e150)))
(let ((e170 (or e125 e145)))
(let ((e171 (ite e169 e81 e92)))
(let ((e172 (xor e52 e117)))
(let ((e173 (= e111 e167)))
(let ((e174 (ite e136 e80 e48)))
(let ((e175 (or e141 e96)))
(let ((e176 (xor e159 e165)))
(let ((e177 (ite e151 e119 e161)))
(let ((e178 (ite e91 e172 e71)))
(let ((e179 (and e174 e162)))
(let ((e180 (not e155)))
(let ((e181 (= e164 e168)))
(let ((e182 (or e175 e163)))
(let ((e183 (= e179 e113)))
(let ((e184 (or e176 e101)))
(let ((e185 (xor e73 e184)))
(let ((e186 (= e149 e166)))
(let ((e187 (not e180)))
(let ((e188 (and e183 e89)))
(let ((e189 (and e46 e142)))
(let ((e190 (xor e182 e189)))
(let ((e191 (xor e173 e177)))
(let ((e192 (or e187 e188)))
(let ((e193 (and e171 e181)))
(let ((e194 (or e192 e193)))
(let ((e195 (xor e95 e170)))
(let ((e196 (not e190)))
(let ((e197 (= e186 e185)))
(let ((e198 (= e178 e191)))
(let ((e199 (ite e72 e196 e105)))
(let ((e200 (and e199 e195)))
(let ((e201 (=> e194 e200)))
(let ((e202 (ite e198 e66 e87)))
(let ((e203 (= e202 e201)))
(let ((e204 (and e197 e197)))
(let ((e205 (=> e203 e204)))
(let ((e206 (and e205 (not (= e27 (_ bv0 11))))))
(let ((e207 (and e206 (not (= e27 (bvnot (_ bv0 11)))))))
e207
)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))

(check-sat)
(set-option :regular-output-channel "/dev/null")
(get-model)