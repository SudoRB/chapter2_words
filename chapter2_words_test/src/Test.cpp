#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "src/word.h"
#include "src/kwic.h"
#include "word_tests.h"

#include <sstream>


//operator tests
void test_opGT_lt(){
	word::Word w1{"abc"};
	word::Word w2("def");
	ASSERT(!(w1 > w2));
}

void test_opGT_eq(){
	word::Word w1{"abc"};
	word::Word w2("abc");
	ASSERT(!(w1 > w2));

}

void test_opGT_gt(){
	word::Word w1{"def"};
	word::Word w2("abc");
	ASSERT(w1 > w2);

}

void test_opLT_lt(){
	word::Word w1{"abc"};
	word::Word w2("def");
	ASSERT(w1 < w2);

}

void test_opLT_eq(){
	word::Word w1{"abc"};
	word::Word w2("abc");
	ASSERT(!(w1 < w2));

}

void test_opLT_gt(){
	word::Word w1{"def"};
	word::Word w2("abc");
	ASSERT(!(w1 < w2));
}

void test_opGTE_lt(){
	word::Word w1{"abc"};
	word::Word w2("def");
	ASSERT(!(w1 >= w2));
}

void test_opGTE_eq(){
	word::Word w1{"abc"};
	word::Word w2("abc");
	ASSERT(w1 >= w2);
}

void test_opGTE_gt(){
	word::Word w1{"def"};
	word::Word w2("Abc");
	ASSERT(w1 >= w2);
}

void test_opLTE_lt(){
	word::Word w1{"abC"};
	word::Word w2("def");
	ASSERT(w1 <= w2);
}

void test_opLTE_eq(){
	word::Word w1{"abC"};
	word::Word w2("abc");
	ASSERT(w1 <= w2);

}

void test_opLTE_gt(){
	word::Word w1{"def"};
	word::Word w2("ABC");
	ASSERT(!(w1 <= w2));

}

void test_opEQ_lt(){
	word::Word w1{"abC"};
	word::Word w2("def");
	ASSERT(!(w1 == w2));

}

void test_opEQ_eq(){
	word::Word w1{"abC"};
	word::Word w2("abc");
	ASSERT(w1 == w2);

}

void test_opEQ_gt(){
	word::Word w1{"def"};
	word::Word w2("ABC");
	ASSERT(!(w1 == w2));

}

void test_opNEQ_lt(){
	word::Word w1{"abC"};
	word::Word w2("def");
	ASSERT(w1 != w2);

}

void test_opNEQ_eq(){
	word::Word w1{"abC"};
	word::Word w2("abc");
	ASSERT(!(w1 != w2));

}

void test_opNEQ_gt(){
	word::Word w1{"def"};
	word::Word w2("ABC");
	ASSERT(w1 != w2);

}

//IO Tests
void test_print(){
	word::Word word{"HulaHop"};
	std::ostringstream out{};
	word.print(out);
	ASSERT_EQUAL("HulaHop", out.str());
}

void test_read_once_valid(){
	std::istringstream in{" hall0"};
	word::Word word{};
	word.read(in);
	ASSERT_EQUAL("hall", word.toString());
}

void test_read_twice_valid(){
	std::istringstream in{"once, twice!"};
	word::Word w1{}, w2{};
	w1.read(in);
	w2.read(in);
	ASSERT("once" == w1.toString() && "twice" == w2.toString());
}

void test_read_empty_invalid(){
	std::istringstream in{""};
	word::Word word{};
	word.read(in);
	ASSERT(word.toString() == "default" && in.eof());
}

void test_read_numeric_invalid(){
	std::istringstream in{"1984"};
	word::Word word{};
	word.read(in);
	ASSERT(word.toString() == "default" && in.eof());
}

void test_read_twice_numericDelimiter_valid(){
	std::istringstream in{"Time4Tea"};
	word::Word w1{};
	word::Word w2{};
	w1.read(in);
	w2.read(in);
	ASSERT("Time" == w1.toString() && "Tea" == w2.toString());
}

void test_read_four_multipleDelimiters_valid(){
	std::istringstream in{"One 1 tWo 2- thRee 3;!fouR"};
	word::Word w1{}, w2{}, w3{}, w4{};
	w1.read(in);
	w2.read(in);
	w3.read(in);
	w4.read(in);
	ASSERT("One" == w1.toString() && "tWo" == w2.toString() && "thRee" == w3.toString() && "fouR" == w4.toString());
}

void test_opOUT_valid(){
	word::Word word{"abcdefghijklmnop"};
	std::ostringstream out{};
	out << word;
	ASSERT_EQUAL("abcdefghijklmnop", out.str());
}

void test_opIN_valid(){
	word::Word word{};
	std::istringstream in{"--hula--"};
	in >> word;
	ASSERT_EQUAL("hula", word.toString());
}

void test_opIN_invalid(){
	word::Word word{};
	std::istringstream in{"&2012%"};
	word.read(in);
	ASSERT(word.toString() == "default" && in.eof());
}

//kwic tests
void test_2lines_3words(){
	std::istringstream in{"one two three\n four five six\n"};
	std::ostringstream out{};
	kwic::kwic(in, out);
	ASSERT_EQUAL(	"five six four \n"
					"four five six \n"
					"one two three \n"
					"six four five \n"
					"three one two \n"
					"two three one \n", out.str());
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//operator tests
	s.push_back(CUTE(test_opGT_lt));
	s.push_back(CUTE(test_opGT_gt));
	s.push_back(CUTE(test_opGT_eq));
	s.push_back(CUTE(test_opLT_lt));
	s.push_back(CUTE(test_opLT_gt));
	s.push_back(CUTE(test_opLT_eq));
	s.push_back(CUTE(test_opGTE_lt));
	s.push_back(CUTE(test_opGTE_gt));
	s.push_back(CUTE(test_opGTE_eq));
	s.push_back(CUTE(test_opLTE_lt));
	s.push_back(CUTE(test_opLTE_gt));
	s.push_back(CUTE(test_opLTE_eq));
	s.push_back(CUTE(test_opEQ_lt));
	s.push_back(CUTE(test_opEQ_gt));
	s.push_back(CUTE(test_opEQ_eq));
	s.push_back(CUTE(test_opNEQ_lt));
	s.push_back(CUTE(test_opNEQ_gt));
	s.push_back(CUTE(test_opNEQ_eq));

	//IO tests
	s.push_back(CUTE(test_print));
	s.push_back(CUTE(test_read_once_valid));
	s.push_back(CUTE(test_read_twice_valid));
	s.push_back(CUTE(test_read_empty_invalid));
	s.push_back(CUTE(test_read_numeric_invalid));
	s.push_back(CUTE(test_read_twice_numericDelimiter_valid));
	s.push_back(CUTE(test_read_four_multipleDelimiters_valid));
	s.push_back(CUTE(test_opOUT_valid));
	s.push_back(CUTE(test_opIN_valid));
	s.push_back(CUTE(test_opIN_invalid));

	//kwic tests
	s.push_back(CUTE(test_2lines_3words));
	push_back_AllTests(s);
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
