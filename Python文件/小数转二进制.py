def convert_integer(n):
    if n == 0:
        return '0'
    binary = ''
    while n > 0:
        binary = str(n % 2) + binary
        n = n // 2
    return binary

def convert_decimal(decimal, max_digits=32):
    binary = ''
    count = 0
    while decimal > 0 and count < max_digits:
        decimal *= 2
        if decimal >= 1:
            binary += '1'
            decimal -= 1
        else:
            binary += '0'
        count += 1
    return binary

num = input("请输入一个十进制数：")

try:
    num_float = float(num)
except ValueError:
    print("输入错误，请输入有效的十进制数。")
    exit()

sign = ''
if num_float < 0:
    sign = '-'
    num_float = abs(num_float)

integer_part = int(num_float)
decimal_part = num_float - integer_part

binary_integer = convert_integer(integer_part)
binary_decimal = convert_decimal(decimal_part)

if binary_decimal:
    result = f"{sign}{binary_integer}.{binary_decimal}"
else:
    result = f"{sign}{binary_integer}"

print("二进制表示为：", result)