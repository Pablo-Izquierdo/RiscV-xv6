import toolspath
from testing import Xv6Build, Xv6Test

class Test0(Xv6Test):
   name = "macros"
   description = "Make sure the macros are the right value."
   tester = "ctests/" + name + ".c"
   make_qemu_args = "CPUS=1"
   point_value = 5
   timeout = 500

class Test1(Xv6Test):
   name = "create"
   description = "Creates a small file and makes sure the type is properly set."
   tester = "ctests/" + name + ".c"
   make_qemu_args = "CPUS=1"
   point_value = 10
   timeout = 500

class Test2(Xv6Test):
  name = "create2"
  description = "Should not create a small file if O_SMALLFILE is passed in but not O_CREATE."
  tester = "ctests/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 10
  timeout = 500

class Test3(Xv6Test):
  name = "open"
  description = "Open() called a second time without O_CREATE and O_SMALLFILE. Checks file's type to make sure it is T_SMALLFILE and that read and write still work"
  tester = "ctests/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 10
  timeout = 500

class Test4(Xv6Test):
  name = "read"
  description = "Tries to read more than possible and makes sure only amount available is read."
  tester = "ctests/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 10
  timeout = 500

class Test5(Xv6Test):
  name = "read2"
  description = "Reads one byte at a time from small file."
  tester = "ctests/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 10
  timeout = 500

class Test6(Xv6Test):
  name = "write"
  description = "Tries to write more than possible to a small file and makes sure only 52 bytes are written."
  tester = "ctests/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 10
  timeout = 500

class Test7(Xv6Test):
  name = "write2"
  description = "Repeatedly opens, writes, closes a small file. The last write should be the one that is persisted."
  tester = "ctests/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 10
  timeout = 500

class Test8(Xv6Test):
  name = "write3"
  description = "Repeatedly opens, writes to the end, closes a small file until file is full."
  tester = "ctests/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 10
  timeout = 500

class Test9(Xv6Test):
  name = "write4"
  description = "Small write followed by a big write to a small file should truncate the big write upto max small file size."
  tester = "ctests/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 10
  timeout = 500

class Test10(Xv6Test):
  name = "readonly"
  description = "Makes sure small files can be opened as read only and writes would fail."
  tester = "ctests/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 10
  timeout = 500

class Test11(Xv6Test):
  name = "writeonly"
  description = "Makes sure small files can be opened as write only and reads would fail."
  tester = "ctests/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 10
  timeout = 500

class Test12(Xv6Test):
  name = "remove"
  description = "Makes sure removing a small file does not corrupt the file system by freeing blocks."
  tester = "ctests/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 10
  timeout = 500

class Test13(Xv6Test):
  name = "fulldisk"
  description = "First uses all free blocks on disk for normal files and then makes sure small files can still be created. ***Note that the test will take a while since big files are created.***"
  tester = "ctests/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 10
  timeout = 10

class Test14(Xv6Test):
  name = "stress"
  description = "Creates and deletes a lot of small files one at a time to make sure nothing breaks under a heavy load."
  tester = "ctests/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 10
  timeout = 500

class Test15(Xv6Test):
  name = "stress2"
  description = "Creates and deletes a lot of small files 100 of them at a time to make sure nothing breaks under a heavy load. ***Note that the test will take a VERY long time since a lot of files are created.***"
  tester = "ctests/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 10
  timeout = 500

class Test16(Xv6Test):
  name = "smallbig"
  description = "Creates bunch of small files; then creates bunch of big files to make sure normal files are not affected."
  tester = "ctests/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 10
  timeout = 500

class Test17(Xv6Test):
  name = "inode"
  description = "Uses all inodes in the file system; then repeatedly deleted and creates a file and makes sure the correct inode is reused for the new file."
  tester = "ctests/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 10
  timeout = 500

class Test18(Xv6Test):
  name = "inode2"
  description = "Uses all inodes in the file system; then repeatedly deletes bunch of files and then creates that many files and makes sure the correct inodes are reused for the new files."
  tester = "ctests/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 10
  timeout = 500

class Test19(Xv6Test):
  name = "usertests"
  description = "Running standard tests to make sure you did not break anything for normal files. ***Note that the test will take a while since a lot of things are being tested.***"
  tester = "ctests/" + name + ".c"
  make_qemu_args = "CPUS=1"
  point_value = 10
  timeout = 500

import toolspath
from testing.runtests import main
#main(Xv6Build, [Test17])
main(Xv6Build, [Test0, Test1, Test2, Test3, Test4, Test5, Test6, Test7, Test8, Test9, Test10, Test11, Test12, Test13, Test14, Test15, Test16, Test17, Test18, Test19])



