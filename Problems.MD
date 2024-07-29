===> Errors?


bash-3.2$ ./philosa 2 69 69 69
1 1 is thinking
1 2 has taken a fork
1 1 has taken a fork
69 1 died
Killed: 9

bash-3.2$ ./philosa 1 69 69 69
1 1 is thinking


===> Fixed
===> Errors?


bash-3.2$ ./philosa 1 69 69 69 
1 1 is thinking
1 1 has taken a fork
69 1 died
mattttt

//TODO: when there is one philo he shouldnt think
```bash
WARNING: ThreadSanitizer: data race (pid=4412)
  Write of size 8 at 0x7b2000000108 by main thread:
    #0 eat routine_bonus.c:60 (philosa:x86_64+0x100003a0d)
    #1 simulate simulator_bonus.c:104 (philosa:x86_64+0x100002f23)
    #2 main philo_bonus.c:23 (philosa:x86_64+0x10000208a)

  Previous read of size 8 at 0x7b2000000108 by thread T1:
    #0 check_death simulator_bonus.c:37 (philosa:x86_64+0x1000022cc)

  As if synchronized via sleep:
    #0 usleep <null>:3 (libclang_rt.tsan_osx_dynamic.dylib:x86_64h+0x2c5ae)
    #1 think_abit simulator_bonus.c:73 (philosa:x86_64+0x1000027d5)
    #2 simulate simulator_bonus.c:96 (philosa:x86_64+0x100002ccb)
    #3 main philo_bonus.c:23 (philosa:x86_64+0x10000208a)

  Location is heap block of size 120 at 0x7b2000000100 allocated by main thread:
    #0 malloc <null>:3 (libclang_rt.tsan_osx_dynamic.dylib:x86_64h+0x5239a)
    #1 allocate_philos init_bonus.c:27 (philosa:x86_64+0x1000018a8)
    #2 init init_bonus.c:63 (philosa:x86_64+0x100001fae)
    #3 main philo_bonus.c:21 (philosa:x86_64+0x10000206c)

  Thread T1 (tid=5423926, running) created by main thread at:
    #0 pthread_create <null>:3 (libclang_rt.tsan_osx_dynamic.dylib:x86_64h+0x2d8fd)
    #1 simulate simulator_bonus.c:91 (philosa:x86_64+0x100002b21)
    #2 main philo_bonus.c:23 (philosa:x86_64+0x10000208a)

SUMMARY: ThreadSanitizer: data race routine_bonus.c:60 in eat
==================
==================
WARNING: ThreadSanitizer: data race (pid=4412)
  Read of size 1 at 0x7b2000000111 by thread T1:
    #0 check_death simulator_bonus.c:38 (philosa:x86_64+0x10000235b)

  Previous write of size 1 at 0x7b2000000111 by main thread:
    #0 eat routine_bonus.c:59 (philosa:x86_64+0x1000039c8)
    #1 simulate simulator_bonus.c:104 (philosa:x86_64+0x100002f23)
    #2 main philo_bonus.c:23 (philosa:x86_64+0x10000208a)

  Location is heap block of size 120 at 0x7b2000000100 allocated by main thread:
    #0 malloc <null>:3 (libclang_rt.tsan_osx_dynamic.dylib:x86_64h+0x5239a)
    #1 allocate_philos init_bonus.c:27 (philosa:x86_64+0x1000018a8)
    #2 init init_bonus.c:63 (philosa:x86_64+0x100001fae)
    #3 main philo_bonus.c:21 (philosa:x86_64+0x10000206c)

  Thread T1 (tid=5423926, running) created by main thread at:
    #0 pthread_create <null>:3 (libclang_rt.tsan_osx_dynamic.dylib:x86_64h+0x2d8fd)
    #1 simulate simulator_bonus.c:91 (philosa:x86_64+0x100002b21)
    #2 main philo_bonus.c:23 (philosa:x86_64+0x10000208a)

SUMMARY: ThreadSanitizer: data race simulator_bonus.c:38 in check_death
==================
515 3 is thinking
==================
WARNING: ThreadSanitizer: data race (pid=4413)
  Write of size 1 at 0x7ffee217f850 by thread T1:
    #0 check_death simulator_bonus.c:41 (philosa:x86_64+0x1000023e0)

  Previous read of size 1 at 0x7ffee217f850 by main thread:
    #0 simulate simulator_bonus.c:92 (philosa:x86_64+0x100002b4a)
    #1 main philo_bonus.c:23 (philosa:x86_64+0x10000208a)

  Location is stack of main thread.

  Thread T1 (tid=5423936, running) created by main thread at:
    #0 pthread_create <null>:3 (libclang_rt.tsan_osx_dynamic.dylib:x86_64h+0x2d8fd)
    #1 simulate simulator_bonus.c:91 (philosa:x86_64+0x100002b21)
    #2 main philo_bonus.c:23 (philosa:x86_64+0x10000208a)

SUMMARY: ThreadSanitizer: data race simulator_bonus.c:41 in check_death
==================
803 2 died
==================
WARNING: ThreadSanitizer: data race (pid=4413)
  Read of size 1 at 0x7b2000000138 by main thread:
    #0 simulate simulator_bonus.c:98 (philosa:x86_64+0x100002d65)
    #1 main philo_bonus.c:23 (philosa:x86_64+0x10000208a)

  Previous write of size 1 at 0x7b2000000138 by thread T1:
    #0 check_death simulator_bonus.c:42 (philosa:x86_64+0x100002405)

  Location is heap block of size 120 at 0x7b2000000100 allocated by main thread:
    #0 malloc <null>:3 (libclang_rt.tsan_osx_dynamic.dylib:x86_64h+0x5239a)
    #1 allocate_philos init_bonus.c:27 (philosa:x86_64+0x1000018a8)
    #2 init init_bonus.c:63 (philosa:x86_64+0x100001fae)
    #3 main philo_bonus.c:21 (philosa:x86_64+0x10000206c)

  Thread T1 (tid=5423936, running) created by main thread at:
    #0 pthread_create <null>:3 (libclang_rt.tsan_osx_dynamic.dylib:x86_64h+0x2d8fd)
    #1 simulate simulator_bonus.c:91 (philosa:x86_64+0x100002b21)
    #2 main philo_bonus.c:23 (philosa:x86_64+0x10000208a)

SUMMARY: ThreadSanitizer: data race simulator_bonus.c:98 in simulate
==================
==================
WARNING: ThreadSanitizer: data race (pid=4415)
  Write of size 1 at 0x7ffee217f850 by thread T1:
    #0 check_death simulator_bonus.c:41 (philosa:x86_64+0x1000023e0)

  Previous read of size 1 at 0x7ffee217f850 by main thread:
    #0 simulate simulator_bonus.c:92 (philosa:x86_64+0x100002b4a)
    #1 main philo_bonus.c:23 (philosa:x86_64+0x10000208a)

  Location is stack of main thread.

  Thread T1 (tid=5423961, running) created by main thread at:
    #0 pthread_create <null>:3 (libclang_rt.tsan_osx_dynamic.dylib:x86_64h+0x2d8fd)
    #1 simulate simulator_bonus.c:91 (philosa:x86_64+0x100002b21)
    #2 main philo_bonus.c:23 (philosa:x86_64+0x10000208a)

SUMMARY: ThreadSanitizer: data race simulator_bonus.c:41 in check_death
==================
ThreadSanitizer: reported 2 warnings
```
machakil safi

===> Fixed