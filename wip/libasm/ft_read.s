global _ft_read
section .text

; https://filippo.io/linux-syscall-table/ 
; https://opensource.apple.com/source/xnu/xnu-1504.3.12/bsd/kern/syscalls.master

; https://stackoverflow.com/a/48845698/7292958 (reason of the 0x2000000 offset)

_ft_read:
	push r12
	push r13
	push r14
	
	mov r12, rdi					; // Argument 1: (int) fildes
	mov r13, rsi					; // Argument 2: (void *) buf
	mov r14, rdx					; // Argument 3: (size_t) nbyte

	mov rax, 0x2000003				; set to syscall #3: read

	mov rdi, r12					; passing parameter: file descriptor
	mov rsi, r13					; passing parameter: buffer
	mov rdx, r14					; passing parameter: buffer_size
	syscall							; do syscall

	pop r14
	pop r13
	pop r12

	ret								; do return