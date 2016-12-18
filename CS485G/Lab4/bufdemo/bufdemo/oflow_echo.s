
oflow_echo:     file format elf64-x86-64


Disassembly of section .init:

0000000000400450 <_init>:
  400450:	48 83 ec 08          	sub    $0x8,%rsp
  400454:	48 8b 05 9d 0b 20 00 	mov    0x200b9d(%rip),%rax        # 600ff8 <_DYNAMIC+0x1d0>
  40045b:	48 85 c0             	test   %rax,%rax
  40045e:	74 05                	je     400465 <_init+0x15>
  400460:	e8 4b 00 00 00       	callq  4004b0 <__gmon_start__@plt>
  400465:	48 83 c4 08          	add    $0x8,%rsp
  400469:	c3                   	retq   

Disassembly of section .plt:

0000000000400470 <puts@plt-0x10>:
  400470:	ff 35 92 0b 20 00    	pushq  0x200b92(%rip)        # 601008 <_GLOBAL_OFFSET_TABLE_+0x8>
  400476:	ff 25 94 0b 20 00    	jmpq   *0x200b94(%rip)        # 601010 <_GLOBAL_OFFSET_TABLE_+0x10>
  40047c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400480 <puts@plt>:
  400480:	ff 25 92 0b 20 00    	jmpq   *0x200b92(%rip)        # 601018 <_GLOBAL_OFFSET_TABLE_+0x18>
  400486:	68 00 00 00 00       	pushq  $0x0
  40048b:	e9 e0 ff ff ff       	jmpq   400470 <_init+0x20>

0000000000400490 <__libc_start_main@plt>:
  400490:	ff 25 8a 0b 20 00    	jmpq   *0x200b8a(%rip)        # 601020 <_GLOBAL_OFFSET_TABLE_+0x20>
  400496:	68 01 00 00 00       	pushq  $0x1
  40049b:	e9 d0 ff ff ff       	jmpq   400470 <_init+0x20>

00000000004004a0 <getchar@plt>:
  4004a0:	ff 25 82 0b 20 00    	jmpq   *0x200b82(%rip)        # 601028 <_GLOBAL_OFFSET_TABLE_+0x28>
  4004a6:	68 02 00 00 00       	pushq  $0x2
  4004ab:	e9 c0 ff ff ff       	jmpq   400470 <_init+0x20>

00000000004004b0 <__gmon_start__@plt>:
  4004b0:	ff 25 7a 0b 20 00    	jmpq   *0x200b7a(%rip)        # 601030 <_GLOBAL_OFFSET_TABLE_+0x30>
  4004b6:	68 03 00 00 00       	pushq  $0x3
  4004bb:	e9 b0 ff ff ff       	jmpq   400470 <_init+0x20>

00000000004004c0 <exit@plt>:
  4004c0:	ff 25 72 0b 20 00    	jmpq   *0x200b72(%rip)        # 601038 <_GLOBAL_OFFSET_TABLE_+0x38>
  4004c6:	68 04 00 00 00       	pushq  $0x4
  4004cb:	e9 a0 ff ff ff       	jmpq   400470 <_init+0x20>

Disassembly of section .text:

00000000004004d0 <_start>:
  4004d0:	31 ed                	xor    %ebp,%ebp
  4004d2:	49 89 d1             	mov    %rdx,%r9
  4004d5:	5e                   	pop    %rsi
  4004d6:	48 89 e2             	mov    %rsp,%rdx
  4004d9:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  4004dd:	50                   	push   %rax
  4004de:	54                   	push   %rsp
  4004df:	49 c7 c0 e0 06 40 00 	mov    $0x4006e0,%r8
  4004e6:	48 c7 c1 70 06 40 00 	mov    $0x400670,%rcx
  4004ed:	48 c7 c7 bd 05 40 00 	mov    $0x4005bd,%rdi
  4004f4:	e8 97 ff ff ff       	callq  400490 <__libc_start_main@plt>
  4004f9:	f4                   	hlt    
  4004fa:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000400500 <deregister_tm_clones>:
  400500:	b8 57 10 60 00       	mov    $0x601057,%eax
  400505:	55                   	push   %rbp
  400506:	48 2d 50 10 60 00    	sub    $0x601050,%rax
  40050c:	48 83 f8 0e          	cmp    $0xe,%rax
  400510:	48 89 e5             	mov    %rsp,%rbp
  400513:	77 02                	ja     400517 <deregister_tm_clones+0x17>
  400515:	5d                   	pop    %rbp
  400516:	c3                   	retq   
  400517:	b8 00 00 00 00       	mov    $0x0,%eax
  40051c:	48 85 c0             	test   %rax,%rax
  40051f:	74 f4                	je     400515 <deregister_tm_clones+0x15>
  400521:	5d                   	pop    %rbp
  400522:	bf 50 10 60 00       	mov    $0x601050,%edi
  400527:	ff e0                	jmpq   *%rax
  400529:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000400530 <register_tm_clones>:
  400530:	b8 50 10 60 00       	mov    $0x601050,%eax
  400535:	55                   	push   %rbp
  400536:	48 2d 50 10 60 00    	sub    $0x601050,%rax
  40053c:	48 c1 f8 03          	sar    $0x3,%rax
  400540:	48 89 e5             	mov    %rsp,%rbp
  400543:	48 89 c2             	mov    %rax,%rdx
  400546:	48 c1 ea 3f          	shr    $0x3f,%rdx
  40054a:	48 01 d0             	add    %rdx,%rax
  40054d:	48 d1 f8             	sar    %rax
  400550:	75 02                	jne    400554 <register_tm_clones+0x24>
  400552:	5d                   	pop    %rbp
  400553:	c3                   	retq   
  400554:	ba 00 00 00 00       	mov    $0x0,%edx
  400559:	48 85 d2             	test   %rdx,%rdx
  40055c:	74 f4                	je     400552 <register_tm_clones+0x22>
  40055e:	5d                   	pop    %rbp
  40055f:	48 89 c6             	mov    %rax,%rsi
  400562:	bf 50 10 60 00       	mov    $0x601050,%edi
  400567:	ff e2                	jmpq   *%rdx
  400569:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000400570 <__do_global_dtors_aux>:
  400570:	80 3d d9 0a 20 00 00 	cmpb   $0x0,0x200ad9(%rip)        # 601050 <__TMC_END__>
  400577:	75 11                	jne    40058a <__do_global_dtors_aux+0x1a>
  400579:	55                   	push   %rbp
  40057a:	48 89 e5             	mov    %rsp,%rbp
  40057d:	e8 7e ff ff ff       	callq  400500 <deregister_tm_clones>
  400582:	5d                   	pop    %rbp
  400583:	c6 05 c6 0a 20 00 01 	movb   $0x1,0x200ac6(%rip)        # 601050 <__TMC_END__>
  40058a:	f3 c3                	repz retq 
  40058c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400590 <frame_dummy>:
  400590:	48 83 3d 88 08 20 00 	cmpq   $0x0,0x200888(%rip)        # 600e20 <__JCR_END__>
  400597:	00 
  400598:	74 1e                	je     4005b8 <frame_dummy+0x28>
  40059a:	b8 00 00 00 00       	mov    $0x0,%eax
  40059f:	48 85 c0             	test   %rax,%rax
  4005a2:	74 14                	je     4005b8 <frame_dummy+0x28>
  4005a4:	55                   	push   %rbp
  4005a5:	bf 20 0e 60 00       	mov    $0x600e20,%edi
  4005aa:	48 89 e5             	mov    %rsp,%rbp
  4005ad:	ff d0                	callq  *%rax
  4005af:	5d                   	pop    %rbp
  4005b0:	e9 7b ff ff ff       	jmpq   400530 <register_tm_clones>
  4005b5:	0f 1f 00             	nopl   (%rax)
  4005b8:	e9 73 ff ff ff       	jmpq   400530 <register_tm_clones>

00000000004005bd <main>:
  4005bd:	55                   	push   %rbp
  4005be:	48 89 e5             	mov    %rsp,%rbp
  4005c1:	b8 00 00 00 00       	mov    $0x0,%eax
  4005c6:	e8 52 00 00 00       	callq  40061d <echo>
  4005cb:	eb f4                	jmp    4005c1 <main+0x4>

00000000004005cd <mygets>:
  4005cd:	55                   	push   %rbp
  4005ce:	48 89 e5             	mov    %rsp,%rbp
  4005d1:	48 83 ec 20          	sub    $0x20,%rsp
  4005d5:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
  4005d9:	e8 c2 fe ff ff       	callq  4004a0 <getchar@plt>
  4005de:	89 45 fc             	mov    %eax,-0x4(%rbp)
  4005e1:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  4005e5:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
  4005e9:	eb 19                	jmp    400604 <mygets+0x37>
  4005eb:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  4005ef:	48 8d 50 01          	lea    0x1(%rax),%rdx
  4005f3:	48 89 55 f0          	mov    %rdx,-0x10(%rbp)
  4005f7:	8b 55 fc             	mov    -0x4(%rbp),%edx
  4005fa:	88 10                	mov    %dl,(%rax)
  4005fc:	e8 9f fe ff ff       	callq  4004a0 <getchar@plt>
  400601:	89 45 fc             	mov    %eax,-0x4(%rbp)
  400604:	83 7d fc ff          	cmpl   $0xffffffff,-0x4(%rbp)
  400608:	74 06                	je     400610 <mygets+0x43>
  40060a:	83 7d fc 0a          	cmpl   $0xa,-0x4(%rbp)
  40060e:	75 db                	jne    4005eb <mygets+0x1e>
  400610:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  400614:	c6 00 00             	movb   $0x0,(%rax)
  400617:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  40061b:	c9                   	leaveq 
  40061c:	c3                   	retq   

000000000040061d <echo>:
  40061d:	55                   	push   %rbp
  40061e:	48 89 e5             	mov    %rsp,%rbp
  400621:	48 83 ec 10          	sub    $0x10,%rsp
  400625:	48 8d 45 f0          	lea    -0x10(%rbp),%rax
  400629:	48 89 c7             	mov    %rax,%rdi
  40062c:	e8 9c ff ff ff       	callq  4005cd <mygets>
  400631:	48 8d 45 f0          	lea    -0x10(%rbp),%rax
  400635:	48 89 c7             	mov    %rax,%rdi
  400638:	e8 43 fe ff ff       	callq  400480 <puts@plt>
  40063d:	c9                   	leaveq 
  40063e:	c3                   	retq   

000000000040063f <not_called>:
  40063f:	55                   	push   %rbp
  400640:	48 89 e5             	mov    %rsp,%rbp
  400643:	bf f8 06 40 00       	mov    $0x4006f8,%edi
  400648:	e8 33 fe ff ff       	callq  400480 <puts@plt>
  40064d:	bf 18 07 40 00       	mov    $0x400718,%edi
  400652:	e8 29 fe ff ff       	callq  400480 <puts@plt>
  400657:	bf 00 00 00 00       	mov    $0x0,%edi
  40065c:	e8 5f fe ff ff       	callq  4004c0 <exit@plt>
  400661:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  400668:	00 00 00 
  40066b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000400670 <__libc_csu_init>:
  400670:	41 57                	push   %r15
  400672:	41 89 ff             	mov    %edi,%r15d
  400675:	41 56                	push   %r14
  400677:	49 89 f6             	mov    %rsi,%r14
  40067a:	41 55                	push   %r13
  40067c:	49 89 d5             	mov    %rdx,%r13
  40067f:	41 54                	push   %r12
  400681:	4c 8d 25 88 07 20 00 	lea    0x200788(%rip),%r12        # 600e10 <__frame_dummy_init_array_entry>
  400688:	55                   	push   %rbp
  400689:	48 8d 2d 88 07 20 00 	lea    0x200788(%rip),%rbp        # 600e18 <__init_array_end>
  400690:	53                   	push   %rbx
  400691:	4c 29 e5             	sub    %r12,%rbp
  400694:	31 db                	xor    %ebx,%ebx
  400696:	48 c1 fd 03          	sar    $0x3,%rbp
  40069a:	48 83 ec 08          	sub    $0x8,%rsp
  40069e:	e8 ad fd ff ff       	callq  400450 <_init>
  4006a3:	48 85 ed             	test   %rbp,%rbp
  4006a6:	74 1e                	je     4006c6 <__libc_csu_init+0x56>
  4006a8:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  4006af:	00 
  4006b0:	4c 89 ea             	mov    %r13,%rdx
  4006b3:	4c 89 f6             	mov    %r14,%rsi
  4006b6:	44 89 ff             	mov    %r15d,%edi
  4006b9:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  4006bd:	48 83 c3 01          	add    $0x1,%rbx
  4006c1:	48 39 eb             	cmp    %rbp,%rbx
  4006c4:	75 ea                	jne    4006b0 <__libc_csu_init+0x40>
  4006c6:	48 83 c4 08          	add    $0x8,%rsp
  4006ca:	5b                   	pop    %rbx
  4006cb:	5d                   	pop    %rbp
  4006cc:	41 5c                	pop    %r12
  4006ce:	41 5d                	pop    %r13
  4006d0:	41 5e                	pop    %r14
  4006d2:	41 5f                	pop    %r15
  4006d4:	c3                   	retq   
  4006d5:	66 66 2e 0f 1f 84 00 	data32 nopw %cs:0x0(%rax,%rax,1)
  4006dc:	00 00 00 00 

00000000004006e0 <__libc_csu_fini>:
  4006e0:	f3 c3                	repz retq 

Disassembly of section .fini:

00000000004006e4 <_fini>:
  4006e4:	48 83 ec 08          	sub    $0x8,%rsp
  4006e8:	48 83 c4 08          	add    $0x8,%rsp
  4006ec:	c3                   	retq   
