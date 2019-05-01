#ifndef TESTCASE_H
#define TESTCASE_H

#include <string>
#include <iostream>
#include <exception>
#include "model/Exceptions/translatorexception.h"

using namespace std;



class TestException : public std::exception
{

    string text;

public:
    TestException (string text): text(text) {
    }

    string describe() {
        return text;
    }

    const char * what () const noexcept
    {
        return "test excepion";
    }
};




void assertTrue(bool con, const char* text) {
    if (!con) {
        throw TestException(text);
    }
}


[[noreturn]] void shouldThrowBefore(const char* text) {
    throw TestException(text);
}



class TestCase {
public:
    virtual void test() = 0;

    virtual ~TestCase() {}
};



#define TEST_BEGIN cout << "!";
#define TEST_PASSED cout << "Test " << __FUNCTION__ << " successully passed" << endl;


#define START_TEST_CASE try {

#define END_TEST_CASE cout << "SUCCESS" << endl;\
} catch (TestException& e) {\
    cerr << "TEST ERROR: " << e.describe() << endl;\
} catch (TranslatorException &e) {\
    cerr << "Unhandled exception: " << e.getMessage() << endl; \
} catch (std::exception& e) {\
    cerr << "Unhandled exception: " << e.what()  << endl; \
} catch (...) {\
    cerr << "Exception: " << "Unexpected exception!" << endl; \
} \
    exit(0);



#endif // TESTCASE_H
