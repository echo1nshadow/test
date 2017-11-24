data segment
	array	db	12,34,42,43,54,56,57,58,59,60,74,76,77,78,79,80
	succ	db	"find successfully", 0dh,0ah, "$"
	fail	db	"fing unsuccessfully",0dh,0ah,"$"
	n	equ	9
data	ends

code segment
	assume	cs:code	ds:data
begin:
	mov	ax,data
	mov	ds,ax
	mov	al,n
	lea	si,array
	lea	di,succ
	dec	di
	cmp	al,[si]
	ja	next
	je	succ1
	jmp	fail1
next:	cmp	al,[di]
	jb	search
	je	succ1
	jmp	fail1
search: xor	bx,bx
	add 	bx,si
	add	bx,di
	shr	bx,1
	cmp	bx,si
	jz	fail1
	cmp	al,[bx]
	je	succ1
	ja	bove
	mov	di,bx
	jmp	search
bove:	mov	si,bx
	jmp	search

succ1:	mov	dx,offset succ
	mov	ah,09h
	int	21h
	jmp	exit1
fail1:	mov	dx,offset fail
	mov	ah,09h
	int	21h
exit1:	mov	ah,4ch
	int	21h
code ends
	end begin	
