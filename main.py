import ctypes.wintypes

import myModule


def string_tests():
    print("Print Hello World from C")
    myModule.c_hello_world()
    print("\nPrint Apfel from C")
    myModule.c_print("Apfel")
    print("\nPrint Ǣ from C")
    myModule.c_print("Ǣ")


def number_tests():
    print("\nPrint given number")
    myModule.print_int(10)
    print()
    myModule.print_int("Test")
    print()
    myModule.print_int(1.1)
    print()
    myModule.print_int(10.)
    print()
    myModule.print_dec(10)
    print()
    myModule.print_dec("Test")
    print()
    myModule.print_dec(1.1)
    print()
    myModule.print_dec(10.)
    print()


def tuple_tests():
    print("\nPrint Apfel and Birne from C")
    myModule.arg_unpack("Apfel", "Birne")


if __name__ == "__main__":
    string_tests()
    tuple_tests()
    number_tests()
    myModule.access_ext_files()
