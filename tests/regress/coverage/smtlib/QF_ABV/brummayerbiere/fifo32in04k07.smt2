(set-logic QF_ABV)
(set-info :source |
This benchmark comes from bounded model checking of two fifo implementations.
The fifos are resetted once at the beginning.
We try to verify behavioral equivalence with k-induction.
All different constraints are disabled.
Fifo inputs: 'enqueue', 'dequeue', 'reset' (active low) and 'data_in'.
Fifo output: 'empty', 'full' and 'data_out'.
Bit-width: 32
k: 7
The fifos have an internal memory of size 16, respectively modelled as array.

Contributed by Robert Brummayer (robert.brummayer@gmail.com).
|)
(set-info :smt-lib-version 2.0)
(set-info :category "crafted")
(set-info :status sat)
(declare-fun head_fs_0 () (_ BitVec 4))
(declare-fun tail_fs_0 () (_ BitVec 4))
(declare-fun full_fs_0 () (_ BitVec 1))
(declare-fun empty_fs_0 () (_ BitVec 1))
(declare-fun data_out_fs_0 () (_ BitVec 32))
(declare-fun head_fq_0 () (_ BitVec 4))
(declare-fun tail_fq_0 () (_ BitVec 4))
(declare-fun full_fq_0 () (_ BitVec 1))
(declare-fun empty_fq_0 () (_ BitVec 1))
(declare-fun data_out_fq_0 () (_ BitVec 32))
(declare-fun reset_0 () (_ BitVec 1))
(declare-fun a30 () (Array (_ BitVec 4) (_ BitVec 32)))
(declare-fun a31 () (Array (_ BitVec 4) (_ BitVec 32)))
(declare-fun enqeue_0 () (_ BitVec 1))
(declare-fun deqeue_0 () (_ BitVec 1))
(declare-fun data_in_0 () (_ BitVec 32))
(declare-fun head_fs_1 () (_ BitVec 4))
(declare-fun tail_fs_1 () (_ BitVec 4))
(declare-fun full_fs_1 () (_ BitVec 1))
(declare-fun empty_fs_1 () (_ BitVec 1))
(declare-fun data_out_fs_1 () (_ BitVec 32))
(declare-fun head_fq_1 () (_ BitVec 4))
(declare-fun tail_fq_1 () (_ BitVec 4))
(declare-fun full_fq_1 () (_ BitVec 1))
(declare-fun empty_fq_1 () (_ BitVec 1))
(declare-fun data_out_fq_1 () (_ BitVec 32))
(declare-fun reset_1 () (_ BitVec 1))
(declare-fun a141 () (Array (_ BitVec 4) (_ BitVec 32)))
(declare-fun a142 () (Array (_ BitVec 4) (_ BitVec 32)))
(declare-fun enqeue_1 () (_ BitVec 1))
(declare-fun deqeue_1 () (_ BitVec 1))
(declare-fun data_in_1 () (_ BitVec 32))
(declare-fun head_fs_2 () (_ BitVec 4))
(declare-fun tail_fs_2 () (_ BitVec 4))
(declare-fun full_fs_2 () (_ BitVec 1))
(declare-fun empty_fs_2 () (_ BitVec 1))
(declare-fun data_out_fs_2 () (_ BitVec 32))
(declare-fun head_fq_2 () (_ BitVec 4))
(declare-fun tail_fq_2 () (_ BitVec 4))
(declare-fun full_fq_2 () (_ BitVec 1))
(declare-fun empty_fq_2 () (_ BitVec 1))
(declare-fun data_out_fq_2 () (_ BitVec 32))
(declare-fun reset_2 () (_ BitVec 1))
(declare-fun a264 () (Array (_ BitVec 4) (_ BitVec 32)))
(declare-fun a265 () (Array (_ BitVec 4) (_ BitVec 32)))
(declare-fun enqeue_2 () (_ BitVec 1))
(declare-fun deqeue_2 () (_ BitVec 1))
(declare-fun data_in_2 () (_ BitVec 32))
(declare-fun head_fs_3 () (_ BitVec 4))
(declare-fun tail_fs_3 () (_ BitVec 4))
(declare-fun full_fs_3 () (_ BitVec 1))
(declare-fun empty_fs_3 () (_ BitVec 1))
(declare-fun data_out_fs_3 () (_ BitVec 32))
(declare-fun head_fq_3 () (_ BitVec 4))
(declare-fun tail_fq_3 () (_ BitVec 4))
(declare-fun full_fq_3 () (_ BitVec 1))
(declare-fun empty_fq_3 () (_ BitVec 1))
(declare-fun data_out_fq_3 () (_ BitVec 32))
(declare-fun reset_3 () (_ BitVec 1))
(declare-fun a387 () (Array (_ BitVec 4) (_ BitVec 32)))
(declare-fun a388 () (Array (_ BitVec 4) (_ BitVec 32)))
(declare-fun enqeue_3 () (_ BitVec 1))
(declare-fun deqeue_3 () (_ BitVec 1))
(declare-fun data_in_3 () (_ BitVec 32))
(declare-fun head_fs_4 () (_ BitVec 4))
(declare-fun tail_fs_4 () (_ BitVec 4))
(declare-fun full_fs_4 () (_ BitVec 1))
(declare-fun empty_fs_4 () (_ BitVec 1))
(declare-fun data_out_fs_4 () (_ BitVec 32))
(declare-fun head_fq_4 () (_ BitVec 4))
(declare-fun tail_fq_4 () (_ BitVec 4))
(declare-fun full_fq_4 () (_ BitVec 1))
(declare-fun empty_fq_4 () (_ BitVec 1))
(declare-fun data_out_fq_4 () (_ BitVec 32))
(declare-fun reset_4 () (_ BitVec 1))
(declare-fun a510 () (Array (_ BitVec 4) (_ BitVec 32)))
(declare-fun a511 () (Array (_ BitVec 4) (_ BitVec 32)))
(declare-fun enqeue_4 () (_ BitVec 1))
(declare-fun deqeue_4 () (_ BitVec 1))
(declare-fun data_in_4 () (_ BitVec 32))
(declare-fun head_fs_5 () (_ BitVec 4))
(declare-fun tail_fs_5 () (_ BitVec 4))
(declare-fun full_fs_5 () (_ BitVec 1))
(declare-fun empty_fs_5 () (_ BitVec 1))
(declare-fun data_out_fs_5 () (_ BitVec 32))
(declare-fun head_fq_5 () (_ BitVec 4))
(declare-fun tail_fq_5 () (_ BitVec 4))
(declare-fun full_fq_5 () (_ BitVec 1))
(declare-fun empty_fq_5 () (_ BitVec 1))
(declare-fun data_out_fq_5 () (_ BitVec 32))
(declare-fun reset_5 () (_ BitVec 1))
(declare-fun a633 () (Array (_ BitVec 4) (_ BitVec 32)))
(declare-fun a634 () (Array (_ BitVec 4) (_ BitVec 32)))
(declare-fun enqeue_5 () (_ BitVec 1))
(declare-fun deqeue_5 () (_ BitVec 1))
(declare-fun data_in_5 () (_ BitVec 32))
(declare-fun head_fs_6 () (_ BitVec 4))
(declare-fun tail_fs_6 () (_ BitVec 4))
(declare-fun full_fs_6 () (_ BitVec 1))
(declare-fun empty_fs_6 () (_ BitVec 1))
(declare-fun data_out_fs_6 () (_ BitVec 32))
(declare-fun head_fq_6 () (_ BitVec 4))
(declare-fun tail_fq_6 () (_ BitVec 4))
(declare-fun full_fq_6 () (_ BitVec 1))
(declare-fun empty_fq_6 () (_ BitVec 1))
(declare-fun data_out_fq_6 () (_ BitVec 32))
(declare-fun reset_6 () (_ BitVec 1))
(declare-fun a756 () (Array (_ BitVec 4) (_ BitVec 32)))
(declare-fun a757 () (Array (_ BitVec 4) (_ BitVec 32)))
(declare-fun enqeue_6 () (_ BitVec 1))
(declare-fun deqeue_6 () (_ BitVec 1))
(declare-fun data_in_6 () (_ BitVec 32))
(declare-fun head_fs_7 () (_ BitVec 4))
(declare-fun tail_fs_7 () (_ BitVec 4))
(declare-fun full_fs_7 () (_ BitVec 1))
(declare-fun empty_fs_7 () (_ BitVec 1))
(declare-fun data_out_fs_7 () (_ BitVec 32))
(declare-fun head_fq_7 () (_ BitVec 4))
(declare-fun tail_fq_7 () (_ BitVec 4))
(declare-fun full_fq_7 () (_ BitVec 1))
(declare-fun empty_fq_7 () (_ BitVec 1))
(declare-fun data_out_fq_7 () (_ BitVec 32))
(declare-fun reset_7 () (_ BitVec 1))
(declare-fun a879 () (Array (_ BitVec 4) (_ BitVec 32)))
(declare-fun a880 () (Array (_ BitVec 4) (_ BitVec 32)))
(assert (let ((?v_55 (= (_ bv1 1) full_fs_0)) (?v_50 (= (_ bv1 1) enqeue_0)) (?v_49 (= (_ bv1 1) (bvand (bvnot (bvand (bvnot enqeue_0) (bvnot deqeue_0))) (bvnot (bvand enqeue_0 deqeue_0))))) (?v_48 (= (_ bv1 1) reset_0)) (?v_53 (= (_ bv1 1) deqeue_0)) (?v_54 (bvadd (_ bv1 4) head_fq_0)) (?v_52 (bvadd (_ bv1 4) tail_fq_0)) (?v_51 (= (_ bv1 1) full_fq_0)) (?v_47 (= (_ bv1 1) full_fs_1)) (?v_42 (= (_ bv1 1) enqeue_1)) (?v_41 (= (_ bv1 1) (bvand (bvnot (bvand (bvnot enqeue_1) (bvnot deqeue_1))) (bvnot (bvand enqeue_1 deqeue_1))))) (?v_40 (= (_ bv1 1) reset_1)) (?v_45 (= (_ bv1 1) deqeue_1)) (?v_46 (bvadd (_ bv1 4) head_fq_1)) (?v_44 (bvadd (_ bv1 4) tail_fq_1)) (?v_43 (= (_ bv1 1) full_fq_1)) (?v_39 (= (_ bv1 1) full_fs_2)) (?v_34 (= (_ bv1 1) enqeue_2)) (?v_33 (= (_ bv1 1) (bvand (bvnot (bvand (bvnot enqeue_2) (bvnot deqeue_2))) (bvnot (bvand enqeue_2 deqeue_2))))) (?v_32 (= (_ bv1 1) reset_2)) (?v_37 (= (_ bv1 1) deqeue_2)) (?v_38 (bvadd (_ bv1 4) head_fq_2)) (?v_36 (bvadd (_ bv1 4) tail_fq_2)) (?v_35 (= (_ bv1 1) full_fq_2)) (?v_31 (= (_ bv1 1) full_fs_3)) (?v_26 (= (_ bv1 1) enqeue_3)) (?v_25 (= (_ bv1 1) (bvand (bvnot (bvand (bvnot enqeue_3) (bvnot deqeue_3))) (bvnot (bvand enqeue_3 deqeue_3))))) (?v_24 (= (_ bv1 1) reset_3)) (?v_29 (= (_ bv1 1) deqeue_3)) (?v_30 (bvadd (_ bv1 4) head_fq_3)) (?v_28 (bvadd (_ bv1 4) tail_fq_3)) (?v_27 (= (_ bv1 1) full_fq_3)) (?v_23 (= (_ bv1 1) full_fs_4)) (?v_18 (= (_ bv1 1) enqeue_4)) (?v_17 (= (_ bv1 1) (bvand (bvnot (bvand (bvnot enqeue_4) (bvnot deqeue_4))) (bvnot (bvand enqeue_4 deqeue_4))))) (?v_16 (= (_ bv1 1) reset_4)) (?v_21 (= (_ bv1 1) deqeue_4)) (?v_22 (bvadd (_ bv1 4) head_fq_4)) (?v_20 (bvadd (_ bv1 4) tail_fq_4)) (?v_19 (= (_ bv1 1) full_fq_4)) (?v_15 (= (_ bv1 1) full_fs_5)) (?v_10 (= (_ bv1 1) enqeue_5)) (?v_9 (= (_ bv1 1) (bvand (bvnot (bvand (bvnot enqeue_5) (bvnot deqeue_5))) (bvnot (bvand enqeue_5 deqeue_5))))) (?v_8 (= (_ bv1 1) reset_5)) (?v_13 (= (_ bv1 1) deqeue_5)) (?v_14 (bvadd (_ bv1 4) head_fq_5)) (?v_12 (bvadd (_ bv1 4) tail_fq_5)) (?v_11 (= (_ bv1 1) full_fq_5)) (?v_7 (= (_ bv1 1) full_fs_6)) (?v_2 (= (_ bv1 1) enqeue_6)) (?v_1 (= (_ bv1 1) (bvand (bvnot (bvand (bvnot enqeue_6) (bvnot deqeue_6))) (bvnot (bvand enqeue_6 deqeue_6))))) (?v_0 (= (_ bv1 1) reset_6)) (?v_5 (= (_ bv1 1) deqeue_6)) (?v_6 (bvadd (_ bv1 4) head_fq_6)) (?v_4 (bvadd (_ bv1 4) tail_fq_6)) (?v_3 (= (_ bv1 1) full_fq_6))) (not (= (bvand reset_7 (bvand (bvnot (bvand (ite (= data_out_fs_7 data_out_fq_7) (_ bv1 1) (_ bv0 1)) (bvand (ite (= full_fs_7 full_fq_7) (_ bv1 1) (_ bv0 1)) (ite (= empty_fs_7 empty_fq_7) (_ bv1 1) (_ bv0 1))))) (bvand reset_7 (bvand (ite (= (ite ?v_0 (ite ?v_1 (ite ?v_2 (ite ?v_3 a757 (store a757 tail_fq_6 data_in_6)) a757) a757) a757) a880) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_0 (ite ?v_1 (ite (= (_ bv1 1) (bvand (bvnot empty_fq_6) deqeue_6)) (select a757 head_fq_6) data_out_fq_6) data_out_fq_6) data_out_fq_6) data_out_fq_7) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_0 (ite ?v_1 (ite ?v_2 (_ bv0 1) (ite (= (_ bv1 1) (ite (= tail_fq_6 ?v_6) (_ bv1 1) (_ bv0 1))) (_ bv1 1) empty_fq_6)) empty_fq_6) (_ bv1 1)) empty_fq_7) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_0 (ite ?v_1 (ite ?v_5 (_ bv0 1) (ite (= (_ bv1 1) (ite (= head_fq_6 (bvadd (_ bv1 4) ?v_4)) (_ bv1 1) (_ bv0 1))) (_ bv1 1) full_fq_6)) full_fq_6) (_ bv0 1)) full_fq_7) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_0 (ite ?v_1 (ite ?v_2 (ite ?v_3 tail_fq_6 ?v_4) tail_fq_6) tail_fq_6) (_ bv0 4)) tail_fq_7) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_0 (ite ?v_1 (ite ?v_5 (ite (= (_ bv1 1) empty_fq_6) head_fq_6 ?v_6) head_fq_6) head_fq_6) (_ bv0 4)) head_fq_7) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_0 (ite ?v_1 (ite ?v_2 (ite ?v_7 a756 (store a756 tail_fs_6 data_in_6)) (store (store (store (store (store (store (store (store (store (store (store (store (store (store a756 (_ bv0 4) (select a756 (_ bv1 4))) (_ bv1 4) (select a756 (_ bv2 4))) (_ bv2 4) (select a756 (_ bv3 4))) (_ bv3 4) (select a756 (_ bv4 4))) (_ bv4 4) (select a756 (_ bv5 4))) (_ bv5 4) (select a756 (_ bv6 4))) (_ bv6 4) (select a756 (_ bv7 4))) (_ bv7 4) (select a756 (_ bv8 4))) (_ bv8 4) (select a756 (_ bv9 4))) (_ bv9 4) (select a756 (_ bv10 4))) (_ bv10 4) (select a756 (_ bv11 4))) (_ bv11 4) (select a756 (_ bv12 4))) (_ bv12 4) (select a756 (_ bv13 4))) (_ bv13 4) (select a756 (_ bv14 4)))) a756) a756) a879) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_0 (ite ?v_1 (ite (= (_ bv1 1) (bvand (bvnot empty_fs_6) deqeue_6)) (select a756 head_fs_6) data_out_fs_6) data_out_fs_6) data_out_fs_6) data_out_fs_7) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_0 (ite ?v_1 (ite ?v_2 (_ bv0 1) (ite (= (_ bv1 1) (ite (= (_ bv1 4) tail_fs_6) (_ bv1 1) (_ bv0 1))) (_ bv1 1) empty_fs_6)) empty_fs_6) (_ bv1 1)) empty_fs_7) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_0 (ite ?v_1 (ite ?v_5 (_ bv0 1) (ite (= (_ bv1 1) (ite (= (_ bv14 4) tail_fs_6) (_ bv1 1) (_ bv0 1))) (_ bv1 1) full_fs_6)) full_fs_6) (_ bv0 1)) full_fs_7) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_0 (ite ?v_1 (ite ?v_2 (ite ?v_7 tail_fs_6 (bvadd (_ bv1 4) tail_fs_6)) (ite (= (_ bv1 1) empty_fs_6) tail_fs_6 (bvadd (_ bv15 4) tail_fs_6))) tail_fs_6) (_ bv0 4)) tail_fs_7) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (_ bv0 4) head_fs_7) (_ bv1 1) (_ bv0 1)) (bvand (bvnot (bvand reset_6 (bvnot (bvand (ite (= data_out_fs_6 data_out_fq_6) (_ bv1 1) (_ bv0 1)) (bvand (ite (= full_fs_6 full_fq_6) (_ bv1 1) (_ bv0 1)) (ite (= empty_fs_6 empty_fq_6) (_ bv1 1) (_ bv0 1))))))) (bvand reset_6 (bvand (ite (= (ite ?v_8 (ite ?v_9 (ite ?v_10 (ite ?v_11 a634 (store a634 tail_fq_5 data_in_5)) a634) a634) a634) a757) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_8 (ite ?v_9 (ite (= (_ bv1 1) (bvand (bvnot empty_fq_5) deqeue_5)) (select a634 head_fq_5) data_out_fq_5) data_out_fq_5) data_out_fq_5) data_out_fq_6) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_8 (ite ?v_9 (ite ?v_10 (_ bv0 1) (ite (= (_ bv1 1) (ite (= tail_fq_5 ?v_14) (_ bv1 1) (_ bv0 1))) (_ bv1 1) empty_fq_5)) empty_fq_5) (_ bv1 1)) empty_fq_6) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_8 (ite ?v_9 (ite ?v_13 (_ bv0 1) (ite (= (_ bv1 1) (ite (= head_fq_5 (bvadd (_ bv1 4) ?v_12)) (_ bv1 1) (_ bv0 1))) (_ bv1 1) full_fq_5)) full_fq_5) (_ bv0 1)) full_fq_6) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_8 (ite ?v_9 (ite ?v_10 (ite ?v_11 tail_fq_5 ?v_12) tail_fq_5) tail_fq_5) (_ bv0 4)) tail_fq_6) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_8 (ite ?v_9 (ite ?v_13 (ite (= (_ bv1 1) empty_fq_5) head_fq_5 ?v_14) head_fq_5) head_fq_5) (_ bv0 4)) head_fq_6) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_8 (ite ?v_9 (ite ?v_10 (ite ?v_15 a633 (store a633 tail_fs_5 data_in_5)) (store (store (store (store (store (store (store (store (store (store (store (store (store (store a633 (_ bv0 4) (select a633 (_ bv1 4))) (_ bv1 4) (select a633 (_ bv2 4))) (_ bv2 4) (select a633 (_ bv3 4))) (_ bv3 4) (select a633 (_ bv4 4))) (_ bv4 4) (select a633 (_ bv5 4))) (_ bv5 4) (select a633 (_ bv6 4))) (_ bv6 4) (select a633 (_ bv7 4))) (_ bv7 4) (select a633 (_ bv8 4))) (_ bv8 4) (select a633 (_ bv9 4))) (_ bv9 4) (select a633 (_ bv10 4))) (_ bv10 4) (select a633 (_ bv11 4))) (_ bv11 4) (select a633 (_ bv12 4))) (_ bv12 4) (select a633 (_ bv13 4))) (_ bv13 4) (select a633 (_ bv14 4)))) a633) a633) a756) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_8 (ite ?v_9 (ite (= (_ bv1 1) (bvand (bvnot empty_fs_5) deqeue_5)) (select a633 head_fs_5) data_out_fs_5) data_out_fs_5) data_out_fs_5) data_out_fs_6) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_8 (ite ?v_9 (ite ?v_10 (_ bv0 1) (ite (= (_ bv1 1) (ite (= (_ bv1 4) tail_fs_5) (_ bv1 1) (_ bv0 1))) (_ bv1 1) empty_fs_5)) empty_fs_5) (_ bv1 1)) empty_fs_6) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_8 (ite ?v_9 (ite ?v_13 (_ bv0 1) (ite (= (_ bv1 1) (ite (= (_ bv14 4) tail_fs_5) (_ bv1 1) (_ bv0 1))) (_ bv1 1) full_fs_5)) full_fs_5) (_ bv0 1)) full_fs_6) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_8 (ite ?v_9 (ite ?v_10 (ite ?v_15 tail_fs_5 (bvadd (_ bv1 4) tail_fs_5)) (ite (= (_ bv1 1) empty_fs_5) tail_fs_5 (bvadd (_ bv15 4) tail_fs_5))) tail_fs_5) (_ bv0 4)) tail_fs_6) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (_ bv0 4) head_fs_6) (_ bv1 1) (_ bv0 1)) (bvand (bvnot (bvand reset_5 (bvnot (bvand (ite (= data_out_fs_5 data_out_fq_5) (_ bv1 1) (_ bv0 1)) (bvand (ite (= full_fs_5 full_fq_5) (_ bv1 1) (_ bv0 1)) (ite (= empty_fs_5 empty_fq_5) (_ bv1 1) (_ bv0 1))))))) (bvand reset_5 (bvand (ite (= (ite ?v_16 (ite ?v_17 (ite ?v_18 (ite ?v_19 a511 (store a511 tail_fq_4 data_in_4)) a511) a511) a511) a634) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_16 (ite ?v_17 (ite (= (_ bv1 1) (bvand (bvnot empty_fq_4) deqeue_4)) (select a511 head_fq_4) data_out_fq_4) data_out_fq_4) data_out_fq_4) data_out_fq_5) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_16 (ite ?v_17 (ite ?v_18 (_ bv0 1) (ite (= (_ bv1 1) (ite (= tail_fq_4 ?v_22) (_ bv1 1) (_ bv0 1))) (_ bv1 1) empty_fq_4)) empty_fq_4) (_ bv1 1)) empty_fq_5) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_16 (ite ?v_17 (ite ?v_21 (_ bv0 1) (ite (= (_ bv1 1) (ite (= head_fq_4 (bvadd (_ bv1 4) ?v_20)) (_ bv1 1) (_ bv0 1))) (_ bv1 1) full_fq_4)) full_fq_4) (_ bv0 1)) full_fq_5) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_16 (ite ?v_17 (ite ?v_18 (ite ?v_19 tail_fq_4 ?v_20) tail_fq_4) tail_fq_4) (_ bv0 4)) tail_fq_5) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_16 (ite ?v_17 (ite ?v_21 (ite (= (_ bv1 1) empty_fq_4) head_fq_4 ?v_22) head_fq_4) head_fq_4) (_ bv0 4)) head_fq_5) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_16 (ite ?v_17 (ite ?v_18 (ite ?v_23 a510 (store a510 tail_fs_4 data_in_4)) (store (store (store (store (store (store (store (store (store (store (store (store (store (store a510 (_ bv0 4) (select a510 (_ bv1 4))) (_ bv1 4) (select a510 (_ bv2 4))) (_ bv2 4) (select a510 (_ bv3 4))) (_ bv3 4) (select a510 (_ bv4 4))) (_ bv4 4) (select a510 (_ bv5 4))) (_ bv5 4) (select a510 (_ bv6 4))) (_ bv6 4) (select a510 (_ bv7 4))) (_ bv7 4) (select a510 (_ bv8 4))) (_ bv8 4) (select a510 (_ bv9 4))) (_ bv9 4) (select a510 (_ bv10 4))) (_ bv10 4) (select a510 (_ bv11 4))) (_ bv11 4) (select a510 (_ bv12 4))) (_ bv12 4) (select a510 (_ bv13 4))) (_ bv13 4) (select a510 (_ bv14 4)))) a510) a510) a633) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_16 (ite ?v_17 (ite (= (_ bv1 1) (bvand (bvnot empty_fs_4) deqeue_4)) (select a510 head_fs_4) data_out_fs_4) data_out_fs_4) data_out_fs_4) data_out_fs_5) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_16 (ite ?v_17 (ite ?v_18 (_ bv0 1) (ite (= (_ bv1 1) (ite (= (_ bv1 4) tail_fs_4) (_ bv1 1) (_ bv0 1))) (_ bv1 1) empty_fs_4)) empty_fs_4) (_ bv1 1)) empty_fs_5) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_16 (ite ?v_17 (ite ?v_21 (_ bv0 1) (ite (= (_ bv1 1) (ite (= (_ bv14 4) tail_fs_4) (_ bv1 1) (_ bv0 1))) (_ bv1 1) full_fs_4)) full_fs_4) (_ bv0 1)) full_fs_5) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_16 (ite ?v_17 (ite ?v_18 (ite ?v_23 tail_fs_4 (bvadd (_ bv1 4) tail_fs_4)) (ite (= (_ bv1 1) empty_fs_4) tail_fs_4 (bvadd (_ bv15 4) tail_fs_4))) tail_fs_4) (_ bv0 4)) tail_fs_5) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (_ bv0 4) head_fs_5) (_ bv1 1) (_ bv0 1)) (bvand (bvnot (bvand reset_4 (bvnot (bvand (ite (= data_out_fs_4 data_out_fq_4) (_ bv1 1) (_ bv0 1)) (bvand (ite (= full_fs_4 full_fq_4) (_ bv1 1) (_ bv0 1)) (ite (= empty_fs_4 empty_fq_4) (_ bv1 1) (_ bv0 1))))))) (bvand reset_4 (bvand (ite (= (ite ?v_24 (ite ?v_25 (ite ?v_26 (ite ?v_27 a388 (store a388 tail_fq_3 data_in_3)) a388) a388) a388) a511) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_24 (ite ?v_25 (ite (= (_ bv1 1) (bvand (bvnot empty_fq_3) deqeue_3)) (select a388 head_fq_3) data_out_fq_3) data_out_fq_3) data_out_fq_3) data_out_fq_4) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_24 (ite ?v_25 (ite ?v_26 (_ bv0 1) (ite (= (_ bv1 1) (ite (= tail_fq_3 ?v_30) (_ bv1 1) (_ bv0 1))) (_ bv1 1) empty_fq_3)) empty_fq_3) (_ bv1 1)) empty_fq_4) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_24 (ite ?v_25 (ite ?v_29 (_ bv0 1) (ite (= (_ bv1 1) (ite (= head_fq_3 (bvadd (_ bv1 4) ?v_28)) (_ bv1 1) (_ bv0 1))) (_ bv1 1) full_fq_3)) full_fq_3) (_ bv0 1)) full_fq_4) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_24 (ite ?v_25 (ite ?v_26 (ite ?v_27 tail_fq_3 ?v_28) tail_fq_3) tail_fq_3) (_ bv0 4)) tail_fq_4) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_24 (ite ?v_25 (ite ?v_29 (ite (= (_ bv1 1) empty_fq_3) head_fq_3 ?v_30) head_fq_3) head_fq_3) (_ bv0 4)) head_fq_4) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_24 (ite ?v_25 (ite ?v_26 (ite ?v_31 a387 (store a387 tail_fs_3 data_in_3)) (store (store (store (store (store (store (store (store (store (store (store (store (store (store a387 (_ bv0 4) (select a387 (_ bv1 4))) (_ bv1 4) (select a387 (_ bv2 4))) (_ bv2 4) (select a387 (_ bv3 4))) (_ bv3 4) (select a387 (_ bv4 4))) (_ bv4 4) (select a387 (_ bv5 4))) (_ bv5 4) (select a387 (_ bv6 4))) (_ bv6 4) (select a387 (_ bv7 4))) (_ bv7 4) (select a387 (_ bv8 4))) (_ bv8 4) (select a387 (_ bv9 4))) (_ bv9 4) (select a387 (_ bv10 4))) (_ bv10 4) (select a387 (_ bv11 4))) (_ bv11 4) (select a387 (_ bv12 4))) (_ bv12 4) (select a387 (_ bv13 4))) (_ bv13 4) (select a387 (_ bv14 4)))) a387) a387) a510) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_24 (ite ?v_25 (ite (= (_ bv1 1) (bvand (bvnot empty_fs_3) deqeue_3)) (select a387 head_fs_3) data_out_fs_3) data_out_fs_3) data_out_fs_3) data_out_fs_4) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_24 (ite ?v_25 (ite ?v_26 (_ bv0 1) (ite (= (_ bv1 1) (ite (= (_ bv1 4) tail_fs_3) (_ bv1 1) (_ bv0 1))) (_ bv1 1) empty_fs_3)) empty_fs_3) (_ bv1 1)) empty_fs_4) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_24 (ite ?v_25 (ite ?v_29 (_ bv0 1) (ite (= (_ bv1 1) (ite (= (_ bv14 4) tail_fs_3) (_ bv1 1) (_ bv0 1))) (_ bv1 1) full_fs_3)) full_fs_3) (_ bv0 1)) full_fs_4) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_24 (ite ?v_25 (ite ?v_26 (ite ?v_31 tail_fs_3 (bvadd (_ bv1 4) tail_fs_3)) (ite (= (_ bv1 1) empty_fs_3) tail_fs_3 (bvadd (_ bv15 4) tail_fs_3))) tail_fs_3) (_ bv0 4)) tail_fs_4) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (_ bv0 4) head_fs_4) (_ bv1 1) (_ bv0 1)) (bvand (bvnot (bvand reset_3 (bvnot (bvand (ite (= data_out_fs_3 data_out_fq_3) (_ bv1 1) (_ bv0 1)) (bvand (ite (= full_fs_3 full_fq_3) (_ bv1 1) (_ bv0 1)) (ite (= empty_fs_3 empty_fq_3) (_ bv1 1) (_ bv0 1))))))) (bvand reset_3 (bvand (ite (= (ite ?v_32 (ite ?v_33 (ite ?v_34 (ite ?v_35 a265 (store a265 tail_fq_2 data_in_2)) a265) a265) a265) a388) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_32 (ite ?v_33 (ite (= (_ bv1 1) (bvand (bvnot empty_fq_2) deqeue_2)) (select a265 head_fq_2) data_out_fq_2) data_out_fq_2) data_out_fq_2) data_out_fq_3) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_32 (ite ?v_33 (ite ?v_34 (_ bv0 1) (ite (= (_ bv1 1) (ite (= tail_fq_2 ?v_38) (_ bv1 1) (_ bv0 1))) (_ bv1 1) empty_fq_2)) empty_fq_2) (_ bv1 1)) empty_fq_3) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_32 (ite ?v_33 (ite ?v_37 (_ bv0 1) (ite (= (_ bv1 1) (ite (= head_fq_2 (bvadd (_ bv1 4) ?v_36)) (_ bv1 1) (_ bv0 1))) (_ bv1 1) full_fq_2)) full_fq_2) (_ bv0 1)) full_fq_3) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_32 (ite ?v_33 (ite ?v_34 (ite ?v_35 tail_fq_2 ?v_36) tail_fq_2) tail_fq_2) (_ bv0 4)) tail_fq_3) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_32 (ite ?v_33 (ite ?v_37 (ite (= (_ bv1 1) empty_fq_2) head_fq_2 ?v_38) head_fq_2) head_fq_2) (_ bv0 4)) head_fq_3) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_32 (ite ?v_33 (ite ?v_34 (ite ?v_39 a264 (store a264 tail_fs_2 data_in_2)) (store (store (store (store (store (store (store (store (store (store (store (store (store (store a264 (_ bv0 4) (select a264 (_ bv1 4))) (_ bv1 4) (select a264 (_ bv2 4))) (_ bv2 4) (select a264 (_ bv3 4))) (_ bv3 4) (select a264 (_ bv4 4))) (_ bv4 4) (select a264 (_ bv5 4))) (_ bv5 4) (select a264 (_ bv6 4))) (_ bv6 4) (select a264 (_ bv7 4))) (_ bv7 4) (select a264 (_ bv8 4))) (_ bv8 4) (select a264 (_ bv9 4))) (_ bv9 4) (select a264 (_ bv10 4))) (_ bv10 4) (select a264 (_ bv11 4))) (_ bv11 4) (select a264 (_ bv12 4))) (_ bv12 4) (select a264 (_ bv13 4))) (_ bv13 4) (select a264 (_ bv14 4)))) a264) a264) a387) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_32 (ite ?v_33 (ite (= (_ bv1 1) (bvand (bvnot empty_fs_2) deqeue_2)) (select a264 head_fs_2) data_out_fs_2) data_out_fs_2) data_out_fs_2) data_out_fs_3) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_32 (ite ?v_33 (ite ?v_34 (_ bv0 1) (ite (= (_ bv1 1) (ite (= (_ bv1 4) tail_fs_2) (_ bv1 1) (_ bv0 1))) (_ bv1 1) empty_fs_2)) empty_fs_2) (_ bv1 1)) empty_fs_3) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_32 (ite ?v_33 (ite ?v_37 (_ bv0 1) (ite (= (_ bv1 1) (ite (= (_ bv14 4) tail_fs_2) (_ bv1 1) (_ bv0 1))) (_ bv1 1) full_fs_2)) full_fs_2) (_ bv0 1)) full_fs_3) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_32 (ite ?v_33 (ite ?v_34 (ite ?v_39 tail_fs_2 (bvadd (_ bv1 4) tail_fs_2)) (ite (= (_ bv1 1) empty_fs_2) tail_fs_2 (bvadd (_ bv15 4) tail_fs_2))) tail_fs_2) (_ bv0 4)) tail_fs_3) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (_ bv0 4) head_fs_3) (_ bv1 1) (_ bv0 1)) (bvand (bvnot (bvand reset_2 (bvnot (bvand (ite (= data_out_fs_2 data_out_fq_2) (_ bv1 1) (_ bv0 1)) (bvand (ite (= full_fs_2 full_fq_2) (_ bv1 1) (_ bv0 1)) (ite (= empty_fs_2 empty_fq_2) (_ bv1 1) (_ bv0 1))))))) (bvand reset_2 (bvand (ite (= (ite ?v_40 (ite ?v_41 (ite ?v_42 (ite ?v_43 a142 (store a142 tail_fq_1 data_in_1)) a142) a142) a142) a265) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_40 (ite ?v_41 (ite (= (_ bv1 1) (bvand (bvnot empty_fq_1) deqeue_1)) (select a142 head_fq_1) data_out_fq_1) data_out_fq_1) data_out_fq_1) data_out_fq_2) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_40 (ite ?v_41 (ite ?v_42 (_ bv0 1) (ite (= (_ bv1 1) (ite (= tail_fq_1 ?v_46) (_ bv1 1) (_ bv0 1))) (_ bv1 1) empty_fq_1)) empty_fq_1) (_ bv1 1)) empty_fq_2) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_40 (ite ?v_41 (ite ?v_45 (_ bv0 1) (ite (= (_ bv1 1) (ite (= head_fq_1 (bvadd (_ bv1 4) ?v_44)) (_ bv1 1) (_ bv0 1))) (_ bv1 1) full_fq_1)) full_fq_1) (_ bv0 1)) full_fq_2) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_40 (ite ?v_41 (ite ?v_42 (ite ?v_43 tail_fq_1 ?v_44) tail_fq_1) tail_fq_1) (_ bv0 4)) tail_fq_2) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_40 (ite ?v_41 (ite ?v_45 (ite (= (_ bv1 1) empty_fq_1) head_fq_1 ?v_46) head_fq_1) head_fq_1) (_ bv0 4)) head_fq_2) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_40 (ite ?v_41 (ite ?v_42 (ite ?v_47 a141 (store a141 tail_fs_1 data_in_1)) (store (store (store (store (store (store (store (store (store (store (store (store (store (store a141 (_ bv0 4) (select a141 (_ bv1 4))) (_ bv1 4) (select a141 (_ bv2 4))) (_ bv2 4) (select a141 (_ bv3 4))) (_ bv3 4) (select a141 (_ bv4 4))) (_ bv4 4) (select a141 (_ bv5 4))) (_ bv5 4) (select a141 (_ bv6 4))) (_ bv6 4) (select a141 (_ bv7 4))) (_ bv7 4) (select a141 (_ bv8 4))) (_ bv8 4) (select a141 (_ bv9 4))) (_ bv9 4) (select a141 (_ bv10 4))) (_ bv10 4) (select a141 (_ bv11 4))) (_ bv11 4) (select a141 (_ bv12 4))) (_ bv12 4) (select a141 (_ bv13 4))) (_ bv13 4) (select a141 (_ bv14 4)))) a141) a141) a264) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_40 (ite ?v_41 (ite (= (_ bv1 1) (bvand (bvnot empty_fs_1) deqeue_1)) (select a141 head_fs_1) data_out_fs_1) data_out_fs_1) data_out_fs_1) data_out_fs_2) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_40 (ite ?v_41 (ite ?v_42 (_ bv0 1) (ite (= (_ bv1 1) (ite (= (_ bv1 4) tail_fs_1) (_ bv1 1) (_ bv0 1))) (_ bv1 1) empty_fs_1)) empty_fs_1) (_ bv1 1)) empty_fs_2) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_40 (ite ?v_41 (ite ?v_45 (_ bv0 1) (ite (= (_ bv1 1) (ite (= (_ bv14 4) tail_fs_1) (_ bv1 1) (_ bv0 1))) (_ bv1 1) full_fs_1)) full_fs_1) (_ bv0 1)) full_fs_2) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_40 (ite ?v_41 (ite ?v_42 (ite ?v_47 tail_fs_1 (bvadd (_ bv1 4) tail_fs_1)) (ite (= (_ bv1 1) empty_fs_1) tail_fs_1 (bvadd (_ bv15 4) tail_fs_1))) tail_fs_1) (_ bv0 4)) tail_fs_2) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (_ bv0 4) head_fs_2) (_ bv1 1) (_ bv0 1)) (bvand (bvnot (bvand reset_1 (bvnot (bvand (ite (= data_out_fs_1 data_out_fq_1) (_ bv1 1) (_ bv0 1)) (bvand (ite (= full_fs_1 full_fq_1) (_ bv1 1) (_ bv0 1)) (ite (= empty_fs_1 empty_fq_1) (_ bv1 1) (_ bv0 1))))))) (bvand reset_1 (bvand (ite (= (ite ?v_48 (ite ?v_49 (ite ?v_50 (ite ?v_51 a31 (store a31 tail_fq_0 data_in_0)) a31) a31) a31) a142) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_48 (ite ?v_49 (ite (= (_ bv1 1) (bvand (bvnot empty_fq_0) deqeue_0)) (select a31 head_fq_0) data_out_fq_0) data_out_fq_0) data_out_fq_0) data_out_fq_1) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_48 (ite ?v_49 (ite ?v_50 (_ bv0 1) (ite (= (_ bv1 1) (ite (= tail_fq_0 ?v_54) (_ bv1 1) (_ bv0 1))) (_ bv1 1) empty_fq_0)) empty_fq_0) (_ bv1 1)) empty_fq_1) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_48 (ite ?v_49 (ite ?v_53 (_ bv0 1) (ite (= (_ bv1 1) (ite (= head_fq_0 (bvadd (_ bv1 4) ?v_52)) (_ bv1 1) (_ bv0 1))) (_ bv1 1) full_fq_0)) full_fq_0) (_ bv0 1)) full_fq_1) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_48 (ite ?v_49 (ite ?v_50 (ite ?v_51 tail_fq_0 ?v_52) tail_fq_0) tail_fq_0) (_ bv0 4)) tail_fq_1) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_48 (ite ?v_49 (ite ?v_53 (ite (= (_ bv1 1) empty_fq_0) head_fq_0 ?v_54) head_fq_0) head_fq_0) (_ bv0 4)) head_fq_1) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_48 (ite ?v_49 (ite ?v_50 (ite ?v_55 a30 (store a30 tail_fs_0 data_in_0)) (store (store (store (store (store (store (store (store (store (store (store (store (store (store a30 (_ bv0 4) (select a30 (_ bv1 4))) (_ bv1 4) (select a30 (_ bv2 4))) (_ bv2 4) (select a30 (_ bv3 4))) (_ bv3 4) (select a30 (_ bv4 4))) (_ bv4 4) (select a30 (_ bv5 4))) (_ bv5 4) (select a30 (_ bv6 4))) (_ bv6 4) (select a30 (_ bv7 4))) (_ bv7 4) (select a30 (_ bv8 4))) (_ bv8 4) (select a30 (_ bv9 4))) (_ bv9 4) (select a30 (_ bv10 4))) (_ bv10 4) (select a30 (_ bv11 4))) (_ bv11 4) (select a30 (_ bv12 4))) (_ bv12 4) (select a30 (_ bv13 4))) (_ bv13 4) (select a30 (_ bv14 4)))) a30) a30) a141) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_48 (ite ?v_49 (ite (= (_ bv1 1) (bvand (bvnot empty_fs_0) deqeue_0)) (select a30 head_fs_0) data_out_fs_0) data_out_fs_0) data_out_fs_0) data_out_fs_1) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_48 (ite ?v_49 (ite ?v_50 (_ bv0 1) (ite (= (_ bv1 1) (ite (= (_ bv1 4) tail_fs_0) (_ bv1 1) (_ bv0 1))) (_ bv1 1) empty_fs_0)) empty_fs_0) (_ bv1 1)) empty_fs_1) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_48 (ite ?v_49 (ite ?v_53 (_ bv0 1) (ite (= (_ bv1 1) (ite (= (_ bv14 4) tail_fs_0) (_ bv1 1) (_ bv0 1))) (_ bv1 1) full_fs_0)) full_fs_0) (_ bv0 1)) full_fs_1) (_ bv1 1) (_ bv0 1)) (bvand (ite (= (ite ?v_48 (ite ?v_49 (ite ?v_50 (ite ?v_55 tail_fs_0 (bvadd (_ bv1 4) tail_fs_0)) (ite (= (_ bv1 1) empty_fs_0) tail_fs_0 (bvadd (_ bv15 4) tail_fs_0))) tail_fs_0) (_ bv0 4)) tail_fs_1) (_ bv1 1) (_ bv0 1)) (bvand (bvnot (bvand reset_0 (bvnot (bvand (ite (= data_out_fs_0 data_out_fq_0) (_ bv1 1) (_ bv0 1)) (bvand (ite (= full_fs_0 full_fq_0) (_ bv1 1) (_ bv0 1)) (ite (= empty_fs_0 empty_fq_0) (_ bv1 1) (_ bv0 1))))))) (ite (= (_ bv0 4) head_fs_1) (_ bv1 1) (_ bv0 1))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))) (_ bv0 1)))))
(check-sat)
(set-option :regular-output-channel "/dev/null")
(get-model)
(exit)
