import decimal
decimal.getcontext().prec = 10010
golden_ratio = (decimal.Decimal(5).sqrt()+1)/2
result = str(golden_ratio)
# The format is '1.618...'
# Let's verify the length of digits after the decimal point
digits_after_decimal = result.split('.')[1]
print(f"Total digits after decimal: {len(digits_after_decimal)}")
# Output the first 10000 digits after decimal, or total 10001 digits including the '1'
print(result[:10002]) # 1 + '.' + 10000 digits = 10002 characters
