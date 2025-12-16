# THIS FILE IS NOT AN INTEGRAL PART OF THE CODEBASE AND WILL LIKELY BE REMOVED IN A FUTURE COMMIT
# This is a test file to generate more than 300 constants to check whether variable length operands are working

N = 300  # >255 to force EXTEND1

with open("meow.mbc", "w") as f:
    f.write("_start\n")
    f.write("START\n")

    for i in range(N):
        f.write(f"PUSH #{i}i\n")

    f.write("STOP\n")
    f.write("END\n")

print("Generated meow.mbc with", N, "constants")
