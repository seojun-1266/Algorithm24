def factorial(n):
    if n < 0:
        return "잘못입력하셨습니다."
    elif n == 0:
        return 1
    else:
        result = 1
        for i in range(1, n + 1):
            result *= i
        return result
num = int(input("숫자를 입력하세요 "))
print(f"{num}!는 {factorial(num)}입니다.")
