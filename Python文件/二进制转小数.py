def binary_to_decimal(binary_str):
    # 检查输入是否合法
    if not all(c in '01.' for c in binary_str):
        raise ValueError("输入必须是二进制数（仅包含0、1和.）")
    
    if binary_str.count('.') > 1:
        raise ValueError("二进制数只能包含一个小数点")
    
    # 处理符号
    sign = 1
    if binary_str.startswith('-'):
        sign = -1
        binary_str = binary_str[1:]
    
    # 分割整数和小数部分
    if '.' in binary_str:
        integer_part, decimal_part = binary_str.split('.')
    else:
        integer_part = binary_str
        decimal_part = ''
    
    # 转换整数部分
    integer_value = 0
    for i, digit in enumerate(reversed(integer_part)):
        if digit == '1':
            integer_value += 2 ** i
    
    # 转换小数部分
    decimal_value = 0.0
    for i, digit in enumerate(decimal_part, start=1):
        if digit == '1':
            decimal_value += 2 ** (-i)
    
    return sign * (integer_value + decimal_value)

# 测试示例
try:
    binary_input = input("请输入一个二进制小数（例如1010.101）：")
    decimal_result = binary_to_decimal(binary_input)
    print(f"十进制表示为：{decimal_result}")
except ValueError as e:
    print(f"错误：{e}")