def factorial(n):
    if n == 0:
        return 1
    else:
        return n * factorial(n - 1)
num = int(input("숫자를 입력하시오"))
if num < 0:
    print("잘못입력하셨습니다.")
else:
    print(f"{num}!는 {factorial(num)}입니다.") 