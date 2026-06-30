# commands.md — exact commands I ran, per part

> Paste the **real** commands you ran, in order, in the fenced blocks below. Graded for
> command competency and is your defence if any output is questioned. One block per part.
> Delete the hint comments and replace with your actual commands.

## Part A — Threads, Mapping & Signals

```bash
# compile the threaded program (mind the threading flag), run it
# capture the 1:1 user→kernel (LWP) mapping into thread_map.txt while it runs
# compile/run signal_demo and demonstrate catching the interactive interrupt


cd ~/os-se-p20240019/final-exam/partA_threads
nano thread_demo.c
gcc -pthread thread_demo.c -o thread_demo
./thread_demo
rm thread_demo.c
nano thread_demo.c
gcc -pthread thread_demo.c -o thread_demo
./thread_demo
nano thread_demo.c    # changed sleep(5) to sleep(15)
gcc -pthread thread_demo.c -o thread_demo
./thread_demo & ps -eLf | grep thread_demo > thread_map.txt
nano signal_demo.c
gcc signal_demo.c -o signal_demo
./signal_demo
```

## Part B — Permissions, Special Bits & ACLs

```bash
# build the tree (shared dir + private file); set octal + symbolic modes
# demonstrate setgid + sticky on a dir you own; build/set the setuid binary
# add and read back an ACL entry; save reports
mkdir shared_dir
touch shared_dir/teamfile.txt
touch private_notes.txt
echo "These are my private notes" > private_notes.txt
chmod 600 private_notes.txt
chmod 711 shared_dir
chmod u=rw,go= private_notes.txt
ls -l private_notes.txt > perm_report.txt
ls -ld shared_dir >> perm_report.txt
stat private_notes.txt >> perm_report.txt
stat shared_dir >> perm_report.txt
mkdir setgid_dir
chmod g+s setgid_dir
ls -ld setgid_dir
mkdir sticky_dir
chmod +t sticky_dir
ls -ld sticky_dir
nano setuid_demo.c
gcc setuid_demo.c -o setuid_demo
chmod u+s setuid_demo
ls -l setuid_demo
./setuid_demo
```

## Part C — Bash Scripting, PATH & Safe Scanning

```bash
# make greeter runnable by name via PATH; record PATH + resolved location
# run collector over your dirs; show it skips unreadable/missing files safely
nano greeter
chmod +x greeter
cp greeter ~/bin/
greeter
echo "PATH=$PATH" > path_report.txt
which greeter >> path_report.txt
mkdir -p data1 data2 data3
echo "Report from data1" > data1/info.txt
echo "Report from data2" > data2/info.txt
echo "Secret report" > data1/locked.txt
chmod 000 data1/locked.txt
nano collector
chmod +x collector
./collector
```

## Part D — Race Condition & flock

```bash
# init stock; run swarm several times unpatched and record final stock each time
# add the exclusive advisory lock around the read-modify-write; re-run swarm
echo "150" > stock.txt
touch sales_log.txt
nano buy_beacon
chmod +x buy_beacon
./buy_beacon Jae 5
./buy_beacon Jae -3
./buy_beacon Jae abc
./buy_beacon
echo "150" > ../stock.txt
./swarm
(repeated 5 times total)
rm buy_beacon
nano buy_beacon   # rewrote with flock -x exclusive lock around critical section
chmod +x buy_beacon
echo "150" > ../stock.txt
./swarm
(repeated 3 times to confirm determinism)
```

## Part E — Backups & cron

```bash
# E1: run backup_project enough times that pruning happens (keep newest RETAIN_N)
# E2: per-user crontab, two entries (absolute paths):
#     recurring (CRON_INTERVAL) -> partE_automation/logs/cron_recurring.log
#     one-shot at TIMED        -> partE_automation/logs/cron_oneshot.log
# E3: backup_exam -> tar the final-exam folder to ~/exam-backups/final-exam-<ts>.tar.gz
#     crontab: run backup_exam on a short interval AND once at exactly 16:00 today
#     then: ls ~/exam-backups
# capture crontab -l + both logs + the ~/exam-backups listing into cron_report.txt
mkdir -p sample_project/src sample_project/docs
echo "print('hello HelioGrid')" > sample_project/src/main.py
echo "# Sample project docs" > sample_project/docs/notes.md
nano backup_project
chmod +x backup_project
./backup_project
sleep 2
./backup_project
sleep 2
./backup_project
sleep 2
./backup_project
nano timed_job
chmod +x timed_job
pwd
crontab -e
crontab -l
nano backup_exam
chmod +x backup_exam
./backup_exam
crontab -e
crontab -l
```
