
a.out:     file format elf64-x86-64


Disassembly of section .init:

0000000000400570 <_init>:
  400570:	48 83 ec 08          	sub    $0x8,%rsp
  400574:	48 8b 05 7d 0a 20 00 	mov    0x200a7d(%rip),%rax        # 600ff8 <_DYNAMIC+0x1d0>
  40057b:	48 85 c0             	test   %rax,%rax
  40057e:	74 05                	je     400585 <_init+0x15>
  400580:	e8 7b 00 00 00       	callq  400600 <__gmon_start__@plt>
  400585:	48 83 c4 08          	add    $0x8,%rsp
  400589:	c3                   	retq   

Disassembly of section .plt:

0000000000400590 <putchar@plt-0x10>:
  400590:	ff 35 72 0a 20 00    	pushq  0x200a72(%rip)        # 601008 <_GLOBAL_OFFSET_TABLE_+0x8>
  400596:	ff 25 74 0a 20 00    	jmpq   *0x200a74(%rip)        # 601010 <_GLOBAL_OFFSET_TABLE_+0x10>
  40059c:	0f 1f 40 00          	nopl   0x0(%rax)

00000000004005a0 <putchar@plt>:
  4005a0:	ff 25 72 0a 20 00    	jmpq   *0x200a72(%rip)        # 601018 <_GLOBAL_OFFSET_TABLE_+0x18>
  4005a6:	68 00 00 00 00       	pushq  $0x0
  4005ab:	e9 e0 ff ff ff       	jmpq   400590 <_init+0x20>

00000000004005b0 <puts@plt>:
  4005b0:	ff 25 6a 0a 20 00    	jmpq   *0x200a6a(%rip)        # 601020 <_GLOBAL_OFFSET_TABLE_+0x20>
  4005b6:	68 01 00 00 00       	pushq  $0x1
  4005bb:	e9 d0 ff ff ff       	jmpq   400590 <_init+0x20>

00000000004005c0 <printf@plt>:
  4005c0:	ff 25 62 0a 20 00    	jmpq   *0x200a62(%rip)        # 601028 <_GLOBAL_OFFSET_TABLE_+0x28>
  4005c6:	68 02 00 00 00       	pushq  $0x2
  4005cb:	e9 c0 ff ff ff       	jmpq   400590 <_init+0x20>

00000000004005d0 <__libc_start_main@plt>:
  4005d0:	ff 25 5a 0a 20 00    	jmpq   *0x200a5a(%rip)        # 601030 <_GLOBAL_OFFSET_TABLE_+0x30>
  4005d6:	68 03 00 00 00       	pushq  $0x3
  4005db:	e9 b0 ff ff ff       	jmpq   400590 <_init+0x20>

00000000004005e0 <fgets@plt>:
  4005e0:	ff 25 52 0a 20 00    	jmpq   *0x200a52(%rip)        # 601038 <_GLOBAL_OFFSET_TABLE_+0x38>
  4005e6:	68 04 00 00 00       	pushq  $0x4
  4005eb:	e9 a0 ff ff ff       	jmpq   400590 <_init+0x20>

00000000004005f0 <strcmp@plt>:
  4005f0:	ff 25 4a 0a 20 00    	jmpq   *0x200a4a(%rip)        # 601040 <_GLOBAL_OFFSET_TABLE_+0x40>
  4005f6:	68 05 00 00 00       	pushq  $0x5
  4005fb:	e9 90 ff ff ff       	jmpq   400590 <_init+0x20>

0000000000400600 <__gmon_start__@plt>:
  400600:	ff 25 42 0a 20 00    	jmpq   *0x200a42(%rip)        # 601048 <_GLOBAL_OFFSET_TABLE_+0x48>
  400606:	68 06 00 00 00       	pushq  $0x6
  40060b:	e9 80 ff ff ff       	jmpq   400590 <_init+0x20>

0000000000400610 <sprintf@plt>:
  400610:	ff 25 3a 0a 20 00    	jmpq   *0x200a3a(%rip)        # 601050 <_GLOBAL_OFFSET_TABLE_+0x50>
  400616:	68 07 00 00 00       	pushq  $0x7
  40061b:	e9 70 ff ff ff       	jmpq   400590 <_init+0x20>

0000000000400620 <exit@plt>:
  400620:	ff 25 32 0a 20 00    	jmpq   *0x200a32(%rip)        # 601058 <_GLOBAL_OFFSET_TABLE_+0x58>
  400626:	68 08 00 00 00       	pushq  $0x8
  40062b:	e9 60 ff ff ff       	jmpq   400590 <_init+0x20>

Disassembly of section .text:

0000000000400630 <_start>:
  400630:	31 ed                	xor    %ebp,%ebp
  400632:	49 89 d1             	mov    %rdx,%r9
  400635:	5e                   	pop    %rsi
  400636:	48 89 e2             	mov    %rsp,%rdx
  400639:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  40063d:	50                   	push   %rax
  40063e:	54                   	push   %rsp
  40063f:	49 c7 c0 a0 08 40 00 	mov    $0x4008a0,%r8
  400646:	48 c7 c1 30 08 40 00 	mov    $0x400830,%rcx
  40064d:	48 c7 c7 1d 07 40 00 	mov    $0x40071d,%rdi
  400654:	e8 77 ff ff ff       	callq  4005d0 <__libc_start_main@plt>
  400659:	f4                   	hlt    
  40065a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000400660 <deregister_tm_clones>:
  400660:	b8 77 10 60 00       	mov    $0x601077,%eax
  400665:	55                   	push   %rbp
  400666:	48 2d 70 10 60 00    	sub    $0x601070,%rax
  40066c:	48 83 f8 0e          	cmp    $0xe,%rax
  400670:	48 89 e5             	mov    %rsp,%rbp
  400673:	77 02                	ja     400677 <deregister_tm_clones+0x17>
  400675:	5d                   	pop    %rbp
  400676:	c3                   	retq   
  400677:	b8 00 00 00 00       	mov    $0x0,%eax
  40067c:	48 85 c0             	test   %rax,%rax
  40067f:	74 f4                	je     400675 <deregister_tm_clones+0x15>
  400681:	5d                   	pop    %rbp
  400682:	bf 70 10 60 00       	mov    $0x601070,%edi
  400687:	ff e0                	jmpq   *%rax
  400689:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000400690 <register_tm_clones>:
  400690:	b8 70 10 60 00       	mov    $0x601070,%eax
  400695:	55                   	push   %rbp
  400696:	48 2d 70 10 60 00    	sub    $0x601070,%rax
  40069c:	48 c1 f8 03          	sar    $0x3,%rax
  4006a0:	48 89 e5             	mov    %rsp,%rbp
  4006a3:	48 89 c2             	mov    %rax,%rdx
  4006a6:	48 c1 ea 3f          	shr    $0x3f,%rdx
  4006aa:	48 01 d0             	add    %rdx,%rax
  4006ad:	48 d1 f8             	sar    %rax
  4006b0:	75 02                	jne    4006b4 <register_tm_clones+0x24>
  4006b2:	5d                   	pop    %rbp
  4006b3:	c3                   	retq   
  4006b4:	ba 00 00 00 00       	mov    $0x0,%edx
  4006b9:	48 85 d2             	test   %rdx,%rdx
  4006bc:	74 f4                	je     4006b2 <register_tm_clones+0x22>
  4006be:	5d                   	pop    %rbp
  4006bf:	48 89 c6             	mov    %rax,%rsi
  4006c2:	bf 70 10 60 00       	mov    $0x601070,%edi
  4006c7:	ff e2                	jmpq   *%rdx
  4006c9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000004006d0 <__do_global_dtors_aux>:
  4006d0:	80 3d a1 09 20 00 00 	cmpb   $0x0,0x2009a1(%rip)        # 601078 <completed.6973>
  4006d7:	75 11                	jne    4006ea <__do_global_dtors_aux+0x1a>
  4006d9:	55                   	push   %rbp
  4006da:	48 89 e5             	mov    %rsp,%rbp
  4006dd:	e8 7e ff ff ff       	callq  400660 <deregister_tm_clones>
  4006e2:	5d                   	pop    %rbp
  4006e3:	c6 05 8e 09 20 00 01 	movb   $0x1,0x20098e(%rip)        # 601078 <completed.6973>
  4006ea:	f3 c3                	repz retq 
  4006ec:	0f 1f 40 00          	nopl   0x0(%rax)

00000000004006f0 <frame_dummy>:
  4006f0:	48 83 3d 28 07 20 00 	cmpq   $0x0,0x200728(%rip)        # 600e20 <__JCR_END__>
  4006f7:	00 
  4006f8:	74 1e                	je     400718 <frame_dummy+0x28>
  4006fa:	b8 00 00 00 00       	mov    $0x0,%eax
  4006ff:	48 85 c0             	test   %rax,%rax
  400702:	74 14                	je     400718 <frame_dummy+0x28>
  400704:	55                   	push   %rbp
  400705:	bf 20 0e 60 00       	mov    $0x600e20,%edi
  40070a:	48 89 e5             	mov    %rsp,%rbp
  40070d:	ff d0                	callq  *%rax
  40070f:	5d                   	pop    %rbp
  400710:	e9 7b ff ff ff       	jmpq   400690 <register_tm_clones>
  400715:	0f 1f 00             	nopl   (%rax)
  400718:	e9 73 ff ff ff       	jmpq   400690 <register_tm_clones>

000000000040071d <main>:
  40071d:	55                   	push   %rbp
  40071e:	48 89 e5             	mov    %rsp,%rbp
  400721:	48 81 ec a0 01 00 00 	sub    $0x1a0,%rsp
  400728:	89 bd 6c fe ff ff    	mov    %edi,-0x194(%rbp)
  40072e:	48 89 b5 60 fe ff ff 	mov    %rsi,-0x1a0(%rbp)
  400735:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  40073c:	00 00 
  40073e:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  400742:	31 c0                	xor    %eax,%eax
  400744:	b8 00 00 00 00       	mov    $0x0,%eax
  400749:	e8 d2 00 00 00       	callq  400820 <proginit>
  40074e:	bf b8 08 40 00       	mov    $0x4008b8,%edi
  400753:	b8 00 00 00 00       	mov    $0x0,%eax
  400758:	e8 63 fe ff ff       	callq  4005c0 <printf@plt>
  40075d:	48 8b 15 0c 09 20 00 	mov    0x20090c(%rip),%rdx        # 601070 <__TMC_END__>
  400764:	48 8d 85 70 fe ff ff 	lea    -0x190(%rbp),%rax
  40076b:	be 80 00 00 00       	mov    $0x80,%esi
  400770:	48 89 c7             	mov    %rax,%rdi
  400773:	e8 68 fe ff ff       	callq  4005e0 <fgets@plt>
  400778:	bf 0a 00 00 00       	mov    $0xa,%edi
  40077d:	e8 1e fe ff ff       	callq  4005a0 <putchar@plt>
  400782:	8b 15 f4 08 20 00    	mov    0x2008f4(%rip),%edx        # 60107c <i>
  400788:	48 8d 8d 70 fe ff ff 	lea    -0x190(%rbp),%rcx
  40078f:	48 8d 85 f0 fe ff ff 	lea    -0x110(%rbp),%rax
  400796:	be e0 08 40 00       	mov    $0x4008e0,%esi
  40079b:	48 89 c7             	mov    %rax,%rdi
  40079e:	b8 00 00 00 00       	mov    $0x0,%eax
  4007a3:	e8 68 fe ff ff       	callq  400610 <sprintf@plt>
  4007a8:	8b 15 ce 08 20 00    	mov    0x2008ce(%rip),%edx        # 60107c <i>
  4007ae:	48 8d 85 70 ff ff ff 	lea    -0x90(%rbp),%rax
  4007b5:	b9 08 09 40 00       	mov    $0x400908,%ecx
  4007ba:	be e0 08 40 00       	mov    $0x4008e0,%esi
  4007bf:	48 89 c7             	mov    %rax,%rdi
  4007c2:	b8 00 00 00 00       	mov    $0x0,%eax
  4007c7:	e8 44 fe ff ff       	callq  400610 <sprintf@plt>
  4007cc:	48 8d 95 f0 fe ff ff 	lea    -0x110(%rbp),%rdx
  4007d3:	48 8d 85 70 ff ff ff 	lea    -0x90(%rbp),%rax
  4007da:	48 89 d6             	mov    %rdx,%rsi
  4007dd:	48 89 c7             	mov    %rax,%rdi
  4007e0:	e8 0b fe ff ff       	callq  4005f0 <strcmp@plt>
  4007e5:	85 c0                	test   %eax,%eax
  4007e7:	75 23                	jne    40080c <main+0xef>
  4007e9:	bf 38 09 40 00       	mov    $0x400938,%edi
  4007ee:	e8 bd fd ff ff       	callq  4005b0 <puts@plt>
  4007f3:	48 8d 85 f0 fe ff ff 	lea    -0x110(%rbp),%rax
  4007fa:	48 89 c7             	mov    %rax,%rdi
  4007fd:	e8 ae fd ff ff       	callq  4005b0 <puts@plt>
  400802:	bf 00 00 00 00       	mov    $0x0,%edi
  400807:	e8 14 fe ff ff       	callq  400620 <exit@plt>
  40080c:	bf 68 09 40 00       	mov    $0x400968,%edi
  400811:	e8 9a fd ff ff       	callq  4005b0 <puts@plt>
  400816:	bf 00 00 00 00       	mov    $0x0,%edi
  40081b:	e8 00 fe ff ff       	callq  400620 <exit@plt>

0000000000400820 <proginit>:
  400820:	55                   	push   %rbp
  400821:	48 89 e5             	mov    %rsp,%rbp
  400824:	c7 05 4e 08 20 00 e5 	movl   $0x1e5,0x20084e(%rip)        # 60107c <i>
  40082b:	01 00 00 
  40082e:	5d                   	pop    %rbp
  40082f:	c3                   	retq   

0000000000400830 <__libc_csu_init>:
  400830:	41 57                	push   %r15
  400832:	41 89 ff             	mov    %edi,%r15d
  400835:	41 56                	push   %r14
  400837:	49 89 f6             	mov    %rsi,%r14
  40083a:	41 55                	push   %r13
  40083c:	49 89 d5             	mov    %rdx,%r13
  40083f:	41 54                	push   %r12
  400841:	4c 8d 25 c8 05 20 00 	lea    0x2005c8(%rip),%r12        # 600e10 <__frame_dummy_init_array_entry>
  400848:	55                   	push   %rbp
  400849:	48 8d 2d c8 05 20 00 	lea    0x2005c8(%rip),%rbp        # 600e18 <__init_array_end>
  400850:	53                   	push   %rbx
  400851:	4c 29 e5             	sub    %r12,%rbp
  400854:	31 db                	xor    %ebx,%ebx
  400856:	48 c1 fd 03          	sar    $0x3,%rbp
  40085a:	48 83 ec 08          	sub    $0x8,%rsp
  40085e:	e8 0d fd ff ff       	callq  400570 <_init>
  400863:	48 85 ed             	test   %rbp,%rbp
  400866:	74 1e                	je     400886 <__libc_csu_init+0x56>
  400868:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  40086f:	00 
  400870:	4c 89 ea             	mov    %r13,%rdx
  400873:	4c 89 f6             	mov    %r14,%rsi
  400876:	44 89 ff             	mov    %r15d,%edi
  400879:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  40087d:	48 83 c3 01          	add    $0x1,%rbx
  400881:	48 39 eb             	cmp    %rbp,%rbx
  400884:	75 ea                	jne    400870 <__libc_csu_init+0x40>
  400886:	48 83 c4 08          	add    $0x8,%rsp
  40088a:	5b                   	pop    %rbx
  40088b:	5d                   	pop    %rbp
  40088c:	41 5c                	pop    %r12
  40088e:	41 5d                	pop    %r13
  400890:	41 5e                	pop    %r14
  400892:	41 5f                	pop    %r15
  400894:	c3                   	retq   
  400895:	66 66 2e 0f 1f 84 00 	data32 nopw %cs:0x0(%rax,%rax,1)
  40089c:	00 00 00 00 

00000000004008a0 <__libc_csu_fini>:
  4008a0:	f3 c3                	repz retq 

Disassembly of section .fini:

00000000004008a4 <_fini>:
  4008a4:	48 83 ec 08          	sub    $0x8,%rsp
  4008a8:	48 83 c4 08          	add    $0x8,%rsp
  4008ac:	c3                   	retq   
