#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

// python -m venv .venv
// source .venv/bin/activate 
// python -m pip install pytest
// python -m pytest /tests/test_arithmatoy.py
// source .devenv/bash_init.sh
// setup
// cmake_build_debug 
// ctest_debug
// .local/cmake/dist/bin/arithmatoy-cli add 10 9 12
//
// sizeof(): The actual number of bits of type char is specified by the preprocessor macro CHAR_BIT, defined in the standard include file limits.h 
//
// cat /usr/include/limits.h | grep CHAR_BIT  => #  define CHAR_BIT      8


int VERBOSE = 0;

const char *get_all_digits() { 
    return "0123456789abcdefghijklmnopqrstuvwxyz"; 
}

const size_t ALL_DIGIT_COUNT = 36;

void arithmatoy_free(char *number) { free(number); }




// TODO
// lets go through this example: 8 + 8 in base 10
char *arithmatoy_add(unsigned int base, const char *lhs, const char *rhs) {
    // the goal is to compute lhs + rhs 
    // we'll remove extra zeroes, copy lhs and rhs, and reverse them to perform arithmetic from left to right
    // we'll create a buffer to store the values at each one of the while loop iteration    
    // we'll reverse the result to reposition it properly and return it
    // to_digit() will be used to convert argument values into ASCII (which is what C uses)
    if (VERBOSE) {
        fprintf(stderr, "add: entering function\n");
        fprintf(stderr, "base %u lhs %s rhs %s\n", base, lhs, rhs);
    }
     
    if ( !lhs && !rhs || base > ALL_DIGIT_COUNT ) { // equal to: if ( lhs == NULL && rhs == NULL || base > ALL_DIGIT_COUNT ) 
        return NULL;
    }

    // if lhs doesnt contain any value, the result is the value of rhs
    if (lhs == NULL) {
        // char *strdup(const char *s);
        // strdup() returns a pointer to a new string which is a duplicate of the string s
        return strdup(rhs);
    }

    if (rhs == NULL) {
        return strdup(lhs);
    }
    
    // reversing numbers to count from left to right + need to cast parameteres in this order: we remove the leading zeroes to avoid the compiler to stop when encountering the null terminator, then we copy the string, and only then reverse it 
    lhs = reverse(strdup(drop_leading_zeros(lhs)));
    rhs = reverse(strdup(drop_leading_zeros(rhs)));

    // size_t Used for a count of bytes.  It is the result of the sizeof() operator.  
    // It is an unsigned integer type capable of storing values in the range [0, SIZE_MAX].
    const size_t lhs_length = strlen(lhs); // => 1
    const size_t rhs_length = strlen(rhs); // => 1
    const size_t max_length = lhs_length > rhs_length ? lhs_length : rhs_length; // lhs_length value will be passed => 1
    const size_t buffer_length = max_length + 2; // +2 int for the possible carry value and the null terminator => 3

    char *buffer = (char *) malloc(buffer_length * sizeof(char)); // (char*)malloc(3 * 1)

    unsigned int carry = 0;
    unsigned int i = 0;

    // we iterate through each digit, for a duration of the max_length
    // goal is to take digit by digit, add them, collect the carry and move on
    while (i < max_length) {
        // add zeroes once one length is reached 
        unsigned int lhs_digit = i < lhs_length ? get_digit_value(lhs[i]) : 0; // => 8
        unsigned int rhs_digit = i < rhs_length ? get_digit_value(rhs[i]) : 0; // => 8

        unsigned int result = lhs_digit + rhs_digit + carry; // => 8 + 8 + 0
     
        carry = result / base; // => 16 / 10 = 1                 
        
        // store digit in buffer
        buffer[i] = to_digit(result % base); // => 16 % 10 = 6 =>> to_digit(6) = 54 => buffer[0] = 54 (ASCII VALUE) 
        ++i;
    }

    // store carry in buffer
    if (carry > 0) {
        buffer[i] = to_digit(carry); // => 1 =>> to_digit(1) = 49
        i++;
    }

    // add null terminator to be able to call reverse()
    buffer[i] = '\0'; // buffer content: 54 | 49 | '\0'

    // re-position numbers properly
    buffer = reverse(buffer); // => '\0' | 49 | 54
    
    // clean the '\0'
    buffer = (char *) drop_leading_zeros(buffer); // => 49 | 54

    return buffer;
}



char *arithmatoy_sub(unsigned int base, const char *lhs, const char *rhs) {  
    // Fill the function, the goal is to compute lhs - rhs (assuming lhs > rhs)
    // lets take 18 - 4 - 0 as an example
    if (VERBOSE) {
        fprintf(stderr, "sub: entering function\n");
    }
    
    if ( !lhs && !rhs || base > ALL_DIGIT_COUNT) {
        return NULL;
    }

    if (rhs == NULL) {
        return strdup(lhs);
    }

    lhs = drop_leading_zeros(lhs); // 14
    rhs = drop_leading_zeros(rhs); // 8

    lhs = reverse(strdup(lhs)); // 41
    rhs = reverse(strdup(rhs)); // 8

    const size_t lhs_length = strlen(lhs);
    const size_t rhs_length = strlen(rhs);
    
    // check for negative result     
    if (lhs_length < rhs_length || (lhs_length == rhs_length && strcmp(lhs, rhs) < 0)) {
        return NULL;
    }
   
    const size_t total_length = rhs_length > lhs_length ? rhs_length : lhs_length;
    const size_t buffer_length = total_length + 2; 

    char *buffer = (char *) malloc(buffer_length * sizeof(char));
    
    // check for 0 result
    if (lhs_length == rhs_length && strcmp(lhs, rhs) == 0) {
        return 0;
    }

    unsigned int carry = 0;
    unsigned int i = 0;

    while (i < total_length) {
        unsigned int lhs_digit = i < lhs_length ? get_digit_value(lhs[i]) : 0; // => 4 
        unsigned int rhs_digit = i < rhs_length ? get_digit_value(rhs[i]) : 0; // => 8 

        unsigned int result = lhs_digit - rhs_digit - carry; // => 4 - 8 - 0 = -4

        carry = result / base; // => -6 / 10 = 0
         
        if (result < 0) {
            carry += 1; // => +1 
        }        
        
        buffer[i] = to_digit(result % base); // => -4 % 10 = 4       
        ++i;
    }

    if (carry > 0) {
        buffer[i] = to_digit(carry); // at this point we have in the buffer 4 then 1
        i++;
    }

    buffer[i] = '\0';

    buffer = reverse(buffer); //  
    buffer = (char *) drop_leading_zeros(buffer); 

    return buffer;

}



char *arithmatoy_mul(unsigned int base, const char *lhs, const char *rhs) {
    if (VERBOSE) {
        fprintf(stderr, "mul: entering function\n");
    }

    if ( !lhs || !rhs ) {
        return NULL;
    }


  // Fill the function, the goal is to compute lhs * rhs
  // You should allocate a new char* large enough to store the result as a
  // string Implement the algorithm Return the result
}
// END TODO





// Here are some utility functions that might be helpful to implement add, sub
// and mul:

unsigned int get_digit_value(char digit) {
  // Convert a digit from get_all_digits() to its integer value
  if (digit >= '0' && digit <= '9') {
    return digit - '0';
  }
  if (digit >= 'a' && digit <= 'z') {
    return 10 + (digit - 'a');
  }
  return -1;
}

char to_digit(unsigned int value) {
  // Convert an integer value to an ASCII "digit" value obtained from char *get_all_digits()
  if (value >= ALL_DIGIT_COUNT) {
    debug_abort("Invalid value for to_digit()");
    return 0;
  }
  return get_all_digits()[value]; // get_all_digits()[9] will return 57 which is the ASCII value of 9
}

char *reverse(char *str) {
  // Reverse a string in place, return the pointer for convenience
  // Might be helpful if you fill your char* buffer from left to right
  const size_t length = strlen(str);
  const size_t bound = length / 2;
  for (size_t i = 0; i < bound; ++i) {
    char tmp = str[i];
    const size_t mirror = length - i - 1;
    str[i] = str[mirror];
    str[mirror] = tmp;
  }
  return str;
}

const char *drop_leading_zeros(const char *number) {
  // If the number has leading zeros, return a pointer past these zeros
  // Might be helpful to avoid computing a result with leading zeros
  if (*number == '\0') {
    return number;
  }
  while (*number == '0') {
    ++number;
  }
  if (*number == '\0') {
    --number;
  }
  return number;
}

void debug_abort(const char *debug_msg) {
  // Print a message and exit
  fprintf(stderr, debug_msg);
  exit(EXIT_FAILURE);
}
