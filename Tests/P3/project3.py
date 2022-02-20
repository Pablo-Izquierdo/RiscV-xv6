import toolspath
from testing import Xv6Build, Xv6Test

class NTest1(Xv6Test):
   name = "null"
   description = "null pointer dereference should kill process"
   tester = "ctests/" + name + ".c"
   make_qemu_args = "CPUS=1"
   point_value = 10
   timeout = 20

class NTest2(Xv6Test):
  name = "null2"
  description = "any dereference from first page should fault"
  tester = "ctests/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 10
  timeout = 20

class NTest3(Xv6Test):
  name = "bounds"
  description = "syscall argument checks (null page). ***NOTE*** only write system call is tested here; when grading, we may change the test to any other system call that may take a NULL pointer."
  tester = "ctests/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 10
  timeout = 20

class ATest1(Xv6Test):
  name = "shmem_access_invalid_input"
  description = "shmem_access invalid input test"
  tester = "ctests/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 10
  timeout = 20

class ATest2(Xv6Test):
  name = "shmem_access_return_value"
  description = "shmem_access return value needs to be one of 4 pages of virtual address space; first access needs to return last virtual page, second access needs to return second to last virtual page, etc."
  tester = "ctests/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 10
  timeout = 20

class ATest3(Xv6Test):
  name = "shmem_access_double_call"
  description = "shmem_access called twice with same page number, making sure same physical page is not mapped into 2 different places in virtual address space"
  tester = "ctests/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 10
  timeout = 20

class ATest4(Xv6Test):
  name = "shmem_access_double_call_fork"
  description = "shmem_access called once in parent process. It is then called again after fork in child process. The address received should be the same address the parent process received."
  tester = "ctests/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 10
  timeout = 20

class ATest5(Xv6Test):
  name = "shmem_access_read_write"
  description = "making sure shared pages are readable and writable"
  tester = "ctests/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 10
  timeout = 20

class ATest6(Xv6Test):
  name = "shmem_access_communication"
  description = "one process writing something and the other process reading it."
  tester = "ctests/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 10
  timeout = 20

#class ATest7(Xv6Test):
#  name = "shmem_access_full_address_space"
#  description = "shmem_access should failed if the entire address space is full."
#  tester = "ctests/" + name + ".c"
#  make_qemu_args = "CPUS=1"
#  point_value = 10
#  timeout = 20

class ATest8(Xv6Test):
  name = "shmem_access_full_address_space2"
  description = "sbrk should not allocate and go past a shared memory."
  tester = "ctests/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 10
  timeout = 25

class ATest9(Xv6Test):
  name = "shmem_access_persistent"
  description = "making sure shared pages are not deallocated when no one references them."
  tester = "ctests/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 10
  timeout = 20

class ATest10(Xv6Test):
  name = "shmem_access_exec"
  description = "a new exec-ed program should not have access to shared pages when it begins."
  tester = "ctests/" + name + ".c"
  tester_helper = "ctests/" + name + "_helper.c"
  make_qemu_args = "CPUS=1"
  point_value = 10
  timeout = 20

class ATest11(Xv6Test):
  name = "shmem_access_exec2"
  description = "a new exec-ed program should reallocate virtual pages if shmem_access is called."
  tester = "ctests/" + name + ".c"
  tester_helper = "ctests/" + name + "_helper.c"
  make_qemu_args = "CPUS=1"
  point_value = 10
  timeout = 20

class ATest12(Xv6Test):
  name = "shmem_access_syscall_args"
  description = "making sure pointers from shared pages can be successfully passed to system calls. ***NOTE*** only open and write system calls are tested here; when grading, we may change the test to any other system call that may take pointers."
  tester = "ctests/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 10
  timeout = 20

class CTest1(Xv6Test):
  name = "shmem_count_invalid_input"
  description = "shmem_count invalid input test"
  tester = "ctests/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 10
  timeout = 20

class CTest2(Xv6Test):
  name = "shmem_count_zero"
  description = "shmem_count should return 0 if no one is referencing the page."
  tester = "ctests/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 10
  timeout = 20

class CTest3(Xv6Test):
  name = "shmem_count_zero2"
  description = "shmem_count should return 0 after child process accesses and exits."
  tester = "ctests/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 10
  timeout = 20

class CTest4(Xv6Test):
  name = "shmem_count_one"
  description = "shmem_count should return 1 after 1 access."
  tester = "ctests/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 10
  timeout = 20

class CTest5(Xv6Test):
  name = "shmem_count_one2"
  description = "shmem_count should return 1 after 2 accesses to the same page."
  tester = "ctests/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 10
  timeout = 20

class CTest6(Xv6Test):
  name = "shmem_count_fork"
  description = "shmem_count should return 2 after fork if the parent process has accessed a shared page."
  tester = "ctests/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 10
  timeout = 20

class CTest7(Xv6Test):
  name = "shmem_count_exec"
  description = "Exec should decrement count for shared pages. Parent accesses a shared page, then it forks. Child performs exec to start a new program. In the new program, the count for the shared page should be 1."
  tester = "ctests/" + name + ".c"
  tester_helper = "ctests/" + name + "_helper.c"
  make_qemu_args = "CPUS=1"
  point_value = 10
  timeout = 20

import toolspath
from testing.runtests import main
#main(Xv6Build, [ATest8])
main(Xv6Build, [NTest1, NTest2, NTest3, ATest1, ATest2, ATest3, ATest4, ATest5, ATest6, ATest8, ATest9, ATest10, ATest11, ATest12, CTest1, CTest2, CTest3, CTest4, CTest5, CTest6, CTest7])
