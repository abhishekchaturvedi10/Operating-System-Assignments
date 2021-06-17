bits 16

org 0x7c00

boot16:

	call SwitchONA20
	cli
	lgdt [GDT_Descriptor]
	mov eax, cr0
	or eax, 0x1
	mov cr0, eax
	jmp Code_Segment : boot32
	
SwitchONA20:
	
	in al, 0x92
	or al, 2
	out 0x92, al
	ret


GDT_Null_Descriptor:
	
	dd 0
	dd 0

GDT_Data_Descriptor:
	
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 10010010b
	db 11001111b
	db 0x0

GDT_Code_Descriptor:
	
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 10011010b
	db 11001111b
	db 0x0

GDT_End:

Data_Segment equ GDT_Data_Descriptor - GDT_Null_Descriptor
Code_Segment equ GDT_Code_Descriptor - GDT_Null_Descriptor

GDT_Descriptor:
	
	GDT_Size:

		dw GDT_End - GDT_Null_Descriptor
		dd GDT_Null_Descriptor

bits 32

boot32:

	mov ax, Data_Segment
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	mov edx, cr0
    	mov ecx, 32  
	mov ebx,000B8000h

.loop:
	
	mov eax, 00000130h   
    	shl edx, 1           
    	adc eax, 0           
    	mov [ebx], ax
    	add ebx, 2
    	dec ecx
    	jnz .loop

times 510 - ($-$$) db 0
dw 0xaa55