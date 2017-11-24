	data segment
	    	array db 12h,23h,21h,54h,34h,60h,33h
		count equ $-array
	data ends
	
	stack segment para stack
		dw 10h dup(?)
	stack ends

	code segment
		assume cs:code, ds:data,ss:stack
	begin:
		mov	ax,data
		mov	ds,ax
		mov	cx,count-1
	lop1:	push	cx
		xor	si,si
	lop2:	mov	al,array[si]
		cmp	al,array[si+1]
		jge	next
		xchg	al,array[si+1]
		mov	array[si],al
	next:	inc	si
		loop	lop2
		pop	cx
		dec	cx
		jnz	lop1

		call 	display
		mov	ah,4ch
		int	21h

	display	proc near
		;mov 	cx, count
	    ;dis:
	;	mov bx,count
	;	sub bx,cx
	;	add bx,array
		lea dx,array
		mov al,dx
		mov ah,2
		int 21h
	;	dec cx
	;	loop dis
		ret
	display	endp
	code 	ends
		end	begin
