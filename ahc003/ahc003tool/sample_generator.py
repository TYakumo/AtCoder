import subprocess
import os

def main():
    for t in range(100):
        num = str(t).zfill(4)
        cmd = "./a.out < " + num + ".txt > sample" + num + ".txt"
        res = str(subprocess.check_output(cmd, shell=True, stderr=subprocess.STDOUT))

if __name__ == "__main__":
    main()