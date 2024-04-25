def find_substring(text, substring):
    text_length = len(text)
    substring_length = len(substring)
    
    for i in range(text_length - substring_length + 1):
        if text[i:i+substring_length] == substring:
            return i
    return -1

text = "Hello, world!"
substring = "world"
index = find_substring(text, substring)
if index != -1:
    print(f"부분 문자열 '{substring}'을(를) 찾았습니다. 인덱스: {index}")
else:
    print(f"부분 문자열 '{substring}'을(를) 찾을 수 없습니다.")
