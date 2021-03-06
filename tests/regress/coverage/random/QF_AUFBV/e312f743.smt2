(set-info :source |fuzzsmt|)
(set-info :smt-lib-version 2.0)
(set-info :category "random")
(set-info :status unknown)
(set-logic QF_AUFBV)
(declare-fun v0 () (_ BitVec 8))
(declare-fun v1 () (_ BitVec 1))
(declare-fun v2 () (_ BitVec 4))
(declare-fun a3 () (Array  (_ BitVec 16)  (_ BitVec 6)))
(declare-fun a4 () (Array  (_ BitVec 1)  (_ BitVec 14)))
(declare-fun a5 () (Array  (_ BitVec 14)  (_ BitVec 1)))
(assert (let ((e6(_ bv23 5)))
(let ((e7 (ite (bvugt ((_ sign_extend 1) v2) e6) (_ bv1 1) (_ bv0 1))))
(let ((e8 ((_ rotate_right 0) e7)))
(let ((e9 (bvnot v1)))
(let ((e10 (ite (bvugt v0 ((_ zero_extend 3) e6)) (_ bv1 1) (_ bv0 1))))
(let ((e11 (store a4 v1 ((_ sign_extend 6) v0))))
(let ((e12 (select a5 ((_ sign_extend 13) e8))))
(let ((e13 (select a4 ((_ extract 7 7) v0))))
(let ((e14 (select a3 ((_ zero_extend 15) v1))))
(let ((e15 (select a5 ((_ zero_extend 13) v1))))
(let ((e16 (select a5 ((_ sign_extend 9) e6))))
(let ((e17 (ite (bvuge e16 e16) (_ bv1 1) (_ bv0 1))))
(let ((e18 (bvxor v2 ((_ sign_extend 3) v1))))
(let ((e19 (bvsdiv v1 e15)))
(let ((e20 (ite (bvsge e8 v1) (_ bv1 1) (_ bv0 1))))
(let ((e21 (bvmul v2 ((_ zero_extend 3) e7))))
(let ((e22 (bvnot e13)))
(let ((e23 (ite (bvuge e12 e15) (_ bv1 1) (_ bv0 1))))
(let ((e24 (bvneg e9)))
(let ((e25 (bvxor e16 e12)))
(let ((e26 (bvlshr e14 ((_ sign_extend 5) e25))))
(let ((e27 (bvxor ((_ zero_extend 4) e16) e6)))
(let ((e28 (ite (bvsgt ((_ sign_extend 9) e27) e22) (_ bv1 1) (_ bv0 1))))
(let ((e29 (bvlshr e10 e20)))
(let ((e30 (ite (bvugt v0 ((_ sign_extend 4) e21)) (_ bv1 1) (_ bv0 1))))
(let ((e31 (bvule e8 e16)))
(let ((e32 (bvult ((_ sign_extend 3) e15) v2)))
(let ((e33 (bvult e16 e30)))
(let ((e34 (bvsgt e20 v1)))
(let ((e35 (bvsle e14 ((_ zero_extend 2) e18))))
(let ((e36 (bvsge e19 e12)))
(let ((e37 (= ((_ zero_extend 7) e20) v0)))
(let ((e38 (distinct ((_ zero_extend 3) e24) e18)))
(let ((e39 (bvuge e18 ((_ sign_extend 3) e29))))
(let ((e40 (bvsge ((_ zero_extend 3) e30) e18)))
(let ((e41 (bvuge e26 ((_ sign_extend 5) e17))))
(let ((e42 (bvsle ((_ sign_extend 1) e27) e26)))
(let ((e43 (bvsge ((_ zero_extend 7) v1) v0)))
(let ((e44 (bvult e6 ((_ zero_extend 4) e25))))
(let ((e45 (bvule ((_ sign_extend 13) e7) e13)))
(let ((e46 (bvuge e29 v1)))
(let ((e47 (bvule e12 e20)))
(let ((e48 (= e14 ((_ sign_extend 5) e23))))
(let ((e49 (bvuge ((_ zero_extend 5) e28) e26)))
(let ((e50 (bvsgt e21 ((_ zero_extend 3) e15))))
(let ((e51 (bvuge ((_ sign_extend 4) e12) e27)))
(let ((e52 (bvsle ((_ zero_extend 8) e14) e13)))
(let ((e53 (= ((_ zero_extend 3) e29) v2)))
(let ((e54 (distinct e27 e6)))
(let ((e55 (bvule e25 e9)))
(let ((e56 (bvult e26 ((_ zero_extend 5) e19))))
(let ((e57 (bvslt e13 ((_ zero_extend 13) e7))))
(let ((e58 (bvslt e7 e25)))
(let ((e59 (= ((_ zero_extend 3) e12) v2)))
(let ((e60 (bvslt e27 ((_ zero_extend 1) e21))))
(let ((e61 (bvsle ((_ sign_extend 1) e6) e26)))
(let ((e62 (bvugt e23 v1)))
(let ((e63 (bvsge ((_ sign_extend 5) e12) e14)))
(let ((e64 (bvugt e19 e30)))
(let ((e65 (bvsle e8 e23)))
(let ((e66 (bvuge e15 e7)))
(let ((e67 (bvsge e9 e20)))
(let ((e68 (bvule e12 e23)))
(let ((e69 (bvsle e18 e21)))
(let ((e70 (bvslt e25 e28)))
(let ((e71 (bvuge e14 ((_ zero_extend 5) e29))))
(let ((e72 (= e20 e28)))
(let ((e73 (bvslt e14 ((_ sign_extend 5) e19))))
(let ((e74 (bvslt ((_ zero_extend 3) e24) e21)))
(let ((e75 (bvuge e15 e8)))
(let ((e76 (bvuge e9 e25)))
(let ((e77 (bvsge e9 e17)))
(let ((e78 (bvsle ((_ zero_extend 7) e7) v0)))
(let ((e79 (bvsgt ((_ sign_extend 13) e7) e22)))
(let ((e80 (bvsgt e17 e9)))
(let ((e81 (bvsle e27 ((_ sign_extend 4) e15))))
(let ((e82 (distinct e18 ((_ sign_extend 3) e30))))
(let ((e83 (bvslt e14 ((_ sign_extend 5) e17))))
(let ((e84 (bvult e22 ((_ sign_extend 13) v1))))
(let ((e85 (distinct ((_ zero_extend 1) e21) e6)))
(let ((e86 (bvult ((_ zero_extend 5) e25) e26)))
(let ((e87 (bvslt e12 e17)))
(let ((e88 (distinct ((_ zero_extend 2) e14) v0)))
(let ((e89 (bvsge e14 ((_ zero_extend 5) e9))))
(let ((e90 (= e22 ((_ sign_extend 13) e24))))
(let ((e91 (bvuge ((_ sign_extend 13) e16) e13)))
(let ((e92 (bvule ((_ sign_extend 5) e29) e26)))
(let ((e93 (bvslt e23 e19)))
(let ((e94 (bvsgt ((_ zero_extend 5) e30) e14)))
(let ((e95 (bvult e30 e24)))
(let ((e96 (bvsgt e13 ((_ sign_extend 9) e27))))
(let ((e97 (bvult e22 e22)))
(let ((e98 (bvule e14 ((_ sign_extend 5) e23))))
(let ((e99 (bvsgt e20 v1)))
(let ((e100 (bvsge e20 v1)))
(let ((e101 (bvslt e21 ((_ zero_extend 3) e25))))
(let ((e102 (bvsge e22 e22)))
(let ((e103 (= ((_ sign_extend 3) e12) v2)))
(let ((e104 (bvult ((_ sign_extend 4) e10) e6)))
(let ((e105 (ite e83 e43 e98)))
(let ((e106 (and e91 e82)))
(let ((e107 (not e68)))
(let ((e108 (or e84 e76)))
(let ((e109 (not e52)))
(let ((e110 (= e92 e100)))
(let ((e111 (=> e99 e40)))
(let ((e112 (=> e80 e111)))
(let ((e113 (= e77 e35)))
(let ((e114 (=> e46 e55)))
(let ((e115 (not e32)))
(let ((e116 (or e87 e41)))
(let ((e117 (=> e114 e105)))
(let ((e118 (xor e67 e81)))
(let ((e119 (ite e34 e34 e54)))
(let ((e120 (and e50 e103)))
(let ((e121 (not e38)))
(let ((e122 (=> e118 e33)))
(let ((e123 (= e112 e122)))
(let ((e124 (= e88 e64)))
(let ((e125 (or e51 e61)))
(let ((e126 (not e60)))
(let ((e127 (not e95)))
(let ((e128 (ite e39 e115 e127)))
(let ((e129 (xor e101 e121)))
(let ((e130 (=> e106 e120)))
(let ((e131 (or e96 e123)))
(let ((e132 (and e85 e89)))
(let ((e133 (= e104 e117)))
(let ((e134 (ite e93 e73 e125)))
(let ((e135 (or e47 e108)))
(let ((e136 (and e74 e66)))
(let ((e137 (not e113)))
(let ((e138 (ite e90 e44 e110)))
(let ((e139 (and e102 e56)))
(let ((e140 (ite e133 e132 e36)))
(let ((e141 (= e48 e130)))
(let ((e142 (or e135 e31)))
(let ((e143 (ite e69 e42 e78)))
(let ((e144 (=> e136 e107)))
(let ((e145 (ite e75 e70 e49)))
(let ((e146 (xor e116 e94)))
(let ((e147 (and e86 e62)))
(let ((e148 (ite e131 e143 e126)))
(let ((e149 (xor e97 e79)))
(let ((e150 (and e53 e57)))
(let ((e151 (xor e137 e59)))
(let ((e152 (=> e144 e150)))
(let ((e153 (= e129 e138)))
(let ((e154 (=> e152 e147)))
(let ((e155 (or e37 e71)))
(let ((e156 (=> e146 e109)))
(let ((e157 (or e155 e128)))
(let ((e158 (= e134 e139)))
(let ((e159 (ite e156 e153 e153)))
(let ((e160 (xor e72 e148)))
(let ((e161 (not e142)))
(let ((e162 (ite e58 e140 e158)))
(let ((e163 (= e63 e124)))
(let ((e164 (not e163)))
(let ((e165 (not e45)))
(let ((e166 (ite e141 e162 e145)))
(let ((e167 (and e149 e157)))
(let ((e168 (=> e165 e164)))
(let ((e169 (=> e154 e154)))
(let ((e170 (not e119)))
(let ((e171 (and e65 e160)))
(let ((e172 (or e151 e159)))
(let ((e173 (and e171 e166)))
(let ((e174 (or e172 e173)))
(let ((e175 (= e168 e167)))
(let ((e176 (not e170)))
(let ((e177 (and e161 e174)))
(let ((e178 (or e177 e177)))
(let ((e179 (=> e175 e176)))
(let ((e180 (or e179 e179)))
(let ((e181 (and e180 e169)))
(let ((e182 (and e181 e181)))
(let ((e183 (and e182 e178)))
(let ((e184 (and e183 (not (= e15 (_ bv0 1))))))
(let ((e185 (and e184 (not (= e15 (bvnot (_ bv0 1)))))))
e185
)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))

(check-sat)
