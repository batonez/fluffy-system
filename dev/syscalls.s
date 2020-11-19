.text

_jxread:
  mov $0x2000003, %rax
  syscall
  ret

_jxwrite:
  mov $0x2000004, %rax
  syscall
  ret

_jxopen:
  mov $0x2000005, %rax
  syscall
  ret

_jxclose:
  mov $0x2000006, %rax
  syscall
  ret

_jxmmap:
  mov $0x20000C5, %rax
  mov %rcx, %r10
  syscall
  ret

_jxmunmap:
  mov $0x2000049, %rax
  syscall
  ret

_jxstat:
  mov $0x2000152, %rax
  syscall
  ret

_jxfstat:
  mov $0x2000153, %rax
  syscall
  ret

.global _jxread
.global _jxwrite
.global _jxopen
.global _jxclose
.global _jxmmap
.global _jxmunmap
.global _jxfstat

