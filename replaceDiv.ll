define i32 @foo(i32 %a, i32 %b) {
	%c = sdiv i32 %a, 64
	%d = add i32 3, 4
	%e = sdiv i32 %a, %b
	%f = sdiv i32 128, %e
	ret i32 %f
}

