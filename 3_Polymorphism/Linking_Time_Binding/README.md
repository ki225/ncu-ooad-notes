# Linking Time Binding
- 這是將多個目標檔（.o）結合成一個執行檔的過程。
- 以下實驗會呈現編譯器在 .o 檔留下 R_X86_64_PLT32 標記（預留位址為 0），鏈結器（Linker）在最後把 actions.o 裡的真實位址填進去。

## 執行靜態連結指令
Linker 會將這兩個檔案合併成一個執行檔

1. 編譯成目標檔 (Object File)
    ```sh
    gcc -c actions.c -o actions.o
    gcc -c main.c -o main.o
    ```


## 觀察目標檔
```sh
objdump -d -r main.o
```

完整組合語言
```
main.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <main>:
   0:   f3 0f 1e fa             endbr64
   4:   55                      push   %rbp
   5:   48 89 e5                mov    %rsp,%rbp
   8:   48 83 ec 10             sub    $0x10,%rsp
   c:   66 0f ef c0             pxor   %xmm0,%xmm0
  10:   f3 0f 11 45 f4          movss  %xmm0,-0xc(%rbp)
  15:   f3 0f 10 05 00 00 00    movss  0x0(%rip),%xmm0        # 1d <main+0x1d>
  1c:   00
                        19: R_X86_64_PC32       .rodata-0x4
  1d:   f3 0f 11 45 f8          movss  %xmm0,-0x8(%rbp)
  22:   f3 0f 10 05 00 00 00    movss  0x0(%rip),%xmm0        # 2a <main+0x2a>
  29:   00
                        26: R_X86_64_PC32       .rodata
  2a:   f3 0f 11 45 fc          movss  %xmm0,-0x4(%rbp)
  2f:   b8 00 00 00 00          mov    $0x0,%eax
  34:   e8 00 00 00 00          call   39 <main+0x39>
                        35: R_X86_64_PLT32      sit_on_it-0x4
  39:   b8 00 00 00 00          mov    $0x0,%eax
  3e:   e8 00 00 00 00          call   43 <main+0x43>
                        3f: R_X86_64_PLT32      think_it-0x4
  43:   b8 00 00 00 00          mov    $0x0,%eax
  48:   e8 00 00 00 00          call   4d <main+0x4d>
                        49: R_X86_64_PLT32      do_something-0x4
  4d:   f3 0f 10 45 f4          movss  -0xc(%rbp),%xmm0
  52:   f3 0f 58 45 f8          addss  -0x8(%rbp),%xmm0
  57:   f3 0f 11 45 f4          movss  %xmm0,-0xc(%rbp)
  5c:   b8 00 00 00 00          mov    $0x0,%eax
  61:   c9                      leave
  62:   c3                      ret
```

可以看到 Static Linking 之前是沒有寫死位址的
- `e8` 是呼叫指令，後面的 `00 00 00 00` 就是位址佔位符。因為編譯器根本不知道 `sit_on_it` 在哪裡，所以先填零
```
  34:   e8 00 00 00 00          call   39 <main+0x39>
                        35: R_X86_64_PLT32      sit_on_it-0x4
  3e:   e8 00 00 00 00          call   43 <main+0x43>
                        3f: R_X86_64_PLT32      think_it-0x4
  48:   e8 00 00 00 00          call   4d <main+0x4d>
                        49: R_X86_64_PLT32      do_something-0x4
```

## 觀察 Relocation Table
- Relocation tables on x86 manage external symbols (functions/data) by providing necessary addressing updates to instructions when a binary is loaded into memory. 
- They link unresolved symbols (e.g., `R_386_JMP_SLOT`, `R_X86_64_PLT32`) at runtime, using the Global Offset Table (GOT) or Procedure Linkage Table (PLT) to resolve addresses for functions not in the local binary. 
  - [x86: Relocation Types](https://docs.oracle.com/cd/E19683-01/817-3677/chapter6-26/index.html)


```sh
readelf -r main.o
```
指出了 main.o 程式碼中哪些地方需要「填入」外部位址。
```
Relocation section '.rela.text' at offset 0x228 contains 5 entries:
  Offset          Info           Type           Sym. Value    Sym. Name + Addend
000000000019  000300000002 R_X86_64_PC32     0000000000000000 .rodata - 4
000000000026  000300000002 R_X86_64_PC32     0000000000000000 .rodata + 0
000000000035  000500000004 R_X86_64_PLT32    0000000000000000 sit_on_it - 4
00000000003f  000600000004 R_X86_64_PLT32    0000000000000000 think_it - 4
000000000049  000700000004 R_X86_64_PLT32    0000000000000000 do_something - 4

Relocation section '.rela.eh_frame' at offset 0x2a0 contains 1 entry:
  Offset          Info           Type           Sym. Value    Sym. Name + Addend
```

## 結果
連結時若同時提供了 main.c 和 actions.o，會直接跳轉到函式的真實位址，而不經過 PLT 轉發
```sh
gcc main.o actions.o -o my_program
```
```
my_program:     file format elf64-x86-64


Disassembly of section .init:

0000000000001000 <_init>:
    1000:       f3 0f 1e fa             endbr64
    1004:       48 83 ec 08             sub    $0x8,%rsp
    1008:       48 8b 05 d9 2f 00 00    mov    0x2fd9(%rip),%rax        # 3fe8 <__gmon_start__@Base>
    100f:       48 85 c0                test   %rax,%rax
    1012:       74 02                   je     1016 <_init+0x16>
    1014:       ff d0                   call   *%rax
    1016:       48 83 c4 08             add    $0x8,%rsp
    101a:       c3                      ret

Disassembly of section .plt:

0000000000001020 <.plt>:
    1020:       ff 35 a2 2f 00 00       push   0x2fa2(%rip)        # 3fc8 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:       ff 25 a4 2f 00 00       jmp    *0x2fa4(%rip)        # 3fd0 <_GLOBAL_OFFSET_TABLE_+0x10>
    102c:       0f 1f 40 00             nopl   0x0(%rax)

Disassembly of section .plt.got:

0000000000001030 <__cxa_finalize@plt>:
    1030:       f3 0f 1e fa             endbr64
    1034:       ff 25 be 2f 00 00       jmp    *0x2fbe(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    103a:       66 0f 1f 44 00 00       nopw   0x0(%rax,%rax,1)

Disassembly of section .text:

0000000000001040 <_start>:
    1040:       f3 0f 1e fa             endbr64
    1044:       31 ed                   xor    %ebp,%ebp
    1046:       49 89 d1                mov    %rdx,%r9
    1049:       5e                      pop    %rsi
    104a:       48 89 e2                mov    %rsp,%rdx
    104d:       48 83 e4 f0             and    $0xfffffffffffffff0,%rsp
    1051:       50                      push   %rax
    1052:       54                      push   %rsp
    1053:       45 31 c0                xor    %r8d,%r8d
    1056:       31 c9                   xor    %ecx,%ecx
    1058:       48 8d 3d ca 00 00 00    lea    0xca(%rip),%rdi        # 1129 <main>
    105f:       ff 15 73 2f 00 00       call   *0x2f73(%rip)        # 3fd8 <__libc_start_main@GLIBC_2.34>
    1065:       f4                      hlt
    1066:       66 2e 0f 1f 84 00 00    cs nopw 0x0(%rax,%rax,1)
    106d:       00 00 00

0000000000001070 <deregister_tm_clones>:
    1070:       48 8d 3d 99 2f 00 00    lea    0x2f99(%rip),%rdi        # 4010 <__TMC_END__>
    1077:       48 8d 05 92 2f 00 00    lea    0x2f92(%rip),%rax        # 4010 <__TMC_END__>
    107e:       48 39 f8                cmp    %rdi,%rax
    1081:       74 15                   je     1098 <deregister_tm_clones+0x28>
    1083:       48 8b 05 56 2f 00 00    mov    0x2f56(%rip),%rax        # 3fe0 <_ITM_deregisterTMCloneTable@Base>
    108a:       48 85 c0                test   %rax,%rax
    108d:       74 09                   je     1098 <deregister_tm_clones+0x28>
    108f:       ff e0                   jmp    *%rax
    1091:       0f 1f 80 00 00 00 00    nopl   0x0(%rax)
    1098:       c3                      ret
    1099:       0f 1f 80 00 00 00 00    nopl   0x0(%rax)

00000000000010a0 <register_tm_clones>:
    10a0:       48 8d 3d 69 2f 00 00    lea    0x2f69(%rip),%rdi        # 4010 <__TMC_END__>
    10a7:       48 8d 35 62 2f 00 00    lea    0x2f62(%rip),%rsi        # 4010 <__TMC_END__>
    10ae:       48 29 fe                sub    %rdi,%rsi
    10b1:       48 89 f0                mov    %rsi,%rax
    10b4:       48 c1 ee 3f             shr    $0x3f,%rsi
    10b8:       48 c1 f8 03             sar    $0x3,%rax
    10bc:       48 01 c6                add    %rax,%rsi
    10bf:       48 d1 fe                sar    $1,%rsi
    10c2:       74 14                   je     10d8 <register_tm_clones+0x38>
    10c4:       48 8b 05 25 2f 00 00    mov    0x2f25(%rip),%rax        # 3ff0 <_ITM_registerTMCloneTable@Base>
    10cb:       48 85 c0                test   %rax,%rax
    10ce:       74 08                   je     10d8 <register_tm_clones+0x38>
    10d0:       ff e0                   jmp    *%rax
    10d2:       66 0f 1f 44 00 00       nopw   0x0(%rax,%rax,1)
    10d8:       c3                      ret
    10d9:       0f 1f 80 00 00 00 00    nopl   0x0(%rax)

00000000000010e0 <__do_global_dtors_aux>:
    10e0:       f3 0f 1e fa             endbr64
    10e4:       80 3d 25 2f 00 00 00    cmpb   $0x0,0x2f25(%rip)        # 4010 <__TMC_END__>
    10eb:       75 2b                   jne    1118 <__do_global_dtors_aux+0x38>
    10ed:       55                      push   %rbp
    10ee:       48 83 3d 02 2f 00 00    cmpq   $0x0,0x2f02(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    10f5:       00
    10f6:       48 89 e5                mov    %rsp,%rbp
    10f9:       74 0c                   je     1107 <__do_global_dtors_aux+0x27>
    10fb:       48 8b 3d 06 2f 00 00    mov    0x2f06(%rip),%rdi        # 4008 <__dso_handle>
    1102:       e8 29 ff ff ff          call   1030 <__cxa_finalize@plt>
    1107:       e8 64 ff ff ff          call   1070 <deregister_tm_clones>
    110c:       c6 05 fd 2e 00 00 01    movb   $0x1,0x2efd(%rip)        # 4010 <__TMC_END__>
    1113:       5d                      pop    %rbp
    1114:       c3                      ret
    1115:       0f 1f 00                nopl   (%rax)
    1118:       c3                      ret
    1119:       0f 1f 80 00 00 00 00    nopl   0x0(%rax)

0000000000001120 <frame_dummy>:
    1120:       f3 0f 1e fa             endbr64
    1124:       e9 77 ff ff ff          jmp    10a0 <register_tm_clones>

0000000000001129 <main>:
    1129:       f3 0f 1e fa             endbr64
    112d:       55                      push   %rbp
    112e:       48 89 e5                mov    %rsp,%rbp
    1131:       48 83 ec 10             sub    $0x10,%rsp
    1135:       66 0f ef c0             pxor   %xmm0,%xmm0
    1139:       f3 0f 11 45 f4          movss  %xmm0,-0xc(%rbp)
    113e:       f3 0f 10 05 be 0e 00    movss  0xebe(%rip),%xmm0        # 2004 <_IO_stdin_used+0x4>
    1145:       00
    1146:       f3 0f 11 45 f8          movss  %xmm0,-0x8(%rbp)
    114b:       f3 0f 10 05 b5 0e 00    movss  0xeb5(%rip),%xmm0        # 2008 <_IO_stdin_used+0x8>
    1152:       00
    1153:       f3 0f 11 45 fc          movss  %xmm0,-0x4(%rbp)
    1158:       b8 00 00 00 00          mov    $0x0,%eax
    115d:       e8 35 00 00 00          call   1197 <sit_on_it>
    1162:       b8 00 00 00 00          mov    $0x0,%eax
    1167:       e8 36 00 00 00          call   11a2 <think_it>
    116c:       b8 00 00 00 00          mov    $0x0,%eax
    1171:       e8 16 00 00 00          call   118c <do_something>
    1176:       f3 0f 10 45 f4          movss  -0xc(%rbp),%xmm0
    117b:       f3 0f 58 45 f8          addss  -0x8(%rbp),%xmm0
    1180:       f3 0f 11 45 f4          movss  %xmm0,-0xc(%rbp)
    1185:       b8 00 00 00 00          mov    $0x0,%eax
    118a:       c9                      leave
    118b:       c3                      ret

000000000000118c <do_something>:
    118c:       f3 0f 1e fa             endbr64
    1190:       55                      push   %rbp
    1191:       48 89 e5                mov    %rsp,%rbp
    1194:       90                      nop
    1195:       5d                      pop    %rbp
    1196:       c3                      ret

0000000000001197 <sit_on_it>:
    1197:       f3 0f 1e fa             endbr64
    119b:       55                      push   %rbp
    119c:       48 89 e5                mov    %rsp,%rbp
    119f:       90                      nop
    11a0:       5d                      pop    %rbp
    11a1:       c3                      ret

00000000000011a2 <think_it>:
    11a2:       f3 0f 1e fa             endbr64
    11a6:       55                      push   %rbp
    11a7:       48 89 e5                mov    %rsp,%rbp
    11aa:       90                      nop
    11ab:       5d                      pop    %rbp
    11ac:       c3                      ret

Disassembly of section .fini:

00000000000011b0 <_fini>:
    11b0:       f3 0f 1e fa             endbr64
    11b4:       48 83 ec 08             sub    $0x8,%rsp
    11b8:       48 83 c4 08             add    $0x8,%rsp
    11bc:       c3                      ret
```
