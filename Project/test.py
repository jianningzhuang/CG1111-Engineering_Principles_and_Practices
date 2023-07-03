def t(x, y):
    try:
        x[1] = x[0] + y
    except TypeError:
        print("This")
    except IndexError:
        print("is")
    finally:
        return x[1]
print(t([1, "Madness"], "Blasphemy"))
