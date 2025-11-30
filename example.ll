define i32 @foo(i32 %a, i32 %b) {
	%c = add i32 1, 2
	%d = add i32 3, 4
	%e = add i32 %a, %b
	ret i32 %e
}
