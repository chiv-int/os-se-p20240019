Here's your completed README.md:

---

# OS Lab 6 Submission — Linux Security, Users, Groups & File Permissions
- **Student Name:** Chiv Inthera
- **Student ID:** p20240019
---
## Task Output Files
Make sure all of the following files are present in your `lab6/` folder:
- [x] `task1_users.txt`
- [x] `task2_groups.txt`
- [x] `task3_permissions.txt`
- [x] `task3_stat_output.txt`
- [x] `task4_special_bits.txt`
- [x] `task5_acl.txt`
- [x] `security_lab/whoami_suid.c`
---
## Screenshots
Insert your screenshots below.
### Screenshot 1 — Task 1: User Creation
Show `cat task1_users.txt` confirming both `dev_alice` and `dev_bob` accounts exist.
![user creation](images/task1_user_creation.png)
---
### Screenshot 2 — Task 1: User Modification
Show the updated `/etc/passwd` entry for `dev_alice` with the GECOS comment field.
![user modify](images/task1_user_modify.png)
---
### Screenshot 3 — Task 2: Group Setup
Show `cat task2_groups.txt` with group membership for both users.
![group setup](images/task2_group_setup.png)
---
### Screenshot 4 — Task 2: Multiple Group Membership
Show `id dev_alice` confirming membership in both `devteam` and `auditors`.
![multi group](images/task2_multi_group.png)
---
### Screenshot 5 — Task 3: Directory Permissions
Show `cat task3_permissions.txt` with `drwxrwx---` on the project directory.
![dir permissions](images/task3_dir_permissions.png)
---
### Screenshot 6 — Task 3: Access Denied
Show the `Permission denied` error when `temp_user` tries to access the project directory.
![access denied](images/task3_access_denied.png)
---
### Screenshot 7 — Task 4: setgid Bit
Show the directory listing with `s` in the group execute position, and `bob_file.txt` inheriting the `devteam` group.
![setgid](images/task4_setgid.png)
---
### Screenshot 8 — Task 4: Sticky Bit
Show the `t` bit in the directory listing and the `Operation not permitted` error when `dev_bob` tries to delete `dev_alice`'s file.
![sticky bit](images/task4_sticky_bit.png)
---
### Screenshot 9 — Task 4: setuid Bit
Show `ls -l whoami_suid` with `s` in the owner execute position and the program's UID output.
![setuid](images/task4_setuid.png)
---
### Screenshot 10 — Task 5: ACL Directory
Show `getfacl /opt/techcorp/devproject` with the `auditors` ACE.
![acl dir](images/task5_acl_dir.png)
---
### Screenshot 11 — Task 5: ACL Access Test
Show `dev_alice` successfully accessing the file and `temp_user` being denied.
![acl test](images/task5_acl_test.png)
---
### Screenshot 12 — Task 5: ACL Output File
Show `cat task5_acl.txt` with the full ACL entries.
![acl output](images/task5_acl_output.png)
---
## Answers to Lab Questions

1. **What is the difference between `userdel` and `userdel -r`?**
   > `userdel` removes only the user account entry from the system (from `/etc/passwd`, `/etc/shadow`, and `/etc/group`), but leaves the user's home directory and mail spool files intact on disk. `userdel -r` does everything `userdel` does but additionally deletes the user's home directory and all its contents, along with the user's mail spool. In a production environment, `userdel` alone is sometimes preferred when you need to preserve the user's files for handover, while `userdel -r` is used when you want a complete cleanup with no leftover data.

2. **Why is it safer to use `visudo` instead of directly editing `/etc/sudoers`?**
   > `visudo` opens the sudoers file in a locked, temporary copy and performs a syntax check before saving. If there is any syntax error, it warns you and refuses to write the broken file, giving you the option to fix it. Directly editing `/etc/sudoers` with a regular text editor skips this validation entirely — a single typo or malformed rule can corrupt the file and lock every user out of `sudo` completely, potentially making the system unrecoverable without booting into single-user mode. `visudo` also prevents two administrators from editing the file at the same time, avoiding race conditions.

3. **What happens when a `setgid` directory contains files created by different users? What benefit does this provide for team collaboration?**
   > When the `setgid` bit is set on a directory, any new file or subdirectory created inside it automatically inherits the group ownership of the directory itself, regardless of which user created the file. Without `setgid`, files would inherit the primary group of the individual user who created them, which could be different for every team member. This is extremely useful for team collaboration because it ensures that all files in a shared project directory belong to the same group (e.g., `devteam`), meaning every group member can read and write every file without needing manual `chown` or `chgrp` corrections after each file is created.

4. **What limitation of standard Unix permissions does the ACL system solve?**
   > Standard Unix permissions only allow three permission sets per file or directory: one for the owner, one for the group, and one for everyone else. This means you cannot grant different levels of access to multiple individual users or multiple groups simultaneously — for example, giving one group read-only access while another group has read-write access to the same resource. ACLs solve this by allowing any number of additional Access Control Entries (ACEs) to be attached to a file or directory, each targeting a specific user or group with its own permission set. In this lab, we used ACLs to give the `auditors` group read-only access to the project directory without changing its primary group or breaking the existing `devteam` permissions.