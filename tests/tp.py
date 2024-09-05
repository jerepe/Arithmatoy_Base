# Aucun n'import ne doit être fait dans ce fichier


def nombre_entier(n: int) -> str:
    return ("S" * n + "0")


def S(n: str) -> str:
    return f'S{n}'


def addition(a: str, b: str) -> str:
    count = a.count('S')
    count += b.count('S')
    return ("S" * count + "0")


def multiplication(a: str, b: str) -> str:
    count = a.count('S')
    count *= b.count('S')
    return ("S" * count + "0")

# factorial iterative
def facto_ite(n: int) -> int:
    if n == 0:
        return 1
    result = n
    while n > 1 :
        result *= (n - 1)
        n -= 1
    return result

# factorial recursive
def facto_rec(n: int) -> int:
    # on evite d'avoir un return a 0
    if n <= 1:
        return  1
    return facto_rec(n - 1) * n


def fibo_rec(n: int) -> int:
    if n == 0:
        return 0
    if n == 1 or n == 2:
        return 1
    return fibo_rec(n -1) + fibo_rec(n - 2)


def fibo_ite(n: int) -> int:
    fn0 = 0
    fn1 = 1
    fn2 = 1
    for i in range(n):
        fn = fn0 + fn1
        fn0 = fn1
        fn1 = fn
    return fn0


def golden_phi(n: int) -> int:
    return (fibo_rec(n + 1) / fibo_rec(n));


def sqrt5(n: int) -> int:
    return 2 * golden_phi(n) - 1


def pow(a: float, n: int) -> float:
    if n == 0:
        return 1
    return a * pow(a, n - 1)
