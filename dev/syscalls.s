.text

_jread:
  mov $0x2000003, %rax
  syscall
  ret

_jwrite:
  mov $0x2000004, %rax
  syscall
  ret

_jopen:
  mov $0x2000005, %rax
  syscall
  ret

_jclose:
  mov $0x2000006, %rax
  syscall
  ret

_jmmap:
  mov $0x20000C5, %rax
  mov %rcx, %r10
  syscall
  ret

_jmunmap:
  mov $0x2000049, %rax
  syscall
  ret

.global _jread
.global _jwrite
.global _jopen
.global _jclose
.global _jmmap
.global _jmunmap
