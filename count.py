#!/usr/bin/python3

code = """
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

    // reversing numbers to count from left to right + need to cast parameteres in this order to avoid type conflicts
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
        buffer[i] = to_digit(result % base); // => 16 % 10 = 6 =>> to_digit(6) = 54
        ++i;
    }

    // store carry in buffer
    if (carry > 0) {
        buffer[i] = to_digit(carry); // => 1 =>> to_digit(1) = 49
        i++;
    }

    // add a null terminator to be able to call reverse()
    buffer[i] = '\0';

    // at this point we have in the buffer, in this order: 6 | 1 | '\0'

    // re-posititonning numbers properly
    buffer = reverse(buffer); // => '\0' | 1 | 6

    // clean the '\0'
    buffer = (char *) drop_leading_zeros(buffer);

    return buffer;
}
"""

num_chrs = len(code)
print(num_chrs)
