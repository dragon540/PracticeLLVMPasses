define i32 @foo(i32 %a, i32 %b) {
	%c = add i32 1, 2
	%d = add i32 3, %c
	%k = mul i32 55, 11
	%e = add i32 %a, %k;
	%f = mul i32 %e, %b
	ret i32 %f
}

