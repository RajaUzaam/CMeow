# generate_consts.py

N = 300  # >255 to force EXTEND1

with open("meow.mbc", "w") as f:
    f.write("_start\n")
    f.write("START\n")

    for i in range(N):
        f.write(f"PUSH #{i}i\n")

    f.write("STOP\n")
    f.write("END\n")

print("Generated meow.mbc with", N, "constants")
