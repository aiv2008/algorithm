# https://leetcode.com/problems/roman-to-integer/


d = {"I": 1, "V": 5, "X": 10, "L": 50, "C": 100, "D": 500, "M": 1000}


def roman_to_integer(s):
    res = 0
    high = -1
    for c in reversed(s):
        now = d[c]
        if now < high:
            res -= now
        else:
            res += now
        high = max(high, now)
    return res


assert roman_to_integer("I") == 1
assert roman_to_integer("V") == 5
assert roman_to_integer("X") == 10
assert roman_to_integer("L") == 50
assert roman_to_integer("C") == 100
assert roman_to_integer("D") == 500
assert roman_to_integer("M") == 1000

assert roman_to_integer("III") == 3
assert roman_to_integer("IV") == 4
assert roman_to_integer("IX") == 9
assert roman_to_integer("LVIII") == 58
assert roman_to_integer("MCMXCIV") == 1994
