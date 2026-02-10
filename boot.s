bits 16
global init

init:
    jmp init

times   0x1fe - ($ - $$)    db  0

signature       dw      0xaa55
