#words = ' '.join(input("").split(' '))#.split(' ')
words = [s for s in input("").split(' ') if s]

print(sorted(set(words)))
