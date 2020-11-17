.text

_read:
  mov $0x2000003, %rax
  syscall
  ret

_write:
  mov $0x2000004, %rax
  syscall
  ret

_open:
  mov $0x2000005, %rax
  syscall
  ret

_close:
  mov $0x2000006, %rax
  syscall
  ret

.global _read
.global _write
.global _open
.global _close

