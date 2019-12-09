#include "pch.h"
#include"..\Project1\TSE.cpp"
#include <gtest/gtest.h>
using namespace MySetEmulation;
using namespace std;

TEST(tse_test, memory_test) {//16
	Trit_set tr;
	tr[0] = True;
	tr[1000] = False;
	EXPECT_EQ(tr.get_capacity(), 1001);
	tr[10000] = Unknown;
	EXPECT_EQ(tr.get_capacity(), 1001);
	Trit_set new_tr(300);
	new_tr[288] = Unknown;
	EXPECT_EQ(new_tr.get_capacity(), 300);
	new_tr[1000] = False;
	EXPECT_EQ(new_tr.get_capacity(), 1001);
	new_tr[304] = Unknown;
	EXPECT_EQ(new_tr.get_capacity(), 1001);
}
TEST(tse_test, tr_set_ctor1_test) {//15
	Trit_set* tr = new Trit_set();
	EXPECT_TRUE(tr != nullptr);
	EXPECT_TRUE(tr->get_length() == 0);
	EXPECT_TRUE(tr->get_capacity() == 0);
}

TEST(tse_test, tr_set_ctor2_test) {//14
	Trit_set* tr = new Trit_set(100);
	EXPECT_TRUE(tr != nullptr);
	EXPECT_TRUE(tr->get_capacity() == 100);
	EXPECT_TRUE(tr->get_length() ==100 * 2 / (8 * sizeof(unsigned int))+(100% (sizeof(unsigned int) * 4) !=0));
}

TEST(tse_test, tr_set_ctor3_test) {//13
	Trit_set tr;
	tr[0] = True;
	tr[3] = False;
	tr[1000] = False;
	Trit_set new_tr(tr);
	EXPECT_TRUE(tr.get_capacity() == new_tr.get_capacity());
	EXPECT_TRUE(tr.get_length() == new_tr.get_length());
	for (size_t i = 0; i < tr.get_capacity(); i++) {
		EXPECT_EQ(tr[i], new_tr[i]);
	}
}
TEST(tse_test, get_capacity_and_length_test) {//12
	Trit_set tr;
	for (int i = 0; i < 500001; i += 100000) {
		tr[i] = True;
	}
	size_t _ln = 500001 * 2 / 8 / sizeof(unsigned int) + (500001 % (sizeof(unsigned int) * 4) != 0);
	EXPECT_EQ(500001, tr.get_capacity());
	EXPECT_EQ(_ln, tr.get_length());
}
TEST(tse_test, shrink_test) {//11
	Trit_set tr(1000000);
	for (size_t i = 0; i < 100000; i++) {
		tr[i] = True;
	}
	EXPECT_EQ(tr.get_capacity(), 1000000);
	tr.shrink();
	EXPECT_EQ(tr.get_capacity(), 100000);
}
TEST(tse_test, trim_test) {//10
	Trit_set tr(1000000);
	for (size_t i = 0; i < 1000000; i++) {
		tr[i] = True;
	}
	EXPECT_EQ(tr.get_capacity(), 1000000);
	tr.trim(50000);
	EXPECT_EQ(tr.get_capacity(), 50001);
}

TEST(tse_test, type_test) {//9
	Trit_set tr(100001);
	Trit tmp;
	for (size_t i = 0; i < 100001; i++) {
		tr[i] = Trit(i % 3);
		tmp = tr[i];
		EXPECT_EQ(tmp, Trit(i % 3));
	}
}
TEST(tse_test, push_pop_test) {//8
	Trit_set tr(660000);
	for (size_t i = 0; i < 660000; i++) {
		tr[i] = Trit(i % 3);
	}
	for (size_t i = 0; i < 660000; i++) {
		switch (i % 3) {
		case 0: { EXPECT_EQ(tr[i], Unknown); break; }
		case 1: { EXPECT_EQ(tr[i], False); break; }
		case 2: { EXPECT_EQ(tr[i], True); break; }
		}
	}
}
TEST(tse_test, complete_trit_test) {//7

	Trit_set tr(1001);
	for (size_t i = 0; i < 1001; i++) {
		tr[i] = Trit(i % 3);
	}
	Trit_set _tr(1001);
	for (size_t i = 0; i < 1001; i++) {
		switch (i % 3) {
		case 0: {_tr[i] = Unknown; break; }
		case 1: {_tr[i] = True; break; }
		case 2: {_tr[i] = False; break; }
		}
	}
	Trit_set completed_tr = !tr;
	EXPECT_TRUE(completed_tr == _tr);
}
TEST(tse_test, trit_and_test) {//6
	Trit_set tr0;
	Trit_set tr1(3333);
	Trit_set tr2(1000);
	Trit_set tr3(1000);
	Trit_set tr4(10);

	for (size_t i = 0; i < 1000; i++) {
		tr1[i] = Trit(i % 3);
		tr2[i] = True;
		tr3[i] = False;
		tr4[i] = Unknown;
	}
	Trit_set tr5 = !tr1;
	Trit_set tr03 = tr0 & tr3;
	Trit_set tr12 = tr1 & tr2;
	Trit_set tr15 = tr1 & tr5;
	Trit_set tr42 = tr4 & tr2;
	Trit_set tr24 = tr2 & tr4;

	for (size_t i = 0; i < 1000; i++) {
		EXPECT_EQ(tr03[i], False);
		EXPECT_EQ(tr12[i], tr1[i]);
		EXPECT_EQ(tr42[i], Unknown);
		switch (i % 3) {
		case 0: { EXPECT_EQ(tr15[i], Unknown); break; }
		case 1: { EXPECT_EQ(tr15[i], False); break; }
		case 2: { EXPECT_EQ(tr15[i], False); break; }
		}
	}
	for (size_t i = 0; i < 10; i++) {
		EXPECT_EQ(tr24[i], tr24[i]);
	}
}
TEST(tse_test, trit_or_test) {//5
	Trit_set tr0;
	Trit_set tr1(3333);
	Trit_set tr2(1000);
	Trit_set tr3(1000);
	Trit_set tr4(10);
	for (size_t i = 0; i < 1000; i++) {
		tr1[i] = Trit(i % 3);
		tr2[i] = True;
		tr3[i] = False;
		tr4[i] = Unknown;
	}
	Trit_set tr5 = !tr1;
	Trit_set tr03 = tr0 | tr3;
	Trit_set tr12 = tr1 | tr2;
	Trit_set tr15 = tr1 | tr5;
	Trit_set tr42 = tr4 | tr2;
	Trit_set tr34 = tr3 | tr4;

	for (size_t i = 0; i < 1000; i++) {
		EXPECT_EQ(tr03[i], Unknown);
		EXPECT_EQ(tr12[i], True);
		EXPECT_EQ(tr42[i], True);
		switch (i % 3) {
		case 0: { EXPECT_EQ(tr15[i], Unknown); break; }
		case 1: { EXPECT_EQ(tr15[i], True); break; }
		case 2: { EXPECT_EQ(tr15[i], True); break; }
		}
	}
	for (size_t i = 0; i < 10; i++) {
		EXPECT_EQ(tr34[i], Unknown);
	}
}
TEST(tse_test, _equal_test) {//4
	Trit_set tr(100001);
	for (size_t i = 0; i < 100001; i++) {
		tr[i] = Trit(i % 3);
	}
	Trit_set _tr(tr);
	EXPECT_TRUE(tr == _tr);
	_tr[1] = False;
	EXPECT_TRUE(tr == _tr);
}

TEST(tse_test, op_not_eq_test) {//3
	Trit_set tr(100001);
	for (size_t i = 0; i < 100001; i++) {
		tr[i] = Trit(i % 3);
	}
	Trit_set _tr(tr);
	EXPECT_TRUE(tr == _tr);
	_tr[1] = True;
	EXPECT_FALSE(tr == _tr);
}

TEST(tse_test, cardinality_test) {//2
	Trit_set tr(35000);
	for (size_t i = 0; i < 35000; i++) {
		tr[i] = Trit(i % 3);
	}
	EXPECT_EQ(11667, tr.cardinality(Unknown));
	EXPECT_EQ(11667, tr.cardinality(False));
	EXPECT_EQ(11666, tr.cardinality(True));
}

TEST(tse_test, map_test) {//1
	Trit_set tr(36000);
	for (size_t i = 0; i < 36000; i++) {
		tr[i] = Trit(i % 3);
	}
	unordered_map< Trit, size_t> check = tr.cardinality();
	EXPECT_EQ(check[Unknown], 12000);
	EXPECT_EQ(check[False], 12000);
	EXPECT_EQ(check[True], 12000);
}
