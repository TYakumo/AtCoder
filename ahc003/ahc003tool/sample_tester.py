import subprocess
import os

def main():
    score = 0
    for t in range(100):
        num = str(t).zfill(4)
        cmd = "cargo run --release --bin tester sample" + num + ".txt ./runner"
        print("run " + cmd)
        res = str(subprocess.check_output(cmd, shell=True, stderr=subprocess.STDOUT))
        # print(type(res))
        # str_list = res.split(os.linesep)
        str_list = res.split("\\")
        # print(str_list[-2])
        value_list = str_list[-2].split(' ')
        print(value_list[-1])
        score += int(value_list[-1])

    print("total score " + str(score))

if __name__ == "__main__":
    main()