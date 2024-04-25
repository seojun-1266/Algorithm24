class Stack:
    def __init__(self):
        self.i = []

    def is_empty(self):
        return self.i == []

    def push(self, i):
        self.i.append(i)

    def pop(self):
        if not self.is_empty():
            return self.i.pop()
        else:
            return None

def reverse_string(input_string):
    stack = Stack()
    for char in input_string:
        stack.push(char)

    reversed_string = ""
    while not stack.is_empty():
        reversed_string += stack.pop()

    return reversed_string

input_string = input("문자열을 입력하세요: ")
reversed_string = reverse_string(input_string)
print("역순으로 출력된 문자열:", reversed_string)
