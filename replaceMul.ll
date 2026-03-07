define i32 @foo(i32 %a, i32 %b) {
	%c = mul i32 %a,64
	%d = add i32 3, 4
	%e = mul i32 %a, %b
	%f = mul i32 128, %e
	ret i32 %f
}

